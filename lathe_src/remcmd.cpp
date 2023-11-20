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
//#include "remParm.h"
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
#include "remParm.h"
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
  if (const int type = getHexFloatRem(&intFloat); type == INT_VAL)		/* if integer */
  {
#if DBG_LOAD
   const int size = remSize[parm];	/* value size */
   printf("w parm %2x s %d val %8x\n", parm, size, static_cast<unsigned>(intFloat.i));
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
 if (const char rtn = getHexFloatRem(&intFloat); rtn != NO_VAL)		  /* if valid number */
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

#pragma clang diagnostic push
#pragma ide diagnostic ignored "bugprone-branch-clone"
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
 case C_Z_MOVE_ABS:
  zMoveAbsCmd();
  break;

 case C_Z_MOVE_REL:
  zMoveRelCmd();
  break;

 case C_Z_J_MOV:
  zJogCmd();
  break;

 case C_Z_J_SPEED:
  zJogSpeedCmd();
  break;

 case C_Z_STOP:
  zStop();
  break;

 case C_Z_SET_LOC:
  zLocCmd();
  break;

 case C_Z_HOME_FWD:
  homeAxis(&zHomeCtl, HOME_FWD);
  break;

 case C_Z_HOME_REV:
  homeAxis(&zHomeCtl, HOME_REV);
  break;

 case C_X_MOVE_ABS:
  xMoveAbsCmd();
  break;

 case C_X_MOVE_REL:
  xMoveRelCmd();
  break;

 case C_X_J_MOV:
  xJogCmd();
  break;

 case C_X_J_SPEED:
  xJogSpeedCmd();
  break;

 case C_X_STOP:
  xStop();
  break;

 case C_X_SET_LOC:
  xLocCmd();
  break;

 case C_X_HOME_FWD:
  homeAxis(&xHomeCtl, HOME_FWD);
  break;

 case C_X_HOME_REV:
  homeAxis(&xHomeCtl, HOME_REV);
  break;

 case C_SPINDLE_START:
  spindleStart();
  break;

 case C_SPINDLE_STOP:
  spindleStop();
  break;

 case C_SPINDLE_UPDATE:
  spindleUpdate();
  break;

 case C_SPINDLE_JOG:
  spindleJog();
  break;

 case C_SPINDLE_JOG_SPEED:
  spindleJogSpeed();
  break;

 case C_CMD_PAUSE:
  pauseCmd();
  break;

 case C_CMD_RESUME:
  resumeCmd();
  break;

 case C_CMD_STOP:
  stopCmd();
  break;

 case C_CMD_DONE:
  doneCmd();
  break;

 case C_CMD_MEASURE:
  measureCmd();
  break;

 case C_CMD_CLEAR:
  clearCmd();
  break;

 case C_CMD_SETUP:
  setup();
  break;

 case C_CMD_SP_SETUP:
  spindleSetup(lrintf(rVar.spMaxRpm));
  break;

 case C_CMD_SYNC_SETUP:
  syncMoveSetup();
  break;

 case C_CMD_Z_SETUP:
  zSetup();
  break;

 case C_CMD_Z_SET_LOC:
  break;

#if 0
 case C_CMD_ZTAPERSETUP:
  zTaperSetup();
  break;
#endif

 case C_CMD_X_SETUP:
  xSetup();
  break;

 case C_CMD_X_SET_LOC:
  break;

#if 0
 case C_CMD_XTAPERSETUP:
  xTaperSetup();
  break;
#endif

 case C_READ_STAT:
  break;

 case C_READ_I_STATE:
 {
  int tmpVal = zMoveCtl.state;
  tmpVal |= xMoveCtl.state << 4;
  sndHexRem(reinterpret_cast<unsigned char *>(&tmpVal), sizeof(tmpVal));
 }
 break;

 case C_LOAD_VAL:		/* load a local parameter */
  loadVal();
  break;

 case C_LOAD_MULTI:		/* load multiple parameters */
 {
  int count;
  getHexRem(&count);
  while (--count >= 0)
   loadVal();
 }
 break;

 case C_READ_VAL:		/* read a local parameter */
 {
  getHexRem(&parm);		/* save the parameter number */
  T_DATA_UNION parmVal;
  parmVal.t_int = 0;
  getRemVar(parm, &parmVal);
  const int tmp = remSize[parm];
  const int size = tmp & SIZE_MASK;
  char buf[12];
  if (tmp & FLT)
   snprintf(buf, sizeof(buf), "%6.4f", parmVal.t_float);
  else
   snprintf(buf, sizeof(buf), "%x", parmVal.t_uint_t);
  printf("r p %2x s %d v %s\n", static_cast<unsigned int>(parm), size, buf);
  putStrRem(buf);
  putRem(' ');
 }
 break;

 case C_LOAD_X_REG:		/* load a xilinx register */
 {
  getHexRem(&parm);		/* save the parameter number */

  getHexRem(&val);		/* get the value */
  LOAD(parm, val);		/* load value to xilinx register */
 }
 break;

 case C_READ_X_REG:		/* read a xilinx register */
 {
  getHexRem(&parm);		/* save the parameter number */
  //   read(parm);		/* read the xilinx register */
  read1(parm);			/* read the xilinx register */
  sndHexRem(reinterpret_cast<unsigned char *>(&readval), sizeof(readval)); /* return the parm */
 }
 break;

 case C_READ_ALL:
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
	    static_cast<float>(idxTmr.freq) / static_cast<float>(rVar.indexPeriod) * 60);
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

 case C_CLEAR_QUE:		/* clear move que */
  runInit();
  break;

 case C_QUE_MOVE:		/* que move operation */
  queMove();
  break;

 case C_MOVE_MULTI:		/* add multiple items to move que */
 {
  int count;
  getHexRem(&count);
  while (--count >= 0)
   queMove();
 }
 break;

 case C_MOVE_QUE_STATUS:		/* get move queue status */
 {
  parm = MAX_CMDS - moveQue.count; /* calculate amount empty */
  sndHexRem(reinterpret_cast<unsigned char *>(&parm), sizeof(parm)); /* send it back */
 }
 break;

