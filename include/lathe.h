#if 1	// <-

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

#include "config.h"
#include "remvar.h"

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
 int clocksRev;			/* clocks per revolution */
 float stepsSec;		/* steps per second */
 float stepsSec2;		/* acceleration steps per second sqrd */
 float time;			/* actual acceleration time */
 int steps;			/* acceleration steps */
 int clocks;			/* acceleration clocks */
 float revs;			/* acceleration revolutions */
 int64_t clocksCycle;		/* clocks per cycle */

 /* control variables for isr */
 float cFactor;			/* factor for computing acceleration */
 int clocksStep;		/* fcy clocks per step */
 unsigned int initialStep;	/* accel steps to minimum speed */
 unsigned int finalStep;	/* accel steps to maximum speed */
 int stepsRev;			/* steps per revolution */
 int stepsCycle;		/* steps per cycle */
 int zStart;			/* z start position */
 int xStart;			/* x start position */
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
 int clocksStep;		/* final clocks per step value */
 unsigned int initialStep;	/* minimum acceleration step */
 unsigned int finalStep;	/* maximum acceleration step */
 int stepsRev;			/* steps per revolution */
 int stepsCycle;		/* steps in a cycle */
 int zStart;			/* z start position */
 int xStart;			/* x start position */

 /* jog variables */
 int iniDist;			/* initial jog distance */
 unsigned int maxDist;		/* maximum jog distance */
 int jogInc;			/* jog increment */

 /* working variables */
 uint32_t intCount;		/* spindle interrupt count */
 int pos;			/* position in revolution */
 int rev;			/* revolutions */
 unsigned int dist;		/* distance to run */
 unsigned int accelStep;	/* current acceleration step */
 int lastCount;			/* last counter value */
 int curCount;			/* current count value */
 int cycleCounter;		/* cycle step counter */
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
   int steps;			/* acceleration steps */
   int droTarget;		/* target for dro position */
   int clocks;			/* acceleration clocks */
   float dist;			/* acceleration distance */

   int remainder;		/* remainder of spindle cyc div z cyc */
   int initialCount;		/* clocks to first accel step */
   int finalCount;		/* clocks to last accel step */
   int totAccelClocks;		/* accel clocks final minus initial */
   int accelSpSteps;		/* spindle steps during acceleration */
   int accelSpRem;		/* spindle steps remainder */

   /* control variables for isr */

   float cFactor;		/* factor to get clocks to next step */
   int clocksStep;		/* clocks per step after acceleration */
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
 char dir;			/* axis direction */
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

 int16_t syncInit;		/* initialized for sync operation */
 int16_t syncStart;		/* waiting for start */
 int16_t active;		/* axis active */

 /* control variables */
 float cFactor;			/* acceleration factor */
 int clocksStep;		/* final clocks per step */
 unsigned int initialStep;	/* initial accel step number */
 unsigned int finalStep;	/* final accel step number */
 unsigned int counterStep1;	/* counter value for incr1 */
 unsigned int counterStep2;	/* counter value for incr2 */
 int d;				/* sum initial value */
 int incr1;			/* incr 1 value */
 int incr2;			/* incr 2 value */
 int delta;			/* update on direction change */
 int stepsCycle;		/* steps in a cycle */
 int accelSpSteps;		/* spindle steps during acceleration */
 int finalCtr;			/* final counter value */

 /* working variables */
 int pos;			/* position */
 unsigned int dist;		/* distance to move */
 int droTarget;			/* dro target value */
 unsigned int accelStep;	/* current step in accel */
 int lastCount;			/* last count value */
 int curCount;			/* current count value */
 int sum;			/* sum for distributing remainder */
 int lastRemCount;		/* last remainder count */
 int remCount;			/* remainder count */
 int cycleCounter;		/* step cycle counter */
 int clockSum;
 int startRev;			/* start revolution */
 int startPos;			/* start position */
 int stopRev;			/* stop revolution */
 int stopPos;			/* stop position */

 int steps;			/* steps moved */

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

EXT int zRunoutFlag;		/* z axis runout flag */
EXT float zRunoutDist;		/* z runout distance */
EXT unsigned int zRunoutStart;	/* z runout start step */
EXT int zRunoutSteps;		/* z runout steps */

EXT T_AXIS xAxis;		/* x axis info */

EXT T_ACCEL zTA;		/* z threading accel */
EXT T_ACCEL zPA;		/* z taper accel */
EXT T_ACCEL zMA;		/* z move accel */
EXT T_ACCEL zJA;		/* z jog accel */
EXT T_ACCEL zJSA;		/* z jog speed accel */
EXT T_ACCEL zSA;		/* z slow jog accel */

