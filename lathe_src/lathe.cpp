/******************************************************************************/
#define __LATHE__
#ifdef STM32F4
#include "stm32f4xx_hal.h"
#endif
#ifdef STM32F7
#include "stm32f7xx_hal.h"
#endif
#ifdef STM32H7
#include "stm32h7xx_hal.h"
#endif

#include <cstdio>
#include <cstring>
#include <cmath>
#include <climits>
#include <cstdint>

#define ENUM_AXIS_STATES 0
#define ENUM_M_STATES    0
#define ENUM_M_COMMANDS  0
#define ENUM_OPERATIONS  0
#define ENUM_H_STATES    0
#define ENUM_D_MESSAGE   0
#define ENUM_EV_EVENTS   0
#define ENUM_SEL_TURN    0
#define ENUM_SEL_THREAD  0

#include "main.h"
#include "config.h"
#include "remvar.h"

#include "serialio.h"
#include "spix.h"
#include "lcd.h"
#include "i2cx.h"

#include "Xilinx.h"
#include "zcontrol.h"
#include "xcontrol.h"

#include "tim.h"

#if defined(MEGAPORT)
#include "megaCmdList.h"
#include "megaParmList.h"
#include "megaCtlstates.h"
#endif	/* MEGAPORT */

#ifdef EXT
#undef EXT
#endif

#define EXT
#include "lathe.h"
#include "stm32Info.h"
#include "arc.h"

#if defined(__LATHE_INC__)		// <-

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
#define REMCMD_TIMEOUT 1000U
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
 uint32_t freq;			/* freq for remcmd rpm calculation */
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

#endif	// ->
#ifdef __LATHE__

#include "latheX.h"

#if defined(SYNC_SPI)

//#include "syncStruct.h"
#include "remParmList.h"
#include "syncParmList.h"

T_SYNC_MULTI_PARM syncParms[] =
{
 {SYNC_ENCODER, ENC_PER_REV},
 {SYNC_CYCLE, L_SYNC_CYCLE},
 {SYNC_OUTPUT, L_SYNC_OUTPUT},
 {SYNC_PRESCALER, L_SYNC_PRESCALER},
 {SYNC_MAX_PARM, 0},
};
#endif	/* SYNC_SPI */

unsigned int lastRevCount;

void delay(unsigned int delay)
{
 delay += 1;
 unsigned int start = millis();
 while ((millis() - start) < delay)
 {
  if (WD_ENA)
   IWDG->KR = 0xAAAA;		/* update hardware watchdog */
 }
}

void delayUSec(unsigned short delay)
{
 unsigned short start = usecTmrRead();
 unsigned short usec = start;
 while (true)
 {
  unsigned short tmp = usecTmrRead(); /* read timer */

  if ((tmp - start) < delay)	/* if delay expired  */
   break;			/* exit loop */
  if ((tmp - usec) > 20)	/* if 20 usec passed */
  {
   usec = tmp;			/* reset timer */
   if (WD_ENA)
    IWDG->KR = 0xAAAA;		/* update hardware watchdog */
  }
 }
}

#if 0
extern uint32_t uwTick;
#endif

unsigned int millis()
{
 return((unsigned int) uwTick);
}

void wdUpdate()
{
 unsigned int curTime = millis();
 if ((curTime - wdUpdateTime) > wdTimeout)
 {
  wdUpdateTime = curTime;
  if (wdState)
  {
   chgPumpClr();
   wdState = 0;
   wdTimeout =  WD_INTERVAL;
  }
  else
  {
   chgPumpSet();
   wdState = 1;
   wdTimeout = WD_PULSE;
  }
 }
}

void stopCmd()
{
 if (DBG_SETUP)
  printf("\nstop\n");

 stopMove();
 if (rVar.cfgFpga == 0)
 {
  spindleStop();
  zStop();
  xStop();
 }
 else
 {
  spindleStopX();
  zStopX();
  xStopX();
 }
 xMoveCtl.stop = 1;
 zMoveCtl.stop = 1;
 rVar.cmdPaused = 0;
 rVar.mvStatus &= ~(MV_PAUSE | MV_ACTIVE | MV_DONE |
		 MV_XHOME_ACTIVE | MV_ZHOME_ACTIVE);
 xHomeCtl.state = H_IDLE;
 zHomeCtl.state = H_IDLE;
#if WIN32
 fflush(stdout);
#endif
}

void doneCmd()
{
 rVar.mvStatus &= ~MV_DONE;
}

void measureCmd()
{
 if (DBG_SETUP)
  printf("\nmeasure\n");

 rVar.mvStatus |= MV_MEASURE;
}

void clearCmd()
{
 if (DBG_SETUP)
  printf("\nclear\n");

 allStop();
 clearAll();
#if WIN32
 fflush(stdout);
#endif
}

void pauseCmd()
{
 if (DBG_SETUP)
  printf("\npause\n");

 rVar.cmdPaused = 1;
 rVar.mvStatus |= MV_PAUSE;
#if WIN32
 fflush(stdout);
#endif
}

void resumeCmd()
{
 if (DBG_SETUP)
  printf("\nresume\n");

 rVar.cmdPaused = 0;
 if (jogPause & DISABLE_JOG)
  jogPause &= ~(PAUSE_ENA_X_JOG | PAUSE_ENA_Z_JOG);
 rVar.mvStatus &= ~(MV_PAUSE | MV_MEASURE | MV_READ_X | MV_READ_Z);
#if WIN32
 fflush(stdout);
#endif
}

#define clr(x) memset(&(x), 0, sizeof(x))

void clearAll()
{
 syncStop();

 if (DBG_SETUP)
  printf("\nclear all\n");

 if (rVar.cfgFpga == 0)
 {
  clr(zIsr);
  clr(xIsr);

  clr(spA);
  clr(spJA);
  clr(sp);

  spEncCount = 0;
 }

 clr(zAxis);
 clr(xAxis);

 clr(zTA);
 clr(zPA);
 clr(zMA);
 clr(zJA);
 clr(zJSA);
 clr(zSA);

 runout.zFlag = 0;
 runout.zStart = 0;
 runout.zDist = 0.0;
 runout.zSteps = 0;

 clr(xTA);
 clr(xPA);
 clr(xRA);
 clr(xMA);
 clr(xJA);
 clr(zJSA);
 clr(xSA);

 clr(zMoveCtl);
 clr(xMoveCtl);
 clr(xHomeCtl);
 clr(zHomeCtl);

 clr(arcData);

 runout.xFlag = 0;
 runout.xSteps = 0;

 clr(cmpTmr);

 if (rVar.cfgFpga)
 {
  LOAD(XLDZCTL, ZRESET);
  LOAD(XLDZCTL, 0);
  LOAD(XLDXCTL, XRESET);
  LOAD(XLDXCTL, 0);
  LOAD(XLDTCTL, 0);
  LOAD(XLDDCTL, 0);
 }

 rVar.cmdPaused = 0;
 jogPause = 0;
 rVar.mvStatus &= ~(MV_PAUSE | MV_ACTIVE | MV_DONE |
	       MV_XHOME_ACTIVE | MV_ZHOME_ACTIVE | MV_MEASURE);

 rVar.currentPass = 0;
 rVar.totalPasses = 0;
 springInfo = 0;

 zAxis.stepsInch = INT_MAX;
 xAxis.stepsInch = INT_MAX;
 rVar.zDroCountInch = INT_MAX;
 rVar.xDroCountInch = INT_MAX;

 printf("Start ZFlag %d\n", ((ZFlag_Pin & ZFlag_GPIO_Port->ODR) != 0));
 printf("Start set\n");
 startSet();
 printf("Start ZFlag %d\n", ((ZFlag_Pin & ZFlag_GPIO_Port->ODR) != 0));
 runInit();
 printf("clearAll done\n");
 flushBuf();
}

void setup()
{
 if (rVar.cfgMpg)
 {
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn); /* enable mpg interrupts */
  EXTI->PR = JogA1_Pin | JogA2_Pin | JogB1_Pin | JogB2_Pin;
 }
 else
  HAL_NVIC_DisableIRQ(EXTI9_5_IRQn); /* disable mpg interrupts */

 if (rVar.cfgDro)
 {
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn); /* enable dro interrupts */
  EXTI->PR = ZA_Pin | ZB_Pin | XA_Pin | XB_Pin;
 }
 else
  HAL_NVIC_DisableIRQ(EXTI15_10_IRQn); /* enable dro interrupts */

#if I2C
 if (rVar.cfgLcd)
 {
  if (!lcdActive)
  {
   printf("lcdInit start");
   flushBuf();
#if 1
   lcdInit();
#else
   int retry = 3;
   while (!lcdInit())
   {
    printf("lcdInit failure\n");
    flushBuf();
    if (--retry <= 0)
    {
     cfgLcd = 0;
     break;
    }
    unsigned int tmp = millis();
    while ((millis() - tmp) < 500)
     ;
   }
#endif
   if (i2cError == 0)
   {
    printf("lcdInit done\n");
    lcdActive = 1;
    lcdRow = 0;
   }
   else
   {
    printf("lcdInit failed\n");
   }
   flushBuf();
  }
 }
#endif

 allStop();
 clearAll();

#ifdef DBG_PINS
#define DBG_GPIO 0
#if DBG_GPIO
 gpioInfo(GPIOB);
 gpioInfo(GPIOC);
#endif

 if (rVar.cfgFpga == 0)
 {
  enaDbgPins(XILINX_PIN);
  HAL_SPI_MspDeInit(&hspi2);
  enaDbgPins(SPI_PIN);
 }

#if I2C == 0
  HAL_I2C_MspDeInit(&hi2c1);
  enaDbgPins(I2C_PIN);
#endif

#if DBG_GPIO
 gpioInfo(GPIOB);
 gpioInfo(GPIOC);
#endif
#endif

 if (rVar.cfgFpga == 0)
  mainLoopSetup();
 else
  mainLoopSetupX();

 if (DBG_SETUP)
 {
  printf("mainLoopSetup done\n");
  flushBuf();
 }

 wdUpdateTime = millis();	/* initial watchdog reference */
 remcmdTimeout = UINT_MAX;	/* set timeout to maximum */

 tmrStepWidth = CALC_STEP_WIDTH(STEP_WIDTH);
 tmrMin = tmrStepWidth * 2;
 tmrStepWidth -= 1;
 tmrMin -= 1;

 rVar.setupDone = 1;			/* indicate setup complete */

 clksPerUSec = rVar.cfgFcy / 1000000; /* clocks per usec */
}

void allStop()
{
 if (DBG_SETUP)
  printf("\nall stop\n");

 if (rVar.cfgFpga == 0)
 {
  if (rVar.stepperDrive		/* if stepper drive */
  ||  rVar.motorTest)		/* or testing motor drive */
  {
   spindleTmrStop();		/* make sure timer stopped */
   spindleTmrClrIE();		/* disable interrupts */
   spindleTmrClrIF();		/* clear interrupt flag */
  }

  zTmrSlvDis();
  zTmrStop();
  zTmrClrIE();
  zTmrClrIF();

  xTmrSlvDis();
  xTmrStop();
  xTmrClrIE();
  xTmrClrIF();
 }
 else
 {
  spindleStopX();
  zStopX();
  xStopX();
 }
 dbg0Clr();
 dbg1Clr();
 dbg2Clr();
 dbg3Clr();
 dbg4Clr();
 dbg5Clr();
 dbg6Clr();
 dbg7Clr();
 dbg8Clr();
 dbg9Clr();
 dbg10Clr();
}

#define TMR1_PWM_MAX 1024

void setSpindleSpeed(int rpm)
{
 if (rVar.cfgMega == 0)
 {
  if constexpr (PWM_TIMER != INDEX_TIMER) /* if pwm and idx tmrs different */
  {
   constexpr unsigned int MAX_COUNT = 65536;

   unsigned int cnt = rVar.cfgFcy / rVar.pwmFreq;
   unsigned int preScale = ((cnt % MAX_COUNT) ?
			    cnt / MAX_COUNT + 1 : cnt / MAX_COUNT);
   cnt /= preScale;
   unsigned int pwmTmrVal = cnt;
   cnt -= 1;

   unsigned int pwm = (rpm * pwmTmrVal) / rVar.maxSpeed;

   if (DBG_SETUP)
   {
    printf("pwmFreq %d preScale %d cnt %d\n",
	   rVar.pwmFreq, preScale, pwmTmrVal);
    printf("rpm %d maxSpeed %d pwm %d\n",
	   rpm, rVar.maxSpeed, pwm);
   }

   pwmTmrInit();
   pwmTmrScl(preScale - 1);
   pwmTmrCntClr();
   pwmTmrSet(cnt);
   pwmTmrStart();
   pwmTmrCCR(pwm - 1);
   pwmTmrPWMMode();
  }
  else			/* if pwm and idx timers the same */
  {
   int pwm = (uint16_t) ((rpm * idxTmr.updateTime) / rVar.maxSpeed);

   pwmTmrCCR(pwm - 1);
   pwmTmrPWMMode();
  }
 }
#if defined(MEGAPORT)
 else
 {
  if (rVar.megaSim == 0)
  {
   auto pwm = (int16_t) ((rpm * TMR1_PWM_MAX) / rVar.maxSpeed);
   char ch = MEGA_SET_RPM;
   putMega(1);
   sndhexMega((const unsigned char *) &ch, sizeof(ch), ' ');
   sndhexMega((const unsigned char *) &pwm, sizeof(pwm), '\r');
  }
  else
  {
   putMega(1);
   char ch = MEGA_SET_VAL;
   sndhexMega((const unsigned char *) &ch, sizeof(ch), ' ');
   ch = M_PARM_RPM;
   sndhexMega((const unsigned char *) &ch, sizeof(ch), ' ');
   sndhexMega((const unsigned char *) &rpm, sizeof(rpm), '\r');

   ch = MEGA_UPDATE_RPM;
   putMega(1);
   sndhexMega((const unsigned char *) &ch, sizeof(ch), '\r');
  }
 }
#endif	/* MEGAPORT */
}

void spindleSetup(int rpm)
{
 if (DBG_SETUP)
 {
  printf("\nspindleSetup %d\n", rpm);
 }

 rVar.spRpm = (float) rpm;	/* save rpm */
 if (rVar.cfgVarSpeed)		/* spindle driven with variable speed motor */
 {
  setSpindleSpeed(rpm);		/* set spindle speed */
 }

 if (sp.active == 0)		/* if spindle not active */
 {
  P_SPINDLE spa = &spA;
  GPIO_InitTypeDef gpio;

#ifdef Index_Pin
  if (rVar.spTestIndex)		/* if testing index pulse */
  {
   gpio.Pin = Index_Pin;
   gpio.Mode = GPIO_MODE_INPUT;	/* configure as input */
   gpio.Pull = GPIO_NOPULL;
   HAL_GPIO_Init(Index_GPIO_Port, &gpio);
  }
  else				/* if normal operation */
  {
   gpio.Pin = Index_Pin;
   gpio.Mode = GPIO_MODE_IT_RISING; /* configure for interrupt */
   gpio.Pull = GPIO_NOPULL;
   HAL_GPIO_Init(Index_GPIO_Port, &gpio);
  }

  HAL_NVIC_EnableIRQ(indexIRQn); /* enable index 2 interrupt */
  EXTI->PR = Index_Pin;
#endif

  spa->label = "spA";
  if (rVar.stepperDrive		/* if using stepper drive */
  ||  rVar.motorTest)		/* or motor test */
  {
   spa->motorSteps = rVar.spSteps;
   spa->microSteps = rVar.spMicro;
   spa->minRPM = rVar.spMinRpm;
   if (rpm == 0)
    spa->maxRPM = rVar.spMaxRpm;
   else
    spa->maxRPM = (float) rpm;
   if (ACCEL_TIME)
    spa->aTime = rVar.spAccelTime;
   else
    spa->accel = rVar.spAccel;
   if (rVar.spDirFlag)
   {
    spa->dirFwd = DIR_SPIN_BIT;
    spa->dirRev = DIR_SPIN_BIT << 16;
   }
   else
   {
    spa->dirFwd = DIR_SPIN_BIT << 16;
    spa->dirRev = DIR_SPIN_BIT;
   }

   spindleAccelCalc(spa);

   spindleInit(spa, 0, SP_FWD);

   if (rpm == 0)
   {
    spa = &spJSA;
    spa->label = "spJSA";

    spa->motorSteps = rVar.spSteps;
    spa->microSteps = rVar.spMicro;
    spa->minRPM = 0;
    spa->maxRPM = rVar.spMaxRpm;
    spa->accel = rVar.spAccel;
    spa->dirFwd = spA.dirFwd;
    spa->dirRev = spA.dirRev;
#if 0
    spindleAccelCalc(spa);
#endif

    spa = &spJA;
    spa->label = "spJA";

    spa->motorSteps = rVar.spSteps;
    spa->microSteps = rVar.spMicro;
    spa->minRPM = rVar.spJogMinRpm;
    spa->maxRPM = rVar.spJogMaxRpm;
    if (ACCEL_TIME)
     spa->aTime = rVar.spJogAccelTime;
    else
     spa->accel = rVar.spAccel;
    spa->dirFwd = spA.dirFwd;
    spa->dirRev = spA.dirRev;
    spa->cFactor = 0.0;
#if 0
    spindleAccelCalc(spa);
#endif
   }
  }
 }
}

// __attribute__((optimize("O0")))
void spindleInit(P_SPINDLE spa, int dist, int dir)
{
 if (DBG_SETUP)
  printf("\nSpindleInit %s\n", spa->label);

 P_SPINDLEISR s = &sp;
 if (s->active == 0)		/* if spindle not active */
 {
  spindleTmrStop();		/* make sure timer stopped */
  spindleTmrClrIE();		/* disable interrupts */
  spindleTmrClrIF();		/* clear interrupt flag */
  dbgSpStopClr();

  if (dir == SP_FWD)		/* if forward */
   dirSpinFwd();		/* set forward */
  else				/* if reverse */
   dirSpinRev();		/* set reverse */

  s->dist = dist;		/* set distance */

  s->initialStep = spa->initialStep;
  s->finalStep = spa->finalStep;
  s->clocksStep = spa->clocksStep;
  s->stepsRev = spa->stepsRev;
  s->cFactor = spa->cFactor;
  auto tmp = (uint64_t) spa->cFactor;
  s->cFactor2 = tmp * tmp;
  s->stepsCycle = spa->stepsCycle;
  s->accel = 1;			/* set acceleration flag */
  s->decel = 0;			/* clear deceleration flag */
  s->accelStep = s->initialStep; /* set initial spindle step */
  s->lastCount = (int) (s->cFactor * sqrtf((float) s->accelStep)); /* last */
  s->accelStep++;		/* update step */
  int count = (int) (s->cFactor * sqrtf((float) s->accelStep)); /* first */
  unsigned int ctr = count - sp.lastCount; /* value to load in timer */
  int pre = 1;			/* initialize prescaler */
  if (DBG_SETUP)
   printf("count %d lastCount %d ctr %d\n", count, s->lastCount, ctr);
  while (ctr > 65535)		/* while counter out of range */
  {
   ctr >>= 1;			/* divide counter by two */
   pre <<= 1;			/* multiple prescaler by two */
  }
  sp.lastCount += ctr * pre;	/* update last count based on real count*/
  if (DBG_SETUP)
   printf("count %d lastCount %d pre %d ctr %d delta %d time %0.6f\n",
	  count, s->lastCount, pre, ctr, ctr * pre,
          (float) (ctr * pre) / (float) rVar.cfgFcy);
  sp.curCount = ctr;		/* save timer value */
  --pre;			/* subtract one for hw value */
  spindleTmrScl(pre);		/* load prescaler */
  sp.curCount = ctr;		/* save timer value */
  --ctr;			/* subtract one for load value */
  spindleTmrCnt(ctr);		/* load counter value */
  spindleTmrSet(ctr);		/* load maximum value */
  spindleTmrCCR(tmrStepWidth);	/* set step pulse width */
  spindleTmrPWMMode();		/* set pwm mode */
  SPINDLE_TMR->CCER = 0;
  spindleTmrPWMEna();		/* enable pwm output */
  spindleTmrSetIE();		/* enable interrupts */
 }
}

void spindleStart()
{
 if (DBG_SETUP)
  printf("\nspindle start\n");

 sp.findSync = 0;		/* set up to sync */
 sp.initSync = 1;		/* to index pulse */
 sp.active = 1;			/* indicate spindle active */
 indexTmrCntClr();		/* clear index timer */
 rVar.revCounter = 0;		/* and revolution counter */

 if (rVar.stepperDrive)		/* if using stepper drive */
 {
  if (DBG_P)
   printf("timer %d psc %u arr %u cnt %u\n", SPINDLE_TIMER,
	  (unsigned int) SPINDLE_TMR->PSC, (unsigned int) SPINDLE_TMR->ARR,
	  (unsigned int) SPINDLE_TMR->CNT);

  spindleTmrStart();		/* start spindle timer */
  putBufStrX("S\n");
  dbgSpStopSet();

  if (rVar.motorTest)		/* if testing motor */
  {
#if 0
   cmpTmr.encCycLen = 5;
   cmpTmr.intCycLen = 4;
   syncStart();			/* start encoder */
#endif
  }
 }
 else				/* if using motor drive */
 {
  lastRevCount = 0;
  rVar.revCounter = 0;
  rVar.lastIndexPeriod = 0;	/* clear last index period */

  if (rVar.cfgSwitch)		/* if spindle switched */
  {
   spFwdSet();			/* turn on spindle */
   if (DBG_SETUP)
    printf("spFwd %d\n", spFwdRead());
  }

  if (rVar.megaSim == 0)
  {
   if (rVar.cfgVarSpeed)		/* if var speed */
   {
    pwmTmrPWMEna();		/* start pwm */
   }
  }
#if defined(MEGAPORT)
  else
  {
   putMega(1);
   char ch = MEGA_ENC_START;
   sndhexMega((const unsigned char *) &ch, sizeof(ch), '\r');
  }
#endif	/* MEGAPORT */
 }
}

void spindleUpdate()
{
 if (DBG_SETUP)
  printf("\nspindle update\n");

 if (rVar.stepperDrive)		/* if stepper drive */
 {
 }
 else				/* if not stepper drive */
 {
  if (rVar.cfgVarSpeed)		/* if variable speed */
  {
   setSpindleSpeed(lrintf(rVar.spRpm)); /* set spindle speed */
  }
 }
}

void spindleStop()
{
 if (DBG_SETUP)
  printf("\nspindle stop\n");

 if (rVar.stepperDrive)
 {
  sp.accel = 0;			/* clear acceleration flag */
  sp.decel = 1;			/* set deceleration flag to stop */
  dbgSpStopSet();
  syncStop();
 }
 else
 {
  if (rVar.cfgSwitch)		/* if switched spindle */
  {
   spFwdClr();
   spRevClr();
  }

  if (rVar.cfgMega == 0)
  {
   if (rVar.cfgVarSpeed)	/* if variable speed */
   {
    if constexpr (PWM_TIMER != USEC_TIMER)
    {
     pwmTmrStop();		/* stop timer */
    }
    pwmTmrPWMDis();		/* disable pwm */
   }
  }
#if defined(MEGAPORT)
  else
  {
   if (rVar.megaSim == 0)
   {
    if (rVar.cfgVarSpeed)	/* if variable speed */
    {
     if constexpr (PWM_TIMER != USEC_TIMER)
     {
      pwmTmrStop();		/* stop timer */
     }
     pwmTmrPWMDis();		/* disable pwm */
    }
   }
   else
   {
    putMega(1);
    char ch = MEGA_ENC_STOP;
    sndhexMega((const unsigned char *) &ch, sizeof(ch), '\r');
   }
  }
#endif  /* MEGAPORT */
 }
}

void cmpTmrSetup()
{
 cmpTmrClrIE();			/* disable update interrupts */
 cmpTmrCntClr();		/* clear counter */
 cmpTmrSet(0xffff);		/* set count to maximum */
 cmpTmrScl(cmpTmr.preScale - 1); /* set prescaler */
 cmpTmrCap1EnaSet();		/* enable capture from encoer */
 cmpTmrCap1SetIE();		/* enable capture interrupt */
 cmpTmr.intClocks = 0;		/* clear clocks in current cycle */
 cmpTmr.measure = 0;		/* clear measure flag */
 cmpTmr.stop = 0;		/* clear stop flag */
}

void syncSetup()
{
 cmpTmr.encCycLen = rVar.lSyncCycle;
 cmpTmr.encCycLen = rVar.lSyncOutput;
 cmpTmr.preScale = rVar.lSyncPrescaler;
}

void syncMeasure()
{
 syncStop();			/* stop encoder */

 if (DBG_SETUP)
  printf("syncMeasure\n");

 rVar.capTmrEnable = 1;		/* enable capture timer */

 cmpTmr.encCycLen = ARRAY_LEN;	/* initialize cycle length */
 cmpTmr.cycleClocks = 0;	/* clear cycle clocks */
 cmpTmr.lastEnc = 0;		/* clear last encoder vale */
 memset(&cmpTmr.delta, 0, sizeof(cmpTmr.delta)); /* clear delta array */

 cmpTmr.encPulse = cmpTmr.encCycLen; /* set number to count */
 cmpTmr.measure = 1;		/* set measurement flag */

 cmpTmrClrIE();			/* disable update interrupts */
 cmpTmrCntClr();		/* clear counter */
 cmpTmrSet(0xffff);		/* set count to maximum */
 cmpTmrScl(0);			/* set prescaler */
 cmpTmrCap1EnaSet();		/* enable capture from encoer */
 cmpTmrCap1SetIE();		/* enable capture interrupt */
 cmpTmr.intClocks = 0;		/* clear clocks in current cycle */
 cmpTmrStart();			/* start capture timer */
}

void syncCalculate()
{
 if (DBG_SETUP)
  printf("syncCalculatee\n");

 uint64_t n = clocksMin * cmpTmr.encCycLen;
 uint64_t d = ((uint64_t) cmpTmr.cycleClocks * rVar.encPerRev);
 auto rpm = (uint16_t) (n / d);

 uint32_t pulseMinIn = rVar.encPerRev * rpm;
 uint32_t pulseMinOut = (pulseMinIn * rVar.lSyncOutput) / rVar.lSyncCycle;
 auto clocksPulse = (uint32_t) (clocksMin / pulseMinOut);
 rVar.lSyncPrescaler = clocksPulse >> 16;

 if (DBG_SETUP)
  printf("n %lld d %lld rpm %d preScaler %d\n",
	 n, d, rpm, rVar.lSyncPrescaler);

 rVar.lSyncPrescaler += 1;
}

void syncStart()
{
 syncStop();			/* stop encoder */

 rVar.capTmrEnable = 1;		/* enable capture timer */

 cmpTmr.encCycLen = rVar.lSyncCycle;
 cmpTmr.intCycLen = rVar.lSyncOutput;
 cmpTmr.preScale = rVar.lSyncPrescaler;

 if (DBG_SETUP)
  printf("syncStart cycle %d output %d preScale %u\n",
	 cmpTmr.encCycLen, cmpTmr.intCycLen, cmpTmr.preScale);

 intTmrCntClr();		/* clear counter */

 cmpTmr.startDelay = (uint16_t) ((rVar.cfgFcy * START_DELAY) / 1000000l - 1);
 intTmrSet(cmpTmr.startDelay);	/* set to initial delay */

 intTmrScl(cmpTmr.preScale - 1); /* set prescaler */
 intTmrSetIE();			/* enable interrupts */

 cmpTmr.cycleClocks = 0;	/* clear cycle clocks */
 cmpTmr.lastEnc = 0;		/* clear last encoder vale */
 memset(&cmpTmr.delta, 0, sizeof(cmpTmr.delta)); /* clear delta array */

 cmpTmr.encClocks = 0;		/* clear clocks in current cycle */

 cmpTmr.encPulse = cmpTmr.encCycLen; /* initialize encoder counter */
 cmpTmr.intPulse = cmpTmr.intCycLen; /* initialize internal counter */

#if DBG_SYNC_COUNT
 cmpTmr.encCount = 0;		/* clear counters */
 cmpTmr.intCount = 0;
 cmpTmr.cycleCount = 0;
 cmpTmr.missedStart = 0;	/* clear missed flag */
#endif

 cmpTmrSetup();

 cmpTmr.startInt = 1;		/* start internal timer */
 if (DBG_INT)
 {
  dbgCycEndSet();
 }
#if DBGTRK
 dbgTrk = true;
#endif

 cmpTmrStart();			/* start capture timer */

#if 0
 printf("internal timer\n");
 tmrInfo(INT_TMR);
 printf("compare timer\n");
 tmrInfo(CMP_TMR);
#endif
}

