//#if !defined(INCLUDE)
#define __LCLCMD__
#ifdef STM32F4
#include "stm32f4xx_hal.h"
#endif
#ifdef STM32F7
#include "stm32f7xx_hal.h"
#endif
#ifdef STM32H7
#include "stm32h7xx_hal.h"

#if defined(NUCLEOH743)
#include "stm32h743xx.h"
#endif  /* NUCLEO743 */

#if defined(NUCLEOH723)
#include "stm32h723xx.h"
#endif  /* NUCLEO723 */

#endif  /* STM32H7 */

#include "lathe.h"

#include "serialio.h"
#include "i2cx.h"
#include "lcd.h"

#include "i2c.h"
#include "config.h"

#include "remStruct.h"

#ifdef EXT
#undef EXT
#endif

#define EXT
#include "stm32Info.h"
#include "lclcmd.h"
//#endif

#if defined(__LCLCMD_INC__)	// <-

#if !defined(EXT)
#define EXT extern
#endif

void lclcmd(int ch);

EXT int16_t addr;
EXT float tpi;
EXT float zTaperDist;
EXT float taper;
EXT int zDist;
//extern int zFlag;
EXT int xDist;

#endif	// ->
#ifdef __LCLCMD__

void zCommand();
void xCommand();

//uint32_t lastFlags;

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

typedef struct s_port_list
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

typedef struct s_output_pin
{
 int pin;
 void (*set) ();
 void (*clr) ();
 uint16_t (*read) ();
} T_OUTPUT_PIN, *P_OUTPUT_PIN;

T_OUTPUT_PIN outputPins[] =
{
 {1, pin1Set, pin1Clr, pin1Read},
 {14, pin14Set, pin14Clr, pin14Read},
 {16, pin16Set, pin16Clr, pin16Read},
 {17, pin16Set, pin17Clr, pin17Read},
 {2, dirZSet, dirZClr, dirZRead},
 {4, dirXSet, dirXClr, dirXRead},
 {6, dir3Set, dir3Clr, dir3Read},
 {8, dir4Set, dir4Clr, dir4Read},
};

extern int zCur;
extern int zDro;
extern int zDelta;

typedef struct sBckCheck
{
 char state;
 char lastState;
 char run;
 unsigned int time;
 int steps;
 int strLoc;
 int strDro;
 int endLoc;
 int endDro;
 int stepDist;
 int droDist;
 int backlash;
} T_BACK_CHECK, *P_BACK_CHECK;

T_BACK_CHECK backCheck;

enum BCK_STATE
{
 BCK_IDLE,
 BCK_INI_MOVE,
 BCK_INI_DELAY,
 BCK_MOVE,
 BCK_DELAY,
};

