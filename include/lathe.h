#if !defined(LATHE_INC)	// <-
#define LATHE_INC

#include <cstdio>
#include <cstring>
#include <cmath>
#include <climits>
#include <cstdint>
#include <cstdarg>

#include "config.h"
#include "remvar.h"
#include "syncCmdList.h"

#if !defined(EXT)
#define EXT extern
#endif

#define CYCLE_CTR
#if defined(CYCLE_CTR)

#define CPU_CYCLES 1
#define DWT_CTRL_CycCntEna DWT_CTRL_CYCCNTENA_Msk
inline void resetCnt()
{
 DWT->CTRL &= ~DWT_CTRL_CycCntEna; // disable the counter
 DWT->CYCCNT = 0;		// reset the counter
}

inline void startCnt()
{
 DWT->CTRL |= DWT_CTRL_CycCntEna; // enable the counter
}

inline void stopCnt()
{
 DWT->CTRL &= ~DWT_CTRL_CycCntEna; // disable the counter
}

inline unsigned int getCycles()
{
 return DWT->CYCCNT;
}

#else  /* CYCLE_CTR */

#define CPU_CYCLES 0
inline void resetCnt() {}
inline void startCnt() {}
inline void stopCnt() {}
inline unsigned int getCycles() {return(0);}

#endif	/* CYCLE_CTR */

#define DBG_CMP 1		/* debug capture timer */
#define DBG_CMP_TIME 1		/* debug capture interrupt timing */
#define DBG_INT 1		/* debug internal timer */
#define DBG_SYNC_COUNT 1        /* debug count input and output pulses */

typedef uint8_t boolean;

#define XDEV 0

typedef struct s_spindle
{
 const char *label;		/* spindle label */
 /* spindle parameters */
 int microSteps;		/* micro steps */
 int motorSteps;		/* motor steps per revolution */

 /* spindle motion parameters */
 float minRPM;			/* minimum rpm */
 float maxRPM;			/* maximum rpm */
 float aTime;			/* acceleration time */
 float accel;			/* spindle acceleration */
 int dirFwd;			/* forward bit */
 int dirRev;			/* reverse bit */

 /* calculated values */

 unsigned int clocksRev;	/* clocks per revolution */
 float stepsSec;		/* steps per second */
 float stepsSec2;		/* accel steps per second sqrd */
 float time;			/* actual acceleration time */
 unsigned int steps;		/* acceleration steps */
 unsigned int clocks;		/* acceleration clocks */
 float revs;			/* acceleration revolutions */
 int64_t clocksCycle;		/* clocks per cycle */

 /* control variables for isr */
 float cFactor;			/* factor for computing acceleration */
 unsigned int clocksStep;	/* fcy clocks per step */
 unsigned int initialStep;	/* accel steps to minimum speed */
 unsigned int finalStep;	/* accel steps to maximum speed */
 unsigned int stepsRev;		/* steps per revolution */
 unsigned int stepsCycle;	/* steps per cycle */
 unsigned int zStart;		/* z start position */
 unsigned int xStart;		/* x start position */
} T_SPINDLE, *P_SPINDLE;

#define STARTZ      (1 << 0)
#define STARTX      (1 << 1)
#define START_TRIG  (1 << 2)
#define START_ENA   (1 << 3)

typedef struct s_spindleIsr
{
 /* flags */
 char active;			/* spindle active */
 char accel;			/* acceleration flag */
 char decel;			/* deceleration flag */
 char sync;			/* running synchronized */
 char startAxis;		/* start z flag */
 char initSync;			/* sync with index pulse */
 char findSync;			/* search for sync pulse */
 char lastIndex;		/* last value of sync input */

 /* control variables */
 float cFactor;			/* acceleration constant */
 uint64_t cFactor2;		/* squared cfactor */
 unsigned clocksStep;		/* final clocks per step value */
 unsigned int initialStep;	/* minimum acceleration step */
 unsigned int finalStep;	/* maximum acceleration step */
 unsigned int stepsRev;		/* steps per revolution */
 unsigned int stepsCycle;	/* steps in a cycle */
 unsigned int zStart;		/* z start position */
 unsigned int xStart;		/* x start position */

 /* jog variables */
 int iniDist;			/* initial jog distance */
 unsigned int maxDist;		/* maximum jog distance */
 int jogInc;			/* jog increment */

 /* working variables */
 unsigned int spStep;		/* spindle step counter */
 unsigned int intCount;		/* spindle interrupt count */
 unsigned int pos;		/* position in revolution */
 unsigned int rev;		/* revolutions */
 unsigned int dist;		/* distance to run */
 unsigned int accelStep;	/* current acceleration step */
 unsigned int lastCount;	/* last counter value */
 unsigned int curCount;		/* current count value */
 unsigned int cycleCounter;	/* cycle step counter */
} T_SPINDLEISR, *P_SPINDLEISR;