void syncStop()
{
 if (DBG_SETUP)
  printf("syncStop\n");

 rVar.capTmrEnable = 0;		/* disable capture timer code */

 cmpTmrStop();			/* stop timer */
 cmpTmrCntClr();
 cmpTmrClrIE();			/* clear interrupts */
 cmpTmrClrIF();

 cmpTmrCap1ClrIE();		/* clear capture 1 interrupts */
 cmpTmrCap1ClrIF();
 cmpTmrOCP1Clr();

#if 0
 cmpTmrCap2ClrIE();		/* clear capture 2 interrupts */
 cmpTmrCap2ClrIF();
 cmpTmrOCP2Clr();
#endif

#if 0
 printf("compare timer\n");
 tmrInfo(CMP_TMR);
#endif

 intTmrStop();			/* stop internal timer */
 intTmrCntClr();
 intTmrClrIE();
 intTmrClrIF();
}

void encoderStart()
{
 syncStop();
 if (DBG_SETUP)
  printf("encoderStart\n");

 cmpTmrSetup();
 cmpTmr.preScale = 1;
}

void encoderSWIEnable(int enable)
{
 if (enable)			/* if enabling interrupt */
 {
  EXTI->PR = encIRQ_Bit;       /* clear pending interrupt */
  HAL_NVIC_SetPriority(encIRQn, 5, 0); /* set interrupt priority */
  NVIC_EnableIRQ(encIRQn);     /* enable encoder interrupts */
  EXTI->IMR |= encIRQ_Bit;     /* enable in mask register */
 }
 else				/* if disabling interrupt */
 {
  EXTI->IMR &= ~encIRQ_Bit;     /* enable in mask register */
  NVIC_DisableIRQ(encIRQn);	/* disable encoder interrupts */
 }
}

void spindleJog()
{
 P_SPINDLEISR s = &sp;
 __disable_irq();		/* disable interrupt */
 if (s->active == 0)		/* if spindle not active */
 {
  __enable_irq();		/* enable interrupts */
  P_SPINDLE spa = &spJA;	/* pointer to jog */
  if (spa->cFactor == 0.0)	/* if acceleration not setup */
  {
   spindleAccelCalc(spa);
  }
  float time = rVar.spJogTimeInitial - spa->time; /* time after accel */
  auto d = (int) (spa->steps + lrintf(spa->stepsSec * time)); /* distance */
  s->jogInc = (int) (rVar.spJogTimeInc * spa->stepsSec); /* save increment */
  s->maxDist = (int) (rVar.spJogTimeMax * spa->stepsSec); /* save maximum */

  if (DBG_P)
   printf("spindleJog dist %5d inc %5d max %5d\n",
	  d, s->jogInc, s->maxDist);

  int dir = rVar.spJogDir == 0 ? SP_FWD : SP_REV;
  spindleInit(spa, d, dir);
  spindleStart();
 }
 else				/* if spindle active */
 {
  s->dist += s->jogInc;		/* add to distance */
  if (s->dist > s->maxDist)	/* if distance greater than max */
   s->dist = s->maxDist;	/* set to maximum */
  if (s->decel)			/* if decelerating */
  {
   s->decel = 0;		/* clear decel flag */
   s->accel = 1;		/* set accel flag */
  }
  __enable_irq();		/* enable interrupts */
 }
}

void spindleJogSpeed()
{
 P_SPINDLEISR s = &sp;
 __disable_irq();		/* disable interrupt */
 P_SPINDLE spa = &spJSA;	/* pointer to jog */
 if ((s->active == 0)		/* if spindle not active */
 &&  (rVar.spJogRpm != 0.0))
 {
  __enable_irq();		/* enable interrupts */
  int dir = SP_FWD;
  if (rVar.spJogRpm < 0)
  {
   rVar.spJogRpm = -rVar.spJogRpm;
   dir = SP_REV;
  }
  spa->maxRPM = rVar.spJogRpm;	/* set maximum speed */
  spindleAccelCalc(spa);	/* calculate acceleration */
  float time = rVar.spJogTimeInitial - spa->time; /* time after accel */
  int d = (int) (spa->steps + (int) (spa->stepsSec * time)); /* initial steps */
  s->jogInc = (int) (2 * rVar.spJogTimeInc * spa->stepsSec); /* save inc */
  s->maxDist = (int) (2 * rVar.spJogTimeMax * spa->stepsSec); /* save max */

  if (DBG_P)
   printf("spindleJog dist %5d inc %5d max %5d\n",
	  d, s->jogInc, s->maxDist);

  spindleInit(spa, d, dir);
  spindleStart();
 }
 else				/* if spindle active */
 {
  __enable_irq();		/* enable interrupts */
  if (rVar.spJogRpm == 0.0)
  {
   if (sp.accelStep < 5)
   {
    spIsrStop();
   }
   else
   {
    sp.accel = 0;
    sp.decel = 1;
    sp.dist = sp.accelStep;
   }
  }
  else
  {
   if (rVar.spJogRpm != spa->maxRPM)	/* if jog speed different */
   {
    spindleSpeedCalc(rVar.spJogRpm);	/* calculate acceleration */
    s->jogInc = (int) (2 * rVar.spJogTimeInc * spa->stepsSec); /* save inc */
    s->maxDist = (int) (2 * rVar.spJogTimeMax * spa->stepsSec); /* save max */
   }
   __disable_irq();		/* disable interrupt */
   s->dist += s->jogInc;	/* add to distance */
   if (s->dist > s->maxDist)	/* if distance greater than max */
    s->dist = s->maxDist;	/* set to maximum */
#if 0
   if (s->decel)		/* if decelerating */
   {
    s->decel = 0;		/* clear decel flag */
    s->accel = 1;		/* set accel flag */
   }
#endif
   __enable_irq();		/* enable interrupts */
  }
 }
}

void spindleSpeedCalc(float finalRPM)
{
 P_SPINDLEISR s = &sp;
 P_SPINDLE spa = &spJSA;
 spa->maxRPM = finalRPM;
 int stepsSec = (int) ((finalRPM * (float) spa->stepsRev) / 60.0);
 spa->stepsSec = (float) stepsSec;
 int clocksStep = (int) (rVar.cfgFcy / stepsSec);

 if (DBG_P)
  printf("finalRPM %0.2f stepsSec %d clocksStep %d\n",
	 finalRPM, stepsSec, clocksStep);

 int finalStepsSec = (int) (((float) spa->stepsRev * finalRPM) / 60.0);
 float finalTime = (float) finalStepsSec / spa->stepsSec2;
 auto finalStep = (unsigned int) (((float) finalStepsSec * finalTime) / 2.0);

 if (DBG_P)
  printf("finalStepsSec %d finalTime %5.3f finalStep %d accelStep %d\n",
	 finalStepsSec, finalTime, finalStep, s->accelStep);

 int aClocksStep;
 if (finalStep > 0)
 {
  if (s->accelStep > finalStep)
  {
   aClocksStep = lrintf(spa->cFactor *
           (sqrtf((float) finalStep) - sqrtf((float) (finalStep - 1))));
  }
  else
  {
   aClocksStep = lrintf(spa->cFactor * (sqrtf((float) (finalStep + 1)) -
				   sqrtf((float) finalStep)));
  }
  clocksStep = aClocksStep;

  if (DBG_P)
   printf("cFactor %0.2f aClocksStep %d finalStepsSec %d\n",
	  spa->cFactor, aClocksStep, finalStepsSec);
 }
 else
  finalStep = 1;

 __disable_irq();		/* disable interrupt */
 if (s->dist != 0)
 {
  unsigned int isrStep = s->accelStep;
  s->lastCount = (int) (s->cFactor * sqrtf((float) isrStep));
  if (isrStep < finalStep)
  {
   putBufStrX("A\n");
   s->decel = 0;
   s->accel = 1;
   s->finalStep = finalStep;
  }
  else
  {
   putBufStrX("D\n");
   s->accel = 0;
   s->decel = -1;
   s->initialStep = finalStep;
  }
  s->clocksStep = clocksStep;
 }
 __enable_irq();		/* enable interrupts */
 if (DBG_P)
  printf("initialStep %d accelStep %d finalStep %d\n",
	 s->initialStep, s->accelStep, s->finalStep);
}

float stepTime(float cFactor, unsigned int step)
{
 int c0 = (int) (cFactor * sqrtf((float) step));
 int c1 = (int) (cFactor * sqrtf((float) (step + 1)));
 int delta = c1 - c0;
 float time = (float) delta / (float) rVar.cfgFcy;
 return(time);
}

void spindleAccelCalc(P_SPINDLE s)
{
 if (DBG_SETUP)
  printf("\nspindleAccelCalc %s minRPM %3.0f maxRPM %3.0f\n",
	 s->label, s->minRPM, s->maxRPM);

 s->stepsRev = s->motorSteps * s->microSteps;

 s->stepsSec = (s->maxRPM * (float) s->stepsRev) / 60.0f;
 s->clocksStep = lrintf((float) rVar.cfgFcy / s->stepsSec);
 s->clocksRev = s->stepsRev * s->clocksStep;

 if (DBG_P)
  printf("clocksStep %d clocksRev %d\n",
	 s->clocksStep, s->clocksRev);

 float stepsSecMin = (s->minRPM * (float) s->stepsRev) / 60.0f;
 float stepsSecMax = (s->maxRPM * (float) s->stepsRev) / 60.0f;
 float deltaV = stepsSecMax - stepsSecMin;

 if (DBG_P)
  printf("deltaV %4.1f stepsSecMin %4.1f stepsSecMax %4.1f\n",
	 deltaV, stepsSecMin, stepsSecMax);

 if (ACCEL_TIME)
 {
  s->stepsSec2 = deltaV / s->aTime;
  s->accel =(s->stepsSec2 / (float) s->stepsRev) * 60.0f;

  if (DBG_P)
   printf("accel %0.3f rpm per sec\n", s->accel);
 }
 else
 {
  s->stepsSec2 = (s->accel / 60.0f) * (float) s->stepsRev;
  s->aTime = deltaV / s->stepsSec2;
  if (DBG_P)
   printf("stepsSec2 %0.0f aTime %0.3f accel %0.3f rpmSec\n",
	  s->stepsSec2, s->aTime, s->accel);
 }

 float accelMinTime = stepsSecMin / s->stepsSec2;
 float accelMaxTime = stepsSecMax / s->stepsSec2;

 if (DBG_P)
  printf("accelMinTime %5.5f accelMaxTime %5.2f\n",
	 accelMinTime, accelMaxTime);

 s->initialStep = lrintf((stepsSecMin * accelMinTime) / 2);
 s->finalStep = lrintf((stepsSecMax * accelMaxTime) / 2);

 if (DBG_P)
  printf("initialStep %d finalStep %d\n", s->initialStep, s->finalStep);

 s->time = deltaV / s->stepsSec2;
 s->steps = s->finalStep - s->initialStep;
 s->clocks = lrintf(s->time * (float) rVar.cfgFcy);
 s->revs = (float) s->steps / (float) s->stepsRev;

 if (DBG_P)
  printf("stepsSec2 %0.3f time %5.3f steps %d clocks %d revs %5.3f\n",
	 s->stepsSec2, s->time, s->steps, s->clocks, s->revs);

 float cFactor0 = (float) rVar.cfgFcy * sqrtf(2.0f) / sqrtf(s->stepsSec2);
 float cFactor1 = (float) s->clocksStep / (sqrtf((float) s->finalStep) -
					   sqrtf((float) s->finalStep - 1));
 s->cFactor = cFactor1;

 if (DBG_P)
 {
  printf( "cFactor0 %0.2f cFactor1 %0.2f\n", cFactor0, cFactor1);
  printf("initialStepTime %0.6f finalStepTime %0.6f\n",
	 stepTime(cFactor1, s->initialStep),
	 stepTime(cFactor1, s->finalStep - 1));
 }

 int lastCount = (int) (s->cFactor * sqrtf((float) s->initialStep));
 float lastTime = ((float) lastCount) / (float) rVar.cfgFcy;

 if (DBG_P)
  printf("MinSteps %4d lastCount %8d lastTime %8.6f\n",
	 s->initialStep, lastCount, lastTime);

 if (false)
 {
  int lastCtr = 0;
  unsigned int step;
  for (step = s->initialStep + 1; step <= s->finalStep; step++)
  {
   int count = (int) (s->cFactor * sqrtf((float) step));
   int ctr = count - lastCount;
   float time = ((float) count) / (float) rVar.cfgFcy;
   float delta = time - lastTime;
   float freq = 1.0f / delta;
   float rpm = (freq / (float) s->stepsRev) * 60.0f;

   if ((step % 50) == 0)
    if (DBG_P)
     printf("step %4d count %9d %7d %5d t %8.6f %8.6f f %8.2f rpm %4.1f\n",
	    step, count, ctr, ctr - lastCtr, time, delta, freq, rpm);

   lastCount = count;
   lastCtr = ctr;
   lastTime = time;
  }
  lastCount = (int) (s->cFactor * sqrtf((float) s->finalStep));
  lastTime = (float) lastCount / (float) rVar.cfgFcy;
  if (DBG_P)
   printf("accelMaxSteps %4d lastCount %8d lastTime %8.6f\n",
	  s->finalStep, lastCount, lastTime);
 }
 int finalCount = (int) (s->cFactor * sqrtf((float) s->finalStep));
 finalCount -= (int) (s->cFactor * sqrtf((float) s->finalStep - 1));

 if (DBG_P)
  printf("finalCount %d clocksStep %d\n", finalCount, s->clocksStep);
}

void slaveEna()
{
 if (rVar.spindleEncoder == 0)	/* *ok* if not using spindle encodeer */
 {
  if (DBG_SETUP)
   printf("\nslave enable 0 z %d x %d\n", zIsr.sync, xIsr.sync);

  unsigned int tmp = sp.stepsRev - 1;	/* get maximum spindle step number */
  if (zIsr.sync)		/* if z sync */
  {
   sp.zStart = tmp - zIsr.accelSpSteps; /* set start pos */
   zIsr.cycleCounter = zIsr.accelSpSteps == 0 ? 1 : 0;

   if (DBG_P)
    printf("slaveEna z start %d\n", sp.zStart);

   sp.startAxis |= STARTZ;	/* set axis flag */
  }

  if (xIsr.sync)		/* if x sync */
  {
   sp.xStart = tmp - xIsr.accelSpSteps; /* set start pos */
   xIsr.cycleCounter = xIsr.accelSpSteps == 0 ? 1 : 0;

   if (DBG_P)
    printf("slaveEna x start %d\n", sp.xStart);

   sp.startAxis |= STARTX;	/* set axis flag */
  }

  if ((sp.startAxis & (STARTZ | STARTX)) != 0) /* if synchronized */
   sp.startAxis |= START_TRIG;	/* set flag to trigger slave mode */
 }
 else				/* *chk* if using spindle encoder */
 {
  if (DBG_SETUP)
   printf("\nslave enable 1  z %d x %d\n", zIsr.syncInit, xIsr.syncInit);

  __disable_irq();		/* disable interrupts */
  if (zIsr.syncInit)		/* if initialized for sync op */
  {
   zIsr.syncStart = zIsr.syncInit; /* set to start on next index */
   zIsr.syncInit = 0;		/* clear flag */
  }

  if (xIsr.syncInit)		/* if initialized for sync op */
  {
   xIsr.syncStart = xIsr.syncInit; /* set to start on next index */
   xIsr.syncInit = 0;		/* clear flag */
  }
  __enable_irq();		/* enable interrupts */
 }
}

void zInit(P_AXIS ax)
{
 ax->axis = 'a';
 ax->pitch = Z_LS_PITCH;
 ax->microSteps = Z_MICRO_STEPS;
 ax->motorSteps = Z_MOTOR_STEPS;
 ax->stepsInch = (int) ((float) (ax->microSteps * ax->motorSteps) / ax->pitch);

 if (DBG_P)
  printf("stepsInch %d\n", ax->stepsInch);
}

void accelInit(P_AXIS ax, P_ACCEL ac)
{
 memset(ac, 0, sizeof(T_ACCEL));
 ac->stepsInch = ax->stepsInch;
}

unsigned int turnInit(P_ZXISR isr, P_ACCEL ac, int dir, unsigned int dist)
{
 isr->cFactor = ac->cFactor;
 isr->clocksStep = ac->clocksStep;
 isr->initialStep = ac->initialStep;
 isr->finalStep = ac->finalStep;

 if (DBG_P)
 {
  printf("\nturnInit %s\n", ac->label);
  printf("cFactor %0.1f clocksStep %d initialStep %d finalStep %d\n",
	 isr->cFactor, isr->clocksStep, isr->initialStep, isr->finalStep);
 }

 isr->counterStep1 = ac->clocksStep - 1;
 isr->counterStep2 = ac->clocksStep + 1 - 1;

 isr->d = ac->d;
 isr->sum = isr->d;
 isr->incr1 = ac->incr1;
 isr->incr2 = ac->incr2;
 isr->x = 0;
 isr->y = 0;
 isr->stepsCycle = ac->stepsCycle;
 isr->accelSpSteps = ac->accelSpSteps;

 isr->useDro = ac->useDro;
 isr->steps = 0;
 isr->done = 0;
 isr->dir = dir;
 isr->remCount = 0;
 isr->dist = dist;
 isr->sync = isr->incr1 != 0 ? 1 : -1;
 isr->decel = 0;
 unsigned int ctr;
 if (ac->cFactor != 0)
 {
  isr->accel = 1;
  isr->accelStep = isr->initialStep;
  ctr = (int) (isr->cFactor * sqrtf((float) isr->accelStep));
  isr->accelStep++;
  isr->lastCount = (int) (isr->cFactor * sqrtf((float) isr->accelStep));
  ctr = isr->lastCount - ctr;
  ctr -= ac->accelSpRem / 2;
  isr->clockSum = ctr;

  if (DBG_P)
   printf("initialCounter %d initialInterval %8.6f\n",
	  ctr, ((float) ctr) / (float) rVar.cfgFcy);
 }
 else
 {
  ctr = ac->clocksStep;
  isr->clockSum = 0;
 }
 isr->curCount = ctr;
 --ctr;
 return(ctr);
}

void encTurnInit(P_ZXISR isr, P_ACCEL ac, int dir, unsigned int dist)
{
 if (DBG_P)
 {
  float d = (float) dist / (float) ac->stepsInch;
  float rev = d / ac->pitch;
  printf("\nencTurnInit %s\n", ac->label);
  printf("dist %7.4f steps %d pitch %6.4f rev %6.2f spSteps %ld\n",
	 d, dist, ac->pitch, rev, lrintf(rev * (float) rVar.encPerRev));
 }

 isr->d = ac->d;
 isr->incr1 = ac->incr1;
 isr->incr2 = ac->incr2;
 isr->delta = ac->delta;
 isr->x = 0;
 isr->y = 0;

 isr->steps = 0;
 isr->done = 0;
 isr->dir = dir;
 isr->dist = dist;
}

void syncTurnInit(P_ZXISR isr, P_ACCEL ac, int dir, unsigned int dist)
{
 if (DBG_P)
 {
  float d = (float) dist / (float) ac->stepsInch;
  float rev = d / ac->pitch;
  printf("\nsyncTurnInit %s\n", ac->label);
  printf("dist %7.4f steps %d pitch %6.4f rev %6.2f spSteps %ld\n",
	 d, dist, ac->pitch, rev, lrintf(rev * (float) rVar.encPerRev));
 }

 isr->steps = 0;
 isr->done = 0;
 isr->dir = dir;
 isr->dist = dist;
}

unsigned int taperInit(P_ZXISR isr, P_ACCEL ac, int dir)
{
 if (DBG_P)
  printf("\ntaperInit %s\n", ac->label);

 isr->dir = dir;
 unsigned int ctr = ac->clocksStep;
 isr->clocksStep = ctr;

 isr->counterStep1 = ctr - 1;
 isr->counterStep2 = ctr + 1 - 1;

 isr->d = ac->d;
 isr->sum = ac->d;
 isr->incr1 = ac->incr1;
 isr->incr2 = ac->incr2;
 isr->x = 0;
 isr->y = 0;
 isr->stepsCycle = ac->stepsCycle;

 isr->cycleCounter = 0;
 isr->sync = isr->incr1 != 0 ? 1 : -1;
 isr->taper = TAPER_SLAVE;

 isr->curCount = ctr;
 --ctr;
 return(ctr);
}

void encTaperInit(P_ZXISR isr, P_ACCEL ac, int dir, int syncInit)
{
 if (DBG_P)
  printf("\nencTaperInit %s dir %d syncInit %d\n", ac->label, dir, syncInit);

 isr->dir = dir;

 isr->syncInit = syncInit;
 isr->d = ac->d;
 isr->sum = ac->d;
 isr->incr1 = ac->incr1;
 isr->incr2 = ac->incr2;
 isr->x = 0;
 isr->y = 0;

 isr->taper = TAPER_SLAVE;
}

unsigned int moveInit(P_ZXISR isr, P_ACCEL ac, int dir, unsigned int dist)
{
 if (DBG_P)
 {
  printf("\nmoveInit %s", ac->label);
  if (ac->useDro)
   printf(" useDro %d dir %2d",
	  ac->useDro, dir);
  printf("\n");
 }

 isr->initialStep = ac->initialStep;
 isr->finalStep = ac->finalStep;
 isr->clocksStep = ac->clocksStep;
 isr->cFactor = ac->cFactor;

 isr->useDro = ac->useDro;	/* copy use dro flag */
 ac->useDro = 0;		/* clear source of flag */
 isr->droTarget = ac->droTarget;
 isr->steps = 0;
 isr->done = 0;
 isr->home = 0;
 isr->doneHome = 0;
 isr->dir = dir;
 isr->remCount = 0;
 isr->dist = dist;
 isr->sync = 0;
 isr->decel = 0;
 unsigned int ctr;
 if (ac->steps != 0)
 {
  isr->accel = 1;
  isr->accelStep = isr->initialStep;
  ctr = (int) (isr->cFactor * sqrtf((float) isr->accelStep));
  isr->accelStep++;
  isr->lastCount = (int) (isr->cFactor * sqrtf((float) isr->accelStep));
  ctr = isr->lastCount - ctr;
  isr->finalCtr = ctr;

  if (DBG_P)
   printf("moveInit accel ctr %d\n", ctr);
 }
 else
 {
  isr->accelStep = 0;
  isr->accel = 0;
  ctr = ac->clocksStep;

  if (DBG_P)
   printf("moveInit ctr %d\n", ctr);
 }
 isr->curCount = ctr;
 --ctr;
 return(ctr);
}

void jogMove(P_MOVECTL mov, int dir)
{
 if (mov->state == AXIS_IDLE)	/* if not moving */
 {
  if (mov->limitsEna)		/* if limits enabled */
  {
   if (mov->limitDir != 0)	/* if at a limit */
   {
    if (rVar.limitOverride == 0) /* if not overriding limits */
    {
     if (((mov->limitDir > 0) && (dir > 0)) /* if same direction as limit */
     ||  ((mov->limitDir < 0) && (dir < 0)))
     {
      printf("%c at limit\n", mov->axisName);
      return;
     }
     mov->limitMove = 1;	/* set moving off limit flag */
    }
   }
  }
  P_ACCEL ac = mov->acJog;	/* pointer to jog */
#if 0
  float time = jogTimeInitial - ac->time; /* time after accel */
  int d = ac->steps + (int) (ac->stepsSec * time); /* initial steps */
#endif
  auto stepsSec = (float) ac->stepsSec;
  int d = (int) (rVar.jogTimeInitial * stepsSec); /* initial steps */
  mov->iniDist = d;		/* save initial distance */
  if (dir < 0)			/* if direction negative */
   d = -d;			/* set to negative */
  mov->stop = 0;		/* clear stop flag */
  mov->jogInc = (int) (rVar.jogTimeInc * stepsSec); /* save increment */
  mov->maxDist = (int) (rVar.jogTimeMax * stepsSec); /* save maximum */

  if (DBG_P)
  {
   auto stepsInch = (float) ac->stepsInch;
   printf("JSpeed dir %d dist %0.4f inc %0.4f max %0.4f\n",
	  dir, (float) d / stepsInch ,  (float) mov->jogInc / stepsInch,
          (float) mov->maxDist / stepsInch);
  }

  mov->moveRel(d, mov->jogCmd);	/* start movement */
 }
 else if (mov->state == AXIS_WAIT_BACKLASH) /* if waiting for backlash */
 {
 }
 else				/* if moving */
 {
  if (mov->dir == DIR_POS)	/* if currently positive */
  {
   if (dir < 0)			/* if dir negative */
    return;			/* exit */
  }
  else				/* if currently negative */
  {
   if (dir > 0)			/* if dir positive */
    return;			/* exit */
  }
  P_ZXISR isr = mov->isr;	/* pointer to isr control block */
  __disable_irq();		/* disable interrupt */
  if (isr->done)		/* if movement stopped */
  {
   __enable_irq();		/* enable interrupts */
  int d = mov->iniDist;		/* get initial distance */
  if (dir < 0)			/* if distance negative */
    d = -d;			/* make negative */
   mov->moveRel(d, mov->jogCmd); /* start movement */
  }
  else				/* if still moving */
  {
   isr->dist += mov->jogInc;	/* add to distance */
   if (isr->dist > mov->maxDist) /* if less than max distance */
    isr->dist = mov->maxDist;	/* set to maximum */
   if (isr->decel)		/* if decelerating */
   {
    isr->decel = 0;		/* clear decel flag */
    isr->accel = 1;		/* set to acceleration */
   }
   __enable_irq();		/* enable interrupts */
  }
 }
}

void jogMpg1(P_MOVECTL mov)
{
 if ((jogPause & DISABLE_JOG)	/* if jogging disabled */
 &&  ((jogPause & mov->jogFlag) == 0)) /* and jogging not enabled */
  return;

 P_JOGQUE jog = mov->jogQue;	/* get queue pointer */
 int dir = 0;
 __disable_irq();		/* disable interrupt */
 if (jog->count != 0)		/* if anything in count */
 {
  --jog->count;			/* count removal */
  dir = (int) jog->buf[jog->emp];	/* get value */
  __enable_irq();		/* enable interrupts */
  jog->emp++;			/* update pointer */
  if (jog->emp >= MAXJOG)	/* if at end of queue */
   jog->emp = 0;		/* reset to start */
 }
 else				/* if nothing in que */
 {
  __enable_irq();		/* enable interrupts */
  return;			/* and exit */
 }

 if (mov->mpgFlag)		/* if direction inverted */
  dir = -dir;			/* invert distance */

 if (mov->dir != dir)		/* if direction change */
 {
  if (dir == 0)			/* if no direction */
   return;			/* exit */
  mov->dir = dir;		/* set direction */
  if (dir > 0)			/* if moving positive */
   mov->dirFwd();		/* set to forward */
  else
   mov->dirRev();		/* set to reverse */

  int backlashSteps = mov->axis->backlashSteps;
  if (backlashSteps != 0)	/* and backlash present */
  {
   mov->moveInit(mov->acMove, 0, backlashSteps); /* setup backlash move */
   mov->start();		/* start move */
  }
 }
 else				/* if no dir change */
 {
  mov->pulse();			/* move a step */
 }
}

