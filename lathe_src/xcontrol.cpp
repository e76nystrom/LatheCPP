//#if !defined(INCLUDE)
#define __XCONTROL__
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

#include "Xilinx.h"
#include "remcmd.h"
#include "spix.h"
#include "serialio.h"
#include "latheX.h"

#ifdef EXT
#undef EXT
#endif

#define EXT
#include "xcontrol.h"
//#endif

#if defined(__XCONTROL_INC__)	// <-

void xSynLoad(void);
void xJMoveX(int dir);
void xMoveX(int32_t pos, char cmd);
void xMoveRelX(int32_t dist, char cmd);
void xControlX(void);

#endif	// ->
#ifdef __XCONTROL__

void xLoad(P_ACCEL ac);

void xLoad(P_ACCEL ac)
{
 if (ac->freqDivider != 0)
  LOAD(XLDXFREQ, ac->freqDivider);
 LOAD(XLDXD, ac->sum);
 LOAD(XLDXINCR1, ac->incr1X);
 LOAD(XLDXINCR2, ac->incr2X);
 LOAD(XLDXACCEL, ac->intAccel);
 LOAD(XLDXACLCNT, ac->accelClocks);
}

void xJMoveX(int dir)
{
 P_MOVECTL mov = &xMoveCtl;
 if (mov->state == AXIS_IDLE)	/* if not moving */
 {
  P_ACCEL ac = &xJA;		/* pointer to jog */
  float time = rVar.jogTimeInitial - ac->timeX; /* time after accel */
  int d = ac->stepsX + (int) (ac->stepsSecX * time); /* initial steps */
  mov->iniDist = d;		/* save initial distance */
  if (dir < 0)			/* if direction negative */
   d = -d;			/* set to negative */
  mov->stop = 0;		/* clear stop flag */
  mov->jogInc = (int) (rVar.jogTimeInc * ac->stepsSecX); /* save increment */
  mov->maxDist = (int) (rVar.jogTimeMax * ac->stepsSecX); /* save maximum */
  printf("xJMove dist %5d xLoc %5d inc %5d max %5d\n",
	 d, rVar.xLoc, mov->jogInc, mov->maxDist);
  xMoveRelX(d, CMD_JOG);	/* start movement */
 }
 else if (mov->state == AXIS_WAIT_BACKLASH) /* if waiting for backlash */
 {
 }
 else				/* if moving */
 {
 }
}

void xMoveX(long pos, char cmd)
{
 P_MOVECTL mov = &xMoveCtl;

 if (DBGMSG)
  dbgMsg(D_XMOV, pos);
 read1(XRDXLOC);		/* read x location */
 mov->loc = readval.i;		/* save result */
 if (DBGMSG)
  dbgMsg(D_XLOC, mov->loc);
 mov->expLoc = pos;		/* save expected location */
 printf("x move %5d %5d\n", (int) pos, (int) (pos - mov->loc));
 xMoveRelX(pos - mov->loc, cmd); /* calculate move distance */
}

void xMoveRelX(long dist, char cmd)
{
 P_MOVECTL mov = &xMoveCtl;

 if (mov->state != AXIS_IDLE)	/* if not in idle state */
  return;			/* exit now */

 if (DBGMSG)
  dbgMsg(D_XDST, dist);
 mov->cmd = cmd;		/* save command */
 if (dist != 0)			/* if distance non zero */
 {
  mov->dist = dist;		/* save move distance */
  if (mov->dist > 0)		/* if moving positive */
  {
   mov->state = ((mov->dir == DIR_NEG) ?
		 AXIS_WAIT_BACKLASH : AXIS_START_MOVE); /* dir chg ? */
   mov->dir = DIR_POS;		/* set to move positive direction */
  }
  else
  {
   mov->dist = -mov->dist;	/* make distance a positive number */
   mov->state = ((mov->dir == DIR_POS) ?
		 AXIS_WAIT_BACKLASH : AXIS_START_MOVE); /* dir chg ? */
   mov->dir = DIR_NEG;		/* set move direction to negative */
  }

  if (mov->state == AXIS_WAIT_BACKLASH)	/* if backlash move needed */
  {
   mov->wait = 1;		/* set wait flag */
   xLoad(&xMA);			/* load move parameters */
   mov->ctlreg = XSTART | XBACKLASH; /* initialize ctl reg */
   if (mov->dir == DIR_POS)	/* if positive direction */
    mov->ctlreg |= XDIR_POS;	/* set direction flag */
   LOAD(XLDXDIST,  xAxis.backlashSteps); /* load backlash */
   LOAD(XLDXCTL,  mov->ctlreg);	/* start move */
   read1(XRDSR);
   if ((readval.i & S_X_START) == 0)
    printf("x start not set\n");
  }
  mov->done = 0;		/* clear done flag */
  mov->stop = 0;		/* clear stop flag */
 }
}

