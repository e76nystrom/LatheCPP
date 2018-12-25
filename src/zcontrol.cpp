#if !defined(INCLUDE)
#include "stm32f4xx_hal.h"
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "config.h"
#include "remvar.h"
#include "Xilinx.h"
#include "remcmd.h"
#include "spi.h"
#include "serialio.h"
#include "lathe.h"
#include "latheX.h"
#endif

void zSynLoad(void);
void zJMoveX(int dir);
void zMoveX(int32_t pos, char cmd);
void zMoveRelX(int32_t dist, char cmd);
void zControlX(void);

#if !defined(INCLUDE)

void zLoad(P_ACCEL ac);

void zLoad(P_ACCEL ac)
{
 if (ac->freqDivider != 0)
  LOAD(XLDZFREQ, ac->freqDivider);
 LOAD(XLDZD, ac->sum);
 LOAD(XLDZINCR1, ac->incr1X);
 LOAD(XLDZINCR2, ac->incr2X);
 LOAD(XLDZACCEL, ac->intAccel);
 LOAD(XLDZACLCNT, ac->accelClocks);
}

void zJMoveX(int dir)
{
 P_MOVECTL mov = &zMoveCtl;
 if (mov->state == ZIDLE)	/* if not moving */
 {
  P_ACCEL ac = &zJA;		/* pointer to jog */
  float time = jogTimeInitial - ac->timeX; /* time after accel */
  int d = ac->stepsX + (int) (ac->stepsSecX * time); /* initial steps */
  mov->iniDist = d;		/* save initial distance */
  if (dir < 0)			/* if direction negative */
   d = -d;			/* set to negative */
  mov->stop = 0;		/* clear stop flag */
  mov->jogInc = (int) (jogTimeInc * ac->stepsSecX); /* save increment */
  mov->maxDist = (int) (jogTimeMax * ac->stepsSecX); /* save maximum */
  printf("zJMove dist %5d zLoc %5d inc %5d max %5d\n", 
	 d, zLoc, mov->jogInc, mov->maxDist);
  zMoveRelX(d, CMD_JOG);	/* start movement */
 }
 else if (mov->state == ZWAITBKLS) /* if waiting for backlash */
 {
 }
 else				/* if moving */
 {
 }
}

void zMoveX(int32_t pos, char cmd)
{
 P_MOVECTL mov = &zMoveCtl;

 if (DBGMSG)
  dbgmsg(D_ZMOV, pos);
 read1(XRDZLOC);		/* read z location */
 mov->loc = readval.i;		/* save result */
 if (DBGMSG)
  dbgmsg(D_ZLOC, mov->loc);
 mov->expLoc = pos;		/* save expected location */
 printf("z move %5d %5d\n", (int) pos, (int) (pos - mov->loc));
 zMoveRelX(pos - mov->loc, cmd); /* calculate move distance */
}

void zMoveRelX(int32_t dist, char cmd)
{
 P_MOVECTL mov = &zMoveCtl;

 if (mov->state != ZIDLE)	/* if not in idle state */
  return;			/* exit now */

 mov->cmd = cmd;		/* save command */
 if (dist != 0)			/* if distance non zero */
 {
  if (dist > 0)			/* if moving positive */
  {
   mov->dist = dist;		/* update distance */
   mov->state = (mov->dir == DIR_NEG) ?  ZWAITBKLS : ZSTARTMOVE; /* dir chg ? */
   mov->dir = DIR_POS;		/* set to move positive direction */
  }
  else
  {
   mov->dist = -dist;		/* make distance a positive number */
   mov->state = (mov->dir == DIR_POS) ?  ZWAITBKLS : ZSTARTMOVE; /* dir chg ? */
   mov->dir = DIR_NEG;		/* set move direction to negative */
  }

  if (mov->state == ZWAITBKLS)	/* if backlash move needed */
  {
   mov->wait = 1;		/* set wait flag */
   zLoad(&zMA);		/* load move parameters */
   mov->ctlreg = ZSTART | ZBACKLASH; /* initialize ctl reg */
   if (mov->dir == DIR_POS)	/* if positive direction */
    mov->ctlreg |= ZDIR_POS;	/* set direction flag */
   LOAD(XLDXDIST,  zAxis.backlashSteps); /* load backlash */
   LOAD(XLDZCTL, mov->ctlreg);	/* start move */
   read1(XRDSR);
   if ((readval.i & S_Z_START) == 0)
    printf("z start not set\n");
  }
  mov->done = 0;		/* clear done flag */
  mov->stop = 0;		/* clear stop flag */
 }
}

