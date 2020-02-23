//#if !defined(INCLUDE)
#define __LATHEX__
#include "stm32f4xx_hal.h"

#include <stdlib.h>
#include <inttypes.h>

#include "lathe.h"

#include "spi.h"
#include "Xilinx.h"
#include "zcontrol.h"
#include "xcontrol.h"
#include "encoder.h"
#include "serialio.h"

#ifdef EXT
#undef EXT
#endif

#define EXT
#include "latheX.h"
//#endif

#if defined(__LATHEX_INC__)	// <-

#ifdef WIN32
#define DBG_DETAIL 1
#else
#define DBG_DETAIL 0
#endif

int bitSize(int val);

void axisCtlX(void);

void setupX(void);

void spindleStartX(void);		/* start spindle */
void spindleStopX(void);		/* stop spindle */
void spindleSetupX(int rpm);

void zStopX(void);
void zSetupX(void);
void zMoveSetupX(void);
void zSynSetupX(int feedType, float feed);
void zTaperSetupX(void);

void xStopX(void);
void xSetupX(void);
void xMoveSetupX(void);
void xSynSetupX(int feedType, float feed);
void xTaperSetupX(void);

void accelCalcX(P_ACCEL ac);

void turnPitchX(P_ACCEL ac, float pitch);
void threadTPIX(P_ACCEL ac, float tpi);
void threadMetricX(P_ACCEL ac, float pitch);
void turnAccelX(P_ACCEL ac, float accel);
void accelSetupX(P_ACCEL ac);

void taperCalcX(P_ACCEL a0, P_ACCEL a1, float taper);

void zTaperInitX(P_ACCEL ac, char dir);
void xTaperInitX(P_ACCEL ac, char dir);

char *i64toa(long long val, char *buf, int buflen);

int tmp(int x);

#endif	// ->
#ifdef __LATHEX__

#ifdef WIN32

#undef LOAD
#define LOAD(a, b)
void stopMove(){}
void zJMove(int dir){}
void zMove(int32_t pos, char cmd){}
void zMoveRel(int32_t dist, char cmd){}
void xJMove(int dir){}
void xMove(int32_t pos, char cmd){}
void xMoveRel(int32_t dist, char cmd){}
void encStart(int tEna){}
void encStop(){}

char cmdPause;
T_MOVEQUE moveQue;

#endif	/* WIN32 */

#define MAX_SCALE 12
#define clr(x) memset(&x, 0, sizeof(x))

int tmp(int x)
{
 return(x);
}

void axisCtlX(void)
{
 if (zMoveCtl.state != ZIDLE)	/* if z axis active */
 {
  read1(XRDZLOC);		/* read z location */
  zLoc = readval.i;
  read1(XRDSR);		/* read status register */
  if (zMoveCtl.wait)		/* if wait flag set */
  {
   if ((readval.i & S_Z_START) == 0) /* if start flag not set */
   {
    if (DBGMSG)
     dbgmsg(D_ZWT, readval.i);
    printf("z waiting no start flag\n");
    zMoveCtl.wait = 0;
   }
  }
  if ((readval.i & S_Z_DONE_INT) /* if done bit set */
  ||  (zFlagX()))		/* if z done flag from xilinx set */
  {
   if (DBGMSG)
    dbgmsg(D_ZDN, zLoc);
   printf("z done\n");
   LOAD(XLDZCTL, 0);		/* clear z control register */
   zMoveCtl.done = 1;		/* signal done */
  }
  zControlX();			/* run z axis state machine */
 }

 if (xMoveCtl.state != XIDLE)	/* if x axis active */
 {
  read1(XRDXLOC);		/* read x location */
  xLoc = readval.i;
  read1(XRDSR);		/* read status register */
  if (xMoveCtl.wait)		/* if wait flag set */
  {
   if ((readval.i & S_X_START) == 0) /* if start flag not set */
   {
    if (DBGMSG)
     dbgmsg(D_XST, readval.i);
    printf("x waiting no start flag\n");
    xMoveCtl.wait = 0;
   }
  }
  if ((readval.i & S_X_DONE_INT) /* if done bit set */
  ||  (xFlagX()))		/* if x done flag from xilinx set */
  {
   printf("x done\n");
   if (DBGMSG)
    dbgmsg(D_XDN, xLoc);
   LOAD(XLDXCTL, 0);		/* clear x control register */
   xMoveCtl.done = 1;		/* set done flag */
  }
  xControlX();			/* run x axis state machine */
 }
}

