#ifdef STM32F4
#include "stm32f4xx_hal.h"
#endif
#ifdef STM32F7
#include "stm32f7xx_hal.h"
#endif
#ifdef STM32H7
#include "stm32h7xx_hal.h"
#endif

#include "lathe.h"

#define EXT extern
#include "serialio.h"

/*
putBufCharIsr output

d - z axis deceleration done
s - spindle isr stop
E - start axis trigger
R - z axis starting runout of x axis
S - initializing sync rising edge of index pulse
X - start x axis based on spindle position
Z - start z axis based on spindle position

putBufStrIsr output

zt - z axis stopped tapering
zD - z axis stopped normal operation
za - z axis acceleration done
zd - z axis deceleration done stopping
xt - x axis stopped tapering
xD - x axis stopped normal operation
xa - x axis acceleration done
xd - x axis deceleration done stopping
x0 - x axis not in sync mod update feed rate
 */

/* position encoder isr */

#define encoderISR(x) EXTI15_10_IRQHandler(x)

/* jog encoder isr */

#define jogISR(x) EXTI9_5_IRQHandler(x)

void spIsrStop(void);
void zIsrStop(char ch);
void xIsrStop(char ch);

extern "C" void encoderISR(void);
extern "C" void jogISR(void);
extern "C" void pwmTmrISR(void);
extern "C" void TIM1_UP_TIM10_IRQHandler(void);
extern "C" void TIM1_TRG_COM_TIM11_IRQHandler(void);
extern "C" void indexISR(void);
extern "C" void spindleTmrISR(void);
extern "C" void zTmrISR(void);
extern "C" void xTmrISR(void);
extern "C" void spEncISR(void);
extern "C" void encISR(void);
extern "C" void cmpTmrISR(void);
extern "C" void intTmrISR(void);
extern "C" void indexTmrISR(void);
extern "C" void step3TmrISR(void);
extern "C" void step4TmrISR(void);
extern "C" void step5TmrISR(void);
extern "C" void encTestTmrISR(void);

int decoder[16] =
{
 0,		/* 0000 0 */
 DIR_NEG,	/* 0001 1 r0 !l_b & !l_a & !c_b &  c_1 */
 DIR_POS,	/* 0010 2 f0 !l_b & !l_a &  c_b & !c_1 */
 0,		/* 0011 3 */
 DIR_POS,	/* 0100 4 f1 !l_b &  l_a & !c_b & !c_1 */
 0,		/* 0101 5 */
 0,		/* 0110 6 */
 DIR_NEG,	/* 0111 7 r3 !l_b &  l_a &  c_b &  c_1 */
 DIR_NEG,	/* 1000 8 r1  l_b & !l_a & !c_b & !c_1 */
 0,		/* 1001 9 */
 0,		/* 1010 a */
 DIR_POS,	/* 1011 b f3  l_b & !l_a &  c_b &  c_1 */
 0,		/* 1100 c */
 DIR_POS,	/* 1101 d f2  l_b &  l_a & !c_b &  c_1 */
 DIR_NEG,	/* 1110 e r2  l_b &  l_a &  c_b & !c_1 */
 0,		/* 1111 f */
};

int zLastDecode;
BITWORD zDecode;
int xLastDecode;
BITWORD xDecode;

int jog1LastDecode;
int jog2LastDecode;

unsigned int lastZJogUSec;
unsigned int lastZJogMSec;
unsigned int lastXJogUSec;
unsigned int lastXJogMSec;

extern "C" void encoderISR(void)
{
 BITWORD tmp;
 if (EXTI->PR & (ZA_Pin | ZB_Pin)) /* if bit change */
 {
  if (EXTI->PR & ZA_Pin)
   EXTI->PR = ZA_Pin;
  if (EXTI->PR & ZB_Pin)
   EXTI->PR = ZB_Pin;

  tmp.w = (zLastDecode >> 2);	/* shift last bits into position */
  tmp.w &= 3;			/* make sure only lower two bits present */
  if (zA())			/* if encoder a */
   tmp.b2 = 1;			/* save in decode word */
  if (zB())			/* if encoder b */
   tmp.b3 = 1;			/* save in decode word */
  zLastDecode = tmp.w;		/* save for next interrupt */

  int val = decoder[tmp.w];	/* look up direction */
  zDecode.w = tmp.w;
  if (zDroInvert)		/* if dro motion inverted */
   val = -val;			/* change direction */
  zDroPos += val;		/* update position */

  if (zIsr.useDro)		/* if using dro for move */
  {
   int dist;
   if (zIsr.dir > 0)		/* if direction positive */
   {
    dist = zIsr.droTarget - zDroPos;
   }
   else				/* if direction negative */
   {
    dist =  zDroPos - zIsr.droTarget;
   }
   if (dist < zDroFinalDist)	/* if close to end */
   {
    if (dist > 0)		/* if not done */
    {
     if (zIsr.decel)		/* if decelerating */
     {
      zIsr.accelStep = 0;	/* end deceleration */
      zIsr.curCount = xIsr.finalCtr;
      zTmrMax(zIsr.curCount);
     }
    }
    else			/* if done */
    {
     zIsrStop('0');		/* stop isr */
    }
   }
  }
  dbgZDroClr();
 }

 if (EXTI->PR & (XA_Pin | XB_Pin)) /* if bit change */
 {
  dbgXDroSet();

  if (EXTI->PR & XA_Pin)
   EXTI->PR = XA_Pin;
  if (EXTI->PR & XB_Pin)
   EXTI->PR = XB_Pin;

  tmp.w = (xLastDecode >> 2);	/* shift last bits into position */
  tmp.w &= 3;			/* make sure only lower two bits present */
  if (xA())			/* if encoder a */
   tmp.b2 = 1;			/* save in decode word */
  if (xB())			/* if encoder b */
   tmp.b3 = 1;			/* save in decode word */
  xLastDecode = tmp.w;		/* save for next interrupt */

  int val = decoder[tmp.w];	/* look up direction */
  xDecode.w = tmp.w;
  if (xDroInvert)		/* if dro motion inverted */
   val = -val;			/* change direction */
  xDroPos += val;		/* update position */

  if (xIsr.useDro)		/* if using dro for move */
  {
   int dist;
   if (xIsr.dir > 0)		/* if direction positive */
   {
    dist = xIsr.droTarget - xDroPos;
   }
   else				/* if direction negative */
   {
    dist =  xDroPos - xIsr.droTarget;
   }
   if (dist < xDroFinalDist)	/* if close to end */
   {
    if (dist > 0)		/* if not done */
    {
     if (xIsr.decel)		/* if decelerating */
     {
      xIsr.accelStep = 0;	/* end deceleration */
      xIsr.curCount = xIsr.finalCtr;
      xTmrMax(xIsr.curCount);
     }
    }
    else			/* if done */
    {
     xIsrStop('0');		/* stop isr */
    }
   }
  }
  dbgXDroClr();
 }
}

