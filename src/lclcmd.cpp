#if !defined(INCLUDE)
#include "stm32f4xx_hal.h"

#define ENUM_D_MESSAGE
#include "lathe.h"

#include "serialio.h"
#include "i2c.h"
#include "lcd.h"
#if !defined(EXT)
#define EXT
#endif
#endif

void lclcmd(int ch);

EXT int16_t addr;
EXT float tpi;
EXT float zTaperDist;
EXT float taper;
EXT int zDist;
extern int zFlag;
EXT int xDist;

#if !defined(INCLUDE)

void zCommand(void);
void xCommand(void);
void pinDisplay(void);

int lastFlags;

#if 0
void readreg(char addr, char *str)
{
 read1(addr);			/* read from device */
 printf("\n\rread addr %2x val %8lx %10ld %s", addr, readval.i, readval.i, str);
}

#define LOADX(a, b) loadreg(a, (byte_long) ((int32_t) b))

void loadreg(char addr, byte_long val)
{
 printf("sending addr %2x %10ld val %8lx\n", addr, val.i, val.i);
 load(addr, val);
}

void loadregb(char addr, char val)
{
 printf("sending addr %2x %10d val %8x\n", addr, val, val);
 loadb(addr, val);
}
#endif

typedef struct
{
 char ch;
 GPIO_TypeDef *port;
} T_PORT_LIST, *P_PORT_LIST;

T_PORT_LIST portList[] =
{
 {'a', GPIOA},
 {'b', GPIOB},
 {'c', GPIOC},
 {'d', GPIOD},
 {'e', GPIOE},
};

