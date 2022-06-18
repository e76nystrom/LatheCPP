#if 1	// <-

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
} T_ARC_DATA, *P_ARC_DATA;

EXT T_ARC_DATA arcData;

void arcInit(float radius);
void arcUpdate(bool dbg);
bool arcStep(void);
void arcQue(unsigned char cmd, unsigned char rpt);
int octantStart(int x, int z);
int octantEnd(int x, int z);
void makeCommand(int x, int z, int dbg);

#endif	// ->