typedef struct s_axis
{
 char axis;			/* axis */
 float pitch;			/* axis leadscrew pitch */
 float ratio;			/* motor leadscrew ratio */
 int microSteps;		/* micro steps */
 int motorSteps;		/* motor steps */
 float accel;			/* acceleration */
 float backlash;		/* backlash */
 int stepsInch;			/* axis steps per inch */
 int droCountsInch;		/* dro count inch */
 int stepFactor;		/* factored steps per inch */
 int droFactor;			/* factored dro counts per inch */
 int backlashSteps;		/* backlash steps */
 int dirFwd;			/* mask for forward */
 int dirRev;			/* mask for reverse */
} T_AXIS, *P_AXIS;

typedef struct s_accel
{
 /* initial parameters */
 const char *label;		/* accel type label */
 float minSpeed;		/* minimum speed */
 float maxSpeed;		/* maximum speed */
 float aTime;			/* accelerationtime */
 float accel;			/* acceleration units/sec^2 */
 float pitch;			/* pitch for threading or feed */
 int stepsInch;			/* axis steps per inch */
 int droCountsInch;		/* dro counts per inch */
 int *droPos;			/* pointer to current dro position */
 char taper;			/* set up for tapering second */
 float taperInch;		/* taper per inch */
 union
 {
  struct			/* processor control */
  {
   /* calculated values */
   int stepsSec;		/* steps per second */
   float stepsSec2;		/* acceleration in steps per sec^2 */
   float time;			/* acceleration time */
   unsigned int steps;		/* acceleration steps */
   int droTarget;		/* target for dro position */
   unsigned int clocks;		/* acceleration clocks */
   float dist;			/* acceleration distance */

   int remainder;		/* remainder of spindle cyc div z cyc */
   int initialCount;		/* clocks to first accel step */
   int finalCount;		/* clocks to last accel step */
   int totAccelClocks;		/* accel clocks final minus initial */
   unsigned int accelSpSteps;	/* spindle steps during accel */
   unsigned int accelSpRem;	/* spindle steps remainder */

   /* control variables for isr */

   float cFactor;		/* factor to get clocks to next step */
   unsigned int clocksStep;	/* clocks per step after accel */
   unsigned int initialStep;	/* initial accel step number */
   unsigned int finalStep;	/* final accel step number */
   int d;			/* sum initial value */
   int incr1;			/* incr 1 value */
   int incr2;			/* incr 2 value */
   int delta;
   int stepsCycle;		/* steps in a cycle */
   char useDro;			/* use dro for move */
  };
  struct			/* xilinx control */
  {
   float minFeed;		/* minimum feed rate */
   float maxFeed;		/* maximum feed rate */

   /* calculated values */
   int clockFreq;
   int clocksPerInch;
   float accelTime;
   int accelSteps;

   /* values for jog */
   int stepsX;
   int stepsSecX;
   int timeX;

   /* intermediate value for hardware setup */
   int scale;
   int dx;
   int dyIni;
   int dyMax;
   int intIncPerClock;

   /* values for hardware setup */
   int sum;			/* sum initial value */
   int incr1X;			/* incr 1 value */
   int incr2X;			/* incr 2 value */
   int intAccel;		/* acceleration adder */
   int accelClocks;		/* acceleration clocks */
   int freqDivider;		/* frequency divider for move */
  };
 };
} T_ACCEL, *P_ACCEL;