void lclcmd(int ch)
{
 if (ch == 'i')			/* init character buffer */
 {
  initCharBuf();
 }
 else if (ch == 'j')		/* jog debug */
 {
  newline();
  printf("jog debug %d: ",  jogDebug);
  flushBuf();
  if (getnum())
  {
   if (val != 0)
    jogDebug = val;
  }
 }
 else if (ch == 1)
 {
  newline();
  encoderMeasure();
 }
 else if (ch == 2)
 {
  newline();
  encoderCalculate();
 }
 else if (ch == 'e')
 {
  newline();
  encoderStop();
  printf("encoder cycle %d: ",  lSyncCycle);
  flushBuf();
  if (getnum())
  {
   if (val != 0)
    lSyncCycle = val;
  }
  printf("\noutput %d: ", lSyncOutput);
  flushBuf();
  if (getnum())
  {
   if (val != 0)
    lSyncOutput = val;
  }
  printf("\nprescaler %d: ", lSyncPrescaler);
  flushBuf();
  if (getnum())
  {
   if (val != 0)
    lSyncPrescaler = val;
  }
  encoderStart();
 }
 else if (ch == '>')
 {
  newline();
  pinDisplay();
 }
 else if (ch == '*')
 {
  unsigned int reg = 0;
  unsigned int mask = 0;
  unsigned int invert = 0;

  while (1)
  {
   printf("\nreg ");
   flushBuf();
   if (getnum())
    reg = val;
   else
    break;

   printf("\nmask ");
   flushBuf();
   if (getnum())
    mask = val;
    
   printf("\ninvert ");
   flushBuf();
   if (getnum())
    invert = val != 0;
  
   int set = (((reg & mask) != 0) ^ invert);
   int clr = (((reg & mask) == 0) ^ invert);

   printf("\nreg %02x mask %02x invert %02x set %d clr %d",
	  reg, mask, invert, set, clr);
  }
 }
 else if (ch == '=')
 {
  newline();
  pinDisplay();
 }
 else if (ch == 'A')
 {
  printf("\ntmr test 0x01"
	 "\ntmr stop 0x02"
	 "\ninp test 0x04"
	 "\nout test 0x08"
	 "\ninp plup 0x10"
	 "\ninp pldn 0x20");
  printf("\npin test: ");
  flushBuf();
  getnum();
  newline();
  testOutputs(val);
 }
 else if (ch == 's')
 {
  float factor[] = {0.00, 0.01, 0.02, 0.05, 0.10, 0.20, 0.50, 1.00};
  //printf("\nspeed: ");
  //flushBuf();
  //float speed = 20.0;
  //if (getfloat())
  // speed = fVal;
  for (int i = 1; i < 8; i++)
  {
   printf("\n");
   float speed = factor[i] * 20.0;
   speedCalc(&zJSA, &zIsr, speed);
  }
 }
 else if (ch == '`')
 {
  spJogRpm = 3.1;
  printf("\nspeed [%0.1f]: ", spJogRpm);
  flushBuf();
  if (getfloat())
   spJogRpm = fVal;

  unsigned int delay = 250;
  printf("delay [%u]: ", delay);
  flushBuf();
  if (getnum())
   delay = (unsigned int) val;

  int repeat = 1;
  printf("\nrepeat [%d]: ", repeat);
  flushBuf();
  if (getnum())
   repeat = val;
  printf("\n");

  unsigned int start = 0;
  while (1)
  {
   if (chRdy())
   {
    ch = getx();
    if (ch == 3)
     break;
   }
   unsigned int t = millis();
   if ((t - start) >= delay)
   {
    unsigned int delta = t - start;
    start = t;
    printf("**repeat %d delta %u\n", repeat, delta);
    spindleJogSpeed();
    if (--repeat <= 0)
     break;
   }
   axisCtl();
   pollBufChar();
  }
 }
 else if (ch == '!')
 {
  zInfo(1);
 }
 else if (ch == '/')
 {
  printf("\njog\n");
  flushBuf();
  P_JOGQUE jog = &zJogQue;
  while (1)
  {
   char dir = 0;
   if (chRdy())
   {
    ch = getx();
    if (ch == 3)
     break;
    if (ch == '.')
    {
     dir = 1;
     putBufChar('>');
    }
    else if (ch == ',')
    {
     dir = -1;
     putBufChar('<');
    }
    else if (ch == 'x')
    {
     jog = &xJogQue;
    }
    else if (ch == 'z')
    {
     jog = &zJogQue;
    }
    if (dir)
    {
     if (jog->count < MAXJOG)
     {
      jog->count++;
      jog->buf[jog->fil] = 1;
      jog->fil++;
      if (jog->fil >= MAXJOG)
       jog->fil = 0;
     }
    }
   }
   else
   {
    axisCtl();
    pollBufChar();
   }
  }
 }
 else if (ch == 'F')
 {
  printf("\nIRQn: ");
  flushBuf();
  if (getnum())
  {
    HAL_NVIC_EnableIRQ((IRQn_Type) val);
  }
 }
 else if (ch == 'I')
 {
  printf("\nPort: ");
  flushBuf();
  ch = getx();
  unsigned int i;
  P_PORT_LIST p = portList;
  GPIO_TypeDef *port = 0;
  for (i = 0; i < sizeof(portList) / sizeof(T_PORT_LIST); i++)
  {
   if (ch == p->ch)
   {
    port = p->port;
    putBufChar(ch);
    break;
   }
  }
  if (port != 0)
  {
   printf("\nmask: ");
   flushBuf();
   if (gethex())
   {
    port->ODR = val;
    printf("\n");
    gpioInfo(port);
   }
  }
 }
 else if (ch == 'J')
 {
  printf("\n");
  I2C1->CR1 |= I2C_CR1_SWRST;
  I2C1->CR1 &= ~I2C_CR1_SWRST;
  initI2c();
  i2cInfo(I2C1, "I2C1");
  printf("\n");
  gpioInfo(GPIOB);
 }
 else if (ch == 'K')
 {
  putBufChar('\n');
  I2C1->CR1 |= I2C_CR1_SWRST;
  printf("\nresetting");
  flushBuf();
  I2C1->CR1 &= ~I2C_CR1_SWRST;
 }
 else if (ch == 'L')
 {
  printf("\ninit: ");
  flushBuf();
  ch = getx();
  putBufChar(ch);
  newline();
  if (ch == 'y')
  {
   lcdInit();
  }
 }
 else if (ch == 'O')
 {
  zSynSetup(runCtl.feedType, runCtl.zFeed, runoutDistance, runoutDepth);
//	    runCtl.taper);
  unsigned int step;
  int count;
  int curCount;
  int lastCount;
  P_ACCEL ac = &zTA;
  step = ac->initialStep;
  lastCount = (int) (ac->cFactor * sqrt(step));
  step++;
  printf("step      count    lastcount\n");
  for (; step < ac->finalStep; step++)
  {
   count = (int) (ac->cFactor * sqrt(step));
   curCount = count - lastCount;
   printf("%4d %10d %12d\n", step, curCount, lastCount);
   lastCount = count;
  }
 }
 else if (ch == 'Q')		/* print peripheral info */
 {
  printf(" flag: ");
  flushBuf();
  if (getnum() == 0)
  {
   val = lastFlags;
  }
  else
  {
   lastFlags = val;
  }
  printf("\n");
  flushBuf();
  if (val & 0x01)
   tmrInfo(TIM1);
  if (val & 0x02)
   tmrInfo(TIM2);
  if (val & 0x04)
   tmrInfo(TIM3);
  if (val & 0x08)
   tmrInfo(TIM4);
  if (val & 0x10)
   tmrInfo(TIM5);
  if (val & 0x20)
  {
#ifdef TIM6
   tmrInfo(TIM6);
#endif
#ifdef TIM7
   tmrInfo(TIM7);
#endif
  }
#ifdef TIM8
  if (val & 0x40)
   tmrInfo(TIM8);
#endif
  if (val & 0x80)
   tmrInfo(TIM9);
  if (val & 0x100)
   tmrInfo(TIM10);
  if (val & 0x200)
   tmrInfo(TIM11);
#ifdef TIM12
  if (val & 0x400)
   tmrInfo(TIM12);
#endif
  if (val & 0x800)		/* exti */
   extiInfo();
  if (val & 0x01000)
   gpioInfo(GPIOA);
  if (val & 0x02000)
   gpioInfo(GPIOB);
  if (val & 0x04000)
   gpioInfo(GPIOC);
#ifdef GPIOD
  if (val & 0x08000)
   gpioInfo(GPIOD);
#endif
#ifdef GPIOE
  if (val & 0x10000)
   gpioInfo(GPIOE);
#endif
  if (val & 0x20000)
   i2cInfo(I2C1, "I2C1");
  if (val & 0x40000)
   usartInfo(DBGPORT, "DBG");
  if (val & 0x80000)
   usartInfo(REMPORT, "REM");
 }
#if DBGMSG
 if (ch == 'D')			/* dump dbg buffer */
 {
  newline();
  int empty = dbgemp;
  int i;
  for (i = 0; i < dbgcnt; i++)
  {
   P_DBGMSG p = &dbgdata[empty];
   float t = (float) p->time / 1000;
#if DBGMSG == 2
   printf("%8.3f %7s %6d\n", t, dMessageList[(int) p->dbg], (int) p->val);
#else
   printf("%8.3f %8s %6d\n", t, p->str, (int) p->val);
#endif
   empty++;
   if (empty >= MAXDBGMSG)
    empty = 0;
  }
  printf("z %d x %d\n", zLoc, xLoc);
 }
 else if (ch == 'E')		/* clear debug buffer */
 {
  memset(&dbgdata, 0, sizeof(dbgdata));
  dbgcnt = 0;
  dbgfil = 0;
  dbgemp = 0;
 }
#endif
 else if (ch == 'H')
 {
#if !HOME_TEST
  val = (XHome_GPIO_Port->BSRR & XHome_Pin) == 0;
  printf("\nx home switch %d\n", (int) val);
#else
  printf("xHomeLoc %0.4f xHomeStart %0.4f xHomeEnd %0.4f xHomeSet %d\n",
	 (float) xHomeLoc / xAxis.stepsInch,
	 (float) xHomeStart / xAxis.stepsInch,
	 (float) xHomeEnd / xAxis.stepsInch, xHomeSet());
#endif
 }
 else if (ch == 'd')		/* dump memory */
 {
  putBufChar(' ');
  if (gethex())
  {
   unsigned char *p;

   p = (unsigned char *) (int) val;
   if (gethex())
   {
    newline();
    prtbuf(p, val);
   }
  }
 }
 else if (ch == 'r')		/* read memory */
 {
  putBufChar(' ');
  if (gethex())
  {
   printf("%x", *(int16_t *) (int) val);
  }
 }
 else if (ch == 'w')
 {
  putBufChar(' ');
  if (gethex())
  {
   int16_t *p;
   p = (int16_t *) (int) val;
   printf(" %x ", *p);
   if (gethex())
   {
    *p = val;
   }
  }
 }
 else if (ch == 'p')
 {
  putBufChar(' ');
  if (getnum())
  {
   print = val;
  }
 }
 else if (ch == 'x')
 {
  putBufChar(' ');
  if (getnum())
  {
   xMoveRel(xDist, CMD_MAX);
  }
 }
#if 0
 else if (ch == 'u')
 {
  putBufChar(' ');
  if (getnum())
  {
   dbgmsg(D_TEST, val);
  }
 }
#endif
 else if (ch == 'Y')
 {
  putstr("\nminRPM ");
  if (getfloat())
   spA.minRPM = fVal;
  putstr("maxRPM ");
  if (getfloat())
   spA.maxRPM = fVal;
  putstr("aTime ");
  if (getfloat())
   spA.aTime = fVal;
  spindleAccelCalc(&spA);
 }
 else if (ch == 'S')
 {
  printf("\nstart spindle\n");
  spindleSetup(0);
  spindleStart();
 }
 else if (ch == 'P')
 {
  spindleStop();
  zStop();
 }
 else if (ch == 'I')
 {
  putstr("\ntpi ");
  if (getfloat())
   threadTPI(&zTA, fVal);
 }
 else if (ch == 'M')
 {
  putstr("\npitch mm ");
  if (getfloat())
   threadMetric(&zTA, fVal);
 }
 else if (ch == 'Z')
 {
  float accel = 0.5;
  putstr("\nz Accel Time ");
  if (getfloat())
   accel = fVal;
  turnAccel(&zTA, accel,  T_STEP_SPINDLE | T_DBG_PRINT, 0);
 }
 else if (ch == 'G')
 {
#if DBGTRK
  memset(trkbuf, 0, sizeof(trkbuf)); /* clear track buffer */
  trkidx = 0;			/* reset index */
  dbgTrk = true;		/* start saving tracking info */
#endif

  newline();
  allStop();

  memset(&spA, 0, sizeof(spA));
  memset(&sp, 0, sizeof(sp));

  zInit(&zAxis);
  accelInit(&zAxis, &zTA);
  accelInit(&zAxis, &zMA);
  accelInit(&zAxis, &zJA);

  memset(&zIsr, 0, sizeof(zIsr));

  spA.minRPM = 10.0;
  spA.maxRPM = 60.0;
  spA.aTime = 1.0;

  spA.microSteps = 64;
  spA.motorSteps = 200;
  spindleAccelCalc(&spA);		/* accelerate spindle */

#if 0
  newline();
  if (tpi == 0.0)
   tpi = 20.0;
  printf("thread [%4.1f] ", tpi);
  flushBuf();
  if (getfloat())
   tpi = fVal;

  if (tpi >= 8)
   threadTPI(&zTA, tpi);
  else if (tpi < .3)
   turnPitch(&zTA, tpi);
  else
   threadMetric(&zTA, tpi);

  newline();
  turnAccel(&zTA, 0.5,  T_STEP_SPINDLE | T_DBG_PRINT, 0); /* accelerate z */
#endif
 }
 else if (ch == 'q')
 {
  allStop();
 }
 else if (ch == 'z')
 {
  zCommand();
 }
 else if (ch == 'x')
 {
  xCommand();
 }
#if DBGTRK
 else if (ch == 'T')		/* print track buffer */
 {
  int16_t idx = trkidx;

  printf("\n");
  if (DBGTRK1W)
  {
   int16_t i = sizeof(trkbuf) / sizeof(int16_t);
   while (--i >= 0)
   {
    int16_t tmp = (int16_t) (*(int16_t *) &trkbuf[idx]);
    printf("%4d %6d %4x\n", idx, tmp, (uint16_t) tmp);
    idx += 1;
    idx &= (TRKBUFSIZE - 1);
   }
  }
  if (DBGTRK1L)
  {
   int16_t i = sizeof(trkbuf) / sizeof(int);
   while (--i >= 0)
   {
    int *p = (int *) &trkbuf[idx];
    int tmp0 = *p;
    printf("%4d %10d\n", idx, tmp0);
    idx += 2;
    idx &= (TRKBUFSIZE - 1);
   }
  }
  if (DBGTRK2L)
  {
   int16_t i = sizeof(trkbuf) / (2 * sizeof(int));
   while (--i >= 0)
   {
    int *p = (int *) &trkbuf[idx];
    int tmp0 = *p;
    int tmp1 = *(p + 1);
    printf("%4d %10d %10d\n", idx, tmp0, tmp1);
    idx += 4;
    idx &= (TRKBUFSIZE - 1);
   }
  }
  if (DBGTRK2WL)
  {
   int16_t i = sizeof(trkbuf) / (2 * sizeof(int16_t) + sizeof(int));
   while (--i >= 0)
   {
    int16_t *p = (int16_t *) &trkbuf[idx];
    int16_t tmp0 = *p++;
    int16_t tmp1 = *p++;
    int tmp2 = *((int32_t *) p);
    printf("%4d %4d %5u %10d\n", idx, tmp0, (uint16_t) tmp1, tmp2);
    idx += 4;
    idx &= (TRKBUFSIZE - 1);
   }
  }
 }
 else if (ch == 'B')		/* clear track buffer */
 {
  memset(trkbuf, 0, sizeof(trkbuf)); /* clear track buffer */
  trkidx = 0;			/* reset index */
  dbgTrk = true;		/* start saving tracking info */
 }
#endif	/* DBGTRK */
#if 0
 else if (ch == 's')
 {
  puts("\nsetup slave");
  tstTmrSlvDis();
  tstPWMMode();
  int cnt = spA.clocksStep - 1;
  tstTmrSet(cnt);
  tstTmrCnt(cnt);
  tstTmrCCR(tmrStepWidth);
  tstPWMEna();			/* enable pwm output */
  tstTmrSetIE();		/* enable interrupts */
 }
 else if (ch == 't')
 {
  puts("\nenable slave");
  dbg6Set();
  tstTmrSlvEna();
 }
 else if (ch == 'u')
 {
  dbg7Set();
  puts("\ndisable slave");
  tstTmrSlvDis();
  tstTmrStop();
  tstTmrClrIE();
  tstTmrClrIF();
  tstTmrCnt(spA.clocksStep - 1);
  dbg7Clr();
 }
#endif
 else if (ch == 'v')
 {
  tmrInfo(TIM3);
  tmrInfo(TIM4);
 }
 else if (ch == '?')
 {
  printf("\nspindle curCount %d z curCount %d x curCount %d\n",
	 sp.curCount, zIsr.curCount, xIsr.curCount);
  printf("spindle cycleCounter %d z cycleCounter %d x cycleCounter %d\n",
	 sp.cycleCounter, zIsr.cycleCounter, xIsr.cycleCounter);
  printf("z clockSum %d z lastRemCount %d\n",
	 zIsr.clockSum, zIsr.lastRemCount);
  printf("x clockSum %d x lastRemCount %d\n",
	 xIsr.clockSum, xIsr.lastRemCount);

  printf("zLoc %6d %7.4f zHomeOffset %7.4f %7.4f\n",
	 zLoc, (float) zLoc / zAxis.stepsInch,
	 zHomeOffset, runCtl.zHomeOffset);
  if (cfgDro)
   printf("zDro %6d %7.4f  zDroOffset %7.4f\n",
	  zDroPos, (float) zDroPos / zDroInch, zDroOffset);

  printf("xLoc %6d %7.4f xHomeOffset %7.4f %7.4f\n",
	 xLoc, (float) xLoc / xAxis.stepsInch,
	 xHomeOffset, runCtl.xHomeOffset);
  if (cfgDro)
   printf("xDro %6d %7.4f  xDroOffset %7.4f\n",
	  xDroPos, (float) xDroPos / xDroInch, xDroOffset);
  fflush(stdout);
 }
}

