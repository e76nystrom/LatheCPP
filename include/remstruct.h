#if !defined(REM_STRUCT)
#define REM_STRUCT

#include <stdint.h>

#if !defined(__DATA_UNION__)
#define __DATA_UNION__

typedef union uDataUnion
{
 float t_float;
 int t_int;
 unsigned int t_unsigned_int;
 int32_t t_int32_t;
 int16_t t_int16_t;
 uint16_t t_uint16_t;
 char t_char;
} T_DATA_UNION, *P_DATA_UNION;

#endif  /* __DATA_UNION__ */

void setRemVar(int parm, T_DATA_UNION val);
void getRemVar(int parm, P_DATA_UNION val);

typedef struct sRemVar
{

// spindle parameters

 int16_t spSteps;               /* 0x00 spindle motor steps */
 int16_t spMicro;               /* 0x01 spindle micro steps */
 float spMinRpm;                /* 0x02 spindle minimum rpm */
 float spMaxRpm;                /* 0x03 spindle maximum rpm */
 float spRpm;                   /* 0x04 spindle rpm */
 float spAccelTime;             /* 0x05 spindle accel time */
 float spAccel;                 /* 0x06 spindle accel rpm/sec^2 */
 float spJogMinRpm;             /* 0x07 spindle jog minimum rpm */
 float spJogMaxRpm;             /* 0x08 spindle jog maximum rpm */
 float spJogRpm;                /* 0x09 spindle jog rpm */
 float spJogAccelTime;          /* 0x0a spindle jog accel time */
 float spJogTimeInitial;        /* 0x0b spindle jog time initl */
 float spJogTimeInc;            /* 0x0c spindle jog time increment */
 float spJogTimeMax;            /* 0x0d spindle jog timemax */
 char spJogDir;                 /* 0x0e spindle direction */
 char spDirFlag;                /* 0x0f spindle invert direction */
 char spTestIndex;              /* 0x10 generate test index pulse */
 char spTestEncoder;            /* 0x11 generate enc test pulse */

// z axis parameters

 float zPitch;                  /* 0x12 z axis leadscrew pitch */
 float zRatio;                  /* 0x13 z axis ratio */
 int16_t zMicro;                /* 0x14 z axis micro steps */
 int16_t zMotor;                /* 0x15 z axis motor steps */
 float zAccelTime;              /* 0x16 z axis acceleration */
 float zAccel;                  /* 0x17 z accel rpm/sec^2 */
 float zBacklash;               /* 0x18 z axis backlash */
 int zStepFactor;               /* 0x19 z steps inch factored */
 char zDirFlag;                 /* 0x1a z invert direction */
 char zMpgFlag;                 /* 0x1b z invert mpg */

// x axis parameters

 float xPitch;                  /* 0x1c x axis leadscrew pitch */
 float xRatio;                  /* 0x1d x axis ratio */
 int16_t xMicro;                /* 0x1e x axis micro steps */
 int16_t xMotor;                /* 0x1f x axis motor steps */
 float xAccelTime;              /* 0x20 x axis acceleration */
 float xAccel;                  /* 0x21 x accel rpm/sec^2 */
 float xBacklash;               /* 0x22 x axis backlash */
 int xStepFactor;               /* 0x23 x steps inch factored */
 char xDirFlag;                 /* 0x24 x invert direction */
 char xMpgFlag;                 /* 0x25 x invert mpg */
 int xDiameter;                 /* 0x26 x diameter */

// z move parameters

 float zMoveMin;                /* 0x27 z move min speed */
 float zMoveMax;                /* 0x28 z move max speed */

// z jog parameters

 float zJogMin;                 /* 0x29 z jog min speed */
 float zJogMax;                 /* 0x2a z jog max speed */
 float zJogSpeed;               /* 0x2b z jog speed */

// x move parameters

 float xMoveMin;                /* 0x2c x move min speed */
 float xMoveMax;                /* 0x2d x move max speed */

// x jog parameters

 float xJogMin;                 /* 0x2e x jog min speed */
 float xJogMax;                 /* 0x2f x jog max speed */
 float xJogSpeed;               /* 0x30 x jog speed */

// pass information

 int16_t totalPasses;           /* 0x31 total passes */
 int16_t currentPass;           /* 0x32 current passes */
 int16_t mvStatus;              /* 0x33 movement status */

// z axis move values

 float zMoveDist;               /* 0x34 z move distance */
 float zMovePos;                /* 0x35 z move position */
 int zJogDir;                   /* 0x36 x jog direction */
 float zSetLoc;                 /* 0x37 z location to set */
 int zLoc;                      /* 0x38 z dro location */
 int zFlag;                     /* 0x39 z move flag */
 int zAbsLoc;                   /* 0x3a z absolute location */
 int zMpgInc;                   /* 0x3b z man pulse gen incr */
 int zMpgMax;                   /* 0x3c z man pulse max distance */

// x axis move values

 float xMoveDist;               /* 0x3d x move distance */
 float xMovePos;                /* 0x3e x move position */
 int xJogDir;                   /* 0x3f x jog direction */
 float xSetLoc;                 /* 0x40 x location to set */
 int xLoc;                      /* 0x41 x dro location */
 int xFlag;                     /* 0x42 x move flag */
 int xAbsLoc;                   /* 0x43 x absolute location */
 int xMpgInc;                   /* 0x44 X man pulse gen incr */
 int xMpgMax;                   /* 0x45 x man pulse max distance */

// common jog parameters

 float jogTimeInitial;          /* 0x46 jog time initial */
 float jogTimeInc;              /* 0x47 jog time increment */
 float jogTimeMax;              /* 0x48 jog time max */

// taper parameters

 float taperCycleDist;          /* 0x49 taperCycleDist */

// index pulse variables

 int indexPreScaler;            /* 0x4a index pre scaler */
 unsigned int lastIndexPeriod;  /* 0x4b last index period */
 unsigned int indexPeriod;      /* 0x4c index period */
 unsigned int revCounter;       /* 0x4d revolution counter */

// z home offset

 int zHomeOffset;               /* 0x4e z home offset */

// x home offset

 int xHomeOffset;               /* 0x4f x home offset */

// z home parameters

 float zHomeSpeed;              /* 0x50 z final homing speed */
 float zHomeDist;               /* 0x51 z max homing distance */
 float zHomeDistRev;            /* 0x52 z max rev homing distance */
 float zHomeDistBackoff;        /* 0x53 z home backoff dist */
 int zHomeDir;                  /* 0x54 z homing direction */

// x home parameters

 float xHomeSpeed;              /* 0x55 x final homing speed */
 float xHomeDist;               /* 0x56 x max homing distance */
 float xHomeDistRev;            /* 0x57 x max rev homing distance */
 float xHomeDistBackoff;        /* 0x58 x home backoff dist */
 int xHomeDir;                  /* 0x59 x homing direction */

// x home test parameters

 int xHomeLoc;                  /* 0x5a x home test location */
 int xHomeStart;                /* 0x5b x start of home signal */
 int xHomeEnd;                  /* 0x5c x end of home signal */

// z dro

 int zDroLoc;                   /* 0x5d z dro location */
 int zDroOffset;                /* 0x5e z dro to zero */
 int zDroCountInch;             /* 0x5f z dro scale */
 int zDroFactor;                /* 0x60 x dro counts inch factored */
 int zDroInvert;                /* 0x61 z dro invert */
 char zUseDro;                  /* 0x62 z use dro for position */
 int zDoneDelay;                /* 0x63 z done to read dro delay */
 int zDroFinalDist;             /* 0x64 z final approach distance */

// x dro

 int xDroLoc;                   /* 0x65 x dro location */
 int xDroOffset;                /* 0x66 x dro to zero */
 int xDroCountInch;             /* 0x67 x dro scale */
 int xDroFactor;                /* 0x68 x dro counts inch factored */
 int xDroInvert;                /* 0x69 x dro invert */
 char xUseDro;                  /* 0x6a x use dro for position */
 int xDoneDelay;                /* 0x6b x done to read dro delay */
 int xDroFinalDist;             /* 0x6c x final approach distance */

// x home or probe status

 int xHomeStatus;               /* 0x6d x home status */

// Z home or probe status

 int zHomeStatus;               /* 0x6e z home status */

// probe configuration

 float probeSpeed;              /* 0x6f probe speed */
 int probeDist;                 /* 0x70 probe test distance */
 int probeInv;                  /* 0x71 invert polarity of probe */

// configuration

 char stepperDrive;             /* 0x72 stepper driven spindle */
 char motorTest;                /* 0x73 use stepper to test motor */
 char spindleEncoder;           /* 0x74 motor with spindle enc */
 char spindleSyncBoard;         /* 0x75 spindle sync board */
 char turnSync;                 /* 0x76 sync type for turning */
 char threadSync;               /* 0x77 sync type for threading */
 char capTmrEnable;             /* 0x78 enable capture timer */
 char cfgFpga;                  /* 0x79 using fpga */
 char cfgMega;                  /* 0x7a control link to mega */
 char cfgMpg;                   /* 0x7b manual pulse generator */
 char cfgDro;                   /* 0x7c digital readout */
 char cfgLcd;                   /* 0x7d lcd display */
 int cfgFcy;                    /* 0x7e system clock speed */
 int cfgSwitch;                 /* 0x7f spindle off on switch */
 int cfgVarSpeed;               /* 0x80 spindle variable speed */

// setup

 char setupDone;                /* 0x81 setup done */

// encoder counts per revolution

 uint16_t encPerRev;            /* 0x82 spindle enc counts per rev */

// test encoder setup variables

 char encEnable;                /* 0x83 encoder enable flag */
 uint16_t encPreScaler;         /* 0x84 encoder prescaler */
 uint16_t encTimer;             /* 0x85 encoder timer counts */
 int encRunCount;               /* 0x86 encoder run count */

// test encoder status variables

 char encRun;                   /* 0x87 encoder running flag */
 int16_t encCounter;            /* 0x88 encoder count in rev */
 int32_t encRevCounter;         /* 0x89 encoder revolution counter */

// measured spindle speed

 int16_t rpm;                   /* 0x8a current measured rpm */

// fpga frequency variables

 int32_t fpgaFrequency;         /* 0x8b fpga clock frequency */
 int16_t freqMult;              /* 0x8c frequency multiplier */

// xilinx configuration register

 int16_t xCfgReg;               /* 0x8d xilinx cfg register */

// sync parameters

 uint16_t lSyncCycle;           /* 0x8e sync cycle length */
 uint16_t lSyncOutput;          /* 0x8f sync outputs per cycle */
 uint16_t lSyncPrescaler;       /* 0x90 sync prescaler */

// threading variables

 int32_t thZStart;              /* 0x91 threading z start */
 int32_t thXStart;              /* 0x92 threading x start */
 float tanThreadAngle;          /* 0x93 tan of threading angle */
 int16_t xFeed;                 /* 0x94 x feed */
 float runoutDistance;          /* 0x95 runout distance */
 float runoutDepth;             /* 0x96 runout depth */

// jog debug

 char jogDebug;                 /* 0x97 jog interrupt debug */

// motor and speed control

 int16_t pwmFreq;               /* 0x98 spindle speed pwm frequency */
 int16_t minSpeed;              /* 0x99 min speed for current range */
 int16_t maxSpeed;              /* 0x9a max speed for current range */

// current operation

 char currentOp;                /* 0x9b current operation */

// global limits and home

 char limitOverride;            /* 0x9c override limit switches */
 char commonLimits;             /* 0x9d all limit switches one pin */
 char limitsEnabled;            /* 0x9e limits enabled */
 char commonHome;               /* 0x9f all home switches one pin */

// z limits and home

 char zLimEna;                  /* 0xa0 z limit enable */
 char zLimNegInv;               /* 0xa1 z negative limit invert */
 char zLimPosInv;               /* 0xa2 z Positive limit Invert */
 char zHomeEna;                 /* 0xa3 z home enable */
 char zHomeInv;                 /* 0xa4 z home invert */

// x limits and home

 char xLimEna;                  /* 0xa5 x limit enable */
 char xLimNegInv;               /* 0xa6 x negative limit invert */
 char xLimPosInv;               /* 0xa7 x Positive limit Invert */
 char xHomeEna;                 /* 0xa8 x home enable */
 char xHomeInv;                 /* 0xa9 x home invert */

// e stop

 char eStopEna;                 /* 0xaa enable estop */
 char eStopInv;                 /* 0xab invert estop siganl */

// command pause

 char cmdPaused;                /* 0xac move commands paused */

// arc parameters

 float arcRadius;               /* 0xad arc radius */
 int arcXCenter;                /* 0xae arc x center */
 int arcZCenter;                /* 0xaf arc z center */
 int arcXStart;                 /* 0xb0 arc x start */
 int arcZStart;                 /* 0xb1 arc z start */
 int arcXEnd;                   /* 0xb2 arc x center */
 int arcZEnd;                   /* 0xb3 arc z center */
 int16_t maxParm;               /* 0xb4 maximum parameter */
} T_REM_VAR, *P_REM_VAR;

extern T_REM_VAR rVar;

#endif /* REM_STRUCT */