extern "C" void jogISR(void)
{
 BITWORD tmp;
 dbgJogIsrClr();
 if (EXTI->PR & (JogA1_Pin | JogB1_Pin)) /* if bit change */
 {
  if (EXTI->PR & JogA1_Pin)
   EXTI->PR = JogA1_Pin;
  if (EXTI->PR & JogB1_Pin)
   EXTI->PR = JogB1_Pin;	/* clear change bits */

  tmp.w = (jog1LastDecode >> 2); /* shift last bits into position */
  tmp.w &= 3;			/* make sure only lower two bits present */
  if (jogA1())			/* if encoder a */
   tmp.b2 = 1;			/* save in decode word */
  if (jogB1())			/* if encoder b */
   tmp.b3 = 1;			/* save in decode word */

  if (jogDebug)			/* debugging */
  {
   char c = tmp.w & 0xf;
   if (c <= 9)
    putBufCharIsr('0' + c);
   else
    putBufCharIsr('A' - 10 + c);
   putBufCharIsr(' ');
  }
  
  if ((jog1LastDecode == 0x7 && tmp.w == 1)
  ||  (jog1LastDecode == 0xb && tmp.w == 2))
  {
   P_JOGQUE jog = &zJogQue;
   if (jog->count < MAXJOG)
   {
    dbgJogIsrSet();
    jog->count++;
#if 1
    unsigned int mSec = millis();
    unsigned short uSec = usecTmrRead();
    unsigned int delta = mSec - lastZJogMSec;
    MPG_VAL val;
    if (delta <= 20)		/* if less than 20 msec */
    {
     val.delta = (uSec - lastZJogUSec); /* use micro seconds */
    }
    else			/* if greater than 20 msec */
    {
     if (delta > 50)		/* if greater than 50 mSec */
      delta = 50;		/* set to 50 mSec */
     val.delta = delta * 1000;	/* convert to uSec */
    }
    lastZJogMSec = mSec;	/* set new last msec value */
    lastZJogUSec = uSec;	/* set new last usec value */
    val.dir = (char) decoder[tmp.w]; /* combine with delta time */
    jog->buf[jog->fil] = val.intVal; /* add to queue */
#else
    jog->buf[jog->fil] = decoder[tmp.w];
#endif
    jog->fil++;
    if (jog->fil >= MAXJOG)
     jog->fil = 0;
   }
  }
 }
 jog1LastDecode = tmp.w;	/* save for next interrupt */

 if (EXTI->PR & (JogA2_Pin | JogB2_Pin)) /* if bit change */
 {
  if (EXTI->PR & JogA2_Pin)
   EXTI->PR = JogA2_Pin;
  if (EXTI->PR & JogB2_Pin)
   EXTI->PR = JogB2_Pin;	/* clear change bits */

  tmp.w = (jog2LastDecode >> 2); /* shift last bits into position */
  tmp.w &= 3;			/* make sure only lower two bits present */
  if (jogA2())			/* if encoder a */
   tmp.b2 = 1;			/* save in decode word */
  if (jogB2())			/* if encoder b */
   tmp.b3 = 1;			/* save in decode word */

  if constexpr (DBGTRK1W1)
  {
   dbgTrk1W((((decoder[tmp.w] & 0xf) << 4) | (tmp.w & 0xf)));
  }
  
  if (jogDebug)			/* debugging */
  {
   char c = tmp.w & 0xf;
   if (c <= 9)
    putBufCharIsr('0' + c);
   else
    putBufCharIsr('A' - 10 + c);
   putBufCharIsr(' ');
  }

  if ((jog2LastDecode == 0x7 && tmp.w == 1)
  ||  (jog2LastDecode == 0xb && tmp.w == 2))
  {
   P_JOGQUE jog = &xJogQue;
   if (jog->count < MAXJOG)	/* if queue not full */
   {
    dbgJogIsrSet();
    jog->count++;
#if 1
    unsigned int mSec = millis();
    unsigned short uSec = usecTmrRead();
    unsigned int delta = mSec - lastXJogMSec;
    MPG_VAL val;
    if (delta <= 20)		/* if less than 20 msec */
    {
     val.delta = (uSec - lastXJogUSec); /* use micro seconds */
    }
    else			/* if greater than 20 msec */
    {
     if (delta > 50)		/* if greater than 50 mSec */
      delta = 50;		/* set to 50 mSec */
     val.delta = delta * 1000;	/* convert to uSec */
    }
    lastXJogMSec = mSec;	/* set new last msec value */
    lastXJogUSec = uSec;	/* set new last usec value */
    val.dir = (char) decoder[tmp.w]; /* combine with delta time */
    jog->buf[jog->fil] = val.intVal; /* add to queue */
#else
    jog->buf[jog->fil] = decoder[tmp.w];
#endif
    jog->fil++;
    if (jog->fil >= MAXJOG)
     jog->fil = 0;
   }
  }
  jog2LastDecode = tmp.w;	/* save for next interrupt */
 }
}