void backlashCheck(P_MOVECTL mov, P_BACK_CHECK bck)
{
 unsigned int t;
 P_ZXISR isr = mov->isr;
 switch (bck->state)
 {
 case BCK_IDLE:
  if (bck->run)
  {
   int loc = *mov->locPtr;    /* get end location */
   int dro = *mov->droLocPtr; /* get end dro location */
   bck->strDro = dro;
   printf("ini loc %6d dro %d\n",
	  ((loc - *mov->homeOffset) * 10000) / mov->stepsInch,
	  ((dro - *mov->droOffset) * 10000) / mov->droCountInch);
   flushBuf();
   mov->dirFwd();
   isr->dir = DIR_POS;
   isr->steps = 0;
   bck->steps = lrint(0.050 * mov->axis->stepsInch);
   bck->state = BCK_INI_MOVE;
   bck->time = millis();
  }
  break;

 case BCK_INI_MOVE:
  t = millis();
  if ((t - bck->time) > 2)
  {
   bck->time = t;
   if ((bck->steps > 0)
   &&  (abs(*mov->droLocPtr - bck->strDro) < 10))
   {
    putx('<');
    mov->pulse();
    bck->steps -= 1;
   }
   else
   {
    bck->state = BCK_INI_DELAY;
   }
  }
  break;

 case BCK_INI_DELAY:
  t = millis();
  if ((t - bck->time) > 50)
  {
   bck->time = t;
   bck->strLoc = *mov->locPtr; /* save start location */
   bck->strDro = *mov->droLocPtr; /* save start dro location */
   printf("\nstr loc %6d dro %d steps %4d\n",
	  ((bck->strLoc - *mov->homeOffset) * 10000 / mov->stepsInch),
	  ((bck->strDro - *mov->droOffset) * 10000 / mov->droCountInch),
	  isr->steps);
   flushBuf();

   mov->dirRev();
   isr->dir = DIR_NEG;
   isr->steps = 0;
   bck->steps = lrint(0.050 * mov->axis->stepsInch);
   bck->state = BCK_MOVE;
   bck->time = millis();
  }
  break;

 case BCK_MOVE:
  t = millis();
  if ((t - bck->time) > 2)
  {
   bck->time = t;
   if ((bck->steps > 0)
   &&  (abs(*mov->droLocPtr - bck->strDro) < 10))
   {
    putx('>');
    mov->pulse();
    bck->steps -= 1;
   }
   else
   {
    bck->state = BCK_DELAY;
   }
  }
  break;

 case BCK_DELAY:
  t = millis();
  if ((t - bck->time) > 50)
  {
   int loc = *mov->locPtr;    /* get end location */
   int dro = *mov->droLocPtr; /* get end dro location */
   bck->endLoc = loc;
   bck->endDro = dro;
   int stepDist = loc - bck->strLoc; /* step dist */
   int droDist = dro - bck->strDro; /* save dro location */
   bck->stepDist = (stepDist * 10000) / mov->stepsInch;
   bck->droDist = (droDist * 10000) / mov->droCountInch;
   bck->backlash = bck->stepDist - bck->droDist;
   printf("\nend loc %6d dro %6d steps %4d\n",
	  ((loc - *mov->homeOffset) * 10000) / mov->stepsInch,
	  ((dro - *mov->droOffset) * 10000) / mov->droCountInch,
	  isr->steps);
   printf("step %6d dro %d\n", bck->stepDist, bck->droDist);
   printf("backlash %6d\n", bck->backlash);
   bck->run = 0;
   bck->state = BCK_IDLE;
  }
  break;
 }
}

