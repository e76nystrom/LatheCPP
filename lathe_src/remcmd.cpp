//#if !defined(INCLUDE)
#define __REMCMD__
#if !defined(WIN32)
#ifdef STM32F4
#include "stm32f4xx_hal.h"
#endif
#ifdef STM32F7
#include "stm32f7xx_hal.h"
#endif
#ifdef STM32H7
#include "stm32h7xx_hal.h"
#endif
#endif

#include "remstruct.h"
#include "lathe.h"

#include "Xilinx.h"
#if !defined(WIN32)
#include "serialio.h"
#include "spix.h"
#include "encoder.h"
#endif

#ifdef EXT
#undef EXT
#endif

#define EXT
#include "remcmd.h"
//#endif

#if defined(__REMCMD_INC__)	// <-

#if !defined(EXT)
#define EXT extern
#endif

#define REM_ISR 1		/* remote port using isr */

#if REM_ISR
#define putrem putRem
#define putstrrem putstrRem
#define sndhexrem sndhexRem
#define getrem getRem
#define gethexrem() gethexRem()
#define getnumrem getnumRem
#define getstrrem getstrRem
#else
#define putrem putx1
#define putstrrem putstr1
#define sndhexrem sndhex1
#define getrem get1
#define gethexrem gethex1
#define getnumrem getnum1
#define getstrrem getstr1
#endif

#define DBG_LOAD 1

void remcmd(void);
void loadVal(void);

EXT int16_t tmpval;

#include "cmdList.h"
#include "parmList.h"
#include "ctlbits.h"

#endif	// ->
#ifdef __REMCMD__

#if defined(WIN32)

typedef union
{
 char b[4];			/* char array */
 int32_t i;			/* long interger */
} byte_long;

int16_t val;
byte_long readval;

#define LOAD(a, b)
#define putx(a)
#define sndhex(a, b)
#define gethex()
#define read1(x)
//#define SNDHEX(a)

char chgmask;
char zstop;
char xstop;
char cmdPause;

void zLoad()
{
}

void xLoad()
{
}

void zMove(int dist, char flag)
{
}

void zMoveRel(int dist)
{
}

void xMove(int dist, char flag)
{
}

void xMoveRel(int dist)
{
}

#endif

#include "remparm.h"

void loadVal(void)
{
 gethexrem();			/* read the parameter number */
 int parm = valRem;		/* save it */

#if 1
 if (parm < MAX_PARM)		/* if in range */
 {
  T_DATA_UNION parmVal;
  int type = getnumrem();	/* get the value */
  if (type == INT_VAL)		/* if integer */
  {
#if DBG_LOAD
   int size = remparm[parm].size; /* value size */
   printf("w parm %2x s %d val %8x\n", parm, size, (unsigned) valRem);
#endif
   parmVal.t_int = valRem;
  }
  else if (type == FLOAT_VAL)	/* if floating value */
  {
   parmVal.t_float = fValRem;
#if DBG_LOAD
   printf("w parm %2x     val %8.4f\n", parm, fValRem);
#endif
  }
  setRemVar(parm, parmVal);
 }
#else
 if (parm < MAX_PARM)		/* if in range */
 {
  P_PARM valptr = &remparm[parm]; /* pointer to parameter info */
  p = (unsigned char *) (valptr->p); /* destination pointer */
  int size = valptr->size;	/* value size */

  int type = getnumrem();	/* get the value */
  if (type == INT_VAL)		/* if integer */
  {
#if DBG_LOAD
   printf("w %2x %d (%08x) =  %8x\n",
	  parm, size, (unsigned) p, (unsigned) valRem);
#endif
   if (size == 4)		/* if a long word */
   {
    *(int32_t *) p = valRem;	/* save as a long word */
   }
   else if (size == 1)		/* if a character */
   {
    *p = valRem;		/* save the character */
   }
   else if (size == 2)		/* if a short integer */
   {
    *(int16_t *) p = valRem;	/* save the value */
   }
  }
  else if (type == FLOAT_VAL)	/* if floating value */
  {
#if DBG_LOAD
   printf("w %2x f (%08x) =  %8.4f\n", parm, (unsigned) p, fValRem);
#endif
   *(float *) p = fValRem;	/* save as a float */
  }
 }
#endif
}