#ifdef PWM_TIMER
extern "C" void pwmTmrISR(void)
{
 if (pwmTmrIF())
 {
  pwmTmrClrIF();
 }
}
#endif

extern "C" void TIM1_UP_TIM10_IRQHandler(void)
{
 if constexpr (STEP3_TIMER == 1)
 {
  if (step3TmrIF())
  {
   step3TmrISR();
  }
 }

 if constexpr (X_TIMER == 1)
 {
  if (xTmrIF())
  {
   xTmrISR();
  }
 }
 
 if constexpr (PWM_TIMER == 1)
 {
  if (pwmTmrIF())
  {
   pwmTmrISR();
  }
 }

 if constexpr (INT_TIMER == 1)
 {
  if (intTmrIF())		/* if int timer */
  {
   intTmrISR();			/* call interrupt service routine */
  }
 }

 if constexpr ((INDEX_TIMER == 1) || (INDEX_TIMER == 10))
 {
  indexTmrISR();
 }
}

extern "C" void TIM1_TRG_COM_TIM11_IRQHandler(void)
{
 if constexpr (INT_TIMER == 11)
 {
  if (intTmrIF())		/* if int timer */
  {
   intTmrISR();			/* call interrupt service routine */
  }
 }
}

extern "C" void indexISR(void)
{
 EXTI->PR = Index_Pin;		/* clear index interrupt */
 
 static T_INDEX_COUNTER indexTmp;

 indexTmrStop();
 indexTmp.overflow = indexOverflow; /* copy overflow value */
 indexTmp.count = indexTmrRead(); /* read index timer */
 indexTmrStart();		/* restart counter */
 if (indexStart != 0)		/* if not the first index interrupt */
 {
  indexPeriod = indexTmp.period - indexStart; /* save to period */
 }
 indexStart = indexTmp.period;	/* set start for next period */

 if (trackSpeed)		/* if tracking speed */
  updateFeed = 1;		/* set to update the feed */

 if constexpr (DBGTRK1L0)	/* if debug tracking index period */
 {
  uint32_t tmp = (uint32_t) indexPeriod;
  tmp /= 10;
  tmp = indexTrkFreq / tmp;
  dbgTrk1L(tmp);
 }
 indexUpdateTime = millis();	/* set update time */
 indexTimeout = INDEX_TIMEOUT;	/* and timeout */
 revCounter++;			/* increment revolution counter */

 if (spindleEncoder)		/* *ok* if using spindle encoder */
 {
  if (zIsr.syncStart)		/* if z axis waiting for sync start */
  {
   zIsr.active = zIsr.syncStart; /* set to active */
   zIsr.syncStart = 0;		/* clear start flag */
   dbgmsg(D_ZEST, spEncCount);	/* encoder count at start */
  }

  if (xIsr.syncStart)		/* if x axis waiting for sync start */
  {
   xIsr.active = xIsr.syncStart; /* set to active */
   xIsr.syncStart = 0;		/* clear start flag */
   dbgmsg(D_XEST, spEncCount);	/* encoder count at start */
  }
 }
 
 if constexpr (DBGTRK1W0)	/* if debug tracking index pulse */
 {
  dbgTrk1W(sp.pos);
 }
}

void spIsrStop(void)
{
 spindleTmrPWMDis();		/* stop step pulse */
 spindleTmrStop();		/* stop timer */
 spindleTmrClrIE();		/* disable interrupt */
 sp.decel = 0;			/* clear flag */
 indexPeriod = 0;		/* set to period of zero */
 sp.active = 0;			/* indicate spindle stopped */
 putBufCharIsr('s');
}

#define DBG_SPINDLE 1

int spStep;

