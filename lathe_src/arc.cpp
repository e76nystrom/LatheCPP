#define __ARC__

#if defined(STM32F4)
#include "stm32f4xx_hal.h"
//#define LATHE_CPP
#endif	/* STM32F4 */

#ifdef STM32H7
#include "stm32h7xx_hal.h"
//#define LATHE_CPP
#endif

//#define _USE_MATH_DEFINES

#include <cstdio>
#include <cmath>
#include <climits>
#include <cstdlib>
#include <cstring>

#if defined(LATHE_CPP)

#define EXT extern
#include "lathe.h"
#include "arc.h"
#include "ctlbits.h"
//#include "remStruct.h"
#include "timers.h"
#include "serialio.h"

inline void updXLoc(int dir)
{
 rVar.xLoc += dir;
 xIsr.steps += 1;
 xPulseTrig();
}

inline void updZLoc(int dir)
{
 rVar.zLoc += dir;
 zIsr.steps += 1;
 zPulseTrig();
}

#define ISR_DEBUG 1
#define ARC_DEBUG 0
#define TEST 0
#define STM_DEBUG 0

#else

#include "../LatheCPP/include/ctlbits.h"

#define __ARC_INC__
#define EXT
#define __disable_irq()
#define __enable_irq()

inline void updXLoc(int dir) {}
inline void updZLoc(int dir) {}
inline void xTmrPWMDis() {}
inline void dbgArcStepSet() {}
inline void dbgArcStepClr() {}
inline void dbgArcUpdSet() {}
inline void dbgArcUpdClr() {}

#define ARC_DEBUG 1
#define TEST 1
#define STM_DEBUG 0

#if ARC_DEBUG
FILE *f;
#endif

#endif	/* LATHE_CPP */

#if defined(__ARC_INC__)		// <-

#define UPDATE_DEBUG false

#define ARC_BUF_SIZE 256

typedef struct sPoint
{
 int x;
 int z;
} T_POINT, *P_POINT;

typedef struct sArcData
{
 float radius;			/* arc radius */

 T_POINT center;		/* arc center */
 T_POINT p0;			/* start point */
 T_POINT p1;			/* end point */

 int xStepsInch;		/* x steps per inch */
 int zStepsInch;		/* z steps per inch */

 int xRadius;			/* x radius in steps */
 int xRadiusSqrd;		/* x radius squared */
 int xStep45;			/* x steps to 45 degrees */

 int zRadius;			/* z radius in steps */
 int zRadiusSqrd;		/* z radius squared */
 int zStep45;			/* z steps to 45 degrees */

 int octStart;			/* start octant */
 int octEnd;			/* end octant */
 int octant;			/* current octant */

 int xEnd;			/* x end value */
 int inXDir;			/* x direction for generating arc */
 int x;				/* current x */
 int xNext;			/* next x */
 int xLast;			/* last x */
 int cmdX;			/* x value for command */

 int zEnd;			/* z end value */
 int inZDir;			/* z direction for generating arc */
 int z;				/* current z */
 int zNext;			/* next z */
 int zLast;			/* last z */
 int cmdZ;			/* z value for command */

 int delta;			/* change in second axis value */
 int lastDelta;			/* last change */

 int cmdCount[8];		/* command counter */
 int steps;			/* number of steps */
 int oneByte;			/* number of one byte commands */
 int count;			/* current command count */

 bool cwDir;			/* arc direction cw or ccw */
 bool lessThan45;		/* currently less than 45 */
 bool endCheck;			/* last octant check end */
 bool active;			/* arc function active */
 bool done;			/* done */
 bool lastMove;			/* output last move */

 /* data used by isr for generating arc */

 int qCount;			/* bytes in queue */
 unsigned char *emp;		/* queue empty pointer */
 unsigned char *fil;		/* queue fill pointer */
 unsigned char *arcBufEnd;	/* buffer end address */
 unsigned char arcBuf[ARC_BUF_SIZE]; /* arc data buffer */
 unsigned char *lastFil;

 int cmd;			/* command being processed */
 int rpt;			/* repeat value for active command */

 int xDir;			/* x direction for isr */
 int xPos;			/* x position for isr */

 int zDir;			/* z direction for isr */
 int zPos;			/* z position for isr */

 int qCol;
 int sCol;

 int d;				/* sum accumulator */
 int incr1;			/* incr 1 value */
 int incr2;			/* incr 2 value */
 int initialD;			/* initial value for accumulator */

 unsigned int stepX;		/* input steps */
 unsigned int stepY;		/* output steps */
} T_ARC_DATA, *P_ARC_DATA;

EXT T_ARC_DATA arcData;

void arcInit(float radius);
void arcUpdate(bool dbg);
bool arcStep(void);
void arcQue(unsigned char cmd, unsigned char rpt);
int octantStart(int x, int z);
int octantEnd(int x, int z);
void makeCommand(int x, int z, int dbg);

#if defined(LATHE_CPP)
void arcStepSetup(int inCount, int outCount);
void arcStepUpdate();
#endif	/* LATHE_CPP */

#endif	// ->
#if defined(__ARC__)