void jogMpg(P_MOVECTL mov)
{
 if ((jogPause & DISABLE_JOG)	/* if jogging disabled */
 &&  ((jogPause & mov->jogFlag) == 0)) /* and jogging not enabled */
  return;

 P_JOGQUE jog = mov->jogQue;	/* get queue pointer */
 int dist = 0;
 MPG_VAL val;
 if (mov->state == AXIS_IDLE)	/* if not moving */
 {
  dbgJogMPG0Set();

  __disable_irq();		/* disable interrupt */
  if (jog->count != 0)		/* if anything in count */
  {
   --jog->count;		/* count removal */
   val.intVal = (int) jog->buf[jog->emp]; /* get value */
   __enable_irq();		/* enable interrupts */
   jog->emp++;			/* update pointer */
   if (jog->emp >= MAXJOG)	/* if at end of queue */
    jog->emp = 0;		/* reset to start */
  }
  else				/* if nothing in que */
  {
   __enable_irq();		/* enable interrupts */
   dbgJogMPG0Clr();
   return;			/* and exit */
  }
  dist = (int) val.dir;

  if (mov->limitsEna)		/* if limits enabled */
  {
   if (mov->limitDir != 0)	/* if at a limit */
   {
    if (rVar.limitOverride == 0) /* if not overriding limits */
    {
     if (((mov->limitDir > 0) && (dist > 0)) /* if same direction as limit */
     ||  ((mov->limitDir < 0) && (dist < 0)))
     {
      printf("%c at limit\n", mov->axisName);
      return;
     }
     mov->limitMove = 1;	/* set moving off limit flag */
    }
   }
  }

  if (mov->mpgFlag)		/* if direction inverted */
   dist = -dist;		/* invert distance */
  mov->maxDist = *(mov->mpgJogMax); /* set maximum distance */
  dist *= *(mov->mpgJogInc);	/* calculate distance */
  //printf("mpgJog 0 dist %4d\n", dist);
  mov->moveRel(dist, mov->jogCmd); /* start relative move */
  dbgJogMPG0Clr();
 }
 else if (mov->state == AXIS_WAIT_BACKLASH) /* if waiting for backlash */
 {
 }
 else 				/* if moving */
 {
  dbgJogMPG1Set();
  if (mov->dir == DIR_POS)	/* if currently positive */
  {
   if (dist < 0)		/* if dir negative */
   {
    dbgJogMPG1Clr();
    return;			/* exit */
   }
  }
  else				/* if currently negative */
  {
   if (dist > 0)		/* if dir positive */
   {
    dbgJogMPG1Clr();
    return;			/* exit */
   }
  }
  __disable_irq();		/* disable interrupt */
  if (jog->count != 0)		/* if anything in count */
  {
   --jog->count;		/* count removal */
   val.intVal = (int) jog->buf[jog->emp]; /* get value */
   __enable_irq();		/* enable interrupts */

   jog->emp++;			/* update pointer */
   if (jog->emp >= MAXJOG)	/* if at end of queue */
    jog->emp = 0;		/* reset to start */
   dist = (int) val.dir;	/* get distance */
   if (mov->mpgFlag)		/* if direction inverted */
    dist = -dist;		/* invert distance */
  }
  else				/* if nothing in que */
  {
   __enable_irq();		/* enable interrupts */
   dbgJogMPG1Clr();
   return;			/* and exit */
  }

  P_ZXISR isr = mov->isr;	/* pointer to isr control block */
  __disable_irq();		/* disable interrupt */
  if (isr->done)		/* if movement stopped */
  {
   dbgJogMPG2Set();
   __enable_irq();		/* enable interrupts */
   mov->maxDist = *(mov->mpgJogMax); /* set maximum distance */
   dist *= *(mov->mpgJogInc);	/* calculate distance */
   mov->moveRel(dist, mov->jogCmd); /* start relative move */
  }
  else				/* if isr active */
  {
   if (dist != mov->dir)	/* if direction changed */
   {
    isr->accel = 0;		/* clear acceleration */
    isr->decel = 1;		/* set deceleration */
    isr->dist = isr->accelStep; /* set distance to stop */
   }
   else				/* if same direction */
   {
    dbgJogMPG3Set();
    isr->dist += *(mov->mpgJogInc); /* add to distance */
    if (isr->dist > mov->maxDist) /* if greater than maximum */
     isr->dist = mov->maxDist;	/* set to maximum */
    //printf("mpgJog 1 dist %4d\n", isr->dist);
    if (isr->decel)		/* if decelerating */
    {
     isr->decel = 0;		/* stop decelerating */
     isr->accel = 1;		/* set to accelerating */
    }
   }
  }
  __enable_irq();		/* enable interrupts */
  dbgJogMPG1Clr();
  dbgJogMPG2Clr();
  dbgJogMPG3Clr();
 }
}

void jogMpg2(P_MOVECTL mov)
{
 if ((jogPause & DISABLE_JOG)	/* if jogging disabled */
 &&  ((jogPause & mov->jogFlag) == 0)) /* and jogging not enabled */
  return;

 P_JOGQUE jog = mov->jogQue;	/* get queue pointer */

 __disable_irq();		/* disable interrupt */
 if (jog->count == 0)		/* if nothing in queue */
 {
  __enable_irq();		/* enable interrupts */
  return;			/* and exit */
 }
 --jog->count;			/* count removal */
 MPG_VAL val;
 val.intVal = (int) jog->buf[jog->emp]; /* get value */
 __enable_irq();		/* enable interrupts */

 jog->emp++;			/* update pointer */
 if (jog->emp >= MAXJOG)	/* if at end of queue */
  jog->emp = 0;			/* reset to start */

 char dir = (int) val.dir;	 /* get direction */
 unsigned int delta = val.delta; /* mask off time delta */
 P_ZXISR isr = mov->isr;	/* pointer to isr info */

 if (rVar.jogDebug)
  printf("%2d %6d %3d\n", dir, delta, isr->dist);
 if (mov->mpgFlag)		/* if direction inverted */
  dir = -dir;			/* invert distance */

 unsigned int ctr;
 int dist = *mov->mpgJogInc;	/* read increment distance */
 if (dist == 0)			/* if continuous jog */
 {
  if (delta < mov->mpgUSecSlow)	/* if fast jog */
  {
   dist = mov->mpgStepsCount;	/* set counts */
  }
  else				/* if slow jog */
  {
   delta = mov->mpgUSecSlow;	/* use slow limit for interval */
   dist = 1;			/* set distance to 1 */
  }
  ctr = (delta * clksPerUSec) / dist; /* calculate new time value */

  __disable_irq();		/* disable interrupt */
  if (isr->dist != 0)		/* if currently active */
  {
   if (dir == mov->dir)		/* if direction same */
   {
    isr->dist += dist;		/* update distance */
    isr->clocksStep = ctr;	/* save counter value */
    mov->timer->ARR = ctr - 1;	/* set new counter value */
   }
   else				/* if direction change */
   {
    mov->isrStop('9');		/* stop movement */
   }
   __enable_irq();		/* enable interrupts */
   return;			/* and exit */
  }
 }
 else				/* if incremental jog */
 {
  ctr = (mov->mpgUSecSlow * clksPerUSec) / mov->mpgStepsCount; /* set ctr */

  __disable_irq();		/* disable interrupt */
  if (isr->dist != 0)		/* if active */
  {
   if (dir != isr->dir)		/* if direction change */
   {
    mov->isrStop('9');		/* stop movement */
   }
   __enable_irq();		/* enable interrupts */
   return;			/* exit */
  }
 }
 __enable_irq();		/* enable interrupts */

 if (mov->mpgBackWait == 0)	/* if not in backlash state */
 {
  if (dir != mov->dir)		/* if direction change */
  {
   mov->dir = dir;		/* save direction */
   if (dir > 0)			/* set direction hardware */
    mov->dirFwd();
   else
    mov->dirRev();

   int backlashSteps = mov->axis->backlashSteps; /* get backlash */
   if (backlashSteps != 0)	/* if non zero */
   {
    if (rVar.jogDebug)
     printf("%c b %d\n", mov->axisName, backlashSteps);
    mov->mpgBackDist = backlashSteps; /* set distance */
    mov->mpgBackWait = 1;	/* set to wait for backlash */
    dir = 0;			/* set to zero for no position update */
   }
   isr->dir = dir;		/* set isr direction */
  }
  else				/* if no direction change */
  {
   isr->dir = dir;		/* set isr direction */
  }

  mov->expLoc += dist * dir;	/* update expected loc */

  if (rVar.jogDebug)
   printf("%c %2d %2d %3d %u\n",
	  mov->axisName, mov->dir, isr->dir, dist, (unsigned int) ctr);

  isr->home = 0;		/* clear variables */
  isr->useDro = 0;
  isr->cFactor = 0;
  isr->accel = 0;
  isr->decel = 0;
  isr->sync = 0;

  isr->dist = dist;		/* set distance */
 }
 else
 {
  mov->mpgBackDist -= 1;	/* count of distance */
  if (mov->mpgBackDist == 0)	/* if finished backlash */
  {
   mov->mpgBackWait = 0;	/* get out of backlash state */
   isr->dir = mov->dir;		/* set direction */
  }
 }

 mov->hwEnable(ctr);		/* setup hardware */
 mov->start();			/* start */
}

enum MPG_STATE
{
 MPG_CHECK_QUE,
 MPG_DIR_CHANGE_WAIT,
 MPG_WAIT_BACKLASH
};

void jogMpg3(P_MOVECTL mov)
{
 if ((jogPause & DISABLE_JOG)	/* if jogging disabled */
 &&  ((jogPause & mov->jogFlag) == 0)) /* and jogging not enabled */
  return;

 if (mov->mpgState != mov->mpgLastState)
 {
  mov->mpgLastState = mov->mpgState;
  putBufCharX(mov->mpgState);
 }

 P_ZXISR isr = mov->isr;	/* pointer to isr info */
 MPG_VAL val;
 switch (mov->mpgState)
 {
 case MPG_CHECK_QUE:
 {
  P_JOGQUE jog = mov->jogQue;	/* get queue pointer */

  __disable_irq();		/* disable interrupt */
  if (jog->count == 0)		/* if nothing in queue */
  {
   __enable_irq();		/* enable interrupts */
   return;			/* and exit */
  }
  --jog->count;			/* count removal */
  val.intVal = (int) jog->buf[jog->emp]; /* get value */
  __enable_irq();		/* enable interrupts */

  jog->emp++;			/* update pointer */
  if (jog->emp >= MAXJOG)	/* if at end of queue */
   jog->emp = 0;		/* reset to start */

  char dir = (int) val.dir;	  /* get direction */
  unsigned int delta = val.delta; /* mask off time delta */

  if (rVar.jogDebug)
   printf("%c dir %2d delta %6d dist %3d\n",
	  mov->axisName, dir, delta, isr->dist);
  if (mov->mpgFlag)		/* if direction inverted */
   dir = -dir;			/* invert distance */

  if (dir != mov->dir)	/* if direction change */
  {
   if (rVar.jogDebug)
    printf("%c chg dir %d\n", mov->axisName, dir);
   mov->dir = dir;		/* save direction */
   mov->isrStop('9');		/* stop movement */
   mov->mpgDirChTim = millis(); /* start of dir change timeout */
   mov->mpgState = MPG_DIR_CHANGE_WAIT;
   dbgZJogDirSet();
  }
  else
  {
   uint32_t ctr;
   int dist = *mov->mpgJogInc;	/* read increment distance */
   if (dist == 0)		/* if continuous jog */
   {
    if (delta < mov->mpgUSecSlow) /* if fast jog */
    {
     dist = mov->mpgStepsCount; /* set counts */
    }
    else			/* if slow jog */
    {
     delta = mov->mpgUSecSlow;	/* use slow limit for interval */
     dist = 1;			/* set distance to 1 */
    }
    ctr = (delta * clksPerUSec) / dist; /* calculate new time value */

    __disable_irq();		/* disable interrupt */
    if (isr->dist != 0)		/* if currently active */
    {
     isr->dist += dist;		/* update distance */
     isr->clocksStep = ctr;	/* save counter value */
     mov->timer->ARR = ctr - 1; /* set new counter value */
     __enable_irq();		/* enable interrupts */
     return;			/* and exit */
    }
   }
   else				/* if incremental jog */
   {
    ctr = (mov->mpgUSecSlow * clksPerUSec) / mov->mpgStepsCount; /* set ctr */
   }
   __enable_irq();		/* enable interrupts */

   if (dir > 0)			/* set direction hardware */
    mov->dirFwd();
   else
    mov->dirRev();
   isr->dir = dir;
   
   mov->expLoc += dist * dir;	/* update expected loc */

   if (rVar.jogDebug)
    printf("%c mDir %2d iDir %2d dist %3d ctr %u\n",
	   mov->axisName, mov->dir, isr->dir, dist, (unsigned int) ctr);

   isr->done = 0;		/* clear variables */
   isr->steps = 0;
   isr->home = 0;
   isr->useDro = 0;
   isr->cFactor = 0;
   isr->accel = 0;
   isr->decel = 0;
   isr->sync = 0;

   isr->dist = dist;		/* set distance */

   mov->hwEnable(ctr);		/* setup hardware */
   mov->start();		/* start */
  }
 }
  break;

  case MPG_DIR_CHANGE_WAIT:
   if ((millis() - mov->mpgDirChTim) > 50) /* if waiting to stop */
   {
    int dir = mov->dir;		/* get direction */
    mov->dir = dir;		/* save direction */
    if (dir > 0)		/* set direction hardware */
     mov->dirFwd();
    else
     mov->dirRev();
    isr->dir = dir;		/* set isr direction */

    int backlashSteps = mov->axis->backlashSteps; /* get backlash */

    if (backlashSteps != 0)	/* if backlash */
    {
     dbgMpgBackLSet();		/* +++ */

     uint32_t ctr = (mov->mpgUSecSlow * clksPerUSec) / backlashSteps;
     
     if (rVar.jogDebug)
      printf("%c mDir %2d iDir %2d dist %3d ctr %u\n",
	     mov->axisName, mov->dir, isr->dir, isr->dist, (unsigned int) ctr);
     isr->dir = 0;

     isr->done = 0;		/* clear variables */
     isr->steps = 0;
     isr->home = 0;
     isr->useDro = 0;
     isr->cFactor = 0;
     isr->accel = 0;
     isr->decel = 0;
     isr->sync = 0;

     isr->dist = backlashSteps;

     mov->hwEnable(ctr);	/* setup hardware */
     mov->start();		/* start */

     mov->mpgState = MPG_WAIT_BACKLASH;
    }
    else
    {
     mov->mpgState = MPG_CHECK_QUE;
     dbgZJogDirClr();
    }
   }
   break;

 case MPG_WAIT_BACKLASH:
  if (isr->done)		/* if done */
  {
   if (rVar.jogDebug)
    printf("%c steps %4d\n", mov->axisName, isr->steps);
   isr->done = 0;		/* clear done flag */

   P_JOGQUE jog = mov->jogQue;	/* get queue pointer */
   __disable_irq();		/* disable interrupt */
   jog->count = 0;		/* reset count */
   jog->fil = 0;		/* reset fill */
   jog->emp = 0;		/* reset emptty */
   __enable_irq();		/* enable interrupts */

   mov->mpgState = MPG_CHECK_QUE;
   dbgMpgBackLClr();		/* +++ */
   dbgZJogDirClr();
  }
  break;
 }
}

void jogSpeed(P_MOVECTL mov, float speed)
{
 int dir = 1;
 if (speed < 0)
 {
  dir = -1;
  speed = -speed;
 }
 P_ACCEL ac = mov->acJogSpeed;	/* pointer to jog */
 if (mov->state == AXIS_IDLE)	/* if not moving */
 {
  ac->maxSpeed = speed;		/* update max speed */
  accelCalc(ac);		/* calculate acceleration */
  float time = 2 * rVar.jogTimeInitial - ac->time; /* time after accel */
  auto stepsSec = (float) ac->stepsSec;
  int d = (int) ac->steps + (int) (time * stepsSec); /* initial steps */
  mov->iniDist = d;		/* save initial distance */
  if (dir < 0)			/* if direction negative */
   d = -d;			/* set to negative */
  mov->stop = 0;		/* clear stop flag */
  mov->jogInc = (int) (2 * rVar.jogTimeInc * stepsSec); /* save increment */
  mov->maxDist = (int) (2 * rVar.jogTimeMax * stepsSec); /* save maximum */

  if (DBG_P)
  {
   auto stepsInch = (float) ac->stepsInch;
   printf("JSpeed dist %0.4f inc %0.4f max %0.4f\n",
          (float) d / stepsInch ,  (float) mov->jogInc / stepsInch,
          (float) mov->maxDist / stepsInch);
  }

  mov->moveRel(d, mov->speedCmd); /* start movement */
 }
 else if (mov->state == AXIS_WAIT_BACKLASH) /* if waiting for backlash */
 {
 }
 else				/* if moving */
 {
  if (mov->dir == DIR_POS)	/* if currently positive */
  {
   if (dir < 0)			/* if dir negative */
    return;			/* exit */
  }
  else				/* if currently negative */
  {
   if (dir > 0)			/* if dir positive */
    return;			/* exit */
  }
  P_ZXISR isr = mov->isr;
  if (speed == 0.0)
  {
   __disable_irq();		/* disable interrupt */
   if (isr->accelStep < 5)
   {
    mov->isrStop('8');
   }
   else
   {
    isr->accel = 0;
    isr->decel = 1;
    isr->dist = isr->accelStep;
   }
   __enable_irq();		/* enable interrupts */
  }
  else
  {
   if (speed != ac->maxSpeed)	/* if jog speed different */
   {
    speedCalc(ac, isr, speed); /* calculate acceleration */
    auto stepsSec = (float) ac->stepsSec;
    mov->jogInc = (int) (2 * rVar.jogTimeInc * stepsSec); /* upd inc */
    mov->maxDist = (int) (2 * rVar.jogTimeMax * stepsSec); /* update max */
   }
   __disable_irq();		/* disable interrupt */
   if (isr->done)		/* if movement stopped */
   {
    __enable_irq();		/* enable interrupts */
    int d = mov->iniDist;	/* get initial distance */
    if (dir < 0)		/* if distance negative */
     d = -d;			/* make negative */
    mov->moveRel(d, mov->speedCmd); /* start movement */
   }
   else				/* if still moving */
   {
    isr->dist += mov->jogInc;	 /* add to distance */
    if (isr->dist > mov->maxDist) /* if less than max distance */
     isr->dist = mov->maxDist;	/* set to maximum */
    __enable_irq();		/* enable interrupts */
   }
  }
 }
}

void zReset()
{
 zTmrStop();
 zTmrClrIE();
 zTmrClrIF();
 runout.zFlag = 0;
}

void zHwEnable(unsigned int ctr)
{
 zTmrScl(0);
 zTmrCnt(ctr);
 zTmrSet(ctr);
 zTmrCCR(tmrStepWidth);
 zTmrPWMMode();
 zTmrPWMEna();
 zTmrSetIE();
}

void zTurnInit(P_ACCEL ac, int dir, unsigned int dist)
{
 if (DBG_P)
  printf("\nzTurninit %s\n", ac->label);

 if (rVar.spindleEncoder == 0)	/* if no spindle encoder */
 {
  if (rVar.stepperDrive == 0)	/* if motor driven */
  {
   motorSetup(&zTA, rVar.zAccel, runCtl.zFeed); /* setup feed based upon rpm */
  }

  unsigned int ctr = turnInit(&zIsr, ac, dir, dist);
  tmrInfo(TIM5);
  zHwEnable(ctr);
  tmrInfo(TIM5);
 }
 else				/* if spindle encoder */
 {
  if (syn.encActive & Z_ACTIVE)
  {
   encTurnInit(&zIsr, ac, dir, dist);
   zIsr.syncInit = syn.zSyncInit;
  }
  else if ((syn.intActive & Z_ACTIVE) || (syn.extActive & Z_ACTIVE))
  {
   syncTurnInit(&zIsr, ac, dir, dist);
   zIsr.syncInit = syn.zSyncInit;
  }
//  else if (syn.extActive & Z_ACTIVE)
//  {
//   syncTurnInit(&zIsr, ac, dir, dist);
//   zIsr.syncInit = syn.zSyncInit;
//  }

  if (runout.active)		/* if runout */
  {
   if (syn.encActive & X_ACTIVE)	/* if using encoder */
    xEncRunoutInit();		/* initialize for encoder runout */

   if ((runCtl.threadFlags & TH_LEFT) == 0) /* if right hand threading */
   {
    runout.zStart = runout.zSteps; /* start of runout */
    runout.zFlag = 1;		/* set runout flag */
   }
   else				/* if left hand threading */
   {
    xIsr.syncInit = syn.xSyncInit;
   }
  }
 }
}

void zTaperInit(P_ACCEL ac, int dir)
{
 if (DBG_P)
  printf("\nzTaperInit %s dir %d\n", ac->label, dir);

 if (ac->taper)
 {
  if (rVar.spindleEncoder == 0)	/* *ok* if no spindle encoder */
  {
   unsigned int ctr = taperInit(&zIsr, ac, dir);
   zHwEnable(ctr);
  }
  else				/* *chk* if spindle encoder */
  {
   int syncInit = 0;
   if (syn.encActive)
   {
    syncInit = SYNC_ACTIVE_ENC;
   }
   if (syn.intActive)
   {
    syncInit = SYNC_ACTIVE_TAPER;
   }
   if (syn.extActive)
   {
    syncInit = SYNC_ACTIVE_TAPER;
   }
   encTaperInit(&zIsr, ac, dir, syncInit);
  }
 }
}

void zMoveInit(P_ACCEL ac, int dir, unsigned int dist)
{
 zReset();
 P_MOVECTL mov = &zMoveCtl;
 ac->useDro = (mov->cmd & DRO_POS) != 0; /* set use dro flag */
 ac->droTarget = mov->droTarget;
 unsigned int ctr = moveInit(&zIsr, ac, dir, dist);
 zHwEnable(ctr);
}

void zStart()
{
 zTmrStart();
 if (DBG_START)
 {
  printf("zStart trackSpeed %d\n", trackSpeed);
  printf(" CR1 %8x  CNT %8x  ARR %8x  CCR %8x\n",
	 (unsigned int) (Z_TMR->CR1), (unsigned int) (Z_TMR->CNT),
	 (unsigned int) (Z_TMR->ARR), (unsigned int) zTmrReadCCR());
  printf("CCMR %8x CCER %8x DIER %8x\n",
	 (unsigned int) zTmrReadCCMR(), (unsigned int) (Z_TMR->CCER),
	 (unsigned int) (Z_TMR->DIER));
 }
 dbgZAccelSet();
}

void zPulseSetup()
{
 zTmrScl(0);
 zTmrCnt(tmrMin);
 zTmrSet(tmrMin);
 zTmrCCR(tmrStepWidth);
 zTmrPWMMode();
 zTmrPWMEna();
}

void zPulseTrig()
{
 zTmrPulse();
 zTmrSetIE();
}

void zPulse()
{
 zTmrScl(0);
 zTmrCnt(tmrMin);
 zTmrSet(tmrMin);
 zTmrCCR(tmrStepWidth);
 zTmrPulse();
 zTmrPWMMode();
 zTmrPWMEna();
 zTmrSetIE();
}

void zStartSlave()
{
 zTmrSlvEna();
 zIsr.active = SYNC_ACTIVE_STEP;
 dbgmsg(D_ZEST, (int)sp.intCount); /* spindle interrupt count at start */
 dbgZAccelSet();
 if (DBG_TMR)
 {
  tmrInfo(TIM2);
  newline();
  tmrInfo(SPINDLE_TMR);
 }
}

void zMoveAbsCmd()
{
 if (zMoveCtl.state == AXIS_IDLE)
 {
  int pos = lrintf(rVar.zMovePos * (float) zAxis.stepsInch) + rVar.zHomeOffset;
  zMove(pos, rVar.zFlag);
 }
}

void zMoveRelCmd()
{
 if (zMoveCtl.state == AXIS_IDLE)
 {
  int dist = lrintf(rVar.zMoveDist * (float) zAxis.stepsInch);
  if ((rVar.zFlag & DRO_POS) != 0)
  {
   int droCounts = lrintf(rVar.zMoveDist * (float) zAxis.droCountsInch);
   zMoveCtl.droTarget = rVar.zDroLoc + droCounts;
   if (DBG_P)
   {
    printf("zMoveRelCmd dist %7.4f steps %7d droCounts %7d\n",
		    rVar.zMoveDist, dist, droCounts);
    printf("droTarget %7d droPos %7d droCounts %7d\n",
	   zMoveCtl.droTarget, rVar.zDroLoc, zMoveCtl.droTarget - rVar.zDroLoc);
   }
  }
  zMoveRel(dist, rVar.zFlag);
 }
}

void zJogCmd()
{
 if ((moveQue.count == 0)	/* if not moving */
 ||  (jogPause & PAUSE_ENA_Z_JOG)
 ||  ((rVar.mvStatus & (MV_PAUSE | MV_MEASURE)) == (MV_PAUSE | MV_MEASURE)))
 {
  jogMove(&zMoveCtl, rVar.zJogDir);
 }
 else if (DBG_JOG)
  printf("zJogCmd count %d jogPause %x mvStatus %x\n",
	 moveQue.count, jogPause, rVar.mvStatus);
}

void zJogSpeedCmd()
{
 if ((moveQue.count == 0)	/* if not moving */
 || ((rVar.mvStatus & (MV_PAUSE | MV_MEASURE)) == (MV_PAUSE | MV_MEASURE)))
 {
  jogSpeed(&zMoveCtl, rVar.zJogSpeed);
 }
 else if (DBG_JOG)
  printf("zJogSpeedCmd count %d mvStatus %x\n",
	 moveQue.count, rVar.mvStatus);
}

void zLocCmd()
{
 if (zMoveCtl.state == AXIS_IDLE)
 {
  rVar.zLoc = (int) (rVar.zSetLoc * (float) zAxis.stepsInch);
 }
}

void zStop()
{
 if (DBG_P)
  printf("zStop dist %5d zLoc %5d\n", zIsr.dist, rVar.zLoc);

 zMoveCtl.stop = 1;
 zIsr.accel = 0;
 zIsr.decel = 1;
 zIsr.errFlag = 0;
 dbgZPosErrClr();
 dbgZAccelSet();
}

void zSetup()
{
 if (DBG_SETUP)
  printf("\nz axis setup\n");

 P_AXIS axis = &zAxis;
 axis->pitch = rVar.zPitch;
 axis->ratio = rVar.zRatio;
 axis->microSteps = rVar.zMicro;
 axis->motorSteps = rVar.zMotor;
 axis->accel = rVar.zAccel;
 axis->backlash = rVar.zBacklash;
 axis->axis = 'z';
 if (rVar.zDirFlag)
 {
  axis->dirFwd = Dir1_Pin;
  axis->dirRev = Dir1_Pin << 16;
 }
 else
 {
  axis->dirFwd = Dir1_Pin << 16;
  axis->dirRev = Dir1_Pin;
 }
 int stepsInch = lrintf(((float) axis->microSteps * (float) axis->motorSteps *
			axis->ratio) / axis->pitch);
 axis->stepsInch = stepsInch;
 axis->backlashSteps = lrintf(axis->backlash * (float) axis->stepsInch);
 axis->droCountsInch = rVar.zDroCountInch;
 axis->stepFactor = rVar.zStepFactor;
 axis->droFactor = rVar.zDroFactor;

 zIsr.axis = 'z';

 if (DBG_SETUP)
  printf("zStepsInch %d zBacklash %0.4f zBacklashSteps %d\n",
	 stepsInch, axis->backlash, axis->backlashSteps);

 zPA.label = "zP";		/* taper accel */
 zPA.stepsInch = stepsInch;

 zMoveSetup();
 zHomeSetup();
}