extern "C" void spindleTmrISR(void)
{
 dbgSpIsrSet();
 spindleTmrClrIF();		/* clear interrupt flag */

 sp.intCount += 1;		/* count an interrupt */
 if (sp.dist != 0)		/* if distance set */
 {
  --sp.dist;			/* count off distance */
  if ((sp.decel == 0)		/* if not decelerating */
  &&  (sp.dist <= (sp.accelStep - sp.initialStep))) /* if time to decel */
  {
   sp.accel = 0;		/* stop acceleration */
   sp.decel = 1;		/* start deceleration */
  }
  if (sp.dist == 0)		/* if done */
  {
   spIsrStop();			/* stop spindle */
  }
 }

 if constexpr (SP_ENC)
 {
  switch (encState)             /* select on state */
  {
  case 0:
   aSet();
   break;
  case 1:
   bSet();
   break;
  case 2:
   aClr();
   break;
  case 3:
   bClr();
   break;
  }
  encState += 1;                /* update state */
  encState &= 0x3;              /* mas in range */
 }
 
 char index;
 if (spTestIndex)		/* if testing index pulse */
 {
  if (spTestEncoder)		/* if testing encoder */
  {
   EXTI->SWIER |= ExtInt_Pin;	/* generate software interrupt */
  }
  
  if (spStep < sp.stepsRev)	/* if not at index pulse */
  {
   spStep++;			/* increment step */
   index = 0;			/* clear index */
  }
  else				/* if at index pulse */
  {
   spStep = 0;			/* reset step counter */
   index = 1;			/* set index pin */
   EXTI->SWIER |= Index_Pin;	/* generate software interrupt */
  }
 }
 else
  index = idx();		/* read index pulse */

 if (sp.initSync)		/* if initializing sync */
 {
  if (sp.findSync == 1)		/* if looking for pulse */
  {
   if ((index != 0)		/* if rising edge */
   &&  (sp.lastIndex == 0))	/* of index pulse */
   {
    putBufCharIsr('S');
    sp.findSync = 0;		/* clear find flag */
    sp.initSync = 0;		/* clear init flag */
    sp.pos = 0;			/* set position to zero */
   }
  }
  else				/* if waiting for index = 0 */
  {
   if (index == 0)		/* if pulse not set */
    sp.findSync = 1;		/* set to look for pulse */
  }
 }
 else				/* if not initializing */
 {
#if 0
  if constexpr (0)		/* **disabled */
  {
   if ((index != 0)		/* if rising edge */
   &&  (sp.lastIndex == 0))	/* of index pulse */
   {
    indexPeriod = indexTmrRead(); /* read index timer */
    indexTmrClr();		/* reset index timer */
    if constexpr (DBGTRK1W0)	/* if debug tracking index pulse */
    {
     dbgTrk1W(sp.pos);
    }
   }
  }
#endif
  
  dbgSpRevClr();
  sp.pos++;			/* update position */
  if (sp.pos >= sp.stepsRev)	/* if completed revolution */
  {
   sp.pos = 0;			/* reset position */
   sp.rev++;			/* count another revolution */
   if (sp.startAxis & START_TRIG) /* if time to trigger start */
   {
    sp.startAxis &= ~START_TRIG; /* clear trigger */
    sp.startAxis |= START_ENA;	/* and set enable */
    sp.cycleCounter = sp.stepsCycle - sp.stepsRev; /* init spindle cyc ctr */
    putBufCharIsr('E');
   }
   dbgSpRevSet();
  }
 }
 sp.lastIndex = index;		/* save index for next interrupt */

 if (sp.accel)			/* if accelerating */
 {
  if (sp.accelStep < sp.finalStep) /* if acceleration active */
  {
   sp.accelStep++;		/* count a step */
   int count = (int) (sp.cFactor * sqrt(sp.accelStep)); /* calc next */
   int ctr = count - sp.lastCount; /* value to load in timer */
   if (ctr > 65535)		/* if more than 16 bits */
   {
    int pre = 1;		/* initialize prescaler */
    while (ctr > 65535)		/* while counter out of range */
    {
     ctr >>= 1;			/* divide counter by two */
     pre <<= 1;			/* multiple prescaler by two */
    }
    sp.lastCount += ctr * pre;	/* update last count based on real count*/
    sp.curCount = ctr;		/* save timer value */
    --pre;			/* subtract one for hw value */
    spindleTmrScl(pre);		/* load prescaler */
   }
   else
   {
    sp.lastCount = count;	/* save last count */
    spindleTmrScl(0);		/* load prescaler */
   }
   sp.curCount = ctr;		/* save timer value */
   --ctr;			/* subtract one for load value */
   spindleTmrSet(ctr);		/* load counter value */
  }
  else				/* if acceleration done */
  {
   spindleTmrMax(sp.clocksStep); /* load final counter value */
   sp.accel = 0;		/* clear flag */
   cmpTmr.startInt = 1;		/* +++ test */
   dbgSpStopClr();
  }
 }
 else if (sp.decel)		/* if decelerating */
 {
  if (sp.accelStep > sp.initialStep) /* if decelerating */
  {
  --sp.accelStep;		/* count a step */
   int count = (int) (sp.cFactor * sqrt(sp.accelStep)); /* calc next */
   int ctr = sp.lastCount - count; /* value to load in timer */
   if (ctr > 65535)		/* if more than 16 bits */
   {
    int pre = 1;		/* initialize prescaler */
    while (ctr > 65535)		/* while counter out of range */
    {
     ctr >>= 1;			/* divide counter by two */
     pre <<= 1;			/* multiple prescaler by two */
    }
    sp.lastCount -= ctr * pre;	/* update last count based on real count*/
    sp.curCount = ctr;		/* save timer value */
    --pre;			/* subtract one for hw value */
    spindleTmrScl(pre);		/* load prescaler */
   }
   else				/* if 16 bits */
   {
    sp.lastCount = count;	/* save last count */
    spindleTmrScl(0);		/* load prescaler */
   }
   sp.curCount = ctr;		/* save timer value */
   --ctr;			/* subtract one for load value */
   spindleTmrSet(ctr);		/* load counter value */
  }
  else				/* if deceleration done */
  {
   if (zIsr.decel < 0)		/* if not stopping */
   {
    zIsr.curCount = zIsr.clocksStep; /* save current value */
    zTmrSet(zIsr.clocksStep);	/* load final counter value */
    zIsr.decel = 0;		/* stop decelerating */
   }
   else
   {
    spIsrStop();
    dbgSpStopClr();
   }
   putBufCharIsr('d');
  }
 }
 else				/* if running */
 {
  dbgSpCycClr();
  sp.cycleCounter++;		/* update spindle cycle counter */
  if (sp.cycleCounter >= sp.stepsCycle) /* if cycle counter at limit */
  {
   sp.cycleCounter = 0;		/* reset cycle counter */
   if constexpr (DBGTRK2L0)
   {
    dbgTrk2L(zIsr.cycleCounter, zTmrRead());
    dbgTrk2L(xIsr.cycleCounter, xTmrRead());
   }
   dbgSpCycSet();
  }

  dbgSlvClr();
  if (sp.startAxis & START_ENA)	/* if start flag set */
  {
   if (sp.startAxis & STARTZ)	/* if starting z */
   {
    if (sp.zStart == sp.pos)	/* if spindle at correct position */
    {
     sp.startAxis &= ~STARTZ;	/* clear flag */
     zStartSlave();		/* set up slave to start */
     putBufCharIsr('Z');
     dbgSlvSet();
    }
   }

   if (sp.startAxis & STARTX)	/* if starting x */
   {
    if (sp.xStart == sp.pos)	/* if spindle at correct position */
    {
     sp.startAxis &= ~STARTX;	/* clear flag */
     xStartSlave();		/* set up slave to start */
     putBufCharIsr('X');
     dbgSlvSet();
    }
   }
  }
 }
 dbgSpIsrClr();
}

void inline zCheckStep(void)
{
 dbgZEncSet();
 dbgZOutClr();

 zIsr.x += 1;
 if (zIsr.d < 0)
 {
  zIsr.d += zIsr.incr1;
 }
 else
 {
  dbgZOutSet();
  zIsr.y += 1;
  zPulse();
  zIsr.d += zIsr.incr2;
 }
 dbgZEncClr();
}