#if defined(LATHE_CPP) || defined(__GNUC__)
const char *fmtDelta(int delta, char *buf, size_t bufSize)
{
 if (delta == INT_MAX)
  return("None");
 else
 {
  snprintf(buf, bufSize, "%4d", delta);
  return(buf);
 }
}
#else
const char *fmtDelta(int delta, char *buf, rsize_t bufSize)
{
 if (delta == INT_MAX)
  return("None");
 else
 {
  sprintf_s(buf, bufSize, "%4d", delta);
  return(buf);
 }
}
#endif	/* LATHE_CPP || __GNUC__ */

#if ARC_DEBUG
typedef struct sLoc
{
 int x;
 int z;
 int delta;
 int lastDelta;
 int stepX;
 int stepZ;
} T_LOC, *P_LOC;

#define HISTORY_SIZE 1024
T_LOC history[HISTORY_SIZE];
int histCount;
P_LOC histPtr;

int stepHistCount;
P_LOC stepHistPtr;

void resetHistory(void)
{
 histCount = 0;
 histPtr = &history[0];
 stepHistCount = 0;
 stepHistPtr = &history[0];
}

void saveHistory(int x, int z, int delta, int lastDelta)
{
 if (histCount < HISTORY_SIZE)
 {
  histCount += 1;
  histPtr->x = x;
  histPtr->z = z;
  histPtr->delta = delta;
  histPtr->lastDelta = lastDelta;
  histPtr += 1;
 }
}

void saveStepHistory(int x, int z)
{
 if (stepHistCount < HISTORY_SIZE)
 {
  stepHistCount += 1;
  stepHistPtr->stepX = x;
  stepHistPtr->stepZ = z;
  stepHistPtr += 1;
 }
}
#endif

/*       x-
       \5|6/
       4\|/7
   z- ------- z+
       3/|\0
       /2|1\
        x+
*/

int octantStart(int x, int z)
{
 if (x >= 0)
  if (z >= 0)
   return((x < arcData.xStep45) ? 0 : 1);
  else
   return((x <= arcData.xStep45) ? 3 : 2);
 else
 {
  x = -x;
  if (z >= 0)
   return((x <= arcData.xStep45) ? 7 : 6);
  else
   return((x < arcData.xStep45) ? 4 : 5);
 }
}

int octantEnd(int x, int z)
{
 if (x >= 0)
  if (z >= 0)
   return((x <= arcData.xStep45) ? 0 : 1);
  else
   return((x < arcData.xStep45) ? 3 : 2);
 else
 {
  x = -x;
  if (z >= 0)
   return((x < arcData.xStep45) ? 7 : 6);
  else
   return((x <= arcData.xStep45) ? 4 : 5);
 }
}

typedef struct sOctInc
{
 int xInc;
 int zInc;
}
 T_OCT_INC, *P_OCT_INC;

int cwOctDir[] = {PCMD_Z_NEG, PCMD_Z_NEG,
		  PCMD_X_NEG | PCMD_Z_NEG, PCMD_X_NEG | PCMD_Z_NEG};
T_OCT_INC cwOctInc[] = {{1, -1}, {1, -1}, {-1, -1}, {-1, -1}};

int ccwOctDir[] = {PCMD_X_NEG, PCMD_X_NEG, 0, 0};
T_OCT_INC ccwOctInc[] = {{-1, 1}, {-1, 1}, {1, 1}, {1, 1}};

void updOctant(int octant)
{
 P_ARC_DATA arc = &arcData;

 arc->octant = octant;
 if (octant == arc->octEnd)
  arc->endCheck = true;

 arc->lessThan45 = (octant == 0) || (octant == 3);

 int cmd;
 P_OCT_INC inc;
 if (arc->cwDir)
 {
  cmd = cwOctDir[octant];
  inc = &cwOctInc[octant];
 }
 else
 {
  cmd = ccwOctDir[octant];
  inc = &ccwOctInc[octant];
 }

 arc->inXDir = inc->xInc;
#if defined(LATHE_CPP)
 xMoveCtl.dir = inc->xInc;
 if (inc->xInc > 0)
  xMoveCtl.dirFwd();
 else
  xMoveCtl.dirRev();
#endif /* LATHE_CPP */

 arc->inZDir = inc->zInc;
#if defined(LATHE_CPP)
 zMoveCtl.dir = inc->zInc;
 if (inc->zInc > 0)
  zMoveCtl.dirFwd();
 else
  zMoveCtl.dirRev();
#endif /* LATHE_CPP */

 cmd = (PCMD_SET_DIR | ((PCMD_DIR_FLAG | cmd) << PCMD_RPT_SHIFT));
 arcQue(cmd, 0);

#if TEST
 fprintf(f, "\noctant %d inxDir %d inZDir %d cmd %2x\n",
	 octant, arc->inXDir, arc->inZDir, cmd);
#endif	/* TEST */

#if defined(LATHE_CPP)
 printf("\noctant %d inxDir %d inZDir %d cmd %2x\n",
	 octant, arc->inXDir, arc->inZDir, cmd);
 printf("xDir %2d dirXPin %d dirXFwd %8x dirXRev %8x\n"
	"zDir %2d dirXPin %d dirXFwd %8x dirXRev %8x\n",
	xMoveCtl.dir, dirXRead(),
	(unsigned int) xAxis.dirFwd, (unsigned int) xAxis.dirRev,
	zMoveCtl.dir, dirZRead(),
	(unsigned int) zAxis.dirFwd, (unsigned int) zAxis.dirRev);
#endif /* LATHE_CPP */
}

