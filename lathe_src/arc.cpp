#define __ARC__
#if defined(STM32F4)
#include "stm32f4xx_hal.h"
#endif	/* STM32F4 */

#define _USE_MATH_DEFINES

#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#if defined(STM32F4)

#define EXT extern
#include "config.h"
#include "lathe.h"
#include "arc.h"
#include "ctlbits.h"
#include "remstruct.h"
#include "timers.h"
#include "serialio.h"

inline void updXLoc(int dir)
{
 rVar.xLoc += dir;
 xPulseTrig();
}

inline void updZLoc(int dir)
{
 rVar.zLoc += dir;
 zPulseTrig();
}

#define ARC_DEBUG 0
#define TEST 0

#else

#include "../LatheCPP/include/ctlbits.h"

#define __ARC_INC__
#define EXT
#define __disable_irq()
#define __enable_irq()

inline void updXLoc(int dir) {}
inline void updZLoc(int dir) {}
inline void xTmrPWMENA() {}
inline void xTmrPWMDis() {}

#define ARC_DEBUG 1
#define TEST 1
#if ARC_DEBUG
FILE *f;
#endif

#endif	/* STM32F4 */

#if defined(__ARC_INC__)		// <-

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

 int zRadius;			/* z raidus in steps */
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

 /* data used by isr for generating arc */

 int qCount;			/* bytes in queue */
 unsigned char *emp;		/* queue empty pointer */
 unsigned char *fil;		/* queue fill pointer */
 unsigned char *arcBufEnd;	/* buffer end address */
 unsigned char arcBuf[ARC_BUF_SIZE]; /* arc data buffer */

 int cmd;			/* command being processed */
 int rpt;			/* repeat value for active command */

 int xDir;			/* x direction for isr */
 int xPos;			/* x position for isr */

 int zDir;			/* z direction for isr */
 int zPos;			/* z position for isr */
} T_ARC_DATA, *P_ARC_DATA;

EXT T_ARC_DATA arcData;

void arcInit(float radius);
void arcUpdate();
bool arcStep(void);
void arcQue(unsigned char cmd, unsigned char rpt);
int octantStart(int x, int z);
int octantEnd(int x, int z);

#endif	// ->
#if defined(__ARC__)

#if defined(STM32F4)
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
#endif

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
  if (z > 0)
   return((x < arcData.xStep45) ? 0 : 1);
   else
    return((x <= arcData.xStep45) ? ((x == 0) ? 4 : 3) : 2);
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
  if (z > 0)
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
 arc->cwDir = false;
 if (arc->octEnd == arc->octStart)
 {
  if (arc->p0.x < arc->p1.x)
   arc->cwDir = true;
 }
 else if (arc->octEnd > arc->octStart)
  arc->cwDir = true;
 
 int cmd;
 if (arc->cwDir)
 {
  cmd = cwOctDir[octant];
  P_OCT_INC inc = &cwOctInc[octant];
  arc->inXDir = inc->xInc;
  arc->inZDir = inc->zInc;
 }
 else
 {
  cmd = ccwOctDir[octant];
  P_OCT_INC inc = &ccwOctInc[octant];
  arc->inXDir = inc->xInc;
  arc->inZDir = inc->zInc;
 }
 cmd = (PCMD_SET_DIR | ((PCMD_DIR_FLAG | cmd) << PCMD_RPT_SHIFT));
 arcQue(cmd, 0);

#if TEST
 fprintf(f, "\noctant %d inxDir %d inZDir %d cmd %2x\n",
	 octant, arc->inXDir, arc->inZDir, cmd);
#endif

#if defined(STM32F4)
 printf("\noctant %d inxDir %d inZDir %d cmd %2x\n",
	 octant, arc->inXDir, arc->inZDir, cmd);
#endif /* STM32F4 */
}