typedef struct s_zxisr
{
 /* flags */
 char sync;			/* synchronized */
 char accel;			/* accelerating */
 char decel;			/* decelerating */
 char taper;			/* taper enabled */
 char done;			/* movement done */
 char home;			/* homing stop on home signal */
 char doneHome;			/* stopped for home signal */
 char axis;			/* axis name */
 char encoderDirect;		/* use encoder directly */
 char useDro;			/* use dro for move */
 char errFlag;
 char dbgPos;

 int dir;			/* axis direction */
 int syncInit;			/* initialized for sync operation */
 int syncStart;			/* waiting for start */
 int active;			/* axis active */

 /* control variables */
 float cFactor;			/* acceleration factor */
 unsigned int clocksStep;	/* final clocks per step */
 unsigned int initialStep;	/* initial accel step number */
 unsigned int finalStep;	/* final accel step number */
 unsigned int counterStep1;	/* counter value for incr1 */
 unsigned int counterStep2;	/* counter value for incr2 */
 int d;				/* sum initial value */
 int incr1;			/* incr 1 value */
 int incr2;			/* incr 2 value */
 int delta;			/* update on direction change */
 int stepsCycle;		/* steps in a cycle */
 unsigned int accelSpSteps;    /* spindle steps during acceleration */
 unsigned int finalCtr;			/* final counter value */

 /* working variables */
 int pos;			/* position */
 unsigned int dist;		/* distance to move */
 int droTarget;			/* dro target value */
 unsigned int accelStep;	/* current step in accel */
 unsigned int lastCount;	/* last count value */
 unsigned int curCount;		/* current count value */
 int sum;			/* sum for distributing remainder */
 int lastRemCount;		/* last remainder count */
 int remCount;			/* remainder count */
 int cycleCounter;		/* step cycle counter */
 unsigned int clockSum;
 unsigned int startRev;		/* start revolution */
 unsigned int startPos;		/* start position */
 unsigned int stopRev;		/* stop revolution */
 unsigned int stopPos;		/* stop position */

 unsigned int steps;		/* steps moved */

 int curDir;			/* current direction */
 int x;				/* input pulses */
 int y;				/* output steps */
} T_ZXISR, *P_ZXISR;

#define TAPER_CTL 1		/* axis is controlling taper */
#define TAPER_SLAVE 2		/* axis is tapering */
#define TAPER_RUNOUT 4		/* taper is for runout */

EXT T_SPINDLE spA;		/* spindle acceleration parameters */
EXT T_SPINDLE spJA;		/* spindle jog acceleration parameters */
EXT T_SPINDLE spJSA;		/* spindle jog speed accel parameters */
EXT T_SPINDLEISR sp;		/* spindle isr variables */

EXT T_AXIS zAxis;		/* z axis info */

EXT T_AXIS xAxis;		/* x axis info */

typedef struct s_runout
{
 boolean active;		/* runout active */
 boolean zFlag;			/* z axis runout flag */
 boolean xFlag;			/* x runout in progress */
 unsigned int zStart;		/* z runout start step */
 float zDist;			/* z runout distance */
 int zSteps;			/* z runout steps */
 int xSteps;			/* x runout steps */
} T_RUNOUT, *P_RUNOUT;

EXT T_RUNOUT runout;

EXT T_ACCEL zTA;		/* z threading accel */
EXT T_ACCEL zPA;		/* z taper accel */
EXT T_ACCEL zMA;		/* z move accel */
EXT T_ACCEL zJA;		/* z jog accel */
EXT T_ACCEL zJSA;		/* z jog speed accel */
EXT T_ACCEL zSA;		/* z slow jog accel */

EXT T_ZXISR zIsr;		/* z isr variables */

EXT T_ACCEL xTA;		/* x threading accel */
EXT T_ACCEL xPA;		/* x taper accel */
EXT T_ACCEL xRA;		/* x runout accel */
EXT T_ACCEL xMA;		/* x move aiccel */
EXT T_ACCEL xJA;		/* x jog accel */
EXT T_ACCEL xJSA;		/* x jog speed accel */
EXT T_ACCEL xSA;		/* x slow jog accel */

EXT T_ZXISR xIsr;		/* x isr variables */

enum eActive
{
 INACTIVE,
 Z_ACTIVE,			/* z axis active */
 X_ACTIVE,			/* x axis active */
};

typedef struct s_sync
{
 char spindle;
 char useEncoder;
 char encoderDirect;

 int zSyncInit;			/* z sync init */
 int xSyncInit;			/* x sync init */

// char active;			/* axis driven by spindle */
 char stepActive;		/* stepper active */
 char encActive;		/* encoder active */
 char intActive;		/* sync internal active */
 char extActive;		/* sync external active */
} T_SYN_CTL, *P_SYN_CTL;

EXT T_SYN_CTL syn;

EXT int trackSpeed;		/* external motor track speed */
EXT int updateFeed;		/* time to update feed */