void arcQue(unsigned char cmd, unsigned char rpt)
{
 P_ARC_DATA arc = &arcData;
 unsigned char *fil = arc->fil;
 arc->lastFil = fil;
#if ISR_DEBUG
// printf("[%02x%02x", ((unsigned int) fil) & 0xff, cmd);
#endif
 *fil++ = cmd;
 if (fil >= arc->arcBufEnd)
  fil = arc->arcBuf;
 int len = 1;
 if (rpt != 0)
 {
  *fil++ = rpt;
  if (fil >= arc->arcBufEnd)
   fil = arc->arcBuf;
  len += 1;
#if ISR_DEBUG
//  printf("%02x]", rpt);
#endif
 }
#if ISR_DEBUG
// else
//  printf("]");
// arc->qCol += 1;
// if (arc->qCol >= 10)
// {
//  printf("\n");
//  arc->qCol = 0;
// }
#endif
 arc->fil = fil;
 __disable_irq();		/* disable interrupt */
 arc->qCount += len;
 __enable_irq();		/* enable interrupts */
}

#if defined(LATHE_CPP)

inline float xPos(int loc)
{
 return(((float) (loc - rVar.xHomeOffset)) / (float) xAxis.stepsInch);
}

inline float zPos(int loc)
{
 return(((float) (loc - rVar.zHomeOffset)) / (float) zAxis.stepsInch);
}

inline float xPosC(int loc)
{
 return((float) loc / (float) xAxis.stepsInch);
}

inline float zPosC(int loc)
{
 return((float) loc / (float) zAxis.stepsInch);
}

#else

inline float xPosC(int loc)
{
 return((float) loc / arcData.xStepsInch);
}

inline float zPosC(int loc)
{
 return((float) loc / arcData.zStepsInch);
}

#endif	/* LATHE_CPP */