void inline xCheckStep(void)
{
 dbgXEncSet();
 dbgXOutClr();
 xIsr.x += 1;
 if (xIsr.d < 0)
 {
  xIsr.d += xIsr.incr1;
 }
 else
 {
  dbgXOutSet();
  xIsr.y += 1;
  xPulse();
  xIsr.d += xIsr.incr2;
 }
 dbgXEncClr();
}

void zIsrStop(char ch)
{
 zTmrSlvDis();			/* disable slave mode */
 zTmrStop();			/* stop timer */
 zTmrClrIE();			/* disable interrupt */
 zIsr.accel = 0;		/* clear accel */
 zIsr.decel = 0;		/* and decel flags */
 zIsr.sync = 0;			/* clear sync flag */
 zIsr.dist = 0;			/* clear distance */
 putBufCharIsr(ch);
 if (zIsr.active)		/* if synchcronized move */
 {
  zIsr.active = 0;		/* clear active flag */
  if (spindleEncoder == 0)	/* *ok* if stepper drive */
   dbgmsg(D_ZEDN, sp.intCount);	/* send spindle interrupt count */
  else				/* *ok* spindle encoder */
  {
   dbgZOutClr();
   dbgmsg(D_ZEDN, spEncCount);	/* send spindle encoder count */
   if (zIsr.encoderDirect == 0)	/* *ok* using encodder directly */
   {
    dbgmsg(D_ZX, zIsr.x);
    dbgmsg(D_ZY, zIsr.y);
   }
  }
 }
 if (zIsr.taper & TAPER_SLAVE)	/* if tapering */
 {
  zIsr.lastRemCount = zIsr.remCount; /* save remainder count */
  dbgZTaperClr();
  putBufStrIsr("zt");
 }
 else				/* if normal operation */
  putBufStrIsr("zD");
 
 zIsr.taper = 0;		/* clear taper flag */
 zIsr.done = 1;			/* indicate done */
 if (cfgDro)
  dbgmsg(D_ZDRO, zDroPos);
 dbgmsg(D_ZLOC, zLoc);
 dbgZAccelClr();
}

extern "C" void zTmrISR(void)
{
 dbgZIsrSet();
 zTmrClrIF();			/* clear interrupt flag */

 zLoc += zIsr.dir;		/* update position */
 zIsr.steps++;			/* count a step moved */

 if (zIsr.home)			/* 1*+ if homing operation */
 {
  updProbeDist();		/* update probe testing distance */
  if (zIsr.home & PROBE_SET)	/* if probing */
  {
   if (probeSet())		/* if probe set */
   {
    zIsr.doneHome = 1;		/* indicate probe done */
    zIsrStop('1');		/* stop movement */
   }
  }

  if (zIsr.home & FIND_HOME)	/* if looking for home */
  {
   if (xHomeIsSet())		/* if home found */
   {
    zIsr.doneHome = 1;		/* indicate homing done */
    zIsrStop('2');		/* stop movement */
   }
  }

  if (zIsr.home & CLEAR_HOME)	/* if moving off home */
  {
   if (xHomeClr())		/* if home moved off home */
   {
    zIsr.doneHome = 1;		/* indicate homing done */
    zIsrStop('3');		/* stop movement */
   }
  }
 }

 if (zIsr.dist != 0)		/* 2*+ if distance set */
 {
  --zIsr.dist;			/* decrement distance */
  if (zIsr.dist == 0)		/* if done */
  {
   if (!zIsr.useDro)		/* if not using dro */
   {
    zIsrStop('4');		/* stop isr */
   }
  }
  else				/* if not done */
  {
   if (zRunoutFlag
   &&  (zIsr.dist <= zRunoutStart)) /* if time to start runout */
   {
    if (spindleEncoder == 0)	/* *ok* if not using encoder */
    {
     xRunoutInit();		/* int x runout */
     xStartSlave();		/* start x as a slave */
     putBufStrIsr("R0");
    }
    else			/* *chk* if using encoder */
    {
     xIsr.active = xSyncInit;	/* set active flag to proper mode */
     putBufStrIsr("R1");
    }
    zRunoutFlag = 0;		/* clear flag */
    dbgRunoutSet();
   }
  
   if ((zIsr.cFactor != 0)	/* if acceleration enabled */
   &&  (zIsr.decel == 0)	/* and not decelerating */
   &&  (zIsr.dist <= (zIsr.accelStep - zIsr.initialStep))) /* time to decel */
   {
    zIsr.accel = 0;		/* stop acceleration */
    zIsr.decel = 1;		/* start deceleration */
    dbgZAccelSet();
   }
  } /* if not done */
 } /* if distance set */
 
 if (zIsr.accel)		/* 3*+ if accelerating */
 {
  if (zIsr.accelStep < zIsr.finalStep) /* if accelerating */
  {
   zIsr.accelStep++;		/* count a step */
   int count = (int) (zIsr.cFactor * sqrt(zIsr.accelStep)); /* calc next */
   zIsr.clockSum += zIsr.curCount;
   zIsr.curCount = count - zIsr.lastCount; /* value to load in timer */
   zIsr.lastCount = count;	/* set last count */
   zTmrMax(zIsr.curCount);	/* load counter value */
  }
  else				/* if acceleration done */
  {
   zIsr.clockSum += zIsr.curCount; /* final acceleration clock count */
   zIsr.curCount = zIsr.clocksStep; /* get clocks per step */
   zTmrMax(zIsr.curCount);	/* save current clocks per step */
   zIsr.accel = 0;		/* clear flag */
   dbgZAccelClr();
   putBufStrIsr("za");
  }
  if constexpr (DBGTRK2L1)
  {
   if (zMoveCtl.cmd & Z_SYN_START)
   {
    dbgTrk2L(zIsr.curCount, zIsr.lastCount);
   }
  }
 }
 else if (zIsr.decel)		/* 4*+ if decelerating */
 {
  if (zIsr.accelStep > zIsr.initialStep) /* if decelerating */
  {
   --zIsr.accelStep;		/* count a step */
   int count = (int) (zIsr.cFactor * sqrt(zIsr.accelStep)); /* calc next */
   zIsr.curCount = zIsr.lastCount - count; /* value to load in timer */
   zIsr.lastCount = count;	/* set last count */
   zTmrMax(zIsr.curCount);	/* load counter value */
  }
  else				/* if deceleration done */
  {
   if (zIsr.decel < 0)		/* if not stopping */
   {
    zIsr.curCount = zIsr.clocksStep; /* save current value */
    zTmrSet(zIsr.clocksStep);	/* load final counter value */
    zIsr.decel = 0;		/* stop decelerating */
   }
   else
   {
    if (!zIsr.useDro)		/* if not using dro */
    {
     zIsrStop('6');		/* stop isr */
     putBufStrIsr("zd");
    }
   }
  }
 }
 else				/* 5*+ tracking state */
 {
  if (zIsr.sync > 0)		/* if running in sync mode */
  {
   if (zIsr.sum < 0)		/* if tracking sum negative */
   {
    zIsr.sum += zIsr.incr1;	/* add incr1 value */
    zTmrSet(zIsr.counterStep1); /* load normal counter value */
   }
   else				/* if positive */
   {
    zIsr.sum += zIsr.incr2;	/* add incr2 value */
    zTmrSet(zIsr.counterStep2); /* load counter plus one value */
    zIsr.remCount++;
   }

   dbgZCycClr();
   zIsr.cycleCounter++;		/* update z cycle counter */
   if (zIsr.cycleCounter >= zIsr.stepsCycle) /* if z cycle finished */
   {
    zIsr.cycleCounter = 0;	/* reset z cycle */
    zIsr.lastRemCount = zIsr.remCount;
    zIsr.remCount = 0;
    dbgZCycSet();
   }
  }
  else				/* if not sync mode */
  {
   if (updateFeed)		/* if time to update feed */
   {
    updateFeed = 0;		/* clear flag */
    if (indexPeriod != 0)	/* if period valid */
    {
     zIsr.clocksStep = indexPeriod / zIsr.stepsCycle; /* update speed */
     zTmrMax(zIsr.clocksStep);	/* set interrupt timer */
     if constexpr (DBGTRK2L3)
     {
      dbgTrk2L(zIsr.clocksStep, indexPeriod);
     }
    }
   }
  }
 }
 dbgZIsrClr();
}