#if DBGMSG
#define MAX_DBG_SIZE (2 + 1 + 1 + 8 + 1)
 case C_READ_DBG:
 {
  getHexRem(&parm);
  if (dbgQue.count > 0)		/* if debug messages */
  {
   while (--parm >= 0)		/* while more requested */
   {
    --dbgQue.count;		/* count off a message */
    const P_DBGMSG p = &dbgQue.data[dbgQue.emp]; /* get pointer to data */
    dbgQue.emp++;		 /* update empty pointer */
    if (dbgQue.emp >= MAXDBGMSG) /* if past end */
     dbgQue.emp = 0;		/* point back to beginning */

    sndHexRem(reinterpret_cast<unsigned char *>(&p->dbg), sizeof(p->dbg)); /* output data */

    putRem(' ');		/* output a space */
    if (p->val < 0)
    {
     putRem('-');
     p->val = -p->val;
    }
    sndHexRem(reinterpret_cast<unsigned char *>(&p->val), sizeof(p->val)); /* output data */
    putRem(' ');		/* output a space */

    if (remCtl.tx_count > REM_TX_SIZE - MAX_DBG_SIZE || /* no space */
        dbgQue.count == 0)	/* or no data */
     break;			/* exit loop */
   }
  }
 }
 break;

 case C_CLR_DBG:
  clrDbgBuf();
  break;
#endif	/* DBGMSG */

#if ENCODER
 case C_ENCSTART:
  encStart(true);
  break;

 case C_ENCSTOP:
  encStop();
  break;
#endif	/* ENCODER */

#if defined(MEGAPORT)

 case C_SET_MEGA_VAL:
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

 case C_SEND_DONE:
  break;

#endif  /* MEGAPORT */
 default:
  printf("remCmd default\n");
  break;
 } /* switch */

#if REM_ISR
 while (true)
 {
  const int tmp = getRem();
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
#pragma clang diagnostic pop

#endif	/* LATHECPP_REMCMD */