void arcInit(float radius)
{
 P_ARC_DATA arc = &arcData;
 arc->count = 0;

#if defined(LATHE_CPP)

 arc->xStepsInch = xAxis.stepsInch;
 arc->zStepsInch = zAxis.stepsInch;

#if (ISR_DEBUG != 0)
 arc->qCol = 0;
 arc->sCol = 0;
#endif

#endif	/* LATHE_CPP */

 arc->qCount = 0;
 arc->emp = arc->arcBuf;
 arc->fil = arc->emp;
 arc->arcBufEnd = &arc->arcBuf[ARC_BUF_SIZE];

 arc->xRadius = lrintf(radius * (float) arc->xStepsInch);
 arc->xRadiusSqrd = arc->xRadius * arc->xRadius;
 arc->xStep45 = lrint(radius * sqrt(2) / 2 * arc->xStepsInch);

 arc->zRadius = arc->xRadius * arc->zStepsInch / arc->xStepsInch;
 arc->zRadiusSqrd = arc->zRadius * arc->zRadius;
 arc->zStep45 = lrint(radius * sqrt(2) / 2 * arc->zStepsInch);

#if TEST
 fprintf(f, "radius %6.3f xRadius %5d xRaidusSqrd %10d "
	 "zRadius %5d zRaidusSqrd %10d\n",
	 radius, arc->xRadius, arc->xRadiusSqrd,
	 arc->zRadius, arc->zRadiusSqrd);

 fprintf(f, "xSteps45 %d zSteps45 %d\n", arc->xStep45, arc->zStep45);
#endif	/* TEST */

#if defined(LATHE_CPP)
 printf("\narcInit\n");
 printf("radius %6.3f xRadius %5d xRadiusSqrd %10d\n"
	 "zRadius %5d zRadiusSqrd %10d\n",
	 radius, arc->xRadius, arc->xRadiusSqrd,
	 arc->zRadius, arc->zRadiusSqrd);

 printf("xSteps45 %d zSteps45 %d\n", arc->xStep45, arc->zStep45);

 printf("c (%7.4f, %7.4f) p0 (%7.4f, %7.4f) p1 (%7.4f %7.4f)\n",
	xPosC(rVar.arcXCenter), zPosC(rVar.arcZCenter),
	xPosC(rVar.arcXStart), zPosC(rVar.arcZStart),
	xPosC(rVar.arcXEnd), zPosC(rVar.arcZEnd));

 arc->center.x = rVar.arcXCenter;
 arc->center.z = rVar.arcZCenter;

 arc->p0.x = rVar.arcXStart - arc->center.x;
 arc->p0.z = rVar.arcZStart - arc->center.z;

 arc->p1.x = rVar.arcXEnd - arc->center.x;
 arc->p1.z = rVar.arcZEnd - arc->center.z;

 int xDelta = arc->p1.x - arc->p0.x;
 int zDelta = arc->p1.z - arc->p0.z;

 xMoveCtl.expLoc = rVar.xLoc + xDelta;
 zMoveCtl.expLoc = rVar.zLoc + zDelta;

 float x0 = xPosC(arc->p0.x);
 float z0 = zPosC(arc->p0.z);
 float x1 = xPosC(arc->p1.x);
 float z1 = zPosC(arc->p1.z);

 printf("p0 (%7.4f, %7.4f) p1 (%7.4f %7.4f)\n", x0, z0, x1, z1);
 printf("radius %7.4f p0 radius %7.4f p1 radius %7.4f\n",
	radius, sqrtf(x0 * x0 + z0 * z0), sqrtf(x1 * x1 + z1 * z1));

 printf("xLoc %7.4f zLoc %7.4f\n", xPos(rVar.xLoc), zPos(rVar.zLoc));

 printf("xDelta %7.4f zDelta %7.4f x expLoc %7.4f z expLoc %7.4f\n",
	xPosC(xDelta), zPosC(zDelta),
	xPos(xMoveCtl.expLoc), zPos(zMoveCtl.expLoc));

#endif	/* LATHE_CPP */

#if TEST
 float x0 = xPosC(arc->p0.x);
 float z0 = zPosC(arc->p0.z);
 float x1 = xPosC(arc->p1.x);
 float z1 = zPosC(arc->p1.z);

 fprintf(f, "p0 (%7.4f, %7.4f) p1 (%7.4f %7.4f)\n", x0, z0, x1, z1);
 fprintf(f, "p0 radius %7.4f p1 radius %7.4f\n",
	 sqrt(x0 * x0 + z0 * z0), sqrt(x1 * x1 + z1 * z1));
#endif	/* TEST */

 arc->octStart = octantStart(arc->p0.x, arc->p0.z);
 arc->octEnd = octantEnd(arc->p1.x, arc->p1.z);

 arc->cwDir = false;
 if (arc->octEnd == arc->octStart)
 {
  if (arc->p0.x < arc->p1.x)
   arc->cwDir = true;
 }
 else if (arc->octEnd > arc->octStart)
  arc->cwDir = true;

#if TEST
 fprintf(f, "p0 (%5d, %5d) o %d p1 (%5d %5d) o %d cwDir %d\n",
	 arc->p0.x, arc->p0.z, arc->octStart, arc->p1.x,
	 arc->p1.z, arc->octEnd, arc->cwDir);
 fflush(f);
#endif	/* TEST */

#if defined(LATHE_CPP)
 printf("p0 (%5d, %5d) o %d p1 (%5d %5d) o %d cwDir %d\n",
	arc->p0.x, arc->p0.z, arc->octStart, arc->p1.x,
	arc->p1.z, arc->octEnd, arc->cwDir);
#endif	/* LATHE_CPP */

 int octant = arc->octStart;

 switch (octant)
 {
 case 0:
 {
  int x = arc->p0.x;
  arc->p0.z = lrint((sqrt(arc->xRadiusSqrd - x * x) * arc->zStepsInch) /
		    arc->xStepsInch);
 }
 break;

 case 1:
 {
  int z = arc->p0.z;
  arc->p0.x = lrint((sqrt(arc->zRadiusSqrd - z * z) * arc->xStepsInch) /
		    arc->zStepsInch);
 }
 break;

 case 2:
 {
  int z = arc->p0.z;
  arc->p0.x = lrint(sqrt((arc->zRadiusSqrd - z * z) * arc->xStepsInch) /
		    arc->zStepsInch);
 }
 break;

 case 3:
 {
  int x = arc->p0.x;
  arc->p0.z = -lrint((sqrt(arc->xRadiusSqrd - x * x) * arc->zStepsInch) /
		     arc->xStepsInch);
 }
 break;

  default:
   break;
 }

 arc->lessThan45 = ((octant == 0) || (octant == 3));
 if (arc->lessThan45)
  arc->xNext = arc->p0.x;
 else
  arc->zNext = arc->p0.z;

 arc->xEnd = arc->p1.x;
 arc->zEnd = arc->p1.z;

 arc->endCheck = (arc->octStart == arc->octEnd);

 arc->inXDir = 1;
 int xLast = arc->p0.x;
 arc->x = xLast;
 arc->xLast = xLast;
 arc->cmdX = xLast;
 arc->xPos = xLast;

 arc->inZDir = -1;
 int zLast = arc->p0.z;
 arc->z = zLast;
 arc->zLast = zLast;
 arc->cmdZ = zLast;
 arc->zPos = zLast;

 arc->count = 0;
 arc->oneByte = 0;
 arc->steps = 0;
 arc->active = false;
 arc->done = false;
 memset((void *) arc->cmdCount, 0, sizeof(arc->cmdCount));

 arc->delta = INT_MAX;
 arc->lastMove = true;

 updOctant(octant);
}

#if defined(LATHE_CPP)

void arcStepSetup(int inCount, int outCount)
{
 if (DBG_P)
  printf("\narcStepSetup in %d out %d\n", inCount, outCount);
 
 P_ARC_DATA arc = &arcData;

 int dx = inCount;
 int dy = outCount;

 arc->incr1 = 2 * dy;
 arc->incr2 = arc->incr1 - 2 * dx;
 arc->initialD = arc->incr1 - dx;

 arc->d = arc->initialD;
}