void arcQue(unsigned char cmd, unsigned char rpt)
{
 P_ARC_DATA arc = &arcData;
 unsigned char *fil = arc->fil;
 *fil++ = cmd;
 if (fil >= arc->arcBufEnd)
  fil = arc->arcBuf;
 int len = 1;
 if ((cmd & PCMD_RPT_MASK) == 0)
 {
  *fil++ = rpt;
  if (fil >= arc->arcBufEnd)
   fil = arc->arcBuf;
  len += 1;
 }
 arc->fil = fil;
 __disable_irq();		/* disable interrupt */
 arc->qCount += len;
 __enable_irq();		/* enable interrupts */
}

void arcInit(float radius)
{
 P_ARC_DATA arc = &arcData;
 arc->count = 0;

#if defined(STM32F4)
 arc->xStepsInch = xAxis.stepsInch;
 arc->zStepsInch = zAxis.stepsInch;

 arc->center.x = rVar.arcXCenter;
 arc->center.z = rVar.arcZCenter;

 arc->p0.x = rVar.arcXStart - arc->center.x;
 arc->p0.z = rVar.arcZStart - arc->center.z;

 arc->p1.x = rVar.arcXEnd - arc->center.x;
 arc->p1.z = rVar.arcZEnd - arc->center.z;
  
#endif	/* STM32F4 */

 arc->qCount = 0;
 arc->emp = arc->arcBuf;
 arc->fil = arc->emp;
 arc->arcBufEnd = &arc->arcBuf[ARC_BUF_SIZE];

 arc->xRadius = lrint(radius * arc->xStepsInch);
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
#endif
#if defined(STM32F4) 
 printf("radius %6.3f xRadius %5d xRaidusSqrd %10d\n"
	 "zRadius %5d zRaidusSqrd %10d\n",
	 radius, arc->xRadius, arc->xRadiusSqrd,
	 arc->zRadius, arc->zRadiusSqrd);

 printf("xSteps45 %d zSteps45 %d\n", arc->xStep45, arc->zStep45);
#endif	/* STM32F4 */

 arc->octStart = octantStart(arc->p0.x, arc->p0.z);
 arc->octEnd = octantEnd(arc->p1.x, arc->p1.z);

#if TEST
 fprintf(f, "p0 (%5d, %5d) o %d p1 (%5d %5d) o %d\n",
	 arc->p0.x, arc->p0.z, arc->octStart, arc->p1.x,
	 arc->p1.z, arc->octEnd);
#endif

#if defined(STM32F4) 
 printf("p0 (%5d, %5d) o %d p1 (%5d %5d) o %d\n",
	 arc->p0.x, arc->p0.z, arc->octStart, arc->p1.x,
	 arc->p1.z, arc->octEnd);
#endif	/* STM32F4 */

 int octant = arc->octStart;

 switch (octant)
 {
 case 0:
 {
  int x = arc->p0.x;
  arc->p0.z = ((lrint(sqrt(arc->xRadiusSqrd - x * x)) * arc->zStepsInch) /
	       arc->xStepsInch);
 }
 break;

 case 1:
 {
  int z = arc->p0.z;
   arc->p0.x = ((lrint(sqrt(arc->zRadiusSqrd - z * z)) * arc->xStepsInch) /
		arc->zStepsInch);
 }
 break;

 case 2:
 {
  int z = arc->p0.z;
   arc->p0.x = ((lrint(sqrt(arc->zRadiusSqrd - z * z)) * arc->xStepsInch) /
		arc->zStepsInch);
 }
 break;

 case 3:
 {
  int x = arc->p0.x;
  arc->p0.z = -((lrint(sqrt(arc->xRadiusSqrd - x * x)) * arc->zStepsInch) /
		arc->xStepsInch);
 }
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

 updOctant(octant);
 }

bool arcStep(void)
{
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
#if defined(STM32F4)
    zIsr.active = 0;
    xIsr.active = 0;
    zTmrStop();
    xTmrStop();
#endif	/* STM32F4 */
   }
   return(false);
  }

  unsigned char *emp = arc->emp;
  cmd = *emp++;
  if (emp >= arc->arcBufEnd)
   emp = arc->arcBuf;
  int len = 1;
  if ((cmd & PCMD_RPT_MASK) != 0)
  {
   rpt = cmd >> PCMD_RPT_SHIFT;
  }
  else
  {
   rpt = *emp++;
   len += 1;
   if (emp >= arc->arcBufEnd)
    emp = arc->arcBuf;
  }
  arc->emp = emp;
  arc->qCount -= len;
  cmd &= PCMD_CMD_MASK;
  arc->cmd = cmd;
  first = true;
 }

