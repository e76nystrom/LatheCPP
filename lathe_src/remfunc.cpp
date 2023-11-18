#include <stdint.h>
#define NO_REM_MACROS
#include "remParm.h"
#include "remStruct.h"

T_REM_VAR rVar;

#define FLT (0x80)
#define SIZE_MASK (0x7)

unsigned char remSize[] =
{

// spindle parameters

 sizeof(rVar.spSteps),                  /* 0x00 spindle motor steps */
 sizeof(rVar.spMicro),                  /* 0x01 spindle micro steps */
 sizeof(rVar.spMinRpm) | FLT,           /* 0x02 spindle minimum rpm */
 sizeof(rVar.spMaxRpm) | FLT,           /* 0x03 spindle maximum rpm */
 sizeof(rVar.spRpm) | FLT,              /* 0x04 spindle rpm */
 sizeof(rVar.spAccelTime) | FLT,        /* 0x05 spindle accel time */
 sizeof(rVar.spAccel) | FLT,            /* 0x06 spindle accel rpm/sec^2 */
 sizeof(rVar.spJogMinRpm) | FLT,        /* 0x07 spindle jog minimum rpm */
 sizeof(rVar.spJogMaxRpm) | FLT,        /* 0x08 spindle jog maximum rpm */
 sizeof(rVar.spJogRpm) | FLT,           /* 0x09 spindle jog rpm */
 sizeof(rVar.spJogAccelTime) | FLT,     /* 0x0a spindle jog accel time */
 sizeof(rVar.spJogTimeInitial) | FLT,   /* 0x0b spindle jog time initl */
 sizeof(rVar.spJogTimeInc) | FLT,       /* 0x0c spindle jog time increment */
 sizeof(rVar.spJogTimeMax) | FLT,       /* 0x0d spindle jog timemax */
 sizeof(rVar.spJogDir),                 /* 0x0e spindle direction */
 sizeof(rVar.spDirFlag),                /* 0x0f spindle invert direction */
 sizeof(rVar.spTestIndex),              /* 0x10 generate test index pulse */
 sizeof(rVar.spTestEncoder),            /* 0x11 generate enc test pulse */

// z axis parameters

 sizeof(rVar.zPitch) | FLT,             /* 0x12 z axis leadscrew pitch */
 sizeof(rVar.zRatio) | FLT,             /* 0x13 z axis ratio */
 sizeof(rVar.zMicro),                   /* 0x14 z axis micro steps */
 sizeof(rVar.zMotor),                   /* 0x15 z axis motor steps */
 sizeof(rVar.zAccelTime) | FLT,         /* 0x16 z axis acceleration */
 sizeof(rVar.zAccel) | FLT,             /* 0x17 z accel rpm/sec^2 */
 sizeof(rVar.zBacklash) | FLT,          /* 0x18 z axis backlash */
 sizeof(rVar.zStepFactor),              /* 0x19 z steps inch factored */
 sizeof(rVar.zDirFlag),                 /* 0x1a z invert direction */
 sizeof(rVar.zMpgFlag),                 /* 0x1b z invert mpg */

// x axis parameters

 sizeof(rVar.xPitch) | FLT,             /* 0x1c x axis leadscrew pitch */
 sizeof(rVar.xRatio) | FLT,             /* 0x1d x axis ratio */
 sizeof(rVar.xMicro),                   /* 0x1e x axis micro steps */
 sizeof(rVar.xMotor),                   /* 0x1f x axis motor steps */
 sizeof(rVar.xAccelTime) | FLT,         /* 0x20 x axis acceleration */
 sizeof(rVar.xAccel) | FLT,             /* 0x21 x accel rpm/sec^2 */
 sizeof(rVar.xBacklash) | FLT,          /* 0x22 x axis backlash */
 sizeof(rVar.xStepFactor),              /* 0x23 x steps inch factored */
 sizeof(rVar.xDirFlag),                 /* 0x24 x invert direction */
 sizeof(rVar.xMpgFlag),                 /* 0x25 x invert mpg */
 sizeof(rVar.xDiameter),                /* 0x26 x diameter */

// z move parameters

 sizeof(rVar.zMoveMin) | FLT,           /* 0x27 z move min speed */
 sizeof(rVar.zMoveMax) | FLT,           /* 0x28 z move max speed */

// z jog parameters

 sizeof(rVar.zJogMin) | FLT,            /* 0x29 z jog min speed */
 sizeof(rVar.zJogMax) | FLT,            /* 0x2a z jog max speed */
 sizeof(rVar.zJogSpeed) | FLT,          /* 0x2b z jog speed */

// x move parameters

 sizeof(rVar.xMoveMin) | FLT,           /* 0x2c x move min speed */
 sizeof(rVar.xMoveMax) | FLT,           /* 0x2d x move max speed */

// x jog parameters

 sizeof(rVar.xJogMin) | FLT,            /* 0x2e x jog min speed */
 sizeof(rVar.xJogMax) | FLT,            /* 0x2f x jog max speed */
 sizeof(rVar.xJogSpeed) | FLT,          /* 0x30 x jog speed */

// pass information

 sizeof(rVar.totalPasses),              /* 0x31 total passes */
 sizeof(rVar.currentPass),              /* 0x32 current passes */
 sizeof(rVar.mvStatus),                 /* 0x33 movement status */

// z axis move values

 sizeof(rVar.zMoveDist) | FLT,          /* 0x34 z move distance */
 sizeof(rVar.zMovePos) | FLT,           /* 0x35 z move position */
 sizeof(rVar.zJogDir),                  /* 0x36 x jog direction */
 sizeof(rVar.zSetLoc) | FLT,            /* 0x37 z location to set */
 sizeof(rVar.zLoc),                     /* 0x38 z dro location */
 sizeof(rVar.zFlag),                    /* 0x39 z move flag */
 sizeof(rVar.zAbsLoc),                  /* 0x3a z absolute location */
 sizeof(rVar.zMpgInc),                  /* 0x3b z man pulse gen incr */
 sizeof(rVar.zMpgMax),                  /* 0x3c z man pulse max distance */

// x axis move values

 sizeof(rVar.xMoveDist) | FLT,          /* 0x3d x move distance */
 sizeof(rVar.xMovePos) | FLT,           /* 0x3e x move position */
 sizeof(rVar.xJogDir),                  /* 0x3f x jog direction */
 sizeof(rVar.xSetLoc) | FLT,            /* 0x40 x location to set */
 sizeof(rVar.xLoc),                     /* 0x41 x dro location */
 sizeof(rVar.xFlag),                    /* 0x42 x move flag */
 sizeof(rVar.xAbsLoc),                  /* 0x43 x absolute location */
 sizeof(rVar.xMpgInc),                  /* 0x44 X man pulse gen incr */
 sizeof(rVar.xMpgMax),                  /* 0x45 x man pulse max distance */

// common jog parameters

 sizeof(rVar.jogTimeInitial) | FLT,     /* 0x46 jog time initial */
 sizeof(rVar.jogTimeInc) | FLT,         /* 0x47 jog time increment */
 sizeof(rVar.jogTimeMax) | FLT,         /* 0x48 jog time max */

// taper parameters

 sizeof(rVar.taperCycleDist) | FLT,     /* 0x49 taperCycleDist */

// index pulse variables

 sizeof(rVar.indexPreScaler),           /* 0x4a index pre scaler */
 sizeof(rVar.lastIndexPeriod),          /* 0x4b last index period */
 sizeof(rVar.indexPeriod),              /* 0x4c index period */
 sizeof(rVar.revCounter),               /* 0x4d revolution counter */

// z home offset

 sizeof(rVar.zHomeOffset),              /* 0x4e z home offset */

// x home offset

 sizeof(rVar.xHomeOffset),              /* 0x4f x home offset */

// z home parameters

 sizeof(rVar.zHomeSpeed) | FLT,         /* 0x50 z final homing speed */
 sizeof(rVar.zHomeDist) | FLT,          /* 0x51 z max homing distance */
 sizeof(rVar.zHomeDistRev) | FLT,       /* 0x52 z max rev homing distance */
 sizeof(rVar.zHomeDistBackoff) | FLT,   /* 0x53 z home backoff dist */
 sizeof(rVar.zHomeDir),                 /* 0x54 z homing direction */

// x home parameters

 sizeof(rVar.xHomeSpeed) | FLT,         /* 0x55 x final homing speed */
 sizeof(rVar.xHomeDist) | FLT,          /* 0x56 x max homing distance */
 sizeof(rVar.xHomeDistRev) | FLT,       /* 0x57 x max rev homing distance */
 sizeof(rVar.xHomeDistBackoff) | FLT,   /* 0x58 x home backoff dist */
 sizeof(rVar.xHomeDir),                 /* 0x59 x homing direction */

// x home test parameters

 sizeof(rVar.xHomeLoc),                 /* 0x5a x home test location */
 sizeof(rVar.xHomeStart),               /* 0x5b x start of home signal */
 sizeof(rVar.xHomeEnd),                 /* 0x5c x end of home signal */

// z dro

 sizeof(rVar.zDroLoc),                  /* 0x5d z dro location */
 sizeof(rVar.zDroOffset),               /* 0x5e z dro to zero */
 sizeof(rVar.zDroCountInch),            /* 0x5f z dro scale */
 sizeof(rVar.zDroFactor),               /* 0x60 x dro counts inch factored */
 sizeof(rVar.zDroInvert),               /* 0x61 z dro invert */
 sizeof(rVar.zUseDro),                  /* 0x62 z use dro for position */
 sizeof(rVar.zDoneDelay),               /* 0x63 z done to read dro delay */
 sizeof(rVar.zDroFinalDist),            /* 0x64 z final approach distance */

// x dro

 sizeof(rVar.xDroLoc),                  /* 0x65 x dro location */
 sizeof(rVar.xDroOffset),               /* 0x66 x dro to zero */
 sizeof(rVar.xDroCountInch),            /* 0x67 x dro scale */
 sizeof(rVar.xDroFactor),               /* 0x68 x dro counts inch factored */
 sizeof(rVar.xDroInvert),               /* 0x69 x dro invert */
 sizeof(rVar.xUseDro),                  /* 0x6a x use dro for position */
 sizeof(rVar.xDoneDelay),               /* 0x6b x done to read dro delay */
 sizeof(rVar.xDroFinalDist),            /* 0x6c x final approach distance */

// x home or probe status

 sizeof(rVar.xHomeStatus),              /* 0x6d x home status */

// Z home or probe status

 sizeof(rVar.zHomeStatus),              /* 0x6e z home status */

// probe configuration

 sizeof(rVar.probeSpeed) | FLT,         /* 0x6f probe speed */
 sizeof(rVar.probeDist),                /* 0x70 probe test distance */
 sizeof(rVar.probeInv),                 /* 0x71 invert polarity of probe */

// configuration

 sizeof(rVar.stepperDrive),             /* 0x72 stepper driven spindle */
 sizeof(rVar.motorTest),                /* 0x73 use stepper to test motor */
 sizeof(rVar.spindleEncoder),           /* 0x74 motor with spindle enc */
 sizeof(rVar.spindleSyncBoard),         /* 0x75 spindle sync board */
 sizeof(rVar.spindleInternalSync),      /* 0x76 spindle internal sync */
 sizeof(rVar.turnSync),                 /* 0x77 sync type for turning */
 sizeof(rVar.threadSync),               /* 0x78 sync type for threading */
 sizeof(rVar.capTmrEnable),             /* 0x79 enable capture timer */
 sizeof(rVar.cfgFpga),                  /* 0x7a using fpga */
 sizeof(rVar.cfgMega),                  /* 0x7b control link to mega */
 sizeof(rVar.cfgMpg),                   /* 0x7c manual pulse generator */
 sizeof(rVar.cfgDro),                   /* 0x7d digital readout */
 sizeof(rVar.cfgLcd),                   /* 0x7e lcd display */
 sizeof(rVar.cfgFcy),                   /* 0x7f system clock speed */
 sizeof(rVar.cfgSwitch),                /* 0x80 spindle off on switch */
 sizeof(rVar.cfgVarSpeed),              /* 0x81 spindle variable speed */

// setup

 sizeof(rVar.setupDone),                /* 0x82 setup done */

// encoder counts per revolution

 sizeof(rVar.encPerRev),                /* 0x83 spindle enc counts per rev */

// test encoder setup variables

 sizeof(rVar.encEnable),                /* 0x84 encoder enable flag */
 sizeof(rVar.encPreScaler),             /* 0x85 encoder prescaler */
 sizeof(rVar.encTimer),                 /* 0x86 encoder timer counts */
 sizeof(rVar.encRunCount),              /* 0x87 encoder run count */

// test encoder status variables

 sizeof(rVar.encRun),                   /* 0x88 encoder running flag */
 sizeof(rVar.encCounter),               /* 0x89 encoder count in rev */
 sizeof(rVar.encRevCounter),            /* 0x8a encoder revolution counter */

// measured spindle speed

 sizeof(rVar.rpm),                      /* 0x8b current measured rpm */

// fpga frequency variables

 sizeof(rVar.fpgaFrequency),            /* 0x8c fpga clock frequency */
 sizeof(rVar.freqMult),                 /* 0x8d frequency multiplier */

// xilinx configuration register

 sizeof(rVar.xCfgReg),                  /* 0x8e xilinx cfg register */

// z sync parameters

 sizeof(rVar.lSyncCycle),               /* 0x8f sync cycle length */
 sizeof(rVar.lSyncOutput),              /* 0x90 sync outputs per cycle */
 sizeof(rVar.lSyncInPrescaler),         /* 0x91 input sync prescaler */
 sizeof(rVar.lSyncOutPrescaler),        /* 0x92 output sync prescaler */

// x sync parameters

 sizeof(rVar.lXSyncCycle),              /* 0x93 sync cycle length */
 sizeof(rVar.lXSyncOutput),             /* 0x94 sync outputs per cycle */
 sizeof(rVar.lXSyncInPrescaler),        /* 0x95 input sync prescaler */
 sizeof(rVar.lXSyncOutPrescaler),       /* 0x96 output sync prescaler */

// threading variables

 sizeof(rVar.thZStart),                 /* 0x97 threading z start */
 sizeof(rVar.thXStart),                 /* 0x98 threading x start */
 sizeof(rVar.tanThreadAngle) | FLT,     /* 0x99 tan of threading angle */
 sizeof(rVar.xFeed),                    /* 0x9a x feed */
 sizeof(rVar.runoutDistance) | FLT,     /* 0x9b runout distance */
 sizeof(rVar.runoutDepth) | FLT,        /* 0x9c runout depth */

// jog debug

 sizeof(rVar.jogDebug),                 /* 0x9d jog interrupt debug */

// motor and speed control

 sizeof(rVar.pwmFreq),                  /* 0x9e spindle speed pwm frequency */
 sizeof(rVar.minSpeed),                 /* 0x9f min speed for current range */
 sizeof(rVar.maxSpeed),                 /* 0xa0 max speed for current range */

// current operation

 sizeof(rVar.currentOp),                /* 0xa1 current operation */

// global limits and home

 sizeof(rVar.limitOverride),            /* 0xa2 override limit switches */
 sizeof(rVar.commonLimits),             /* 0xa3 all limit switches one pin */
 sizeof(rVar.limitsEnabled),            /* 0xa4 limits enabled */
 sizeof(rVar.commonHome),               /* 0xa5 all home switches one pin */

// z limits and home

 sizeof(rVar.zLimEna),                  /* 0xa6 z limit enable */
 sizeof(rVar.zLimNegInv),               /* 0xa7 z negative limit invert */
 sizeof(rVar.zLimPosInv),               /* 0xa8 z Positive limit Invert */
 sizeof(rVar.zHomeEna),                 /* 0xa9 z home enable */
 sizeof(rVar.zHomeInv),                 /* 0xaa z home invert */

// x limits and home

 sizeof(rVar.xLimEna),                  /* 0xab x limit enable */
 sizeof(rVar.xLimNegInv),               /* 0xac x negative limit invert */
 sizeof(rVar.xLimPosInv),               /* 0xad x Positive limit Invert */
 sizeof(rVar.xHomeEna),                 /* 0xae x home enable */
 sizeof(rVar.xHomeInv),                 /* 0xaf x home invert */

// e stop

 sizeof(rVar.eStopEna),                 /* 0xb0 enable estop */
 sizeof(rVar.eStopInv),                 /* 0xb1 invert estop signal */

// command pause

 sizeof(rVar.cmdPaused),                /* 0xb2 move commands paused */

// arc parameters

 sizeof(rVar.arcRadius) | FLT,          /* 0xb3 arc radius */
 sizeof(rVar.arcXCenter),               /* 0xb4 arc x center */
 sizeof(rVar.arcZCenter),               /* 0xb5 arc z center */
 sizeof(rVar.arcXStart),                /* 0xb6 arc x start */
 sizeof(rVar.arcZStart),                /* 0xb7 arc z start */
 sizeof(rVar.arcXEnd),                  /* 0xb8 arc x center */
 sizeof(rVar.arcZEnd),                  /* 0xb9 arc z center */
 sizeof(rVar.megaVfd),                  /* 0xba mega vfd speed mode */
 sizeof(rVar.megaSim),                  /* 0xbb mega encoder lines */
 sizeof(rVar.usbEna),                   /* 0xbc enable usb */
 sizeof(rVar.maxParm),                  /* 0xbd maximum parameter */
};