void arcStepUpdate()
{
 arcData.stepX += 1;
 if (arcData.d < 0)
 {
  arcData.d += arcData.incr1;
 }
 else
 {
  arcData.stepY += 1;
  zPulse();
  arcData.d += arcData.incr2;

  arcStep();
 }
}

#endif	/* LATHE_CPP */

bool arcStep()
{
 dbgArcStepSet();
 P_ARC_DATA arc = &arcData;

 int cmd = arc->cmd;
 int rpt = arc->rpt;
 bool first = false;
 if (rpt == 0)
 {
  if (arc->qCount <= 0)
  {
   if (arc->done)
   {
    arc->active = false;
#if defined(LATHE_CPP)
    zIsr.active = 0;
    xIsr.active = 0;
    zTmrStop();
    xTmrStop();
#endif	/* LATHE_CPP */
   }
   dbgArcStepClr();
   return(false);
  }

  unsigned char *emp = arc->emp;
#if defined(LATHE_CPP) && (ISR_DEBUG != 0)
  putBufCharIsr('(');
  sndhexIsr((unsigned char *) &arc->emp, 1);
#endif
  cmd = *emp++;
  if (emp >= arc->arcBufEnd)
   emp = arc->arcBuf;
  int len = 1;
  
  int tmpCmd = cmd & PCMD_CMD_MASK;
  if (tmpCmd != PCMD_EXTEND)
  {
   rpt = cmd >> PCMD_RPT_SHIFT;
   cmd = tmpCmd;
#if defined(LATHE_CPP) && (ISR_DEBUG != 0)
   putBufCharIsr(cmd + '0');
#endif
  }
  else
  {
   cmd = (cmd >> PCMD_RPT_SHIFT) + PEXT_OFFSET;
   rpt = 0;
#if defined(LATHE_CPP) && (ISR_DEBUG != 0)
   putBufCharIsr(cmd + 'a' - PEXT_OFFSET);
#endif
  }
  arc->cmd = cmd;
  first = true;
  
  if (rpt == 0)
  {
   rpt = *emp++;
   len = 2;
   if (emp >= arc->arcBufEnd)
    emp = arc->arcBuf;
  }
#if defined(LATHE_CPP) && (ISR_DEBUG != 0)
  sndhexIsr((unsigned char *) &rpt, 1);
  putBufCharIsr(')');
  arc->sCol += 1;
  if (arc->sCol >= 10)
  {
   putBufStrIsr("\n\r");
   arc->sCol = 0;
  }
#endif
    
  arc->emp = emp;
  arc->qCount -= len;

#if defined(LATHE_CPP) && (ISR_DEBUG != 0)
  arc->rpt = rpt;
  if (arc->rpt < 0)
  {
   putBufStrIsr("0R<");
  }
#endif
 }

#if TEST
 if (cmd != PCMD_SET_DIR)
  saveStepHistory(arc->xPos, arc->zPos);
#endif	/* TEST */

 switch (cmd)
 {
 case PCMD_INCX_HLDZ_S1:	/* 0 */
  rpt -= 1;
  updXLoc(arc->xDir);
  arc->xPos += arc->xDir;
  if (rpt == 0)
  {
   updZLoc(arc->zDir);
   arc->zPos += arc->zDir;
  }
  break;

 case PCMD_INCX_HLDZ_SN:	/* 1 */
  rpt -= 1;
  updXLoc(arc->xDir);
  arc->xPos += arc->xDir;
  if (first == false)
  {
   updZLoc(arc->zDir);
   arc->zPos += arc->zDir;
  }
  break;

 case PCMD_HLDX_S1_INCZ:	/* 2 */
  rpt -= 1;
  updZLoc(arc->zDir);
  arc->zPos += arc->zDir;
  if (rpt == 0)
  {
   updXLoc(arc->xDir);
   arc->xPos += arc->xDir;
  }
  break;

 case PCMD_HLDX_SN_INCZ:	/* 3 */
  rpt -= 1;
  updZLoc(arc->zDir);
  arc->zPos += arc->zDir;
  if (first == false)
  {
   updXLoc(arc->xDir);
   arc->xPos += arc->xDir;
  }
  break;

 case PCMD_SET_DIR:		/* 7 */
  arc->xDir = (rpt & PCMD_X_NEG) == 0 ? 1 : -1;
  arc->zDir = (rpt & PCMD_Z_NEG) == 0 ? 1 : -1;
  arc->rpt = 0;
  dbgArcStepClr();
  return(true);
  // break;

 case PEXT_OFFSET + PEXT_INCX:	/* 0 */
  rpt -= 1;
  updXLoc(arc->xDir);
  arc->xPos += arc->xDir;
  break;

 case PEXT_OFFSET + PEXT_INCZ:	/* 1 */
  rpt -= 1;
  updZLoc(arc->zDir);
  arc->zPos += arc->zDir;
  break;

 case PEXT_OFFSET + PEXT_INCX_INCZ: /* 2 */
  rpt -= 1;
  updXLoc(arc->xDir);
  arc->xPos += arc->xDir;
  updZLoc(arc->zDir);
  arc->zPos += arc->zDir;
  break;
  
 case PEXT_OFFSET + PEXT_INCX2_INCZ: /* 3 */
  rpt -= 1;
  updZLoc(arc->zDir);
  arc->zPos += arc->zDir;
  if (rpt <= 1)
  {
   updXLoc(arc->xDir);
   arc->xPos += arc->xDir;
  }
  break;

  default:
   break;
 }

 arc->rpt = rpt;
#if defined(LATHE_CPP)
 if (arc->rpt < 0)
 {
  putBufStrIsr("1R<");
 }
#endif
 arc->steps += 1;
 dbgArcStepClr();
 return(true);
}