EXT unsigned int tmrStepWidth;	/* step width */
EXT unsigned int  tmrMin;	/* timer minimum width */

EXT uint32_t spEncCount;	/* spindle encoder interrupt count */

EXT int16_t encState;		/* state of encoder */

#define ARRAY_LEN 2048		/* size of array */
#define START_DELAY 2		/* delay internal start */
typedef struct
{
 uint32_t encCount;		/* encoder counts */
 uint32_t intCount;		/* internal counts */
 uint32_t cycleCount;		/* encoder cycle counter */
 int missedStart;		/* start flag missed */

 unsigned int encCycLen;	/* encoder cycle length */
 unsigned int  encPulse;	/* encoder pulse number */
 uint16_t lastEnc;		/* last encoder capture */
 uint32_t encClocks;		/* clocks in current encoder cycle */
 uint32_t cycleClocks;		/* estimated clocks in cycle */

 uint16_t preScale;		/* counter pre scaler */

 int intCycLen;			/* internal cycle length */
 int intPulse;			/* internal pulse number */
 uint32_t intClocks;		/* clocks in current internal cycle */

 boolean startInt;		/* start internal timer */
 boolean measure;		/* measure flag */
 boolean stop;			/* stop flag */

 uint16_t startDelay;		/* initial delay */
 uint16_t delta[ARRAY_LEN];	/* saved delta values */
} T_CMP_TMR, *P_CMP_TMR;

EXT T_CMP_TMR cmpTmr;
EXT uint64_t clocksMin;		/* timer clocks per minute */

#define MAXJOG 16
typedef struct s_jogque
{
 int fil;
 int emp;
 int count;
 uint32_t buf[MAXJOG];
} T_JOGQUE, *P_JOGQUE;

EXT T_JOGQUE zJogQue;
EXT T_JOGQUE xJogQue;
EXT char jogPause;		/* flag for enabling jog during pause */

typedef struct s_movectl
{
 char state;			/* move state */
 char prev;			/* previous state */
 char stop;			/* stop flag */
 char jog;			/* jogging with control */
 char done;			/* done flag fpga */
 char wait;			/* waiting for done fpga */
 char ctlreg;			/* control register fpga */
 char axisName;			/* axis name */
 char mpgFlag;			/* mpg direction inverted */
 char mpgDirCh;			/* mpg direction change */
 char mpgBackWait;		/* mpg backlash wait */
 char mpgState;			/* mpg current state */
 char mpgLastState;		/* mpg last state */
 char limitsEna;		/* limits enabled */
 char limitMove;		/* move off limits in progress */
 unsigned int delayStart;	/* delay start time */
 unsigned int delayTimeout;	/* delay timeout in millis */
 int cmd;			/* move command */
 int dir;			/* direction -1 neg, 0 backlash, 1 pos */
 int dirChange;			/* direction */
 int limitDir;			/* direction when limit tripped */
 unsigned int dist;		/* distance to move */
 int droTarget;			/* target dro value */
 int loc;			/* current location */
 int expLoc;			/* expected location */
 int iniDist;			/* initial jog distance */
 unsigned int maxDist;		/* maximum jog distance */
 int jogInc;			/* jog increment */
 int jogFlag;			/* jog enable flag */
 int *mpgJogInc;		/* mpg jog increment */
 int *mpgJogMax;		/* mpg jog maximum distance */
 int mpgStepsCount;		/* mpg jog steps per mpg count */
 int mpgBackDist;		/* mpg backlash counter */
 unsigned int mpgDirChTim;	/* mpg direction change timer */
 unsigned int mpgUSecSlow;	/* time limit for slow jog  */
 int16_t jogCmd;		/* command for jog */
 int16_t speedCmd;		/* command for jog speed */
 P_AXIS axis;			/* axis parameters */
 P_ZXISR isr;			/* isr control block */
 P_JOGQUE jogQue;		/* jog queue */
 P_ACCEL acThread;		/* thread movement */
 P_ACCEL acTaper;		/* taper movement */
 P_ACCEL acMove;		/* unsynchronized movement */
 P_ACCEL acJog;			/* jog */
 P_ACCEL acJogSpeed;		/* jog at speed */
 int stepsInch;			/* steps per inch */
 int droCountInch;		/* dro count inch */
 TIM_TypeDef *timer;		/* axis timer */
 void (*isrStop) (char ch);	/* isr stop routine */
 void (*move) (int pos, int cmd); /* move absolute function */
 void (*moveRel) (int pos, int cmd); /* move relative function */
 void (*moveInit) (P_ACCEL ac, int dir, unsigned int dist); /* move init */
 void (*dirFwd) ();		/* direction forward */
 void (*dirRev) ();		/* direction rev */
 void (*hwEnable) (unsigned int ctr); /* hardware enable */
 void (*start) ();		/* axis start */
 void (*pulse) ();		/* axis pulse */
 int *locPtr;			/* pointer to location */
 int *droLocPtr;		/* pointer to dro location */
 int *homeOffset;		/* pointer to home offset */
 int *droOffset;		/* pointer to dro offset */
} T_MOVECTL, *P_MOVECTL;