void zMoveSetup()
{
 zTA.label = "zT";		/* z synchronous */
 zTA.stepsInch = zAxis.stepsInch;

 P_ACCEL ac = &zMA;		/* z move */
 ac->label = "zM";
 ac->minSpeed = rVar.zMoveMin;
 ac->maxSpeed = rVar.zMoveMax;
 ac->accel = zAxis.accel;
 ac->stepsInch = zAxis.stepsInch;
 accelCalc(ac);

 ac = &zJA;			/* z jog */
 ac->label = "zJ";
 ac->minSpeed = rVar.zJogMin;
 ac->maxSpeed = rVar.zJogMax;
 ac->accel = zAxis.accel;
 ac->stepsInch = zAxis.stepsInch;
 accelCalc(ac);

 memcpy(&zJSA, ac, sizeof(zJSA));
 zJSA.label = "zJS";		/* z jog speed */

 P_MOVECTL mov = &zMoveCtl;
 mov->axisName = 'z';
 if (rVar.limitsEnabled)
  mov->limitsEna = rVar.zLimEna;
 mov->mpgJogInc = &rVar.zMpgInc;
 mov->mpgJogMax = &rVar.zMpgMax;
 mov->mpgFlag = rVar.zMpgFlag;
 mov->axis = &zAxis;
 mov->isr = &zIsr;
 mov->jogFlag = PAUSE_ENA_Z_JOG;
 mov->jogQue = &zJogQue;
 mov->acThread = &zTA;
 mov->acTaper = &zPA;
 mov->acMove = &zMA;
 mov->acJog = &zJA;
 mov->acJogSpeed = &zJSA;
 mov->isrStop = &zIsrStop;
 mov->move = &zMove;
 mov->moveRel = &zMoveRel;
 mov->mpgStepsCount = 14;
 mov->mpgUSecSlow = 20 * 1000;
 mov->jogCmd = CMD_JOG;
 mov->speedCmd = CMD_SPEED;
 if (rVar.zUseDro)
 {
  mov->jogCmd |= DRO_UPD;
  mov->speedCmd |= CMD_SPEED;
 }
 mov->stepsInch = zAxis.stepsInch;
 mov->droCountInch = rVar.zDroCountInch;
 mov->timer = Z_TMR;
 mov->moveInit = &zMoveInit;
 mov->dirFwd = &dirZFwd;
 mov->dirRev = &dirZRev;
 mov->hwEnable = zHwEnable;
 /* mov->start = &zStart; */
 mov->start = &zTmrStart;
 mov->pulse = &zPulse;
 mov->locPtr = &rVar.zLoc;
 mov->droLocPtr = &rVar.zDroLoc;
 mov->homeOffset = &rVar.zHomeOffset;
 mov->droOffset = &rVar.zDroOffset;
}

void syncMoveSetup()
{
 if (DBG_SETUP)
  printf("\nsyncMoveSetup op %d %s turn %d %s thread %d %s\n",
	 rVar.currentOp, operationsList[(int) rVar.currentOp],
	 rVar.turnSync, selTurnList[(int) rVar.turnSync],
	 rVar.threadSync, selThreadList[(int) rVar.threadSync]);

 runout.active = 0;
 //active = 0;
 syn.encActive = 0;
 syn.zSyncInit = 0;
 syn.encoderDirect = 0;

 syn.zSyncInit = 0;
 syn.xSyncInit = 0;

 char active = 0;
 switch(rVar.currentOp)
 {
 case OP_TURN:
  active = Z_ACTIVE;
  break;
 case OP_FACE:
  //active = X_ACTIVE;
  //break;
 case OP_CUTOFF:
  active = X_ACTIVE;
  break;
 case OP_TAPER:
  active = X_ACTIVE | Z_ACTIVE;
  break;
 case OP_THREAD:
  //active = Z_ACTIVE;
  //break;
 case OP_ARC:
  //active = Z_ACTIVE;
  //break;
 default:
  active = Z_ACTIVE;
  break;
 }

 if (rVar.currentOp != OP_THREAD) /* if not threading */
 {
  switch(rVar.turnSync)
  {
  case SEL_TU_SPEED:		/* 0 Motor Speed */
   break;

  case SEL_TU_STEP:		/* 1 Stepper */
   syn.stepActive = active;
   if ((active & Z_ACTIVE) != 0)
    syn.zSyncInit = SYNC_ACTIVE_STEP;
   if ((active & X_ACTIVE) != 0)
    syn.xSyncInit = SYNC_ACTIVE_STEP;
   break;

  case SEL_TU_ENC:		/* 2 Encoder */
   syn.encActive = active;
   if ((active & Z_ACTIVE) != 0)
    syn.zSyncInit = SYNC_ACTIVE_ENC;
   if ((active & X_ACTIVE) != 0)
    syn.xSyncInit = SYNC_ACTIVE_ENC;
   break;

  case SEL_TU_ISYN:		/* 3 Int Syn */
   syn.intActive = active;
   if (active & Z_ACTIVE)
    syn.zSyncInit = SYNC_ACTIVE_TMR;
   if (active & X_ACTIVE)
    syn.xSyncInit = SYNC_ACTIVE_TMR;
   break;

  case SEL_TU_ESYN:		/* 4 Ext Syn */
   syn.extActive = active;
   if (active & Z_ACTIVE)
    syn.zSyncInit = SYNC_ACTIVE_EXT;
   if (active & X_ACTIVE)
    syn.xSyncInit = SYNC_ACTIVE_EXT;
   break;
  }
 }
 else				/* if threading */
 {
  char flag = runCtl.threadFlags;
  runout.active = (flag & TH_RUNOUT) != 0;
  switch(rVar.threadSync)
  {
  case SEL_TH_NO_ENC:		/* 0 no encoder threading disabled */
   //break;

  case SEL_TH_STEP:		/* 1 spindle stepper sync timers */
   break;

  case SEL_TH_ENC:		/* 2 use encoder directly */
   syn.encActive = Z_ACTIVE;
   syn.zSyncInit = SYNC_ACTIVE_ENC;
   if (runout.active)
   {
    syn.encActive |= X_ACTIVE;
    syn.xSyncInit = SYNC_ACTIVE_ENC;
   }
   break;

  case SEL_TH_ISYN_RENC:	/* 3 internal sync runout encoder */
   syn.intActive = Z_ACTIVE;
   syn.zSyncInit = SYNC_ACTIVE_TMR;
   if (runout.active)
   {
    syn.encActive = X_ACTIVE;
    syn.xSyncInit = SYNC_ACTIVE_ENC;
   }
   break;

  case SEL_TH_ESYN_RENC:	/* 4 external sync runout encoder */
   syn.extActive = Z_ACTIVE;
   syn.zSyncInit = SYNC_ACTIVE_EXT;
   if (runout.active)
   {
    syn.encActive = X_ACTIVE;
    syn.xSyncInit = SYNC_ACTIVE_ENC;
   }
   break;

  case SEL_TH_ESYN_RSYN:	/* 5 external sync runout sync */
   syn.extActive = Z_ACTIVE;
   syn.zSyncInit = SYNC_ACTIVE_EXT;
   if (runout.active)
   {
    syn.intActive = X_ACTIVE;
    syn.xSyncInit = SYNC_ACTIVE_TMR;
   }
   break;
  }
 }

 if (syn.zSyncInit != 0)		/* if threading */
   syn.zSyncInit |= SYNC_ACTIVE_THREAD; /* set flag for isr */

 syn.encoderDirect = ((syn.zSyncInit | syn.xSyncInit) & SYNC_ACTIVE_ENC) != 0;
 if (DBG_SETUP)
 {
  printf("zSyncInit %d xSyncInit %d encoderDirect %d\n",
	 syn.zSyncInit, syn.xSyncInit, syn.encoderDirect);
  printf("active %d encActive %d synIntActive %d "
	 "synExtAcitve %d runoutActive %d\n\n",
	 active, syn.encActive, syn.intActive, syn.encActive, runout.active);
 }

 if (rVar.spindleEncoder)	/* *ok* */
 {
  HAL_NVIC_EnableIRQ(spSyncIRQn); /* enable spindle sync interrupt */
  EXTI->PR = ExtInt_Pin;
 }
 else
  HAL_NVIC_DisableIRQ(spSyncIRQn); /* disable spindle sync interrupt */
}

void zMoveRel(int dist, int cmd)
{
 P_MOVECTL mov = &zMoveCtl;

 if (DBG_MOVOP)
 {
  auto stepsInch = (float) zAxis.stepsInch;
  printf("zMoveRel %2x l %7.4f d %7.4f dir %2d\n",
	 cmd, (float) rVar.zLoc / stepsInch,
	 (float) dist / stepsInch, mov->dir);
 }
 mov->loc = rVar.zLoc;		/* save current location */
 mov->expLoc = rVar.zLoc + dist; /* calculate expected end location */
 mov->cmd = cmd;		/* save command */
 if (rVar.cfgDro)
  dbgmsg(D_ZDRO, rVar.zDroLoc);
 dbgmsg(D_ZLOC, mov->loc);
 dbgmsg(D_ZDST, dist);
 if (dist != 0)			/* if distance non zero */
 {
  if (dist > 0)			/* if moving positive */
  {
   mov->dist = dist;		/* save distance */
   mov->dirChange = (mov->dir != DIR_POS); /* dir chg */
   mov->dir = DIR_POS;		/* set to move positive direction */
   dirZFwd();			/* set to forward */
  }
  else
  {
   mov->dist = -dist;		/* make distance a positive number */
   mov->dirChange = (mov->dir != DIR_NEG); /* dir chg */
   mov->dir = DIR_NEG;		/* set move direction to negative */
   dirZRev();			/* set to reverse */
  }
  if (mov->dirChange		/* if direction change */
  &&  (zAxis.backlashSteps != 0)) /* and backlash present */
  {
   zMoveInit(&zMA, 0, zAxis.backlashSteps); /* setup backlash move */
   zStart();			/* start move */
   mov->state = AXIS_WAIT_BACKLASH; /* set to wait for backlash */
  }
  else				/* if no backlash */
  {
   mov->state = AXIS_START_MOVE; /* set to start move */
   zControl();			/* and start move */
  }
 }
}

void zSynSetup(int feedType, float feed, float runoutDist, float runoutDepth)
{
 if (DBG_SETUP)
  printf("\nzSynSetup\n");

 P_ACCEL ac = &zTA;
 switch (feedType)
 {
 case FEED_PITCH:
  turnPitch(ac, feed);
  break;
 case FEED_TPI:
  threadTPI(ac, feed);
  break;
 case FEED_METRIC:
  threadMetric(ac, feed);
  break;
  default:
   break;
 }

 if (rVar.spindleEncoder == 0)	/* *ok* if not using encoder */
 {
  turnCalc(ac);
  turnAccel(ac, rVar.zAccel, T_STEP_SPINDLE | T_DBG_PRINT, 0);
 }
 else				/* *chk* if spindle encoder */
 {
  if (syn.encActive & Z_ACTIVE)	/* if using encoder for z */
  {
   zIsr.encoderDirect = 1;
   encTurnCalc(ac);
  }
 }

 if (runout.active)		/* if runout */
 {
  runout.zDist = runoutDist;
  runout.zSteps = lrintf(runoutDist * (float) ac->stepsInch);
  runout.xSteps = lrintf(fabsf(runoutDepth) * (float) xAxis.stepsInch);
  float dist = runoutDist / ac->pitch;

  if (DBG_P)
   printf("\nrunout %0.4f zRunoutDist %0.4f zRunoutSteps %d\n"	\
	  "runoutDepth %0.4f xRunoutSteps %d\n",
	  dist, runout.zDist, runout.zSteps,
	  runoutDepth, runout.xSteps);

  if (rVar.spindleEncoder == 0)	/* *ok* if no spindle encoder */
  {
   runoutCalc(ac, &xRA, dist, runoutDepth);
  }
  else				/* *chk* if spindle encoder */
  {
   if (syn.encActive & X_ACTIVE)
    encRunoutCalc(ac, &xRA, dist, runoutDepth);
  }
 }
 else				/* if no runout */
 {
  runout.zDist = 0;
  runout.zSteps = 0;
 }
}

void zInfo(char flag)
{
 if (flag == 1)
  printf("\n");
 printf("cr1 %2x sr %2x cnt %d cFactor %0.2f curCount %d %d stepsSec %d\n",
	(unsigned int) TIM2->CR1, (unsigned int) TIM2->SR, (int) TIM2->CNT,
	zIsr.cFactor, zIsr.curCount, (int) zTmrMaxRead(),
	(int) (rVar.cfgFcy / zIsr.curCount));
 printf("done %d accel %d decel %d initialStep %d accelStep %d finalStep %d",
	zIsr.done, zIsr.accel, zIsr.decel,
	zIsr.initialStep, zIsr.accelStep, zIsr.finalStep);
 if (flag == 0)
  printf("\n");
}

void zMove(int pos, int cmd)
{
 dbgmsg(D_ZMOV, pos);
 int dist = pos - rVar.zLoc;
 zMoveRel(dist, cmd);
}

void zMoveDro(int pos, int cmd)
{
 int droDist = pos - (rVar.zDroLoc - rVar.zDroOffset);
 /* dist = droDist * (stepsInch / countsInch) */
 int dist = (2 * droDist * zAxis.stepFactor) / zAxis.droFactor;
 dist = (dist + 1) >> 1;
 int droTarget = pos + rVar.zDroOffset;
 zMoveCtl.droTarget = droTarget;
 if (DBG_QUE)
 {
  /* counts = inches * (counts / inch) */
  printf("zMoveDro cmd %03x pos %7.4f droPos %7.4f dist %7.4f steps %d "
	 "counts %d\n",
	 cmd, ((float) pos) / (float) zAxis.droCountsInch,
	 ((float) (rVar.zDroLoc - rVar.zDroOffset)) /
	 (float) zAxis.droCountsInch,
	 ((float) droDist) / (float) zAxis.droCountsInch, dist, droDist);
  printf("droTarget %7d droPos %7d droCounts %7d\n",
	 droTarget, rVar.zDroLoc, droTarget - rVar.zDroLoc);
 }
 zMoveRel(dist, cmd);
}

void zControl()
{
 P_MOVECTL mov = &zMoveCtl;

 if (mov->stop)			/* if stop */
 {
  mov->stop = 0;		/* clear stop flag */
  mov->state = AXIS_WAIT_MOVE;	/* wait for move complete */
 }

#if DBGMSG
 if (mov->state != mov->prev)
 {
  dbgmsg(D_ZST, mov->state);
  mov->prev = mov->state;
 }
#endif

 int cmd = mov->cmd;		/* read command */
 switch(mov->state)		/* dispatch on state */
 {
 case AXIS_IDLE:		/* 0x00 idle state */
  break;

 case AXIS_WAIT_BACKLASH:	/* 0x01 wait for backlash move to complete */
  if (zIsr.done)		/* if done */
  {
   dbgmsg(D_ZBSTP, (int)zIsr.steps);
   zIsr.done = 0;		/* clear done flag */
   mov->state = AXIS_START_MOVE; /* advance to move state */
  }
  break;

 case AXIS_START_MOVE:		/* 0x02 start an x move */
 {
  if (DBG_P)
   printf("zstartmove %x\n", cmd);

  switch (cmd & CMD_MSK)
  {
  case CMD_SYN:
   zTurnInit(&zTA, mov->dir, mov->dist); /* init synchronized move */
   if ((cmd & (Z_SYN_START | Z_SYN_LEFT)) != 0) /* if start on index pulse */
   {
    if ((cmd & X_SYN_TAPER) != 0) /* if tapering */
    {
     zIsr.taper = TAPER_CTL;	/* indicate z controlling taper */
     float dist = (float) mov->dist / (float) zAxis.stepsInch; /* distance */
     int taperDist = (int) (dist * xPA.taperInch * (float) xAxis.stepsInch);
     xIsr.dist = taperDist;	/* save for isr */

     if (rVar.cfgDro)
      dbgmsg(D_XDRO, rVar.xDroLoc);
     dbgmsg(D_XLOC, rVar.xLoc);
     dbgmsg(D_XDST, taperDist);

     if (DBG_P)
      printf("taperDist %4d %7.4f taperInch %8.6f zDist %4d %7.4f\n",
	     taperDist, (float) taperDist / (float) xPA.stepsInch,
             xPA.taperInch, mov->dist, dist);

     if ((rVar.stepperDrive == 0)    /* if motor driven */
     &&  (rVar.spindleEncoder == 0)) /* *ok* and no spindle encoder */
     {
      zStart();			/* start z */
      xStart();			/* start x */
     }
     dbgXTaperSet();
    } /* end taper */

    if (rVar.stepperDrive	/* if stepper drive */
    ||	rVar.spindleEncoder)	/* *chk* or spindle encoder */
    {
     slaveEna();		/* enable slave mode */
    }
   }
   else				/* if not start on index pulse */
   {
    if (rVar.spindleEncoder == 0) /* *ok* if no spindle encoder */
    {
     zStart();			/* start now */
     if (rVar.stepperDrive == 0) /* if motor drive */
      trackSpeed = 1;		/* set to track speed */
     else
     {
      zIsr.active = SYNC_ACTIVE_STEP; /* set to active */
      dbgmsg(D_ZEST, (int)sp.intCount); /* spindle int count at start */
     }
    }
    else			/* *chk* if spindle encoder */
    {
     zIsr.active = zIsr.syncInit; /* make active */
     zIsr.syncInit = 0;		/* clear init flag */
     dbgmsg(D_ZEST, (int)spEncCount); /* encoder count at start */
    }
   }
   break;

  case CMD_JOG:
   zMoveInit(&zJA, mov->dir, mov->dist); /* setup move */
   if ((cmd & FIND_HOME) != 0)
    zIsr.home |= HOME_SET;
   if ((cmd & CLEAR_HOME) != 0)
    zIsr.home |= HOME_CLR;
   if ((cmd & FIND_PROBE) != 0)
    zIsr.home |= PROBE_SET;
   if ((cmd & CLEAR_PROBE) != 0)
    zIsr.home |= PROBE_CLR;
   mov->jog = 1;
   zStart();			/* start move */
   break;

  case CMD_MOV:
  case CMD_MAX:
   zMoveInit(&zMA, mov->dir, mov->dist); /* setup move */
   zStart();			/* start move */
   break;

  case CMD_SPEED:
   zMoveInit(&zJSA, mov->dir, mov->dist); /* setup move */
   zStart();			/* start move */
   if (DBG_MOVOP)
    zInfo(0);
   break;

  case JOGSLOW:			/* slow jog to probe or find home */
   zMoveInit(&zSA, mov->dir, mov->dist); /* setup move */
   if ((cmd & FIND_HOME) != 0)
    zIsr.home |= HOME_SET;
   if ((cmd & CLEAR_HOME) != 0)
    zIsr.home |= HOME_CLR;
   if ((cmd & FIND_PROBE) != 0)
    zIsr.home |= PROBE_SET;
   if ((cmd & CLEAR_PROBE) != 0)
    zIsr.home |= PROBE_CLR;
   mov->jog = 1;
   zStart();
   break;
  }
  mov->state = AXIS_WAIT_MOVE;	/* wait for move to complete */
 }
 break;

 case AXIS_WAIT_MOVE:		/* 0x03 wait for an x move to complete */
  if (zIsr.done)		/* if done */
   mov->state = AXIS_DONE;	/* clean up everything */
  break;

 case AXIS_DONE:		/* 0x04 done state */
 default:			/* all others */
  if (mov->cmd & DRO_UPD)	/* fix x loc if used dro for position */
  {
   /* xLoc = droPos * (stepsInch / countsInch) */
   int zTmp = ((2 * (rVar.zDroLoc - rVar.zDroOffset) * zAxis.stepFactor) /
	       zAxis.droFactor);
   zTmp = (zTmp + 1) >> 1;	/* round */
   rVar.zLoc = zTmp + rVar.zHomeOffset;
   if (DBG_P)
    printf("DRO_UPD droPos %7.4f zPos %7.4f zLoc %6d\n",
	   (2.0 * (float) (rVar.zDroLoc - rVar.zDroOffset)) /
	   zAxis.droCountsInch,
	   (2.0 * (float) (rVar.zLoc - rVar.zHomeOffset)) / zAxis.stepsInch,
	   rVar.zLoc);
  }
  if (limitIsClr())
  {
   mov->limitDir = 0;		/* clear limit flags */
   mov->limitMove = 0;
  }

  zIsr.done = 0;		/* clear done flag */
  mov->cmd = 0;			/* clear command */
  mov->loc = rVar.zLoc;		/* save it */
  if (!mov->jog)		/* if not jogging */
  {
   if (mov->loc != mov->expLoc)	/* if not at expected location */
   {
    printf("z move error actual %d expected %d\n", mov->loc, mov->expLoc);
    dbgmsg(D_ZEXP, mov->expLoc);
   }
  }
  mov->jog = 0;			/* clear jog flag */
  trackSpeed = 0;		/* disable speed tracking */
  mov->state = AXIS_IDLE;	/* set state to idle */
  dbgmsg(D_ZSTP, (int)zIsr.steps);
  dbgmsg(D_ZST, mov->state);
  break;
 }
}

void xInit(P_AXIS ax)
{
 ax->axis = 'x';
 ax->pitch = X_LS_PITCH;
 ax->microSteps = X_MICRO_STEPS;
 ax->motorSteps = X_MOTOR_STEPS;
 ax->stepsInch = lrintf((float) (ax->microSteps * ax->motorSteps) / ax->pitch);

 if (DBG_SETUP)
  printf("\nxInit stepsInch %d\n", ax->stepsInch);
}

void zHomeSetup()
{
 if (DBG_SETUP)
  printf("zHomeSetup\n");
 P_HOMECTL home = &zHomeCtl;
 home->mov = &zMoveCtl;
 home->status = &rVar.zHomeStatus;
 home->homeIsSet = zAHomeIsSet;
 home->homeIsClr = zAHomeIsClr;

 P_ACCEL ac = &zSA;
 ac->label = "zS";
 ac->minSpeed = rVar.zHomeSpeed;
 ac->maxSpeed = rVar.zHomeSpeed;
 ac->accel = zAxis.accel;
 ac->stepsInch = zAxis.stepsInch;

 accelCalc(ac);

 auto stepsInch = (float) zAxis.stepsInch;
 int dir = rVar.zHomeDir;
 home->findDist = dir * lrintf(rVar.zHomeDist * stepsInch);
 home->findDistRev = -dir * lrintf(rVar.zHomeDistRev * stepsInch);
 home->backoffDist = -dir * lrintf(rVar.zHomeDistBackoff * stepsInch);
 home->slowDist = dir * lrintf(1.25f * rVar.zHomeDistBackoff * stepsInch);
}

void xReset()
{
 xTmrStop();
 xTmrClrIE();
 xTmrClrIF();
}

void xHwEnable(unsigned int ctr)
{
 xTmrScl(0);
 xTmrCnt(ctr);
 xTmrSet(ctr);
 xTmrCCR(tmrStepWidth);
 xTmrPWMMode();
 xTmrPWMEna();
 xTmrSetIE();
}

void xTurnInit(P_ACCEL ac, int dir, unsigned int dist)
{
 if (rVar.spindleEncoder == 0)	/* if no spindle encoder */
 {
  if (rVar.stepperDrive == 0)	/* if motor drive */
  {
   motorSetup(&xTA, rVar.xAccel, runCtl.xFeed); /* setup feed based upon rpm */
  }

  xReset();
  unsigned int ctr = turnInit(&xIsr, ac, dir, dist);
  xHwEnable(ctr);
 }
 else				/* if spindle encoder */
 {
  if (syn.encActive & X_ACTIVE)	/* if using encoder directly */
  {
   encTurnInit(&xIsr, ac, dir, dist);
   xIsr.syncInit = syn.xSyncInit;
  }
  if (syn.intActive & X_ACTIVE)	/* if internal sync */
  {
   syncTurnInit(&xIsr, ac, dir, dist);
   xIsr.syncInit = syn.xSyncInit;
  }
     if (syn.extActive & X_ACTIVE)	/* if external sync */
  {
   syncTurnInit(&xIsr, ac, dir, dist);
   xIsr.syncInit = syn.xSyncInit;
  }
 }
}

void xTaperInit(P_ACCEL ac, int dir)
{
 if (DBG_P)
  printf("\nxTaperInit %s dir %d\n", ac->label, dir);

 if (ac->taper)
 {
  if (rVar.spindleEncoder == 0)	/* *ok* if no spindle encoder */
  {
   unsigned int ctr = taperInit(&xIsr, ac, dir);
   xHwEnable(ctr);
  }
  else				/* *chk* if spindle encoder */
  {
   int syncInit = 0;
   if (syn.encActive)
   {
    syncInit = SYNC_ACTIVE_ENC;	/* 0x04 */
   }
   if (syn.intActive)
   {
    syncInit = SYNC_ACTIVE_TAPER; /* 0x10 */
   }
   if (syn.extActive)
   {
    syncInit = SYNC_ACTIVE_TAPER;
   }
   encTaperInit(&xIsr, ac, dir, syncInit);
  }
 }
}

void xRunoutInit()
{
 if (rVar.runoutDepth > 0)		/* if depth positive */
 {
  xIsr.dir = DIR_POS;		/* set dir positive */
  dirXFwd();
 }
 else				/* if negative */
 {
  xIsr.dir = DIR_NEG;		/* set dir negative */
  dirXRev();
 }

 xTmrSlvDis();			/* disable x slave mode */
 xTmrStop();			/* stop x timer */
 xTmrClrIE();			/* disable x interrupts */

 xIsr.dist = xRA.stepsCycle;	/* distance is one cycle */
 xIsr.steps = 0;		/* clear step counter */

 unsigned int ctr = xRA.clocksStep;
 xIsr.clocksStep = ctr;

 xIsr.counterStep1 = ctr - 1;
 xIsr.counterStep2 = ctr + 1 - 1;

 xIsr.d = xRA.d;
 xIsr.sum = xRA.d;
 xIsr.incr1 = xRA.incr1;
 xIsr.incr2 = xRA.incr2;
 xIsr.x = 0;
 xIsr.y = 0;
 xIsr.stepsCycle = xRA.stepsCycle;
 xIsr.accelSpSteps = xRA.accelSpSteps;

 xIsr.cycleCounter = 0;
 xIsr.sync = xIsr.incr1 != 0 ? 1 : -1;
 xIsr.taper = TAPER_SLAVE | TAPER_RUNOUT; /* indicate x is tapering */

 xIsr.curCount = ctr;
 xHwEnable(ctr);		/* setup x timer */

 dbgmsg(D_XLOC, rVar.xLoc);
 dbgmsg(D_XDST, (int)xIsr.dist);
}

void xSyncRunoutInit()
{
 runout.xFlag = 1;		/* set the runout flag */
 xIsr.taper = TAPER_SLAVE | TAPER_RUNOUT; /* indicate x is tapering */
 xIsr.dist = runout.xSteps;	/* set x runout distance */

 if (rVar.runoutDepth > 0)	/* if depth positive */
 {
  xIsr.dir = DIR_POS;		/* set dir positive */
  dirXFwd();
 }
 else				/* if negative */
 {
  xIsr.dir = DIR_NEG;		/* set dir negative */
  dirXRev();
 }

 if (DBG_P)
  printf("\nxSyncRunoutInit dir %d dist %d\n", xIsr.dir, xIsr.dist);

 dbgmsg(D_XLOC, rVar.xLoc);
 dbgmsg(D_XDST, (int)xIsr.dist);
}