#if ARC_DEBUG
void arcTest(int xChange, int zChange, int cmd, int rpt)
{
 P_ARC_DATA arc = &arcData;
#if TEST
 while (arcStep() != false)
  ;
#endif	/* TEST */

 fprintf(f, "%5d x %5d z %5d ",
	 arc->count, arc->cmdX, arc->cmdZ);

 arc->cmdCount[cmd & PCMD_CMD_MASK] += 1;

#if TEST
 P_LOC h;
 h = &history[0];
 char err = ' ';
 if ((h->x != h->stepX) || (h->z != h->stepZ))
 {
  printf("error at %5d\n", arc->count);
  arc->xPos = arc->x;
  arc->zPos = arc->z;
  err = '*';
 }
 fprintf(f, "x %5d z %5d%c", h->stepX, h->stepZ, err);
#endif	/* TEST */

 char buf[16];
 fprintf(f, "delta %4d %4s xChg %3d zChg %3d rpt %3d cmd %d %2x\n",
	 arc->delta, fmtDelta(arc->lastDelta, buf, sizeof(buf)),
	 xChange, zChange, rpt, cmd & PCMD_CMD_MASK, cmd);
 fflush(f);

 int i;
 h = &history[1];
 for (i = 1; i < histCount; i++)
 {
  fprintf(f, "      x %5d z %5d", h->x, h->z);
#if TEST
  if (stepHistCount > i)
   fprintf(f, " x %5d z %5d", h->stepX, h->stepZ);
#endif
  fprintf(f, " delta %4d %4s",
	  h->delta, fmtDelta(h->lastDelta, buf, sizeof(buf)));
  fprintf(f, "\n");
  h += 1;
 }
 for (; i < stepHistCount; i++)
 {
  fprintf(f, "%21s x %5d z %5d\n", " ", h->stepX, h->stepZ);
  h += 1;
 }
 fflush(f);
 resetHistory();
}
#endif

#if defined(LATHE_CPP)
void arcPrint(int xChange, int zChange, int cmd, int rpt)
{
 P_ARC_DATA arc = &arcData;

 arc->cmdCount[cmd & PCMD_CMD_MASK] += 1;

 printf("%2x %3d %5d x %5d z %5d ",
	((unsigned int) arc->lastFil) & 0xff, arc->qCount, arc->count,
	arc->cmdX, arc->cmdZ);
 char buf[16];
 printf("delta %4d %4s xChg %3d zChg %3d rpt %3d cmd %d %2x\n",
	arc->delta, fmtDelta(arc->lastDelta, buf, sizeof(buf)),
	xChange, zChange, rpt, cmd & PCMD_CMD_MASK, cmd);
 flushBuf();
}
#endif	/* LATHE_CPP */

inline bool endCheck0(P_ARC_DATA arc)
{
 if (arc->endCheck)
 {
  if (arc->inXDir > 0)
  {
   if (arc->xNext > arc->xEnd)
   {
    arc->done = true;
    return(true);
   }
  }
  else
  {
   if (arc->xNext < arc->xEnd)
   {
    arc->done = true;
    return(true);
   }
  }
 }
 return(false);
}

inline bool endCheck1(P_ARC_DATA arc)
{
 if (arc->endCheck)
 {
  if (arc->inZDir < 0)
  {
   if (arc->zNext < arc->zEnd)
   {
    arc->done = true;
    return(true);
   }
  }
  else
  {
   if (arc->zNext > arc->zEnd)
   {
    arc->done = true;
    return(true);
   }
  }
 }
 return(false);
}

