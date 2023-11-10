#if !defined(REM_STRUCT)
#define REM_STRUCT

#include <stdint.h>

#if !defined(__DATA_UNION__)
#define __DATA_UNION__

#define uint_t unsigned int

typedef union uDataUnion
{
 float    t_float;
 int      t_int;
 uint_t   t_uint_t;
 int32_t  t_int32_t;
 uint32_t t_uint32_t;
 int16_t  t_int16_t;
 uint16_t t_uint16_t;
 char     t_char;
} T_DATA_UNION, *P_DATA_UNION;

#endif  /* __DATA_UNION__ */

void setRemVar(int parm, T_DATA_UNION val);
void getRemVar(int parm, P_DATA_UNION val);

typedef struct sRemVar
{

// spindle parameters

 int16_t spSteps;       /* 0x00 SP_STEPS         spindle motor steps */
 int16_t spMicro;       /* 0x01 SP_MICRO         spindle micro steps */
 float spMinRpm;        /* 0x02 SP_MIN_RPM       spindle minimum rpm */
 float spMaxRpm;        /* 0x03 SP_MAX_RPM       spindle maximum rpm */
 float spRpm;           /* 0x04 SP_RPM           spindle rpm */
 float spAccelTime;     /* 0x05 SP_ACCEL_TIME    spindle accel time */
 float spAccel;         /* 0x06 SP_ACCEL         spindle accel rpm/sec^2 */
 float spJogMinRpm;     /* 0x07 SP_JOG_MIN_RPM   spindle jog minimum rpm */
 float spJogMaxRpm;     /* 0x08 SP_JOG_MAX_RPM   spindle jog maximum rpm */
 float spJogRpm;        /* 0x09 SP_JOG_RPM       spindle jog rpm */
 float spJogAccelTime;  /* 0x0a SP_JOG_ACCEL_TIME spindle jog accel time */
 float spJogTimeInitial;/* 0x0b SP_JOG_TIME_INITIAL spindle jog time initl */
 float spJogTimeInc;    /* 0x0c SP_JOG_TIME_INC  spindle jog time increment */
 float spJogTimeMax;    /* 0x0d SP_JOG_TIME_MAX  spindle jog timemax */
 char spJogDir;         /* 0x0e SP_JOG_DIR       spindle direction */
 char spDirFlag;        /* 0x0f SP_DIR_FLAG      spindle invert direction */
 char spTestIndex;      /* 0x10 SP_TEST_INDEX    generate test index pulse */
 char spTestEncoder;    /* 0x11 SP_TEST_ENCODER  generate enc test pulse */

// z axis parameters

 float zPitch;          /* 0x12 Z_PITCH          z axis leadscrew pitch */
 float zRatio;          /* 0x13 Z_RATIO          z axis ratio */
 int16_t zMicro;        /* 0x14 Z_MICRO          z axis micro steps */
 int16_t zMotor;        /* 0x15 Z_MOTOR          z axis motor steps */
 float zAccelTime;      /* 0x16 Z_ACCEL_TIME     z axis acceleration */
 float zAccel;          /* 0x17 Z_ACCEL          z accel rpm/sec^2 */
 float zBacklash;       /* 0x18 Z_BACKLASH       z axis backlash */
 int zStepFactor;       /* 0x19 Z_STEP_FACTOR    z steps inch factored */
 char zDirFlag;         /* 0x1a Z_DIR_FLAG       z invert direction */
 char zMpgFlag;         /* 0x1b Z_MPG_FLAG       z invert mpg */

// x axis parameters

 float xPitch;          /* 0x1c X_PITCH          x axis leadscrew pitch */
 float xRatio;          /* 0x1d X_RATIO          x axis ratio */
 int16_t xMicro;        /* 0x1e X_MICRO          x axis micro steps */
 int16_t xMotor;        /* 0x1f X_MOTOR          x axis motor steps */
 float xAccelTime;      /* 0x20 X_ACCEL_TIME     x axis acceleration */
 float xAccel;          /* 0x21 X_ACCEL          x accel rpm/sec^2 */
 float xBacklash;       /* 0x22 X_BACKLASH       x axis backlash */
 int xStepFactor;       /* 0x23 X_STEP_FACTOR    x steps inch factored */
 char xDirFlag;         /* 0x24 X_DIR_FLAG       x invert direction */
 char xMpgFlag;         /* 0x25 X_MPG_FLAG       x invert mpg */
 int xDiameter;         /* 0x26 X_DIAMETER       x diameter */

// z move parameters

 float zMoveMin;        /* 0x27 Z_MOVE_MIN       z move min speed */
 float zMoveMax;        /* 0x28 Z_MOVE_MAX       z move max speed */

// z jog parameters

 float zJogMin;         /* 0x29 Z_JOG_MIN        z jog min speed */
 float zJogMax;         /* 0x2a Z_JOG_MAX        z jog max speed */
 float zJogSpeed;       /* 0x2b Z_JOG_SPEED      z jog speed */

// x move parameters

 float xMoveMin;        /* 0x2c X_MOVE_MIN       x move min speed */
 float xMoveMax;        /* 0x2d X_MOVE_MAX       x move max speed */

// x jog parameters

 float xJogMin;         /* 0x2e X_JOG_MIN        x jog min speed */
 float xJogMax;         /* 0x2f X_JOG_MAX        x jog max speed */
 float xJogSpeed;       /* 0x30 X_JOG_SPEED      x jog speed */

// pass information

 int16_t totalPasses;   /* 0x31 TOTAL_PASSES     total passes */
 int16_t currentPass;   /* 0x32 CURRENT_PASS     current passes */
 int16_t mvStatus;      /* 0x33 MV_STATUS        movement status */

// z axis move values

 float zMoveDist;       /* 0x34 Z_MOVE_DIST      z move distance */
 float zMovePos;        /* 0x35 Z_MOVE_POS       z move position */
 int zJogDir;           /* 0x36 Z_JOG_DIR        x jog direction */
 float zSetLoc;         /* 0x37 Z_SET_LOC        z location to set */
 int zLoc;              /* 0x38 Z_LOC            z dro location */
 int zFlag;             /* 0x39 Z_FLAG           z move flag */
 int zAbsLoc;           /* 0x3a Z_ABS_LOC        z absolute location */
 int zMpgInc;           /* 0x3b Z_MPG_INC        z man pulse gen incr */
 int zMpgMax;           /* 0x3c Z_MPG_MAX        z man pulse max distance */

// x axis move values

 float xMoveDist;       /* 0x3d X_MOVE_DIST      x move distance */
 float xMovePos;        /* 0x3e X_MOVE_POS       x move position */
 int xJogDir;           /* 0x3f X_JOG_DIR        x jog direction */
 float xSetLoc;         /* 0x40 X_SET_LOC        x location to set */
 int xLoc;              /* 0x41 X_LOC            x dro location */
 int xFlag;             /* 0x42 X_FLAG           x move flag */
 int xAbsLoc;           /* 0x43 X_ABS_LOC        x absolute location */
 int xMpgInc;           /* 0x44 X_MPG_INC        X man pulse gen incr */
 int xMpgMax;           /* 0x45 X_MPG_MAX        x man pulse max distance */

// common jog parameters

 float jogTimeInitial;  /* 0x46 JOG_TIME_INITIAL jog time initial */
 float jogTimeInc;      /* 0x47 JOG_TIME_INC     jog time increment */
 float jogTimeMax;      /* 0x48 JOG_TIME_MAX     jog time max */

// taper parameters

 float taperCycleDist;  /* 0x49 TAPER_CYCLE_DIST taperCycleDist */

// index pulse variables

 int indexPreScaler;    /* 0x4a INDEX_PRE_SCALER index pre scaler */
 uint_t lastIndexPeriod;/* 0x4b LAST_INDEX_PERIOD last index period */
 uint_t indexPeriod;    /* 0x4c INDEX_PERIOD     index period */
 uint_t revCounter;     /* 0x4d REV_COUNTER      revolution counter */

// z home offset

 int zHomeOffset;       /* 0x4e Z_HOME_OFFSET    z home offset */

// x home offset

 int xHomeOffset;       /* 0x4f X_HOME_OFFSET    x home offset */

// z home parameters

 float zHomeSpeed;      /* 0x50 Z_HOME_SPEED     z final homing speed */
 float zHomeDist;       /* 0x51 Z_HOME_DIST      z max homing distance */
 float zHomeDistRev;    /* 0x52 Z_HOME_DIST_REV  z max rev homing distance */
 float zHomeDistBackoff;/* 0x53 Z_HOME_DIST_BACKOFF z home backoff dist */
 int zHomeDir;          /* 0x54 Z_HOME_DIR       z homing direction */

// x home parameters

 float xHomeSpeed;      /* 0x55 X_HOME_SPEED     x final homing speed */
 float xHomeDist;       /* 0x56 X_HOME_DIST      x max homing distance */
 float xHomeDistRev;    /* 0x57 X_HOME_DIST_REV  x max rev homing distance */
 float xHomeDistBackoff;/* 0x58 X_HOME_DIST_BACKOFF x home backoff dist */
 int xHomeDir;          /* 0x59 X_HOME_DIR       x homing direction */

// x home test parameters

 int xHomeLoc;          /* 0x5a X_HOME_LOC       x home test location */
 int xHomeStart;        /* 0x5b X_HOME_START     x start of home signal */
 int xHomeEnd;          /* 0x5c X_HOME_END       x end of home signal */

// z dro

 int zDroLoc;           /* 0x5d Z_DRO_LOC        z dro location */
 int zDroOffset;        /* 0x5e Z_DRO_OFFSET     z dro to zero */
 int zDroCountInch;     /* 0x5f Z_DRO_COUNT_INCH z dro scale */
 int zDroFactor;        /* 0x60 Z_DRO_FACTOR     x dro counts inch factored */
 int zDroInvert;        /* 0x61 Z_DRO_INVERT     z dro invert */
 char zUseDro;          /* 0x62 Z_USE_DRO        z use dro for position */
 int zDoneDelay;        /* 0x63 Z_DONE_DELAY     z done to read dro delay */
 int zDroFinalDist;     /* 0x64 Z_DRO_FINAL_DIST z final approach distance */

// x dro

 int xDroLoc;           /* 0x65 X_DRO_LOC        x dro location */
 int xDroOffset;        /* 0x66 X_DRO_OFFSET     x dro to zero */
 int xDroCountInch;     /* 0x67 X_DRO_COUNT_INCH x dro scale */
 int xDroFactor;        /* 0x68 X_DRO_FACTOR     x dro counts inch factored */
 int xDroInvert;        /* 0x69 X_DRO_INVERT     x dro invert */
 char xUseDro;          /* 0x6a X_USE_DRO        x use dro for position */
 int xDoneDelay;        /* 0x6b X_DONE_DELAY     x done to read dro delay */
 int xDroFinalDist;     /* 0x6c X_DRO_FINAL_DIST x final approach distance */

// x home or probe status

 int xHomeStatus;       /* 0x6d X_HOME_STATUS    x home status */

// Z home or probe status

 int zHomeStatus;       /* 0x6e Z_HOME_STATUS    z home status */

// probe configuration

 float probeSpeed;      /* 0x6f PROBE_SPEED      probe speed */
 int probeDist;         /* 0x70 PROBE_DIST       probe test distance */
 int probeInv;          /* 0x71 PROBE_INV        invert polarity of probe */

// configuration

 char stepperDrive;     /* 0x72 STEPPER_DRIVE    stepper driven spindle */
 char motorTest;        /* 0x73 MOTOR_TEST       use stepper to test motor */
 char spindleEncoder;   /* 0x74 SPINDLE_ENCODER  motor with spindle enc */
 char spindleSyncBoard; /* 0x75 SPINDLE_SYNC_BOARD spindle sync board */
 char spindleInternalSync;/* 0x76 SPINDLE_INTERNAL_SYNC spindle internal sync */
 char turnSync;         /* 0x77 TURN_SYNC        sync type for turning */
 char threadSync;       /* 0x78 THREAD_SYNC      sync type for threading */
 char capTmrEnable;     /* 0x79 CAP_TMR_ENABLE   enable capture timer */
 char cfgFpga;          /* 0x7a CFG_FPGA         using fpga */
 char cfgMega;          /* 0x7b CFG_MEGA         control link to mega */
 char cfgMpg;           /* 0x7c CFG_MPG          manual pulse generator */
 char cfgDro;           /* 0x7d CFG_DRO          digital readout */
 char cfgLcd;           /* 0x7e CFG_LCD          lcd display */
 uint_t cfgFcy;         /* 0x7f CFG_FCY          system clock speed */
 int cfgSwitch;         /* 0x80 CFG_SWITCH       spindle off on switch */
 int cfgVarSpeed;       /* 0x81 CFG_VAR_SPEED    spindle variable speed */

// setup

 char setupDone;        /* 0x82 SETUP_DONE       setup done */

// encoder counts per revolution

 uint16_t encPerRev;    /* 0x83 ENC_PER_REV      spindle enc counts per rev */

// test encoder setup variables

 char encEnable;        /* 0x84 ENC_ENABLE       encoder enable flag */
 uint16_t encPreScaler; /* 0x85 ENC_PRE_SCALER   encoder prescaler */
 uint16_t encTimer;     /* 0x86 ENC_TIMER        encoder timer counts */
 int encRunCount;       /* 0x87 ENC_RUN_COUNT    encoder run count */

// test encoder status variables

 char encRun;           /* 0x88 ENC_RUN          encoder running flag */
 int16_t encCounter;    /* 0x89 ENC_COUNTER      encoder count in rev */
 int32_t encRevCounter; /* 0x8a ENC_REV_COUNTER  encoder revolution counter */

// measured spindle speed

 int16_t rpm;           /* 0x8b RPM              current measured rpm */

// fpga frequency variables

 int32_t fpgaFrequency; /* 0x8c FPGA_FREQUENCY   fpga clock frequency */
 int16_t freqMult;      /* 0x8d FREQ_MULT        frequency multiplier */

// xilinx configuration register

 int16_t xCfgReg;       /* 0x8e X_CFG_REG        xilinx cfg register */

// z sync parameters

 uint16_t lSyncCycle;   /* 0x8f L_SYNC_CYCLE     sync cycle length */
 uint16_t lSyncOutput;  /* 0x90 L_SYNC_OUTPUT    sync outputs per cycle */
 uint16_t lSyncInPrescaler;/* 0x91 L_SYNC_IN_PRESCALER input sync prescaler */
 uint16_t lSyncOutPrescaler;/* 0x92 L_SYNC_OUT_PRESCALER output sync prescaler */

// x sync parameters

 uint16_t lXSyncCycle;  /* 0x93 L_X_SYNC_CYCLE   sync cycle length */
 uint16_t lXSyncOutput; /* 0x94 L_X_SYNC_OUTPUT  sync outputs per cycle */
 uint16_t lXSyncInPrescaler;/* 0x95 L_X_SYNC_IN_PRESCALER input sync prescaler */
 uint16_t lXSyncOutPrescaler;/* 0x96 L_X_SYNC_OUT_PRESCALER output sync prescaler */

// threading variables

 int32_t thZStart;      /* 0x97 TH_Z_START       threading z start */
 int32_t thXStart;      /* 0x98 TH_X_START       threading x start */
 float tanThreadAngle;  /* 0x99 TAN_THREAD_ANGLE tan of threading angle */
 int32_t xFeed;         /* 0x9a X_FEED           x feed */
 float runoutDistance;  /* 0x9b RUNOUT_DISTANCE  runout distance */
 float runoutDepth;     /* 0x9c RUNOUT_DEPTH     runout depth */

// jog debug

 char jogDebug;         /* 0x9d JOG_DEBUG        jog interrupt debug */

// motor and speed control

 uint_t pwmFreq;        /* 0x9e PWM_FREQ         spindle speed pwm frequency */
 int16_t minSpeed;      /* 0x9f MIN_SPEED        min speed for current range */
 int16_t maxSpeed;      /* 0xa0 MAX_SPEED        max speed for current range */

// current operation

 char currentOp;        /* 0xa1 CURRENT_OP       current operation */

// global limits and home

 char limitOverride;    /* 0xa2 LIMIT_OVERRIDE   override limit switches */
 char commonLimits;     /* 0xa3 COMMON_LIMITS    all limit switches one pin */
 char limitsEnabled;    /* 0xa4 LIMITS_ENABLED   limits enabled */
 char commonHome;       /* 0xa5 COMMON_HOME      all home switches one pin */

// z limits and home

 char zLimEna;          /* 0xa6 Z_LIM_ENA        z limit enable */
 char zLimNegInv;       /* 0xa7 Z_LIM_NEG_INV    z negative limit invert */
 char zLimPosInv;       /* 0xa8 Z_LIM_POS_INV    z Positive limit Invert */
 char zHomeEna;         /* 0xa9 Z_HOME_ENA       z home enable */
 char zHomeInv;         /* 0xaa Z_HOME_INV       z home invert */

// x limits and home

 char xLimEna;          /* 0xab X_LIM_ENA        x limit enable */
 char xLimNegInv;       /* 0xac X_LIM_NEG_INV    x negative limit invert */
 char xLimPosInv;       /* 0xad X_LIM_POS_INV    x Positive limit Invert */
 char xHomeEna;         /* 0xae X_HOME_ENA       x home enable */
 char xHomeInv;         /* 0xaf X_HOME_INV       x home invert */

// e stop

 char eStopEna;         /* 0xb0 E_STOP_ENA       enable estop */
 char eStopInv;         /* 0xb1 E_STOP_INV       invert estop signal */

// command pause

 char cmdPaused;        /* 0xb2 CMD_PAUSED       move commands paused */

// arc parameters

 float arcRadius;       /* 0xb3 ARC_RADIUS       arc radius */
 int arcXCenter;        /* 0xb4 ARC_X_CENTER     arc x center */
 int arcZCenter;        /* 0xb5 ARC_Z_CENTER     arc z center */
 int arcXStart;         /* 0xb6 ARC_X_START      arc x start */
 int arcZStart;         /* 0xb7 ARC_Z_START      arc z start */
 int arcXEnd;           /* 0xb8 ARC_X_END        arc x center */
 int arcZEnd;           /* 0xb9 ARC_Z_END        arc z center */
 char megaVfd;          /* 0xba MEGA_VFD         mega vfd speed mode */
 char megaSim;          /* 0xbb MEGA_SIM         mega encoder lines */
 char usbEna;           /* 0xbc USB_ENA          enable usb */
 int16_t maxParm;       /* 0xbd MAX_PARM         maximum parameter */
} T_REM_VAR, *P_REM_VAR;

extern unsigned char remSize[];
extern T_REM_VAR rVar;

#endif /* REM_STRUCT */