void xEncRunoutInit()
{
 runout.xFlag = 1;		/* set the runout flag */
 xIsr.taper = TAPER_SLAVE | TAPER_RUNOUT; /* indicate x is tapering */
 xIsr.dist = runout.xSteps;	/* set x runout distance */

 if (rVar.runoutDepth > 0)	/* if depth positive */
 {
  xIsr.dir = DIR_POS;		/* set dir positive */
  dirXFwd();
 }
 else				/* if negative */
 {
  xIsr.dir = DIR_NEG;		/* set dir negative */
  dirXRev();
 }

 xIsr.d = xRA.d;
 xIsr.incr1 = xRA.incr1;
 xIsr.incr2 = xRA.incr2;
 xIsr.x = 0;
 xIsr.y = 0;

 if (DBG_P)
  printf("\nxEncRunoutInit dir %d dist %d\n", xIsr.dir, xIsr.dist);

 dbgmsg(D_XLOC, rVar.xLoc);
 dbgmsg(D_XDST, (int)xIsr.dist);
}

void xMoveInit(P_ACCEL ac, int dir, unsigned int dist)
{
 xReset();
 P_MOVECTL mov = &xMoveCtl;
 ac->useDro = (mov->cmd & DRO_POS) != 0; /* set use dro flag */
 ac->droTarget = mov->droTarget;
 unsigned int ctr = moveInit(&xIsr, ac, dir, dist);
 xHwEnable(ctr);
}

void xStart()
{
 xIsr.startRev = sp.rev;
 xIsr.startPos = sp.pos;
 xTmrStart();
 if (DBG_START)
 {
  printf("xStart trackSpeed %d\n", trackSpeed);
  printf(" CR1 %8x  CNT %8x  ARR %8x  CCR %8x\n",
	 (unsigned int) (X_TMR->CR1), (unsigned int) (X_TMR->CNT),
	 (unsigned int) (X_TMR->ARR), (unsigned int) xTmrReadCCR());
  printf("CCMR %8x CCER %8x DIER %8x\n",
	 (unsigned int) xTmrReadCCMR(), (unsigned int) (X_TMR->CCER),
	 (unsigned int) (X_TMR->DIER));
 }
 dbgXAccelSet();
}

void xPulseSetup()
{
 xTmrScl(0);
 xTmrCnt(tmrMin);
 xTmrSet(tmrMin);
 xTmrCCR(tmrStepWidth);
 xTmrPWMMode();
 xTmrPWMEna();
}

void xPulseTrig()
{
 xTmrPulse();
 xTmrSetIE();
}

void xPulse()
{
 xTmrScl(0);
 xTmrCnt(tmrMin);
 xTmrSet(tmrMin);
 xTmrCCR(tmrStepWidth);
 xTmrPulse();
 xTmrPWMMode();
 xTmrPWMEna();
 xTmrSetIE();
}

void xStartSlave()
{
 xTmrSlvEna();
 dbgXAccelSet();
 xIsr.active = SYNC_ACTIVE_STEP;
 dbgmsg(D_XEST, (int)sp.intCount); /* spindle interrupt count at start */
}

void xMoveAbsCmd()
{
 if (xMoveCtl.state == AXIS_IDLE)
 {
  int pos = lrintf(rVar.xMovePos * (float) xAxis.stepsInch) + rVar.xHomeOffset;
  xMove(pos, rVar.xFlag);
 }
}

void xMoveRelCmd()
{
 if (xMoveCtl.state == AXIS_IDLE)
 {
  int dist = lrintf(rVar.xMoveDist * (float) xAxis.stepsInch);
  if ((rVar.xFlag & DRO_POS) != 0)
  {
   int droCounts = lrintf(rVar.xMoveDist * (float) xAxis.droCountsInch);
   xMoveCtl.droTarget = rVar.xDroLoc + droCounts;
   if (DBG_P)
   {
    printf("xMoveRelCmd dist %7.4f steps %7d droCounts %7d\n",
	   rVar.xMoveDist, dist, droCounts);
    printf("droTarget %7d droPos %7d droCounts %7d\n",
	   xMoveCtl.droTarget, rVar.xDroLoc, xMoveCtl.droTarget - rVar.xDroLoc);
   }
  }
  xMoveRel(dist, rVar.xFlag);
 }
}

void xJogCmd()
{
 if ((moveQue.count == 0)	/* if not moving */
 ||  (jogPause & PAUSE_ENA_X_JOG)
 ||  ((rVar.mvStatus & (MV_PAUSE | MV_MEASURE)) == (MV_PAUSE | MV_MEASURE)))
 {
  jogMove(&xMoveCtl, rVar.xJogDir);
 }
 else if (DBG_JOG)
  printf("xJogCmd count %d jogPause %x mvStatus %x\n",
	 moveQue.count, jogPause, rVar.mvStatus);
}

void xJogSpeedCmd()
{
 if ((moveQue.count == 0)	/* if not moving */
 || ((rVar.mvStatus & (MV_PAUSE | MV_MEASURE)) == (MV_PAUSE | MV_MEASURE)))
 {
  jogSpeed(&xMoveCtl, rVar.xJogSpeed);
 }
 else if (DBG_JOG)
  printf("xJogSpeedCmd count %d mvStatus %x\n",
	 moveQue.count, rVar.mvStatus);
}

void xLocCmd()
{
 if (xMoveCtl.state == AXIS_IDLE)
 {
  rVar.xLoc = (int) (rVar.xSetLoc * (float) xAxis.stepsInch);
 }
}

void xStop()
{
 if (DBG_P)
  printf("xStop dist %5d xLoc %5d\n", xIsr.dist, rVar.xLoc);

 xMoveCtl.stop = 1;
 xIsr.accel = 0;
 xIsr.decel = 1;
 dbgXAccelSet();
 dbgXStopSet();
}

void xSetup()
{
 if (DBG_SETUP)
  printf("\nX axis setup\n");

 P_AXIS axis = &xAxis;
 axis->pitch = rVar.xPitch;
 axis->ratio = rVar.xRatio;
 axis->microSteps = rVar.xMicro;
 axis->motorSteps = rVar.xMotor;
 axis->accel = rVar.xAccel;
 axis->backlash = rVar.xBacklash;
 axis->axis = 'x';
 if (rVar.xDirFlag)
 {
  axis->dirFwd = Dir2_Pin;
  axis->dirRev = Dir2_Pin << 16;
 }
 else
 {
  axis->dirFwd = Dir2_Pin << 16;
  axis->dirRev = Dir2_Pin;
 }
 int stepsInch = lrintf(((float) axis->microSteps * (float) axis->motorSteps *
			axis->ratio) / axis->pitch);
 axis->stepsInch = stepsInch;
 axis->backlashSteps = lrintf(axis->backlash * (float) axis->stepsInch);
 axis->droCountsInch = rVar.xDroCountInch;
 axis->stepFactor = rVar.xStepFactor;
 axis->droFactor = rVar.xDroFactor;

 xIsr.axis = 'x';

 if (DBG_SETUP)
  printf("xStepsInch %d xBacklash %0.4f xBacklashSteps %d\n",
	 stepsInch, axis->backlash, axis->backlashSteps);

 xPA.label = "xP";		/* taper accel */
 xPA.stepsInch = stepsInch;

 xRA.label = "xR";		/* runout accel */
 xRA.stepsInch = stepsInch;

 xMoveSetup();
 xHomeSetup();
}

void xMoveSetup()
{
 xTA.label = "xT";		/* synchronous accel */
 xTA.stepsInch = xAxis.stepsInch;

 P_ACCEL ac = &xMA;		/* move accel */
 ac->label = "xM";
 ac->minSpeed = rVar.xMoveMin;
 ac->maxSpeed = rVar.xMoveMax;
 ac->accel = xAxis.accel;
 ac->stepsInch = xAxis.stepsInch;
 ac->droCountsInch = xAxis.droCountsInch;
 accelCalc(ac);

 ac = &xJA;			/* jog accel */
 ac->label = "xJ";
 ac->minSpeed = rVar.xJogMin;
 ac->maxSpeed = rVar.xJogMax;
 ac->accel = xAxis.accel;
 ac->stepsInch = xAxis.stepsInch;
 ac->droCountsInch = xAxis.droCountsInch;
 accelCalc(ac);

 memcpy(&xJSA, ac, sizeof(xJSA)); /* jog speed accel */
 xJSA.label = "xJS";

 P_MOVECTL mov = &xMoveCtl;
 mov->axisName = 'x';
 if (rVar.limitsEnabled)
  mov->limitsEna = rVar.xLimEna;
 mov->mpgJogInc = &rVar.xMpgInc;
 mov->mpgJogMax = &rVar.xMpgMax;
 mov->mpgFlag = rVar.xMpgFlag;
 mov->axis = &xAxis;
 mov->isr = &xIsr;
 mov->jogFlag = PAUSE_ENA_X_JOG;
 mov->jogQue = &xJogQue;
 mov->acThread = &xTA;
 mov->acTaper = &xPA;
 mov->acMove = &xMA;
 mov->acJog = &xJA;
 mov->acJogSpeed = &xJSA;
 mov->isrStop = &xIsrStop;
 mov->move = &xMove;
 mov->moveRel = &xMoveRel;
 mov->mpgStepsCount = 14;
 mov->mpgUSecSlow = 20 * 1000;
 mov->jogCmd = CMD_JOG;
 mov->speedCmd = CMD_SPEED;
 if (rVar.xUseDro)
 {
  mov->jogCmd |= DRO_UPD;
  mov->speedCmd |= CMD_SPEED;
 }
 if (DBG_SETUP)
  printf("xUseDro %d jogCmd %x\n", rVar.xUseDro, (unsigned int) mov->jogCmd);
 mov->timer = X_TMR;
 mov->moveInit = &xMoveInit;
 mov->dirFwd = &dirXFwd;
 mov->dirRev = &dirXRev;
 mov->hwEnable = &xHwEnable;
// mov->start = &xStart;
 mov->start = &xTmrStart;
 mov->pulse = &xPulse;
 mov->locPtr = &rVar.xLoc;
 mov->droLocPtr = &rVar.xDroLoc;
 mov->homeOffset = &rVar.xHomeOffset;
 mov->droOffset = &rVar.xDroOffset;
}

void xMoveRel(int dist, int cmd)
{
 P_MOVECTL mov = &xMoveCtl;

 if (mov->limitsEna)		/* if limits enabled */
 {
  if (mov->limitDir != 0)	/* if at a limit */
  {
   if (rVar.limitOverride == 0)	/* if not overriding limits */
   {
    printf("xMoveRel limitDir %d dist %d\n", mov->limitDir, dist);
    if (((mov->limitDir > 0) && (dist > 0)) /* if same direction as limit */
    ||  ((mov->limitDir < 0) && (dist < 0)))
    {
     printf("x at limit\n");
     return;
    }
   }
  }
 }

  mov->loc = rVar.xLoc;		/* save current location */
 mov->expLoc = rVar.xLoc + dist; /* save expected location */
 if (DBG_MOVOP)
 {
  auto stepsInch = (float) xAxis.stepsInch;
  float xTmp = (float) (rVar.xLoc - runCtl.xHomeOffset) / stepsInch;
  float xExp = (float) (mov->expLoc - runCtl.xHomeOffset) / stepsInch;
  printf("xMoveRel cmd %03x l %7.4f d %7.4f %d diam %7.4f "
	 "expLoc %7.4f dir %2d\n",
	 cmd, xTmp, ((float) dist) / stepsInch, dist, 2.0 * xTmp,
	 xExp, mov->dir);
 }
 mov->cmd = cmd;		/* save command */
 if (rVar.cfgDro)
  dbgmsg(D_XDRO, rVar.xDroLoc);
 dbgmsg(D_XLOC, mov->loc);
 dbgmsg(D_XDST, dist);
 if (dist != 0)			/* if distance non zero */
 {
  if (dist > 0)			/* if moving positive */
  {
   mov->dist = dist;		/* save distance */
   mov->dirChange = (mov->dir != DIR_POS); /* dir chg */
   mov->dir = DIR_POS;		/* set to move positive direction */
   dirXFwd();			/* set to forward */
  }
  else
  {
   mov->dist = -dist;		/* make distance a positive number */
   mov->dirChange = (mov->dir != DIR_NEG); /* dir chg */
   mov->dir = DIR_NEG;		/* set move direction to negative */
   dirXRev();			/* set to reverse */
  }
  if (mov->dirChange		/* if direction change */
  &&  (xAxis.backlashSteps != 0)) /* and backlash present */
  {
   xMoveInit(&xMA, 0, xAxis.backlashSteps); /* setup backlash move */
   xStart();			/* start move */
   mov->state = AXIS_WAIT_BACKLASH; /* set to wait for backlash */
  }
  else				/* if no backlash */
  {
   mov->state = AXIS_START_MOVE; /* set to start move */
   xControl();			/* and start move */
  }
 }
}

void xSynSetup(int feedType, float feed)
{
 if (DBG_SETUP)
  printf("\nxSynSetup\n");

 P_ACCEL ac = &xTA;
 switch (feedType)
 {
 case FEED_PITCH:
  turnPitch(ac, feed);
  break;
 case FEED_TPI:
  threadTPI(ac, feed);
  break;
 case FEED_METRIC:
  threadMetric(ac, feed);
  break;
  default:
   break;
 }

 if (rVar.spindleEncoder == 0)	/* *ok* if not using encoder */
 {
  turnCalc(ac);
  turnAccel(ac, rVar.xAccel,  T_STEP_SPINDLE | T_DBG_PRINT, 0);
 }
 else				/* *chk* if spindle encoder */
 {
  if (syn.encoderDirect)
  {
   xIsr.encoderDirect = 1;
   encTurnCalc(ac);
  }
 }
}

void xInfo(char flag)
{
 if (flag == 1)
  printf("\n");
 printf("cr1 %2x sr %2x cnt %d cFactor %0.2f curCount %d %d stepsSec %d\n",
	(unsigned int) X_TMR->CR1, (unsigned int) X_TMR->SR, (int) X_TMR->CNT,
	xIsr.cFactor, xIsr.curCount, (int) xTmrMaxRead(),
	(int) (rVar.cfgFcy / xIsr.curCount));
 printf("done %d accel %d decel %d initialStep %d accelStep %d finalStep %d",
	xIsr.done, xIsr.accel, xIsr.decel,
	xIsr.initialStep, xIsr.accelStep, xIsr.finalStep);
 if (flag == 0)
  printf("\n");
}

void xMove(int pos, int cmd)
{
 int dist = pos - rVar.xLoc;
 xMoveRel(dist, cmd);
}

void xMoveDro(int pos, int cmd)
{
 dbgXFinalDroSet();
 int droDist = pos - xDro();
 /* dist = droDist * (stepsInch / countsInch) */
 int dist = (2 * droDist * xAxis.stepFactor) / xAxis.droFactor;
 dist = (dist + 1) >> 1;
 int droTarget = pos + rVar.xDroOffset;
 xMoveCtl.droTarget = droTarget;
 if (DBG_QUE)
 {
  /* counts = inches * (counts / inch) */
  auto droCount = (float) xAxis.droCountsInch;
  printf("xMoveDro cmd %03x pos %7.4f droPos %7.4f dist %7.4f steps %d "
	 "counts %d\n",
	 cmd, ((float) pos) / droCount,	 ((float) xDro()) / droCount,
	 ((float) droDist) / droCount, dist, droDist);
  printf("droFinalDist %5d droTarget %7d droPos %7d droCounts %7d\n",
	 rVar.xDroFinalDist, droTarget, rVar.xDroLoc, droTarget - rVar.xDroLoc);
 }
 dbgXFinalDroClr();
 dbgXUpdDroSet();
 xMoveRel(dist, cmd);
}

void xControl()
{
 P_MOVECTL mov = &xMoveCtl;

#if DBGMSG
 if (mov->state != mov->prev)
 {
  dbgmsg(D_XST, mov->state);
  mov->prev = mov->state;
 }
#endif

 int cmd = mov->cmd;		/* read command */
 switch(mov->state)		/* dispatch on state */
 {
 case AXIS_IDLE:		/* 0x00 idle state */
  break;

 case AXIS_WAIT_BACKLASH:	/* 0x01 wait for backlash mv to complete */
  if (xIsr.done)		/* if done */
  {
   dbgmsg(D_XBSTP, (int)xIsr.steps);
   xIsr.done = 0;		/* clear done flag */
   mov->state = AXIS_START_MOVE; /* advance to move state */
  }
  break;

 case AXIS_START_MOVE:		/* 0x02 start an x move */
 {
  if (DBG_P)
   printf("xstartmove %03x\n", cmd);

  switch (cmd & CMD_MSK)	/* select on move type */
  {
  case CMD_SYN:			/* synchronized move */
   xTurnInit(&xTA, mov->dir, mov->dist); /* init for turning */
   if ((cmd & X_SYN_START) != 0) /* if start on index pulse */
   {
    if ((cmd & Z_SYN_TAPER) != 0) /* if tapering */
    {
     xIsr.taper = TAPER_CTL;	/* indicate x controlling taper */
     float dist = (float) mov->dist / (float) xAxis.stepsInch; /* distance */
     int taperDist = (int) (dist * zPA.taperInch * (float) zAxis.stepsInch);
     zIsr.dist = taperDist;	/* save for isr */
     if (rVar.cfgDro)
      dbgmsg(D_ZDRO, rVar.zDroLoc);
     dbgmsg(D_ZLOC, rVar.zLoc);
     dbgmsg(D_ZDST, taperDist);

     if (DBG_P)
      printf("taperDist %4d %7.4f taperInch %8.6f xDist %4d %7.4f\n",
	     taperDist, (float) taperDist / (float) xPA.stepsInch,
             xPA.taperInch,
	     mov->dist, (float) mov->dist / (float) xAxis.stepsInch);

     if ((rVar.spindleEncoder == 0) /* *ok* if no spindle encoder */
     &&  (rVar.stepperDrive == 0))  /* and motor drive */
     {
      xStart();			/* start x */
      zStart();			/* start z */
     }
     dbgZTaperSet();
    }

    if (rVar.stepperDrive	/* if stepper drive */
    ||	rVar.spindleEncoder)	/* *chk* spindle encoder */
    {
     slaveEna();		/* enable slave mode */
    }
   }
   else				/* if not start on index pulse */
   {
    if (rVar.spindleEncoder == 0) /* *ok* if no spindle encoder */
    {
     xStart();			/* start now */
     if (rVar.stepperDrive == 0) /* if motor drive */
      trackSpeed = 1;		/* set to track speed */
     else
     {
      xIsr.active = SYNC_ACTIVE_STEP; /* set to active */
      dbgmsg(D_ZEST, (int)sp.intCount); /* send spindle interrupt count at start */
     }
    }
    else			/* *chk* if spindle encoder */
    {
     xIsr.active = xIsr.syncInit; /* make active */
     xIsr.syncInit = 0;		/* clear init flag */
     dbgmsg(D_XEST, (int) spEncCount); /* encoder count at start */
    }
   }
   break;

  case CMD_JOG:			/* jog */
   xMoveInit(&xJA, mov->dir, mov->dist); /* setup move */
   xIsr.home = 0;
   if ((cmd & FIND_HOME) != 0)
    xIsr.home |= HOME_SET;
   if ((cmd & CLEAR_HOME) != 0)
    xIsr.home |= HOME_CLR;
   if ((cmd & FIND_PROBE) != 0)
    xIsr.home |= PROBE_SET;
   if ((cmd & CLEAR_PROBE) != 0)
    xIsr.home |= PROBE_CLR;
   printf("x jog cmd %02x home %02x\n", cmd, xIsr.home);
   mov->jog = 1;
   xStart();
   break;

  case CMD_MAX:			/* move at max speed */
  case CMD_MOV:			/* move */
   xMoveInit(&xMA, mov->dir, mov->dist); /* setup move */
   xStart();
   break;

  case CMD_SPEED:
   xMoveInit(&xJSA, mov->dir, mov->dist); /* setup move */
   xStart();			/* start move */
   if (DBG_MOVOP)
    xInfo(0);
   break;

  case JOGSLOW:			/* slow jog to probe or find home */
   xMoveInit(&xSA, mov->dir, mov->dist); /* setup move */
   xIsr.home = 0;
   if ((cmd & FIND_HOME) != 0)
    xIsr.home |= HOME_SET;
   if ((cmd & CLEAR_HOME) != 0)
    xIsr.home |= HOME_CLR;
   if ((cmd & FIND_PROBE) != 0)
    xIsr.home |= PROBE_SET;
   if ((cmd & CLEAR_PROBE) != 0)
    xIsr.home |= PROBE_CLR;
   printf("x jogslow cmd %02x home %02x\n", cmd, xIsr.home);
   mov->jog = 1;
   xStart();
   break;
  }
  mov->state = AXIS_WAIT_MOVE;	/* wait for move to complete */
 }
 break;

 case AXIS_WAIT_MOVE:		/* 0x03 wait for an x move to complete */
  if (xIsr.done)		/* if done */
  {
   if (DBG_MOVOP & DBG_DISABLE)
   {
    unsigned int spindleSteps = xIsr.stopPos + xIsr.stopRev * sp.stepsRev;
    spindleSteps -= xIsr.startPos + xIsr.startRev * sp.stepsRev;
    unsigned int revs = spindleSteps / sp.stepsRev;
    unsigned int steps = spindleSteps % sp.stepsRev;
    float fRev = (float) spindleSteps / (float) sp.stepsRev;
    float fDist = (float) mov->dist / (float) xAxis.stepsInch;

    if (DBG_P)
     printf("x dist %7.4f %6d feed %7.4f spindle revs %d steps %d\n",
	    fDist, mov->dist, fDist / fRev, revs, steps);
   }
   if (rVar.xDoneDelay != 0)		/* if delay */
   {
    mov->state = AXIS_DELAY;	/* wait for position to settle */
    mov->delayStart = millis();	/* set start of delay */
    mov->delayTimeout = rVar.xDoneDelay; /* set delay length */
   }
   else				/* if no delay */
    mov->state = AXIS_DONE;
  }
  break;

 case AXIS_DELAY:	       /* 0x04 delay for position to settle */
  if ((millis() - mov->delayStart) >= mov->delayTimeout) /* if delay done */
  {
   mov->state = AXIS_DONE;	/* advance to done state */
  }
  break;

 case AXIS_DONE:		/* 0x05 done state */
 default:			/* all others */
  if (mov->cmd & DRO_UPD)	/* fix x loc if using dro for position */
  {
   dbgmsg(D_XDRO, rVar.xDroLoc);
   dbgmsg(D_XLOC, rVar.xLoc);
   dbgXUpdDroClr();
   /* xLoc = droPos * (stepsInch / countsInch) */
   int xTmp = ((2 * xDro() * xAxis.stepFactor) / xAxis.droFactor);
   xTmp = ((xTmp + 1) >> 1) + rVar.xHomeOffset; /* round and add offset */
   int xErr = xTmp - rVar.xLoc;
   rVar.xLoc = xTmp;
   dbgmsg(D_XERR, xErr);
   if (DBG_P)
    printf("DRO_UPD droPos %7.4f xPos %7.4f xErr %7.4f xLoc %6d\n",
	   (2.0 * (float) xDro()) / xAxis.droCountsInch,
	   (2.0 * (float) (rVar.xLoc - rVar.xHomeOffset)) / xAxis.stepsInch,
	   (2.0 * (float) xErr / xAxis.stepsInch), rVar.xLoc);
  }
  if (limitIsClr())
  {
   mov->limitDir = 0;		/* clear limit flags */
   mov->limitMove = 0;
  }

  dbgXDoneClr();
  xIsr.done = 0;		/* clear done flag */
  mov->stop = 0;		/* clear stop flag */
  mov->cmd = 0;			/* clear command */
  mov->loc = rVar.xLoc;		/* save it */
  if (!mov->jog)		/* if not jogging */
  {
   if (mov->loc != mov->expLoc)	/* if not at expected location */
   {
    printf("x move error actual %d expected %d\n", mov->loc, mov->expLoc);
    dbgmsg(D_XEXP, mov->expLoc);
   }
  }
  mov->jog = 0;			/* clear jog flag */
  trackSpeed = 0;		/* disable speed tracking */
  mov->state = AXIS_IDLE;	/* set state to idle */
  dbgmsg(D_XSTP, (int)xIsr.steps);
  dbgmsg(D_XST, mov->state);
  break;
 }
}

void xHomeSetup()
{
 if (DBG_SETUP)
  printf("xHomeSetup\n");
 P_HOMECTL home = &xHomeCtl;
 home->mov = &xMoveCtl;
 home->status = &rVar.xHomeStatus;
 //home->done = &xHomeDone;
 home->homeIsSet = xAHomeIsSet;
 home->homeIsClr = xAHomeIsClr;

 P_ACCEL ac = &xSA;
 ac->label = "xS";
 ac->minSpeed = rVar.xHomeSpeed;
 ac->maxSpeed = rVar.xHomeSpeed;
 ac->accel = xAxis.accel;
 ac->stepsInch = xAxis.stepsInch;

 accelCalc(ac);

 auto stepsInch = (float) xAxis.stepsInch;
 int dir = rVar.xHomeDir;
 home->findDist = dir * (int) (rVar.xHomeDist * stepsInch);
 home->findDistRev = -dir * (int) (rVar.xHomeDistRev * stepsInch);
 home->backoffDist = -dir * (int) (rVar.xHomeDistBackoff * stepsInch);
 home->slowDist = dir * (int) (1.25 * rVar.xHomeDistBackoff * stepsInch);
}

void homeAxis(P_HOMECTL home, int homeCmd)
{
 P_MOVECTL mov = home->mov;
 if (mov->state == AXIS_IDLE)	/* if axis idle */
 {
  *home->status = HOME_ACTIVE;
  home->setActive = MV_ZHOME_ACTIVE;
  home->clrActive = ~MV_ZHOME_ACTIVE;
  home->setHomed = MV_ZHOME;
  home->clrHomed = ~MV_ZHOME;
  int dist = 0;
  int flag = 0;
  if (homeCmd == HOME_FWD)	/* if forward homing*/
  {
   if (home->homeIsClr())	/* if home switch open */
   {
    dist = home->findDist;
    flag = CMD_JOG | FIND_HOME;
    home->state = H_HOME;	/* find home forward */
   }
   else
   {
    dist = -home->findDist;
    flag = CMD_JOG | CLEAR_HOME;
    home->state = H_OFF_HOME;	/* move off home swtich */
   }
  }
  else				/* if reverse homing */
  {
   if (home->homeIsClr())	/* if home switch hope */
   {
    dist = home->findDistRev;
    flag = CMD_JOG | FIND_HOME;
    home->state = H_HOME;	/* find home */
   }
   else
   {
    dist = -home->findDist;
    flag = CMD_JOG | CLEAR_HOME;
    home->state = H_OFF_HOME;	/* move off home switch */
   }
  }
  if (DBG_SETUP)
  {
   P_AXIS axis = mov->axis;
   printf("homeAxis %c dist %7.4f flag %02x\n", axis->axis,
	  ((float) dist) / (float) axis->stepsInch, flag);
  }
  mov->moveRel(dist, flag);
  int tmp = rVar.mvStatus;
  tmp &= home->clrHomed;  /* set not homed */
  tmp |= home->setActive; /* set home active */
  rVar.mvStatus = (int16_t) tmp;
 }
}