EXT T_MOVECTL zMoveCtl;
EXT T_MOVECTL xMoveCtl;

EXT unsigned int clksPerUSec;	/* clocks per usec */

typedef struct s_homectl
{
 P_MOVECTL mov;
 int state;
 int prev;
 int16_t setActive;
 int16_t clrActive;
 int16_t setHomed;
 int16_t clrHomed;
 int *status;
 int findDist;
 int findDistRev;
 int backoffDist;
 int slowDist;
 uint16_t (*homeIsSet) ();
 uint16_t (*homeIsClr) ();
 void (*moveRel) (int pos, int cmd); /* move relative function */
} T_HOMECTL, *P_HOMECTL;

EXT T_HOMECTL xHomeCtl;
EXT T_HOMECTL zHomeCtl;

#define DEG_RAD (180.0 / 3.141592653589793)

typedef struct s_runctl
{
 char state;			/* state */
 char lastState;		/* last state */
 char spindleCmd;		/* wait spindle command */
 char probeCmd;			/* probe command */
 int pass;			/* current pass */
 char threadFlags;		/* threading flags */
 float taper;			/* taper */
 float zVal;			/* saved z value */
 float xVal;			/* saved x value */
 int feedType;			/* feed type */
 float zFeed;			/* z feed value */
 float xFeed;			/* x feed value */
 int zHomeOffset;		/* z home ofset */
 int xHomeOffset;		/* x home offset */
 int zStart;			/* threading z start */
 int xStart;			/* threading x start */
 float tanAngle;		/* tangent of threading angle */
 int safeZ;			/* z safe location */
 int safeX;			/* x safe location */
 uint32_t start;		/* start time */
} T_RUN_CTL, *P_RUN_CTL;

#define MAX_CMDS 64

typedef struct s_movecmd
{
 union
 {
  struct
  {
   uint16_t cmd;		/* move command */
   uint16_t flag;		/* command flags */
  };
  struct
  {
   uint32_t op;			/* combination of command and flags */
  };
 };
 union
 {
  float val;			/* floating value */
  int32_t iVal;			/* integer value */
 };
} T_MOVECMD, *P_MOVECMD;

typedef struct s_moveque
{
 int fil;
 int emp;
 int count;
 T_MOVECMD cmd[MAX_CMDS];
} T_MOVEQUE, *P_MOVEQUE;

EXT T_RUN_CTL runCtl;
EXT T_MOVEQUE moveQue;

EXT int16_t springInfo;

#define WD_INTERVAL 8		/* interval between watchdog pulses */
#define WD_PULSE 2		/* watchdog pulse width */

#define MAX_TIMEOUT UINT_MAX
#define REMCMD_TIMEOUT 1500U
#define INDEX_TIMEOUT 1500U

EXT unsigned int wdUpdateTime;	/* watchdog update time */
EXT unsigned int wdTimeout;	/* watchdog timeout */
EXT int wdState;		/* watchdog state */

EXT unsigned int remcmdUpdateTime;
EXT unsigned int remcmdTimeout;

typedef struct
{
 union
 {
  struct
  {
   uint16_t count;
   uint16_t overflow;
  };
  struct
  {
   uint32_t period;
  };
 };
} T_INDEX_COUNTER;

typedef struct s_indexTmr
{
 int indexTmrPreScale;		/* index timer prescaler */

 int tmrCount;			/* index timer count */
 int tmrAct;			/* index timer active */
 unsigned int timeout;
 unsigned int updateTime;

 uint16_t overflow;		/* index counter overflow */
 uint32_t start;		/* index period start count */
 uint32_t trkFreq;		/* freq for dbgTrk rpm calculation */
 uint32_t freq;			/* freq for remCmd rpm calculation */
} T_INDEX_TMR, *P_INDEX_TMR;