void remcmd(void)
{
 dbgRemCmdSet();
 int parm;

 remcmdUpdateTime = millis();
 remcmdTimeout = REMCMD_TIMEOUT;

 putrem('-');
 gethexrem();			/* read parameter */
 parm = valRem;
 switch (parm)
 {
 case ZMOVEABS:
  zMoveAbsCmd();
  break;

 case ZMOVEREL:
  zMoveRelCmd();
  break;

 case ZJMOV:
  zJogCmd();
  break;

 case ZJSPEED:
  zJogSpeedCmd();
  break;

 case ZSTOP:
  zStop();
 break;

 case ZSETLOC:
  zLocCmd();
 break;

 case ZHOMEFWD:
  homeAxis(&zHomeCtl, HOME_FWD);
 break;

 case ZHOMEREV:
  homeAxis(&zHomeCtl, HOME_REV);
 break;

 case XMOVEABS:
  xMoveAbsCmd();
 break;

 case XMOVEREL:
  xMoveRelCmd();
 break;

 case XJMOV:
  xJogCmd();
 break;

 case XJSPEED:
  xJogSpeedCmd();
 break;

 case XSTOP:
  xStop();
 break;

 case XSETLOC:
  xLocCmd();
 break;

 case XHOMEFWD:
  homeAxis(&xHomeCtl, HOME_FWD);
 break;

 case XHOMEREV:
  homeAxis(&xHomeCtl, HOME_REV);
 break;

 case SPINDLE_START:
  spindleStart();
 break;

 case SPINDLE_STOP:
  spindleStop();
 break;

 case SPINDLE_UPDATE:
  spindleUpdate();
 break;

 case SPINDLE_JOG:
  spindleJog();
 break;

 case SPINDLE_JOG_SPEED:
  spindleJogSpeed();
 break;

 case CMD_PAUSE:
  pauseCmd();
 break;

 case CMD_RESUME:
  resumeCmd();
 break;

 case CMD_STOP:
  stopCmd();
 break;

 case CMD_DONE:
  doneCmd();
 break;

 case CMD_MEASURE:
  measureCmd();
 break;

 case CMD_CLEAR:
  clearCmd();
 break;

 case CMD_SETUP:
  setup();
 break;

 case CMD_SPSETUP:
  spindleSetup(rVar.spMaxRpm);
 break;

 case CMD_SYNCSETUP:
  syncMoveSetup();
 break;

 case CMD_ZSETUP:
  zSetup();
 break;

#if 0
 case CMD_ZTAPERSETUP:
  zTaperSetup();
 break;
#endif

 case CMD_XSETUP:
  xSetup();
 break;

#if 0
 case CMD_XTAPERSETUP:
  xTaperSetup();
 break;
#endif

 case READSTAT:
 break;

 case READISTATE:
 {
  tmpval = zMoveCtl.state;
  tmpval |= xMoveCtl.state << 4;
  sndhexrem((unsigned char *) &tmpval, sizeof(tmpval));
 }
 break;

 case LOADVAL:			/* load a local parameter */
  loadVal();
 break;

 case LOADMULTI:		/* load multiple parameters */
 {
  gethexrem();
  int count = valRem;
  while (--count >= 0)
   loadVal();
 }
 break;

 case READVAL:			/* read a local parameter */
 {
  gethexrem();			/* save the parameter number */
  parm = valRem;		/* save it */
#if 1
  T_DATA_UNION parmVal;
  parmVal.t_int = 0;
  getRemVar(parm, &parmVal);
  int size = remparm[parm].size;
  printf("r p %2x s %d v %8x\n",
	 (unsigned int) parm, size, parmVal.t_unsigned_int);
  sndhexrem((unsigned char *) &parmVal.t_char, size); /* send the response */
#else
  valptr = &remparm[parm];	/* pointer to parameters */
  if (DBG_LOAD)
  {
   unsigned char *p = (unsigned char *) (valptr->p);
   char size;
   unsigned int tmp = 0;
   size = valptr->size;
   if (size == 4)
   {
    tmp = *(int32_t *) p;
   }
   else if (size == 1)
   {
    tmp = *p;
   }
   else if (size == 2)
   {
    tmp = *(int16_t *) p;
   }
   printf("r %2x %d (%08x) = %8x\n",
	  (unsigned int) parm, size, (unsigned int) p, tmp);
  }
  sndhexrem((unsigned char *) valptr->p, valptr->size); /* send the response */
#endif
 }
 break;

 case LOADXREG:			/* load a xilinx register */
 {
  gethexrem();			/* save the parameter number */
  parm = valRem;		/* save it */
  gethexrem();			/* get the value */
  LOAD(parm, val);		/* load value to xilinx register */
 }
 break;

 case READXREG:			/* read a xilinx register */
 {
  gethexrem();			/* save the parameter number */
  parm = valRem;		/* save it */
//   read(parm);		/* read the xilinx register */
  read1(parm);			/* read the xilinx register */
  sndhexrem((unsigned char *) &readval, sizeof(readval)); /* return the parm */
 }
 break;

 case READALL:
 {
  char buf[80];
//  if (zAxis.stepsInch != 0)
//  {
  // sprintf(buf, "%0.4f ", ((float) zLoc) / zAxis.stepsInch);
  sprintf(buf, "%d ", rVar.zLoc);
  putstrrem(buf);
//  }
//  else
//   putstrrem("# ");

//  if (xAxis.stepsInch != 0)
//  {
  // sprintf(buf, "%0.4f ", ((float) xLoc) / xAxis.stepsInch);
  sprintf(buf, "%d ", rVar.xLoc);
  putstrrem(buf);
//  }
//  else
//   putstrrem("# ");

  if (rVar.cfgFpga == 0)		/* processor control */
  {
   if (rVar.indexPeriod != 0)
   {
    sprintf(buf, "%1.0f ",
	    ((float) indexFreq / (uint32_t) rVar.indexPeriod) * 60);
    putstrrem(buf);
   }
   else
    putstrrem("0 ");
  }
  else				/* xilinx control */
  {
   putstrrem("0 ");
  }

  sprintf(buf, "%d %d %d %d",
	  runCtl.pass, rVar.zDroLoc, rVar.xDroLoc, rVar.mvStatus);
  putstrrem(buf);
 }
 break;

 case CLEARQUE:			/* clear move que */
  runInit();
 break;

 case QUEMOVE:			/* que move operation */
 {
  gethexrem();			/* save op code and flag */
  parm = valRem;		/* save input value */
  char rtn = getnumrem();	/* read parameter */
  if (rtn != NO_VAL)		/* if valid number */
  {
   if (rVar.setupDone)		/* if setup complete */
   {
    if (rtn == FLOAT_VAL)	/* if floating */
     queMoveCmd(parm, fValRem);	/* que command */
    else			/* if integer */
     queIntCmd(parm, valRem);	/* que command */
   }
  }
 }
 break;

 case MOVEQUESTATUS:		/* get move queue status */
 {
  parm = MAX_CMDS - moveQue.count; /* calculate amount empty */
  sndhexrem((unsigned char *) &parm, sizeof(parm)); /* send it back */
 }
 break;

#if DBGMSG
#define MAX_DBG_SIZE (2 + 1 + 1 + 8 + 1)
 case READDBG:
 {
  gethexrem();
  parm = valRem;
  if (dbgcnt > 0)		/* if debug messages */
  {
   while (--parm >= 0)		/* while more requested */
   {
    --dbgcnt;			/* count off a message */
    P_DBGMSG p = &dbgdata[dbgemp]; /* get pointer to data */
    dbgemp++;			/* update empty pointer */
    if (dbgemp >= MAXDBGMSG)	/* if past end */
     dbgemp = 0;		/* point back to beginning */

#if DBGMSG == 2
    sndhexrem((unsigned char *) &p->dbg, sizeof(p->dbg)); /* output data */
#else
    int16_t count = sizeof(p->str); /* get maximum length */
    char *p1 = p->str;		/* get poninter to string */
    while (--count >= 0)	/* while not at end of buffer */
    {
     char ch = *p1++;		/* read a character */
     if (ch == 0)		/* if null */
      break;			/* exit loop */
     putrem(ch);		/* output character */
    }
#endif
    putrem(' ');		/* output a space */
    if (p->val < 0)
    {
     putrem('-');
     p->val = -p->val;
    }
    sndhexrem((unsigned char *) &p->val, sizeof(p->val)); /* output data */
    if ((remCtl.tx_count < (TX_BUF_SIZE - MAX_DBG_SIZE)) /* if space */
	&&  (dbgcnt != 0))		/* and more data */
     putrem(' ');		/* output a space */
    else			/* if no more data */
     break;			/* exit loop */
   }
  }
 }
 break;

 case CLRDBG:
  clrDbgBuf();
 break;
#endif

#if ENCODER
 case ENCSTART:
  encStart(true);
 break;

 case ENCSTOP:
  encStop();
 break;
#endif
 }

#if REM_ISR
 while (1)
 {
  int tmp = getRem();
  if (tmp < 0)
  {
   printf("end of buffer\n");
   break;
  }
  if (tmp == '\r')
   break;
  printf("extra char %d\n", tmp);
  flushBuf();
 }
#endif

// flushBuf();
 putrem('*');
 dbgRemCmdClr();
}

#endif