#if TEST
 if (cmd <= PCMD_INCX2_INCZ)
  saveStepHistory(arc->xPos, arc->zPos);
#endif

 switch (cmd)
 {
 case PCMD_INCX_HLDZ_S1:	/* 0 */
  rpt -= 1;
  updXLoc(arc->xDir);
  arc->xPos += arc->xDir;
  if (rpt == 0)
  {
   updZLoc(arc->xDir);
   arc->zPos += arc->zDir;
  }
  break;
  
 case PCMD_INCX_HLDZ_SN:	/* 1 */
  rpt -= 1;
  updXLoc(arc->xDir);
  arc->xPos += arc->xDir;
  if (first == false)
  {
   updZLoc(arc->xDir);
   arc->zPos += arc->zDir;
  }
  break;
  
 case PCMD_HLDX_S1_INCZ:	/* 2 */
  rpt -= 1;
  updZLoc(arc->xDir);
  arc->zPos += arc->zDir;
  if (rpt == 0)
  {
   updXLoc(arc->xDir);
   arc->xPos += arc->xDir;
  }
  else
   xTmrPWMDis();
  break;
  
 case PCMD_HLDX_SN_INCZ:	/* 3 */
  rpt -= 1;
  updZLoc(arc->xDir);
  arc->zPos += arc->zDir;
  if (first == false)
  {
   updXLoc(arc->xDir);
   arc->xPos += arc->xDir;
  }
  else
   xTmrPWMDis();
  break;

 case PCMD_INCX2_INCZ:		/* 4 */
  rpt -= 1;
  updZLoc(arc->xDir);
  arc->zPos += arc->zDir;
  if (rpt <= 1)
  {
   updXLoc(arc->xDir);
   arc->xPos += arc->xDir;
  }
  else
   xTmrPWMDis();
  break;

 case PCMD_SET_DIR:		/* 7 */
  arc->xDir = (rpt & PCMD_X_NEG) == 0 ? 1 : -1;
  arc->zDir = (rpt & PCMD_Z_NEG) == 0 ? 1 : -1;
  arc->rpt = 0;
  return(true);
  break;
 }
 arc->rpt = rpt;
 arc->steps += 1;
 return(true);
}