int bitSize(int val)
{
 int bits = 0;
 while (bits < 32)
 {
  if (val == 0)
   break;
  val >>= 1;
  bits += 1;
 }
 return(bits);
}

void setupX(void)
{
 if (DBG_SETUP)
  printf("\nsetup\n");
#if WIN32
 fflush(stdout);
#endif
}

void spindleStartX(void)
{
 if (DBG_SETUP)
  printf("\nspindle start\n");
#if ENCODER
 if (encEnable)
  encStart(true);
#endif
#if WIN32
 fflush(stdout);
#endif
}

void spindleStopX(void)
{
 if (DBG_SETUP)
  printf("\nspindle stop\n");
#if ENCODER
 if (encEnable)
 {
  encStop(true);
  encEnable = 0;
 }
#endif
#if WIN32
 fflush(stdout);
#endif
}

void spindleSetupX(int rpm)
{
 if (DBG_SETUP)
  printf("\nspindle setup rpm %d\n", rpm);
 LOAD(XLDCFG, xCfgReg);
#if WIN32
 fflush(stdout);
#endif
}

void zStopX(void)
{
 LOAD(XLDZCTL, 0);		/* stop z */
}

void zSetupX(void)
{
 P_AXIS axis = &zAxis;

 if (DBG_SETUP)
  printf("\nz axis setup\n");
 axis->pitch = zPitch;
 axis->ratio = zRatio;
 axis->microSteps = zMicro;
 axis->motorSteps = zMotor;
 axis->accel = zAccel;
 axis->backlash = zBacklash;

 axis->stepsInch = lrint((axis->microSteps * axis->motorSteps * 
			  axis->ratio) / axis->pitch);
 axis->backlashSteps = lrint(axis->backlash * axis->stepsInch);

 zMoveSetupX();
#if WIN32
 fflush(stdout);
#endif
}

void zMoveSetupX(void)
{
 zTA.stepsInch = zAxis.stepsInch;

 P_ACCEL ac = &zMA;

 ac->minFeed = zMoveMin;
 ac->maxFeed = zMoveMax;
 ac->accel = zAxis.accel;
 ac->stepsInch = zAxis.stepsInch;

 if (DBG_SETUP)
  printf("\nz move accel\n");
 accelCalcX(ac);

 ac = &zJA;

 ac->minFeed = zJogMin;
 ac->maxFeed = zJogMax;
 ac->accel = zAxis.accel;
 ac->stepsInch = zAxis.stepsInch;

 if (DBG_SETUP)
  printf("\nz jog accel\n");
 accelCalcX(ac);

 ac = &zPA;
 ac->stepsInch = zAxis.stepsInch;
}

void zSynSetupX(int feedType, float feed)
{
 if (DBG_SETUP)
  printf("\nz sync accel\n");
 P_ACCEL ac = &zTA;
 ac->stepsInch = zAxis.stepsInch;
 ac->minFeed = zMA.minFeed;	/* set minimum */
 ac->accel = zAxis.accel;
 switch (feedType)
 {
 case FEED_PITCH:
  turnPitchX(ac, feed);
  break;
 case FEED_TPI:
  threadTPIX(ac, feed);
  break;
 case FEED_METRIC:
  threadMetricX(ac, feed);
  break;
 }
 turnAccelX(ac, zAccel);
#if WIN32
 fflush(stdout);
#endif
}

void zTaperSetupX(void)
{
}

void xStopX(void)
{
 LOAD(XLDXCTL, 0);		/* stop x */
}