void xIsrStop(char ch)
{
 xTmrSlvDis();			/* disable slave mode */
 xTmrStop();			/* stop timer */
 xTmrClrIE();			/* disable interrupt */
 xIsr.accel = 0;		/* clear accel */
 xIsr.decel = 0;		/* and decel flags */
 xIsr.sync = 0;			/* clear sync flag */
 xIsr.dist = 0;			/* clear distance */
 
 putBufCharIsr(ch);
 if (xIsr.active)		/* if synchrinized move */
 {
  xIsr.active = 0;		/* clear active flag */
  if (spindleEncoder == 0)	/* *ok* if no encoder */
   dbgmsg(D_XEDN, sp.intCount);	/* send spindle interrupt count */
  else				/* *ok* */
  {
   dbgXOutClr();
   dbgmsg(D_XEDN, spEncCount);	/* send spindle encoder count */
   if (spindleSync == 0)	/* *ok* using encodder directly */
   {
    dbgmsg(D_XX, xIsr.x);
    dbgmsg(D_XY, xIsr.y);
   }
  }
 }
 
 if (xIsr.taper & TAPER_SLAVE)	/* if tapering */
 {
  xIsr.lastRemCount = xIsr.remCount; /* save remainder count */
  if (xIsr.taper & TAPER_RUNOUT)
  {
   dbgRunoutClr();
   dbgmsg(D_XSTP, xIsr.steps);
   dbgmsg(D_ZLOC, zLoc);
  }
  dbgXTaperClr();
  putBufStrIsr("xt");
 }
 else
  putBufStrIsr("xD");

 xIsr.taper = 0;		/* clear taper flag */
 xIsr.done = 1;			/* indicate done */
 xIsr.stopRev = sp.rev;
 xIsr.stopPos = sp.pos;
 
 if (cfgDro)
  dbgmsg(D_XDRO, xDroPos);
 dbgmsg(D_XLOC, xLoc);
 dbgXAccelClr();
 dbgXStopClr();
 dbgXDoneSet();
}

