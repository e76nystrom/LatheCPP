/******************************************************************************/
//#if !defined(INCLUDE)
#define __LATHE__
#include "stm32f4xx_hal.h"

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#include <stdint.h>
#include <stdbool.h>

#define ENUM_M_STATES
#define ENUM_M_COMMANDS
#define ENUM_SEL_TURN
#define ENUM_SEL_THREAD
#define ENUM_OPERATIONS

#include "main.h"
#include "config.h"
#include "remvar.h"

#include "serialio.h"
#include "spi.h"
#include "lcd.h"

#include "Xilinx.h"
#include "zcontrol.h"
#include "xcontrol.h"

#ifdef EXT
#undef EXT
#endif

#define EXT
#include "lathe.h"
//#endif

#if defined(__LATHE_INC__)		// <-

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

 char syncInit;			/* initialized for sync operation */
 char syncStart;		/* waiting for start */
 char active;			/* axis active */

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

EXT char zSyncInit;		/* z sync init */

EXT T_ACCEL xTA;		/* x threading accel */
EXT T_ACCEL xPA;		/* x taper accel */
EXT T_ACCEL xRA;		/* x runout accel */
EXT T_ACCEL xMA;		/* x move accel */
EXT T_ACCEL xJA;		/* x jog accel */
EXT T_ACCEL xJSA;		/* x jog speed accel */
EXT T_ACCEL xSA;		/* x slow jog accel */

EXT T_ZXISR xIsr;		/* x isr variables */

EXT char xSyncInit;		/* x sync init */

#define Z_ACTIVE 1		/* z axis active */
#define X_ACTIVE 2		/* x axis active */

EXT char runoutActive;		/* runout active */
EXT char active;		/* axis driven by spindle */
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

#define WD_INTERVAL 50		/* interval between watchdog pulses */
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
 char buf[MAXJOG];
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
 char done;			/* done flag xilinx */
 char wait;			/* waiting for done xilinx */
 char ctlreg;			/* control register xilinx */
 char axisName;			/* axis name */
 int cmd;			/* move command */
 int dir;			/* direction -1 neg, 0 backlash, 1 pos */
 int dirChange;			/* direction */
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
 char mpgFlag;			/* mpg direction flag */
 char mpgBackWait;		/* mpg backlash wait */
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
 void (*isrStop) (char ch);	/* isr stop routine */
 void (*move) (int pos, int cmd); /* move absolute function */
 void (*moveRel) (int pos, int cmd); /* move relative function */
 void (*moveInit) (P_ACCEL ac, char dir, int dist); /* move initialization */
 void (*dirFwd) (void);		/* direction forward */
 void (*dirRev) (void);		/* direction rev */
 void (*start) (void);		/* axis start */
 void (*pulse) (void);		/* axis pulse */
} T_MOVECTL, *P_MOVECTL;

EXT T_MOVECTL zMoveCtl;
EXT T_MOVECTL xMoveCtl;

typedef struct s_homectl
{
 int state;
 int prev;
 int findDist;
 int backoffDist;
 int slowDist;
} T_HOMECTL, *P_HOMECTL;

EXT T_HOMECTL xHomeCtl;

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

typedef struct
{
 union
 {
  struct
  {
   char port;
   char num;
  };
  struct
  {
   uint16_t pinName;
  };
 };
} T_PIN_NAME;

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
void measureCmd(void);
void clearCmd(void);

void allStop(void);			/* stop all */

void zIsrStop(char ch);
void xIsrStop(char ch);
void spIsrStop(void);

void clearAll(void);
void setup(void);

void spindleSetup(int rpm);
void spindleInit(P_SPINDLE spa, int dist, int dir); /* init spindle */
void spindleStart(void);	/* start spindle */
void spindleJog(void);		/* spindle jog */
void spindleJogSpeed(void);	/* spindle jog at speed */
void spindleStop(void);		/* stop spindle */
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
void jogMpg1(P_MOVECTL mov);
void jogMpg(P_MOVECTL mov);
void jogSpeed(P_MOVECTL mov, float speed);

void zInit(P_AXIS ax);
void zReset(void);
void zHwEnable(int ctr);
void zTurnInit(P_ACCEL ac, char dir, int dist);
void zTaperInit(P_ACCEL ac, char dir);
void zMoveInit(P_ACCEL ac, char dir, int dist);
void zStart(void);
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
void zFwd(void);
void zRev(void);

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
void xMoveDro(float pos, int cmd);
void xMoveRel(int pos, int cmd);
void xControl(void);
void xFwd(void);
void xRev(void);
void xHomeAxis(void);
void xHomeControl(void);

void axisCtl(void);

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

T_PIN_NAME pinName(char *buf, GPIO_TypeDef *port, int pin);
char *gpioStr(char *buf, int size, T_PIN_NAME *pinInfo);
void gpioInfo(GPIO_TypeDef *gpio);
void tmrInfo(TIM_TypeDef *tmr);
void extiInfo(void);
void usartInfo(USART_TypeDef *usart, const char *str);
void i2cInfo(I2C_TypeDef *i2c, const char *str);

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
 while (1)
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

extern SPI_HandleTypeDef hspi2;
extern I2C_HandleTypeDef hi2c1;

extern uint32_t uwTick;

unsigned int millis(void)
{
 return((unsigned int) uwTick);
}

void wdUpdate(void)
{
 unsigned int curTime = millis();
 if ((curTime - wdUpdateTime) > wdTimeout)
 {
  wdUpdateTime = curTime;
  if (wdState)
  {
   pin17Clr();
   wdState = 0;
   wdTimeout =  WD_INTERVAL;
  }
  else
  {
   pin17Set();
   wdState = 1;
   wdTimeout = WD_PULSE;
  }
 }
}

void stopCmd(void)
{
 if (DBG_SETUP)
  printf("\nstop\n");

 stopMove();
 if (cfgXilinx == 0)
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
 cmdPause = 0;
 mvStatus &= ~(MV_PAUSE | MV_ACTIVE | MV_HOME_ACTIVE);
 xHomeCtl.state = H_IDLE;
#if WIN32
 fflush(stdout);
#endif
}

void measureCmd(void)
{
 if (DBG_SETUP)
  printf("\nmeasure\n");

 mvStatus |= MV_MEASURE;
}

void clearCmd(void)
{
 if (DBG_SETUP)
  printf("\nclear\n");

 allStop();
 clearAll();
#if WIN32
 fflush(stdout);
#endif
}

void pauseCmd(void)
{
 if (DBG_SETUP)
  printf("\npause\n");

 cmdPause = 1;
 mvStatus |= MV_PAUSE;
#if WIN32
 fflush(stdout);
#endif
}

void resumeCmd(void)
{
 if (DBG_SETUP)
  printf("\nresume\n");

 cmdPause = 0;
 if (jogPause & DISABLE_JOG)
  jogPause &= ~(PAUSE_ENA_X_JOG | PAUSE_ENA_Z_JOG);
 mvStatus &= ~(MV_PAUSE | MV_MEASURE | MV_READ_X | MV_READ_Z);
#if WIN32
 fflush(stdout);
#endif
}

#define clr(x) memset(&x, 0, sizeof(x))

void clearAll(void)
{
 syncStop();
 
 if (DBG_SETUP)
  printf("\nclear all\n");

 if (cfgXilinx == 0)
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

 zRunoutFlag = 0;
 zRunoutStart = 0;
 zRunoutDist = 0.0;
 zRunoutSteps = 0;

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

 xRunoutFlag = 0;
 xRunoutSteps = 0;

 clr(cmpTmr);

 if (cfgXilinx)
 {
  LOAD(XLDZCTL, ZRESET);
  LOAD(XLDZCTL, 0);
  LOAD(XLDXCTL, XRESET);
  LOAD(XLDXCTL, 0);
  LOAD(XLDTCTL, 0);
  LOAD(XLDDCTL, 0);
 }

 cmdPause = 0;
 jogPause = 0;
 mvStatus &= ~(MV_PAUSE | MV_ACTIVE | MV_HOME_ACTIVE | MV_MEASURE);

 currentPass = 0;
 totalPasses = 0;
 springInfo = 0;
  
 zAxis.stepsInch = INT_MAX;
 xAxis.stepsInch = INT_MAX;
 zDroCountInch = INT_MAX;
 xDroCountInch = INT_MAX;

 printf("Start ZFlag %d\n", ((ZFlag_Pin & ZFlag_GPIO_Port->ODR) != 0));
 printf("Start set\n");
 startSet();
 printf("Start ZFlag %d\n", ((ZFlag_Pin & ZFlag_GPIO_Port->ODR) != 0));
 runInit();
 printf("clearAll done\n");
 flushBuf();
}

void setup(void)
{
 if (cfgMpg)
 {
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn); /* enable mpg interrrupts */
  EXTI->PR = JogA1_Pin | JogA2_Pin | JogB1_Pin | JogB2_Pin;
 }
 else
  HAL_NVIC_DisableIRQ(EXTI9_5_IRQn); /* disable mpg interrrupts */

 if (cfgDro)
 {
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn); /* enable dro interrupts */
  EXTI->PR = ZA_Pin | ZB_Pin | XA_Pin | XB_Pin;
 }
 else
  HAL_NVIC_DisableIRQ(EXTI15_10_IRQn); /* enable dro interrupts */