EXT T_INDEX_TMR idxTmr;

EXT int lcdRow;
EXT int lcdActive;

#if DBGTRK

#define TRKBUFSIZE (4*64)
EXT boolean dbgTrk;
EXT int16_t trkidx;
EXT int16_t trkbuf[TRKBUFSIZE];

#endif

void delay(unsigned int delay);
void delayUSec(unsigned short delay);
extern "C" unsigned int getSP();

void mainLoopSetup();
void mainLoopSetupX();

unsigned int millis();
void wdUpdate();

void pauseCmd();
void resumeCmd();
void stopCmd();
void doneCmd();
void measureCmd();
void clearCmd();

void allStop();			/* stop all */

void zIsrStop(char ch);
void xIsrStop(char ch);
void spIsrStop();

void clearAll();
void setup();

void setSpindleSpeed(int rpm);	/* set spindle speed */
void spindleSetup(int rpm);
void spindleInit(P_SPINDLE spa, int dist, int dir); /* init spindle */
void spindleStart();		/* start spindle */
void spindleStop();		/* stop spindle */
void spindleUpdate();		/* update spindle speed */
void spindleJog();		/* spindle jog */
void spindleJogSpeed();		/* spindle jog at speed */
float stepTime(float cFactor, unsigned int step);
void spindleAccelCalc(P_SPINDLE sp); /* calculate spindle acceleration */
void spindleSpeedCalc(float finalRPM);

void slaveEna();		/* enable slave */

void accelInit(P_AXIS ax, P_ACCEL ac);
unsigned int turnInit(P_ZXISR isr, P_ACCEL ac, int dir, unsigned int dist);
void encTurnInit(P_ZXISR isr, P_ACCEL ac, int dir, unsigned int dist);
void syncTurnInit(P_ZXISR isr, P_ACCEL ac, int dir, unsigned int dist);
unsigned int taperInit(P_ZXISR isr, P_ACCEL ac, int dir);
void encTaperInit(P_ZXISR isr, P_ACCEL ac, int dir, int syncInit);
unsigned int moveInit(P_ZXISR isr, P_ACCEL ac, int dir, unsigned int dist);

void cmpTmrSetup();

void syncMoveSetup();

void syncSetup();
void syncMeasure();
void syncCalculate();
void syncStart();		/* start pulse encoder */
void syncStop();		/* stop pulse encoder */
void encoderSWIEnable(int enable);

void encoderStart();

void jogMove(P_MOVECTL mov, int dir);
void jogMpg(P_MOVECTL mov);
void jogMpg1(P_MOVECTL mov);
void jogMpg2(P_MOVECTL mov);
void jogMpg3(P_MOVECTL mov);
void jogSpeed(P_MOVECTL mov, float speed);

void zInit(P_AXIS ax);
void zReset();
void zHwEnable(unsigned int ctr);
void zTurnInit(P_ACCEL ac, int dir, unsigned int dist);
void zTaperInit(P_ACCEL ac, int dir);
void zMoveInit(P_ACCEL ac, int dir, unsigned int dist);
void zStart();
void zPulseSetup();
void zPulseTrig();
void zPulse();
void zStartSlave();

void zMoveAbsCmd();
void zMoveRelCmd();
void zJogCmd();
void zJogSpeedCmd();
void zLocCmd();

void zStop();
void zSetup();
void zMoveSetup();
void zSynSetup(int feedType, float feed, float runout, float runoutDepth);
void zInfo(char flag);
void zMove(int pos, int cmd);
void zMoveRel(int pos, int cmd);
void zControl();
void zHomeSetup();

void xInit(P_AXIS ax);
void xReset();
void xHwEnable(unsigned int ctr);
void xTurnInit(P_ACCEL ac, int dir, unsigned int dist);
void xTaperInit(P_ACCEL ac, int dir);
void xRunoutInit();
void xSyncRunoutInit();
void xEncRunoutInit();
void xMoveInit(P_ACCEL ac, int dir, unsigned int dist);
void xStart();
void xPulseSetup();
void xPulseTrig();
void xPulse();
void xStartSlave();

void xMoveAbsCmd();
void xMoveRelCmd();
void xJogCmd();
void xJogSpeedCmd();
void xLocCmd();