#if ARC_DEBUG
void arcTest(int xChange, int zChange, int cmd, int rpt)
{ 
 P_ARC_DATA arc = &arcData;
#if TEST
 while (arcStep() != false)
  ;
#endif

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
#endif

 char buf[8];
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

#if defined(STM32F4)
void arcPrint(int xChange, int zChange, int cmd, int rpt)
{ 
 P_ARC_DATA arc = &arcData;

 arc->cmdCount[cmd & PCMD_CMD_MASK] += 1;

 printf("%3d %5d x %5d z %5d ",
	arc->qCount, arc->count, arc->cmdX, arc->cmdZ);
 char buf[8];
 printf("delta %4d %4s xChg %3d zChg %3d rpt %3d cmd %d %2x\n",
	arc->delta, fmtDelta(arc->lastDelta, buf, sizeof(buf)),
	xChange, zChange, rpt, cmd & PCMD_CMD_MASK, cmd);
 flushBuf();
}
#endif	/* STM32F4 */

void arcUpdate()
{
#if defined(STM32F4)
 flushBuf();
#endif	/* STM32F4 */
 P_ARC_DATA arc = &arcData;
 while (true)
 {
  if (arc->qCount >= (ARC_BUF_SIZE - 2))
   break;
  int x;
  int z;
  int delta;
  if (arc->lessThan45)
  {
   if (arc->endCheck)
   {
    if (arc->inXDir > 0)
    {
     if (arc->xNext > arc->xEnd)
     {
      arc->done = true;
      break;
     }
    }
    else
    {
     if (arc->xNext < arc->xEnd)
     {
      arc->done = true;
      break;
     }
    }
   }
   arc->zLast = arc->z;
   x = arc->xNext;
   arc->x = x;
   z = ((lrint(sqrt(arc->xRadiusSqrd - x * x)) * arc->zStepsInch) /
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
   if (arc->endCheck)
   {
    if (arc->inZDir < 0)
    {
     if (arc->zNext < arc->zEnd)
     {
      arc->done = true;
      break;
     }
    }
    else
    {
     if (arc->zNext > arc->zEnd)
     {
      arc->done = true;
      break;
     }
    }
   }
   arc->xLast = arc->x;
   z = arc->zNext;
   arc->z = z;
   if (z == 0)
    x = arc->xRadius;
   else
    x = ((lrint(sqrt(arc->zRadiusSqrd - z * z)) * arc->xStepsInch) /
	 arc->zStepsInch);
   arc->x = x;
   arc->lastDelta = arc->delta;
   delta = x - arc->xLast;
   arc->zNext += arc->inZDir;
  }
  arc->delta = delta;

  if ((arc->lastDelta != INT_MAX) && (delta != arc->lastDelta))
  {
   int xChange = abs(x - arc->cmdX);
   int zChange = abs(z - arc->cmdZ);

   int cmd = PCMD_SPARE_1;
   int rpt = 0;

   if (zChange == 1)
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
    rpt = zChange;
    cmd = PCMD_INCX2_INCZ;	/* 4 */
   }

   if (rpt < PCMD_RPT_SHORT)
   {
    cmd |= rpt << PCMD_RPT_SHIFT;
    arc->oneByte += 1;
   }

   arcQue(cmd, rpt);

#if ARC_DEBUG
   arcTest(xChange, zChange, cmd, rpt);
#endif
#if defined(STM32F4)
//   arcPrint(xChange, zChange, cmd, rpt);
#endif	/* STM32F4 */
 
   arc->count += 1;

   arc->cmdX = x;
   arc->cmdZ = z;
   arc->delta = INT_MAX;
   int octant = arc->octant;
   if (arc->cwDir)
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
    }
   }
   else
   {
   }
  }
#if ARC_DEBUG
  saveHistory(x, z, arc->delta, arc->lastDelta);
#endif
 }
}

#if !defined(STM32F4)

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
 errno_t err = fopen_s(&f, "dbg.lst", "w");
 if (err != 0)
 {
  printf("unable to open file\n");
  return(-1);
 }

#if 0

 float a0;
 float a1;
 if (argc >= 3)
 {
  a0 = atof(argv[1]);
  a1 = atof(argv[2]);
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

#else

 /*
   radius  0.539 xRadius  6847 xRaidusSqrd   46881409
   zRadius  5477 zRaidusSqrd   29997529
   xSteps45 4841 zSteps45 3873
   p0 ( 6066,  2540) o 1 p1 ( 6350  2047)
 */

 radius = (float) 0.539;

 arc->xStepsInch = lrint((200 * 10 * 25.4) / 4);
 arc->zStepsInch = lrint((200 * 10 * 25.4) / 5);

 fprintf(f, "xStepsInch %5d zStepsInch %5d\n",
	 arc->xStepsInch, arc->zStepsInch);

 arc->p0.x = 6066;
 arc->p0.z = 2540;
 
 arc->p1.x = 6350;
 arc->p1.z = 2047;

 #endif

 resetHistory();
 arcInit(radius);
 
 while (!arc->done)
 {
  arcUpdate();
#if TEST
  arcStep();
#endif
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

#endif	/* STM32F4 */

#endif	/* __ARC__ */