#if I2C
 if (cfgLcd)
 {
  if (!lcdActive)
  {
   printf("lcdInit\n");
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
   printf("lcdInit done\n");
   flushBuf();
   lcdActive = 1;
   lcdRow = 0;
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

 if (cfgXilinx == 0)
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

 if (cfgXilinx == 0)
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

 setupDone = 1;			/* indicate setup complete */
}

void allStop(void)
{
 if (DBG_SETUP)
  printf("\nall stop\n");

 if (cfgXilinx == 0)
 {
  if (stepperDrive		/* if stepper drive */
  ||  motorTest)		/* or testing motor drive */
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

void spindleSetup(int rpm)
{
 if (DBG_SETUP)
 {
  printf("\nspindleSetup %d\n", rpm);
 }

 if (cfgVarSpeed)		/* spindle driven with variable speed motor */
 {
  if constexpr (PWM_TIMER != INDEX_TIMER) /* if pwm and idx tmrs different */
  { 
   constexpr int MAX_COUNT = 65536;

   int cnt = cfgFcy / pwmFreq;
   int preScale = (cnt % MAX_COUNT) ? cnt / MAX_COUNT + 1 : cnt / MAX_COUNT;
   cnt /= preScale;
   int pwmTmrVal = cnt;
   cnt -= 1;
    
   int pwm = (rpm * pwmTmrVal) / maxSpeed;

   if (DBG_SETUP)
   {
    printf("pwmFreq %d preScale %d cnt %d\n", pwmFreq, preScale, pwmTmrVal);
    printf("rpm %d maxSpeed %d pwm %d\n", rpm, maxSpeed, pwm);
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
   int pwm = (uint16_t) ((rpm * indexTmrCount) / maxSpeed);
    
   pwmTmrCCR(pwm - 1);
   pwmTmrPWMMode();
  }
 }
   
 if (sp.active == 0)		/* if spindle not active */
 {
  P_SPINDLE spa = &spA;
  GPIO_InitTypeDef gpio;

  if (spTestIndex)		/* if testing index pulse */
  {
   gpio.Pin = Index2_Pin;
   gpio.Mode = GPIO_MODE_INPUT;	/* configure as input */
   gpio.Pull = GPIO_NOPULL;
   HAL_GPIO_Init(Index2_GPIO_Port, &gpio);
  }
  else				/* if normal operation */
  {
   gpio.Pin = Index2_Pin;
   gpio.Mode = GPIO_MODE_IT_RISING; /* configure for interrupt */
   gpio.Pull = GPIO_NOPULL;
   HAL_GPIO_Init(Index2_GPIO_Port, &gpio);
  }

  HAL_NVIC_EnableIRQ(index2IRQn); /* enable index 2 interrupt */
  EXTI->PR = Index2_Pin;

  spa->label = "spA";
  if (stepperDrive		/* if using stepper drive */
  ||  motorTest)		/* or motor test */
  {
   spa->motorSteps = spSteps;
   spa->microSteps = spMicro;
   spa->minRPM = spMinRpm;
   if (rpm == 0)
    spa->maxRPM = spMaxRpm;
   else
    spa->maxRPM = rpm;
   if (ACCEL_TIME)
    spa->aTime = spAccelTime;
   else
    spa->accel = spAccel;
   if (spDirFlag)
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

    spa->motorSteps = spSteps;
    spa->microSteps = spMicro;
    spa->minRPM = 0;
    spa->maxRPM = spMaxRpm;
    spa->accel = spAccel;
    spa->dirFwd = spA.dirFwd;
    spa->dirRev = spA.dirRev;
#if 0
    spindleAccelCalc(spa);
#endif

    spa = &spJA;
    spa->label = "spJA";

    spa->motorSteps = spSteps;
    spa->microSteps = spMicro;
    spa->minRPM = spJogMinRpm;
    spa->maxRPM = spJogMaxRpm;
    if (ACCEL_TIME)
     spa->aTime = spJogAccelTime;
    else
     spa->accel = spAccel;
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
  s->stepsCycle = spa->stepsCycle;

  s->accel = 1;			/* set acceleration flag */
  s->decel = 0;			/* clear deceleration flag */
  s->accelStep = s->initialStep; /* set initial spindle step */
  s->lastCount = (int) (s->cFactor * sqrt(s->accelStep)); /* calc last */
  s->accelStep++;		/* update step */
  int count = (int) (s->cFactor * sqrt(s->accelStep)); /* calc first step */
  int ctr = count - sp.lastCount; /* value to load in timer */
  int pre = 1;			/* initialize prescaler */
  if (DBG_SETUP)
   printf("count %d lastCount %d ctr %d\n",
	  count, s->lastCount, ctr);
  while (ctr > 65535)		/* while counter out of range */
  {
   ctr >>= 1;			/* divide counter by two */
   pre <<= 1;			/* multiple prescaler by two */
  }
  sp.lastCount += ctr * pre;	/* update last count based on real count*/
  if (DBG_SETUP)
   printf("count %d lastCount %d pre %d ctr %d delta %d time %0.6f\n",
	  count, s->lastCount, pre, ctr, ctr * pre,
	  ((float) ctr * pre) / cfgFcy);
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
 revCounter = 0;		/* and revolution counter */

 if (stepperDrive)		/* if using stepper drive */
 {
  if (DBG_P)
   printf("timer %d psc %u arr %u cnt %u\n", SPINDLE_TIMER,
	  (unsigned int) SPINDLE_TMR->PSC, (unsigned int) SPINDLE_TMR->ARR,
	  (unsigned int) SPINDLE_TMR->CNT);

  spindleTmrStart();		/* start spindle timer */
  putBufStrX("S\n");
  dbgSpStopSet();

  if (motorTest)		/* if testing motor */
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
  revCounter = 0;
  lastIndexPeriod = 0;		/* clear last index period */

  if (cfgSwitch)		/* if spindle switched */
  {
   spRunSet();			/* turn on spindle */
   if (DBG_SETUP)
    printf("spRun %d\n", spRunRead());
  }

  if (cfgVarSpeed)		/* if var speed */
  {
   pwmTmrPWMEna();		/* start pwm */
  }
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

void syncSetup(void)
{
 cmpTmr.encCycLen = lSyncCycle;
 cmpTmr.encCycLen = lSyncOutput;
 cmpTmr.preScale = lSyncPrescaler;
}

void syncMeasure(void)
{
 syncStop();			/* stop encoder */

 if (DBG_SETUP)
  printf("syncMeasure\n");

 capTmrEnable = 1;		/* enable capture timer */

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

void syncCalculate(void)
{
 if (DBG_SETUP)
  printf("syncCalculatee\n");

 uint64_t n = clocksMin * cmpTmr.encCycLen;
 uint64_t d = ((uint64_t) cmpTmr.cycleClocks * encPerRev);
 uint16_t rpm = (uint16_t) (n / d);

 uint32_t pulseMinIn = encPerRev * rpm;
 uint32_t pulseMinOut = (pulseMinIn * lSyncOutput) / lSyncCycle;
 uint32_t clocksPulse = (uint32_t) (clocksMin / pulseMinOut);
 lSyncPrescaler = clocksPulse >> 16;

 if (DBG_SETUP)
  printf("n %lld d %lld rpm %d preScaler %d\n",
	 n, d, rpm, lSyncPrescaler);

 lSyncPrescaler += 1;
}

void syncStart(void)
{
 syncStop();			/* stop encoder */

 capTmrEnable = 1;		/* enable capture timer */
  
 cmpTmr.encCycLen = lSyncCycle;
 cmpTmr.intCycLen = lSyncOutput;
 cmpTmr.preScale = lSyncPrescaler;

 if (DBG_SETUP)
  printf("syncStart cycle %d output %d preScale %u\n",
	 cmpTmr.encCycLen, cmpTmr.intCycLen, cmpTmr.preScale);
  
 intTmrCntClr();		/* clear counter */

 cmpTmr.startDelay = (uint16_t) ((cfgFcy * START_DELAY) / 1000000l - 1);
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

void syncStop(void)
{
 if (DBG_SETUP)
  printf("syncStop\n");

 capTmrEnable = 0;		/* disable capture timer code */
 
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
  NVIC_EnableIRQ(encIRQn);     /* enable encoder interrrupts */
  EXTI->IMR |= encIRQ_Bit;     /* enable in mask register */
 }
 else				/* if disabling interrupt */
 {
  EXTI->IMR &= ~encIRQ_Bit;     /* enable in mask register */
  NVIC_DisableIRQ(encIRQn);	/* disable encoder interrrupts */
 }
}

#define SP_JTIMEINITIAL 0.75	/* initial jog time */
#define SP_JTIMEINC 0.15	/* incremental jog time */
#define SP_JTIMEMAX 1.0		/* maximum jog time */

void spindleJog(void)
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
  float time = spJogTimeInitial - spa->time; /* time after accel */
  int d = spa->steps + (int) (spa->stepsSec * time); /* initial steps */
  s->jogInc = (int) (spJogTimeInc * spa->stepsSec); /* save increment */
  s->maxDist = (int) (spJogTimeMax * spa->stepsSec); /* save maximum */

  if (DBG_P)
   printf("spindleJog dist %5d inc %5d max %5d\n",
	  d, s->jogInc, s->maxDist);

  int dir = spJogDir == 0 ? SP_FWD : SP_REV;
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

void spindleJogSpeed(void)
{
 P_SPINDLEISR s = &sp;
 __disable_irq();		/* disable interrupt */
 P_SPINDLE spa = &spJSA;	/* pointer to jog */
 if ((s->active == 0)		/* if spindle not active */
 &&  (spJogRpm != 0.0))
 {
  __enable_irq();		/* enable interrupts */
  int dir = SP_FWD;
  if (spJogRpm < 0)
  {
   spJogRpm = -spJogRpm;
   dir = SP_REV;
  }
  spa->maxRPM = spJogRpm;	/* set maximum speed */
  spindleAccelCalc(spa);	/* calculate acceleration */
  float time = spJogTimeInitial - spa->time; /* time after accel */
  int d = spa->steps + (int) (spa->stepsSec * time); /* initial steps */
  s->jogInc = (int) (2 * spJogTimeInc * spa->stepsSec); /* save increment */
  s->maxDist = (int) (2 * spJogTimeMax * spa->stepsSec); /* save maximum */

  if (DBG_P)
   printf("spindleJog dist %5d inc %5d max %5d\n",
	  d, s->jogInc, s->maxDist);

  spindleInit(spa, d, dir);
  spindleStart();
 }
 else				/* if spindle active */
 {
  __enable_irq();		/* enable interrupts */
  if (spJogRpm == 0.0)
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
   if (spJogRpm != spa->maxRPM)	/* if jog speed different */
   {
    spindleSpeedCalc(spJogRpm);	/* calculate acceleration */
    s->jogInc = (int) (2 * spJogTimeInc * spa->stepsSec); /* save increment */
    s->maxDist = (int) (2 * spJogTimeMax * spa->stepsSec); /* save maximum */
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
 int stepsSec = (int) ((finalRPM * spa->stepsRev) / 60.0);
 spa->stepsSec = stepsSec;
 int clocksStep = (int) (cfgFcy / stepsSec);

 if (DBG_P)
  printf("finalRPM %0.2f stepsSec %d clocksStep %d\n",
	 finalRPM, stepsSec, clocksStep);

 int finalStepsSec = (int) ((spa->stepsRev * finalRPM) / 60.0);
 float finalTime = finalStepsSec / spa->stepsSec2;
 unsigned int finalStep = (unsigned int) ((finalStepsSec * finalTime) / 2.0);

 if (DBG_P)
  printf("finalStepsSec %d finalTime %5.3f finalStep %d accelStep %d\n",
	 finalStepsSec, finalTime, finalStep, s->accelStep);

 int aClocksStep;
 if (finalStep > 0)
 {
  if (s->accelStep > finalStep)
  {
   aClocksStep = spa->cFactor * (sqrt(finalStep) - sqrt(finalStep - 1));
  }
  else
  {
   aClocksStep = spa->cFactor * (sqrt(finalStep + 1) -
				   sqrt(finalStep));
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
  s->lastCount = (int) (s->cFactor * sqrt(isrStep));
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

void spindleStop(void)
{
 if (DBG_SETUP)
  printf("\nspindle stop\n");

 if (stepperDrive)
 {
  sp.accel = 0;			/* clear acceleration flag */
  sp.decel = 1;			/* set deceleration flag to stop */
  dbgSpStopSet();
  syncStop();
 }
 else
 {
  if (cfgSwitch)		/* if switched spindle */
  {
   spRunClr();
  }
  if (cfgVarSpeed)		/* if variable speed */
  {
   if constexpr (PWM_TIMER != USEC_TIMER)
   { 
    pwmTmrStop();		/* stop timer */
   }
   pwmTmrPWMDis();		/* disable pwm */
  }
 }
}

float stepTime(float cFactor, int step)
{
 int c0 = (int) (cFactor * sqrt(step));
 int c1 = (int) (cFactor * sqrt(step + 1));
 int delta = c1 - c0;
 float time = (float) delta / cfgFcy;
 return(time);
}

void spindleAccelCalc(P_SPINDLE sp)
{
 if (DBG_SETUP)
  printf("\nspindleAccelCalc %s minRPM %3.0f maxRPM %3.0f\n",
	 sp->label, sp->minRPM, sp->maxRPM);

 sp->stepsRev = sp->motorSteps * sp->microSteps;

 sp->stepsSec = (sp->maxRPM * sp->stepsRev) / 60.0;
 sp->clocksStep = lrint(cfgFcy / sp->stepsSec);
 sp->clocksRev = sp->stepsRev * sp->clocksStep;

 if (DBG_P)
  printf("clocksStep %d clocksRev %d\n",
	 sp->clocksStep, sp->clocksRev);

 float stepsSecMin = (sp->minRPM * sp->stepsRev) / 60;
 float stepsSecMax = (sp->maxRPM * sp->stepsRev) / 60;
 float deltaV = stepsSecMax - stepsSecMin;

 if (DBG_P)
  printf("deltaV %4.1f stepsSecMin %4.1f stepsSecMax %4.1f\n",
	 deltaV, stepsSecMin, stepsSecMax);

 if (ACCEL_TIME)
 {
  sp->stepsSec2 = deltaV / sp->aTime;
  sp->accel =(sp->stepsSec2 / sp->stepsRev) * 60;

  if (DBG_P)
   printf("accel %0.3f rpm per sec\n", sp->accel);
 }
 else
 {
  sp->stepsSec2 = (sp->accel / 60) * sp->stepsRev;
  sp->aTime = deltaV / sp->stepsSec2;
  if (DBG_P)
   printf("stepsSec2 %0.0f aTime %0.3f accel %0.3f rpmSec\n",
	  sp->stepsSec2, sp->aTime, sp->accel);
 }

 float accelMinTime = stepsSecMin / sp->stepsSec2;
 float accelMaxTime = stepsSecMax / sp->stepsSec2;

 if (DBG_P)
  printf("accelMinTime %5.5f accelMaxTime %5.2f\n",
	 accelMinTime, accelMaxTime);

 sp->initialStep = lrint((stepsSecMin * accelMinTime) / 2);
 sp->finalStep = lrint((stepsSecMax * accelMaxTime) / 2);

 if (DBG_P)
  printf("initialStep %d finalStep %d\n", sp->initialStep, sp->finalStep);

 sp->time = deltaV / sp->stepsSec2;
 sp->steps = sp->finalStep - sp->initialStep;
 sp->clocks = sp->time * cfgFcy;
 sp->revs = ((float) sp->steps) / sp->stepsRev;

 if (DBG_P)
  printf("stepsSec2 %0.3f time %5.3f steps %d clocks %d revs %5.3f\n",
	 sp->stepsSec2, sp->time, sp->steps, sp->clocks, sp->revs);

 float cFactor0 = (cfgFcy * sqrt(2)) / sqrt(sp->stepsSec2);
 float cFactor1 = (sp->clocksStep / (sqrt(sp->finalStep) -
				     sqrt(sp->finalStep - 1)));
 sp->cFactor = cFactor1;

 if (DBG_P)
 {
  printf( "cFactor0 %0.2f cFactor1 %0.2f\n", cFactor0, cFactor1);
  printf("initialStepTime %0.6f finalStepTime %0.6f\n",
	 stepTime(cFactor1, sp->initialStep),
	 stepTime(cFactor1, sp->finalStep - 1));
 }

 int lastCount = (int) (sp->cFactor * sqrt(sp->initialStep));
 float lastTime = ((float) lastCount) / cfgFcy;

 if (DBG_P)
  printf("MinSteps %4d lastCount %8d lastTime %8.6f\n",
	 sp->initialStep, lastCount, lastTime);

 if (0)
 {
  int lastCtr = 0;
  unsigned int step;
  for (step = sp->initialStep + 1; step <= sp->finalStep; step++)
  {
   int count = (int) (sp->cFactor * sqrt(step));
   int ctr = count - lastCount;
   float time = ((float) count) / cfgFcy;
   float delta = time - lastTime;
   float freq = 1.0 / delta;
   float rpm = (freq / sp->stepsRev) * 60;

   if ((step % 50) == 0)
    if (DBG_P)
     printf("step %4d count %9d %7d %5d t %8.6f %8.6f f %8.2f rpm %4.1f\n",
	    step, count, ctr, ctr - lastCtr, time, delta, freq, rpm);

   lastCount = count;
   lastCtr = ctr;
   lastTime = time;
  }
  lastCount = (int) (sp->cFactor * sqrt(sp->finalStep));
  lastTime = ((float) lastCount) / cfgFcy;
  if (DBG_P)
   printf("accelMaxSteps %4d lastCount %8d lastTime %8.6f\n",
	  sp->finalStep, lastCount, lastTime);
 }
 int finalCount = (int) (sp->cFactor * sqrt(sp->finalStep));
 finalCount -= (int) (sp->cFactor * sqrt(sp->finalStep - 1));

 if (DBG_P)
  printf("finalCount %d clocksStep %d\n", finalCount, sp->clocksStep);
}

void slaveEna(void)
{
 if (spindleEncoder == 0)	/* *ok* if not using spindle encodeer */
 {
  if (DBG_SETUP)
   printf("\nslave enable 0 z %d x %d\n", zIsr.sync, xIsr.sync);

  int tmp = sp.stepsRev - 1;	/* get maximum spindle step number */
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
 ax->stepsInch = (int) ((ax->microSteps * ax->motorSteps) / ax->pitch);

 if (DBG_P)
  printf("stepsInch %d\n", ax->stepsInch);
}

void accelInit(P_AXIS ax, P_ACCEL ac)
{
 memset(ac, 0, sizeof(T_ACCEL));
 ac->stepsInch = ax->stepsInch;
}

int turnInit(P_ZXISR isr, P_ACCEL ac, char dir, int dist)
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
 int ctr;
 if (ac->cFactor != 0)
 {
  isr->accel = 1;
  isr->accelStep = isr->initialStep;
  ctr = (int) (isr->cFactor * sqrt(isr->accelStep));
  isr->accelStep++;
  isr->lastCount = (int) (isr->cFactor * sqrt(isr->accelStep));
  ctr = isr->lastCount - ctr;
  ctr -= ac->accelSpRem / 2;
  isr->clockSum = ctr;

  if (DBG_P)
   printf("initialCounter %d initialInterval %8.6f\n",
	  ctr, ((float) ctr) / cfgFcy);
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

void encTurnInit(P_ZXISR isr, P_ACCEL ac, char dir, int dist)
{
 if (DBG_P)
 {
  float d = (float) dist / ac->stepsInch;
  float rev = d / ac->pitch;
  printf("\nencTurnInit %s\n", ac->label);
  printf("dist %7.4f steps %d pitch %6.4f rev %6.2f spSteps %d\n",
	 d, dist, ac->pitch, rev, (int) (rev * encPerRev));
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

void syncTurnInit(P_ZXISR isr, P_ACCEL ac, char dir, int dist)
{
 if (DBG_P)
 {
  float d = (float) dist / ac->stepsInch;
  float rev = d / ac->pitch;
  printf("\nsyncTurnInit %s\n", ac->label);
  printf("dist %7.4f steps %d pitch %6.4f rev %6.2f spSteps %d\n",
	 d, dist, ac->pitch, rev, (int) (rev * encPerRev));
 }

 isr->steps = 0;
 isr->done = 0;
 isr->dir = dir;
 isr->dist = dist;
}

int taperInit(P_ZXISR isr, P_ACCEL ac, char dir)
{
 if (DBG_P)
  printf("\ntaperInit %s\n", ac->label);

 isr->dir = dir;
 int ctr = ac->clocksStep;
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

void encTaperInit(P_ZXISR isr, P_ACCEL ac, char dir, char syncInit)
{
 if (DBG_P)
  printf("\ntaperInit %s\n", ac->label);

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

int moveInit(P_ZXISR isr, P_ACCEL ac, char dir, int dist)
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
 int ctr;
 if (ac->steps != 0)
 {
  isr->accel = 1;
  isr->accelStep = isr->initialStep;
  ctr = (int) (isr->cFactor * sqrt(isr->accelStep));
  isr->accelStep++;
  isr->lastCount = (int) (isr->cFactor * sqrt(isr->accelStep));
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
 if (mov->state == ZIDLE)	/* if not moving */
 {
  P_ACCEL ac = mov->acJog;	/* pointer to jog */
#if 0
  float time = jogTimeInitial - ac->time; /* time after accel */
  int d = ac->steps + (int) (ac->stepsSec * time); /* initial steps */
#endif
  int d = (int) (ac->stepsSec * jogTimeInitial); /* initial steps */
  mov->iniDist = d;		/* save initial distance */
  if (dir < 0)			/* if direction negative */
   d = -d;			/* set to negative */
  mov->stop = 0;		/* clear stop flag */
  mov->jogInc = (int) (jogTimeInc * ac->stepsSec); /* save increment */
  mov->maxDist = (int) (jogTimeMax * ac->stepsSec); /* save maximum */

  if (DBG_P)
  {
   float stepsInch = ac->stepsInch;
   printf("JSpeed dir %d dist %0.4f inc %0.4f max %0.4f\n",
	  dir, d / stepsInch ,  mov->jogInc / stepsInch,
	  mov->maxDist / stepsInch);
  }

  mov->moveRel(d, mov->jogCmd);	/* start movement */
 }
 else if (mov->state == ZWAITBKLS) /* if waiting for backlash */
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
   zMoveRel(d, mov->jogCmd);	/* start movement */
  }
  else				/* if still moving */
  {
   isr->dist += mov->jogInc;	 /* add to distance */
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
  dir = jog->buf[jog->emp];	/* get value */
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
 if (mov->state == ZIDLE)	/* if not moving */
 {
  dbgJogMPG0Set();
  __disable_irq();		/* disable interrupt */
  if (jog->count != 0)		/* if anything in count */
  {
   --jog->count;		/* count removal */
   dist = jog->buf[jog->emp];	/* get value */
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
   
  if (mov->mpgFlag)		/* if direction inverted */
   dist = -dist;		/* invert distance */
  mov->maxDist = *(mov->mpgJogMax); /* set maximum distance */
  dist *= *(mov->mpgJogInc);	/* calculate distance */
  //printf("mpgJog 0 dist %4d\n", dist);
  mov->moveRel(dist, mov->jogCmd); /* start relative move */
  dbgJogMPG0Clr();
 }
 else if (mov->state == ZWAITBKLS) /* if waiting for backlash */
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
   dist = jog->buf[jog->emp];	/* get value */
   __enable_irq();		/* enable interrupts */
   jog->emp++;			/* update pointer */
   if (jog->emp >= MAXJOG)	/* if at end of queue */
    jog->emp = 0;		/* reset to start */
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

void jogSpeed(P_MOVECTL mov, float speed)
{
 int dir = 1;
 if (speed < 0)
 {
  dir = -1;
  speed = -speed;
 }
 P_ACCEL ac = mov->acJogSpeed;	/* pointer to jog */
 if (mov->state == ZIDLE)	/* if not moving */
 {
  ac->maxSpeed = speed;		/* update max speed */
  accelCalc(ac);		/* calculate acceleration */
  float time = 2 * jogTimeInitial - ac->time; /* time after accel */
  int d = ac->steps + (int) (ac->stepsSec * time); /* initial steps */
  mov->iniDist = d;		/* save initial distance */
  if (dir < 0)			/* if direction negative */
   d = -d;			/* set to negative */
  mov->stop = 0;		/* clear stop flag */
  mov->jogInc = (int) (2 * jogTimeInc * ac->stepsSec); /* save increment */
  mov->maxDist = (int) (2 * jogTimeMax * ac->stepsSec); /* save maximum */

  if (DBG_P)
  {
   float stepsInch = ac->stepsInch;
   printf("JSpeed dist %0.4f inc %0.4f max %0.4f\n",
	  d / stepsInch ,  mov->jogInc / stepsInch,
	  mov->maxDist / stepsInch);
  }

  mov->moveRel(d, mov->speedCmd); /* start movement */
 }
 else if (mov->state == ZWAITBKLS) /* if waiting for backlash */
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
   if (speed != ac->maxSpeed) /* if jog speed different */
   {
    speedCalc(ac, isr, speed); /* calculate acceleration */
    mov->jogInc = (int) (2 * jogTimeInc * ac->stepsSec); /* upd increment */
    mov->maxDist = (int) (2 * jogTimeMax * ac->stepsSec); /* update maximum */
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

void zReset(void)
{
 zTmrStop();
 zTmrClrIE();
 zTmrClrIF();
 zRunoutFlag = 0;
}

void zHwEnable(int ctr)
{
 zTmrScl(0);
 zTmrCnt(ctr);
 zTmrSet(ctr);
 zTmrCCR(tmrStepWidth);
 zTmrPWMMode();
 zTmrPWMEna();
 zTmrSetIE();
}

void zTurnInit(P_ACCEL ac, char dir, int dist)
{
 if (DBG_P)
  printf("\nzTurninit %s\n", ac->label);

 if (spindleEncoder == 0)	/* if no spindle encoder */
 {
  if (stepperDrive == 0)	/* if motor driven */
  {
   motorSetup(&zTA, zAccel, runCtl.zFeed); /* setup feed based upon rpm */
  }

  int ctr = turnInit(&zIsr, ac, dir, dist);
  zHwEnable(ctr);
 }
 else				/* if spindle encoder */
 {
  if (encActive & Z_ACTIVE)
  {
   encTurnInit(&zIsr, ac, dir, dist);
   zIsr.syncInit = zSyncInit;
  }
  else if (synIntActive & Z_ACTIVE)
  {
   syncTurnInit(&zIsr, ac, dir, dist);
   zIsr.syncInit = zSyncInit;
  }
  else if (synExtActive & Z_ACTIVE)
  {
   syncTurnInit(&zIsr, ac, dir, dist);
   zIsr.syncInit = zSyncInit;
  }

  if (runoutActive)		/* if runout */
  {
   if (encActive & X_ACTIVE)	/* if using encoder */
    xEncRunoutInit();		/* initialize for encoder runout */

   if ((runCtl.threadFlags & TH_LEFT) == 0) /* if right hand threading */
   {
    zRunoutStart = zRunoutSteps; /* start of runout */
    zRunoutFlag = 1;		/* set runout flag */
   }
   else				/* if left hand threading */
   {
    xIsr.syncInit = xSyncInit;
   }
  }
 }
}

void zTaperInit(P_ACCEL ac, char dir)
{
 if (ac->taper)
 {
  if (spindleEncoder == 0) 	/* *ok* if no spindle encoder */
  {
   int ctr = taperInit(&zIsr, ac, dir);
   zHwEnable(ctr);
  }
  else				/* *chk* if spindle encoder */
  {
   char syncInit = 0;
   if (encActive)
   {
    syncInit = SYNC_ACTIVE_ENC;
   }
   if (synIntActive)
   {
    syncInit = SYNC_ACTIVE_TAPER;
   }
   if (synExtActive)
   {
    syncInit = SYNC_ACTIVE_TAPER;
   }
   encTaperInit(&zIsr, ac, dir, syncInit);
  }
 }
}

void zMoveInit(P_ACCEL ac, char dir, int dist)
{
 zReset();
 int ctr = moveInit(&zIsr, ac, dir, dist);
 zHwEnable(ctr);
}

void zStart(void)
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

void zPulse(void)
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

void zStartSlave(void)
{
 zTmrSlvEna();
 zIsr.active = SYNC_ACTIVE_STEP;
 dbgmsg(D_ZEST, sp.intCount); /* spindle interrupt count at start */
 dbgZAccelSet();
 if (DBG_TMR)
 {
  tmrInfo(TIM2);
  newline();
  tmrInfo(SPINDLE_TMR);
 }
}

void zMoveAbsCmd(void)
{
 if (zMoveCtl.state == ZIDLE)
 {
  int pos = lrint(zMovePos * zAxis.stepsInch) + zHomeOffset;
  zMove(pos, zFlag);
 }
}

void zMoveRelCmd(void)
{
 if (zMoveCtl.state == ZIDLE)
 {
  int dist = lrint(zMoveDist * zAxis.stepsInch);
  zMoveRel(dist, zFlag);
 }
}

void zJogCmd(void)
{
 if ((moveQue.count == 0)	/* if not moving */
 ||  (jogPause & PAUSE_ENA_Z_JOG)
 ||  ((mvStatus & (MV_PAUSE | MV_MEASURE)) == (MV_PAUSE | MV_MEASURE)))
 {
  jogMove(&zMoveCtl, zJogDir);
 }
 else if (DBG_JOG)
  printf("zJogCmd count %d jogPause %x mvStatus %x\n",
	 moveQue.count, jogPause, mvStatus);
}

void zJogSpeedCmd(void)
{
 if ((moveQue.count == 0)	/* if not moving */
 || ((mvStatus & (MV_PAUSE | MV_MEASURE)) == (MV_PAUSE | MV_MEASURE)))
 {
  jogSpeed(&zMoveCtl, zJogSpeed);
 }
 else if (DBG_JOG)
  printf("zJogSpeedCmd count %d mvStatus %x\n",
	 moveQue.count, mvStatus);
}

void zLocCmd(void)
{
 if (zMoveCtl.state == ZIDLE)
 {
  zLoc = (int) (zSetLoc * zAxis.stepsInch);
 }
}

void zStop(void)
{
 if (DBG_P)
 printf("zStop dist %5d zLoc %5d\n", zIsr.dist, zLoc);

 zMoveCtl.stop = 1;
 zIsr.accel = 0;
 zIsr.decel = 1;
 dbgZAccelSet();
}

void zSetup(void)
{
 if (DBG_SETUP)
  printf("\nz axis setup\n");

 P_AXIS axis = &zAxis;
 axis->pitch = zPitch;
 axis->ratio = zRatio;
 axis->microSteps = zMicro;
 axis->motorSteps = zMotor;
 axis->accel = zAccel;
 axis->backlash = zBacklash;
 axis->axis = 'z';
 if (zDirFlag)
 {
  axis->dirFwd = Dir1_Pin;
  axis->dirRev = Dir1_Pin << 16;
 }
 else
 {
  axis->dirFwd = Dir1_Pin << 16;
  axis->dirRev = Dir1_Pin;
 }
 int stepsInch = lrint((axis->microSteps * axis->motorSteps * 
			axis->ratio) / axis->pitch);
 axis->stepsInch = stepsInch;
 axis->backlashSteps = lrint(axis->backlash * axis->stepsInch);

 zIsr.axis = 'z';

 if (DBG_SETUP)
  printf("zStepsInch %d zBacklash %0.4f zBacklashSteps %d\n",
	 stepsInch, axis->backlash, axis->backlashSteps);

 zPA.label = "zP";		/* taper accel */
 zPA.stepsInch = stepsInch;

 zMoveSetup();
}

void zMoveSetup(void)
{
 zTA.label = "zT";		/* z synchronous */
 zTA.stepsInch = zAxis.stepsInch;

 P_ACCEL ac = &zMA;		/* z move */
 ac->label = "zM";
 ac->minSpeed = zMoveMin;
 ac->maxSpeed = zMoveMax;
 ac->accel = zAxis.accel;
 ac->stepsInch = zAxis.stepsInch;
 accelCalc(ac);

 ac = &zJA;			/* z jog */
 ac->label = "zJ";
 ac->minSpeed = zJogMin;
 ac->maxSpeed = zJogMax;
 ac->accel = zAxis.accel;
 ac->stepsInch = zAxis.stepsInch;
 accelCalc(ac);

 memcpy(&zJSA, ac, sizeof(zJSA));
 zJSA.label = "zJS";		/* z jog speed */

 P_MOVECTL mov = &zMoveCtl;
 mov->axisName = 'z';
 mov->mpgJogInc = &zMpgInc;
 mov->mpgJogMax = &zMpgMax;
 mov->mpgFlag = zMpgFlag;
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
 mov->jogCmd = CMD_JOG;
 mov->speedCmd = CMD_SPEED;
 if (zUseDro)
 {
  mov->jogCmd |= DRO_UPD;
  mov->speedCmd |= CMD_SPEED;
 }
 mov->moveInit = &zMoveInit;
 mov->dirFwd = &zFwd;
 mov->dirRev = &zRev;
 mov->start = &zStart;
 mov->pulse = &zPulse;
}

void syncMoveSetup(void)
{
 if (DBG_SETUP)
  printf("\nsyncMoveSetup op %d %s turn %d %s thread %d %s\n",
	 currentOp, operationsList[(int) currentOp],
	 turnSync, selTurnList[(int) turnSync],
	 threadSync, selThreadList[(int) threadSync]);

 runoutActive = 0;
 active = 0;
 encActive = 0;
 synIntActive = 0;
 synExtActive = 0;
 
 zSyncInit = 0;
 xSyncInit = 0;

 char active;
 switch(currentOp)
 {
 case OP_TURN:
  active = Z_ACTIVE;
  break;
 case OP_FACE:
  active = X_ACTIVE;
  break;
 case OP_CUTOFF:
  active = X_ACTIVE;
  break;
 case OP_TAPER:
  active = X_ACTIVE | Z_ACTIVE;
  break;
 case OP_THREAD:
  active = Z_ACTIVE;
  break;
 default:
  active = Z_ACTIVE;
  break;
 }    
    
 if (currentOp != OP_THREAD) /* if not threading */
 {
  switch(turnSync)
  {
  case SEL_TU_SPEED: /* Motor Speed */
   break;
    
  case SEL_TU_STEP:  /* Stepper */
   break;
    
  case SEL_TU_ENC:   /* Encoder */
   encActive = active;
   if ((active & Z_ACTIVE) != 0)
    zSyncInit = SYNC_ACTIVE_ENC;
   if ((active & X_ACTIVE) != 0)
    xSyncInit = SYNC_ACTIVE_ENC;
   break;
    
  case SEL_TU_ISYN:  /* Int Syn */
   synIntActive = active;
   if (active & Z_ACTIVE)
    zSyncInit = SYNC_ACTIVE_TMR;
   if (active & X_ACTIVE)
    xSyncInit = SYNC_ACTIVE_TMR;
   break;
    
  case SEL_TU_ESYN:  /* Ext Syn */
   synExtActive = active;
   if (active & Z_ACTIVE)
    zSyncInit = SYNC_ACTIVE_EXT;
   if (active & X_ACTIVE)
    xSyncInit = SYNC_ACTIVE_EXT;
   break;
  }
 }
 else
 {
  char flag = runCtl.threadFlags;
  runoutActive = (flag & TH_RUNOUT) != 0;
  switch(threadSync)
  {
  case SEL_TH_NO_ENC:		/* no encoder threading disabled */
   break;

  case SEL_TH_STEP:		/* spindle stepper sync timers */
   break;

  case SEL_TH_ENC:		/* use encoder directly */
   encActive = Z_ACTIVE;
   zSyncInit = SYNC_ACTIVE_ENC;
   if (runoutActive)
   {
    encActive |= X_ACTIVE;
    xSyncInit = SYNC_ACTIVE_ENC;
   }
   break;

  case SEL_TH_ISYN_RENC:	/* internal sync runout encoder */
   synIntActive = Z_ACTIVE;
   zSyncInit = SYNC_ACTIVE_TMR;
   if (runoutActive)
   {
    encActive = X_ACTIVE;
    xSyncInit = SYNC_ACTIVE_ENC;
    break;

   case SEL_TH_ESYN_RENC:	/* external sync runout encoder */
    synExtActive = Z_ACTIVE;
    zSyncInit = SYNC_ACTIVE_EXT;
    if (runoutActive)
    {
     encActive = X_ACTIVE;
     xSyncInit = SYNC_ACTIVE_ENC;
    }
    break;

   case SEL_TH_ESYN_RSYN:	/* external sync runout sync */
    synExtActive = Z_ACTIVE;
    zSyncInit = SYNC_ACTIVE_EXT;
    if (runoutActive)
    {
     synIntActive = X_ACTIVE;
     xSyncInit = SYNC_ACTIVE_TMR;
    }
    break;
   }
  }
 }
 
 encoderDirect = ((zSyncInit | xSyncInit) & SYNC_ACTIVE_ENC) != 0;
 if (DBG_SETUP)
 {
  printf("zSyncInit %d xSyncInit %d encoderDirect %d\n",
	 zSyncInit, xSyncInit, encoderDirect);
  printf("active %d encActive %d synIntActive %d "
	 "synExtAcitve %d runoutActive %d\n",
	 active, encActive, synIntActive, synExtActive, runoutActive);
 }

 if (spindleEncoder)		/* *ok* */
 {
  HAL_NVIC_EnableIRQ(spSyncIRQn); /* enable spindle sync interrupt */
  EXTI->PR = ExtInt_Pin;
 }
 else
  HAL_NVIC_DisableIRQ(spSyncIRQn); /* disable spindle sync interrupt */
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
 }

 if (spindleEncoder == 0)	/* *ok* if not using encoder */
 {
  turnCalc(ac);
  turnAccel(ac, zAccel, T_STEP_SPINDLE | T_DBG_PRINT, 0);
 }
 else				/* *chk* if spindle encoder */
 {
  if (encActive & Z_ACTIVE)	/* if using encoder for z */
  {
   zIsr.encoderDirect = 1;
   encTurnCalc(ac);
  }
 }
 
 if (runoutActive)		/* if runout */
 {
  zRunoutDist = runoutDist;
  zRunoutSteps = lrint(runoutDist * ac->stepsInch);
  xRunoutSteps = lrint(fabs(runoutDepth) * xAxis.stepsInch);
  float runout = runoutDist / ac->pitch;

  if (DBG_P)
   printf("\nrunout %0.4f zRunoutDist %0.4f zRunoutSteps %d\n"	\
	  "runoutDepth %0.4f xRunoutSteps %d\n",
	  runout, zRunoutDist, zRunoutSteps,
	  runoutDepth, xRunoutSteps);

  if (spindleEncoder == 0)	/* *ok* if no spindle encoder */
  {
   runoutCalc(ac, &xRA, runout, runoutDepth);
  }
  else				/* *chk* if spindle encoder */
  {
   if (encActive & X_ACTIVE)
    encRunoutCalc(ac, &xRA, runout, runoutDepth);
  }
 }
 else				/* if no runout */
 {
  zRunoutDist = 0;
  zRunoutSteps = 0;
 }
}

void zInfo(char flag)
{
 if (flag == 1)
  printf("\n");
 printf("cr1 %2x sr %2x cnt %d cFactor %0.2f curCount %d %d stepsSec %d\n",
	(unsigned int) TIM2->CR1, (unsigned int) TIM2->SR, (int) TIM2->CNT,
	zIsr.cFactor, zIsr.curCount, (int) zTmrMaxRead(),
	(int) (cfgFcy / zIsr.curCount));
 printf("done %d accel %d decel %d initialStep %d accelStep %d finalStep %d",
	zIsr.done, zIsr.accel, zIsr.decel,
	zIsr.initialStep, zIsr.accelStep, zIsr.finalStep);
 if (flag == 0)
  printf("\n");
}

void zMove(int pos, int cmd)
{
 dbgmsg(D_ZMOV, pos);
 int dist = pos - zLoc;
 zMoveRel(dist, cmd);
}

void zMoveRel(int dist, int cmd)
{
 P_MOVECTL mov = &zMoveCtl;

 if (DBG_MOVOP)
 {
  float stepsInch = zAxis.stepsInch;
  printf("zMoveRel %2x l %7.4f d %7.4f\n",
	 cmd, zLoc / stepsInch, dist / stepsInch);
 }
 mov->loc = zLoc;		/* save current location */
 mov->expLoc = zLoc + dist;	/* calculate expected end location */
 mov->cmd = cmd;		/* save command */
 if (cfgDro)
  dbgmsg(D_ZDRO, zDroPos);
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
   mov->state = ZWAITBKLS;	/* set to wait for backlash */
  }
  else				/* if no backlash */
  {
   mov->state = ZSTARTMOVE;	/* set to start move */
   zControl();			/* and start move */
  }
 }
}

void zControl(void)
{
 P_MOVECTL mov = &zMoveCtl;

 if (mov->stop)			/* if stop */
 {
  mov->stop = 0;		/* clear stop flag */
  mov->state = ZWAITMOVE;	/* wait for move complete */
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
 case ZIDLE:			/* 0x00 idle state */
  break;

 case ZWAITBKLS:		/* 0x01 wait for backlash move to complete */
  if (zIsr.done)		/* if done */
  {
   dbgmsg(D_ZBSTP, zIsr.steps);
   zIsr.done = 0;		/* clear done flag */
   mov->state = ZSTARTMOVE;	/* advance to move state */
  }
  break;

 case ZSTARTMOVE:		/* 0x02 start an x move */
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
     float dist = (float) mov->dist / zAxis.stepsInch; /* distance */
     int taperDist = (int) (dist * xPA.taperInch * xAxis.stepsInch);
     xIsr.dist = taperDist;	/* save for isr */

     if (cfgDro)
      dbgmsg(D_XDRO, xDroPos);
     dbgmsg(D_XLOC, xLoc);
     dbgmsg(D_XDST, taperDist);

     if (DBG_P)
      printf("taperDist %4d %7.4f taperInch %8.6f zDist %4d %7.4f\n",
	     taperDist, (float) taperDist / xPA.stepsInch, xPA.taperInch,
	     mov->dist, dist);

     if ((stepperDrive == 0)	/* if motor driven */
     &&  (spindleEncoder == 0))	/* *ok* and no spindle encoder */
     {
      zStart();			/* start z */
      xStart();			/* start x */
     }
     dbgXTaperSet();
    } /* end taper */

    if (stepperDrive		/* if stepper drive */
    ||	spindleEncoder)		/* *chk* spindle encoder */
    {
     slaveEna();		/* enable slave mode */
    }
   }
   else				/* if not start on index pulse */
   {
    if (spindleEncoder == 0)	/* *ok* if no spindle encoder */
    {
     zStart();			/* start now */
     if (stepperDrive == 0)	/* if motor drive */
      trackSpeed = 1;		/* set to track speed */
     else
     {
      zIsr.active = SYNC_ACTIVE_STEP; /* set to active */
      dbgmsg(D_ZEST, sp.intCount); /* send spindle interrupt count at start */
     }
    }
    else			/* *chk* if spindle encoder */
    {
     zIsr.active = zIsr.syncInit; /* make active */
     zIsr.syncInit = 0;		/* clear init flag */
     dbgmsg(D_ZEST, spEncCount); /* encoder count at start */
    }
   }
   break;

  case CMD_JOG:
   zMoveInit(&zJA, mov->dir, mov->dist); /* setup move */
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
   if ((cmd & FIND_PROBE) != 0)
    zIsr.home |= PROBE_SET;
   if ((cmd & CLEAR_PROBE) != 0)
    zIsr.home |= PROBE_CLR;
   mov->jog = 1;
   zStart();
   break;
  }
  mov->state = ZWAITMOVE;	/* wait for move to complete */
 }
 break;

 case ZWAITMOVE:		/* 0x03 wait for an x move to complete */
  if (zIsr.done)		/* if done */
   mov->state = ZDONE;		/* clean up everything */
//  ||  !zTmrTstIE())		/* or interrupt enable cleared */
  break;

 case ZDONE:			/* 0x04 done state */
 default:			/* all others */
  zIsr.done = 0;		/* clear done flag */
  mov->cmd = 0;			/* clear command */
  mov->loc = zLoc;		/* save it */
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
  mov->state = ZIDLE;		/* set state to idle */
  dbgmsg(D_ZSTP, zIsr.steps);
  dbgmsg(D_ZST, mov->state);
  break;
 }
}

void zFwd(void)
{
 dirZFwd();
}

void zRev(void)
{
 dirZRev();
}

void xInit(P_AXIS ax)
{
 ax->axis = 'x';
 ax->pitch = X_LS_PITCH;
 ax->microSteps = X_MICRO_STEPS;
 ax->motorSteps = X_MOTOR_STEPS;
 ax->stepsInch = ((ax->microSteps * ax->motorSteps) / ax->pitch);

 if (DBG_SETUP)
  printf("\nxInit stepsInch %d\n", ax->stepsInch);
}

void xReset(void)
{
 xTmrStop();
 xTmrClrIE();
 xTmrClrIF();
}

void xHwEnable(int ctr)
{
 xTmrScl(0);
 xTmrCnt(ctr);
 xTmrSet(ctr);
 xTmrCCR(tmrStepWidth);
 xTmrPWMMode();
 xTmrPWMEna();
 xTmrSetIE();
}

void xTurnInit(P_ACCEL ac, char dir, int dist)
{
 if (spindleEncoder == 0)	/* if no spindle encoder */
 {
  if (stepperDrive == 0)	/* if motor drive */
  {
   motorSetup(&xTA, xAccel, runCtl.xFeed); /* setup feed based upon rpm */
  }

  xReset();
  int ctr = turnInit(&xIsr, ac, dir, dist);
  xHwEnable(ctr);
 }
 else				/* if spindle encoder */
 {
  if (encActive & X_ACTIVE)	/* if using encoder directly */
  {
   encTurnInit(&xIsr, ac, dir, dist);
   xIsr.syncInit = xSyncInit;
  }
  if (synIntActive & X_ACTIVE)	/* if internal sync */
  {
   syncTurnInit(&xIsr, ac, dir, dist);
   xIsr.syncInit = xSyncInit;
  }
  if (synExtActive & X_ACTIVE)	/* if external sync */
  {
   syncTurnInit(&xIsr, ac, dir, dist);
   xIsr.syncInit = xSyncInit;
  }
 }
}

void xTaperInit(P_ACCEL ac, char dir)
{
 if (ac->taper)
 {
  if (spindleEncoder == 0) 	/* *ok* if no spindle encoder */
  {
   int ctr = taperInit(&xIsr, ac, dir);
   xHwEnable(ctr);
  }
  else				/* *chk* if spindle encoder */
  {
   char syncInit = 0;
   if (encActive)
   {
    syncInit = SYNC_ACTIVE_ENC;
   }
   if (synIntActive)
   {
    syncInit = SYNC_ACTIVE_TAPER;
   }
   if (synExtActive)
   {
    syncInit = SYNC_ACTIVE_TAPER;
   }
   encTaperInit(&xIsr, ac, dir, syncInit);
  }
 }
}

void xRunoutInit(void)
{
 if (runoutDepth > 0)		/* if depth positive */
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

 int ctr = xRA.clocksStep;
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

 dbgmsg(D_XLOC, xLoc);
 dbgmsg(D_XDST, xIsr.dist);
}

void xSyncRunoutInit(void)
{
 xRunoutFlag = 1;		/* set the runout flag */
 xIsr.taper = TAPER_SLAVE | TAPER_RUNOUT; /* indicate x is tapering */
 xIsr.dist = xRunoutSteps;	/* set x runout distance */

 if (runoutDepth > 0)		/* if depth positive */
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

 dbgmsg(D_XLOC, xLoc);
 dbgmsg(D_XDST, xIsr.dist);
}

void xEncRunoutInit(void)
{
 xRunoutFlag = 1;		/* set the runout flag */
 xIsr.taper = TAPER_SLAVE | TAPER_RUNOUT; /* indicate x is tapering */
 xIsr.dist = xRunoutSteps;	/* set x runout distance */

 if (runoutDepth > 0)		/* if depth positive */
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

 dbgmsg(D_XLOC, xLoc);
 dbgmsg(D_XDST, xIsr.dist);
}

void xMoveInit(P_ACCEL ac, char dir, int dist)
{
 xReset();
 P_MOVECTL mov = &xMoveCtl;
 ac->useDro = (mov->cmd & DRO_POS) != 0; /* set use dro flag */
 ac->droTarget = mov->droTarget;
 int ctr = moveInit(&xIsr, ac, dir, dist);
 xHwEnable(ctr);
}

void xStart(void)
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

void xPulse(void)
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

void xStartSlave(void)
{
 xTmrSlvEna();
 dbgXAccelSet();
 xIsr.active = SYNC_ACTIVE_STEP;
 dbgmsg(D_XEST, sp.intCount); /* spindle interrupt count at start */
}

void xMoveAbsCmd(void)
{
 if (xMoveCtl.state == XIDLE)
 {
  int pos = lrint(xMovePos * xAxis.stepsInch) + xHomeOffset;
  xMove(pos, xFlag);
 }
}

void xMoveRelCmd(void)
{
 if (xMoveCtl.state == XIDLE)
 {
  int dist = lrint(xMoveDist * xAxis.stepsInch);
  if ((xFlag & DRO_POS) != 0)
  {
   int droCounts = lrint(xMoveDist * xAxis.droCountsInch);
   xMoveCtl.droTarget = xDroPos + droCounts;
   if (DBG_P)
   {
    printf("xMoveRelCmd dist %7.4f steps %7d droCounts %7d\n",
	   xMoveDist, dist, droCounts);
    printf("droTarget %7d droPos %7d droCounts %7d\n",
	   xMoveCtl.droTarget, xDroPos, xMoveCtl.droTarget - xDroPos);
   }
  }
  xMoveRel(dist, xFlag);
 }
}

void xJogCmd(void)
{
 if ((moveQue.count == 0)	/* if not moving */
 ||  (jogPause & PAUSE_ENA_X_JOG)
 ||  ((mvStatus & (MV_PAUSE | MV_MEASURE)) == (MV_PAUSE | MV_MEASURE)))
 {
  jogMove(&xMoveCtl, xJogDir);
 }
 else if (DBG_JOG)
  printf("xJogCmd count %d jogPause %x mvStatus %x\n",
	 moveQue.count, jogPause, mvStatus);
}

void xJogSpeedCmd(void)
{
 if ((moveQue.count == 0)	/* if not moving */
 || ((mvStatus & (MV_PAUSE | MV_MEASURE)) == (MV_PAUSE | MV_MEASURE)))
 {
  jogSpeed(&xMoveCtl, xJogSpeed);
 }
 else if (DBG_JOG)
  printf("xJogSpeedCmd count %d mvStatus %x\n",
	 moveQue.count, mvStatus);
}

void xLocCmd(void)
{
 if (xMoveCtl.state == XIDLE)
 {
  xLoc = (int) (xSetLoc * xAxis.stepsInch);
 }
}

void xStop(void)
{
 if (DBG_P)
  printf("xStop dist %5d xLoc %5d\n", xIsr.dist, xLoc);

 xMoveCtl.stop = 1;
 xIsr.accel = 0;
 xIsr.decel = 1;
 dbgXAccelSet();
 dbgXStopSet();
}

void xSetup(void)
{
 if (DBG_SETUP)
  printf("\nX axis setup\n");

 P_AXIS axis = &xAxis;
 axis->pitch = xPitch;
 axis->ratio = xRatio;
 axis->microSteps = xMicro;
 axis->motorSteps = xMotor;
 axis->accel = xAccel;
 axis->backlash = xBacklash;
 axis->axis = 'x';
 if (xDirFlag)
 {
  axis->dirFwd = Dir2_Pin;
  axis->dirRev = Dir2_Pin << 16;
 }
 else
 {
  axis->dirFwd = Dir2_Pin << 16;
  axis->dirRev = Dir2_Pin;
 }
 int stepsInch = lrint((axis->microSteps * axis->motorSteps * 
			axis->ratio) / axis->pitch);
 axis->stepsInch = stepsInch;
 axis->backlashSteps = lrint(axis->backlash * axis->stepsInch);
 axis->droCountsInch = xDroCountInch;

 xIsr.axis = 'x';

 if (DBG_SETUP)
  printf("xStepsInch %d xBacklash %0.4f xBacklashSteps %d\n",
	 stepsInch, axis->backlash, axis->backlashSteps);

 xPA.label = "xP";		/* taper accel */
 xPA.stepsInch = stepsInch;

 xRA.label = "xR";		/* runout accel */
 xRA.stepsInch = stepsInch;

 xMoveSetup();
}

void xMoveSetup(void)
{
 xTA.label = "xT";		/* synchronous accel */
 xTA.stepsInch = xAxis.stepsInch;

 P_ACCEL ac = &xMA;		/* move accel */
 ac->label = "xM";
 ac->minSpeed = xMoveMin;
 ac->maxSpeed = xMoveMax;
 ac->accel = xAxis.accel;
 ac->stepsInch = xAxis.stepsInch;
 ac->droCountsInch = xAxis.droCountsInch;
 accelCalc(ac);

 ac = &xJA;			/* jog accel */
 ac->label = "xJ";
 ac->minSpeed = xJogMin;
 ac->maxSpeed = xJogMax;
 ac->accel = xAxis.accel;
 ac->stepsInch = xAxis.stepsInch;
 ac->droCountsInch = xAxis.droCountsInch;
 accelCalc(ac);

 memcpy(&xJSA, ac, sizeof(xJSA)); /* jog speed accel */
 xJSA.label = "xJS";

 P_MOVECTL mov = &xMoveCtl;
 mov->axisName = 'x';
 mov->mpgJogInc = &xMpgInc;
 mov->mpgJogMax = &xMpgMax;
 mov->mpgFlag = xMpgFlag;
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
 mov->jogCmd = CMD_JOG;
 mov->speedCmd = CMD_SPEED;
 if (xUseDro)
 {
  mov->jogCmd |= DRO_UPD;
  mov->speedCmd |= CMD_SPEED;
 }
 if (DBG_SETUP)
  printf("xUseDro %d jogCmd %x\n", xUseDro, (unsigned int) mov->jogCmd);
 mov->moveInit = &xMoveInit;
 mov->dirFwd = &xFwd;
 mov->dirRev = &xRev;
 mov->start = &xStart;
 mov->pulse = &xPulse;
}

void xMoveRel(int dist, int cmd)
{
 P_MOVECTL mov = &xMoveCtl;

 int stepsInch = xAxis.stepsInch;
 if (DBG_MOVOP)
 {
  float xTmp = (float) (xLoc - runCtl.xHomeOffset) / stepsInch;
  printf("xMoveRel cmd %03x l %7.4f d %7.4f diam %7.4f\n",
	 cmd, xTmp, (float) dist / stepsInch, 2.0 * xTmp);
 }
 mov->loc = xLoc;		/* save current location */
 mov->expLoc = xLoc + dist;	/* save expected location */
 mov->cmd = cmd;		/* save command */
 if (cfgDro)
  dbgmsg(D_XDRO, xDroPos);
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
   mov->state = XWAITBKLS;	/* set to wait for backlash */
  }
  else				/* if no backlash */
  {
   mov->state = XSTARTMOVE;	/* set to start move */
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
 }

 if (spindleEncoder == 0)	/* *ok* if not using encoder */
 {
  turnCalc(ac);
  turnAccel(ac, xAccel,  T_STEP_SPINDLE | T_DBG_PRINT, 0);
 }
 else				/* *chk* if spindle encoder */
 {
  if (encoderDirect)
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
	(int) (cfgFcy / xIsr.curCount));
 printf("done %d accel %d decel %d initialStep %d accelStep %d finalStep %d",
	xIsr.done, xIsr.accel, xIsr.decel,
	xIsr.initialStep, xIsr.accelStep, xIsr.finalStep);
 if (flag == 0)
  printf("\n");
}

void xMove(int pos, int cmd)
{
 int dist = pos - xLoc;
 xMoveRel(dist, cmd);
}

void xMoveDro(float pos, int cmd)
{
 /* inches = counts / (counts / inch) */
 float droPos = ((float) (xDroPos - xDroOffset)) / xAxis.droCountsInch;
 float droDist = pos - droPos;
 /* steps = inches * (steps / inch) */
 int dist = lrint(droDist * xAxis.stepsInch);
 int droTarget = lrint(pos * xAxis.droCountsInch + xDroOffset);
 xMoveCtl.droTarget = droTarget;
 if (DBG_QUE)
 {
  /* counts = inches * (counts / inch) */
  unsigned int droCounts = abs(lrint(droDist * xAxis.droCountsInch));
  printf("xMoveDro cmd %03x pos %7.4f droPos %7.4f dist %7.4f steps %d "
	 "counts %d\n",
	 cmd, pos, droPos, pos - droPos, dist, droCounts);
  printf("droTarget %7d droPos %7d droCounts %7d\n",
	 droTarget, xDroPos, droTarget - xDroPos);
 }
 xMoveRel(dist, cmd);
}

void xControl(void)
{
 P_MOVECTL mov = &xMoveCtl;

 // if (mov->stop)		/* if stop */
 // mov->state = XDONE;		/* clean up in done state */

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
 case XIDLE:			/* 0x00 idle state */
  break;

 case XWAITBKLS:		/* 0x01 wait for backlash mv to complete */
  if (xIsr.done)		/* if done */
  {
   dbgmsg(D_XBSTP, xIsr.steps);
   xIsr.done = 0;		/* clear done flag */
   mov->state = XSTARTMOVE;	/* advance to move state */
  }
  break;

 case XSTARTMOVE:		/* 0x02 start an x move */
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
     float dist = (float) mov->dist / xAxis.stepsInch; /* distance */
     int taperDist = (int) (dist * zPA.taperInch * zAxis.stepsInch);
     zIsr.dist = taperDist;	/* save for isr */
     if (cfgDro)
      dbgmsg(D_ZDRO, zDroPos);
     dbgmsg(D_ZLOC, zLoc);
     dbgmsg(D_ZDST, taperDist);

     if (DBG_P)
      printf("taperDist %4d %7.4f taperInch %8.6f xDist %4d %7.4f\n",
	     taperDist, (float) taperDist / xPA.stepsInch, xPA.taperInch,
	     mov->dist, (float) mov->dist / xAxis.stepsInch);

     if ((spindleEncoder == 0)	/* *ok* if no spindle encoder */
     &&  (stepperDrive == 0))	/* and motor drive */
     {
      xStart();			/* start x */
      zStart();			/* start z */
     }
     dbgZTaperSet();
    }

    if (stepperDrive		/* if stepper drive */
    ||	spindleEncoder)		/* *chk* spindle encoder */
    {
     slaveEna();		/* enable slave mode */
    }
   }
   else				/* if not start on index pulse */
   {
    if (spindleEncoder == 0)	/* *ok* if no spindle encoder */
    {
     xStart();			/* start now */
     if (stepperDrive == 0)	/* if motor drive */
      trackSpeed = 1;		/* set to track speed */
     else
     {
      xIsr.active = SYNC_ACTIVE_STEP; /* set to active */
      dbgmsg(D_ZEST, sp.intCount); /* send spindle interrupt count at start */
     }
    }
    else			/* *chk* if spindle encoder */
    {
     xIsr.active = xIsr.syncInit; /* make active */
     xIsr.syncInit = 0;		/* clear init flag */
     dbgmsg(D_XEST, spEncCount); /* encoder count at start */
    }
   }
   break;

  case CMD_JOG:			/* jog */
   xMoveInit(&xJA, mov->dir, mov->dist); /* setup move */
   if ((cmd & XFIND_HOME) != 0)
    xIsr.home |= FIND_HOME;
   if ((cmd & XCLEAR_HOME) != 0)
    xIsr.home |= CLEAR_HOME;
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
   if ((cmd & XFIND_HOME) != 0)
    xIsr.home |= FIND_HOME;
   if ((cmd & XCLEAR_HOME) != 0)
    xIsr.home |= CLEAR_HOME;
   if ((cmd & FIND_PROBE) != 0)
    xIsr.home |= PROBE_SET;
   if ((cmd & CLEAR_PROBE) != 0)
    xIsr.home |= PROBE_CLR;
   mov->jog = 1;
   xStart();
   break;
  }
  mov->state = XWAITMOVE;	/* wait for move to complete */
 }
 break;

 case XWAITMOVE:		/* 0x03 wait for an x move to complete */
  if (xIsr.done)		/* if done */
  {
   if (DBG_MOVOP & DBG_DISABLE)
   {
    int spindleSteps = xIsr.stopPos + xIsr.stopRev * sp.stepsRev;
    spindleSteps -= xIsr.startPos + xIsr.startRev * sp.stepsRev;
    int revs = spindleSteps / sp.stepsRev;
    int steps = spindleSteps % sp.stepsRev;
    float fRev = (float) spindleSteps / sp.stepsRev;
    float fDist = (float) mov->dist / xAxis.stepsInch;

    if (DBG_P)
     printf("x dist %7.4f %6d feed %7.4f spindle revs %d steps %d\n",
	    fDist, mov->dist, fDist / fRev, revs, steps);
   }
   mov->state = XDONE;		/* clean up everything */
  }
  break;

 case XDONE:			/* 0x04 done state */
 default:			/* all others */
  if (mov->cmd & DRO_UPD)	/* fix x loc if used dro for position */
  {
   float droPos = ((float) (xDroPos - xDroOffset)) / xAxis.droCountsInch;
   xLoc = lrint(droPos * xAxis.stepsInch) + xHomeOffset;
   if (DBG_P)
    printf("DRO_UPD droPos %7.4f xPos %7.4f xLoc %6d\n",
	   2 * droPos, 2 * ((float) (xLoc - xHomeOffset)) / xAxis.stepsInch,
	   xLoc);
  }
  dbgXDoneClr();
  xIsr.done = 0;		/* clear done flag */
  mov->stop = 0;		/* clear stop flag */
  mov->cmd = 0;			/* clear command */
  mov->loc = xLoc;		/* save it */
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
  mov->state = XIDLE;		/* set state to idle */
  dbgmsg(D_XSTP, xIsr.steps);
  dbgmsg(D_XST, mov->state);
  break;
 }
}

void xFwd(void)
{
 dirXFwd();
}

void xRev(void)
{
 dirXRev();
}

void xHomeAxis(void)
{
 P_HOMECTL home = &xHomeCtl;

 int dir = xHomeDir;
 xHomeStatus = HOME_ACTIVE;
 home->findDist = dir * (int) (xHomeDist * xAxis.stepsInch);
 home->backoffDist = -dir * (int) (xHomeBackoffDist * xAxis.stepsInch);
 home->slowDist = dir * (int) (1.25 * xHomeBackoffDist * xAxis.stepsInch);
  
 mvStatus |= MV_HOME_ACTIVE;	/* set home active */
 mvStatus &= ~MV_XHOME;		/* set not homed */
 home->state = H_CHECK_ONHOME;

 P_ACCEL ac = &xSA;
 ac->label = "xS";
 ac->minSpeed = xHomeSpeed;
 ac->maxSpeed = xHomeSpeed;
 ac->accel = xAxis.accel;
 ac->stepsInch = xAxis.stepsInch;

 accelCalc(ac);
}

void xHomeControl(void)
{
 P_HOMECTL home = &xHomeCtl;

#if DBGMSG
 if (home->state != home->prev)
 {
  dbgmsg(D_HST, home->state);
  home->prev = home->state;
 }
#endif

 switch (home->state)
 {
 case H_IDLE:			/* 0x00 idle */
  break;

 case H_CHECK_ONHOME:		/* 0x01 check for home switch closed */
  if (xHomeSet())		/* if home switch closed */
  {
   xMoveRel(home->backoffDist, CMD_JOG); /* send backoff move */
   home->state = H_BACKOFF_HOME; /* go to back state */
  }
  else				 /* if home switch open */
  {
   xMoveRel(home->findDist, CMD_JOG | XFIND_HOME); /* find home switch */
   home->state = H_WAIT_FINDHOME; /* wait for home found */
  }
  break;

 case H_WAIT_FINDHOME:		/* 0x02 wait to find home switch */
  if (xMoveCtl.state == XIDLE)	/* if opeartion complete */
  {
   if (xHomeSet())		/* if home switch set */
    home->state = H_BACKOFF_HOME; /* advance to backoff state */
   else
   {				/* if did not find switch */
    xHomeDone = 1;		/* indicate done */
    xHomeStatus = HOME_FAIL;	/* set failure status */
    home->state = H_IDLE;	/* return to idle state */
   }
  }
  break;

 case H_BACKOFF_HOME:		/* 0x03 backoff home switch */
  if (xMoveCtl.state == XIDLE)	/* if opeartion complete */
  {
   if (xHomeSet())		/* if home switch closed */
    xMoveRel(home->backoffDist, CMD_JOG); /* send backoff move */
   else
   {
    xMoveRel(home->slowDist, JOGSLOW | XFIND_HOME); /* move back slowly */
    home->state = H_WAIT_SLOWFIND; /* advance to wait */
   }
  }
  break;

 case H_WAIT_BACKOFF:		/* 0x04 wait for backoff complete */
  if (xMoveCtl.state == XIDLE)	/* if opeartion complete */
  {
   if (xHomeClr())		/* if clear of switch */
   {
    xMoveRel(home->slowDist, JOGSLOW | XFIND_HOME); /* move back slowly */
    home->state = H_WAIT_SLOWFIND; /* advance to wait */
   }
   else
   {				/* if did not find switch */
    xHomeDone = 1;		/* indicate done */
    xHomeStatus = HOME_FAIL;	/* set failure status */
    home->state = H_IDLE;	/* return to idle state */
   }
  }
  break;

 case H_WAIT_SLOWFIND:		/* 0x05 wait to find switch */
  if (xMoveCtl.state == XIDLE)	/* if opeartion complete */
  {
   xHomeDone = 1;		/* set home done flag */
   mvStatus &= ~MV_HOME_ACTIVE;	/* home complete */
   if (xHomeSet())		/* if successful */
   {
    xHomeStatus = HOME_SUCCESS;	/* set flag */
    mvStatus |= MV_XHOME;	/* indicate homed */
    xLoc = 0;			/* set position to zero */
   }
   else				/* if failure */
   {
    xHomeStatus = HOME_FAIL;	/* set flag */
   }
   home->state = H_IDLE;	/* back to idle state */
  }
  break;
 }
}

void axisCtl(void)
{
 dbgAxisCtlSet();
 if ((millis() - indexUpdateTime) > indexTimeout) /* if index not updated */
 {
  indexTimeout = MAX_TIMEOUT;	/* set to maximum */
  if (indexPeriod != 0)
  {
   indexPeriod = 0;		/* set index period to zero */
   indexStart = 0;		/* reset start time */
   revCounter = 0;
   printf("mainLoop clear indexPeriod\n");
  }
 }

 if (zMoveCtl.state != ZIDLE)	/* if z axis active */
  zControl();			/* run z axis state machine */

 if (zMoveCtl.mpgBackWait)	/* if waiting for mpg backlash */
 {
  if (zIsr.done != 0)		/* if z done */
  {
   zIsr.done = 0;		/* clear done flag */
   zMoveCtl.mpgBackWait = 0;	/* clear backlash flag */
  }
 }
 else if (zJogQue.count != 0)	/* if z jog flag set */
 {
  jogMpg(&zMoveCtl);		/* run z jog routine */
 }
 
 if (xMoveCtl.state != XIDLE)	/* if x axis active */
  xControl();			/* run x axis state machine */

 if (xHomeCtl.state != H_IDLE) /* if home control not idle */
  xHomeControl();		/* run home statue machine */
 else
 {
  if (xMoveCtl.mpgBackWait)	/* if waiting for mpg backlash */
  {
   if (xIsr.done != 0)		/* if x done */
   {
    xIsr.done = 0;		/* clear done flag */
    xMoveCtl.mpgBackWait = 0;	/* clear backlash flag */
   }
  }
  else if (xJogQue.count != 0)	/* if x jog flag set */
  {
   jogMpg(&xMoveCtl);		/* run z jog routine */
  }
 }

#if 0
 if (stepperDrive == 0)
 {
  if (indexTmrAct == 0)		/* if index timer not active */
  {
   if (EXTI->PR & Index2_Pin)	/* clear index 2 interrupt */
   {
    indexTmrAct = 1;
    indexPeriod = 0;
    indexOverflow = 0;
    indexTmrCntClr();
    indexTmrSetIE();
   }
  }
  else				/* if index timer act */
  {
  }
 }
#endif
 
 dbgAxisCtlClr();
}

void runInit(void)
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

char queMoveCmd(uint32_t op, float val)
{
 P_MOVEQUE que = &moveQue;
 if (que->count < MAX_CMDS)
 {
  P_MOVECMD cmd = &que->cmd[que->fil];
  que->fil++;
  if (que->fil >= MAX_CMDS)
   que->fil = 0;
  cmd->op = op;
  cmd->val = val;
  que->count++;

  if (DBG_QUE)
   printf("move %2d op %-18s %4x val %7.4f\n",
	   que->count, mCommandsList[(int) cmd->cmd],
	  (unsigned int) cmd->op, cmd->val);
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

  if (DBG_QUE)
   printf("move %2d op %-14s %4x val %7d\n",
	  que->count, mCommandsList[(int) cmd->cmd],
	  (unsigned int) cmd->op, (int) cmd->iVal);
  return(1);
 }

 if (DBG_QUE)
  printf("move of op %8x val %d\n", (unsigned int) op, val);
 return(0);
}

void stopMove(void)
{
 memset(&moveQue, 0, sizeof(moveQue));
}

void procMove(void)
{
 P_RUN_CTL mv = &runCtl;

 if (cmdPause			/* if paused */
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

   --que->count;
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
    printf("%2d flag %04x %-14s\n",
	   cmd->cmd, cmd->flag, mCommandsList[(int) cmd->cmd]);
   }

   switch (cmd->cmd)
   {
   case MOVE_Z:
    val = lrint(cmd->val * zAxis.stepsInch) + mv->zHomeOffset;
    if (cfgXilinx == 0)
     zMove(val, cmd->flag);
    else
     zMoveX(val, cmd->flag);
    mv->state = M_WAIT_Z;
    break;

   case MOVE_X:
    val = lrint(cmd->val * xAxis.stepsInch) + mv->xHomeOffset;
    dbgmsg(D_XMOV, val);
    if (!cfgDro			/* if not confugre */
    ||  ((cmd->flag & DRO_POS) == 0)) /* or not using dro for position */
    {
     if (cfgXilinx == 0)
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
     xMoveDro(cmd->val, cmd->flag);
    }
    mv->state = M_WAIT_X;
    break;

   case SAVE_Z:
    if (DBG_QUE)
     printf("save z %7.4f\n", cmd->val);

    mv->zVal = lrint(cmd->val * zAxis.stepsInch) + mv->zHomeOffset;
    done = 0;
    break;

   case SAVE_X:
    if (DBG_QUE)
     printf("save X %7.4f\n", cmd->val);

    mv->xVal = lrint(cmd->val * xAxis.stepsInch) + mv->xHomeOffset;
    done = 0;
    break;

   case SAVE_Z_OFFSET:
    if (DBG_QUE)
     printf("save z offset %7.4f\n", ((float) cmd->iVal) / zAxis.stepsInch);

    mv->zHomeOffset = cmd->iVal;
    done = 0;
    break;

   case SAVE_X_OFFSET:
    if (DBG_QUE)
     printf("save x offset %7.4f\n", ((float) cmd->iVal) / xAxis.stepsInch );

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

    val = lrint(cmd->val * zAxis.stepsInch) + mv->zHomeOffset;
    moveZX(val, mv->xVal);
    mv->state = M_WAIT_Z;
    break;

   case MOVE_XZ:
    if (DBG_QUE)
     printf("move xz %7.4f\n", cmd->val);

    val = lrint(cmd->val * xAxis.stepsInch) + mv->xHomeOffset;
    moveXZ(mv->zVal, val);
    mv->state = M_WAIT_X;
    break;

   case TAPER_ZX:		/* move z taper x */
   {
    if (DBG_QUE)
     printf("taper zx %7.4f\n", cmd->val);

    xPA.stepsInch = xAxis.stepsInch;
    val = lrint(cmd->val * zAxis.stepsInch) + mv->zHomeOffset;
    int dist = mv->xVal - xLoc;
    int dir = dist >= 0 ? DIR_POS : DIR_NEG;

    if ((stepperDrive == 0)	/* if motor drive */
    &&  (spindleEncoder == 0))	/* and no encoder */
    {
     motorSetup(&zTA, zAccel, runCtl.zFeed);
    }

    if (cfgXilinx == 0)
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
    val = lrint(cmd->val * xAxis.stepsInch) + mv->xHomeOffset;
    int dist = mv->zVal - zLoc;
    int dir = dist >= 0 ? DIR_POS : DIR_NEG;
    
    if ((stepperDrive == 0)	/* if motor drive */
    &&  (spindleEncoder == 0))	/* and no encoder */
    {
     motorSetup(&xTA, xAccel, runCtl.xFeed);
    }
    
    if (cfgXilinx == 0)
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

    if (cfgXilinx == 0)
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
    if (cfgXilinx == 0)
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
    zSynSetup(mv->feedType, cmd->val, runoutDistance, runoutDepth);
    done = 0;
    break;

   case X_SYN_SETUP:
    mv->xFeed = cmd->val;
    if (cfgXilinx == 0)
     xSynSetup(mv->feedType, cmd->val);
    else
     xSynSetup(mv->feedType, cmd->val);
    done = 0;
    break;

   case PASS_NUM:
   {
    int iVal = cmd->iVal;
    mv->pass = iVal;
    int passNum = iVal * 0xff;

    if (DBG_QUE)
     printf("pass %2d flag %d\n", passNum, iVal >> 8);

    if ((iVal & 0xff00) == 0)
    {
     currentPass = passNum;
     springInfo = 0;
     if ((mvStatus & MV_MEASURE) /* if measure flag set */
     &&  (passNum > 1))		 /* and pass one or greater */
     {
      if (DBG_QUE)
       printf("measure start %d\n", passNum);

      cmdPause = 1;		/* pause */
      mvStatus |= MV_PAUSE;
      if (cfgXilinx == 0)
       spindleStop();
      else
       spindleStopX();
      mv->safeZ = zLoc - zHomeOffset;
      mv->safeX = xLoc - xHomeOffset;
      mv->state = M_WAIT_SPINDLE;
     }
     else
      done = 0;
    }
    else
    {
     springInfo = iVal;
     done = 0;
    }
    dbgmsg(D_PASS, iVal);
    break;
   }

   case QUE_PAUSE:
    if (DBG_QUE)
     printf("pause %x\n", (unsigned int) cmd->iVal);

    cmdPause = 1;
    jogPause = DISABLE_JOG | cmd->iVal;
    if (cmd->iVal & PAUSE_READ_X)
     mvStatus |= MV_READ_X;
    if (cmd->iVal & PAUSE_READ_Z)
     mvStatus |= MV_READ_Z;
    mvStatus |= MV_PAUSE;
    break;

   case MOVE_Z_OFFSET:
   {
    xFeed = thXStart - xLoc;
    int zOffset = -(int) (xFeed * tanThreadAngle);

    if (DBG_QUE)
     printf("xFeed %d %7.4f zOffset %d %7.4f\n",
	    xFeed, (float) xFeed / xAxis.stepsInch,
	    zOffset, (float) zOffset / zAxis.stepsInch);

    if ((mv->threadFlags & TH_LEFT) != 0)
     zOffset = -zOffset;
    if ((mv->threadFlags & TH_INTERNAL) != 0)
     zOffset = -zOffset;
    int zLoc = thZStart + zOffset;
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
    ac->minSpeed = probeSpeed;
    ac->maxSpeed = probeSpeed;
    ac->accel = zAxis.accel;
    ac->stepsInch = zAxis.stepsInch;
    accelCalc(ac);
    val = (int) (cmd->val * zAxis.stepsInch);
    zIsr.doneHome = 0;
    zHomeStatus = 0;
    if (PROBE_TEST)
    {
     setProbeDist(val / 2);

     if (DBG_QUE)
      printf("dist %d probeDist %d\n", val, probeDist);
    }
    if (probeSet())
    {
     zHomeStatus = PROBE_FAIL;
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
    ac->minSpeed = xHomeSpeed;
    ac->maxSpeed = xHomeSpeed;
    ac->accel = xAxis.accel;
    ac->stepsInch = xAxis.stepsInch;
    accelCalc(ac);
    val = (int) (cmd->val * xAxis.stepsInch);
    xIsr.doneHome = 0;
    xHomeStatus = 0;
    if (PROBE_TEST)
    {
     setProbeDist(val / 2);

     if (DBG_QUE)
      printf("dist %d probeDist %d\n", val, probeDist);
    }
    if (probeSet())
    {
     xHomeStatus = PROBE_FAIL;
     return;
    }
    xMoveRel(val, JOGSLOW | FIND_PROBE);
    mv->probeCmd = PROBE_X;
    mv->state = M_WAIT_PROBE;
    break;
   }

   case SAVE_Z_DRO:
    dbgmsg(D_ZPDRO, zDroPos);
    break;

   case SAVE_X_DRO:
    dbgmsg(D_XPDRO, xDroPos);
    break;

   case OP_DONE:
    dbgmsg(D_DONE, cmd->iVal);
    if (cmd->iVal == PARM_START)
    {
     mv->start = uwTick;
     mvStatus |= MV_ACTIVE;
     jogPause = DISABLE_JOG;
    }
    else if (cmd->iVal == PARM_DONE)
    {
     mv->start = 0;
     mvStatus &= ~MV_ACTIVE;
     jogPause = 0;
     if (capTmrEnable || encoderDirect)
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
  if (zMoveCtl.state == ZIDLE)	/* if operation complete */
  {
   if (xRunoutFlag)		/* if runout */
   {
    if (xIsr.active == 0)	/* if x isr no longer active active */
    {
     xRunoutFlag = 0;		/* clear runout flag */
     mv->state = M_IDLE;	/* return to idle state */
    }
   }
   else				/* if no runout */
    mv->state = M_IDLE;		/* return to idle state */
  }
  break;

 case M_WAIT_X:
  if (xMoveCtl.state == XIDLE)	/* if operation complete */
   mv->state = M_IDLE;
  break;

 case M_WAIT_SPINDLE:
  if (cfgXilinx == 0)		/* processor control version */
  {
   if (stepperDrive)		/* if stepper drive */
   {
    if ((sp.accel == 0)		/* if done accelerating */
    &&  (sp.decel == 0))	/* and done decelerating */
    {
     if (DBG_QUE)
      printf("spindle done mvStatus x%02x\n", (unsigned int) mvStatus);

     if ((mvStatus & (MV_PAUSE | MV_MEASURE)) ==
	 (MV_PAUSE | MV_MEASURE)) /* if paused for measuring */
      mv->state = M_WAIT_MEASURE; /* wait for measurement to complete */
     else			/* if not stopping for measuring */
      mv->state = M_IDLE;	/* go to idle state */
    }
   }
   else				/* if not stepper drive */
   {
    if (lastRevCount != revCounter)
    {
     lastRevCount = revCounter;
     if ((indexPeriod != 0) 
     &&  (lastIndexPeriod != 0))
     {
      int delta = indexPeriod - lastIndexPeriod;
      if (delta < 0)
       delta = -delta;
      float percent = delta * 100.0 / indexPeriod;
      float rpm = ((float) cfgFcy / indexPeriod) * 60;

      if (DBG_QUE)
      {
       printf("rpm %3.0f rev %2d indexPeriod %8d delta %10d %6.1f%%\n",
	      rpm, revCounter, indexPeriod, delta, percent);
       flushBuf();
      }

      if (percent < 1.0)
      {
       if (DBG_QUE)
	printf("spindleSync %d spindleSyncBoard %d useEncoder %d\n",
	       spindleSync, spindleSyncBoard, useEncoder);

       if (mv->spindleCmd == STOP_SPINDLE) /* if stopping spindle */
       {
	mv->state = M_IDLE;	/* return to idle state */
       }
       else			/* if not stopping spindle */
       {
	if (synExtActive)	/* if using external sync board */
	{
	 printf("Start ZFlag %d\n",
		((ZFlag_Pin & ZFlag_GPIO_Port->ODR) != 0));
	 printf("Start clr\n");
	 startClr();		/* set sync start flag */
	 printf("Start ZFlag %d\n",
		((ZFlag_Pin & ZFlag_GPIO_Port->ODR) != 0));
	 mv->state = M_WAIT_SYNC_READY; /* wait for encoder */
	}
	else if (synIntActive)	/* if using internal sync */
	{
	 syncSetup();		/* set up x encoder variables */
	 syncMeasure();		/* measure for encoder */
	 mv->state = M_WAIT_MEASURE_DONE; /* wait for measurement done */
	}
	else if (encActive)	/* if using encoder directly */
	{
	 encoderStart();	/* start encoder to use interrupt */
	 mv->state = M_IDLE;	/* return to idle state */
	}
#if 0	
	if (currentOp == OP_THREAD) /* if threading */
	{
	 if (spindleSync)	/* *ok* if spindle sync */
	 {
	  if (spindleSyncBoard)	/* *ok* if spindle sync board */
	  {
	   printf("Start ZFlag %d\n",
		  ((ZFlag_Pin & ZFlag_GPIO_Port->ODR) != 0));
	   printf("Start clr\n");
	   startClr();		/* set sync start flag */
	   printf("Start ZFlag %d\n",
		  ((ZFlag_Pin & ZFlag_GPIO_Port->ODR) != 0));
	   mv->state = M_WAIT_SYNC_READY; /* wait for encoder */
	  }
	  else			/* if using local timer */
	  {
	   if (useEncoder == 0)	/* if not using encoder directly */
	   {
	    syncSetup();	/* set up x encoder variables */
	    syncMeasure();	/* measure for encoder */
	    mv->state = M_WAIT_MEASURE_DONE; /* wait for measurement done */
	   }
	   else			/* if just using encoder */
	    mv->state = M_START_SYNC; /* start encoder */
	  }
	 }
	 else			/* if not using spindle sync */
	 {
	  syncStart();		/* start encoder to use interrupt */
	  mv->state = M_IDLE;	/* return to idle state */
	 }
	}
	else			/* if not threading */
	{
	 syncStart();		/* start encoder to use interrupt */
	 mv->state = M_IDLE;	/* return to idle state */
	}
#endif
       }	/* if not stopping spindle */
      }		/* if speed stable */
     }		/* if valid index period */
     lastIndexPeriod = indexPeriod; /* set new last period */
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
   if (synIntActive)		/* if using internal sync */
   {
    syncSetup();		/* set up x encoder variables */
    syncMeasure();		/* measure for x encoder */
    mv->state = M_WAIT_MEASURE_DONE; /* wait for measurement done */
   }
   else	if (encActive)		/* if using encoder */
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
   if (zMoveCtl.state == ZIDLE)	/* if opearation complete */
   {
    mv->state = M_IDLE;
    zHomeStatus = zIsr.doneHome ? PROBE_SUCCESS : PROBE_FAIL;

    if (DBG_QUE)
     printf("z probe done %d\n", zIsr.doneHome);
   }
  }
  else if (mv->probeCmd == PROBE_X)
  {
   if (xMoveCtl.state == XIDLE)	/* if opearation complete */
   {
    mv->state = M_IDLE;
    xHomeStatus = xIsr.doneHome ? PROBE_SUCCESS : PROBE_FAIL;

    if (DBG_QUE)
     printf("x probe done %d\n", xIsr.doneHome);
   }
  }
  break;

 case M_WAIT_MEASURE:
  if ((mvStatus & MV_MEASURE) == 0) /* if measurement complete */
  {
   if (DBG_QUE)
    printf("measure complete\n");

   xMove(mv->safeX, CMD_MAX);
   mv->state = M_WAIT_SAFE_X;
  }
  break;

 case M_WAIT_SAFE_X:
  if (xMoveCtl.state == XIDLE)	/* if operation complete */
  {
   zMove(mv->safeZ, CMD_MAX);
   mv->state = M_WAIT_SAFE_Z;
  }
  break;

 case M_WAIT_SAFE_Z:
  if (zMoveCtl.state == ZIDLE)	/* if operation complete */
  {
   if (cfgXilinx == 0)
   {
    if (stepperDrive)
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
}

void moveZX(int zDest, int xDest)
{
 if (DBG_MOVOP)
  printf("moveZX %7.4f %7.4f\n", (float) zDest / zAxis.stepsInch,
	 (float) xDest / xAxis.stepsInch);
}

void moveXZ(int zDest, int xDest)
{
 if (DBG_MOVOP)
  printf("moveZX %7.4f %7.4f\n", (float) zDest / zAxis.stepsInch,
	 (float) xDest / xAxis.stepsInch);

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
 if (spindleEncoder == 0)	/* *ok* if no spindle encoder */
 {
  int revCycle = lrint(1.0 / pitch);
  if (revCycle > 20)
   revCycle = 20;
  float cycleDist = revCycle * pitch;

  if (DBG_P)
   printf("pitch %5.3f revCycle %d cycleDist %5.3f\n",
	  pitch, revCycle, cycleDist);

  spA.clocksCycle = (int64_t) (spA.clocksRev * revCycle);
  spA.stepsCycle = spA.stepsRev * revCycle;
  ac->stepsCycle = lrint(ac->stepsInch * cycleDist);
  float cycleTime = ((float) spA.clocksCycle) / cfgFcy;

  if (DBG_P)
   printf("clocksCycle %lld cycleTime %6.3f stepsCycle %d z stepsCycle %d\n",
	  spA.clocksCycle, cycleTime, spA.stepsCycle, ac->stepsCycle);
 }
 else				/* *chk* if using spindle encoder */
 {
  if (ac->label[0] == 'z')	/* if z axis */
  {
   encoderDirect |= Z_ENCODER_DIRECT; /* use encoder directly for z */
   zIsr.encoderDirect = 1;	/* use encoder directly for z isr */
  }
  else				/* if x axis */
  {
   encoderDirect |= X_ENCODER_DIRECT; /* use encoder directly for x */
   xIsr.encoderDirect = 1;	/* use encoder directly for x isr */
  }
 }
}

void threadTPI(P_ACCEL ac, float tpi)
{
 if (DBG_P)
  printf("\nthreadTPI %s\n", ac->label);

 ac->pitch = 1.0 / tpi;
 if (spindleEncoder == 0)	/* *ok* if no spindle encoder */
 {
  spA.clocksCycle = (spA.clocksRev * (int64_t) (tpi * 100)) / 100;
  spA.stepsCycle = spA.stepsRev * tpi;
  ac->stepsCycle = ac->stepsInch;
  float cycleTime = ((float) spA.clocksCycle) / cfgFcy;

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

 ac->pitch = pitch / 25.4;
 if (spindleEncoder == 0)	/* *ok* if no spindle encoder */
 {
  int revolutions = 127;
  float inches = (pitch * revolutions) / 25.4;

  spA.clocksCycle = (int64_t) (spA.clocksRev * revolutions);
  spA.stepsCycle = spA.stepsRev * revolutions;
  ac->stepsCycle = ac->stepsInch * inches;
  float cycleTime = ((float) spA.clocksCycle) / cfgFcy;

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
			(int64_t) ac->clocksStep * ac->stepsCycle);
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

 int encPerInch = lrint(encPerRev / ac->pitch);
 int dx = encPerInch;
 int dy = ac->stepsInch;
 ac->incr1 = 2 * dy;
 ac->incr2 = ac->incr1 - 2 * dx;
 ac->d = ac->incr1 - dx;

 if (DBG_P)
  printf("encPerInch dx %d stepsInch dy %d incr1 %d incr2 %d d %d\n",
	 dx, dy, ac->incr1, ac->incr2, ac->d);
}

/* update clocks per step based on motor speed */

void motorUpdate(P_ZXISR isr, P_ACCEL ac);

void motorUpdate(P_ZXISR isr, P_ACCEL ac)
{
 if ((isr->accel == 0)		/* if not accel */
 &&  (isr->decel == 0)		/* and not decel */
 &&  (isr->taper == 0))		/* and not tapering */
 {
  ac->clocksStep = indexPeriod / ac->stepsCycle;
  isr->clocksStep = ac->clocksStep;
 }
}

/* calculation for use with external motor */

void motorSetup(P_ACCEL ac, float accel, float feed)
{
 if (DBG_P)
  printf("\nmotorSetup %s accel %0.0f feed %0.3f\n", ac->label, accel, feed);

 ac->pitch = feed;		/* save feed */
 ac->stepsCycle = (int) (feed * ac->stepsInch); /* one spindle rev */
 ac->clocksStep = indexPeriod / ac->stepsCycle;
 float rpm = ((float) cfgFcy / indexPeriod) * 60;

 if (DBG_P)
  printf("stepsCycle %d indexPeriod %d clocksStep %d rpm %5.1f\n",
	 ac->stepsCycle, indexPeriod, ac->clocksStep, rpm);

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
 ac->stepsSec = speedIPM * ac->stepsInch / 60;

 if (dbg)
  printf("RPM %0.0f speedIPM %4.1f in/min StepsSec %d steps/sec\n",
	 rpm, speedIPM, ac->stepsSec);

 if (ACCEL_TIME)
 {
 }
 else
 {
  ac->stepsSec2 = (ac->accel / 60) * ac->stepsInch;
  ac->time = (speedIPM / 60.0) / ac->accel;
 }

 if (dbg)
  printf("accel %5.3f in/sec^2 stepsSec2 %5.3f time %0.3f\n",
	 ac->accel, ac->stepsSec2, ac->time);

 ac->steps = (int) ((ac->time * ac->stepsSec) / 2.0);
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

  float cFactor0 = (cfgFcy * sqrt(2)) / sqrt(ac->stepsSec2);
  float cFactor1 = (ac->clocksStep / (sqrt(ac->finalStep) -
				      sqrt(ac->finalStep - 1)));
  ac->cFactor = cFactor1;

  ac->clocks = (int) (ac->cFactor * sqrt(ac->finalStep));
  ac->time = ((float) ac->clocks) / cfgFcy;
  ac->dist = ((float) ac->steps) / ac->stepsInch;

  ac->finalCount = (int) (ac->cFactor * sqrt(ac->finalStep));
  ac->initialCount = (int) (ac->cFactor * sqrt(ac->initialStep + 1));
  ac->initialCount -= (int) (ac->cFactor * sqrt(ac->initialStep));
  ac->totAccelClocks = ac->finalCount - ac->initialCount;
  ac->finalCount -= (int) (ac->cFactor * sqrt(ac->finalStep - 1));

  if (dbg)
  {
   printf( "cFactor0 %0.2f cFactor1 %0.2f\n", cFactor0, cFactor1);
   printf("time %8.6f steps %d clocks %d dist %5.3f\n",
	  ac->time, ac->steps, ac->clocks, ac->dist);
   printf("initialCount %d finalCount %d totAccelClocks %d\n",
	  ac->initialCount, ac->finalCount, ac->totAccelClocks);
   printf("initalTime %8.6f isrTime %8.6f\n",
	  ((float) ac->initialCount) / cfgFcy,
	  ((float) ac->totAccelClocks) / cfgFcy);
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
 int stepsSec = (int) ((finalSpeed * accel->stepsInch) / 60.0);
 accel->stepsSec = stepsSec;
 int clocksStep = (int) (cfgFcy / stepsSec);

 int finalStepsSec = (int) ((accel->stepsInch * finalSpeed) / 60.0);
 float finalTime = finalStepsSec / accel->stepsSec2;
 unsigned int finalStep = (unsigned int) ((finalStepsSec * finalTime) / 2.0);

 if (DBG_P)
 {
  printf("finalSpeed %0.2f stepsSec %d clocksStep %d\n",
	 finalSpeed, stepsSec, clocksStep);
  printf("finalStepsSec %d finalTime %5.3f finalStep %d accelStep %d\n",
	 finalStepsSec, finalTime, finalStep, isr->accelStep);
 }

 int aClocksStep;
 if (finalStep > 0)
 {
  if (isr->accelStep > finalStep)
  {
   aClocksStep = accel->cFactor * (sqrt(finalStep) - sqrt(finalStep - 1));
  }
  else
  {
   aClocksStep = accel->cFactor * (sqrt(finalStep + 1) -
				   sqrt(finalStep));
  }
  clocksStep = aClocksStep;

  if (DBG_P)
   printf("cFactor %0.2f aClocksStep %d finalStepsSec %d\n",
	  accel->cFactor, aClocksStep, finalStepsSec);
 }
 else
  finalStep = 1;

 __disable_irq();		/* disable interrupt */
 if (isr->dist != 0)
 {
  unsigned int isrStep = isr->accelStep;
  isr->lastCount = (int) (isr->cFactor * sqrt(isrStep));
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

 accel->stepsSec = (int) ((accel->maxSpeed * accel->stepsInch) / 60.0);
 accel->clocksStep = (int) (cfgFcy / accel->stepsSec);

 if (DBG_P)
  printf("stepsSec %d clocksStep %d\n",
	 accel->stepsSec, accel->clocksStep);

 int minStepsSec = (int) ((accel->stepsInch * accel->minSpeed) / 60.0);
 int maxStepsSec = (int) ((accel->stepsInch * accel->maxSpeed) / 60.0);
 if (DBG_P)
  printf("minStepsSec %d maxStepsSec %d\n",
	 minStepsSec, maxStepsSec);

 float deltaV = maxStepsSec - minStepsSec;
 if (ACCEL_TIME)
 {
  accel->stepsSec2 = accel->aTime * accel->stepsInch;

  if (DBG_P)
   printf("deltaV %2.0f stepsSec2 %6.3f\n",
	  deltaV, accel->stepsSec2);
 }
 else
 {
  accel->stepsSec2 = (accel->accel / 60) * accel->stepsInch;
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

  float cFactor0 = (cfgFcy * sqrt(2)) / sqrt(accel->stepsSec2);
  if (accel->finalStep > 0)
  {
   float cFactor1 = (accel->clocksStep / (sqrt(accel->finalStep) -
					  sqrt(accel->finalStep - 1)));
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
  int finalCount = (int) (accel->cFactor * sqrt(accel->finalStep));
  accel->clocks = finalCount;
  accel->clocks -= (int) (accel->cFactor * sqrt(accel->initialStep));
  accel->time = ((float) accel->clocks) / cfgFcy;
  accel->dist = (float) accel->steps / accel->stepsInch;
  finalCount -= (int) (accel->cFactor * sqrt(accel->finalStep - 1));

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

 float a0CycleDist = taperCycleDist;
 float a1CycleDist = taper * a0CycleDist;

 if (DBG_P)
  printf("a0CycleDist %6.4f a1CycleDist %6.4f\n",
	 a0CycleDist, a1CycleDist);

 if (spindleEncoder == 0)	/* *ok* if no spindle encoder */
 {
  a1->accelSpSteps = 0;
  a1->accelSpRem = 0;

  int d0Steps = lrint(a0CycleDist * a0->stepsInch);
  int d1Steps = lrint(a1CycleDist * a1->stepsInch);
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
  if (encActive)		/* if using encoder */
  {
   int dx = lrint((encPerRev * a0CycleDist) / a0->pitch); /* encPercycle */
   int dy = lrint(a1CycleDist * a1->stepsInch); /* stepsCycle */
   a1->incr1 = 2 * dy;
   a1->incr2 = a1->incr1 - 2 * dx;
   a1->d = a1->incr1 - dx;

   if (DBG_P)
    printf("encPerCycle dx %d stepsCycle dy %d incr1 %d incr2 %d d %d\n",
	   dx, dy, a1->incr1, a1->incr2, a1->d);
  }
  if (synIntActive		/* if using sync */
  ||  synExtActive)
  {
   int dx = lrint(a0CycleDist * a0->stepsInch);
   int dy = lrint(a1CycleDist * a1->stepsInch);
   a1->incr1 = 2 * dy;
   a1->incr2 = a1->incr1 - 2 * dx;
   a1->d = a1->incr1 - dx;

   if (DBG_P)
    printf("synPerCycle dx %d stepsCycle dy %d incr1 %d incr2 %d d %d\n",
	   dx, dy, a1->incr1, a1->incr2, a1->d);
  }
 }
}

void runoutCalc(P_ACCEL a0, P_ACCEL a1, float runout, float runoutDepth)
{
 printf("\nrunoutCalc a0 %s a1 %s runout %7.4f runoutDepth %7.4f\n",
	a0->label, a1->label, runout, runoutDepth);

 int d0Clocks = (int) (runout * spA.clocksRev);
 int d1Steps = xRunoutSteps;

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

void encRunoutCalc(P_ACCEL a0, P_ACCEL a1, float runout, float runoutDepth)
{
 printf("\nencRunoutCalc a0 %s a1 %s runout %7.4f runoutDepth %7.4f\n",
	a0->label, a1->label, runout, runoutDepth);

 int dx = lrint(runout * encPerRev);
 int dy = xRunoutSteps;

 a1->incr1 = 2 * dy;
 a1->incr2 = a1->incr1 - 2 * dx;
 a1->d = a1->incr1 - dx;

 if (DBG_P)
 {
  printf("encClocks dx %d xRunoutSteps dy %d incr1 %d incr2 %d d %d\n",
	 dx, dy, a1->incr1, a1->incr2, a1->d);
 }
}

/* TIM3 init function */

extern TIM_HandleTypeDef htim3;

void TIM3_Init(void)
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

extern TIM_HandleTypeDef htim8;

void TIM8_Init(void)
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
 GPIO_TypeDef *port;
 char name;
} T_GPIO, *P_GPIO;

T_GPIO gpio[] = 
{
 {GPIOA, 'A'},
 {GPIOB, 'B'},
 {GPIOC, 'C'},
 {GPIOD, 'D'},
 {GPIOE, 'E'},
};

char portName(GPIO_TypeDef *port);

char portName(GPIO_TypeDef *port)
{
 for (unsigned int j = 0; j < sizeof(gpio) / sizeof(T_GPIO); j++)
 {
  if (port == gpio[j].port)
  {
   return(gpio[j].name);
  }
 }
 return('*');
}

T_PIN_NAME pinName(char *buf, GPIO_TypeDef *port, int pin)
{
 char pName = portName(port);
 T_PIN_NAME val;
 val.port = pName;
 int pinNum = 0;
 while (pin != 0)
 {
  if (pin & 1)
   break;
  pin >>= 1;
  pinNum++;
 }
 sprintf(buf, "P%c%d", pName, pinNum);
 val.num = pinNum;
 return(val);
}

char modeInfo[] = {'I', 'O', 'F', 'A'};
const char *typeInfo[] = {"PP", "OD", "  "};
const char *speedInfo[] = {"LS", "MS", "HS", "VH", "  "};
const char *pupdInfo[] = {"  ", "PU", "PD", "**"};

char *gpioStr(char *buf, int size, T_PIN_NAME *pinInfo)
{
 buf[0] = 0;
 GPIO_TypeDef *port;
 for (unsigned int j = 0; j < sizeof(gpio) / sizeof(T_GPIO); j++)
 {
  if (gpio[j].name == pinInfo->port)
  {
   port = gpio[j].port;
   int pin = pinInfo->num;
//   printf("port  %08x %2d %c %2d\n", (unsigned int) port, pin,
//	  pinInfo->port, pinInfo->num);

   int mode = (port->MODER >> (pin << 1)) & 3;
//   printf("mode  %08x %d\n", (unsigned int) port->MODER, mode);

   int outType = (port->OTYPER >> pin) & 1;
//   printf("type  %08x %d\n", (unsigned int) port->OTYPER, outType);

   int outSpeed = (port->OSPEEDR >> (pin << 1)) & 3;
//   printf("speed %08x %d\n", (unsigned int) port->OSPEEDR, outSpeed);

   int pupd = (port->PUPDR >> (pin << 1)) & 3;
//   printf("pupd  %08x %d\n", (unsigned int) port->PUPDR, pupd);

   int afr = (port->AFR[pin >> 3] >> ((pin << 2) & 0x1f)) & 0xf;

   char interrupt = ' ';
   if (mode == GPIO_MODE_INPUT)
   {
    outType = (sizeof(typeInfo) / sizeof(char *)) - 1;
    outSpeed = (sizeof(speedInfo) / sizeof(char *)) - 1;

    if ((EXTI->IMR >> pin) & 1)
    {
     int exti = (SYSCFG->EXTICR[pin >> 2] >> ((pin << 2) & 0xf)) & 0xf;
     if ((pinInfo->port - 'A') == exti)
      interrupt = 'I';
//     printf("exti %2d pinInfo->port - 'A' %d pin >> 2 %d pin << 2 %d\n",
//	    exti, pinInfo->port - 'A', pin >> 2, pin << 2);
    }
   }

//   printf("afr   %08x %d (pin >> 3) %d ((pin << 2) & 0x1f) %2d\n",
//	  (unsigned int) port->AFR[pin >> 3], afr,
//	  (pin >> 3), ((pin << 2) & 0x1f));
//   flushBuf();

   snprintf(buf, size, "%c %c %2s %2s %2s %2d",
	    interrupt, modeInfo[mode], typeInfo[outType],
	    speedInfo[outSpeed], pupdInfo[pupd], afr);
   break;
  }
 }
 return(buf);
}

void gpioInfo(GPIO_TypeDef *gpio)
{
 printf("gpio %x %c\n",(unsigned int) gpio, portName(gpio));
 printf("MODER   %8x ",(unsigned int) gpio->MODER);
 printf("OTYPER  %8x\n",(unsigned int) gpio->OTYPER);
 printf("OSPEEDR %8x ",(unsigned int) gpio->OSPEEDR);
 printf("PUPDR   %8x\n",(unsigned int) gpio->PUPDR);
 printf("IDR     %8x ",(unsigned int) gpio->IDR);
 printf("ODR     %8x\n",(unsigned int) gpio->ODR);
 printf("BSRR    %8x ",(unsigned int) gpio->BSRR);
 printf("LCKR    %8x\n",(unsigned int) gpio->LCKR);
 printf("AFR[0]  %8x ",(unsigned int) gpio->AFR[0]);
 printf("AFR[1]  %8x\n",(unsigned int) gpio->AFR[1]);
 int i;
 printf("         ");
 for (i = 0; i < 16; i++)
  printf(" %2d", i);

 printf("\nmoder    ");
 int val = gpio->MODER;
 for (i = 0; i < 16; i++)
  printf(" %2d", (val >> (2 * i)) & 0x3);

 printf("\notyper   ");
 val = gpio->OTYPER;
 for (i = 0; i < 16; i++)
  printf(" %2d", (val >> i) & 0x1);

 printf("\nopspeedr ");
 val = gpio->OSPEEDR;
 for (i = 0; i < 16; i++)
  printf(" %2d", (val >> (2 * i)) & 0x3);

 printf("\npupdr    ");
 val = gpio->PUPDR;
 for (i = 0; i < 16; i++)
  printf(" %2d", (val >> (2 * i)) & 0x3);

 printf("\nidr      ");
 val = gpio->IDR;
 for (i = 0; i < 16; i++)
  printf(" %2d", (val >> i) & 0x1);

 printf("\nodr      ");
 val = gpio->ODR;
 for (i = 0; i < 16; i++)
  printf(" %2d", (val >> i) & 0x1);

 printf("\nafr      ");
 val = gpio->AFR[0];
 for (i = 0; i < 8; i++)
  printf(" %2d", (val >> (4 * i)) & 0xf);
 val = gpio->AFR[1];
 for (i = 0; i < 8; i++)
  printf(" %2d", (val >> (4 * i)) & 0xf);
 printf("\n");
 flushBuf();
}

typedef struct
{
 TIM_TypeDef *tmr;
 char num;
} T_TIM, *P_TIM;

T_TIM tim[] =
{
 {TIM1,  1},
 {TIM2,  2},
 {TIM3,  3},
 {TIM4,  4},
 {TIM5,  5},
#ifdef TIM6
 {TIM6,  6},
#endif
#ifdef TIM7
 {TIM7,  7},
#endif
#ifdef TIM8
 {TIM8,  8},
#endif
 {TIM9,  9},
 {TIM10, 10},
 {TIM11, 11},
#ifdef TIM12
 {TIM12, 12},
#endif
#ifdef TIM13
 {TIM13, 13},
#endif
#ifdef TIM14
 {TIM14, 14},
#endif
};

char timNum(TIM_TypeDef *tmr);

char timNum(TIM_TypeDef *tmr)
{
 for (unsigned int j = 0; j < sizeof(tim) / sizeof(T_TIM); j++)
 {
  if (tmr == tim[j].tmr)
  {
   return(tim[j].num);
  }
 }
 return(0);
}

void tmrInfo(TIM_TypeDef *tmr)
{
 printf("tmr %x TIM%d\n",(unsigned int) tmr, timNum(tmr));
 printf("CR1   %8x ",(unsigned int) tmr->CR1);
 printf("CR2   %8x\n",(unsigned int) tmr->CR2);
 printf("SMCR  %8x ",(unsigned int) tmr->SMCR);
 printf("DIER  %8x\n",(unsigned int) tmr->DIER);
 printf("SR    %8x ",(unsigned int) tmr->SR);
 printf("EGR   %8x\n",(unsigned int) tmr->EGR);
 printf("CCMR1 %8x ",(unsigned int) tmr->CCMR1);
 printf("CCMR2 %8x\n",(unsigned int) tmr->CCMR2);
 printf("CCER  %8x ",(unsigned int) tmr->CCER);
 printf("CNT   %8x\n",(unsigned int) tmr->CNT);
 printf("PSC   %8x ",(unsigned int) tmr->PSC);
 printf("ARR   %8x\n",(unsigned int) tmr->ARR);
 printf("RCR   %8x ",(unsigned int) tmr->RCR);
 printf("CCR1  %8x\n",(unsigned int) tmr->CCR1);
 printf("CCR2  %8x ",(unsigned int) tmr->CCR2);
 printf("CCR3  %8x\n",(unsigned int) tmr->CCR3);
 printf("CCR4  %8x ",(unsigned int) tmr->CCR4);
 printf("BDTR  %8x\n",(unsigned int) tmr->BDTR);
 printf("DCR   %8x ",(unsigned int) tmr->DCR);
 printf("OR    %8x\n",(unsigned int) tmr->OR);
 flushBuf();
}

void extiInfo(void)
{
 printf("EXTI %x\n",(unsigned int) EXTI);
 int i;
 printf("      ");
 for (i = 0; i <= 22; i++)
  printf(" %2d", i);

 printf("\nIMR   ");
 int val = EXTI->IMR;
 for (i = 0; i <= 22; i++)
  printf(" %2d", (val >> i) & 0x1);

 printf("\nEMR   ");
 val = EXTI->EMR;
 for (i = 0; i <= 22; i++)
  printf(" %2d", (val >> i) & 0x1);

 printf("\nRTSR  ");
 val = EXTI->RTSR;
 for (i = 0; i <= 22; i++)
  printf(" %2d", (val >> i) & 0x1);

 printf("\nFTSR  ");
 val = EXTI->FTSR;
 for (i = 0; i <= 22; i++)
  printf(" %2d", (val >> i) & 0x1);

 printf("\nSWIER ");
 val = EXTI->SWIER;
 for (i = 0; i <= 22; i++)
  printf(" %2d", (val >> i) & 0x1);

 printf("\nPR    ");
 val = EXTI->PR;
 for (i = 0; i <= 22; i++)
  printf(" %2d", (val >> i) & 0x1);

 printf("\nSYSCFG %x\n",(unsigned int) SYSCFG);
 printf("      ");
 for (i = 0; i < 16; i++)
  printf(" %2d", i);

 printf("\nEXTICR");
 int mask = EXTI->IMR;
 for (i = 0; i < 4; i++)
 {
  val = SYSCFG->EXTICR[i];
  int j;
  for (j = 0; j < 4; j++)
  {
   printf("  %c", (mask & 1) ? 'a' + ((val >> (4 * j)) & 0xf) : ' ');
   mask >>= 1;
  }
 }
 printf("\n");
 flushBuf();
}

void usartInfo(USART_TypeDef *usart, const char *str)
{
 printf("usart %x %s\n",(unsigned int) usart, str);
 printf("SR   %8x ",(unsigned int) usart->SR);
 printf("DR   %8x\n",(unsigned int) usart->DR);
 printf("BRR  %8x ",(unsigned int) usart->BRR);
 printf("CR1  %8x\n",(unsigned int) usart->CR1);
 printf("CR2  %8x ",(unsigned int) usart->CR2);
 printf("CR3  %8x\n",(unsigned int) usart->CR3);
 printf("GTPR %8x\n",(unsigned int) usart->GTPR);
 flushBuf();
}

void i2cInfo(I2C_TypeDef *i2c, const char *str)
{
 printf("i2c %x %s\n",(unsigned int) i2c, str);
 printf("CR1   %8x ",(unsigned int) i2c->CR1);
 printf("CR2   %8x\n",(unsigned int) i2c->CR2);
 printf("OAR1  %8x ",(unsigned int) i2c->OAR1);
 printf("OAR2  %8x\n",(unsigned int) i2c->OAR2);
 printf("SR1   %8x ",(unsigned int) i2c->SR1);
 printf("SR2   %8x\n",(unsigned int) i2c->SR2);
 printf("DR    %8x ",(unsigned int) i2c->DR);
 printf("CCR   %8x\n",(unsigned int) i2c->CCR);
 printf("TRISE %8x\n",(unsigned int) i2c->TRISE);
 flushBuf();
}

typedef struct
{
 uint16_t mask;
 GPIO_TypeDef *gpio;
 const char *name;
} T_PORT_INPUT, *P_PORT_INPUT;

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
 PORT_INPUT(Index1),
 PORT_INPUT(Index2),
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

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim8;
extern TIM_HandleTypeDef htim12;

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
  int count = cfgFcy;
  int pre = 1;
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
 while (1)
 {
  if ((chRdy() != 0)
  ||  (chRdy1() != 0))
   break;
  pollBufChar();
  if ((millis() - tmp) >= 10U)	/* if time elapsed */
  {
   tmp = millis();		/* save current time */
   if (flag & INPUT_TEST)
   {
    T_PORT_INPUT *p = inputDef;
    int mask = 1;
    for (unsigned int i = 0; i < sizeof(inputDef) / sizeof(T_PORT_INPUT); i++)
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