void zControlX(void)
{
 P_MOVECTL mov = &zMoveCtl;

 if (mov->stop)			/* if stop */
  mov->state = ZDONE;		/* clean up in done state */

 if (DBGMSG)
 {
  if (mov->state != mov->prev)
  {
   dbgmsg(D_ZST, mov->state);
   mov->prev = mov->state;
  }
 }

 switch(mov->state)		/* dispatch on state */
 {
 case ZIDLE:			/* 0 idle state */
  break;

 case ZWAITBKLS:		/* 1 wait for backlash move to complete */
 {
  if (mov->done)		/* if done */
  {
   mov->done = 0;		/* clear done flag */
   mov->wait = 0;		/* clear wait flag */
   mov->state = ZSTARTMOVE;	/* advance to start move state */
  }
 }
 break;

 case ZSTARTMOVE:		/* 2 start a z move */
 {
  mov->ctlreg = ZSTART;		/* initialize control reg */
  char ch = mov->cmd & CMD_MSK;	/* get type of move */
  if (ch == CMD_SYN)		/* if synchronized move */
  {
   zLoad(&zTA);			/* load turn parameters */
   mov->ctlreg |= ZSRC_SYN;	/* set sync flags */
   if (mov->cmd & Z_SYN_START)	/* if wait for sync */
    mov->ctlreg |= ZWAIT_SYNC;	/* set to wait for sync */
  }
  else
  {
   if (ch == CMD_JOG)		/* if jog */
    zLoad(&zJA);		/* load jog parameters */
   else if (ch == CMD_MAX)	/* if max */
    zLoad(&zMA);		/* load move parameters */
   else				/* else */
    zLoad(&zTA);		/* load turn parameters */
  }
  if (mov->dir == DIR_POS)		/* if moving positive */
   mov->ctlreg |= ZDIR_POS;	/* set direction flag */
  LOAD(XLDZDIST, mov->dist);	/* set distance to move */
  LOAD(XLDZCTL, mov->ctlreg);	/* start move */
  read1(XRDSR);
  if ((readval.i & S_Z_START) == 0)
   printf("z start not set\n");
  mov->wait = 1;		/* set wait flag */
  mov->state = ZWAITMOVE;	/* wait for move to complete */
 }
 break;

 case ZWAITMOVE:		/* 3 wait for a z move to complete */
 {
  if (mov->done)		/* if done */
  {
   mov->wait = 0;		/* clear wait flag */
   mov->state = ZDONE;		/* clean up everything */
  }
 }
 break;

 case ZDONE:			/* 4 done state */
 default:			/* all others */
 {
  LOAD(XLDZCTL, 0);		/* stop move */
  mov->stop = 0;		/* clear stop flag */
  mov->done = 0;		/* clear done flag */
  mov->cmd = 0;			/* clear command */
  read1(XRDZLOC);		/* read current location */
  mov->loc = readval.i;		/* save it */
  if (mov->loc != mov->expLoc)	/* if not at expected location */
  {
   printf("z move error actual %d expected %d\n", mov->loc, mov->expLoc);
   if (DBGMSG)
    dbgmsg(D_ZEXP,  mov->expLoc);
  }
  if (DBGMSG)
   dbgmsg(D_ZLOC, mov->loc);
  mov->state = ZIDLE;		/* set state to idle */
  if (DBGMSG)
   dbgmsg(D_ZST, mov->state);
 }
 break;
 }
}

#endif