extern "C" void xTmrISR(void)
{
 dbgXIsrSet();
 dbgXRemClr();
 xTmrClrIF();			/* clear interrupt flag */

 xLoc += xIsr.dir;		/* update position */
 xIsr.steps++;			/* count a step moved */
 xUpdHomeLoc();			/* update home testing location */

 if (xIsr.home)			/* 1*+ if homing operation */
 {
  updProbeDist();		/* update probe testing distance */
  if (xIsr.home & PROBE_SET)	/* if probing */
  {
   if (probeSet())		/* if probe set */
   {
    xIsr.doneHome = 1;		/* indicate probe done */
    xIsrStop('1');		/* stop movement */
   }
  }

  if (xIsr.home & FIND_HOME)	/* if looking for home */
  {
   if (xHomeIsSet())		/* if home found */
   {
    xIsr.doneHome = 1;		/* indicate homing done */
    xIsrStop('2');		/* stop movement */
   }
  }

  if (xIsr.home & CLEAR_HOME)	/* if moving off home */
  {
   if (xHomeClr())		/* if home moved off home */
   {
    xIsr.doneHome = 1;		/* indicate homing done */
    xIsrStop('3');		/* stop movement */
   }
  }
 }

 if (xIsr.dist != 0)		/* 2*+ if distance set */
 {
  --xIsr.dist;			/* decrement distance */
  if (xIsr.dist == 0)		/* 2.1*+ if done */
  {
   if (!xIsr.useDro)		/* if not using dro */
   {
    xIsrStop('4');		/* stop isr */
   }
  }
  else if ((xIsr.cFactor != 0)	/* 2.2*+ if acceleration enabled */
       &&  (xIsr.decel == 0)	/* and not decelerating */
       &&  (xIsr.dist <= (xIsr.accelStep - xIsr.initialStep))) /* decel time */
  {
   xIsr.accel = 0;		/* stop acceleration */
   xIsr.decel = 1;		/* start deceleration */
   dbgXAccelSet();
  }
 }
  
 if (xIsr.accel)		/* 3*+ if accelerating */
 {
  if (xIsr.accelStep < xIsr.finalStep) /* if accelerating */
  {
   xIsr.accelStep++;		/* count a step */
   int count = (int) (xIsr.cFactor * sqrt(xIsr.accelStep)); /* calc next */
   xIsr.curCount = count - xIsr.lastCount; /* value to load in timer */
   xIsr.lastCount = count;	/* set last count */
   xTmrMax(xIsr.curCount);	/* load counter value */
  }
  else				/* if acceleration done */
  {
   xTmrMax(xIsr.clocksStep);	/* load final counter value */
   xIsr.accel = 0;		/* clear flag */
   xIsr.cycleCounter = 0;	/* reset x cycle counter */
   if (zIsr.taper)		/* if tapering enabled */
   {
    zStart();			/* start x running */
   }
   dbgXAccelClr();
   putBufStrIsr("xa");
  }
 }
 else if (xIsr.decel)		/* 4*+ if decelerating */
 {
  if (xIsr.accelStep > xIsr.initialStep) /* if decelerating */
  {
   --xIsr.accelStep;		/* count a step */
   int count = (int) (xIsr.cFactor * sqrt(xIsr.accelStep)); /* calc next */
   xIsr.curCount = xIsr.lastCount - count; /* value to load in timer */
   xIsr.lastCount = count;	/* set last count */
   xTmrMax(xIsr.curCount);	/* load counter value */
  }
  else				/* if deceleration done */
  {
   if (!xIsr.useDro)		/* if not using dro */
   {
    xIsrStop('6');		/* stop isr */
    dbg7Clr();
    putBufStrIsr("xd");
   }
  }
 }
 else				/* 5*+ tracking state */
 {
  if (xIsr.sync > 0)		/* 5.1*+ if running in sync mode */
  {
   if (xIsr.sum < 0)		/* if tracking sum negative */
   {
    xIsr.sum += xIsr.incr1;	/* add incr1 value */
    xTmrSet(xIsr.counterStep1);	/* load normal counter value */
   }
   else				/* if positive */
   {
    xIsr.sum += xIsr.incr2;	/* add incr2 value */
    xTmrSet(xIsr.counterStep2);	/* load counter plus one value */
    xIsr.remCount++;
    dbgXRemSet();
   }

   dbgXCycClr();
   xIsr.cycleCounter++;		/* update x cycle counter */
   if (xIsr.cycleCounter >= xIsr.stepsCycle) /* if x cycle finished */
   {
    xIsr.cycleCounter = 0;	/* reset x cycle */
    xIsr.lastRemCount = xIsr.remCount;
    xIsr.remCount = 0;
    dbgXCycSet();
   }
  }
  else if (updateFeed)		/* 5.2*+ if time to update feed */
  {
   updateFeed = 0;		/* clear flag */
   if (xIsr.stepsCycle != 0)
   {
    xIsr.clocksStep = indexPeriod / xIsr.stepsCycle;
    xTmrMax(xIsr.clocksStep);	/* set interrupt timer */
   }
   else
    putBufStrIsr("x0");
  }
 }
 dbgXIsrClr();
}

extern "C" void spSyncISR(void)
{
 EXTI->PR = ExtInt_Pin;		/* clear encoder interrupt */

 if ((zIsr.active & SYNC_ACTIVE_EXT) != 0) /* if z axis active */
 {
  dbgZEncSet();
  zPulse();
  if (xIsr.active & SYNC_ACTIVE_TAPER)
  {
   xCheckStep();		/* check for x axis step */
  }
  dbgZEncClr();
 }
   
 if ((xIsr.active & SYNC_ACTIVE_EXT) != 0) /* if x axis active */
 {
  dbgXEncSet();
  xPulse();
  if (zIsr.active & SYNC_ACTIVE_TAPER)
  {
   zCheckStep();		/* check for z axis step */
  }
  dbgXEncClr();
 }
}

extern "C" void encISR(void)
{
 EXTI->PR = encIRQ_Bit;

 if ((zIsr.active & SYNC_ACTIVE_ENC) != 0) /* if z axis active */
 {
  zCheckStep();			/* check for z axis step */
 }

 if ((xIsr.active & SYNC_ACTIVE_ENC) != 0) /* if x axis active */
 {
  xCheckStep();			/* check for x axis step */
 }
}

#define toggle(cond, set, clr)			\
 if (cond) {set;} else {clr;}