void xStop();
void xSetup();
void xMoveSetup();
void xSynSetup(int feedType, float feed);
void xInfo(char flag);
void xMove(int pos, int cmd);
void xMoveDro(int pos, int cmd);
void xMoveRel(int pos, int cmd);
void xControl();
void xHomeSetup();

void axisCtl();
void homeAxis(P_HOMECTL home, int homeCmd);
void homeControl(P_HOMECTL home);

void runInit();
char queMoveCmd(uint32_t op, float val);
char queIntCmd(uint32_t op, int val);
void stopMove();
void procMove();

void moveZX(int zLoc, int xLoc);
void moveXZ(int xLoc, int ZLoc);

//void taperZX(int zLoc, float taper);
//void taperXZ(int xLoc, float taper);

void turnPitch(P_ACCEL ac, float pitch);
void threadTPI(P_ACCEL ac, float tpi);
void threadMetric(P_ACCEL ac, float pitch);
void turnCalc(P_ACCEL ac);
void encTurnCalc(P_ACCEL ac);
void motorSetup(P_ACCEL ac, float accel, float feed);
void turnAccel(P_ACCEL ac, float accel, int flag, float rpm);

#define T_STEP_SPINDLE 1
#define T_DBG_PRINT 2

void speedCalc(P_ACCEL accel, P_ZXISR isr, float finalSpeed);
void accelCalc(P_ACCEL accel);
void taperCalc(P_ACCEL a0, P_ACCEL a1, float taper);
void runoutCalc(P_ACCEL a0, P_ACCEL a1, float runout, float depth);
void encRunoutCalc(P_ACCEL a0, P_ACCEL a1, float runout, float depth);

void TIM3_Init();
void TIM8_Init();

void enaDbgPins(int flag);

#if 0
T_PIN_NAME pinName(char *buf, GPIO_TypeDef *port, int pin);
char *gpioStr(char *buf, int size, T_PIN_NAME *pinInfo);
void gpioInfo(GPIO_TypeDef *gpio);
void tmrInfo(TIM_TypeDef *tmr);
void extiInfo();
void usartInfo(USART_TypeDef *usart, const char *str);
void i2cInfo(I2C_TypeDef *i2c, const char *str);
void rccInfo();
#endif

void testOutputs(int inputTest);
void pinDisplay();

typedef union
{
 struct
 {
  unsigned b0:1;
  unsigned b1:1;
  unsigned b2:1;
  unsigned b3:1;
  unsigned b4:1;
  unsigned b5:1;
  unsigned b6:1;
  unsigned b7:1;
  unsigned b8:1;
  unsigned b9:1;
  unsigned b10:1;
  unsigned b11:1;
  unsigned b12:1;
  unsigned b13:1;
  unsigned b14:1;
  unsigned b15:1;
  unsigned b16:1;
  unsigned b17:1;
  unsigned b18:1;
  unsigned b19:1;
  unsigned b20:1;
  unsigned b21:1;
  unsigned b22:1;
  unsigned b23:1;
  unsigned b24:1;
  unsigned b25:1;
  unsigned b26:1;
  unsigned b27:1;
  unsigned b28:1;
  unsigned b29:1;
  unsigned b30:1;
  unsigned b31:1;
 };
 struct
 {
  int w;
 };
} BITWORD;

typedef union
{
 struct
 {
  unsigned short delta;
  char r0;
  char dir;
 };
 struct
 {
  int intVal;
 };
} MPG_VAL;

inline int xDro()
{
 return(rVar.xDroLoc - rVar.xDroOffset);
}

#if defined(MEGAPORT)

void megaPoll();
void megaRsp();

#endif	/* MEGAPORT */

#if defined(SYNC_SPI)

typedef struct sSyncMultiParm
{
 int16_t syncParm;
 int16_t remParm;
} T_SYNC_MULTI_PARM, *P_SYNC_MULTI_PARM;

void initSync();
void syncResp();

void syncCommand(uint8_t cmd);
void syncSendMulti(P_SYNC_MULTI_PARM p);
void syncPoll();

EXT bool syncCmdDone;
EXT bool syncLoadDone;
EXT bool syncReadDone;
EXT bool syncPollDone;

#endif	/* SYNC_SPI */

#include "main.h"
#include "pinDef.h"
#include "timers.h"
#include "home.h"
#include "probe.h"
#include "dbgtrk.h"
#include "dbg.h"

#endif  /* LATHE_INC */	// ->