void homeControl(P_HOMECTL home)
{
#if DBGMSG
 if (home->state != home->prev)
 {
  printf("home state %d prev %d\n", home->state, home->prev);
  dbgmsg(D_HST, home->state);
  home->prev = home->state;
 }
#endif
 P_MOVECTL mov = home->mov;

 if (mov->state == AXIS_IDLE)	/* if stopped moving */
 {
  switch (home->state)
  {
  case H_IDLE:			/* 0x00 idle */
   break;

  case H_HOME:			/* 0x01 found home switch */
   if (home->homeIsSet())	/* if home switch set */
   {
    mov->moveRel(-home->findDist, CMD_JOG | CLEAR_HOME); /* move off switch */
    home->state = H_OFF_HOME;	/* off home state */
   }
   else
   {				/* if did not find switch */
    *(home->status) = HOME_FAIL; /* set failure status */
    home->state = H_IDLE;	/* return to idle state */
   }
   break;

  case H_OFF_HOME:		/* 0x02 move off home switch */
   if (home->homeIsClr())	/* if home switch open */
   {
    mov->moveRel(home->backoffDist, CMD_JOG); /* move to backoff dist */
    home->state = H_BACKOFF;	/* backoff state */
   }
   else
   {
    *(home->status) = HOME_FAIL; /* set failure status */
    home->state = H_IDLE;	/* return to idle state */
   }
   break;

  case H_BACKOFF:		/* 0x03 wait for backoff complete */
   if (home->homeIsClr())	/* if clear of switch */
   {
    mov->moveRel(home->slowDist, JOGSLOW | FIND_HOME); /* move back slowly */
    home->state = H_SLOW;	/* advance to wait */
   }
   else
   {				/* if did not find switch */
    *(home->status) = HOME_FAIL; /* set failure status */
    home->state = H_IDLE;	/* return to idle state */
   }
   break;

  case H_SLOW:			/* 0x04 wait to find switch */
  {
   int tmp = (int) rVar.mvStatus;
   tmp &= (int) home->clrActive; /* home complete */
   if (home->homeIsSet())        /* if successful */
   {
    *(home->status) = HOME_SUCCESS; /* set flag */
    tmp |= (int) home->setHomed; /* indicate homed */
    *home->status = HOME_SUCCESS; /* set to success */
    *mov->locPtr = 0;                /* set position to zero */
    *mov->droLocPtr = 0;        /* set dro position to zero */
   } else                                /* if failure */
   {
    *(home->status) = HOME_FAIL; /* set failed flag */
   }
   rVar.mvStatus = (int16_t) tmp;
   home->state = H_IDLE;        /* back to idle state */
  }
   break;
  } /* switch */
 }  /* AXIS_IDLE */
}

void axisCtl()
{
 dbgAxisCtlSet();
 if ((millis() - idxTmr.updateTime) > idxTmr.timeout) /* if index not updated */
 {
  idxTmr.timeout = MAX_TIMEOUT;	/* set to maximum */
  if (rVar.indexPeriod != 0)
  {
   rVar.indexPeriod = 0;	/* set index period to zero */
   idxTmr.start = 0;		/* reset start time */
   rVar.revCounter = 0;
   printf("mainLoop clear indexPeriod\n");
  }
 }

 P_MOVECTL mov;
 if (rVar.limitsEnabled)	/* if limits enabled */
 {
  if (rVar.commonLimits)	/* if common limits */
  {
   if (limitIsSet())		/* if limit is set */
   {
    rVar.mvStatus |= MV_XLIMIT;	/* set at limit bit */
    if (xIsr.dist)		/* if x isr active */
    {
     mov = &xMoveCtl;
     if (mov->limitMove == 0)	/* if not a limit move */
     {
      if (mov->limitDir == 0)	/* if not at limit */
      {
       xIsrStop('7');		/* stop x isr */
       mov->limitDir = xIsr.dir; /* save direction when limit tripped */
      }
     }
    }

    if (zIsr.dist)		/* if z isr active */
    {
     zMoveCtl.limitDir = zIsr.dir; /* save direction when limit tripped */
     zIsrStop('7');		/* stop z isr */
    }
   }
   else				/* if limit clear */
    rVar.mvStatus &= MV_XLIMIT;	/* clear at limit bit */
  }
  else				/* if inidvidual limits */
  {
   if (rVar.zLimEna)		/* if z limits enabled */
   {
    int dir = 0;
    if (zPosLimIsSet() != rVar.zLimPosInv)
     dir = DIR_POS;
    else if (zNegLimIsSet() != rVar.zLimNegInv) /* if at limit */
     dir = DIR_NEG;
    if (dir != 0)		/* if at limit */
    {
     mov = &zMoveCtl;
     if ((mov->limitDir == 0)	/* if not at limits */
     ||  (zIsr.dir == dir))	/* or trying to move further to limit */
     {
      mov->limitDir = dir;	/* set direction where limit occured */
      rVar.mvStatus |= MV_ZLIMIT;	/* set at limit bit */
      if (zIsr.dist != 0)	/* if moving */
      {
       zIsrStop('7');		/* stop movement */
      }
     }
    }
    else
    {
     zMoveCtl.limitDir = 0;	/* clear limit */
     rVar.mvStatus &= ~MV_ZLIMIT; /* clear at limit bit */
    }
   }

   if (rVar.xLimEna)		/* if x limits enabled */
   {
    int dir = 0;
    if (xPosLimIsSet() != rVar.xLimPosInv)
     dir = DIR_POS;
    else if (xNegLimIsSet() != rVar.xLimNegInv) /* if at limit */
     dir = DIR_NEG;
    if (dir != 0)		/* if at limit */
    {
     mov = &xMoveCtl;
     if ((mov->limitDir == 0)	/* if not at limits */
     ||  (xIsr.dir == dir))	/* or trying to move further to limit */
     {
      mov->limitDir = dir;	/* set direction where limit occured */
      rVar.mvStatus |= MV_XLIMIT; /* set at limit bit */
      if (xIsr.dist != 0)	/* if moving */
      {
       xIsrStop('7');		/* stop movement */
      }
     }
    }
    else
    {
     xMoveCtl.limitDir = 0;	/* clear limit */
     rVar.mvStatus &= ~MV_XLIMIT; /* clear at limit bit */
    }
   }
  }
 }

 mov = &zMoveCtl;
 if (mov->state != AXIS_IDLE)	/* if z axis active */
  zControl();			/* run z axis state machine */

 if (zHomeCtl.state != H_IDLE)	/* if home control not idle */
  homeControl(&zHomeCtl);	/* run home state machine */

 // if (mov->mpgBackWait)		/* if waiting for mpg backlash */
 // {
 //  if (zIsr.done != 0)		/* if z done */
 //  {
 //   zIsr.done = 0;		/* clear done flag */
 //   mov->mpgBackWait = 0;	/* clear backlash flag */
 //  }
 // }
 // else
 if ((zJogQue.count != 0) ||	/* if anything in queue */
     (mov->mpgState != MPG_CHECK_QUE)) /* or not in queue check state*/
 {
  jogMpg3(mov);			/* run timed jog routine */
 }

 mov = &xMoveCtl;
 if (mov->state != AXIS_IDLE)	/* if x axis active */
  xControl();			/* run x axis state machine */

 if (xHomeCtl.state != H_IDLE)	/* if home control not idle */
  homeControl(&xHomeCtl);	/* run home state machine */

// if (mov->mpgBackWait)		/* if waiting for mpg backlash */
// {
//  if (xIsr.done != 0)		/* if x done */
//  {
//   xIsr.done = 0;		/* clear done flag */
//   mov->mpgBackWait = 0;	/* clear backlash flag */
//  }
// }
// else
 if ((xJogQue.count != 0) ||	/* if anything in queue */
     (mov->mpgState != MPG_CHECK_QUE)) /* or not in queue check state*/
 {
  jogMpg3(mov);			/* run timed jog routine */
 }

 dbgAxisCtlClr();
}

void runInit()
{
 P_RUN_CTL mv = &runCtl;

 mv->state = M_IDLE;
 mv->pass = 0;
 mv->taper = 0.0;
 mv->zVal = 0.0;
 mv->xVal = 0.0;
 mv->zHomeOffset = 0;
 mv->xHomeOffset = 0;
 mv->threadFlags = 0;
 mv->feedType = 0;
 mv->tanAngle = 0.0;

 clr(moveQue);
}

#define FLOAT_CMD 0x8000

char queMoveCmd(uint32_t op, float val)
{
 P_MOVEQUE que = &moveQue;
 if (que->count < MAX_CMDS)
 {
  P_MOVECMD cmd = &que->cmd[que->fil];
  que->fil++;
  if (que->fil >= MAX_CMDS)
   que->fil = 0;
  cmd->op = op | FLOAT_CMD;
  cmd->val = val;
  que->count++;
  return(1);
 }

 if (DBG_QUE)
  printf("move of op %8x val %7.4f\n", (unsigned int) op, val);
 return(0);
}

char queIntCmd(uint32_t op, int val)
{
 P_MOVEQUE que = &moveQue;
 if (que->count < MAX_CMDS)
 {
  P_MOVECMD cmd = &que->cmd[que->fil];
  que->fil++;
  if (que->fil >= MAX_CMDS)
   que->fil = 0;
  cmd->op = op;
  cmd->iVal = val;
  que->count++;
  return(1);
 }

 if (DBG_QUE)
  printf("move of op %8x val %d\n", (unsigned int) op, val);
 return(0);
}

void stopMove()
{
 memset(&moveQue, 0, sizeof(moveQue));
}

void procMove()
{
 dbgProcMoveSet();
 P_RUN_CTL mv = &runCtl;

 if (rVar.cmdPaused		/* if paused */
 &&  (mv->state == M_IDLE))	/* and idle state */
  return;			/* exit */

 switch (mv->state)
 {
 case M_IDLE:
 {
  P_MOVEQUE que = &moveQue;
  while (que->count != 0)
  {
   char done = 1;		/* execute one command */
   int val;

   __disable_irq();		/* disable interrupt */
   --que->count;
   __enable_irq();		/* enable interrupts */
   P_MOVECMD cmd = &que->cmd[que->emp];
   que->emp++;
   if (que->emp >= MAX_CMDS)
    que->emp = 0;

   if (DBG_QUE & 1)
   {
    dbgmsg(D_MCMD, (cmd->flag << 8) | cmd->cmd);
    printf("cmd ");
    if (mv->start != 0)
    {
     unsigned int tMs = uwTick - mv->start;
     unsigned int tS = tMs / 1000;
     tMs %= 1000;
     printf("%3u.%03u ", tS, tMs);
    }

    if (DBG_QUE)
    {
     if (cmd->op & FLOAT_CMD)
     {
      cmd->cmd &= ~FLOAT_CMD;
      printf("move %2d op %-14s %2x %4x val %7.4f\n",
	     que->count, mCommandsList[(int) cmd->cmd],
	     (unsigned int) cmd->cmd, (unsigned int) cmd->flag,
	     cmd->val);
     }
     else
     {
      printf("move %2d op %-14s %2x %4x val %7d\n",
	     que->count, mCommandsList[(int) cmd->cmd],
	     (unsigned int) cmd->cmd, (unsigned int) cmd->flag,
	     (int) cmd->iVal);
     }
    }
   }

   switch (cmd->cmd)
   {
   case MOVE_Z:
#if 0
    val = lrintf(cmd->val * zAxis.stepsInch) + mv->zHomeOffset;
    if (rVar.cfgFpga == 0)
     zMove(val, cmd->flag);
    else
     zMoveX(val, cmd->flag);
#else
    val = cmd->iVal + mv->zHomeOffset;
    dbgmsg(D_ZMOV, val);
    if (!rVar.cfgDro		      /* if dro not confugred */
    ||  ((cmd->flag & DRO_POS) == 0)) /* or not using dro for position */
    {
     if (rVar.cfgFpga == 0)
     {
      /*
	printf("zMove z %7.4f zHomeOffset %7.4f val %d zLoc %d %7.4f\n",
	cmd->val, mv->zHomeOffset, val,
	zLoc, (float) zLoc / zAxis.stepsInch);
      */
      zMove(val, cmd->flag);
     }
     else
      zMoveX(val, cmd->flag);
    }
    else			/* if using dro for position */
    {
     zMoveDro(cmd->iVal, cmd->flag);
    }

#endif
    mv->state = M_WAIT_Z;
    break;

   case MOVE_X:
    val = cmd->iVal + mv->xHomeOffset;
    dbgmsg(D_XMOV, val);
    if (!rVar.cfgDro		      /* if not confugre */
    ||  ((cmd->flag & DRO_POS) == 0)) /* or not using dro for position */
    {
     if (rVar.cfgFpga == 0)
     {
      /*
	printf("xMove x %7.4f xHomeOffset %7.4f val %d xLoc %d %7.4f\n",
	cmd->val, mv->xHomeOffset, val,
	xLoc, (float) xLoc / xAxis.stepsInch);
      */
      xMove(val, cmd->flag);
     }
     else
      xMoveX(val, cmd->flag);
    }
    else			/* if using dro for position */
    {
     xMoveDro(cmd->iVal, cmd->flag);
    }
    mv->state = M_WAIT_X;
    break;

   case SAVE_Z:
    if (DBG_QUE)
     printf("save z %7.4f\n", cmd->val);

    mv->zVal = cmd->val * (float) zAxis.stepsInch + (float) mv->zHomeOffset;
    done = 0;
    break;

   case SAVE_X:
    if (DBG_QUE)
     printf("save X %7.4f\n", cmd->val);

    mv->xVal = cmd->val * (float) xAxis.stepsInch + (float) mv->xHomeOffset;
    done = 0;
    break;

   case SAVE_Z_OFFSET:
    if (DBG_QUE)
     printf("save z offset %7.4f\n",
            ((float) cmd->iVal) / (float) zAxis.stepsInch);

    mv->zHomeOffset = cmd->iVal;
    done = 0;
    break;

   case SAVE_X_OFFSET:
    if (DBG_QUE)
     printf("save x offset %7.4f\n",
            ((float) cmd->iVal) / (float) xAxis.stepsInch );

    mv->xHomeOffset = cmd->iVal;
    done = 0;
    break;

   case SAVE_TAPER:
    if (DBG_QUE)
     printf("save taper %7.4f\n", cmd->val);

    mv->taper = cmd->val;
    done = 0;
    break;

   case MOVE_ZX:
    if (DBG_QUE)
     printf("move zx %7.4f\n", cmd->val);

    val = lrintf(cmd->val * (float) zAxis.stepsInch) + mv->zHomeOffset;
    moveZX(val, (int)mv->xVal);
    mv->state = M_WAIT_Z;
    break;

   case MOVE_XZ:
    if (DBG_QUE)
     printf("move xz %7.4f\n", cmd->val);

    val = lrintf(cmd->val * (float) xAxis.stepsInch) + mv->xHomeOffset;
    moveXZ(lrintf(mv->zVal), val);
    mv->state = M_WAIT_X;
    break;

   case TAPER_ZX:		/* move z taper x */
   {
    if (DBG_QUE)
     printf("taper zx %7.4f\n", cmd->val);

    xPA.stepsInch = xAxis.stepsInch;
    val = lrintf(cmd->val * (float) zAxis.stepsInch) + mv->zHomeOffset;
    int dist = lrintf(mv->xVal) - rVar.xLoc;
    int dir = dist >= 0 ? DIR_POS : DIR_NEG;

    if ((rVar.stepperDrive == 0)    /* if motor drive */
    &&  (rVar.spindleEncoder == 0)) /* and no encoder */
    {
     motorSetup(&zTA, rVar.zAccel, runCtl.zFeed);
    }

    if (rVar.cfgFpga == 0)
    {
     taperCalc(&zTA, &xPA, mv->taper);
     xTaperInit(&xPA, dir);
     zMove(val, CMD_SYN | Z_SYN_START | X_SYN_TAPER);
    }
    else
    {
     taperCalcX(&zTA, &xPA, mv->taper);
     xTaperInitX(&xPA, dir);
     zMoveX(val, CMD_SYN | Z_SYN_START | X_SYN_TAPER);
    }
    mv->state = M_WAIT_Z;
    break;
   }

   case TAPER_XZ:		/* move x taper z */
   {
    if (DBG_QUE)
     printf("taper xz %7.4f\n", cmd->val);

    zPA.stepsInch = zAxis.stepsInch;
    val = cmd->iVal + mv->xHomeOffset;
    int dist = lrintf(mv->zVal) - rVar.zLoc;
    int dir = dist >= 0 ? DIR_POS : DIR_NEG;

    if ((rVar.stepperDrive == 0)    /* if motor drive */
    &&  (rVar.spindleEncoder == 0)) /* and no encoder */
    {
     motorSetup(&xTA, rVar.xAccel, runCtl.xFeed);
    }

    if (rVar.cfgFpga == 0)
    {
     taperCalc(&xTA, &zPA, mv->taper);
     zTaperInit(&zPA, dir);
     xMove(val, CMD_SYN | X_SYN_START | Z_SYN_TAPER);
    }
    else
    {
     taperCalcX(&xTA, &zPA, mv->taper);
     zTaperInitX(&zPA, dir);
     xMoveX(val, CMD_SYN | X_SYN_START | Z_SYN_TAPER);
    }

    mv->state = M_WAIT_X;
    break;
   }

   case START_SPINDLE:
    if (DBG_QUE)
     printf("start spindle %d rpm\n", (int) cmd->iVal);

    if (rVar.cfgFpga == 0)
    {
     spindleSetup(cmd->iVal);
     spindleStart();
    }
    else
    {
     spindleSetupX(cmd->iVal);
     spindleStartX();
    }
    mv->spindleCmd = cmd->cmd;
    mv->state = M_WAIT_SPINDLE;
    break;

   case STOP_SPINDLE:
    if (rVar.cfgFpga == 0)
     spindleStop();
    else
     spindleStopX();
    mv->spindleCmd = cmd->cmd;
    mv->state = M_WAIT_SPINDLE;
    break;

   case SAVE_FEED_TYPE:
    mv->feedType = cmd->iVal;
    done = 0;
    break;

   case Z_SYN_SETUP:
    mv->zFeed = cmd->val;
    zSynSetup(mv->feedType, cmd->val, rVar.runoutDistance, rVar.runoutDepth);
    done = 0;
    break;

   case X_SYN_SETUP:
    mv->xFeed = cmd->val;
    if (rVar.cfgFpga == 0)
     xSynSetup(mv->feedType, cmd->val);
    else
     xSynSetup(mv->feedType, cmd->val);
    done = 0;
    break;

   case SEND_SYNC_PARMS:
#if defined(SYNC_SPI)
    syncSendMulti(syncParms);
    mv->state = M_WAIT_SYNC_PARMS;
#endif  /* SYNC_SPI */
    break;

   case SYNC_COMMAND:
#if defined(SYNC_SPI)
    syncCommand((char) cmd->iVal);
    mv->state = M_WAIT_SYNC_CMD;
#endif  /* SYNC_SPI */
    break;

   case PASS_NUM:
   {
    int iVal = cmd->iVal;
    mv->pass = iVal;
    int passNum = iVal & 0xff;

    if (DBG_QUE)
     printf("pass %2d flag %d\n", passNum, iVal >> 8);

    if ((iVal & 0xff00) == 0)
    {
     rVar.currentPass = (int16_t) passNum;
     springInfo = 0;
     if ((rVar.mvStatus & MV_MEASURE) /* if measure flag set */
     &&  (passNum > 1))		 /* and pass one or greater */
     {
      if (DBG_QUE)
       printf("measure start %d\n", passNum);

      rVar.cmdPaused = 1;		/* pause */
      rVar.mvStatus |= MV_PAUSE;
      if (rVar.cfgFpga == 0)
       spindleStop();
      else
       spindleStopX();
      mv->safeZ = rVar.zLoc - rVar.zHomeOffset;
      mv->safeX = rVar.xLoc - rVar.xHomeOffset;
      mv->state = M_WAIT_SPINDLE;
     }
     else
      done = 0;
    }
    else
    {
     springInfo = (int16_t) iVal;
     done = 0;
    }
    dbgmsg(D_PASS, iVal);
    break;
   }

   case QUE_PAUSE:
    if (DBG_QUE)
     printf("pause %x\n", (unsigned int) cmd->iVal);

    rVar.cmdPaused = 1;
    jogPause = DISABLE_JOG | cmd->iVal;
    if (cmd->iVal & PAUSE_READ_X)
     rVar.mvStatus |= MV_READ_X;
    if (cmd->iVal & PAUSE_READ_Z)
     rVar.mvStatus |= MV_READ_Z;
    rVar.mvStatus |= MV_PAUSE;
    break;

   case MOVE_Z_OFFSET:
   {
    rVar.xFeed = rVar.thXStart - rVar.xLoc;
    int zOffset = -(int) ((float) rVar.xFeed * rVar.tanThreadAngle);

    if (DBG_QUE)
     printf("xFeed %d %7.4f zOffset %d %7.4f\n",
            (int) rVar.xFeed, (float) rVar.xFeed / (float) xAxis.stepsInch,
	    zOffset, (float) zOffset / (float) zAxis.stepsInch);

    if ((mv->threadFlags & TH_LEFT) != 0)
     zOffset = -zOffset;
    if ((mv->threadFlags & TH_INTERNAL) != 0)
     zOffset = -zOffset;
    int zLoc = rVar.thZStart + zOffset;
    zMove(zLoc, CMD_JOG);
    mv->state = M_WAIT_Z;
   }
    break;

   case Z_FEED_SETUP:
    if (DBG_QUE)
     printf("z feed setup\n");

#if 0
    lastRevCount = 0;
    revCounter = 0;
    lastIndexPeriod = 0;	/* clear last index period */
    mv->zFeed = cmd->val;
    mv->spindleCmd = cmd->cmd;	/* save cmd for wait spindle */
    mv->state = M_WAIT_SPINDLE;	/* wait for spindle to start */
#endif
    done = 0;
    break;

   case X_FEED_SETUP:
    if (DBG_QUE)
     printf("x feed setup\n");

#if 0
    lastRevCount = 0;
    revCounter = 0;
    lastIndexPeriod = 0;	/* clear last index period */
    mv->xFeed = cmd->val;
    mv->spindleCmd = cmd->cmd;	/* save cmd for wait spindle */
    mv->state = M_WAIT_SPINDLE;	/* wait for spindle to start */
#endif
    done = 0;
    break;

   case SAVE_FLAGS:
    if (DBG_QUE)
     printf("save flags %02x\n", (unsigned int) cmd->iVal);

    mv->threadFlags = cmd->iVal;
    done = 0;
    break;

   case PROBE_Z:
   {
    if (DBG_QUE)
     printf("probe z %7.4f\n", cmd->val);

    P_ACCEL ac = &zSA;
    ac->label = "zS";
    ac->minSpeed = rVar.probeSpeed;
    ac->maxSpeed = rVar.probeSpeed;
    ac->accel = zAxis.accel;
    ac->stepsInch = zAxis.stepsInch;
    accelCalc(ac);
    val = lrintf(cmd->val * (float) zAxis.stepsInch);
    zIsr.doneHome = 0;
    rVar.zHomeStatus = 0;
    if (PROBE_TEST)
    {
     setProbeDist(val / 2);

     if (DBG_QUE)
      printf("dist %d probeDist %d\n", val, rVar.probeDist);
    }
    if (probeSet())
    {
     rVar.zHomeStatus = PROBE_FAIL;
     return;
    }
    zMoveRel(val, JOGSLOW | FIND_PROBE);
    mv->probeCmd = PROBE_Z;
    mv->state = M_WAIT_PROBE;
    break;
   }

   case PROBE_X:
   {
    if (DBG_QUE)
     printf("probe x %7.4f\n", cmd->val);

    P_ACCEL ac = &xSA;
    ac->label = "xS";
    ac->minSpeed = rVar.xHomeSpeed;
    ac->maxSpeed = rVar.xHomeSpeed;
    ac->accel = xAxis.accel;
    ac->stepsInch = xAxis.stepsInch;
    accelCalc(ac);
    val = lrintf(cmd->val * (float) xAxis.stepsInch);
    xIsr.doneHome = 0;
    rVar.xHomeStatus = 0;
    if (PROBE_TEST)
    {
     setProbeDist(val / 2);

     if (DBG_QUE)
      printf("dist %d probeDist %d\n", val, rVar.probeDist);
    }
    if (probeSet())
    {
     rVar.xHomeStatus = PROBE_FAIL;
     return;
    }
    xMoveRel(val, JOGSLOW | FIND_PROBE);
    mv->probeCmd = PROBE_X;
    mv->state = M_WAIT_PROBE;
    break;
   }

   case SAVE_Z_DRO:
    dbgmsg(D_ZPDRO, rVar.zDroLoc);
    break;

   case SAVE_X_DRO:
    dbgmsg(D_XPDRO, rVar.xDroLoc);
    break;

   case QUE_PARM:
    T_DATA_UNION parmVal;
    parmVal.t_unsigned_int = cmd->iVal;
    setRemVar(cmd->flag, parmVal);
    break;

   case MOVE_ARC:
    arcInit(rVar.arcRadius);
    arcUpdate(UPDATE_DEBUG);	/* fill queue */
    arcData.active = true;	/* set arc active flag */
    zTurnInit(&zTA, 0, 0);	/* init synchronized move */
    zPulseSetup();
    xPulseSetup();
#if 0
    printf("Z_TMR %d pwm %d\n", Z_TIMER, Z_TMR_PWM);
    printf(" CR1 %8x  CNT %8x  ARR %8x  CCR %8x\n",
	   (unsigned int) (Z_TMR->CR1), (unsigned int) (Z_TMR->CNT),
	   (unsigned int) (Z_TMR->ARR), (unsigned int) zTmrReadCCR());
    printf("CCMR %8x CCER %8x DIER %8x\n",
	   (unsigned int) zTmrReadCCMR(), (unsigned int) (Z_TMR->CCER),
	   (unsigned int) (Z_TMR->DIER));

    printf("X_TMR %d pwm %d\n", X_TIMER, X_TMR_PWM);
    printf(" CR1 %8x  CNT %8x  ARR %8x  CCR %8x\n",
	   (unsigned int) (X_TMR->CR1), (unsigned int) (X_TMR->CNT),
	   (unsigned int) (X_TMR->ARR), (unsigned int) xTmrReadCCR());
    printf("CCMR %8x CCER %8x DIER %8x\n",
	   (unsigned int) xTmrReadCCMR(), (unsigned int) (X_TMR->CCER),
	   (unsigned int) (X_TMR->DIER));
    flushBuf();
#endif
    zIsr.syncInit <<= ARC_SHIFT;
    printf("zIsr.syncInit %3x\n", zIsr.syncInit);
    zIsr.active = zIsr.syncInit; /* make active */
    zIsr.syncInit = 0;		/* clear init flag */
    xIsr.steps = 0;
    zIsr.steps = 0;
    xMoveCtl.expLoc = rVar.arcXEnd + rVar.xHomeOffset;
    zMoveCtl.expLoc = rVar.arcZEnd + rVar.zHomeOffset;
    mv->state = M_WAIT_ARC;
    break;

   case OP_DONE:
    dbgmsg(D_DONE, cmd->iVal);
    if (cmd->iVal == PARM_START)
    {
     mv->start = uwTick;
     rVar.mvStatus &= ~MV_DONE;
     rVar.mvStatus |= MV_ACTIVE;
     jogPause = DISABLE_JOG;
    }
    else if (cmd->iVal == PARM_DONE)
    {
     mv->start = 0;
     rVar.mvStatus &= ~MV_ACTIVE;
     rVar.mvStatus |= MV_DONE;
     jogPause = 0;
     if (rVar.capTmrEnable || syn.encoderDirect)
     {
      syncStop();		/* stop x encoder */
      encoderSWIEnable(0);	/* disable software interrupt for encoder */
     }
    }
    break;
   }

   if (done)
    break;
  }
 }
 break;

 case M_WAIT_Z:
  if (zMoveCtl.state == AXIS_IDLE) /* if operation complete */
  {
   if (runout.xFlag)		/* if runout */
   {
    if (xIsr.active == 0)	/* if x isr no longer active active */
    {
     runout.xFlag = 0;		/* clear runout flag */
     mv->state = M_IDLE;	/* return to idle state */
    }
   }
   else				/* if no runout */
    mv->state = M_IDLE;		/* return to idle state */
  }
  break;

 case M_WAIT_X:
  if (xMoveCtl.state == AXIS_IDLE) /* if operation complete */
   mv->state = M_IDLE;
  break;

 case M_WAIT_SYNC_PARMS:
#if defined(SYNC_SPI)
  if (syncLoadDone)
   mv->state = M_IDLE;
#endif  /* SYNC_SPI */
  break;

 case M_WAIT_SYNC_CMD:
#if defined(SYNC_SPI)
  if (syncCmdDone)
   mv->state = M_IDLE;
#endif  /* SYNC_SPI */
  break;   

 case M_WAIT_SPINDLE:
  if (rVar.cfgFpga == 0)	/* processor control version */
  {
   if (rVar.stepperDrive)	/* if stepper drive */
   {
    if ((sp.accel == 0)		/* if done accelerating */
    &&  (sp.decel == 0))	/* and done decelerating */
    {
     if (DBG_QUE)
      printf("spindle done mvStatus x%02x\n", (unsigned int) rVar.mvStatus);

     if ((rVar.mvStatus & (MV_PAUSE | MV_MEASURE)) ==
	 (MV_PAUSE | MV_MEASURE)) /* if paused for measuring */
      mv->state = M_WAIT_MEASURE; /* wait for measurement to complete */
     else			/* if not stopping for measuring */
      mv->state = M_IDLE;	/* go to idle state */
    }
   }
   else				/* if not stepper drive */
   {
    if (lastRevCount != rVar.revCounter)
    {
     lastRevCount = rVar.revCounter;
     if ((rVar.indexPeriod != 0)
     &&  (rVar.lastIndexPeriod != 0))
     {
      int delta = (int) (rVar.indexPeriod - rVar.lastIndexPeriod);
      if (delta < 0)
       delta = -delta;
      float percent = ((float) delta * 100.0f) / (float) rVar.indexPeriod;
      float rpm = ((float) rVar.cfgFcy / (float) rVar.indexPeriod) * 60.0f;

      if (DBG_QUE)
      {
       printf("rpm %3.0f rev %2d indexPeriod %8d delta %10d %6.1f%%\n",
	      rpm, rVar.revCounter, rVar.indexPeriod, delta, percent);
       flushBuf();
      }

      if (percent < 1.0)
      {
       if (DBG_QUE)
       {
	printf("spindleSync %d spindleSyncBoard %d useEncoder %d\n",
	       syn.spindle, rVar.spindleSyncBoard, syn.useEncoder);
	printf("synExtActive %d synIntActive %d, encActive %d\n",
	       syn.extActive, syn.intActive, syn.encActive);
       }

       if (mv->spindleCmd == STOP_SPINDLE) /* if stopping spindle */
       {
	mv->state = M_IDLE;	/* return to idle state */
       }
       else			/* if not stopping spindle */
       {
	if (syn.extActive)	/* if using external sync board */
	{
	 printf("Start ZFlag %d\n",
		((ZFlag_Pin & ZFlag_GPIO_Port->ODR) != 0));
	 printf("Start clr\n");
	 startClr();		/* set sync start flag */
	 printf("Start ZFlag %d\n",
		((ZFlag_Pin & ZFlag_GPIO_Port->ODR) != 0));
	 mv->state = M_WAIT_SYNC_READY; /* wait for encoder */
	}
	else if (syn.intActive)	/* if using internal sync */
	{
	 syncSetup();		/* set up x encoder variables */
	 syncMeasure();		/* measure for encoder */
	 mv->state = M_WAIT_MEASURE_DONE; /* wait for measurement done */
	}
	else if (syn.encActive)	/* if using encoder directly */
	{
	 encoderStart();	/* start encoder to use interrupt */
	 mv->state = M_IDLE;	/* return to idle state */
	}
	else			/* if not threading */
	{
	 encoderStart();	/* enable interrupt for encoder */
	 mv->state = M_IDLE;	/* return to idle state */
	}
       }	/* if not stopping spindle */
      }		/* if speed stable */
     }		/* if valid index period */
     else if (mv->spindleCmd == STOP_SPINDLE) /* if stopping spindle */
     {
      mv->state = M_IDLE;	/* return to idle state */
     }
     rVar.lastIndexPeriod = rVar.indexPeriod; /* set new last period */
    }
   }
  }
  else				/* xilinx configuration */
  {
  }
  break;

 case M_WAIT_SYNC_READY:
  if (readyIsClr())		/* if sync ready */
  {
   startSet();			/* clear start flag */
   mv->state = M_WAIT_SYNC_DONE;
  }
  break;

 case M_WAIT_SYNC_DONE:
  if (readyIsSet())		/* if ready cleared */
  {
   if (syn.intActive)		/* if using internal sync */
   {
    syncSetup();		/* set up x encoder variables */
    syncMeasure();		/* measure for x encoder */
    mv->state = M_WAIT_MEASURE_DONE; /* wait for measurement done */
   }
   else	if (syn.encActive)		/* if using encoder */
   {
    encoderStart();		/* start encoder to use interrupt */
    mv->state = M_IDLE;		/* return to idle state */
   }
   else				/* if not using anything else */
   {
    mv->state = M_IDLE;		/* return to idle state */
   }
  }
  break;

 case M_WAIT_MEASURE_DONE:
  if (cmpTmr.measure == 0)	/* if measurement complete */
  {
   syncCalculate();		/* calculate encoder pre scaler */
   mv->state = M_START_SYNC;	/* start sync */
  }
  break;

 case M_START_SYNC:
  syncStart();			/* start sync */
  mv->state = M_IDLE;		/* return to idle state */
  break;

 case M_WAIT_PROBE:
  if (mv->probeCmd == PROBE_Z)
  {
   if (zMoveCtl.state == AXIS_IDLE) /* if opearation complete */
   {
    mv->state = M_IDLE;
    rVar.zHomeStatus = zIsr.doneHome ? PROBE_SUCCESS : PROBE_FAIL;

    if (DBG_QUE)
     printf("z probe done %d\n", zIsr.doneHome);
   }
  }
  else if (mv->probeCmd == PROBE_X)
  {
   if (xMoveCtl.state == AXIS_IDLE) /* if opearation complete */
   {
    mv->state = M_IDLE;
    rVar.xHomeStatus = xIsr.doneHome ? PROBE_SUCCESS : PROBE_FAIL;

    if (DBG_QUE)
     printf("x probe done %d\n", xIsr.doneHome);
   }
  }
  break;

 case M_WAIT_MEASURE:
  if ((rVar.mvStatus & MV_MEASURE) == 0) /* if measurement complete */
  {
   if (DBG_QUE)
    printf("measure complete\n");

   xMove(mv->safeX, CMD_MAX);
   mv->state = M_WAIT_SAFE_X;
  }
  break;

 case M_WAIT_SAFE_X:
  if (xMoveCtl.state == AXIS_IDLE) /* if operation complete */
  {
   zMove(mv->safeZ, CMD_MAX);
   mv->state = M_WAIT_SAFE_Z;
  }
  break;

 case M_WAIT_SAFE_Z:
  if (zMoveCtl.state == AXIS_IDLE) /* if operation complete */
  {
   if (rVar.cfgFpga == 0)
   {
    if (rVar.stepperDrive)
    {
     spindleInit(&spA, 0, SP_FWD);
     spindleStart();
    }
   }
   else
    spindleStartX();
   mv->state = M_WAIT_SPINDLE;
  }
  break;

  case M_WAIT_ARC:
   if (!arcData.done)
   {
    arcUpdate(false);
   }
   else
    if (arcData.active == false)
    {
     xMoveCtl.loc = rVar.zLoc;
     zMoveCtl.loc = rVar.xLoc;
     if (xMoveCtl.loc != xMoveCtl.expLoc)
     {
      printf("x move arc error actual %5d expected %5d\n",
	     xMoveCtl.loc, xMoveCtl.expLoc);
      dbgmsg(D_XEXP, xMoveCtl.expLoc);
     }
     if (zMoveCtl.loc != zMoveCtl.expLoc)
     {
      printf("z move arc error actual %5d expected %5d\n",
	     zMoveCtl.loc, zMoveCtl.expLoc);
      dbgmsg(D_ZEXP, zMoveCtl.expLoc);
     }
     dbgmsg(D_XSTP, (int) xIsr.steps);
     dbgmsg(D_ZSTP, (int) zIsr.steps);
     mv->state = M_IDLE;
    }
   break;
  }

 if (DBG_QUE)
 {
  if (mv->state != mv->lastState)
  {
   dbgmsg(D_MSTA, mv->state);
   mv->lastState = mv->state;
   printf("mvState %d %s\n", mv->state, mStatesList[(int) mv->state]);
  }
 }
 dbgProcMoveClr();
}