void setRemVar(const int parm, const T_DATA_UNION val)
{
 switch(parm)
 {
 default:
  break;

 case SP_STEPS:                  /*  0 0x00 spindle motor steps */
  rVar.spSteps = val.t_int16_t;
  break;

 case SP_MICRO:                  /*  1 0x01 spindle micro steps */
  rVar.spMicro = val.t_int16_t;
  break;

 case SP_MIN_RPM:                /*  2 0x02 spindle minimum rpm */
  rVar.spMinRpm = val.t_float;
  break;

 case SP_MAX_RPM:                /*  3 0x03 spindle maximum rpm */
  rVar.spMaxRpm = val.t_float;
  break;

 case SP_RPM:                    /*  4 0x04 spindle rpm */
  rVar.spRpm = val.t_float;
  break;

 case SP_ACCEL_TIME:             /*  5 0x05 spindle accel time */
  rVar.spAccelTime = val.t_float;
  break;

 case SP_ACCEL:                  /*  6 0x06 spindle accel rpm/sec^2 */
  rVar.spAccel = val.t_float;
  break;

 case SP_JOG_MIN_RPM:            /*  7 0x07 spindle jog minimum rpm */
  rVar.spJogMinRpm = val.t_float;
  break;

 case SP_JOG_MAX_RPM:            /*  8 0x08 spindle jog maximum rpm */
  rVar.spJogMaxRpm = val.t_float;
  break;

 case SP_JOG_RPM:                /*  9 0x09 spindle jog rpm */
  rVar.spJogRpm = val.t_float;
  break;

 case SP_JOG_ACCEL_TIME:         /* 10 0x0a spindle jog accel time */
  rVar.spJogAccelTime = val.t_float;
  break;

 case SP_JOG_TIME_INITIAL:       /* 11 0x0b spindle jog time initl */
  rVar.spJogTimeInitial = val.t_float;
  break;

 case SP_JOG_TIME_INC:           /* 12 0x0c spindle jog time increment */
  rVar.spJogTimeInc = val.t_float;
  break;

 case SP_JOG_TIME_MAX:           /* 13 0x0d spindle jog timemax */
  rVar.spJogTimeMax = val.t_float;
  break;

 case SP_JOG_DIR:                /* 14 0x0e spindle direction */
  rVar.spJogDir = val.t_char;
  break;

 case SP_DIR_FLAG:               /* 15 0x0f spindle invert direction */
  rVar.spDirFlag = val.t_char;
  break;

 case SP_TEST_INDEX:             /* 16 0x10 generate test index pulse */
  rVar.spTestIndex = val.t_char;
  break;

 case SP_TEST_ENCODER:           /* 17 0x11 generate enc test pulse */
  rVar.spTestEncoder = val.t_char;
  break;

 case Z_PITCH:                   /* 18 0x12 z axis leadscrew pitch */
  rVar.zPitch = val.t_float;
  break;

 case Z_RATIO:                   /* 19 0x13 z axis ratio */
  rVar.zRatio = val.t_float;
  break;

 case Z_MICRO:                   /* 20 0x14 z axis micro steps */
  rVar.zMicro = val.t_int16_t;
  break;

 case Z_MOTOR:                   /* 21 0x15 z axis motor steps */
  rVar.zMotor = val.t_int16_t;
  break;

 case Z_ACCEL_TIME:              /* 22 0x16 z axis acceleration */
  rVar.zAccelTime = val.t_float;
  break;

 case Z_ACCEL:                   /* 23 0x17 z accel rpm/sec^2 */
  rVar.zAccel = val.t_float;
  break;

 case Z_BACKLASH:                /* 24 0x18 z axis backlash */
  rVar.zBacklash = val.t_float;
  break;

 case Z_STEP_FACTOR:             /* 25 0x19 z steps inch factored */
  rVar.zStepFactor = val.t_int;
  break;

 case Z_DIR_FLAG:                /* 26 0x1a z invert direction */
  rVar.zDirFlag = val.t_char;
  break;

 case Z_MPG_FLAG:                /* 27 0x1b z invert mpg */
  rVar.zMpgFlag = val.t_char;
  break;

 case X_PITCH:                   /* 28 0x1c x axis leadscrew pitch */
  rVar.xPitch = val.t_float;
  break;

 case X_RATIO:                   /* 29 0x1d x axis ratio */
  rVar.xRatio = val.t_float;
  break;

 case X_MICRO:                   /* 30 0x1e x axis micro steps */
  rVar.xMicro = val.t_int16_t;
  break;

 case X_MOTOR:                   /* 31 0x1f x axis motor steps */
  rVar.xMotor = val.t_int16_t;
  break;

 case X_ACCEL_TIME:              /* 32 0x20 x axis acceleration */
  rVar.xAccelTime = val.t_float;
  break;

 case X_ACCEL:                   /* 33 0x21 x accel rpm/sec^2 */
  rVar.xAccel = val.t_float;
  break;

 case X_BACKLASH:                /* 34 0x22 x axis backlash */
  rVar.xBacklash = val.t_float;
  break;

 case X_STEP_FACTOR:             /* 35 0x23 x steps inch factored */
  rVar.xStepFactor = val.t_int;
  break;

 case X_DIR_FLAG:                /* 36 0x24 x invert direction */
  rVar.xDirFlag = val.t_char;
  break;

 case X_MPG_FLAG:                /* 37 0x25 x invert mpg */
  rVar.xMpgFlag = val.t_char;
  break;

 case X_DIAMETER:                /* 38 0x26 x diameter */
  rVar.xDiameter = val.t_int;
  break;

 case Z_MOVE_MIN:                /* 39 0x27 z move min speed */
  rVar.zMoveMin = val.t_float;
  break;

 case Z_MOVE_MAX:                /* 40 0x28 z move max speed */
  rVar.zMoveMax = val.t_float;
  break;

 case Z_JOG_MIN:                 /* 41 0x29 z jog min speed */
  rVar.zJogMin = val.t_float;
  break;

 case Z_JOG_MAX:                 /* 42 0x2a z jog max speed */
  rVar.zJogMax = val.t_float;
  break;

 case Z_JOG_SPEED:               /* 43 0x2b z jog speed */
  rVar.zJogSpeed = val.t_float;
  break;

 case X_MOVE_MIN:                /* 44 0x2c x move min speed */
  rVar.xMoveMin = val.t_float;
  break;

 case X_MOVE_MAX:                /* 45 0x2d x move max speed */
  rVar.xMoveMax = val.t_float;
  break;

 case X_JOG_MIN:                 /* 46 0x2e x jog min speed */
  rVar.xJogMin = val.t_float;
  break;

 case X_JOG_MAX:                 /* 47 0x2f x jog max speed */
  rVar.xJogMax = val.t_float;
  break;

 case X_JOG_SPEED:               /* 48 0x30 x jog speed */
  rVar.xJogSpeed = val.t_float;
  break;

 case TOTAL_PASSES:              /* 49 0x31 total passes */
  rVar.totalPasses = val.t_int16_t;
  break;

 case CURRENT_PASS:              /* 50 0x32 current passes */
  rVar.currentPass = val.t_int16_t;
  break;

 case MV_STATUS:                 /* 51 0x33 movement status */
  rVar.mvStatus = val.t_int16_t;
  break;

 case Z_MOVE_DIST:               /* 52 0x34 z move distance */
  rVar.zMoveDist = val.t_float;
  break;

 case Z_MOVE_POS:                /* 53 0x35 z move position */
  rVar.zMovePos = val.t_float;
  break;

 case Z_JOG_DIR:                 /* 54 0x36 x jog direction */
  rVar.zJogDir = val.t_int;
  break;

 case Z_SET_LOC:                 /* 55 0x37 z location to set */
  rVar.zSetLoc = val.t_float;
  break;

 case Z_LOC:                     /* 56 0x38 z dro location */
  rVar.zLoc = val.t_int;
  break;

 case Z_FLAG:                    /* 57 0x39 z move flag */
  rVar.zFlag = val.t_int;
  break;

 case Z_ABS_LOC:                 /* 58 0x3a z absolute location */
  rVar.zAbsLoc = val.t_int;
  break;

 case Z_MPG_INC:                 /* 59 0x3b z man pulse gen incr */
  rVar.zMpgInc = val.t_int;
  break;

 case Z_MPG_MAX:                 /* 60 0x3c z man pulse max distance */
  rVar.zMpgMax = val.t_int;
  break;

 case X_MOVE_DIST:               /* 61 0x3d x move distance */
  rVar.xMoveDist = val.t_float;
  break;

 case X_MOVE_POS:                /* 62 0x3e x move position */
  rVar.xMovePos = val.t_float;
  break;

 case X_JOG_DIR:                 /* 63 0x3f x jog direction */
  rVar.xJogDir = val.t_int;
  break;

 case X_SET_LOC:                 /* 64 0x40 x location to set */
  rVar.xSetLoc = val.t_float;
  break;

 case X_LOC:                     /* 65 0x41 x dro location */
  rVar.xLoc = val.t_int;
  break;

 case X_FLAG:                    /* 66 0x42 x move flag */
  rVar.xFlag = val.t_int;
  break;

 case X_ABS_LOC:                 /* 67 0x43 x absolute location */
  rVar.xAbsLoc = val.t_int;
  break;

 case X_MPG_INC:                 /* 68 0x44 X man pulse gen incr */
  rVar.xMpgInc = val.t_int;
  break;

 case X_MPG_MAX:                 /* 69 0x45 x man pulse max distance */
  rVar.xMpgMax = val.t_int;
  break;

 case JOG_TIME_INITIAL:          /* 70 0x46 jog time initial */
  rVar.jogTimeInitial = val.t_float;
  break;

 case JOG_TIME_INC:              /* 71 0x47 jog time increment */
  rVar.jogTimeInc = val.t_float;
  break;

 case JOG_TIME_MAX:              /* 72 0x48 jog time max */
  rVar.jogTimeMax = val.t_float;
  break;

 case TAPER_CYCLE_DIST:          /* 73 0x49 taperCycleDist */
  rVar.taperCycleDist = val.t_float;
  break;

 case INDEX_PRE_SCALER:          /* 74 0x4a index pre scaler */
  rVar.indexPreScaler = val.t_int;
  break;

 case LAST_INDEX_PERIOD:         /* 75 0x4b last index period */
  rVar.lastIndexPeriod = val.t_uint_t;
  break;

 case INDEX_PERIOD:              /* 76 0x4c index period */
  rVar.indexPeriod = val.t_uint_t;
  break;

 case REV_COUNTER:               /* 77 0x4d revolution counter */
  rVar.revCounter = val.t_uint_t;
  break;

 case Z_HOME_OFFSET:             /* 78 0x4e z home offset */
  rVar.zHomeOffset = val.t_int;
  break;

 case X_HOME_OFFSET:             /* 79 0x4f x home offset */
  rVar.xHomeOffset = val.t_int;
  break;

 case Z_HOME_SPEED:              /* 80 0x50 z final homing speed */
  rVar.zHomeSpeed = val.t_float;
  break;

 case Z_HOME_DIST:               /* 81 0x51 z max homing distance */
  rVar.zHomeDist = val.t_float;
  break;

 case Z_HOME_DIST_REV:           /* 82 0x52 z max rev homing distance */
  rVar.zHomeDistRev = val.t_float;
  break;

 case Z_HOME_DIST_BACKOFF:       /* 83 0x53 z home backoff dist */
  rVar.zHomeDistBackoff = val.t_float;
  break;

 case Z_HOME_DIR:                /* 84 0x54 z homing direction */
  rVar.zHomeDir = val.t_int;
  break;

 case X_HOME_SPEED:              /* 85 0x55 x final homing speed */
  rVar.xHomeSpeed = val.t_float;
  break;

 case X_HOME_DIST:               /* 86 0x56 x max homing distance */
  rVar.xHomeDist = val.t_float;
  break;

 case X_HOME_DIST_REV:           /* 87 0x57 x max rev homing distance */
  rVar.xHomeDistRev = val.t_float;
  break;

 case X_HOME_DIST_BACKOFF:       /* 88 0x58 x home backoff dist */
  rVar.xHomeDistBackoff = val.t_float;
  break;

 case X_HOME_DIR:                /* 89 0x59 x homing direction */
  rVar.xHomeDir = val.t_int;
  break;

 case X_HOME_LOC:                /* 90 0x5a x home test location */
  rVar.xHomeLoc = val.t_int;
  break;

 case X_HOME_START:              /* 91 0x5b x start of home signal */
  rVar.xHomeStart = val.t_int;
  break;

 case X_HOME_END:                /* 92 0x5c x end of home signal */
  rVar.xHomeEnd = val.t_int;
  break;

 case Z_DRO_LOC:                 /* 93 0x5d z dro location */
  rVar.zDroLoc = val.t_int;
  break;

 case Z_DRO_OFFSET:              /* 94 0x5e z dro to zero */
  rVar.zDroOffset = val.t_int;
  break;

 case Z_DRO_COUNT_INCH:          /* 95 0x5f z dro scale */
  rVar.zDroCountInch = val.t_int;
  break;

 case Z_DRO_FACTOR:              /* 96 0x60 x dro counts inch factored */
  rVar.zDroFactor = val.t_int;
  break;

 case Z_DRO_INVERT:              /* 97 0x61 z dro invert */
  rVar.zDroInvert = val.t_int;
  break;

 case Z_USE_DRO:                 /* 98 0x62 z use dro for position */
  rVar.zUseDro = val.t_char;
  break;

 case Z_DONE_DELAY:              /* 99 0x63 z done to read dro delay */
  rVar.zDoneDelay = val.t_int;
  break;

 case Z_DRO_FINAL_DIST:          /* 100 0x64 z final approach distance */
  rVar.zDroFinalDist = val.t_int;
  break;

 case X_DRO_LOC:                 /* 101 0x65 x dro location */
  rVar.xDroLoc = val.t_int;
  break;

 case X_DRO_OFFSET:              /* 102 0x66 x dro to zero */
  rVar.xDroOffset = val.t_int;
  break;

 case X_DRO_COUNT_INCH:          /* 103 0x67 x dro scale */
  rVar.xDroCountInch = val.t_int;
  break;

 case X_DRO_FACTOR:              /* 104 0x68 x dro counts inch factored */
  rVar.xDroFactor = val.t_int;
  break;

 case X_DRO_INVERT:              /* 105 0x69 x dro invert */
  rVar.xDroInvert = val.t_int;
  break;

 case X_USE_DRO:                 /* 106 0x6a x use dro for position */
  rVar.xUseDro = val.t_char;
  break;

 case X_DONE_DELAY:              /* 107 0x6b x done to read dro delay */
  rVar.xDoneDelay = val.t_int;
  break;

 case X_DRO_FINAL_DIST:          /* 108 0x6c x final approach distance */
  rVar.xDroFinalDist = val.t_int;
  break;

 case X_HOME_STATUS:             /* 109 0x6d x home status */
  rVar.xHomeStatus = val.t_int;
  break;

 case Z_HOME_STATUS:             /* 110 0x6e z home status */
  rVar.zHomeStatus = val.t_int;
  break;

 case PROBE_SPEED:               /* 111 0x6f probe speed */
  rVar.probeSpeed = val.t_float;
  break;

 case PROBE_DIST:                /* 112 0x70 probe test distance */
  rVar.probeDist = val.t_int;
  break;

 case PROBE_INV:                 /* 113 0x71 invert polarity of probe */
  rVar.probeInv = val.t_int;
  break;

 case STEPPER_DRIVE:             /* 114 0x72 stepper driven spindle */
  rVar.stepperDrive = val.t_char;
  break;

 case MOTOR_TEST:                /* 115 0x73 use stepper to test motor */
  rVar.motorTest = val.t_char;
  break;

 case SPINDLE_ENCODER:           /* 116 0x74 motor with spindle enc */
  rVar.spindleEncoder = val.t_char;
  break;

 case SPINDLE_SYNC_BOARD:        /* 117 0x75 spindle sync board */
  rVar.spindleSyncBoard = val.t_char;
  break;

 case SPINDLE_INTERNAL_SYNC:     /* 118 0x76 spindle internal sync */
  rVar.spindleInternalSync = val.t_char;
  break;

 case TURN_SYNC:                 /* 119 0x77 sync type for turning */
  rVar.turnSync = val.t_char;
  break;

 case THREAD_SYNC:               /* 120 0x78 sync type for threading */
  rVar.threadSync = val.t_char;
  break;

 case CAP_TMR_ENABLE:            /* 121 0x79 enable capture timer */
  rVar.capTmrEnable = val.t_char;
  break;

 case CFG_FPGA:                  /* 122 0x7a using fpga */
  rVar.cfgFpga = val.t_char;
  break;

 case CFG_MEGA:                  /* 123 0x7b control link to mega */
  rVar.cfgMega = val.t_char;
  break;

 case CFG_MPG:                   /* 124 0x7c manual pulse generator */
  rVar.cfgMpg = val.t_char;
  break;

 case CFG_DRO:                   /* 125 0x7d digital readout */
  rVar.cfgDro = val.t_char;
  break;

 case CFG_LCD:                   /* 126 0x7e lcd display */
  rVar.cfgLcd = val.t_char;
  break;

 case CFG_FCY:                   /* 127 0x7f system clock speed */
  rVar.cfgFcy = val.t_uint_t;
  break;

 case CFG_SWITCH:                /* 128 0x80 spindle off on switch */
  rVar.cfgSwitch = val.t_int;
  break;

 case CFG_VAR_SPEED:             /* 129 0x81 spindle variable speed */
  rVar.cfgVarSpeed = val.t_int;
  break;

 case SETUP_DONE:                /* 130 0x82 setup done */
  rVar.setupDone = val.t_char;
  break;

 case ENC_PER_REV:               /* 131 0x83 spindle enc counts per rev */
  rVar.encPerRev = val.t_uint16_t;
  break;

 case ENC_ENABLE:                /* 132 0x84 encoder enable flag */
  rVar.encEnable = val.t_char;
  break;

 case ENC_PRE_SCALER:            /* 133 0x85 encoder prescaler */
  rVar.encPreScaler = val.t_uint16_t;
  break;

 case ENC_TIMER:                 /* 134 0x86 encoder timer counts */
  rVar.encTimer = val.t_uint16_t;
  break;

 case ENC_RUN_COUNT:             /* 135 0x87 encoder run count */
  rVar.encRunCount = val.t_int;
  break;

 case ENC_RUN:                   /* 136 0x88 encoder running flag */
  rVar.encRun = val.t_char;
  break;

 case ENC_COUNTER:               /* 137 0x89 encoder count in rev */
  rVar.encCounter = val.t_int16_t;
  break;

 case ENC_REV_COUNTER:           /* 138 0x8a encoder revolution counter */
  rVar.encRevCounter = val.t_int32_t;
  break;

 case RPM:                       /* 139 0x8b current measured rpm */
  rVar.rpm = val.t_int16_t;
  break;

 case FPGA_FREQUENCY:            /* 140 0x8c fpga clock frequency */
  rVar.fpgaFrequency = val.t_int32_t;
  break;

 case FREQ_MULT:                 /* 141 0x8d frequency multiplier */
  rVar.freqMult = val.t_int16_t;
  break;

 case X_CFG_REG:                 /* 142 0x8e xilinx cfg register */
  rVar.xCfgReg = val.t_int16_t;
  break;

 case L_SYNC_CYCLE:              /* 143 0x8f sync cycle length */
  rVar.lSyncCycle = val.t_uint16_t;
  break;

 case L_SYNC_OUTPUT:             /* 144 0x90 sync outputs per cycle */
  rVar.lSyncOutput = val.t_uint16_t;
  break;

 case L_SYNC_IN_PRESCALER:       /* 145 0x91 input sync prescaler */
  rVar.lSyncInPrescaler = val.t_uint16_t;
  break;

 case L_SYNC_OUT_PRESCALER:      /* 146 0x92 output sync prescaler */
  rVar.lSyncOutPrescaler = val.t_uint16_t;
  break;

 case L_X_SYNC_CYCLE:            /* 147 0x93 sync cycle length */
  rVar.lXSyncCycle = val.t_uint16_t;
  break;

 case L_X_SYNC_OUTPUT:           /* 148 0x94 sync outputs per cycle */
  rVar.lXSyncOutput = val.t_uint16_t;
  break;

 case L_X_SYNC_IN_PRESCALER:     /* 149 0x95 input sync prescaler */
  rVar.lXSyncInPrescaler = val.t_uint16_t;
  break;

 case L_X_SYNC_OUT_PRESCALER:    /* 150 0x96 output sync prescaler */
  rVar.lXSyncOutPrescaler = val.t_uint16_t;
  break;

 case TH_Z_START:                /* 151 0x97 threading z start */
  rVar.thZStart = val.t_int32_t;
  break;

 case TH_X_START:                /* 152 0x98 threading x start */
  rVar.thXStart = val.t_int32_t;
  break;

 case TAN_THREAD_ANGLE:          /* 153 0x99 tan of threading angle */
  rVar.tanThreadAngle = val.t_float;
  break;

 case X_FEED:                    /* 154 0x9a x feed */
  rVar.xFeed = val.t_int32_t;
  break;

 case RUNOUT_DISTANCE:           /* 155 0x9b runout distance */
  rVar.runoutDistance = val.t_float;
  break;

 case RUNOUT_DEPTH:              /* 156 0x9c runout depth */
  rVar.runoutDepth = val.t_float;
  break;

 case JOG_DEBUG:                 /* 157 0x9d jog interrupt debug */
  rVar.jogDebug = val.t_char;
  break;

 case PWM_FREQ:                  /* 158 0x9e spindle speed pwm frequency */
  rVar.pwmFreq = val.t_uint_t;
  break;

 case MIN_SPEED:                 /* 159 0x9f min speed for current range */
  rVar.minSpeed = val.t_int16_t;
  break;

 case MAX_SPEED:                 /* 160 0xa0 max speed for current range */
  rVar.maxSpeed = val.t_int16_t;
  break;

 case CURRENT_OP:                /* 161 0xa1 current operation */
  rVar.currentOp = val.t_char;
  break;

 case LIMIT_OVERRIDE:            /* 162 0xa2 override limit switches */
  rVar.limitOverride = val.t_char;
  break;

 case COMMON_LIMITS:             /* 163 0xa3 all limit switches one pin */
  rVar.commonLimits = val.t_char;
  break;

 case LIMITS_ENABLED:            /* 164 0xa4 limits enabled */
  rVar.limitsEnabled = val.t_char;
  break;

 case COMMON_HOME:               /* 165 0xa5 all home switches one pin */
  rVar.commonHome = val.t_char;
  break;

 case Z_LIM_ENA:                 /* 166 0xa6 z limit enable */
  rVar.zLimEna = val.t_char;
  break;

 case Z_LIM_NEG_INV:             /* 167 0xa7 z negative limit invert */
  rVar.zLimNegInv = val.t_char;
  break;

 case Z_LIM_POS_INV:             /* 168 0xa8 z Positive limit Invert */
  rVar.zLimPosInv = val.t_char;
  break;

 case Z_HOME_ENA:                /* 169 0xa9 z home enable */
  rVar.zHomeEna = val.t_char;
  break;

 case Z_HOME_INV:                /* 170 0xaa z home invert */
  rVar.zHomeInv = val.t_char;
  break;

 case X_LIM_ENA:                 /* 171 0xab x limit enable */
  rVar.xLimEna = val.t_char;
  break;

 case X_LIM_NEG_INV:             /* 172 0xac x negative limit invert */
  rVar.xLimNegInv = val.t_char;
  break;

 case X_LIM_POS_INV:             /* 173 0xad x Positive limit Invert */
  rVar.xLimPosInv = val.t_char;
  break;

 case X_HOME_ENA:                /* 174 0xae x home enable */
  rVar.xHomeEna = val.t_char;
  break;

 case X_HOME_INV:                /* 175 0xaf x home invert */
  rVar.xHomeInv = val.t_char;
  break;

 case E_STOP_ENA:                /* 176 0xb0 enable estop */
  rVar.eStopEna = val.t_char;
  break;

 case E_STOP_INV:                /* 177 0xb1 invert estop signal */
  rVar.eStopInv = val.t_char;
  break;

 case CMD_PAUSED:                /* 178 0xb2 move commands paused */
  rVar.cmdPaused = val.t_char;
  break;

 case ARC_RADIUS:                /* 179 0xb3 arc radius */
  rVar.arcRadius = val.t_float;
  break;

 case ARC_X_CENTER:              /* 180 0xb4 arc x center */
  rVar.arcXCenter = val.t_int;
  break;

 case ARC_Z_CENTER:              /* 181 0xb5 arc z center */
  rVar.arcZCenter = val.t_int;
  break;

 case ARC_X_START:               /* 182 0xb6 arc x start */
  rVar.arcXStart = val.t_int;
  break;

 case ARC_Z_START:               /* 183 0xb7 arc z start */
  rVar.arcZStart = val.t_int;
  break;

 case ARC_X_END:                 /* 184 0xb8 arc x center */
  rVar.arcXEnd = val.t_int;
  break;

 case ARC_Z_END:                 /* 185 0xb9 arc z center */
  rVar.arcZEnd = val.t_int;
  break;

 case MEGA_VFD:                  /* 186 0xba mega vfd speed mode */
  rVar.megaVfd = val.t_char;
  break;

 case MEGA_SIM:                  /* 187 0xbb mega encoder lines */
  rVar.megaSim = val.t_char;
  break;

 case USB_ENA:                   /* 188 0xbc enable usb */
  rVar.usbEna = val.t_char;
  break;

 case MAX_PARM:                  /* 189 0xbd maximum parameter */
  rVar.maxParm = val.t_int16_t;
  break;

 }
}