EXT boolean xRunoutFlag;	/* x runout in progress */
EXT int xRunoutSteps;		/* x runout steps */

EXT T_ZXISR zIsr;		/* z isr variables */

EXT int16_t zSyncInit;		/* z sync init */

EXT T_ACCEL xTA;		/* x threading accel */
EXT T_ACCEL xPA;		/* x taper accel */
EXT T_ACCEL xRA;		/* x runout accel */
EXT T_ACCEL xMA;		/* x move aiccel */
EXT T_ACCEL xJA;		/* x jog accel */
EXT T_ACCEL xJSA;		/* x jog speed accel */
EXT T_ACCEL xSA;		/* x slow jog accel */

EXT T_ZXISR xIsr;		/* x isr variables */

EXT int16_t xSyncInit;		/* x sync init */

#define Z_ACTIVE 1		/* z axis active */
#define X_ACTIVE 2		/* x axis active */

EXT char runoutActive;		/* runout active */
EXT char active;		/* axis driven by spindle */
EXT char stepActive;		/* stepper active */
EXT char encActive;		/* encoder active */
EXT char synIntActive;		/* sync internal active */
EXT char synExtActive;		/* sync external active */

EXT int32_t tmrStepWidth;	/* step width */
EXT int32_t tmrMin;		/* timer minimum width */

EXT int trackSpeed;		/* external motor track speed */
EXT int updateFeed;		/* time to update feed */

EXT unsigned int wdUpdateTime;	/* watchdog update time */
EXT unsigned int wdTimeout;	/* watchdog timeout */
EXT int wdState;		/* watchdog state */

#define WD_INTERVAL 8		/* interval between watchdog pulses */
#define WD_PULSE 2		/* watchdog pulse width */

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
 int encPulse;			/* encoder pulse number */
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

 int16_t startDelay;		/* initial delay */
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
 char mpgFlag;			/* mpg direction flag */
 char mpgBackWait;		/* mpg backlash wait */
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
 TIM_TypeDef *timer;		/* axis timer */
 void (*isrStop) (char ch);	/* isr stop routine */
 void (*move) (int pos, int cmd); /* move absolute function */
 void (*moveRel) (int pos, int cmd); /* move relative function */
 void (*moveInit) (P_ACCEL ac, char dir, int dist); /* move initialization */
 void (*dirFwd) (void);		/* direction forward */
 void (*dirRev) (void);		/* direction rev */
 void (*hwEnable) (int ctr);	/* hardware enable */
 void (*start) (void);		/* axis start */
 void (*pulse) (void);		/* axis pulse */
 int *locPtr;			/* pointer to location */
 int *droLocPtr;		/* pointer to dro location */
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
 uint16_t (*homeIsSet) (void);
 uint16_t (*homeIsClr) (void);
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

#define MAX_TIMEOUT UINT_MAX
#define REMCMD_TIMEOUT 1000U
#define INDEX_TIMEOUT 1500U

EXT unsigned int remcmdUpdateTime;
EXT unsigned int remcmdTimeout;

EXT unsigned int indexUpdateTime;

EXT char spindleSync;
EXT char useEncoder;
EXT char encoderDirect;

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

EXT int indexTmrPreScale;	/* index timer prescaler */
EXT int indexTmrCount;		/* index timer count */
EXT int indexTmrAct;		/* index timer active */
EXT unsigned int indexTimeout;

EXT uint16_t indexOverflow;	/* index counter overflow */
EXT uint32_t indexStart;	/* index period start count */
EXT uint32_t indexTrkFreq;	/* freq for dbgTrk rpm calculation */
EXT uint32_t indexFreq;		/* freq for remcmd rpm calculation */

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
extern "C" unsigned int getSP(void);

void mainLoopSetup(void);
void mainLoopSetupX(void);

unsigned int millis(void);
void wdUpdate(void);

void pauseCmd(void);
void resumeCmd(void);
void stopCmd(void);
void doneCmd(void);
void measureCmd(void);
void clearCmd(void);

void allStop(void);			/* stop all */

void zIsrStop(char ch);
void xIsrStop(char ch);
void spIsrStop(void);

void clearAll(void);
void setup(void);

void setSpindleSpeed(int rpm);	/* set spindle speed */
void spindleSetup(int rpm);
void spindleInit(P_SPINDLE spa, int dist, int dir); /* init spindle */
void spindleStart(void);	/* start spindle */
void spindleStop(void);		/* stop spindle */
void spindleUpdate(void);	/* update spindle speed */
void spindleJog(void);		/* spindle jog */
void spindleJogSpeed(void);	/* spindle jog at speed */
float stepTime(float cFactor, int step);
void spindleAccelCalc(P_SPINDLE sp); /* calculate spindle acceleration */
void spindleSpeedCalc(float finalRPM);