void moveZX(int zDest, int xDest)
{
 if (DBG_MOVOP)
  printf("moveZX %7.4f %7.4f\n", (float) zDest / (float) zAxis.stepsInch,
	 (float) xDest / (float) xAxis.stepsInch);
}

void moveXZ(int zDest, int xDest)
{
 if (DBG_MOVOP)
  printf("moveZX %7.4f %7.4f\n", (float) zDest / (float) zAxis.stepsInch,
	 (float) xDest / (float) xAxis.stepsInch);

#if 0
 int deltaZ = zDest - zDest;
 int deltaX = xDest - xDest;
#endif
}

void turnPitch(P_ACCEL ac, float pitch)
{
 if (DBG_P)
  printf("\nturnPitch %s\n", ac->label);

 ac->pitch = pitch;
 if (rVar.spindleEncoder == 0)	/* *ok* if no spindle encoder */
 {
  int revCycle = lrintf(1.0f / pitch);
  if (revCycle > 20)
   revCycle = 20;
  float cycleDist = (float) revCycle * pitch;

  if (DBG_P)
   printf("pitch %5.3f revCycle %d cycleDist %5.3f\n",
	  pitch, revCycle, cycleDist);

  spA.clocksCycle = ((int64_t) spA.clocksRev) * revCycle;
  spA.stepsCycle = spA.stepsRev * revCycle;
  ac->stepsCycle = lrintf((float) ac->stepsInch * cycleDist);
  float cycleTime = ((float) spA.clocksCycle) / (float) rVar.cfgFcy;

  if (DBG_P)
   printf("clocksCycle %lld cycleTime %6.3f stepsCycle %d z stepsCycle %d\n",
	  spA.clocksCycle, cycleTime, spA.stepsCycle, ac->stepsCycle);
 }
 else				/* *chk* if using spindle encoder */
 {
  if (ac->label[0] == 'z')	/* if z axis */
  {
   syn.encoderDirect |= Z_ENCODER_DIRECT; /* use encoder directly for z */
   zIsr.encoderDirect = 1;	/* use encoder directly for z isr */
  }
  else				/* if x axis */
  {
   syn.encoderDirect |= X_ENCODER_DIRECT; /* use encoder directly for x */
   xIsr.encoderDirect = 1;	/* use encoder directly for x isr */
  }
 }
}

void threadTPI(P_ACCEL ac, float tpi)
{
 if (DBG_P)
  printf("\nthreadTPI %s\n", ac->label);

 ac->pitch = 1.0f / (float) tpi;
 if (rVar.spindleEncoder == 0)	/* *ok* if no spindle encoder */
 {
  spA.clocksCycle = (spA.clocksRev * (int64_t) (tpi * 100)) / 100;
  spA.stepsCycle = (unsigned int) ((float) spA.stepsRev * tpi);
  ac->stepsCycle = ac->stepsInch;
  float cycleTime = ((float) spA.clocksCycle) / (float) rVar.cfgFcy;

  if (DBG_P)
  {
   printf("clocksCycle %lld cycleTime %6.3f stepsCycle %d z stepsCycle %d\n",
	  spA.clocksCycle, cycleTime, spA.stepsCycle, ac->stepsCycle);
   printf("tpi %2.0f pitch %5.3f\n", tpi, ac->pitch);
  }
 }
 else				/* *chk* if using encoder */
 {
 }
}

void threadMetric(P_ACCEL ac, float pitch)
{
 if (DBG_P)
  printf("\nthreadMetric %s\n", ac->label);

 ac->pitch = pitch / 25.4f;
 if (rVar.spindleEncoder == 0)	/* *ok* if no spindle encoder */
 {
  int revolutions = 127;
  float inches = (pitch * (float) revolutions) / 25.4f;

  spA.clocksCycle = ((int64_t) spA.clocksRev) * revolutions;
  spA.stepsCycle = spA.stepsRev * revolutions;
  ac->stepsCycle = lrintf((float) ac->stepsInch * inches);
  float cycleTime = ((float) spA.clocksCycle) / (float) rVar.cfgFcy;

  if (DBG_P)
  {
   printf("pitch %3.1f mm pitch %5.3f in inches %5.3f\n",
	  pitch, ac->pitch, inches);
   printf("clocksCycle %lld cycleTime %6.3f stepsCycle %d zStepsCycle %d\n",
	  spA.clocksCycle, cycleTime, spA.stepsCycle, ac->stepsCycle);
  }
 }
 else				/* *chk* if using encoder */
 {
 }
}

/* common routine for turning */

void turnCalc(P_ACCEL ac)
{
 if (DBG_P)
  printf("\nturnCalc %s\n", ac->label);

 ac->clocksStep = (int) (spA.clocksCycle / ac->stepsCycle);
 ac->remainder = (int) (spA.clocksCycle -
			((int64_t) ac->clocksStep) * ac->stepsCycle);
 int dx = ac->stepsCycle;
 int dy = ac->remainder;
 if (dy != 0)
 {
  ac->incr1 = 2 * dy;
  ac->incr2 = ac->incr1 - 2 * dx;
  ac->d = ac->incr1 - dx;
 }
 else
 {
  ac->incr1 = 0;
  ac->incr2 = 0;
  ac->d = 0;
 }

 if (DBG_P)
 {
  printf("clocksStep %d remainder %d\n",
	 ac->clocksStep, ac->remainder);
  printf("stepsCycle dx %d remainder dy %d incr1 %d incr2 %d d %d\n",
	 ac->stepsCycle, ac->remainder, ac->incr1, ac->incr2, ac->d);
 }
}

void encTurnCalc(P_ACCEL ac)
{
 if (DBG_P)
  printf("\nencTurnCalc %s\n", ac->label);

 int encPerInch = lrintf((float) rVar.encPerRev / ac->pitch);
 int dx = encPerInch;
 int dy = ac->stepsInch;
 ac->incr1 = 2 * dy;
 ac->incr2 = ac->incr1 - 2 * dx;
 ac->d = ac->incr1 - dx;

 if (DBG_P)
  printf("encPerInch dx %d stepsInch dy %d incr1 %d incr2 %d d %d\n",
	 dx, dy, ac->incr1, ac->incr2, ac->d);
}

#if 0
/* update clocks per step based on motor speed */

void motorUpdate(P_ZXISR isr, P_ACCEL ac);

void motorUpdate(P_ZXISR isr, P_ACCEL ac)
{
 if ((isr->accel == 0)		/* if not accel */
 &&  (isr->decel == 0)		/* and not decel */
 &&  (isr->taper == 0))		/* and not tapering */
 {
  ac->clocksStep = rVar.indexPeriod / ac->stepsCycle;
  isr->clocksStep = ac->clocksStep;
 }
}
#endif

/* calculation for use with external motor */

void motorSetup(P_ACCEL ac, float accel, float feed)
{
 if (DBG_P)
  printf("\nmotorSetup %s accel %0.0f feed %0.3f\n", ac->label, accel, feed);

 ac->pitch = feed;		/* save feed */
 ac->stepsCycle = (int) (feed * (float) ac->stepsInch); /* one spindle rev */
 ac->clocksStep = rVar.indexPeriod / ac->stepsCycle;
 float rpm = ((float) rVar.cfgFcy / (float) rVar.indexPeriod) * 60;

 if (DBG_P)
  printf("stepsCycle %d indexPeriod %d clocksStep %d rpm %5.1f\n",
	 ac->stepsCycle, rVar.indexPeriod, ac->clocksStep, rpm);

 turnAccel(ac, accel, T_DBG_PRINT, rpm);
}

/* calculate acceleration for turn */

void turnAccel(P_ACCEL ac, float accel, int flag, float rpm)
{
 char dbg = flag & T_DBG_PRINT;
 if (dbg)
  printf("\nturnAccel %s\n", ac->label);

 ac->accel = accel;
 if (flag & T_STEP_SPINDLE)
  rpm = spA.maxRPM;
 float speedIPM = ac->pitch * rpm;
 ac->stepsSec = lrintf(speedIPM * (float) ac->stepsInch / 60.0f);

 if (dbg)
  printf("RPM %0.0f speedIPM %4.1f in/min StepsSec %d steps/sec\n",
	 rpm, speedIPM, ac->stepsSec);

 if (ACCEL_TIME)
 {
 }
 else
 {
  ac->stepsSec2 = (ac->accel / 60.0f) * (float) ac->stepsInch;
  ac->time = (speedIPM / 60.0f) / ac->accel;
 }

 if (dbg)
  printf("accel %5.3f in/sec^2 stepsSec2 %5.3f time %0.3f\n",
	 ac->accel, ac->stepsSec2, ac->time);

 ac->steps = (int) ((ac->time * (float) ac->stepsSec) / 2.0f);
 if (ac->steps == 0)
 {
  if (dbg)
   printf("ac->steps 0\n");

  ac->cFactor = 0.0;
  ac->clocks = 0;
  ac->dist = 0.0;
  ac->accelSpSteps = 0;
  ac->accelSpRem = 0;
  ac->initialStep = 0;
  ac->finalStep = 0;
 }
 else
 {
  ac->initialStep = 0;
  ac->finalStep = ac->steps;

  float cFactor0 = ((float) rVar.cfgFcy * sqrtf(2.0f)) / sqrtf(ac->stepsSec2);
  float cFactor1 = ((float) ac->clocksStep /
                    (sqrtf((float) ac->finalStep) -
                     sqrtf((float) (ac->finalStep - 1))));
  ac->cFactor = cFactor1;

  ac->clocks = (int) (ac->cFactor * sqrtf((float) ac->finalStep));
  ac->time = ((float) ac->clocks) / (float) rVar.cfgFcy;
  ac->dist = ((float) ac->steps) / (float) ac->stepsInch;

  ac->finalCount = (int) (ac->cFactor * sqrtf((float) ac->finalStep));
  ac->initialCount = (int) (ac->cFactor * sqrtf((float) (ac->initialStep + 1)));
  ac->initialCount -= (int) (ac->cFactor * sqrtf((float) ac->initialStep));
  ac->totAccelClocks = ac->finalCount - ac->initialCount;
  ac->finalCount -= (int) (ac->cFactor * sqrtf((float) (ac->finalStep - 1)));

  if (dbg)
  {
   printf( "cFactor0 %0.2f cFactor1 %0.2f\n", cFactor0, cFactor1);
   printf("time %8.6f steps %d clocks %d dist %5.3f\n",
	  ac->time, ac->steps, ac->clocks, ac->dist);
   printf("initialCount %d finalCount %d totAccelClocks %d\n",
	  ac->initialCount, ac->finalCount, ac->totAccelClocks);
   printf("initalTime %8.6f isrTime %8.6f\n",
	  ((float) ac->initialCount) / (float) rVar.cfgFcy,
	  ((float) ac->totAccelClocks) / (float) rVar.cfgFcy);
  }

  if (flag & T_STEP_SPINDLE)
  {
   ac->accelSpSteps = ac->totAccelClocks / spA.clocksStep;
   ac->accelSpRem = ac->totAccelClocks - ac->accelSpSteps * spA.clocksStep;

   if (dbg)
    printf("accelSpSteps %d accelSpRem %d\n",
	   ac->accelSpSteps, ac->accelSpRem);
  }
 }
}

void speedCalc(P_ACCEL accel, P_ZXISR isr, float finalSpeed)
{
 if (DBG_P)
  printf("\nspeedCalc %s\n", accel->label);

 accel->maxSpeed = finalSpeed;
 int stepsSec = (int) ((finalSpeed * (float) accel->stepsInch) / 60.0f);
 accel->stepsSec = stepsSec;
 int clocksStep = (int) (rVar.cfgFcy / stepsSec);

 float finalStepsSec = (finalSpeed * (float) accel->stepsInch) / 60.0f;
 float finalTime = finalStepsSec / accel->stepsSec2;
 auto finalStep = (unsigned int) ((finalStepsSec * finalTime) / 2.0f);

 if (DBG_P)
 {
  printf("finalSpeed %0.2f stepsSec %d clocksStep %d\n",
	 finalSpeed, stepsSec, clocksStep);
  printf("finalStepsSec %ld finalTime %5.3f finalStep %d accelStep %d\n",
         lrintf(finalStepsSec), finalTime, finalStep, isr->accelStep);
 }

 int aClocksStep;
 if (finalStep > 0)
 {
  if (isr->accelStep > finalStep)
  {
   aClocksStep = lrintf(accel->cFactor * (sqrtf((float) finalStep) -
           sqrtf((float) (finalStep - 1))));
  }
  else
  {
   aClocksStep = lrintf(accel->cFactor * (sqrtf((float) (finalStep + 1) )-
				   sqrtf((float) finalStep)));
  }
  clocksStep = aClocksStep;

  if (DBG_P)
   printf("cFactor %0.2f aClocksStep %d finalStepsSec %ld\n",
	  accel->cFactor, aClocksStep, lrintf(finalStepsSec));
 }
 else
  finalStep = 1;

 __disable_irq();		/* disable interrupt */
 if (isr->dist != 0)
 {
  unsigned int isrStep = isr->accelStep;
  isr->lastCount = (int) (isr->cFactor * sqrtf((float) isrStep));
  if (isrStep < finalStep)
  {
   putBufStrX("A\n");
   isr->decel = 0;
   isr->accel = 1;
   isr->finalStep = finalStep;
  }
  else
  {
   putBufStrX("D\n");
   isr->accel = 0;
   isr->decel = -1;
   isr->initialStep = finalStep;
  }
  isr->clocksStep = clocksStep;
 }
 __enable_irq();		/* enable interrupts */

 if (DBG_P)
  printf("initialStep %d accelStep %d finalStep %d\n",
	 isr->initialStep, isr->accelStep, isr->finalStep);
}

/* calculate acceleration for move */

void accelCalc(P_ACCEL accel)
{
 if (DBG_P)
 {
  printf("\naccelCalc %s\n", accel->label);
  printf("minSpeed %1.0f maxSpeed %1.0f accel %4.2f\n",
	 accel->minSpeed, accel->maxSpeed, accel->accel);
 }

 accel->stepsSec = (int) ((accel->maxSpeed * (float) accel->stepsInch) / 60.0f);
 accel->clocksStep = (int) (rVar.cfgFcy / accel->stepsSec);

 if (DBG_P)
  printf("stepsSec %d clocksStep %d\n",
	 accel->stepsSec, accel->clocksStep);

 float minStepsSec = ((float) accel->stepsInch * accel->minSpeed) / 60.0f;
 float maxStepsSec = ((float) accel->stepsInch * accel->maxSpeed) / 60.0f;
 if (DBG_P)
  printf("minStepsSec %4.0f maxStepsSec %4.0f\n",
	 minStepsSec, maxStepsSec);

 float deltaV = maxStepsSec - minStepsSec;
 if (ACCEL_TIME)
 {
  accel->stepsSec2 = accel->aTime * (float) accel->stepsInch;

  if (DBG_P)
   printf("deltaV %2.0f stepsSec2 %6.3f\n",
	  deltaV, accel->stepsSec2);
 }
 else
 {
  accel->stepsSec2 = (accel->accel / 60.0f) * (float) accel->stepsInch;
  accel->aTime = deltaV / accel->stepsSec2;

  if (DBG_P)
   printf("aTime %0.6f deltaV %2.0f stepsSec2 %6.3f\n",
	  accel->aTime, deltaV, accel->stepsSec2);
 }

 if (deltaV != 0)
 {
  float minTime = minStepsSec / accel->stepsSec2;
  float maxTime = maxStepsSec / accel->stepsSec2;

  if (DBG_P)
   printf("minTime %5.3f maxTime %5.3f\n",
	  minTime, maxTime);

  accel->initialStep = (int) ((minStepsSec * minTime) / 2.0);
  accel->finalStep = (int) ((maxStepsSec * maxTime) / 2.0);

  if (DBG_P)
   printf("initalStep %d finalStep %d\n",
	  accel->initialStep, accel->finalStep);

  float cFactor0 = (((float) rVar.cfgFcy * sqrtf(2.0f)) /
		    sqrtf(accel->stepsSec2));
  if (accel->finalStep > 0)
  {
   float cFactor1 = ((float) accel->clocksStep /
		     (sqrtf((float) accel->finalStep) -
		      sqrtf((float) (accel->finalStep - 1))));
   if (DBG_P)
    printf( "cFactor0 %0.2f cFactor1 %0.2f\n", cFactor0, cFactor1);

   accel->cFactor = cFactor1;
  }
  else
  {
   if (DBG_P)
    printf( "cFactor0 %0.2f\n", cFactor0);

   accel->cFactor = cFactor0;
  }

  accel->steps = accel->finalStep - accel->initialStep;
  int finalCount = (int) (accel->cFactor * sqrtf((float) accel->finalStep));
  accel->clocks = finalCount;
  accel->clocks -= (int) (accel->cFactor * sqrtf((float) accel->initialStep));
  accel->time = ((float) accel->clocks) / (float) rVar.cfgFcy;
  accel->dist = (float) accel->steps / (float) accel->stepsInch;
  finalCount -= (int) (accel->cFactor * sqrtf((float) (accel->finalStep - 1)));

  if (DBG_P)
  {
   printf("time %8.6f steps %d clocks %d dist %5.3f\n",
	  accel->time, accel->steps, accel->clocks, accel->dist);
   printf("finalCount %d clocksStep %d\n", finalCount, accel->clocksStep);
  }
 }
}

void taperCalc(P_ACCEL a0, P_ACCEL a1, float taper)
{
 if (DBG_P)
  printf("\ntaperCalc a0 %s a1 %s taper %0.6f\n",
	 a0->label, a1->label, taper);

 a1->taper = 1;
 a1->taperInch = taper;

 float a0CycleDist = rVar.taperCycleDist;
 float a1CycleDist = taper * a0CycleDist;

 if (DBG_P)
  printf("a0CycleDist %6.4f a1CycleDist %6.4f\n",
	 a0CycleDist, a1CycleDist);

 if (rVar.spindleEncoder == 0)	/* *ok* if no spindle encoder */
 {
  a1->accelSpSteps = 0;
  a1->accelSpRem = 0;

  int d0Steps = lrintf(a0CycleDist * (float) a0->stepsInch);
  int d1Steps = lrintf(a1CycleDist * (float) a1->stepsInch);
  int64_t d0Clocks = d0Steps * (int64_t) a0->clocksStep;

  if (DBG_P)
   printf("d0Steps %d d1Steps %d d0Clocks %lld\n",
	  d0Steps, d1Steps, d0Clocks);

  a1->clocksStep = (int) (d0Clocks / d1Steps);
  a1->remainder = (int) (d0Clocks - d1Steps * a1->clocksStep);
  a1->stepsCycle = d1Steps;

  int dx = d1Steps;
  int dy = a1->remainder;
  if (dy != 0)
  {
   a1->incr1 = 2 * dy;
   a1->incr2 = a1->incr1 - 2 * dx;
   a1->d = a1->incr1 - dx;
  }
  else
  {
   a1->incr1 = 0;
   a1->incr2 = 0;
   a1->d = 0;
  }

  if (DBG_P)
  {
   printf("clocksStep %d remainder %d\n",
	  a1->clocksStep, a1->remainder);
   printf("stepsCycle dx %d remainder dy %d incr1 %d incr2 %d d %d\n",
	  dx, dy, a1->incr1, a1->incr2, a1->d);
  }
 }
 else				/* *chk* if using encoder */
 {
  if (syn.encActive)		/* if using encoder */
  {
   int dx = lrintf(((float) rVar.encPerRev * a0CycleDist) /
		   a0->pitch); /* encPercycle */
   int dy = lrintf(a1CycleDist * (float) a1->stepsInch); /* stepsCycle */
   a1->incr1 = 2 * dy;
   a1->incr2 = a1->incr1 - 2 * dx;
   a1->d = a1->incr1 - dx;

   if (DBG_P)
    printf("encPerCycle dx %d stepsCycle dy %d incr1 %d incr2 %d d %d\n",
	   dx, dy, a1->incr1, a1->incr2, a1->d);
  }
  if (syn.intActive		/* if using sync */
  ||  syn.extActive)
  {
   int dx = lrintf(a0CycleDist * (float) a0->stepsInch);
   int dy = lrintf(a1CycleDist * (float) a1->stepsInch);
   a1->incr1 = 2 * dy;
   a1->incr2 = a1->incr1 - 2 * dx;
   a1->d = a1->incr1 - dx;

   if (DBG_P)
    printf("synPerCycle dx %d stepsCycle dy %d incr1 %d incr2 %d d %d\n",
	   dx, dy, a1->incr1, a1->incr2, a1->d);
  }
 }
}