void xSetupX(void)
{
 P_AXIS axis = &xAxis;

 if (DBG_SETUP)
  printf("\nX axis setup\n");
 axis->pitch = xPitch;
 axis->ratio = xRatio;
 axis->microSteps = xMicro;
 axis->motorSteps = xMotor;
 axis->accel = xAccel;
 axis->backlash = xBacklash;

 axis->stepsInch = lrint((axis->microSteps * axis->motorSteps * 
			  axis->ratio) / axis->pitch);
 axis->backlashSteps = lrint(axis->backlash * axis->stepsInch);

 xMoveSetupX();
#if WIN32
 fflush(stdout);
#endif
}

void xMoveSetupX(void)
{
 P_ACCEL ac = &xMA;

 ac->minFeed = xMoveMin;
 ac->maxFeed = xMoveMax;
 ac->accel = xAxis.accel;
 ac->stepsInch = xAxis.stepsInch;

 if (DBG_SETUP)
  printf("\nx move accel\n");
 accelCalcX(ac);

 ac = &xJA;

 ac->minFeed = xJogMin;
 ac->maxFeed = xJogMax;
 ac->accel = xAxis.accel;
 ac->stepsInch = xAxis.stepsInch;

 if (DBG_SETUP)
  printf("\nx jog accel\n");
 accelCalcX(ac);

 ac = &zPA;
 ac->stepsInch = zAxis.stepsInch;
}

void xSynSetupX(int feedType, float feed)
{
 if (DBG_SETUP)
  printf("\nx sync accel\n");
 P_ACCEL ac = &xTA;
 ac->stepsInch = xAxis.stepsInch;
 ac->minFeed = xMA.minFeed;	/* set minimum */
 ac->accel = xAxis.accel;
 switch (feedType)
 {
 case FEED_PITCH:
  turnPitchX(ac, feed);
  break;
 case FEED_TPI:
  threadTPIX(ac, feed);
  break;
 case FEED_METRIC:
  threadMetricX(ac, feed);
  break;
 }
 turnAccelX(ac, xAccel);
#if WIN32
 fflush(stdout);
#endif
}

void xTaperSetupX(void)
{
}

/* calculate acceleration for move */

void accelCalcX(P_ACCEL ac)
{
 int stepsSecMax = (int) ((ac->maxFeed / 60.0) * ac->stepsInch);
 ac->clockFreq = stepsSecMax * freqMult;
 ac->clocksPerInch = ac->stepsInch * freqMult;
 ac->freqDivider = (fpgaFrequency / ac->clockFreq) - 1;
 if (DBG_SETUP)
  printf("freqGenMax %d freqDivider %d\n", ac->clockFreq, ac->freqDivider);

 accelSetupX(ac);
}

void turnPitchX(P_ACCEL ac, float pitch)
{
 if (DBG_SETUP)
  printf("\nturnPitch\n");
 ac->pitch = pitch;
}

void threadTPIX(P_ACCEL ac, float tpi)
{
 if (DBG_SETUP)
  printf("\nturnTPI\n");
 ac->pitch = (float) (1.0 / tpi);
}

void threadMetricX(P_ACCEL ac, float pitch)
{
 if (DBG_SETUP)
  printf("\nturnMetric\n");
 ac->pitch = (float) (pitch / 25.4);
}

/* calculate acceleration for turn */

void turnAccelX(P_ACCEL ac, float accel)
{
 if (DBG_SETUP)
  printf("\nturnAccel %3.1f\n", accel);
 ac->maxFeed = rpm * ac->pitch;
 ac->clocksPerInch = (int) (encPerRev / ac->pitch);
 ac->clockFreq = (int) ((rpm * encPerRev) / 60.0);
 if (ac->maxFeed < ac->minFeed)	/* if below minimum */
 {
  ac->intAccel = 0;
  ac->accelClocks = 0;
 }
 else
 {
  accelSetupX(ac);
 }
}