void slaveEna(void);		/* enable slave */

void accelInit(P_AXIS ax, P_ACCEL ac);
int turnInit(P_ZXISR isr, P_ACCEL ac, char dir, int dist);
void encTurnInit(P_ZXISR isr, P_ACCEL ac, char dir, int dist);
void syncTurnInit(P_ZXISR isr, P_ACCEL ac, char dir, int dist);
int taperInit(P_ZXISR isr, P_ACCEL ac, char dir);
void encTaperInit(P_ZXISR isr, P_ACCEL ac, char dir);
int moveInit(P_ZXISR isr, P_ACCEL ac, char dir, int dist);

void cmpTmrSetup(void);

void syncMoveSetup(void);

void syncSetup(void);
void syncMeasure(void);
void syncCalculate(void);
void syncStart(void);		/* start pulse encoder */
void syncStop(void);		/* stop pulse encoder */
void encoderSWIEnable(int enable);

void encoderStart(void);

void jogMove(P_MOVECTL mov, int dir);
void jogMpg(P_MOVECTL mov);
void jogMpg1(P_MOVECTL mov);
void jogMpg2(P_MOVECTL mov);
void jogSpeed(P_MOVECTL mov, float speed);

void zInit(P_AXIS ax);
void zReset(void);
void zHwEnable(int ctr);
void zTurnInit(P_ACCEL ac, char dir, int dist);
void zTaperInit(P_ACCEL ac, char dir);
void zMoveInit(P_ACCEL ac, char dir, int dist);
void zStart(void);
void zPulseSetup(void);
void zPulseTrig(void);
void zPulse(void);
void zStartSlave(void);

void zMoveAbsCmd(void);
void zMoveRelCmd(void);
void zJogCmd(void);
void zJogSpeedCmd(void);
void zLocCmd(void);

void zStop(void);
void zSetup(void);
void zMoveSetup(void);
void zSynSetup(int feedType, float feed, float runout, float runoutDepth);
void zInfo(char flag);
void zMove(int pos, int cmd);
void zMoveRel(int pos, int cmd);
void zControl(void);
void zHomeSetup(void);

void xInit(P_AXIS ax);
void xReset(void);
void xHwEnable(int ctr);
void xTurnInit(P_ACCEL ac, char dir, int dist);
void xTaperInit(P_ACCEL ac, char dir);
void xRunoutInit(void);
void xSyncRunoutInit(void);
void xEncRunoutInit(void);
void xMoveInit(P_ACCEL ac, char dir, int dist);
void xStart(void);
void xPulseSetup(void);
void xPulseTrig(void);
void xPulse(void);
void xStartSlave(void);

void xMoveAbsCmd(void);
void xMoveRelCmd(void);
void xJogCmd(void);
void xJogSpeedCmd(void);
void xLocCmd(void);

void xStop(void);
void xSetup(void);
void xMoveSetup(void);
void xSynSetup(int feedType, float feed);
void xInfo(char flag);
void xMove(int pos, int cmd);
void xMoveDro(int pos, int cmd);
void xMoveRel(int pos, int cmd);
void xControl(void);
void xHomeSetup(void);

void axisCtl(void);
void homeAxis(P_HOMECTL home, int homeCmd);
void homeControl(P_HOMECTL home);

void runInit(void);
char queMoveCmd(uint32_t op, float val);
char queIntCmd(uint32_t op, int val);
void stopMove(void);
void procMove(void);

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

void TIM3_Init(void);
void TIM8_Init(void);

void enaDbgPins(int flag);

#if 0
T_PIN_NAME pinName(char *buf, GPIO_TypeDef *port, int pin);
char *gpioStr(char *buf, int size, T_PIN_NAME *pinInfo);
void gpioInfo(GPIO_TypeDef *gpio);
void tmrInfo(TIM_TypeDef *tmr);
void extiInfo(void);
void usartInfo(USART_TypeDef *usart, const char *str);
void i2cInfo(I2C_TypeDef *i2c, const char *str);
void rccInfo(void);
#endif

void testOutputs(int inputTest);
void pinDisplay(void);

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

#include "main.h"
#include "pinDef.h"
#include "timers.h"
#include "home.h"
#include "probe.h"
#include "dbgtrk.h"
#include "dbg.h"

#endif	// ->