void runoutCalc(P_ACCEL a0, P_ACCEL a1, float dist, float runoutDepth)
{
 printf("\nrunoutCalc a0 %s a1 %s runout %7.4f runoutDepth %7.4f\n",
	a0->label, a1->label, dist, runoutDepth);

 int d0Clocks = (int) (dist * (float) spA.clocksRev);
 int d1Steps = runout.xSteps;

 a1->clocksStep = (int) (d0Clocks / d1Steps);
 a1->remainder = (int) (d0Clocks - d1Steps * a1->clocksStep);
 a1->stepsCycle = d1Steps;
 a1->accelSpSteps = 0;
 a1->accelSpRem = 0;

 int dx = d1Steps;
 int dy = a1->remainder;
 if (dy != 0)
 {
  a1->incr1 = 2 * dy;
  a1->incr2 = a1->incr1 - 2 * dx;
  a1->d = a1->incr1 - dx;
 }
 else
 {
  a1->incr1 = 0;
  a1->incr2 = 0;
  a1->d = 0;
 }

 if (DBG_P)
 {
  printf("d0Clocks %d d1Steps %d clocksStep %d remainder %d\n",
	 d0Clocks, d1Steps, a1->clocksStep, a1->remainder);
  printf("d1Steps dx %d remainder dy %d incr1 %d incr2 %d d %d\n",
	 dx, dy, a1->incr1, a1->incr2, a1->d);
 }
}

void encRunoutCalc(P_ACCEL a0, P_ACCEL a1, float dist, float runoutDepth)
{
 printf("\nencRunoutCalc a0 %s a1 %s runout %7.4f runoutDepth %7.4f\n",
	a0->label, a1->label, dist, runoutDepth);

 int dx = lrintf(dist * (float) rVar.encPerRev);
 int dy = runout.xSteps;

 a1->incr1 = 2 * dy;
 a1->incr2 = a1->incr1 - 2 * dx;
 a1->d = a1->incr1 - dx;

 if (DBG_P)
 {
  printf("encClocks dx %d xRunoutSteps dy %d incr1 %d incr2 %d d %d\n",
	 dx, dy, a1->incr1, a1->incr2, a1->d);
 }
}

#if defined(MEGAPORT)

void megaRsp()
{
 putBufStrIsr("mr");
 int parm;
 gethexMega(&parm);
 int val;
 switch (parm)
 {
 case MEGA_SET_RPM:
  break;

 case MEGA_GET_RPM:
  break;

 case MEGA_POLL:
  gethexMega(&val);
  break;

 default:
  gethexMega(&val);
  break;
 }

 while (true)
 {
  int ch = getMega();
  if (ch == '*')
   break;
  if (ch < 0)
   break;
 }

 if (megaCtl.txWait)
 {
  putBufStrIsr("wc");
  dbgMegaWaitClr();
  megaCtl.txWait = false;
  megaTxIntEna();
 }
 else
 {
  putBufStrIsr("tc");
  megaCtl.timer = 0;
 }
}

void megaPoll()
{
 putMega(1);
 char ch = MEGA_POLL;
 sndhexMega((const unsigned char *) &ch, sizeof(ch), '\r');
}

#endif	/* MEGAPORT */

#if defined(SYNC_SPI)

void initSync()
{
 SPI_SEL_GPIO_Port->BSRR = SPI_SEL_Pin;
}

#if 0
#define CHAR_BUF_SIZE 80

typedef struct sBufCtl
{
 int count;
 char buf[CHAR_BUF_SIZE];
} T_BUF_CTL, *P_BUF_CTL;

T_BUF_CTL cBufCtl;
T_BUF_CTL rBufCtl;

void initBuf()
{
 cBufCtl.count = 0;
}

void putBuf(char ch)
{
 if (cBufCtl.count < CHAR_BUF_SIZE)
 {
  cBufCtl.buf[cBufCtl.count] = ch;
  cBufCtl.count += 1;
 }
}
#endif

void sndHexSPI(unsigned char *p, int size)
{
 char tmp;
 char ch;
 int zeros = 0;

 p += size;
 while (size != 0)
 {
  --size;
  p--;
  tmp = *p;
  ch = tmp;
  ch >>= 4;
  ch &= 0xf;
  if ((ch != 0)
  ||  zeros)
  {
   zeros = 1;
   if (ch < 10)
    ch += '0';
   else
    ch += 'a' - 10;
   putSPI(ch);
  }

  tmp &= 0xf;
  if ((tmp != 0)
  ||  zeros)
  {
   zeros = 1;
   if (tmp < 10)
    tmp += '0';
   else
    tmp += 'a' - 10;
   putSPI(tmp);
  }
 }

 if (zeros == 0)
  putSPI('0');
}

int valSPI;

char getHexSPI()
{
 int ch;
 int count;

 valSPI = 0;
 count = 0;
 while (count <= 8)
 {
  ch = getSPI();
  if ((ch >= '0')
  &&  (ch <= '9'))
  {
   ch -= '0';
  }
  else if ((ch >= 'a')
  &&       (ch <= 'f'))
  {
   ch -= 'a' - 10;
  }
  else if ((ch == ' ') || (ch == '*') || (ch < 0))
   break;
  else
   continue;

  count++;
  valSPI <<= 4;
  valSPI += ch;
 }
 return(count != 0);
}

void syncCommand(uint8_t cmd)
{
 syncCmdDone = false;
 putSPI(1);
 sndHexSPI(&cmd, sizeof(cmd));
 putSPI('\r');
 spiMasterStart();
}

extern char remParm[];

void syncSendMulti(P_SYNC_MULTI_PARM p)
{
 syncLoadDone = false;

 P_SYNC_MULTI_PARM p0 = p;
 unsigned char count = 0;
 while (p0->syncParm != SYNC_MAX_PARM)
 {
  count +=1;
  p0 += 1;
 }
 
 putSPI(1);
 unsigned char tmp = SYNC_LOADMULTI;
 sndHexSPI(&tmp, sizeof(tmp));
 putSPI(' ');
 sndHexSPI(&count, sizeof(count));
 while (true)
 {
  if (p->syncParm == SYNC_MAX_PARM)
   break;
  else
  {
   T_DATA_UNION parmVal;
   parmVal.t_int = 0;
   putSPI(' ');
   sndHexSPI((unsigned char *) &p->syncParm, sizeof(p->syncParm));
   putSPI(' ');
   getRemVar(p->remParm, &parmVal);
   int size = remParm[p->remParm];
   printf("r p %2x s %d v %8x\n",
	  (unsigned int) p->syncParm, size, parmVal.t_unsigned_int);
   sndHexSPI((unsigned char *) &parmVal.t_unsigned_int, size);
   p += 1;
  }
 }
 putSPI('\r');
 spiMasterStart();
}

void syncPoll()
{
 syncPollDone = false;
 putSPI(1);
 unsigned char tmp = SYNC_POLL;
 sndHexSPI(&tmp, sizeof(tmp));
 putSPI('\r');
 spiMasterStart();
}

void syncResp()
{
 int parm;

 dbgSyncRespSet();
 parm = getSPI();
 getHexSPI();			/* read parameter */
 parm = valSPI;
 putBufChar(parm + '0');
 switch (parm)
 {
 case SYNC_SETUP:
  //syncCmdDone = true;
  //break;

 case SYNC_START:
  //syncCmdDone = true;
  //break;

 case SYNC_STOP:
  syncCmdDone = true;
  break;
  
 case SYNC_LOADVAL:		/* load a local parameter */
  //syncLoadDone = true;
  //break;

 case SYNC_LOADMULTI:		/* load multiple parameters */
  syncLoadDone = true;
  break;

 case SYNC_READVAL:		/* read a local parameter */
 {
#if 0
  T_DATA_UNION parmVal;
  getHexSPI();			/* save the parameter number */
  parm = valSPI;		/* save it */
  if (parm < SYNC_MAX_PARM)	/* if in range */
  {
   parmVal.t_int = 0;
   setSyncVar(parm, parmVal);
#if DBG_LOAD
   int size = syncParm[parm];
   printf("r p %2x s %d v %8x\n",
	  (unsigned int) parm, size, parmVal.t_unsigned_int);
#endif
  }
#endif
  syncReadDone = true;
 }
  break;

 case SYNC_POLL:
  syncPollDone = true;
  break;

 default:
  break;
 }

 //printf("count %d emp %d fil %d\n",
 //	spiCtl.rxCount, spiCtl.rxEmp, spiCtl.rxFil);
 //flushBuf();

 while (getSPI() >= 0)
 {
 }
 dbgSyncRespClr();
}

#endif	/* SYNC_SPI */

/* TIM3 init function */

//extern TIM_HandleTypeDef htim3;

void TIM3_Init()
{
 printf("TIM3_Init ");
 if (DBG_TMR)
 {
  tmrInfo(TIM3);
  gpioInfo(GPIOC);
 }

 TIM_ClockConfigTypeDef sClockSourceConfig;
 TIM_MasterConfigTypeDef sMasterConfig;
 TIM_OC_InitTypeDef sConfigOC;

 htim3.Instance = TIM3;
 htim3.Init.Prescaler = 0;
 htim3.Init.CounterMode = TIM_COUNTERMODE_DOWN;
 htim3.Init.Period = 10000;
 htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
 if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
 {
  Error_Handler();
 }

 sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
 if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
 {
  Error_Handler();
 }

 if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
 {
  Error_Handler();
 }

 sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
 sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_ENABLE;
 if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
 {
  Error_Handler();
 }

 TIM3->CCR1 = 0;
 TIM3->CCR2 = 0;
 TIM3->CCR3 = 0;
 TIM3->CCR4 = 0;
 TIM3->CCMR1 = 0;
 TIM3->CCMR2 = 0;

 sConfigOC.OCMode = TIM_OCMODE_PWM1;
 sConfigOC.Pulse = 100;
 sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
 sConfigOC.OCFastMode = TIM_OCFAST_ENABLE;

//#ifdef STEP3_PWM1
 if constexpr (((SPINDLE_TIMER == 3) && (SPINDLE_TMR_PWM == 1)) ||
	       ((STEP3_TIMER == 3) && (STEP3_TMR_PWM == 1)) ||
	       ((STEP4_TIMER == 3) && (STEP4_TMR_PWM == 1)))
 {
  printf("pwm 1 ");
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
   Error_Handler();
  }
 }
//#endif
//#ifdef STEP3_PWM2
//#if (STEP3_TIMER == 3) && (STEP3_TMR_PWM == 2)
 if constexpr (((SPINDLE_TIMER == 3) && (SPINDLE_TMR_PWM == 2)) ||
	       ((STEP3_TIMER == 3) && (STEP3_TMR_PWM == 2)) ||
	       ((STEP4_TIMER == 3) && (STEP4_TMR_PWM == 2)))
 {
  printf("pwm 2 ");
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
   Error_Handler();
  }
 }
//#endif
//#ifdef STEP3_PWM3
//#if (STEP3_TIMER == 3) && (STEP3_TMR_PWM == 3)
 if constexpr (((SPINDLE_TIMER == 3) && (SPINDLE_TMR_PWM == 3)) ||
	       ((STEP3_TIMER == 3) && (STEP3_TMR_PWM == 3)) ||
	       ((STEP4_TIMER == 3) && (STEP4_TMR_PWM == 3)))
 {
  printf("pwm 3 ");
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
   Error_Handler();
  }
 }
//#endif
//#ifdef STEP3_PWM4
//#if (STEP3_TIMER == 3) && (STEP3_TMR_PWM == 4)
 if constexpr (((SPINDLE_TIMER == 3) && (SPINDLE_TMR_PWM == 4)) ||
	       ((STEP3_TIMER == 3) && (STEP3_TMR_PWM == 4)) ||
	       ((STEP4_TIMER == 3) && (STEP4_TMR_PWM == 4)))
 {
  printf("pwm 4 ");
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
   Error_Handler();
  }
 }
//#endif

 char buf[8];
 pinName(buf, Step3_GPIO_Port, Step3_Pin);
 printf("Step3_Pin %s ", buf);

 GPIO_InitTypeDef GPIO_InitStruct;
 GPIO_InitStruct.Pin = Step3_Pin;
 GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
 GPIO_InitStruct.Pull = GPIO_NOPULL;
 GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
 GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
 HAL_GPIO_Init(Step3_GPIO_Port, &GPIO_InitStruct);

 if (DBG_TMR)
 {
  tmrInfo(TIM3);
  gpioInfo(Step3_GPIO_Port);
 }
}

#ifdef TIM8

/* TIM8 init function */

//extern TIM_HandleTypeDef htim8;

void TIM8_Init()
{
 printf("TIM8_Init ");
 TIM_ClockConfigTypeDef sClockSourceConfig;
 TIM_MasterConfigTypeDef sMasterConfig;
 TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig;
 TIM_OC_InitTypeDef sConfigOC;

 if (DBG_TMR)
  tmrInfo(TIM8);

 htim8.Instance = TIM8;
 htim8.Init.Prescaler = 0;
 htim8.Init.CounterMode = TIM_COUNTERMODE_DOWN;
 htim8.Init.Period = 1000;
 htim8.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
 htim8.Init.RepetitionCounter = 0;
 if (HAL_TIM_Base_Init(&htim8) != HAL_OK)
 {
  Error_Handler();
 }

 sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
 if (HAL_TIM_ConfigClockSource(&htim8, &sClockSourceConfig) != HAL_OK)
 {
  Error_Handler();
 }

 if (HAL_TIM_PWM_Init(&htim8) != HAL_OK)
 {
  Error_Handler();
 }

 sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
 sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_ENABLE;
 if (HAL_TIMEx_MasterConfigSynchronization(&htim8, &sMasterConfig) != HAL_OK)
 {
  Error_Handler();
 }

 sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
 sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
 sBreakDeadTimeConfig.DeadTime = 0;
 sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
 sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
 sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
 if (HAL_TIMEx_ConfigBreakDeadTime(&htim8, &sBreakDeadTimeConfig) != HAL_OK)
 {
  Error_Handler();
 }

 TIM8->CCR1 = 0;
 TIM8->CCR2 = 0;
 TIM8->CCR3 = 0;
 TIM8->CCR4 = 0;
 TIM8->CCMR1 = 0;
 TIM8->CCMR2 = 0;

 sConfigOC.OCMode = TIM_OCMODE_PWM1;
 sConfigOC.Pulse = 100;
 sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
 sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
 sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
 sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;

//#ifdef STEP5_PWM1
 if constexpr ((SPINDLE_TIMER == 8) && (SPINDLE_TMR_PWM == 1))
 {
  printf("pwm 1 ");
  if (HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
   Error_Handler();
  }
 }
//#endif
//#ifdef STEP5_PWM2
 if constexpr ((SPINDLE_TIMER == 8) && (SPINDLE_TMR_PWM == 2))
 {
  printf("pwm 2 ");
  if (HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
   Error_Handler();
  }
 }
//#endif
//#ifdef STEP5_PWM3
 if constexpr ((SPINDLE_TIMER == 8) && (SPINDLE_TMR_PWM == 3))
 {
  printf("pwm 3 ");
  if (HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
   Error_Handler();
  }
 }
//#endif
//#ifdef STEP5_PWM4
 if constexpr ((SPINDLE_TIMER == 8) && (SPINDLE_TMR_PWM == 4))
 {
  printf("pwm 4 ");
  if (HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
   Error_Handler();
  }
 }
//#endif

 char buf[8];
 pinName(buf, Step5_GPIO_Port, Step5_Pin);
 printf("Step5_Pin %s ", buf);

 GPIO_InitTypeDef GPIO_InitStruct;
 GPIO_InitStruct.Pin = Step5_Pin;
 GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
 GPIO_InitStruct.Pull = GPIO_NOPULL;
 GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
 GPIO_InitStruct.Alternate = GPIO_AF3_TIM8;
 HAL_GPIO_Init(Step5_GPIO_Port, &GPIO_InitStruct);

 if (DBG_TMR)
 {
  tmrInfo(TIM8);
  gpioInfo(Step5_GPIO_Port);
 }
}
#endif /* TIM8 */

#ifdef DBG_PINS

typedef struct
{
 uint32_t pin;
 GPIO_TypeDef *port;
 int flag;
} T_DBG_INIT, *P_DBG_INIT;

T_DBG_INIT iniDbg[] =
{
#ifdef Dbg0_Pin
 {Dbg0_Pin, Dbg0_GPIO_Port, DBG0_TYPE},
#endif
#ifdef Dbg1_Pin
 {Dbg1_Pin, Dbg1_GPIO_Port, DBG1_TYPE},
#endif
#ifdef Dbg2_Pin
 {Dbg2_Pin, Dbg2_GPIO_Port, DBG2_TYPE},
#endif
#ifdef Dbg3_Pin
 {Dbg3_Pin, Dbg3_GPIO_Port, DBG3_TYPE},
#endif
#ifdef Dbg4_Pin
 {Dbg4_Pin, Dbg4_GPIO_Port, DBG4_TYPE},
#endif
#ifdef Dbg5_Pin
 {Dbg5_Pin, Dbg5_GPIO_Port, DBG5_TYPE},
#endif
#ifdef Dbg6_Pin
 {Dbg6_Pin, Dbg6_GPIO_Port, DBG6_TYPE},
#endif
#ifdef Dbg7_Pin
 {Dbg7_Pin, Dbg7_GPIO_Port, DBG7_TYPE},
#endif
#ifdef Dbg8_Pin
 {Dbg8_Pin, Dbg8_GPIO_Port, DBG8_TYPE},
#endif
#ifdef Dbg9_Pin
 {Dbg9_Pin, Dbg9_GPIO_Port, DBG9_TYPE},
#endif
#ifdef Dbg10_Pin
 {Dbg10_Pin, Dbg10_GPIO_Port, DBG10_TYPE},
#endif
#ifdef Dbg11_Pin
 {Dbg11_Pin, Dbg11_GPIO_Port, DBG11_TYPE},
#endif
};

void enaDbgPins(int flag)
{
 GPIO_InitTypeDef GPIO_InitStruct;
 P_DBG_INIT p = iniDbg;
 int count = sizeof(iniDbg) / sizeof(T_DBG_INIT);
 while (--count >= 0)
 {
  if ((p->flag & flag) != 0)
  {
   GPIO_InitStruct.Pin = p->pin;
   GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
   GPIO_InitStruct.Pull = GPIO_NOPULL;
   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
   HAL_GPIO_Init(p->port, &GPIO_InitStruct);
  }
  p++;
 }
}

#endif

typedef struct
{
 uint16_t mask;
 GPIO_TypeDef *gpio;
 const char *name;
} T_PORT_INPUT; //, *P_PORT_INPUT;

#define PORT_INPUT(pin) {pin ## _Pin, pin ## _GPIO_Port, #pin}

T_PORT_INPUT inputDef[] =
{
 PORT_INPUT(Pin10),
 PORT_INPUT(Pin11),
 PORT_INPUT(Pin12),
 PORT_INPUT(Pin13),
 PORT_INPUT(Pin15),
 PORT_INPUT(ZA),
 PORT_INPUT(ZB),
 PORT_INPUT(XA),
 PORT_INPUT(XB),
 PORT_INPUT(JogA1),
 PORT_INPUT(JogB1),
 PORT_INPUT(JogA2),
 PORT_INPUT(JogB2),
#ifdef Index_Pin
 PORT_INPUT(Index),
#endif
 PORT_INPUT(ExtInt),
 PORT_INPUT(ZFlag),
 PORT_INPUT(XFlag),
};

#define TMR_TEST (1 << 0)
#define TMR_STOP (1 << 1)
#define INPUT_TEST (1 << 2)
#define OUTPUT_TEST (1 << 3)
#define INPUT_PULLUP (1 << 4)
#define INPUT_PULLDOWN (1 << 5)

void testOutputs(int flag)
{
 if (flag & (INPUT_PULLUP | INPUT_PULLDOWN))
 {
  T_PORT_INPUT *p = inputDef;
  for (unsigned int i = 0; i < sizeof(inputDef) / sizeof(T_PORT_INPUT); i++)
  {
   int pinMask = p->mask;
   int j = 0;
   while (pinMask != 1)
   {
    pinMask >>= 1;
    j++;
   }
   printf("%-6s GPIO%c bit %2d %04x\n",
	  p->name, portName(p->gpio), j, (unsigned int) p->mask);
   j <<= 1;
   volatile uint32_t *pupdr = &p->gpio->PUPDR;
   *pupdr &= ~(3 << i);
   *pupdr |= ((flag & INPUT_PULLUP) ? GPIO_PULLUP : GPIO_PULLDOWN) << j;
   p++;
  }
 }

 if (flag & TMR_TEST)
 {
  unsigned int count = rVar.cfgFcy;
  unsigned int pre = 1;
  while (count > 65536)
  {
   count /= 10;
   pre *= 10;
  }
  pre -= 1;
  count -= 1;

#ifdef Z_TMR
  zTmrInit();
  zTmrCnt(count);
  zTmrSet(count);
  zTmrScl(pre);
  zTmrStart();
  zTmrCCR(count / 2);
  zTmrPWMMode();
  zTmrPWMEna();
  tmrInfo(Z_TMR);
#endif

#ifdef X_TMR
  xTmrInit();
  xTmrCnt(count);
  xTmrSet(count);
  xTmrScl(pre);
  xTmrStart();
  xTmrCCR(count / 2);
  xTmrPWMMode();
  xTmrPWMEna();
  tmrInfo(X_TMR);
#endif

#ifdef STEP2B_TMR
  step2bTmrInit();
  step2bTmrCnt(count);
  step2bTmrSet(count);
  step2bTmrScl(pre);
  step2bTmrStart();
  step2bTmrCCR(count / 2);
  step2bTmrPWMMode();
  step2bTmrPWMEna();
  tmrInfo(STEP2B_TMR);
#endif

#ifdef STEP3_TMR
  step3TmrInit();
  step3TmrCnt(count);
  step3TmrSet(count);
  step3TmrScl(pre);
  step3TmrStart();
  step3TmrCCR(count / 2);
  step3TmrPWMMode();
  step3TmrPWMEna();
  tmrInfo(STEP3_TMR);
#endif

#ifdef STEP4_TMR
  step4TmrInit();
  step4TmrCnt(count);
  step4TmrSet(count);
  step4TmrScl(pre);
  step4TmrStart();
  step4TmrCCR(count / 2);
  step4TmrPWMMode();
  step4TmrPWMEna();
  tmrInfo(STEP4_TMR);
#endif

#ifdef STEP5_TMR
  step5TmrInit();
  step5TmrCnt(count);
  step5TmrSet(count);
  step5TmrScl(pre);
  step5TmrStart();
  step5TmrCCR(count / 2);
  step5TmrPWMMode();
  step5TmrPWMEna();
  tmrInfo(STEP5_TMR);
#endif

#ifdef SPINDLE_TMR
  spindleTmrInit();
  spindleTmrCnt(count);
  spindleTmrSet(count);
  spindleTmrScl(pre);
  spindleTmrStart();
  spindleTmrCCR(count / 2);
  spindleTmrPWMMode();
  spindleTmrPWMEna();
  tmrInfo(SPINDLE_TMR);
#endif

#ifdef PWM_TMR
  pwmTmrInit();
  pwmTmrCnt(0);
  pwmTmrSet(count);
  pwmTmrScl(pre);
  pwmTmrStart();
  pwmTmrCCR(count / 2);
  pwmTmrPWMMode();
  pwmTmrPWMEna();
  tmrInfo(PWM_TMR);
#endif

#ifdef PWM_SHARED_INDEX
  indexTmrInit();
  indexTmrCnt(0);
  indexTmrSet(count);
  indexTmrScl(pre);
  indexTmrStart();
  pwmTmrCCR(count / 2);
  pwmTmrPWMMode();
  pwmTmrPWMEna();
  tmrInfo(INDEX_TMR);
#endif
 }

 unsigned int tmp;
 unsigned int i = 0;
 tmp = millis();
 int inputMask = 0;
 while (true)
 {
  if ((dbgRxReady() != 0)
  ||  (remRxReady() != 0))
   break;
  pollBufChar();
  if ((millis() - tmp) >= 10U)	/* if time elapsed */
  {
   tmp = millis();		/* save current time */
   if (flag & INPUT_TEST)
   {
    T_PORT_INPUT *p = inputDef;
    int mask = 1;
    for (unsigned int j = 0; i < sizeof(inputDef) / sizeof(T_PORT_INPUT); j++)
    {
     if ((p->gpio->IDR & p->mask) != 0) /* if bit set */
     {
      if ((inputMask & mask) == 0) /* if bit currently clear */
      {
       inputMask |= mask;	/* set input mask */
       printf("%-6s set\n", p->name);
       break;			/* one change per loop */
      }
     }
     else			/* if bit clear */
     {
      if ((inputMask & mask) != 0)
      {
       inputMask &= ~mask;	/* clear input mask */
       printf("%-6s clr\n", p->name);
       break;			/* one change per loop */
      }
     }
     mask <<= 1;		/* update mask */
     p++;			/* move to next input */
    }
    flushBuf();
   }
  }

  if (flag & OUTPUT_TEST)
  {
   i & (1 << 0) ? dirZSet()  : dirZClr();
   i & (1 << 1) ? dirXSet()  : dirXClr();
   i & (1 << 2) ? dir3Set()  : dir3Clr();
   i & (1 << 3) ? dir4Set()  : dir4Clr();
   i & (1 << 4) ? dir5Set()  : dir5Clr();
   i & (1 << 5) ? pin1Set()  : pin1Clr();
   i & (1 << 6) ? pin14Set() : pin14Clr();
   i & (1 << 7) ? pin17Set() : pin17Clr();
   i++;
  }
 }

 if (flag & TMR_STOP)
 {
#ifdef Z_TMR
  zTmrStop();
#endif
#ifdef X_TMR
  xTmrStop();
#endif
#ifdef STEP3_TMR
  step3TmrStop();
#endif
#ifdef STEP4_TMR
  step4TmrStop();
#endif
#ifdef STEP5_TMR
  step5TmrStop();
#endif
#ifdef SPINDLE_TMR
  spindleTmrStop();
#endif
#ifdef PWM_TMR
  pwmTmrStop();
#endif
#ifdef PWM_SHARED_INDEX
  indexTmrStop();
#endif
 }
}

#endif
