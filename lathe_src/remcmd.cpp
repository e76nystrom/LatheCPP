#define LATHECPP_REMCMD
#if !defined(WIN32)
#ifdef STM32F4
#include "stm32f4xx_hal.h"
#endif
#ifdef STM32F7
#include "stm32f7xx_hal.h"
#endif
#ifdef STM32H7
//#include "stm32h7xx_hal.h"
#endif
#endif

#include "lathe.h"
//#include "remStruct.h"

#include "Xilinx.h"

#if !defined(WIN32)
#include "serialio.h"
#include "spix.h"
//#include "encoder.h"
#endif

#if !defined(EXT)
#define EXT
#endif  /* EXT */

#include "remcmd.h"
#include "remParm.h"
#if defined(USB)
#include "class/cdc/cdc_device.h"
#endif  /* USB */

#if defined(MEGAPORT)
#include "megaCmdList.h"
#endif	/* MEGAPORT */

#if defined(REMCMD_INCLUDE)	// <-

#if !defined(EXT)
#define EXT extern
#endif

#if defined(USB)
#define REM_USB 0
#endif  /* USB */

#define REM_ISR 1		/* remote port using isr */
#define DBG_LOAD 1

void remCmd();
void loadVal();

#include "remCmdList.h"
#include "remParmList.h"
#include "ctlbits.h"

#endif	/* REMCMD_INCLUDE*/ // ->
#ifdef LATHECPP_REMCMD

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

#endif	/* WIN32 */

void loadVal()
{
 int parm;
 getHexRem(&parm);		/* read the parameter number */
 if (parm < MAX_PARM)		/* if in range */
 {
  T_INT_FLOAT intFloat;
  T_DATA_UNION parmVal;
  int type = getHexFloatRem(&intFloat); /* get the value */
  if (type == INT_VAL)		/* if integer */
  {
#if DBG_LOAD
   int size = remParm[parm];	/* value size */
   printf("w parm %2x s %d val %8x\n", parm, size, (unsigned) intFloat.i);
#endif
   parmVal.t_int = intFloat.i;
  }
  else if (type == FLOAT_VAL)	/* if floating value */
  {
   parmVal.t_float = intFloat.f;
#if DBG_LOAD
   printf("w parm %2x     val %8.4f\n", parm, intFloat.f);
#endif
  }
  setRemVar(parm, parmVal);
 }
}

void queMove()
{
 int parm;
 getHexRem(&parm);		/* save op code and flag */
 T_INT_FLOAT intFloat;
 char rtn = getHexFloatRem(&intFloat); /* read parameter */
 if (rtn != NO_VAL)		  /* if valid number */
 {
  if (rVar.setupDone)		/* if setup complete */
  {
   if (rtn == FLOAT_VAL)	  /* if floating */
    queMoveCmd(parm, intFloat.f); /* que command */
   else				  /* if integer */
    queIntCmd(parm, intFloat.i);  /* que command */
  }
 }
}

#define BYTE_COUNT