void zCommand(void)
{
 newline();
 while (1)
 {
  putBufChar('>');
  char ch = getx();
  putBufChar(ch);
  newline();
  if (ch == 'a')
  {
   zSetup();
  }
  else if (ch == 'c')
  {
   zInit(&zAxis);
   accelInit(&zAxis, &zTA);
   accelInit(&zAxis, &zMA);
   accelInit(&zAxis, &zJA);

   xInit(&xAxis);
   accelInit(&xAxis, &xPA);
  }
  else if (ch == 'm')
  {
   if (zDist == 0)
    zDist = 1000;
   printf("dist [%d] ", zDist);
   fflush(stdout);
   if (getnum())
    zDist = val;
   newline();
   zMoveInit(&zMA, 1, zDist);
   zStart();
  }
  else if (ch == 't')
  {
   puts("start spindle\n");
   spindleInit(&spA, 0, SP_FWD);
   slaveEna();
   spindleStart();
  }
  else if (ch == 'h')
  {
   if (tpi == 0.0)
    tpi = .007;
   printf("thread [%5.3f] ", tpi);
   fflush(stdout);
   if (getfloat())
    tpi = fVal;

   if (tpi >= 8)
    threadTPI(&zTA, tpi);
   else if (tpi < .3)
    turnPitch(&zTA, tpi);
   else
    threadMetric(&zTA, tpi);
   newline();
   turnAccel(&zTA, 0.5,  T_STEP_SPINDLE | T_DBG_PRINT, 0);
   zTurnInit(&zTA, 1, 0);
  }
  else if (ch == 'p')
  {
/*
   if (zTaperDist == 0.0)
    zTaperDist = 1.0;
   printf("zTaperDist [%5.3f] ", zTaperDist);
   fflush(stdout);
   if (getfloat())
    zTaperDist = fVal;
*/
   if (taper == 0.0)
    taper = 0.127;
   printf("taper [%5.3f] ", taper);
   fflush(stdout);
   if (getfloat())
    taper = fVal;
    
   taperCalc(&zTA, &xPA, taper);
   xTaperInit(&xPA, 1);
  }
  else if (ch == 'q')
  {
   zStop();
  }
  else if (ch == 'v')
  {
   tmrInfo(TIM3);
   tmrInfo(TIM2);
//  if (xTA.taper)
   tmrInfo(TIM5);
  }
  else if (ch == 'M')
  {
   if (zDist == 0)
    zDist = 1000;
   printf("dist [%d] ", zDist);
   fflush(stdout);
   putBufChar(' ');
   if (getnum())
    zDist = val;
   newline();

   if (zFlag == 0)
    zFlag = CMD_MOV;
   printf("flag [%d] ", zFlag);
   fflush(stdout);
   putBufChar(' ');
   if (getnum())
    zFlag = val;
   newline();

   zMoveRel(zDist, zFlag);
   break;
  }
  else if (ch == ' ')
   break;
 }
}

void xCommand(void)
{
}

#endif