void accelSetupX(P_ACCEL ac)
{
 if (DBG_SETUP)
 {
  printf("accel %0.2f minFeed %0.2f feedRate %0.2f ipm\n",
	 ac->accel, ac->minFeed, ac->maxFeed);
  printf("clocksPerInch %d clockFreq %d stepsInch %d\n",
	 ac->clocksPerInch, ac->clockFreq, ac->stepsInch);
 }

 int stepsSecMax = (int) ((ac->maxFeed * ac->stepsInch) / 60.0);
 int stepsSecMin = (int) ((ac->minFeed * ac->stepsInch) / 60.0);
 if (DBG_SETUP)
  printf("stepsSecMin %d stepsSecMax %d\n", stepsSecMin, stepsSecMax);

 float stepsSec2 = (float) (ac->accel * ac->stepsInch);
 ac->accelTime = (float) ((stepsSecMax - stepsSecMin) / stepsSec2);
 ac->accelClocks = (int) (ac->clockFreq * ac->accelTime);
 if (DBG_SETUP)
  printf("stepsSec2 %0.0f accelTime %8.6f accelClocks %d\n",
	 stepsSec2, ac->accelTime, ac->accelClocks);

 int accelMinStep = (int) (((stepsSecMin / stepsSec2) * stepsSecMin) / 2.0);
 int accelMaxStep = (int) (((stepsSecMax / stepsSec2) * stepsSecMax) / 2.0);
 ac->accelSteps = accelMaxStep - accelMinStep;
 if (DBG_SETUP)
  printf("accelSteps %d accelMinStep %d accelMaxStep %d\n", 
	 ac->accelSteps, accelMinStep, accelMaxStep);

 int dxBase = ac->clocksPerInch;
 int dyMaxBase = ac->stepsInch;
 int dyMinBase = (int) ((ac->stepsInch * ac->minFeed) / ac->maxFeed);
 if (DBG_SETUP)
  printf("\ndxBase %d dyMaxBase %d dyMinBase %d\n",
	 dxBase, dyMaxBase, dyMinBase);

 int scale;
 int accelClocks = ac->accelClocks;
 int intIncPerClock = 0;
 for (scale = 0; scale < MAX_SCALE; scale++)
 {
  ac->dx = dxBase << scale;
  ac->dyMax = dyMaxBase << scale;
  int dyMin = dyMinBase << scale;
  int dyDelta = ac->dyMax - dyMin;
  if (DBG_DETAIL)
   printf("\nscale %d dx %d dyMin %d dyMax %d dyDelta %d\n",
	  scale, ac->dx, dyMin, ac->dyMax, dyDelta);

  float incPerClock = (float) dyDelta / accelClocks;
  intIncPerClock = (int) incPerClock;
  if (intIncPerClock == 0)
   continue;
  ac->intIncPerClock = intIncPerClock;
  int dyDeltaC = intIncPerClock * accelClocks;
  int err = (int) (abs(dyDelta - dyDeltaC)) >> scale;
  ac->dyIni = ac->dyMax - intIncPerClock * accelClocks;
  if (DBG_DETAIL)
   printf("dyIni %d dyMax %d intIncPerClock %d accelClocks %d\n",
	  ac->dyIni, ac->dyMax, intIncPerClock, accelClocks);

  int bits = bitSize(ac->dx) + 1;
  if (DBG_DETAIL)
   printf("dyIni %d dyMax %d dyDelta %d incPerClock %6.2f "
	  "err %d bits %d\n",
	  ac->dyIni, ac->dyMax, dyDelta, incPerClock, err, bits);

  if ((bits >= 30)
  ||  (err == 0))
  {
   if (DBG_SETUP)
   {
    printf("\nscale %d dx %d dyMin %d dyMax %d dyDelta %d\n",
	   scale, ac->dx, dyMin, ac->dyMax, dyDelta);
    printf("dyIni %d dyMax %d dyDelta %d incPerClock %6.2f "
	   "err %d bits %d\n",
	   ac->dyIni, ac->dyMax, dyDelta, incPerClock, err, bits);
   }
   break;
  }
 }
 ac->scale = scale;
 ac->incr1X = 2 * ac->dyIni;
 ac->incr2X = ac->sum - 2 * ac->dx;
 ac->sum = ac->incr1X - ac->dx;
 ac->intAccel = 2 * intIncPerClock;
 if (DBG_SETUP)
  printf("\nincr1 %d incr2 %d sum %d\n", ac->incr1X, ac->incr2X, ac->sum);
 
 if (intIncPerClock != 0)
 {
  int64_t totalSum = (int64_t) accelClocks * ac->incr1X + ac->sum;
  int64_t totalInc = ((int64_t) accelClocks * (accelClocks - 1) * 
		      ac->intAccel) / 2;
  ac->accelSteps = (int) ((totalSum + totalInc) / (2 * ac->dx));
#ifdef WIN32
  if (DBG_SETUP)
   printf("accelClocks %d "
	  "totalSum %" PRId64 " totalInc %" PRId64 " accelSteps %d\n", 
	  ac->accelClocks, totalSum, totalInc, ac->accelSteps);
#else
  if (DBG_SETUP)
  {
   char buf[32];
   printf("accelClocks %d ", ac->accelClocks);
   printf("totalSum %s ", i64toa(totalSum, buf, sizeof(buf)));
   printf("totalInc %s ", i64toa(totalInc, buf, sizeof(buf)));
   printf("accelSteps %d\n",  ac->accelSteps);
  }
#endif
 }
 else
 {
  ac->accelSteps = 0;
 }
}