void xControlX(void)
{
 P_MOVECTL mov = &xMoveCtl;
 if (mov->stop)			/* if stop */
  mov->state = AXIS_DONE;	/* clean up in done state */

 if (DBGMSG)
 {
  if (mov->state != mov->prev)
  {
   dbgMsg(D_XST, mov->state);
   mov->prev = mov->state;
  }
 }

 switch(mov->state)		/* dispatch on state */
 {
 case AXIS_IDLE:		/* 0x00 idle state */
  break;

 case AXIS_WAIT_BACKLASH:	/* 0x01 wait for backlash move to complete */
 {
  if (mov->done)		/* if done */
  {
   mov->done = 0;		/* clear done flag */
   mov->wait = 0;		/* clear wait flag */
   mov->state = AXIS_START_MOVE; /* advance to move state */
  }
 }
 break;

 case AXIS_START_MOVE:		/* 0x02 start an x move */
 {
  mov->ctlreg = XSTART;		/* initialize control reg */
  char ch = mov->cmd & CMD_MSK;	/* get type of move */
  if (ch == CMD_SYN)		/* if synchronized move */
  {
   xLoad(&xTA);			/* load turn parameters */
   mov->ctlreg |= XSRC_SYN;	/* set sync flags */
  }
  else				/* if not synchronized */
  {
   if (ch == CMD_JOG)		/* if jog */
    xLoad(&xMA);		/* load jog parameters */
   else if (ch == CMD_MAX)		/* if max */
    xLoad(&xMA);		/* load move parameters */
   else				/* else */
    xLoad(&xTA);		/* load turn parameters */
  }
  if (mov->dir == DIR_POS)	/* if moving positive */
   mov->ctlreg |= XDIR_POS;	/* set direction flag */
  LOAD(XLDXDIST,  mov->dist);	/* set distance to move */
  LOAD(XLDXCTL,  mov->ctlreg);	/* start move */
  read1(XRDSR);
  if ((readval.i & S_X_START) == 0)
   printf("x start not set\n");
  mov->wait = 1;		/* set wait flag */
  mov->state = AXIS_WAIT_MOVE;	/* wait for move to complete */
 }
 break;

 case AXIS_WAIT_MOVE:		/* 0x03 wait for an x move to complete */
 {
  if (mov->done)		/* if done */
  {
   mov->wait = 0;		/* clear wait flag */
   mov->state = AXIS_DONE;	/* clean up everything */
  }
 }
 break;

 case AXIS_DONE:		/* 0x04 done state */
 default:			/* all others */
 {
  LOAD(XLDXCTL,  0);		/* stop move */
  mov->stop = 0;		/* clear stop flag */
  mov->done = 0;		/* clear done flag */
  mov->cmd = 0;			/* clear command */
  read1(XRDXLOC);		/* read current location */
  mov->loc = readval.i;		/* save it */
  if (mov->loc != mov->expLoc)	/* if not at expected location */
  {
   printf("x move error actual %d expected %d\n", mov->loc, mov->expLoc);
   if (DBGMSG)
    dbgMsg(D_XEXP, mov->expLoc);
  }
  if (DBGMSG)
   dbgMsg(D_XLOC, mov->loc);
  mov->state = AXIS_IDLE;	/* set state to idle */
  if (DBGMSG)
   dbgMsg(D_XST, mov->state);
 }
 break;
 }
}


#endif