extern "C" void cmpTmrISR(void)
{
 uint16_t captureVal;
 uint16_t delta;
 if constexpr (DBG_CMP_TIME)
 {
  dbgCapIsrSet();
 }
 spEncCount++;			/* count an interrupt */

 if (cmpTmrCap1IF())		/* if encoder input pulse */
 {
  captureVal = cmpTmrCap1();	/* read capture value */
  cmpTmrCap1ClrIF();		/* clear interrupt */
  cmpTmrOCP1Clr();		/* clear over capture flag */

  if (encoderDirect)		/* if encoder direct */
  {
//   EXTI->SWIER |= ExtInt_Pin;	/* generate software interrupt */
   encISR();
  }

  if (capTmrEnable)		/* if capture timer enabled */
  {
   delta = captureVal - cmpTmr.lastEnc; /* time since last pulse */
   cmpTmr.lastEnc = captureVal;	/* save time of last capture */
   cmpTmr.encPulse -= 1;		/* count off a pulse */

   uint32_t cycleClocks = cmpTmr.cycleClocks; /* get cycleclocks */
   uint16_t *p = &cmpTmr.delta[cmpTmr.encPulse]; /* get loc in history array */
   cycleClocks -= *p;		/* subtract old value */
   cycleClocks += delta;		/* add in new value */
   *p = delta;			/* save new value */

   cmpTmr.cycleClocks = cycleClocks; /* update clocks in a cycle */

   if constexpr (DBG_CMP)
   {
    if constexpr (DBGTRK2WL0)
    {
     dbgTrk2WL(cmpTmr.encPulse, delta, cycleClocks);
    }
   }

   if (cmpTmr.encPulse <= 0)	/* if end of cycle */
   {
    cmpTmr.encPulse = cmpTmr.encCycLen; /* reset cycle counter */
    if (cmpTmr.startInt)		/* if time to start internal timer */
    {
     intTmrStart();		/* start timer */
     cmpTmr.startInt = 0;	/* clear flag */

     if constexpr (DBG_INT)
     {
      dbgCycEndClr();
     }
    }
    else if (cmpTmr.measure)	/* if measure flag set */
    {
     cmpTmr.measure = 0;		/* indicate measurement done */
     cmpTmrCap1ClrIE();		/* clear capture 1 interrupt enable */
     cmpTmrStop();		/* stop timer */
    }
    else if (cmpTmr.stop)	/* if time to stop */
    {
     cmpTmr.stop = 0;		/* clear stop flag */
     cmpTmrCap1ClrIE();		/* clear capture 1 interrupt enable */
     cmpTmrStop();		/* stop timer */
    }
    else
    {
     if constexpr (DBG_SYNC_COUNT)
      cmpTmr.missedStart += 1;	/* count missed start */
    }

    if constexpr (DBG_SYNC_COUNT)
    {
     cmpTmr.cycleCount += 1;
     if constexpr (DBG_CMP)
     {
      toggle(cmpTmr.cycleCount & 1, dbgCycleSet(), dbgCycleClr());
     }
    }
   }

   if constexpr (DBG_SYNC_COUNT)
   {
    cmpTmr.encCount += 1;	/* count interrupt */
    if constexpr (DBG_CMP)
    {
     toggle(cmpTmr.encCount & 1, dbgIntCSet(), dbgIntCClr());
    }
   }
  }
 }
 
 if constexpr (0)		/* **disabled */
 {
  if (cmpTmrIF())		/* if update interrupt */
  {
   cmpTmrClrIF();		/* clear interrupt flag */
  }

  if (cmpTmrCap2IF())		/* if encoder input pulse */
  {
   cmpTmrCap2ClrIF();		/* clear interrupt */
   cmpTmrOCP2Clr();		/* clear over capture flag */
  }
 }

 if constexpr (DBG_CMP_TIME)
 {
  dbgCapIsrClr();
 }
}

extern "C" void intTmrISR(void)
{
 dbgIntIsrSet();
 intTmrClrIF();			/* clear interrupt */
 uint32_t ctr  = ((cmpTmr.cycleClocks - cmpTmr.intClocks) /
		  cmpTmr.intPulse);
 cmpTmr.intPulse -= 1;		/* count a pulse in cycle */
 cmpTmr.intClocks += ctr;	/* update count for next interrupt */

 if (cmpTmr.intPulse > 0)	/* if not done */
 {
  intTmrSet(ctr - 1);		/* set timer interval */
 }
 else
 {
  intTmrStop();			/* stop timer */
  intTmrSet(cmpTmr.startDelay);	/* set to start value */
  intTmrCntClr();		/* clear counter */
  cmpTmr.intPulse = cmpTmr.intCycLen; /* initialize counter to cycle len */
  cmpTmr.intClocks = 0;		/* clear clock counter */
  if (cmpTmr.stop == 0)		/* if time to stop */
   cmpTmr.startInt = 1;		/* start on next encoder pulse */

  if constexpr (DBG_INT)
  {
   dbgCycEndSet();
  }
 }

 if (zIsr.active & SYNC_ACTIVE_TMR) /* if z axis active */
 {
  dbgZEncSet();
  zPulse();			/* trigger z interrupt */
  if (xIsr.active & SYNC_ACTIVE_TAPER)
  {
   xCheckStep();		/* check for x axis step */
  }
  dbgZEncClr();
 }

 if (xIsr.active & SYNC_ACTIVE_TMR) /* if x axis active */
 {
  dbgXEncSet();
  xPulse();			/* trigger x interrupt */
  if (zIsr.active & SYNC_ACTIVE_TAPER)
  {
   zCheckStep();		/* check for z axis step */
  }
  dbgXEncClr();
 }

 if constexpr (DBG_SYNC_COUNT)
 {
  cmpTmr.intCount += 1;
  if constexpr (DBG_INT)
  {
   toggle(cmpTmr.intCount & 1, dbgIntPSet(), dbgIntPClr());
  }
 }

 if constexpr (DBG_INT)
 {
  if constexpr (DBGTRK2WL1)
  {
   dbgTrk2WL(1000 + cmpTmr.intPulse, ctr, cmpTmr.intClocks);
  }
 }
 dbgIntIsrClr();
}

extern "C" void indexTmrISR(void)
{
 if (indexTmrIF())		/* if index timer */
 {
  indexTmrClrIF();		/* clear interrupt flag */
  indexOverflow++;		/* update overflow */
 }
}

#ifdef STEP3_TIMER
extern "C" void step3TmrISR(void)
{
 dbgS3IsrSet();
 step3TmrClrIF();		/* clear interrupt flag */

 dbgS3IsrClr();
}
#endif

#ifdef STEP4_TIMER
extern "C" void step4TmrISR(void)
{
 dbgS4IsrSet();
 step4TmrClrIF();		/* clear interrupt flag */

 dbgS4IsrClr();
}
#endif

#ifdef STEP5_TIMER
extern "C" void step5TmrISR(void)
{
 dbgS5IsrSet();
 step5TmrClrIF();		/* clear interrupt flag */

 dbgS5IsrClr();
}
#endif