void remCmd()
{
 dbgRemCmdSet();
 int parm;
 int val;

#if defined(USB)
 remCtl.tx_fil = 0;
 remCtl.tx_count = 0;
#endif  /* USB */

 remcmdUpdateTime = millis();
 remcmdTimeout = REMCMD_TIMEOUT;

 putRem('-');
#if defined(BYTE_COUNT)
 skipRem(2);
#endif  /* BYTE_COUNT */
 getHexRemEcho(&parm);		/* read parameter */
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
  spindleSetup((int) rVar.spMaxRpm);
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
  int tmpVal = zMoveCtl.state;
  tmpVal |= xMoveCtl.state << 4;
  sndHexRem((unsigned char *) &tmpVal, sizeof(tmpVal));
 }
 break;

 case LOADVAL:			/* load a local parameter */
  loadVal();
  break;

 case LOADMULTI:		/* load multiple parameters */
 {
  int count;
  getHexRem(&count);
  while (--count >= 0)
   loadVal();
 }
 break;

 case READVAL:			/* read a local parameter */
 {
  getHexRem(&parm);		/* save the parameter number */
  T_DATA_UNION parmVal;
  parmVal.t_int = 0;
  getRemVar(parm, &parmVal);
  int tmp = remParm[parm];
  int size = tmp & SIZE_MASK;
  char buf[12];
  if (tmp & FLT)
   snprintf(buf, sizeof(buf), "%6.4f", parmVal.t_float);
  else
   snprintf(buf, sizeof(buf), "%x", parmVal.t_unsigned_int);
  printf("r p %2x s %d v %s\n", (unsigned int) parm, size, buf);
  putStrRem(buf);
  putRem(' ');
 }
 break;

 case LOADXREG:			/* load a xilinx register */
 {
  getHexRem(&parm);		/* save the parameter number */

  getHexRem(&val);		/* get the value */
  LOAD(parm, val);		/* load value to xilinx register */
 }
 break;

 case READXREG:			/* read a xilinx register */
 {
  getHexRem(&parm);		/* save the parameter number */
  //   read(parm);		/* read the xilinx register */
  read1(parm);			/* read the xilinx register */
  sndHexRem((unsigned char *) &readval, sizeof(readval)); /* return the parm */
 }
 break;

 case READALL:
 {
  char buf[80];
//  if (zAxis.stepsInch != 0)
//  {
  // sprintf(buf, "%0.4f ", ((float) zLoc) / zAxis.stepsInch);
  sprintf(buf, "%d ", rVar.zLoc);
  putStrRem(buf);
//  }
//  else
//   putStrRem("# ");

//  if (xAxis.stepsInch != 0)
//  {
  // sprintf(buf, "%0.4f ", ((float) xLoc) / xAxis.stepsInch);
  sprintf(buf, "%d ", rVar.xLoc);
  putStrRem(buf);
//  }
//  else
//   putStrRem("# ");

  if (rVar.cfgFpga == 0)        /* processor control */
  {
   if (rVar.indexPeriod != 0)
   {
    sprintf(buf, "%1.0f ",
	    ((float) idxTmr.freq / (float) rVar.indexPeriod) * 60);
    putStrRem(buf);
   }
   else
    putStrRem("0 ");
  }
  else				/* xilinx control */
  {
   putStrRem("0 ");
  }

  sprintf(buf, "%d %d %d %d ",
	  runCtl.pass, rVar.zDroLoc, rVar.xDroLoc, rVar.mvStatus);
  putStrRem(buf);

  sprintf(buf, "%d %d ", MAX_CMDS - moveQue.count, dbgQue.count);
  putStrRem(buf);
 }
 break;

 case CLEARQUE:			/* clear move que */
  runInit();
  break;

 case QUEMOVE:			/* que move operation */
  queMove();
  break;

 case MOVEMULTI:		/* add multiple items to move que */
 {
  int count;
  getHexRem(&count);
  while (--count >= 0)
   queMove();
 }
 break;

 case MOVEQUESTATUS:		/* get move queue status */
 {
  parm = MAX_CMDS - moveQue.count; /* calculate amount empty */
  sndHexRem((unsigned char *) &parm, sizeof(parm)); /* send it back */
 }
 break;

#if DBGMSG
#define MAX_DBG_SIZE (2 + 1 + 1 + 8 + 1)
 case READDBG:
 {
  getHexRem(&parm);
  if (dbgQue.count > 0)		/* if debug messages */
  {
   while (--parm >= 0)		/* while more requested */
   {
    --dbgQue.count;		/* count off a message */
    P_DBGMSG p = &dbgQue.data[dbgQue.emp]; /* get pointer to data */
    dbgQue.emp++;		 /* update empty pointer */
    if (dbgQue.emp >= MAXDBGMSG) /* if past end */
     dbgQue.emp = 0;		/* point back to beginning */

    sndHexRem((unsigned char *) &p->dbg, sizeof(p->dbg)); /* output data */

    putRem(' ');		/* output a space */
    if (p->val < 0)
    {
     putRem('-');
     p->val = -p->val;
    }
    sndHexRem((unsigned char *) &p->val, sizeof(p->val)); /* output data */
    putRem(' ');		/* output a space */

    if ((remCtl.tx_count > (REM_TX_SIZE - MAX_DBG_SIZE)) || /* no space */
        (dbgQue.count == 0))	/* or no data */
     break;			/* exit loop */
   }
  }
 }
 break;

 case CLRDBG:
  clrDbgBuf();
  break;
#endif	/* DBGMSG */

#if ENCODER
 case ENCSTART:
  encStart(true);
  break;

 case ENCSTOP:
  encStop();
  break;
#endif	/* ENCODER */

#if defined(MEGAPORT)

 case SET_MEGA_VAL:
 {
  putMega(1);
  char ch = MEGA_SET_VAL;
  sndhexMega((const unsigned char *) &ch, sizeof(ch), ' ');
  getHexRem(&parm);		/* read parameter */
  sndhexMega((const unsigned char *) &parm, sizeof(parm), ' ');
  getHexRem(&val);		/* read value */
  sndhexMega((const unsigned char *) &val, sizeof(val), '\r');
 }
 break;

#endif  /* MEGAPORT */
 default:
  printf("remCmd default\n");
  break;
 } /* switch */

#if REM_ISR
 while (true)
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
#endif	/* REM_ISR */

// flushBuf();
 putRem('*');

#if defined(BYTE_COUNT)
 {
  char buf[4];
  sprintf(buf, "%02x", countRem() - 3);
//  putBufStr(buf);
//  newline();
  fillRem(buf, 2);
 }
#endif  /* BYTE_COUNT */

 dbgRemCmdClr();
}

#endif	/* LATHECPP_REMCMD */