void taperCalcX(P_ACCEL a0, P_ACCEL a1, float taper)
{
 if (DBG_SETUP)
  printf("\ntaperCalc %s %s\n", a0->label, a1->label);

 a1->taper = true;
 a1->taperInch = taper;

 a1->dx = a1->stepsInch;
 a1->dyMax = (int) (taper * a1->stepsInch);

 a1->incr1X = 2 * a1->dyMax;
 a1->incr2X = a1->incr1X - 2 * a1->dx;
 a1->sum = a1->incr1X - a1->dx;
 if (DBG_SETUP)
 {
  printf("dx %d dy %d",  a1->dx, a1->dyMax);
  printf("incr1 %d incr2 %d sum %d bits %d",
	 a1->incr1X, a1->incr2X, a1->sum, bitSize(a1->incr2X));
 }
#ifdef WIN32
 fflush(stdout);
#endif
}

void zTaperInitX(P_ACCEL ac, char dir)
{
 printf("\nztaperInit\n");

 LOAD(XLDZCTL, dir);
 LOAD(XLDZD, ac->sum);
 LOAD(XLDZINCR1, ac->incr1X);
 LOAD(XLDZINCR2, ac->incr2X);
 LOAD(XLDZACCEL, 0);
 LOAD(XLDZACLCNT, 0);
 LOAD(XLDTCTL, TENA | TZ);
#ifdef WIN32
 fflush(stdout);
#endif
}

void xTaperInitX(P_ACCEL ac, char dir)
{
 printf("\nxtaperInit\n");
 LOAD(XLDXCTL, dir);
 LOAD(XLDXD, ac->sum);
 LOAD(XLDXINCR1, ac->incr1X);
 LOAD(XLDXINCR2, ac->incr2X);
 LOAD(XLDXACCEL, 0);
 LOAD(XLDXACLCNT, 0);
 LOAD(XLDTCTL, TENA | TX);
#ifdef WIN32
 fflush(stdout);
#endif
}

char *i64toa(long long val, char *buf, int buflen)
{
 char minus = false;
 if (val < 0)
 {
  minus = true;
  val = -val;
 }
 char *p = buf + buflen;
 --buflen;
 *--p = 0;
 while (val != 0)
 {
  --buflen;
  if (buflen <= 0)
   break;
  *--p = (val % 10) + '0';
  val /= 10;
 }
 if (minus)
 {
  --buflen;
  if (buflen > 0)
   *--p = '-';
 }
 return(p);
}

#endif