void lclcmd(int ch)
{
 int val;
 float fVal;
 if (ch == '#')
 {
  newline();
  int tmpLoc = ((rVar.zLoc - rVar.zHomeOffset) * 10000) / zAxis.stepsInch;
  int tmpDro = ((rVar.zDroLoc - rVar.zDroOffset) * 10000) / rVar.zDroCountInch;
  int tmpDelta = tmpDro - tmpLoc;
  printf("tmpLoc %6d tmpDro %6d tmpDelta %6d\n", tmpLoc, tmpDro, tmpDelta);
  printf("zLoc %6d zHomeOffset %6d zStepsInch %6d\n",
	 rVar.zLoc, rVar.zHomeOffset, zAxis.stepsInch);
  printf("zDro %6d xDroOffset %6d zStepsInc %6d\n",
	 rVar.zDroLoc, rVar.zDroOffset, rVar.zDroCountInch);
  printf("zCur %6d zDro %6d zDelta %6d\n", zCur, zDro, zDelta);
 }
#if defined(STM32H7)
 else if (ch == '%')
 {
  printf("\n%04x %04x\n", (unsigned int) IntSync_GPIO_Port->ODR,
         (unsigned int) IntSync_GPIO_Port->ODR);
  if ((IntSync_GPIO_Port->IDR & IntSync_Pin) == 0)
   IntSync_GPIO_Port->BSRR = IntSync_Pin;
  else
   IntSync_GPIO_Port->BSRR = IntSync_Pin << 16;
  printf("%04x %04x\n", (unsigned int) IntSync_GPIO_Port->ODR,
         (unsigned int) IntSync_GPIO_Port->ODR);
 }
#endif  /* STM32H7 */
 else if (ch == '!')
 {
  newline();
  P_BACK_CHECK bc = &backCheck;
  P_MOVECTL mov = &zMoveCtl;
  memset((void *) bc, 0, sizeof(backCheck));
  bc->run = 1;
  while (bc->run != 0)
  {
   if (dbgRxReady())
   {
    ch = (char) dbgRxRead();
    if (ch == 3)
     break;
   }

   backlashCheck(mov, bc);

   pollBufChar();
  }
 }
 else if (ch == 'i')		/* init character buffer */
 {
  initCharBuf();
 }
 else
 {
  if (ch == 'C')
  {
   int parm;
   if (query(&getNum, &parm, "\nparameter: "))
   {
    T_INT_FLOAT intFloat;
    T_DATA_UNION parmVal;
    ch = query(&getNumAll, &intFloat, "value: ");
    if (ch == INT_VAL)
    {
     parmVal.t_int = intFloat.i;
     setRemVar(parm, parmVal);
     parmVal.t_uint_t = 0xffffffff;
     getRemVar(parm, &parmVal);
     printf("parm %d val %d parmVal %08x\n",
	    parm, intFloat.i, parmVal.t_uint_t);
    }
    else if (ch == FLOAT_VAL)
    {
     parmVal.t_float = intFloat.f;
     setRemVar(parm, parmVal);
     parmVal.t_uint_t = 0xffffffff;
     getRemVar(parm, &parmVal);
     printf("parm %d fVal %7.3f parmVal %7.3f\n",
	    parm, intFloat.f, parmVal.t_float);
    }
   }
  }
  else
  {
   if (ch == 'j')		/* jog debug */
   {
    newline();
    printf("jog debug %d: ",  rVar.jogDebug);
    flushBuf();
    if (getNum(&val))
    {
     if (val != 0)
      rVar.jogDebug = val;
    }
   }
   else if (ch == 1)
   {
    newline();
    syncMeasure();
   }
   else if (ch == 2)
   {
    newline();
    syncCalculate();
   }
   else if (ch == '-')
   {
    newline();
    int tmp = 0;
    if (pin10IsSet())
     tmp |= 0x00001;
    if (pin11IsSet())
     tmp |= 0x00002;
    if (pin12IsSet())
     tmp |= 0x00004;
    if (pin13IsSet())
     tmp |= 0x00008;
    if (pin15IsSet())
     tmp |= 0x00010;

#if defined(PinA2_Pin)
    int tmpSet = 0;
    int tmpClr = 0;
    if (pinA2IsSet())
     tmp |= 0x00020;
    if (pinA3IsSet())
     tmp |= 0x00040;
    if (pinA4IsSet())
     tmp |= 0x00080;
    if (pinA5IsSet())
     tmp |= 0x00100;

    if (pinA6IsSet())
     tmp |= 0x00200;
    if (zNegLimIsSet())
     tmpSet |= 0x00200;
    if (zNegLimIsClr())
     tmpClr |= 0x00200;

    if (pinA7IsSet())
     tmp |= 0x00400;
    if (zAHomeIsSet())
     tmpSet |= 0x00400;
    if (zAHomeIsClr())
     tmpClr |= 0x00400;

    if (pinA8IsSet())
     tmp |= 0x00800;
    if (zPosLimIsSet())
     tmpSet |= 0x00800;
    if (zPosLimIsClr())
     tmpClr |= 0x00800;

    if (pinA9IsSet())
     tmp |= 0x01000;
    if (pinA10IsSet())
     tmp |= 0x02000;

    if (pinA11IsSet())
     tmp |= 0x04000;
    if (zPosLimIsSet())
     tmpSet |= 0x04000;
    if (zPosLimIsClr())
     tmpClr |= 0x04000;

    if (pinA12IsSet())
     tmp |= 0x08000;
    if (xAHomeIsSet())
     tmpSet |= 0x08000;
    if (xAHomeIsClr())
     tmpClr |= 0x08000;

    if (pinA13IsSet())
     tmp |= 0x10000;
    if (xPosLimIsSet())
     tmpSet |= 0x010000;
    if (xPosLimIsClr())
     tmpClr |= 0x010000;

    if (pinA15IsSet())
     tmp |= 0x20000;

    printf("10 11 12 13 15  2  3  4  5  6  7  8  9 10 11 12 13 15\n");
    printf("** ** ** ** ** ** ** ** ** z- zh z+ ** ** x- xh x+ **\n");
    int mask = 1;
    for (int i = 0; i < 18; i++)
    {
     printf("%2d ", (mask & tmp) ? 1 : 0);
     mask <<= 1;
    }
    printf("\n");
    mask = 1;
    for (int i = 0; i < 18; i++)
    {
     printf("%2d ", (mask & tmpSet) ? 1 : 0);
     mask <<= 1;
    }
    printf("\n");
    mask = 1;
    for (int i = 0; i < 18; i++)
    {
     printf("%2d ", (mask & tmpClr) ? 1 : 0);
     mask <<= 1;
    }
    printf("\n");
#else
    printf("10 11 12 13 15\n");
    printf("x+ ** x- pr y+\n");
    int mask = 1;
    for (int i = 0; i < 5; i++)
    {
     printf("%2d ", (mask & tmp) ? 1 : 0);
     mask <<= 1;
    }
#endif	/* PinA2_Pin */
   }
   else if (ch == 'o')
   {
    if (query(&getNum, &val, "\npin: "))
    {
     int pin = val;
     char found = 0;
     P_OUTPUT_PIN p = outputPins;
     for (unsigned int i = 0; i < sizeof(outputPins) / sizeof(T_OUTPUT_PIN);
	  i++, p++)
     {
      if (pin == p->pin)
      {
       found = true;
       break;
      }
     }
     if (found)
     {
      if (query(&getNum, &val, "val: "))
      {
       if (val != 0)
	p->set();
       else
	p->clr();
      }
      printf("\npin %d %d", pin, p->read());
     }
    }
   }
   else if (ch == 'e')
   {
    newline();
    syncStop();
    if (query(&getNum, &val, "encoder cycle %d: ",  rVar.lSyncCycle))
    {
     if (val != 0)
      rVar.lSyncCycle = val;
    }
    if (query(&getNum, &val, "output %d: ", rVar.lSyncOutput))
    {
     if (val != 0)
      rVar.lSyncOutput = val;
    }
    if (query(&getNum, &val, "prescaler %d: ", rVar.lSyncInPreScaler))
    {
     if (val != 0)
      rVar.lSyncInPreScaler = val;
    }
    syncStart();
   }
   else if (ch == '>')
   {
    newline();
    pinDisplay();
   }
   else if (ch == '*')
   {
    unsigned int reg;
    unsigned int mask = 0;
    unsigned int invert = 0;

    while (true)
    {
     if (query(&getNum, &val, "\nreg "))
      reg = val;
     else
      break;

     if (query(&getNum, &val, "mask "))
      mask = val;

     if (query(&getNum, &val, "invert "))
      invert = val != 0;

     unsigned int set = (((reg & mask) != 0) ^ invert);
     unsigned int clr = (((reg & mask) == 0) ^ invert);

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
    query(&getNum, &val, "\npin test: ");
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
     float speed = factor[i] * 20.0f;
     speedCalc(&zJSA, &zIsr, speed);
    }
   }
   else if (ch == '`')
   {
    rVar.spJogRpm = 3.1;
    printf("\nspeed [%0.1f]: ", rVar.spJogRpm);
    flushBuf();
    if (getfloat(&fVal))
     rVar.spJogRpm = fVal;

    unsigned int delay = 250;
    if (query(&getNum, &val, "delay [%u]: ", delay))
     delay = (unsigned int) val;

    int repeat = 1;
    if (query(&getNum, &val, "repeat [%d]: ", repeat))
     repeat = val;
    printf("\n");

    unsigned int start = 0;
    while (true)
    {
     if (dbgRxReady())
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
    putBufChar('z');
    while (true)
    {
     char dir = 0;
     if (dbgRxReady())
     {
      ch = (char) dbgRxRead();
      if (ch == 3)
       break;

      if (ch == '.')
      {
       dir = 1;
       // putBufChar('>');
      }
      else if (ch == ',')
      {
       dir = -1;
       // putBufChar('<');
      }
      else if (ch == 'x')
      {
       putBufChar(ch);
       jog = &xJogQue;
      }
      else if (ch == 'z')
      {
       putBufChar(ch);
       jog = &zJogQue;
      }

      if (dir)
      {
       putBufChar(dir > 0 ? '>' : '<');
       newline();
       if (jog->count < MAXJOG)
       {
	MPG_VAL mpgVal;
	mpgVal.delta = 50 * 1000;
	mpgVal.dir = dir;
	jog->count++;
	jog->buf[jog->fil] = mpgVal.intVal;
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
    if (query(&getNum, &val, "\nIRQn: "))
    {
     HAL_NVIC_EnableIRQ((IRQn_Type) val);
    }
   }
   else if (ch == '@')
   {
    ch = query("\nPort: ");
    unsigned int i;
    P_PORT_LIST p = portList;
    GPIO_TypeDef *port = nullptr;
    for (i = 0; i < sizeof(portList) / sizeof(T_PORT_LIST); i++)
    {
     if (ch == p->ch)
     {
      port = p->port;
      putBufChar(ch);
      break;
     }
    }
    if (port != nullptr)
    {
     unsigned int modeSave = port->MODER;
     gpioInfo(port);
     if (query(&gethex, &val, "\nbit: "))
     {
      int pin = val;
      int modeShift = 2 * pin;
      int modeMask = 3 << modeShift;
      port->MODER &= ~modeMask;
      port->MODER |= 1 << modeShift;
      int bit = (1 << pin);
      port->ODR |= bit;
      gpioInfo(port);

      query(&gethex, &val, "\nset: ");
      port->ODR &= ~bit;
      gpioInfo(port);

      query(&gethex, &val, "\nclr: ");
      port->MODER = modeSave;
      gpioInfo(port);
     }
    }
   }
   else if (ch == 'I')
   {
    ch = query("\nPort: ");
    unsigned int i;
    P_PORT_LIST p = portList;
    GPIO_TypeDef *port = nullptr;
    for (i = 0; i < sizeof(portList) / sizeof(T_PORT_LIST); i++)
    {
     if (ch == p->ch)
     {
      port = p->port;
      putBufChar(ch);
      break;
     }
    }
    if (port != nullptr)
    {
     if (query(&gethex, &val, "\nmask: "))
     {
      port->ODR = val;
      printf("\n");
      gpioInfo(port);
     }
    }
   }
#if 1
   else if (ch == 'J')
   {
    newline();
    mxI2CInit();
    i2cInfo(I2C_DEV, I2C_NAME);
    printf("\n");
    gpioInfo(I2C_GPIO);
   }
   else if (ch == 'K')
   {
    newline();
    lcdInit();
   }
#endif
   else if (ch == 'L')
   {
    newline();
    setBacklight(1);
    setCursor(0, 0);
    char buf[2];
    buf[1] = 0;
    for (int row = 0; row < 4; row++)
    {
     setCursorBuf(0, row);
     buf[0] = '0' + row;
     lcdString(buf);
     lcdString(" Test");
     i2cSend();
     while (i2cCtl.state != I_IDLE)
      i2cControl();
    }
   }
   else if (ch == 'O')
   {
    zSynSetup(runCtl.feedType, runCtl.zFeed, rVar.runoutDistance, rVar.runoutDepth);
    unsigned int step;
    int count;
    int curCount;
    int lastCount;
    P_ACCEL ac = &zTA;
    step = ac->initialStep;
    lastCount = (int) (ac->cFactor * sqrt(step));
    step++;
    printf("step      count    lastCount\n");
    for (; step < ac->finalStep; step++)
    {
     count = (int) (ac->cFactor * sqrt(step));
     curCount = count - lastCount;
     printf("%4d %10d %12d\n", step, curCount, lastCount);
     lastCount = count;
    }
   }
   else if (ch == 'Q')
    info();

#if DBGMSG
   else if (ch == 'D')		/* dump dbg buffer */
   {
    newline();
    int empty = dbgQue.emp;
    int i;
    for (i = 0; i < dbgQue.count; i++)
    {
     P_DBGMSG p = &dbgQue.data[empty];
     float t = (float) p->time / 1000;
     printf("%8.3f %7s %6d\n", t, dMessageList[(int) p->dbg], (int) p->val);
     empty++;
     if (empty >= MAXDBGMSG)
      empty = 0;
    }
    printf("z %d x %d\n", rVar.zLoc, rVar.xLoc);
   }
   else if (ch == 'E')		/* clear debug buffer */
   {
    memset(&dbgQue.data, 0, sizeof(dbgQue.data));
    dbgQue.count = 0;
    dbgQue.fil = 0;
    dbgQue.emp = 0;
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
    if (gethex(&val))
    {
     unsigned char *p;

     p = (unsigned char *) (int) val;
     if (gethex(&val))
     {
      newline();
      prtBuf(p, val);
     }
    }
   }
   else if (ch == 'r')		/* read memory */
   {
    putBufChar(' ');
    if (gethex(&val))
    {
     printf("%x", *(int16_t *) (int) val);
    }
   }
   else if (ch == 'w')
   {
    putBufChar(' ');
    if (gethex(&val))
    {
     int16_t *p;
     p = (int16_t *) (int) val;
     printf(" %x ", *p);
     if (gethex(&val))
     {
      *p = (int16_t) val;
     }
    }
   }
#if 0
   else if (ch == 'p')
   {
    putBufChar(' ');
    if (getNum())
    {
     print = val;
    }
   }
#endif
   else if (ch == 'x')
   {
    putBufChar(' ');
    if (getNum(&val))
    {
     xMoveRel(xDist, CMD_MAX);
    }
   }
#if 0
   else if (ch == 'u')
   {
    putBufChar(' ');
    if (getNum())
    {
     dbgMsg(D_TEST, val);
    }
   }
#endif
   else if (ch == 'Y')
   {
    putstr("\nminRPM ");
    if (getfloat(&fVal))
     spA.minRPM = fVal;
    putstr("maxRPM ");
    if (getfloat(&fVal))
     spA.maxRPM = fVal;
    putstr("aTime ");
    if (getfloat(&fVal))
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
    if (getfloat(&fVal))
     threadTPI(&zTA, fVal);
   }
   else if (ch == 'M')
   {
    putstr("\npitch mm ");
    if (getfloat(&fVal))
     threadMetric(&zTA, fVal);
   }
   else if (ch == 'Z')
   {
    float accel = 0.5;
    putstr("\nz Accel Time ");
    if (getfloat(&fVal))
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
     int16_t i = TRKBUFSIZE;
     while (--i >= 0)
     {
      auto tmp = (int16_t) (*(int16_t *) &trkbuf[idx]);
      printf("%4d %6d %4x\n", idx, tmp, (uint16_t) tmp);
      idx += 1;
      idx &= (TRKBUFSIZE - 1);
     }
    }
    if (DBGTRK1L)
    {
     int16_t i = TRKBUFSIZE / 2;
     while (--i >= 0)
     {
      int *p = (int *) &trkbuf[idx];
      if (DBGTRK1L1)
      {
       MPG_VAL mpgVal;
       mpgVal.intVal = *p;
       printf("%4d x%08x %2d %8d\n",
	      idx, (unsigned int) mpgVal.intVal, mpgVal.dir, mpgVal.delta);
      }
      else
      {
       int tmp0 = *p;
       printf("%4d %10d\n", idx, tmp0);
      }
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
      auto *p = (int16_t *) &trkbuf[idx];
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
	   rVar.zLoc, (float) rVar.zLoc / (float) zAxis.stepsInch,
	   ((float) rVar.zHomeOffset) / (float) zAxis.stepsInch,
	   ((float) runCtl.zHomeOffset) / (float) zAxis.stepsInch);
    if (rVar.cfgDro)
     printf("zDro %6d %7.4f  zDroOffset %7.4f\n",
	    rVar.zDroLoc, ((float) rVar.zDroLoc) / (float) rVar.zDroCountInch,
	    ((float) rVar.zDroOffset) / (float) rVar.zDroCountInch);

    printf("xLoc %6d %7.4f xHomeOffset %7.4f %7.4f\n",
	   rVar.xLoc, (float) rVar.xLoc / (float) xAxis.stepsInch,
	   ((float) rVar.xHomeOffset) / (float) xAxis.stepsInch,
	   ((float) runCtl.xHomeOffset) /(float) xAxis.stepsInch);
    if (rVar.cfgDro)
     printf("xDro %6d %7.4f  xDroOffset %7.4f\n",
	    rVar.xDroLoc, ((float) rVar.xDroLoc) / (float) rVar.xDroCountInch,
	    ((float) rVar.xDroOffset) / (float) rVar.xDroCountInch);
    fflush(stdout);
   }
  }
 }
}

void zCommand()
{
 int val;
 float fVal;
 newline();
 while (true)
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
   if (query(&getNum, &val, "dist [%d] ", zDist))
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
   if (getfloat(&fVal))
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
   if (getfloat(&fVal))
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
   if (query(&getNum, &val, "dist [%d] ", zDist))
    zDist = val;
   newline();

   if (rVar.zFlag == 0)
    rVar.zFlag = CMD_MOV;
   if (query(&getNum, &val, "flag [%d] ", rVar.zFlag))
    rVar.zFlag = val;
   newline();

   zMoveRel(zDist, rVar.zFlag);
   break;
  }
  else if (ch == ' ')
   break;
 }
}

void xCommand()
{
}

#endif