void makeCommand(int x, int z, int dbg)
{
 P_ARC_DATA arc = &arcData;
 int xChange = abs(x - arc->cmdX);
 int zChange = abs(z - arc->cmdZ);

 int cmd = PCMD_SPARE_1;
 int rpt = 0;
 bool extend = false;

 if (xChange != 0 and zChange == 0)
 {
  extend = true;
  rpt = xChange;
  cmd = PEXT_INCX;		/* ext 0 */
 }
 else if (xChange == 0 and zChange != 0)
 {
  extend = true;
  rpt = zChange;
  cmd = PEXT_INCZ;		/* ext 1 */
 }
 else if (xChange == zChange)
 {
  if (zChange == 0)
   return;
  extend = true;
  rpt = zChange;
  cmd = PEXT_INCX_INCZ;		/* ext 2 */
 }
 else if (zChange == 1)
 {
  rpt = xChange;
  cmd = PCMD_INCX_HLDZ_S1;	/* 0 */
 }
 else if (xChange == (zChange + 1))
 {
  rpt = xChange;
  cmd = PCMD_INCX_HLDZ_SN;	/* 1 */
 }
 else if (xChange == 1)
 {
  rpt = zChange;
  cmd = PCMD_HLDX_S1_INCZ;	/* 2 */
 }
 else if (zChange == (xChange + 1))
 {
  rpt = zChange;
  cmd = PCMD_HLDX_SN_INCZ;	/* 3 */
 }
 else if (xChange == 2)
 {
  extend = true;
  rpt = zChange;
  cmd = PEXT_INCX2_INCZ;	/* ext 3 */
 }
 else
 {
  printf("no command\n");
 }

#if ISR_DEBUG
 printf("[%02x", ((unsigned int) arc->fil) & 0xff);
#endif
 
 if (rpt == 0)
 {
  printf("repeat 0");
 }
  
 if (!extend)
 {
#if ISR_DEBUG
  printf("%c%02x]", cmd + '0', rpt);
#endif
  if (rpt < PCMD_RPT_SHORT)
  {
   cmd |= rpt << PCMD_RPT_SHIFT;
   rpt = 0;
   arc->oneByte += 1;
  }
 }
 else
 {
#if ISR_DEBUG
  printf("%c%02x]", cmd + 'a', rpt);
#endif
  cmd = PCMD_EXTEND | (cmd << PCMD_RPT_SHIFT);
 }
#if ISR_DEBUG
 arc->qCol += 1;
 if (arc->qCol >= 10)
 {
  printf("\n");
  arc->qCol = 0;
 }
#endif
 
 arcQue(cmd, rpt);

#if ARC_DEBUG
 arcTest(xChange, zChange, cmd, rpt);
#endif	/* ARC_DEBUG */

#if defined(LATHE_CPP)
 if (dbg)
  arcPrint(xChange, zChange, cmd, rpt);
#endif	/* LATHE_CPP */

 arc->count += 1;

 arc->cmdX = x;
 arc->cmdZ = z;
}

void arcUpdate(bool dbg)
{
 P_ARC_DATA arc = &arcData;
 while (true)
 {
  if (arc->qCount >= (ARC_BUF_SIZE - 2))
   break;
  dbgArcUpdSet();
  int x;
  int z;
  int delta;
  if (arc->lessThan45)
  {
   if (endCheck0(arc))
    break;
   arc->zLast = arc->z;
   x = arc->xNext;
   arc->x = x;
   z = lrint((sqrt(arc->xRadiusSqrd - x * x) * arc->zStepsInch) /
	     arc->xStepsInch);
   if (arc->octant > 1)
    z = -z;
   arc->z = z;
   arc->lastDelta = arc->delta;
   delta = z - arc->zLast;
   arc->xNext += arc->inXDir;
  }
  else
  {
   if (endCheck1(arc))
    break;
   arc->xLast = arc->x;
   z = arc->zNext;
   arc->z = z;
   if (z == 0)
    x = arc->xRadius;
   else
    x = lrint((sqrt(arc->zRadiusSqrd - z * z) * arc->xStepsInch) /
	      arc->zStepsInch);
   arc->x = x;
   arc->lastDelta = arc->delta;
   delta = x - arc->xLast;
   arc->zNext += arc->inZDir;
  }
  arc->delta = delta;

  if (false)
  {
   char buf[16];
   printf("x %5d z %5d delta %5d lastDelta %5s\n",
	  arc->x, arc->z, delta, fmtDelta(arc->lastDelta, buf, sizeof(buf)));
#if defined(LATHE_CPP)
   flushBuf();
#else
   fflush(stdout);
#endif
  }

#if 0
  if (arc->octant == 1)
  {
   if (arc->zNext >= arc->zStep45)
   {
    arc->octant -= 1;
    arc->zLast = arc->z;
    arc->xNext = arc->x + arc->inXDir;
    updOctant(arc->octant);
   }
  }
  return;
#endif

  if ((arc->lastDelta != INT_MAX) && (delta != arc->lastDelta))
  {
   makeCommand(x, z, dbg);

   arc->delta = INT_MAX;
   int octant = arc->octant;
   if (arc->cwDir)		/* cw direction */
   {
    switch (octant)
    {
    case 0:
     if (arc->xNext > arc->xStep45)
     {
      octant += 1;
      updOctant(octant);
      arc->xLast = arc->x;
      arc->zNext = arc->z + arc->inZDir;
#if ARC_DEBUG
      fprintf(f, "xLast %5d zNext %5d\n", arc->xLast, arc->zNext);
#endif
     }
     break;

    case 1:
     if (arc->zNext <= 0)
     {
      octant += 1;
      updOctant(octant);
     }
     break;

    case 2:
     if (abs(arc->zNext) >= arc->zStep45)
     {
      octant += 1;
      updOctant(octant);
      arc->zLast = arc->z;
      arc->xNext = arc->x + arc->inXDir;
#if ARC_DEBUG
      fprintf(f, "zLast %5d xNext %5d\n", arc->zLast, arc->xNext);
#endif
     }
     break;

     default:
      break;
    } /* switch */
   } /* cwDir */
   else				/* ccw dir */
   {
    switch (octant)
    {
    case 0:
     break;

    case 1:
     if (arc->zNext >= arc->zStep45)
     {
      octant -= 1;
      updOctant(octant);
      arc->zLast = arc->z;
      arc->xNext = arc->x + arc->inXDir;
#if ARC_DEBUG
      fprintf(f, "zLast %5d xNext %5d\n", arc->zLast, arc->xNext);
#endif
     }
     break;

    case 2:
     if (arc->zNext > 0)
     {
      octant -= 1;
      updOctant(octant);
     }
     break;

    case 3:
     if (arc->xNext >= arc->xStep45)
     {
      octant -= 1;
      updOctant(octant);
      arc->xLast = arc->x;
      arc->zNext = arc->z + arc->inZDir;
#if ARC_DEBUG
       fprintf(f, "xLast %5d zNext %5d\n", arc->xLast, arc->zNext);
#endif
     }
     break;

     default:
      break;
     
    }
   } /* switch */
  } /* else cwDir */

#if ARC_DEBUG
  saveHistory(x, z, arc->delta, arc->lastDelta);
#endif
 }

 if (arc->done && arc->lastMove)
 {
  arc->lastMove = false;
  makeCommand(arc->x, arc->z, UPDATE_DEBUG);
 }
 
 dbgArcUpdClr();
}