void getRemVar(const int parm, const P_DATA_UNION val)
{
 switch(parm)
 {
 default:
  break;

 case SP_STEPS:                  /*  0 0x00 spindle motor steps */
  val->t_int16_t = rVar.spSteps;
  break;

 case SP_MICRO:                  /*  1 0x01 spindle micro steps */
  val->t_int16_t = rVar.spMicro;
  break;

 case SP_MIN_RPM:                /*  2 0x02 spindle minimum rpm */
  val->t_float = rVar.spMinRpm;
  break;

 case SP_MAX_RPM:                /*  3 0x03 spindle maximum rpm */
  val->t_float = rVar.spMaxRpm;
  break;

 case SP_RPM:                    /*  4 0x04 spindle rpm */
  val->t_float = rVar.spRpm;
  break;

 case SP_ACCEL_TIME:             /*  5 0x05 spindle accel time */
  val->t_float = rVar.spAccelTime;
  break;

 case SP_ACCEL:                  /*  6 0x06 spindle accel rpm/sec^2 */
  val->t_float = rVar.spAccel;
  break;

 case SP_JOG_MIN_RPM:            /*  7 0x07 spindle jog minimum rpm */
  val->t_float = rVar.spJogMinRpm;
  break;

 case SP_JOG_MAX_RPM:            /*  8 0x08 spindle jog maximum rpm */
  val->t_float = rVar.spJogMaxRpm;
  break;

 case SP_JOG_RPM:                /*  9 0x09 spindle jog rpm */
  val->t_float = rVar.spJogRpm;
  break;

 case SP_JOG_ACCEL_TIME:         /* 10 0x0a spindle jog accel time */
  val->t_float = rVar.spJogAccelTime;
  break;

 case SP_JOG_TIME_INITIAL:       /* 11 0x0b spindle jog time initl */
  val->t_float = rVar.spJogTimeInitial;
  break;

 case SP_JOG_TIME_INC:           /* 12 0x0c spindle jog time increment */
  val->t_float = rVar.spJogTimeInc;
  break;

 case SP_JOG_TIME_MAX:           /* 13 0x0d spindle jog timemax */
  val->t_float = rVar.spJogTimeMax;
  break;

 case SP_JOG_DIR:                /* 14 0x0e spindle direction */
  val->t_char = rVar.spJogDir;
  break;

 case SP_DIR_FLAG:               /* 15 0x0f spindle invert direction */
  val->t_char = rVar.spDirFlag;
  break;

 case SP_TEST_INDEX:             /* 16 0x10 generate test index pulse */
  val->t_char = rVar.spTestIndex;
  break;

 case SP_TEST_ENCODER:           /* 17 0x11 generate enc test pulse */
  val->t_char = rVar.spTestEncoder;
  break;

 case Z_PITCH:                   /* 18 0x12 z axis leadscrew pitch */
  val->t_float = rVar.zPitch;
  break;

 case Z_RATIO:                   /* 19 0x13 z axis ratio */
  val->t_float = rVar.zRatio;
  break;

 case Z_MICRO:                   /* 20 0x14 z axis micro steps */
  val->t_int16_t = rVar.zMicro;
  break;

 case Z_MOTOR:                   /* 21 0x15 z axis motor steps */
  val->t_int16_t = rVar.zMotor;
  break;

 case Z_ACCEL_TIME:              /* 22 0x16 z axis acceleration */
  val->t_float = rVar.zAccelTime;
  break;

 case Z_ACCEL:                   /* 23 0x17 z accel rpm/sec^2 */
  val->t_float = rVar.zAccel;
  break;

 case Z_BACKLASH:                /* 24 0x18 z axis backlash */
  val->t_float = rVar.zBacklash;
  break;

 case Z_STEP_FACTOR:             /* 25 0x19 z steps inch factored */
  val->t_int = rVar.zStepFactor;
  break;

 case Z_DIR_FLAG:                /* 26 0x1a z invert direction */
  val->t_char = rVar.zDirFlag;
  break;

 case Z_MPG_FLAG:                /* 27 0x1b z invert mpg */
  val->t_char = rVar.zMpgFlag;
  break;

 case X_PITCH:                   /* 28 0x1c x axis leadscrew pitch */
  val->t_float = rVar.xPitch;
  break;

 case X_RATIO:                   /* 29 0x1d x axis ratio */
  val->t_float = rVar.xRatio;
  break;

 case X_MICRO:                   /* 30 0x1e x axis micro steps */
  val->t_int16_t = rVar.xMicro;
  break;

 case X_MOTOR:                   /* 31 0x1f x axis motor steps */
  val->t_int16_t = rVar.xMotor;
  break;

 case X_ACCEL_TIME:              /* 32 0x20 x axis acceleration */
  val->t_float = rVar.xAccelTime;
  break;

 case X_ACCEL:                   /* 33 0x21 x accel rpm/sec^2 */
  val->t_float = rVar.xAccel;
  break;

 case X_BACKLASH:                /* 34 0x22 x axis backlash */
  val->t_float = rVar.xBacklash;
  break;

 case X_STEP_FACTOR:             /* 35 0x23 x steps inch factored */
  val->t_int = rVar.xStepFactor;
  break;

 case X_DIR_FLAG:                /* 36 0x24 x invert direction */
  val->t_char = rVar.xDirFlag;
  break;

 case X_MPG_FLAG:                /* 37 0x25 x invert mpg */
  val->t_char = rVar.xMpgFlag;
  break;

 case X_DIAMETER:                /* 38 0x26 x diameter */
  val->t_int = rVar.xDiameter;
  break;

 case Z_MOVE_MIN:                /* 39 0x27 z move min speed */
  val->t_float = rVar.zMoveMin;
  break;

 case Z_MOVE_MAX:                /* 40 0x28 z move max speed */
  val->t_float = rVar.zMoveMax;
  break;

 case Z_JOG_MIN:                 /* 41 0x29 z jog min speed */
  val->t_float = rVar.zJogMin;
  break;

 case Z_JOG_MAX:                 /* 42 0x2a z jog max speed */
  val->t_float = rVar.zJogMax;
  break;

 case Z_JOG_SPEED:               /* 43 0x2b z jog speed */
  val->t_float = rVar.zJogSpeed;
  break;

 case X_MOVE_MIN:                /* 44 0x2c x move min speed */
  val->t_float = rVar.xMoveMin;
  break;

 case X_MOVE_MAX:                /* 45 0x2d x move max speed */
  val->t_float = rVar.xMoveMax;
  break;

 case X_JOG_MIN:                 /* 46 0x2e x jog min speed */
  val->t_float = rVar.xJogMin;
  break;

 case X_JOG_MAX:                 /* 47 0x2f x jog max speed */
  val->t_float = rVar.xJogMax;
  break;

 case X_JOG_SPEED:               /* 48 0x30 x jog speed */
  val->t_float = rVar.xJogSpeed;
  break;

 case TOTAL_PASSES:              /* 49 0x31 total passes */
  val->t_int16_t = rVar.totalPasses;
  break;

 case CURRENT_PASS:              /* 50 0x32 current passes */
  val->t_int16_t = rVar.currentPass;
  break;

 case MV_STATUS:                 /* 51 0x33 movement status */
  val->t_int16_t = rVar.mvStatus;
  break;

 case Z_MOVE_DIST:               /* 52 0x34 z move distance */
  val->t_float = rVar.zMoveDist;
  break;

 case Z_MOVE_POS:                /* 53 0x35 z move position */
  val->t_float = rVar.zMovePos;
  break;

 case Z_JOG_DIR:                 /* 54 0x36 x jog direction */
  val->t_int = rVar.zJogDir;
  break;

 case Z_SET_LOC:                 /* 55 0x37 z location to set */
  val->t_float = rVar.zSetLoc;
  break;

 case Z_LOC:                     /* 56 0x38 z dro location */
  val->t_int = rVar.zLoc;
  break;

 case Z_FLAG:                    /* 57 0x39 z move flag */
  val->t_int = rVar.zFlag;
  break;

 case Z_ABS_LOC:                 /* 58 0x3a z absolute location */
  val->t_int = rVar.zAbsLoc;
  break;

 case Z_MPG_INC:                 /* 59 0x3b z man pulse gen incr */
  val->t_int = rVar.zMpgInc;
  break;

 case Z_MPG_MAX:                 /* 60 0x3c z man pulse max distance */
  val->t_int = rVar.zMpgMax;
  break;

 case X_MOVE_DIST:               /* 61 0x3d x move distance */
  val->t_float = rVar.xMoveDist;
  break;

 case X_MOVE_POS:                /* 62 0x3e x move position */
  val->t_float = rVar.xMovePos;
  break;

 case X_JOG_DIR:                 /* 63 0x3f x jog direction */
  val->t_int = rVar.xJogDir;
  break;

 case X_SET_LOC:                 /* 64 0x40 x location to set */
  val->t_float = rVar.xSetLoc;
  break;

 case X_LOC:                     /* 65 0x41 x dro location */
  val->t_int = rVar.xLoc;
  break;

 case X_FLAG:                    /* 66 0x42 x move flag */
  val->t_int = rVar.xFlag;
  break;

 case X_ABS_LOC:                 /* 67 0x43 x absolute location */
  val->t_int = rVar.xAbsLoc;
  break;

 case X_MPG_INC:                 /* 68 0x44 X man pulse gen incr */
  val->t_int = rVar.xMpgInc;
  break;

 case X_MPG_MAX:                 /* 69 0x45 x man pulse max distance */
  val->t_int = rVar.xMpgMax;
  break;

 case JOG_TIME_INITIAL:          /* 70 0x46 jog time initial */
  val->t_float = rVar.jogTimeInitial;
  break;

 case JOG_TIME_INC:              /* 71 0x47 jog time increment */
  val->t_float = rVar.jogTimeInc;
  break;

 case JOG_TIME_MAX:              /* 72 0x48 jog time max */
  val->t_float = rVar.jogTimeMax;
  break;

 case TAPER_CYCLE_DIST:          /* 73 0x49 taperCycleDist */
  val->t_float = rVar.taperCycleDist;
  break;

 case INDEX_PRE_SCALER:          /* 74 0x4a index pre scaler */
  val->t_int = rVar.indexPreScaler;
  break;

 case LAST_INDEX_PERIOD:         /* 75 0x4b last index period */
  val->t_uint_t = rVar.lastIndexPeriod;
  break;

 case INDEX_PERIOD:              /* 76 0x4c index period */
  val->t_uint_t = rVar.indexPeriod;
  break;

 case REV_COUNTER:               /* 77 0x4d revolution counter */
  val->t_uint_t = rVar.revCounter;
  break;

 case Z_HOME_OFFSET:             /* 78 0x4e z home offset */
  val->t_int = rVar.zHomeOffset;
  break;

 case X_HOME_OFFSET:             /* 79 0x4f x home offset */
  val->t_int = rVar.xHomeOffset;
  break;

 case Z_HOME_SPEED:              /* 80 0x50 z final homing speed */
  val->t_float = rVar.zHomeSpeed;
  break;

 case Z_HOME_DIST:               /* 81 0x51 z max homing distance */
  val->t_float = rVar.zHomeDist;
  break;

 case Z_HOME_DIST_REV:           /* 82 0x52 z max rev homing distance */
  val->t_float = rVar.zHomeDistRev;
  break;

 case Z_HOME_DIST_BACKOFF:       /* 83 0x53 z home backoff dist */
  val->t_float = rVar.zHomeDistBackoff;
  break;

 case Z_HOME_DIR:                /* 84 0x54 z homing direction */
  val->t_int = rVar.zHomeDir;
  break;

 case X_HOME_SPEED:              /* 85 0x55 x final homing speed */
  val->t_float = rVar.xHomeSpeed;
  break;

 case X_HOME_DIST:               /* 86 0x56 x max homing distance */
  val->t_float = rVar.xHomeDist;
  break;

 case X_HOME_DIST_REV:           /* 87 0x57 x max rev homing distance */
  val->t_float = rVar.xHomeDistRev;
  break;

 case X_HOME_DIST_BACKOFF:       /* 88 0x58 x home backoff dist */
  val->t_float = rVar.xHomeDistBackoff;
  break;

 case X_HOME_DIR:                /* 89 0x59 x homing direction */
  val->t_int = rVar.xHomeDir;
  break;

 case X_HOME_LOC:                /* 90 0x5a x home test location */
  val->t_int = rVar.xHomeLoc;
  break;

 case X_HOME_START:              /* 91 0x5b x start of home signal */
  val->t_int = rVar.xHomeStart;
  break;

 case X_HOME_END:                /* 92 0x5c x end of home signal */
  val->t_int = rVar.xHomeEnd;
  break;

 case Z_DRO_LOC:                 /* 93 0x5d z dro location */
  val->t_int = rVar.zDroLoc;
  break;

 case Z_DRO_OFFSET:              /* 94 0x5e z dro to zero */
  val->t_int = rVar.zDroOffset;
  break;

 case Z_DRO_COUNT_INCH:          /* 95 0x5f z dro scale */
  val->t_int = rVar.zDroCountInch;
  break;

 case Z_DRO_FACTOR:              /* 96 0x60 x dro counts inch factored */
  val->t_int = rVar.zDroFactor;
  break;

 case Z_DRO_INVERT:              /* 97 0x61 z dro invert */
  val->t_int = rVar.zDroInvert;
  break;

 case Z_USE_DRO:                 /* 98 0x62 z use dro for position */
  val->t_char = rVar.zUseDro;
  break;

 case Z_DONE_DELAY:              /* 99 0x63 z done to read dro delay */
  val->t_int = rVar.zDoneDelay;
  break;

 case Z_DRO_FINAL_DIST:          /* 100 0x64 z final approach distance */
  val->t_int = rVar.zDroFinalDist;
  break;

 case X_DRO_LOC:                 /* 101 0x65 x dro location */
  val->t_int = rVar.xDroLoc;
  break;

 case X_DRO_OFFSET:              /* 102 0x66 x dro to zero */
  val->t_int = rVar.xDroOffset;
  break;

 case X_DRO_COUNT_INCH:          /* 103 0x67 x dro scale */
  val->t_int = rVar.xDroCountInch;
  break;

 case X_DRO_FACTOR:              /* 104 0x68 x dro counts inch factored */
  val->t_int = rVar.xDroFactor;
  break;

 case X_DRO_INVERT:              /* 105 0x69 x dro invert */
  val->t_int = rVar.xDroInvert;
  break;

 case X_USE_DRO:                 /* 106 0x6a x use dro for position */
  val->t_char = rVar.xUseDro;
  break;

 case X_DONE_DELAY:              /* 107 0x6b x done to read dro delay */
  val->t_int = rVar.xDoneDelay;
  break;

 case X_DRO_FINAL_DIST:          /* 108 0x6c x final approach distance */
  val->t_int = rVar.xDroFinalDist;
  break;

 case X_HOME_STATUS:             /* 109 0x6d x home status */
  val->t_int = rVar.xHomeStatus;
  break;

 case Z_HOME_STATUS:             /* 110 0x6e z home status */
  val->t_int = rVar.zHomeStatus;
  break;

 case PROBE_SPEED:               /* 111 0x6f probe speed */
  val->t_float = rVar.probeSpeed;
  break;

 case PROBE_DIST:                /* 112 0x70 probe test distance */
  val->t_int = rVar.probeDist;
  break;

 case PROBE_INV:                 /* 113 0x71 invert polarity of probe */
  val->t_int = rVar.probeInv;
  break;

 case STEPPER_DRIVE:             /* 114 0x72 stepper driven spindle */
  val->t_char = rVar.stepperDrive;
  break;

 case MOTOR_TEST:                /* 115 0x73 use stepper to test motor */
  val->t_char = rVar.motorTest;
  break;

 case SPINDLE_ENCODER:           /* 116 0x74 motor with spindle enc */
  val->t_char = rVar.spindleEncoder;
  break;

 case SPINDLE_SYNC_BOARD:        /* 117 0x75 spindle sync board */
  val->t_char = rVar.spindleSyncBoard;
  break;

 case SPINDLE_INTERNAL_SYNC:     /* 118 0x76 spindle internal sync */
  val->t_char = rVar.spindleInternalSync;
  break;

 case TURN_SYNC:                 /* 119 0x77 sync type for turning */
  val->t_char = rVar.turnSync;
  break;

 case THREAD_SYNC:               /* 120 0x78 sync type for threading */
  val->t_char = rVar.threadSync;
  break;

 case CAP_TMR_ENABLE:            /* 121 0x79 enable capture timer */
  val->t_char = rVar.capTmrEnable;
  break;

 case CFG_FPGA:                  /* 122 0x7a using fpga */
  val->t_char = rVar.cfgFpga;
  break;

 case CFG_MEGA:                  /* 123 0x7b control link to mega */
  val->t_char = rVar.cfgMega;
  break;

 case CFG_MPG:                   /* 124 0x7c manual pulse generator */
  val->t_char = rVar.cfgMpg;
  break;

 case CFG_DRO:                   /* 125 0x7d digital readout */
  val->t_char = rVar.cfgDro;
  break;

 case CFG_LCD:                   /* 126 0x7e lcd display */
  val->t_char = rVar.cfgLcd;
  break;

 case CFG_FCY:                   /* 127 0x7f system clock speed */
  val->t_uint_t = rVar.cfgFcy;
  break;

 case CFG_SWITCH:                /* 128 0x80 spindle off on switch */
  val->t_int = rVar.cfgSwitch;
  break;

 case CFG_VAR_SPEED:             /* 129 0x81 spindle variable speed */
  val->t_int = rVar.cfgVarSpeed;
  break;

 case SETUP_DONE:                /* 130 0x82 setup done */
  val->t_char = rVar.setupDone;
  break;

 case ENC_PER_REV:               /* 131 0x83 spindle enc counts per rev */
  val->t_uint16_t = rVar.encPerRev;
  break;

 case ENC_ENABLE:                /* 132 0x84 encoder enable flag */
  val->t_char = rVar.encEnable;
  break;

 case ENC_PRE_SCALER:            /* 133 0x85 encoder prescaler */
  val->t_uint16_t = rVar.encPreScaler;
  break;

 case ENC_TIMER:                 /* 134 0x86 encoder timer counts */
  val->t_uint16_t = rVar.encTimer;
  break;

 case ENC_RUN_COUNT:             /* 135 0x87 encoder run count */
  val->t_int = rVar.encRunCount;
  break;

 case ENC_RUN:                   /* 136 0x88 encoder running flag */
  val->t_char = rVar.encRun;
  break;

 case ENC_COUNTER:               /* 137 0x89 encoder count in rev */
  val->t_int16_t = rVar.encCounter;
  break;

 case ENC_REV_COUNTER:           /* 138 0x8a encoder revolution counter */
  val->t_int32_t = rVar.encRevCounter;
  break;

 case RPM:                       /* 139 0x8b current measured rpm */
  val->t_int16_t = rVar.rpm;
  break;

 case FPGA_FREQUENCY:            /* 140 0x8c fpga clock frequency */
  val->t_int32_t = rVar.fpgaFrequency;
  break;

 case FREQ_MULT:                 /* 141 0x8d frequency multiplier */
  val->t_int16_t = rVar.freqMult;
  break;

 case X_CFG_REG:                 /* 142 0x8e xilinx cfg register */
  val->t_int16_t = rVar.xCfgReg;
  break;

 case L_SYNC_CYCLE:              /* 143 0x8f sync cycle length */
  val->t_uint16_t = rVar.lSyncCycle;
  break;

 case L_SYNC_OUTPUT:             /* 144 0x90 sync outputs per cycle */
  val->t_uint16_t = rVar.lSyncOutput;
  break;

 case L_SYNC_IN_PRESCALER:       /* 145 0x91 input sync prescaler */
  val->t_uint16_t = rVar.lSyncInPrescaler;
  break;

 case L_SYNC_OUT_PRESCALER:      /* 146 0x92 output sync prescaler */
  val->t_uint16_t = rVar.lSyncOutPrescaler;
  break;

 case L_X_SYNC_CYCLE:            /* 147 0x93 sync cycle length */
  val->t_uint16_t = rVar.lXSyncCycle;
  break;

 case L_X_SYNC_OUTPUT:           /* 148 0x94 sync outputs per cycle */
  val->t_uint16_t = rVar.lXSyncOutput;
  break;

 case L_X_SYNC_IN_PRESCALER:     /* 149 0x95 input sync prescaler */
  val->t_uint16_t = rVar.lXSyncInPrescaler;
  break;

 case L_X_SYNC_OUT_PRESCALER:    /* 150 0x96 output sync prescaler */
  val->t_uint16_t = rVar.lXSyncOutPrescaler;
  break;

 case TH_Z_START:                /* 151 0x97 threading z start */
  val->t_int32_t = rVar.thZStart;
  break;

 case TH_X_START:                /* 152 0x98 threading x start */
  val->t_int32_t = rVar.thXStart;
  break;

 case TAN_THREAD_ANGLE:          /* 153 0x99 tan of threading angle */
  val->t_float = rVar.tanThreadAngle;
  break;

 case X_FEED:                    /* 154 0x9a x feed */
  val->t_int32_t = rVar.xFeed;
  break;

 case RUNOUT_DISTANCE:           /* 155 0x9b runout distance */
  val->t_float = rVar.runoutDistance;
  break;

 case RUNOUT_DEPTH:              /* 156 0x9c runout depth */
  val->t_float = rVar.runoutDepth;
  break;

 case JOG_DEBUG:                 /* 157 0x9d jog interrupt debug */
  val->t_char = rVar.jogDebug;
  break;

 case PWM_FREQ:                  /* 158 0x9e spindle speed pwm frequency */
  val->t_uint_t = rVar.pwmFreq;
  break;

 case MIN_SPEED:                 /* 159 0x9f min speed for current range */
  val->t_int16_t = rVar.minSpeed;
  break;

 case MAX_SPEED:                 /* 160 0xa0 max speed for current range */
  val->t_int16_t = rVar.maxSpeed;
  break;

 case CURRENT_OP:                /* 161 0xa1 current operation */
  val->t_char = rVar.currentOp;
  break;

 case LIMIT_OVERRIDE:            /* 162 0xa2 override limit switches */
  val->t_char = rVar.limitOverride;
  break;

 case COMMON_LIMITS:             /* 163 0xa3 all limit switches one pin */
  val->t_char = rVar.commonLimits;
  break;

 case LIMITS_ENABLED:            /* 164 0xa4 limits enabled */
  val->t_char = rVar.limitsEnabled;
  break;

 case COMMON_HOME:               /* 165 0xa5 all home switches one pin */
  val->t_char = rVar.commonHome;
  break;

 case Z_LIM_ENA:                 /* 166 0xa6 z limit enable */
  val->t_char = rVar.zLimEna;
  break;

 case Z_LIM_NEG_INV:             /* 167 0xa7 z negative limit invert */
  val->t_char = rVar.zLimNegInv;
  break;

 case Z_LIM_POS_INV:             /* 168 0xa8 z Positive limit Invert */
  val->t_char = rVar.zLimPosInv;
  break;

 case Z_HOME_ENA:                /* 169 0xa9 z home enable */
  val->t_char = rVar.zHomeEna;
  break;

 case Z_HOME_INV:                /* 170 0xaa z home invert */
  val->t_char = rVar.zHomeInv;
  break;

 case X_LIM_ENA:                 /* 171 0xab x limit enable */
  val->t_char = rVar.xLimEna;
  break;

 case X_LIM_NEG_INV:             /* 172 0xac x negative limit invert */
  val->t_char = rVar.xLimNegInv;
  break;

 case X_LIM_POS_INV:             /* 173 0xad x Positive limit Invert */
  val->t_char = rVar.xLimPosInv;
  break;

 case X_HOME_ENA:                /* 174 0xae x home enable */
  val->t_char = rVar.xHomeEna;
  break;

 case X_HOME_INV:                /* 175 0xaf x home invert */
  val->t_char = rVar.xHomeInv;
  break;

 case E_STOP_ENA:                /* 176 0xb0 enable estop */
  val->t_char = rVar.eStopEna;
  break;

 case E_STOP_INV:                /* 177 0xb1 invert estop signal */
  val->t_char = rVar.eStopInv;
  break;

 case CMD_PAUSED:                /* 178 0xb2 move commands paused */
  val->t_char = rVar.cmdPaused;
  break;

 case ARC_RADIUS:                /* 179 0xb3 arc radius */
  val->t_float = rVar.arcRadius;
  break;

 case ARC_X_CENTER:              /* 180 0xb4 arc x center */
  val->t_int = rVar.arcXCenter;
  break;

 case ARC_Z_CENTER:              /* 181 0xb5 arc z center */
  val->t_int = rVar.arcZCenter;
  break;

 case ARC_X_START:               /* 182 0xb6 arc x start */
  val->t_int = rVar.arcXStart;
  break;

 case ARC_Z_START:               /* 183 0xb7 arc z start */
  val->t_int = rVar.arcZStart;
  break;

 case ARC_X_END:                 /* 184 0xb8 arc x center */
  val->t_int = rVar.arcXEnd;
  break;

 case ARC_Z_END:                 /* 185 0xb9 arc z center */
  val->t_int = rVar.arcZEnd;
  break;

 case MEGA_VFD:                  /* 186 0xba mega vfd speed mode */
  val->t_char = rVar.megaVfd;
  break;

 case MEGA_SIM:                  /* 187 0xbb mega encoder lines */
  val->t_char = rVar.megaSim;
  break;

 case USB_ENA:                   /* 188 0xbc enable usb */
  val->t_char = rVar.usbEna;
  break;

 case MAX_PARM:                  /* 189 0xbd maximum parameter */
  val->t_int16_t = rVar.maxParm;
  break;

 }
}
