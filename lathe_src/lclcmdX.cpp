//#if !defined(INCLUDE)
#define __LCLCMDX__
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
#include "stm32Info.h"

#include "Xilinx.h"
#include "serialio.h"
#include "spix.h"
#include "zcontrol.h"
#include "xcontrol.h"
#include "encoder.h"

#if DBGMSG
extern const char *dMessageList[];
#endif

#ifdef EXT
#undef EXT
#endif

#define EXT
#include "lclcmdX.h"
//#endif

#if defined(__LCLCMDX_INC__)	// <-

void lclcmdX(int ch);
void readreg(char addr,char *str);
void loadregb(char addr, char val);

extern int16_t addr;

#endif	// ->
#if !defined(INCLUDE)

#define dx (2540l * 8l)
#define dy 600l

#define incr1 (2 * dy)
#define incr2 (2 * (dy - dx))
#define d (incr1 - dx)

#define FREQ 1000l
#define MINVELOCITY 100l
#define MAXVELOCITY 1000l
#define ACCEL 2000l

#define SCALE 8

#define accelFreq (FREQ << SCALE)
#define minVelocity (MINVELOCITY << SCALE)
#define maxVelocity (MAXVELOCITY << SCALE)
#define accel ((ACCEL << SCALE) / FREQ)

void readreg(char addr,char *str)
{
 read1(addr);			/* read from device */
 printf("\nread addr %2x val %8lx %10ld %s",addr,readval.i,readval.i,str);
}

#define LOADX(a,b) loadreg(a,(byte_long) ((int32_t) b))

void loadreg(char addr, byte_long val);

void loadreg(char addr, byte_long val)
{
 printf("sending addr %2x %10ld val %8lx\n",addr,val.i,val.i);
 load(addr,val.i);
}

void loadregb(char addr, char val)
{
 printf("sending addr %2x %10d val %8x\n",addr,val,val);
 loadb(addr,val);
}

void lclcmdX(int ch)
{
 int val;
 if (ch == 'd')			/* dump memory */
 {
  putx(' ');
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
#if DBGMSG
 else if (ch == 'D')		/* dump dbg buffer */
 {
  newline();
  int empty = dbgQue.emp;
  for (int i = 0; i < dbgQue.count; i++)
  {
   P_DBGMSG p = &dbgQue.data[empty];
   float t = (float) p->time / 1000;
   printf("%8.3f %7s %8x %12d\n", t, dMessageList[(int) p->dbg],
	  (unsigned int) p->val, (int) p->val);
   empty++;
   if (empty >= MAXDBGMSG)
    empty = 0;
   while (1)
   {
    if (pollBufChar() == 0)
     break;
   }
  }
  printf("z %d x %d\n", rVar.zLoc, rVar.xLoc);
 }
 else if (ch == 'E')		/* clear debug buffer */
 {
  clrDbgBuf();
 }
#endif
#if ENC_TEST
 else if (ch == 'e')
 {
  printf(" counts ");
  fflush(stdout);
  if (getNum(&val))
  {
   encInit();
   rVar.encRunCount = val;
   encStart(true);
  }
  else
  {
   printf(" stop[y] ");
   fflush(stdout);
   ch = getx();
   if (ch == 'y')
   {
    encStop();
   }
  }
 }
#endif
 else if (ch == 't')
 {
  putx(' ');
  if (getNum(&val))
  {
   newline();
   int i;
   int j = 0;
   for (i = 0; i < val; i++)
   {
    LOAD(XLDZCTL, j);
    read1(XRDZCTL);
    int testVal = j & ((1 << (zCtlSize)) - 1);
    if (readval.i != testVal)
    {
//     setSync();
     printf("%4d z testVal %8x readVal %8x\n",
	    i, (unsigned int) testVal, (unsigned int) readval.i);
//     clrSync();
    }

    LOAD(XLDXCTL, j);
    read1(XRDXCTL);
    testVal = j & ((1 << (xCtlSize)) - 1);
    if (readval.i != testVal)
    {
//     setSync();
     printf("%4d x testVal %8x readVal %8x\n",
	    i, (unsigned int) testVal, (unsigned int) readval.i);
//     clrSync();
    }
    j += 1;
    while (pollBufChar() != 0)
     ;
   }
  }
 }
 else if (ch == 'q')
 {
  extiInfo();
  gpioInfo(GPIOA);
  usartInfo(DBGPORT, "DBG");
  usartInfo(REMPORT, "REM");
 }
 else if (ch == 'r')		/* read memory */
 {
  putx(' ');
  if (gethex(&val))
  {
   printf("%x",*(int16_t *) (int) val);
  }
 }
 else if (ch == 'w')		/* write memory */
 {
  putx(' ');
  if (gethex(&val))
  {
   int16_t *p;
   p = (int16_t *) (int) val;
   printf(" %x ",*p);
   if (gethex(&val))
   {
    *p = val;
   }
  }
 }
 else if (ch == 'a')		/* set command address */
 {
  putx(' ');
  if (getNum(&val))
   addr = val;
 }
 else if (ch == 'g')		/* read spi data */
 {
  putx(' ');
  if (getNum(&val))
  {
   addr = val;			/* save address */
   read1(addr);			/* read from device */
   printf("\nread addr %x val %8lx %10ld",addr,readval.i,readval.i);
  }
 }
 else if (ch == 'G')		/* read spi repeatedly */
 {
  putx(' ');
  if (getNum(&val))			/* enter address */
  {
   addr = val;			/* save address */
   putx(' ');
   if (getNum(&val))		/* enter number of tries */
   {
    newline();
    int16_t i = (int16_t) val;
    while (1)
    {
     read1(addr);		/* read from device */
     if (dbgRxReady())		/* if character available */
     {
      ch = dbgRxRead();
      break;
     }
     if ((i != 0)
     &&  (--i <= 0))
      break;
    }
    printf("spiw0 %d spiw1 %d",spiw0,spiw1);
   }
  }
 }
 else if (ch == 's')		/* send val to address a */
 {
  printf(" addr ");
  fflush(stdout);
  if (getNum(&val))			/* read address */
  {
   addr = val;
   printf(" data ");
   fflush(stdout);
   if (getNum(&val))		/* read data */
   {
    printf("\nsending addr %x %10d val %8lx", addr, val, (unsigned long) val);
    LOAD(addr,val);
   }
  }
 }
#if 0
 else if (ch == 'p')		/* set print flag */
 {
  putx(' ');
  if (getNum(&val))
  {
   print = val;
  }
 }
#endif
 else if (ch == 'r')		/* reset */
 {
  LOAD(XLDZCTL,0);
  LOAD(XLDXCTL,0);
  LOAD(XLDTCTL,0);
  LOAD(XLDDCTL,0);
 }
 else if (ch == 'x')		/* move x rel */
 {
  putx(' ');
  if (getNum(&val))
  {
   xMoveRelX(val, CMD_MOV);
  }
 }
 else if (ch == 'z')		/* move z rel */
 {
  putx(' ');
  if (getNum(&val))
  {
   zMoveRelX(val, CMD_MOV);
  }
 }
 else if (ch == 'u')		/* send debug message */
 {
  putx(' ');
  if (getNum(&val))
  {
   dbgMsg(D_TEST, val);
  }
 }
}

#endif