#if !defined(LATHE_CPP)

float radians(float a)
{
 return((float) (a * M_PI / 180.0));
}

P_POINT polarToRect(P_POINT center, float radius, float a, P_POINT p)
{
 float a0 = radians(a);
 p->x = lrint(center->x + radius * sin(a0) * arcData.xStepsInch);
 p->z = lrint(center->z + radius * cos(a0) * arcData.zStepsInch);
 return(p);
}

int main(int argc, char *argv[])
{
 float radius;
 P_ARC_DATA arc = &arcData;
#if defined(__GNUC__)
 f = fopen("dbg.lst", "w");
 if (f == NULL)
 {
  printf("unable to open file\n");
  return(-1);
 }
#else
 errno_t err = fopen_s(&f, "dbg.lst", "w");
 if (err != 0)
 {
  printf("unable to open file\n");
  return(-1);
 }
#endif	/* __GNUC__ */

#if 0

 float a0;
 float a1;
 if (argc >= 3)
 {
  a0 = (float) atof(argv[1]);
  a1 = (float) atof(argv[2]);
 }
 else
 {
  a0 = 0;
  a1 = 90;
 }

 radius = .125;
 arc->radius = radius;

 arc->xStepsInch = lrint((200 * 10 * 25.4) / 4);
 arc->zStepsInch = lrint((200 * 10 * 25.4) / 5);

 fprintf(f, "xStepsInch %5d zStepsInch %5d\n",
	 arc->xStepsInch, arc->zStepsInch);

 T_POINT c = {0, 0};
 polarToRect(&c, radius, a0, &arc->p0);
 polarToRect(&c, radius, a1, &arc->p1);

#else  /* 0 */

 /*
   radius  0.539 xRadius  6847 xRaidusSqrd   46881409
   zRadius  5477 zRaidusSqrd   29997529
   xSteps45 4841 zSteps45 3873
   p0 ( 6066,  2540) o 1 p1 ( 6350  2047)
 */

 radius = (float) 0.479;

 arc->xStepsInch = lrint((200 * 10 * 25.4) / 4);
 arc->zStepsInch = lrint((200 * 10 * 25.4) / 5);

 fprintf(f, "xStepsInch %5d zStepsInch %5d\n",
	 arc->xStepsInch, arc->zStepsInch);

 arc->p0.x = 6018;
 arc->p0.z = 3810;

 arc->p1.x = 7674;
 arc->p1.z = 0;

 #endif	 /* 0 */

 resetHistory();
 arcInit(radius);

#if 0
 char buf0[16];
 char buf1[16];
 printf("x %5d z %5d delta %5s lastDelta %5s\n",
	arc->x, arc->z, fmtDelta(arc->delta, buf0, sizeof(buf0)),
	fmtDelta(arc->lastDelta, buf1, sizeof(buf1)));
#endif

 while (!arc->done)
 {
  arcUpdate(false);
#if TEST
  arcStep();
#endif	/* TEST */
 }
 fprintf(f, "%5d x %5d z %5d\n",
	 arc->count, arc->cmdX, arc->cmdZ);
 for (int i = 0; i < (int) (sizeof(arc->cmdCount) / sizeof(int)); i ++)
 {
  int val = arc->cmdCount[i];
  if (val != 0)
   fprintf(f, "%d %4d\n", i, val);
 }
 fprintf(f, "commands %d bytes %d steps %d oneByte %d\n",
	arc->count, 2 * (arc->count - arc->oneByte) + arc->oneByte,
	arc->steps, arc->oneByte);
 fclose(f);
}

#endif	/* LATHE_CPP */

#endif	/* __ARC__ */
