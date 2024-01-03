// c2File

#include <stdint.h>
#define NO_REM_MACROS
#include "remParm.h"
#include "remStruct.h"
#if !defined(EXT)
#define EXT extern
#endif
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
 sizeof(rVar.spJogTimeInitial) | FLT,   /* 0x0b spindle jog time initial */
 sizeof(rVar.spJogTimeInc) | FLT,       /* 0x0c spindle jog time increment */
 sizeof(rVar.spJogTimeMax) | FLT,       /* 0x0d spindle jog time max */
 sizeof(rVar.spJogDir),                 /* 0x0e spindle direction */
 sizeof(rVar.spDirInv),                 /* 0x0f spindle invert direction */
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
 sizeof(rVar.zDirInv),                  /* 0x1a z invert direction */
 sizeof(rVar.zMpgInv),                  /* 0x1b z invert mpg */

// x axis parameters

 sizeof(rVar.xPitch) | FLT,             /* 0x1c x axis leadscrew pitch */
 sizeof(rVar.xRatio) | FLT,             /* 0x1d x axis ratio */
 sizeof(rVar.xMicro),                   /* 0x1e x axis micro steps */
 sizeof(rVar.xMotor),                   /* 0x1f x axis motor steps */
 sizeof(rVar.xAccelTime) | FLT,         /* 0x20 x axis acceleration */
 sizeof(rVar.xAccel) | FLT,             /* 0x21 x accel rpm/sec^2 */
 sizeof(rVar.xBacklash) | FLT,          /* 0x22 x axis backlash */
 sizeof(rVar.xStepFactor),              /* 0x23 x steps inch factored */
 sizeof(rVar.xDirInv),                  /* 0x24 x invert direction */
 sizeof(rVar.xMpgInv),                  /* 0x25 x invert mpg */
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

// z limit test parameters

 sizeof(rVar.zTestLimitMin),            /* 0x55 z test limit minimum */
 sizeof(rVar.zTestLimitMax),            /* 0x56 z test limit maximum */
 sizeof(rVar.zTestHomeMin),             /* 0x57 z test home minimum */
 sizeof(rVar.zTestHomeMax),             /* 0x58 z test home maximum */
 sizeof(rVar.zTestProbe),               /* 0x59 z test probe */

// x home parameters

 sizeof(rVar.xHomeSpeed) | FLT,         /* 0x5a x final homing speed */
 sizeof(rVar.xHomeDist) | FLT,          /* 0x5b x max homing distance */
 sizeof(rVar.xHomeDistRev) | FLT,       /* 0x5c x max rev homing distance */
 sizeof(rVar.xHomeDistBackoff) | FLT,   /* 0x5d x home backoff dist */
 sizeof(rVar.xHomeDir),                 /* 0x5e x homing direction */

// x home test parameters

 sizeof(rVar.xHomeLoc),                 /* 0x5f x home test location */
 sizeof(rVar.xHomeStart),               /* 0x60 x start of home signal */
 sizeof(rVar.xHomeEnd),                 /* 0x61 x end of home signal */

// x limit test parameters

 sizeof(rVar.xTestLimitMin),            /* 0x62 x test limit minimum */
 sizeof(rVar.xTestLimitMax),            /* 0x63 x test limit maximum */
 sizeof(rVar.xTestHomeMin),             /* 0x64 x test home minimum */
 sizeof(rVar.xTestHomeMax),             /* 0x65 x test home maximum */
 sizeof(rVar.xTestProbe),               /* 0x66 x test probe */

// z dro

 sizeof(rVar.zDroLoc),                  /* 0x67 z dro location */
 sizeof(rVar.zDroOffset),               /* 0x68 z dro to zero */
 sizeof(rVar.zDroCountInch),            /* 0x69 z dro scale */
 sizeof(rVar.zDroFactor),               /* 0x6a x dro counts inch factored */
 sizeof(rVar.zDroInvert),               /* 0x6b z dro invert */
 sizeof(rVar.zUseDro),                  /* 0x6c z use dro for position */
 sizeof(rVar.zDoneDelay),               /* 0x6d z done to read dro delay */
 sizeof(rVar.zDroFinalDist),            /* 0x6e z final approach distance */

// x dro

 sizeof(rVar.xDroLoc),                  /* 0x6f x dro location */
 sizeof(rVar.xDroOffset),               /* 0x70 x dro to zero */
 sizeof(rVar.xDroCountInch),            /* 0x71 x dro scale */
 sizeof(rVar.xDroFactor),               /* 0x72 x dro counts inch factored */
 sizeof(rVar.xDroInvert),               /* 0x73 x dro invert */
 sizeof(rVar.xUseDro),                  /* 0x74 x use dro for position */
 sizeof(rVar.xDoneDelay),               /* 0x75 x done to read dro delay */
 sizeof(rVar.xDroFinalDist),            /* 0x76 x final approach distance */

// x home or probe status

 sizeof(rVar.xHomeStatus),              /* 0x77 x home status */

// Z home or probe status

 sizeof(rVar.zHomeStatus),              /* 0x78 z home status */

// probe configuration

 sizeof(rVar.probeSpeed) | FLT,         /* 0x79 probe speed */
 sizeof(rVar.probeDist),                /* 0x7a probe test distance */
 sizeof(rVar.probeInv),                 /* 0x7b invert polarity of probe */

// configuration

 sizeof(rVar.stepperDrive),             /* 0x7c stepper driven spindle */
 sizeof(rVar.motorTest),                /* 0x7d use stepper to test motor */
 sizeof(rVar.spindleEncoder),           /* 0x7e motor with spindle enc */
 sizeof(rVar.spindleSyncBoard),         /* 0x7f spindle sync board */
 sizeof(rVar.spindleInternalSync),      /* 0x80 spindle internal sync */
 sizeof(rVar.turnSync),                 /* 0x81 sync type for turning */
 sizeof(rVar.threadSync),               /* 0x82 sync type for threading */
 sizeof(rVar.runoutSync),               /* 0x83 sync type for runout */
 sizeof(rVar.capTmrEnable),             /* 0x84 enable capture timer */
 sizeof(rVar.cfgFpga),                  /* 0x85 using fpga */
 sizeof(rVar.cfgMega),                  /* 0x86 control link to mega */
 sizeof(rVar.cfgMpg),                   /* 0x87 manual pulse generator */
 sizeof(rVar.cfgDro),                   /* 0x88 digital readout */
 sizeof(rVar.cfgLcd),                   /* 0x89 lcd display */
 sizeof(rVar.cfgFcy),                   /* 0x8a system clock speed */
 sizeof(rVar.cfgSwitch),                /* 0x8b spindle off on switch */
 sizeof(rVar.cfgVarSpeed),              /* 0x8c spindle variable speed */

// setup

 sizeof(rVar.setupDone),                /* 0x8d setup done */

// encoder counts per revolution

 sizeof(rVar.encPerRev),                /* 0x8e spindle enc counts per rev */

// test encoder setup variables

 sizeof(rVar.encEnable),                /* 0x8f encoder enable flag */
 sizeof(rVar.encPreScaler),             /* 0x90 encoder prescaler */
 sizeof(rVar.encTimer),                 /* 0x91 encoder timer counts */
 sizeof(rVar.encRunCount),              /* 0x92 encoder run count */

// test encoder status variables

 sizeof(rVar.encRun),                   /* 0x93 encoder running flag */
 sizeof(rVar.encCounter),               /* 0x94 encoder count in rev */
 sizeof(rVar.encRevCounter),            /* 0x95 encoder revolution counter */

// measured spindle speed

 sizeof(rVar.rpm),                      /* 0x96 current measured rpm */

// fpga frequency variables

 sizeof(rVar.fpgaFrequency),            /* 0x97 fpga clock frequency */
 sizeof(rVar.freqMult),                 /* 0x98 frequency multiplier */

// xilinx configuration register

 sizeof(rVar.xCfgReg),                  /* 0x99 xilinx cfg register */

// z sync parameters

 sizeof(rVar.lSyncCycle),               /* 0x9a sync cycle length */
 sizeof(rVar.lSyncOutput),              /* 0x9b sync outputs per cycle */
 sizeof(rVar.lSyncInPreScaler),         /* 0x9c input sync prescaler */
 sizeof(rVar.lSyncOutPreScaler),        /* 0x9d output sync prescaler */

// x sync parameters

 sizeof(rVar.lXSyncCycle),              /* 0x9e sync cycle length */
 sizeof(rVar.lXSyncOutput),             /* 0x9f sync outputs per cycle */
 sizeof(rVar.lXSyncInPreScaler),        /* 0xa0 input sync prescaler */
 sizeof(rVar.lXSyncOutPreScaler),       /* 0xa1 output sync prescaler */

// threading variables

 sizeof(rVar.thZStart),                 /* 0xa2 threading z start */
 sizeof(rVar.thXStart),                 /* 0xa3 threading x start */
 sizeof(rVar.tanThreadAngle) | FLT,     /* 0xa4 tan of threading angle */
 sizeof(rVar.xFeed),                    /* 0xa5 x feed */
 sizeof(rVar.runoutLimit),              /* 0xa6 encoder steps to runout */
 sizeof(rVar.runoutDistance) | FLT,     /* 0xa7 runout distance */
 sizeof(rVar.runoutDepth) | FLT,        /* 0xa8 runout depth */

// jog debug

 sizeof(rVar.jogDebug),                 /* 0xa9 jog interrupt debug */

// motor and speed control

 sizeof(rVar.pwmFreq),                  /* 0xaa spindle speed pwm frequency */
 sizeof(rVar.minSpeed),                 /* 0xab min speed for current range */
 sizeof(rVar.maxSpeed),                 /* 0xac max speed for current range */

// current operation

 sizeof(rVar.currentOp),                /* 0xad current operation */

// global limits and home

 sizeof(rVar.limitOverride),            /* 0xae override limit switches */
 sizeof(rVar.commonLimits),             /* 0xaf all limit switches one pin */
 sizeof(rVar.limitsEnabled),            /* 0xb0 limits enabled */
 sizeof(rVar.commonHome),               /* 0xb1 all home switches one pin */

// z limits and home

 sizeof(rVar.zLimEna),                  /* 0xb2 z limit enable */
 sizeof(rVar.zLimNegInv),               /* 0xb3 z negative limit invert */
 sizeof(rVar.zLimPosInv),               /* 0xb4 z Positive limit Invert */
 sizeof(rVar.zHomeEna),                 /* 0xb5 z home enable */
 sizeof(rVar.zHomeInv),                 /* 0xb6 z home invert */

// x limits and home

 sizeof(rVar.xLimEna),                  /* 0xb7 x limit enable */
 sizeof(rVar.xLimNegInv),               /* 0xb8 x negative limit invert */
 sizeof(rVar.xLimPosInv),               /* 0xb9 x Positive limit Invert */
 sizeof(rVar.xHomeEna),                 /* 0xba x home enable */
 sizeof(rVar.xHomeInv),                 /* 0xbb x home invert */

// e stop

 sizeof(rVar.eStopEna),                 /* 0xbc enable estop */
 sizeof(rVar.eStopInv),                 /* 0xbd invert estop signal */

// command pause

 sizeof(rVar.cmdPaused),                /* 0xbe move commands paused */

// arc parameters

 sizeof(rVar.arcRadius) | FLT,          /* 0xbf arc radius */
 sizeof(rVar.arcXCenter),               /* 0xc0 arc x center */
 sizeof(rVar.arcZCenter),               /* 0xc1 arc z center */
 sizeof(rVar.arcXStart),                /* 0xc2 arc x start */
 sizeof(rVar.arcZStart),                /* 0xc3 arc z start */
 sizeof(rVar.arcXEnd),                  /* 0xc4 arc x center */
 sizeof(rVar.arcZEnd),                  /* 0xc5 arc z center */
 sizeof(rVar.megaVfd),                  /* 0xc6 mega vfd speed mode */
 sizeof(rVar.megaSim),                  /* 0xc7 mega encoder lines */
 sizeof(rVar.usbEna),                   /* 0xc8 enable usb */
 sizeof(rVar.droStep),                  /* 0xc9 step pulse drives dro */
 sizeof(rVar.maxParm),                  /* 0xca maximum parameter */
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

 case SP_JOG_TIME_INITIAL:       /* 11 0x0b spindle jog time initial */
  rVar.spJogTimeInitial = val.t_float;
  break;

 case SP_JOG_TIME_INC:           /* 12 0x0c spindle jog time increment */
  rVar.spJogTimeInc = val.t_float;
  break;

 case SP_JOG_TIME_MAX:           /* 13 0x0d spindle jog time max */
  rVar.spJogTimeMax = val.t_float;
  break;

 case SP_JOG_DIR:                /* 14 0x0e spindle direction */
  rVar.spJogDir = val.t_char;
  break;

 case SP_DIR_INV:                /* 15 0x0f spindle invert direction */
  rVar.spDirInv = val.t_char;
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

 case Z_DIR_INV:                 /* 26 0x1a z invert direction */
  rVar.zDirInv = val.t_char;
  break;

 case Z_MPG_INV:                 /* 27 0x1b z invert mpg */
  rVar.zMpgInv = val.t_char;
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

 case X_DIR_INV:                 /* 36 0x24 x invert direction */
  rVar.xDirInv = val.t_char;
  break;

 case X_MPG_INV:                 /* 37 0x25 x invert mpg */
  rVar.xMpgInv = val.t_char;
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

 case Z_TEST_LIMIT_MIN:          /* 85 0x55 z test limit minimum */
  rVar.zTestLimitMin = val.t_int;
  break;

 case Z_TEST_LIMIT_MAX:          /* 86 0x56 z test limit maximum */
  rVar.zTestLimitMax = val.t_int;
  break;

 case Z_TEST_HOME_MIN:           /* 87 0x57 z test home minimum */
  rVar.zTestHomeMin = val.t_int;
  break;

 case Z_TEST_HOME_MAX:           /* 88 0x58 z test home maximum */
  rVar.zTestHomeMax = val.t_int;
  break;

 case Z_TEST_PROBE:              /* 89 0x59 z test probe */
  rVar.zTestProbe = val.t_int;
  break;

 case X_HOME_SPEED:              /* 90 0x5a x final homing speed */
  rVar.xHomeSpeed = val.t_float;
  break;

 case X_HOME_DIST:               /* 91 0x5b x max homing distance */
  rVar.xHomeDist = val.t_float;
  break;

 case X_HOME_DIST_REV:           /* 92 0x5c x max rev homing distance */
  rVar.xHomeDistRev = val.t_float;
  break;

 case X_HOME_DIST_BACKOFF:       /* 93 0x5d x home backoff dist */
  rVar.xHomeDistBackoff = val.t_float;
  break;

 case X_HOME_DIR:                /* 94 0x5e x homing direction */
  rVar.xHomeDir = val.t_int;
  break;

 case X_HOME_LOC:                /* 95 0x5f x home test location */
  rVar.xHomeLoc = val.t_int;
  break;

 case X_HOME_START:              /* 96 0x60 x start of home signal */
  rVar.xHomeStart = val.t_int;
  break;

 case X_HOME_END:                /* 97 0x61 x end of home signal */
  rVar.xHomeEnd = val.t_int;
  break;

 case X_TEST_LIMIT_MIN:          /* 98 0x62 x test limit minimum */
  rVar.xTestLimitMin = val.t_int;
  break;

 case X_TEST_LIMIT_MAX:          /* 99 0x63 x test limit maximum */
  rVar.xTestLimitMax = val.t_int;
  break;

 case X_TEST_HOME_MIN:           /* 100 0x64 x test home minimum */
  rVar.xTestHomeMin = val.t_int;
  break;

 case X_TEST_HOME_MAX:           /* 101 0x65 x test home maximum */
  rVar.xTestHomeMax = val.t_int;
  break;

 case X_TEST_PROBE:              /* 102 0x66 x test probe */
  rVar.xTestProbe = val.t_int;
  break;

 case Z_DRO_LOC:                 /* 103 0x67 z dro location */
  rVar.zDroLoc = val.t_int;
  break;

 case Z_DRO_OFFSET:              /* 104 0x68 z dro to zero */
  rVar.zDroOffset = val.t_int;
  break;

 case Z_DRO_COUNT_INCH:          /* 105 0x69 z dro scale */
  rVar.zDroCountInch = val.t_int;
  break;

 case Z_DRO_FACTOR:              /* 106 0x6a x dro counts inch factored */
  rVar.zDroFactor = val.t_int;
  break;

 case Z_DRO_INVERT:              /* 107 0x6b z dro invert */
  rVar.zDroInvert = val.t_int;
  break;

 case Z_USE_DRO:                 /* 108 0x6c z use dro for position */
  rVar.zUseDro = val.t_char;
  break;

 case Z_DONE_DELAY:              /* 109 0x6d z done to read dro delay */
  rVar.zDoneDelay = val.t_int;
  break;

 case Z_DRO_FINAL_DIST:          /* 110 0x6e z final approach distance */
  rVar.zDroFinalDist = val.t_int;
  break;

 case X_DRO_LOC:                 /* 111 0x6f x dro location */
  rVar.xDroLoc = val.t_int;
  break;

 case X_DRO_OFFSET:              /* 112 0x70 x dro to zero */
  rVar.xDroOffset = val.t_int;
  break;

 case X_DRO_COUNT_INCH:          /* 113 0x71 x dro scale */
  rVar.xDroCountInch = val.t_int;
  break;

 case X_DRO_FACTOR:              /* 114 0x72 x dro counts inch factored */
  rVar.xDroFactor = val.t_int;
  break;

 case X_DRO_INVERT:              /* 115 0x73 x dro invert */
  rVar.xDroInvert = val.t_int;
  break;

 case X_USE_DRO:                 /* 116 0x74 x use dro for position */
  rVar.xUseDro = val.t_char;
  break;

 case X_DONE_DELAY:              /* 117 0x75 x done to read dro delay */
  rVar.xDoneDelay = val.t_int;
  break;

 case X_DRO_FINAL_DIST:          /* 118 0x76 x final approach distance */
  rVar.xDroFinalDist = val.t_int;
  break;

 case X_HOME_STATUS:             /* 119 0x77 x home status */
  rVar.xHomeStatus = val.t_int;
  break;

 case Z_HOME_STATUS:             /* 120 0x78 z home status */
  rVar.zHomeStatus = val.t_int;
  break;

 case PROBE_SPEED:               /* 121 0x79 probe speed */
  rVar.probeSpeed = val.t_float;
  break;

 case PROBE_DIST:                /* 122 0x7a probe test distance */
  rVar.probeDist = val.t_int;
  break;

 case PROBE_INV:                 /* 123 0x7b invert polarity of probe */
  rVar.probeInv = val.t_int;
  break;

 case STEPPER_DRIVE:             /* 124 0x7c stepper driven spindle */
  rVar.stepperDrive = val.t_char;
  break;

 case MOTOR_TEST:                /* 125 0x7d use stepper to test motor */
  rVar.motorTest = val.t_char;
  break;

 case SPINDLE_ENCODER:           /* 126 0x7e motor with spindle enc */
  rVar.spindleEncoder = val.t_char;
  break;

 case SPINDLE_SYNC_BOARD:        /* 127 0x7f spindle sync board */
  rVar.spindleSyncBoard = val.t_char;
  break;

 case SPINDLE_INTERNAL_SYNC:     /* 128 0x80 spindle internal sync */
  rVar.spindleInternalSync = val.t_char;
  break;

 case TURN_SYNC:                 /* 129 0x81 sync type for turning */
  rVar.turnSync = val.t_char;
  break;

 case THREAD_SYNC:               /* 130 0x82 sync type for threading */
  rVar.threadSync = val.t_char;
  break;

 case RUNOUT_SYNC:               /* 131 0x83 sync type for runout */
  rVar.runoutSync = val.t_char;
  break;

 case CAP_TMR_ENABLE:            /* 132 0x84 enable capture timer */
  rVar.capTmrEnable = val.t_char;
  break;

 case CFG_FPGA:                  /* 133 0x85 using fpga */
  rVar.cfgFpga = val.t_char;
  break;

 case CFG_MEGA:                  /* 134 0x86 control link to mega */
  rVar.cfgMega = val.t_char;
  break;

 case CFG_MPG:                   /* 135 0x87 manual pulse generator */
  rVar.cfgMpg = val.t_char;
  break;

 case CFG_DRO:                   /* 136 0x88 digital readout */
  rVar.cfgDro = val.t_char;
  break;

 case CFG_LCD:                   /* 137 0x89 lcd display */
  rVar.cfgLcd = val.t_char;
  break;

 case CFG_FCY:                   /* 138 0x8a system clock speed */
  rVar.cfgFcy = val.t_uint_t;
  break;

 case CFG_SWITCH:                /* 139 0x8b spindle off on switch */
  rVar.cfgSwitch = val.t_int;
  break;

 case CFG_VAR_SPEED:             /* 140 0x8c spindle variable speed */
  rVar.cfgVarSpeed = val.t_int;
  break;

 case SETUP_DONE:                /* 141 0x8d setup done */
  rVar.setupDone = val.t_char;
  break;

 case ENC_PER_REV:               /* 142 0x8e spindle enc counts per rev */
  rVar.encPerRev = val.t_uint16_t;
  break;

 case ENC_ENABLE:                /* 143 0x8f encoder enable flag */
  rVar.encEnable = val.t_char;
  break;

 case ENC_PRE_SCALER:            /* 144 0x90 encoder prescaler */
  rVar.encPreScaler = val.t_uint16_t;
  break;

 case ENC_TIMER:                 /* 145 0x91 encoder timer counts */
  rVar.encTimer = val.t_uint16_t;
  break;

 case ENC_RUN_COUNT:             /* 146 0x92 encoder run count */
  rVar.encRunCount = val.t_int;
  break;

 case ENC_RUN:                   /* 147 0x93 encoder running flag */
  rVar.encRun = val.t_char;
  break;

 case ENC_COUNTER:               /* 148 0x94 encoder count in rev */
  rVar.encCounter = val.t_int16_t;
  break;

 case ENC_REV_COUNTER:           /* 149 0x95 encoder revolution counter */
  rVar.encRevCounter = val.t_int32_t;
  break;

 case RPM:                       /* 150 0x96 current measured rpm */
  rVar.rpm = val.t_int16_t;
  break;

 case FPGA_FREQUENCY:            /* 151 0x97 fpga clock frequency */
  rVar.fpgaFrequency = val.t_int32_t;
  break;

 case FREQ_MULT:                 /* 152 0x98 frequency multiplier */
  rVar.freqMult = val.t_int16_t;
  break;

 case X_CFG_REG:                 /* 153 0x99 xilinx cfg register */
  rVar.xCfgReg = val.t_int16_t;
  break;

 case L_SYNC_CYCLE:              /* 154 0x9a sync cycle length */
  rVar.lSyncCycle = val.t_uint16_t;
  break;

 case L_SYNC_OUTPUT:             /* 155 0x9b sync outputs per cycle */
  rVar.lSyncOutput = val.t_uint16_t;
  break;

 case L_SYNC_IN_PRE_SCALER:      /* 156 0x9c input sync prescaler */
  rVar.lSyncInPreScaler = val.t_uint16_t;
  break;

 case L_SYNC_OUT_PRE_SCALER:     /* 157 0x9d output sync prescaler */
  rVar.lSyncOutPreScaler = val.t_uint16_t;
  break;

 case L_X_SYNC_CYCLE:            /* 158 0x9e sync cycle length */
  rVar.lXSyncCycle = val.t_uint16_t;
  break;

 case L_X_SYNC_OUTPUT:           /* 159 0x9f sync outputs per cycle */
  rVar.lXSyncOutput = val.t_uint16_t;
  break;

 case L_X_SYNC_IN_PRE_SCALER:    /* 160 0xa0 input sync prescaler */
  rVar.lXSyncInPreScaler = val.t_uint16_t;
  break;

 case L_X_SYNC_OUT_PRE_SCALER:   /* 161 0xa1 output sync prescaler */
  rVar.lXSyncOutPreScaler = val.t_uint16_t;
  break;

 case TH_Z_START:                /* 162 0xa2 threading z start */
  rVar.thZStart = val.t_int32_t;
  break;

 case TH_X_START:                /* 163 0xa3 threading x start */
  rVar.thXStart = val.t_int32_t;
  break;

 case TAN_THREAD_ANGLE:          /* 164 0xa4 tan of threading angle */
  rVar.tanThreadAngle = val.t_float;
  break;

 case X_FEED:                    /* 165 0xa5 x feed */
  rVar.xFeed = val.t_int32_t;
  break;

 case RUNOUT_LIMIT:              /* 166 0xa6 encoder steps to runout */
  rVar.runoutLimit = val.t_int;
  break;

 case RUNOUT_DISTANCE:           /* 167 0xa7 runout distance */
  rVar.runoutDistance = val.t_float;
  break;

 case RUNOUT_DEPTH:              /* 168 0xa8 runout depth */
  rVar.runoutDepth = val.t_float;
  break;

 case JOG_DEBUG:                 /* 169 0xa9 jog interrupt debug */
  rVar.jogDebug = val.t_char;
  break;

 case PWM_FREQ:                  /* 170 0xaa spindle speed pwm frequency */
  rVar.pwmFreq = val.t_uint_t;
  break;

 case MIN_SPEED:                 /* 171 0xab min speed for current range */
  rVar.minSpeed = val.t_int16_t;
  break;

 case MAX_SPEED:                 /* 172 0xac max speed for current range */
  rVar.maxSpeed = val.t_int16_t;
  break;

 case CURRENT_OP:                /* 173 0xad current operation */
  rVar.currentOp = val.t_char;
  break;

 case LIMIT_OVERRIDE:            /* 174 0xae override limit switches */
  rVar.limitOverride = val.t_char;
  break;

 case COMMON_LIMITS:             /* 175 0xaf all limit switches one pin */
  rVar.commonLimits = val.t_char;
  break;

 case LIMITS_ENABLED:            /* 176 0xb0 limits enabled */
  rVar.limitsEnabled = val.t_char;
  break;

 case COMMON_HOME:               /* 177 0xb1 all home switches one pin */
  rVar.commonHome = val.t_char;
  break;

 case Z_LIM_ENA:                 /* 178 0xb2 z limit enable */
  rVar.zLimEna = val.t_char;
  break;

 case Z_LIM_NEG_INV:             /* 179 0xb3 z negative limit invert */
  rVar.zLimNegInv = val.t_char;
  break;

 case Z_LIM_POS_INV:             /* 180 0xb4 z Positive limit Invert */
  rVar.zLimPosInv = val.t_char;
  break;

 case Z_HOME_ENA:                /* 181 0xb5 z home enable */
  rVar.zHomeEna = val.t_char;
  break;

 case Z_HOME_INV:                /* 182 0xb6 z home invert */
  rVar.zHomeInv = val.t_char;
  break;

 case X_LIM_ENA:                 /* 183 0xb7 x limit enable */
  rVar.xLimEna = val.t_char;
  break;

 case X_LIM_NEG_INV:             /* 184 0xb8 x negative limit invert */
  rVar.xLimNegInv = val.t_char;
  break;

 case X_LIM_POS_INV:             /* 185 0xb9 x Positive limit Invert */
  rVar.xLimPosInv = val.t_char;
  break;

 case X_HOME_ENA:                /* 186 0xba x home enable */
  rVar.xHomeEna = val.t_char;
  break;

 case X_HOME_INV:                /* 187 0xbb x home invert */
  rVar.xHomeInv = val.t_char;
  break;

 case E_STOP_ENA:                /* 188 0xbc enable estop */
  rVar.eStopEna = val.t_char;
  break;

 case E_STOP_INV:                /* 189 0xbd invert estop signal */
  rVar.eStopInv = val.t_char;
  break;

 case CMD_PAUSED:                /* 190 0xbe move commands paused */
  rVar.cmdPaused = val.t_char;
  break;

 case ARC_RADIUS:                /* 191 0xbf arc radius */
  rVar.arcRadius = val.t_float;
  break;

 case ARC_X_CENTER:              /* 192 0xc0 arc x center */
  rVar.arcXCenter = val.t_int;
  break;

 case ARC_Z_CENTER:              /* 193 0xc1 arc z center */
  rVar.arcZCenter = val.t_int;
  break;

 case ARC_X_START:               /* 194 0xc2 arc x start */
  rVar.arcXStart = val.t_int;
  break;

 case ARC_Z_START:               /* 195 0xc3 arc z start */
  rVar.arcZStart = val.t_int;
  break;

 case ARC_X_END:                 /* 196 0xc4 arc x center */
  rVar.arcXEnd = val.t_int;
  break;

 case ARC_Z_END:                 /* 197 0xc5 arc z center */
  rVar.arcZEnd = val.t_int;
  break;

 case MEGA_VFD:                  /* 198 0xc6 mega vfd speed mode */
  rVar.megaVfd = val.t_char;
  break;

 case MEGA_SIM:                  /* 199 0xc7 mega encoder lines */
  rVar.megaSim = val.t_char;
  break;

 case USB_ENA:                   /* 200 0xc8 enable usb */
  rVar.usbEna = val.t_char;
  break;

 case DRO_STEP:                  /* 201 0xc9 step pulse drives dro */
  rVar.droStep = val.t_char;
  break;

 case MAX_PARM:                  /* 202 0xca maximum parameter */
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

 case SP_JOG_TIME_INITIAL:       /* 11 0x0b spindle jog time initial */
  val->t_float = rVar.spJogTimeInitial;
  break;

 case SP_JOG_TIME_INC:           /* 12 0x0c spindle jog time increment */
  val->t_float = rVar.spJogTimeInc;
  break;

 case SP_JOG_TIME_MAX:           /* 13 0x0d spindle jog time max */
  val->t_float = rVar.spJogTimeMax;
  break;

 case SP_JOG_DIR:                /* 14 0x0e spindle direction */
  val->t_char = rVar.spJogDir;
  break;

 case SP_DIR_INV:                /* 15 0x0f spindle invert direction */
  val->t_char = rVar.spDirInv;
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

 case Z_DIR_INV:                 /* 26 0x1a z invert direction */
  val->t_char = rVar.zDirInv;
  break;

 case Z_MPG_INV:                 /* 27 0x1b z invert mpg */
  val->t_char = rVar.zMpgInv;
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

 case X_DIR_INV:                 /* 36 0x24 x invert direction */
  val->t_char = rVar.xDirInv;
  break;

 case X_MPG_INV:                 /* 37 0x25 x invert mpg */
  val->t_char = rVar.xMpgInv;
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

 case Z_TEST_LIMIT_MIN:          /* 85 0x55 z test limit minimum */
  val->t_int = rVar.zTestLimitMin;
  break;

 case Z_TEST_LIMIT_MAX:          /* 86 0x56 z test limit maximum */
  val->t_int = rVar.zTestLimitMax;
  break;

 case Z_TEST_HOME_MIN:           /* 87 0x57 z test home minimum */
  val->t_int = rVar.zTestHomeMin;
  break;

 case Z_TEST_HOME_MAX:           /* 88 0x58 z test home maximum */
  val->t_int = rVar.zTestHomeMax;
  break;

 case Z_TEST_PROBE:              /* 89 0x59 z test probe */
  val->t_int = rVar.zTestProbe;
  break;

 case X_HOME_SPEED:              /* 90 0x5a x final homing speed */
  val->t_float = rVar.xHomeSpeed;
  break;

 case X_HOME_DIST:               /* 91 0x5b x max homing distance */
  val->t_float = rVar.xHomeDist;
  break;

 case X_HOME_DIST_REV:           /* 92 0x5c x max rev homing distance */
  val->t_float = rVar.xHomeDistRev;
  break;

 case X_HOME_DIST_BACKOFF:       /* 93 0x5d x home backoff dist */
  val->t_float = rVar.xHomeDistBackoff;
  break;

 case X_HOME_DIR:                /* 94 0x5e x homing direction */
  val->t_int = rVar.xHomeDir;
  break;

 case X_HOME_LOC:                /* 95 0x5f x home test location */
  val->t_int = rVar.xHomeLoc;
  break;

 case X_HOME_START:              /* 96 0x60 x start of home signal */
  val->t_int = rVar.xHomeStart;
  break;

 case X_HOME_END:                /* 97 0x61 x end of home signal */
  val->t_int = rVar.xHomeEnd;
  break;

 case X_TEST_LIMIT_MIN:          /* 98 0x62 x test limit minimum */
  val->t_int = rVar.xTestLimitMin;
  break;

 case X_TEST_LIMIT_MAX:          /* 99 0x63 x test limit maximum */
  val->t_int = rVar.xTestLimitMax;
  break;

 case X_TEST_HOME_MIN:           /* 100 0x64 x test home minimum */
  val->t_int = rVar.xTestHomeMin;
  break;

 case X_TEST_HOME_MAX:           /* 101 0x65 x test home maximum */
  val->t_int = rVar.xTestHomeMax;
  break;

 case X_TEST_PROBE:              /* 102 0x66 x test probe */
  val->t_int = rVar.xTestProbe;
  break;

 case Z_DRO_LOC:                 /* 103 0x67 z dro location */
  val->t_int = rVar.zDroLoc;
  break;

 case Z_DRO_OFFSET:              /* 104 0x68 z dro to zero */
  val->t_int = rVar.zDroOffset;
  break;

 case Z_DRO_COUNT_INCH:          /* 105 0x69 z dro scale */
  val->t_int = rVar.zDroCountInch;
  break;

 case Z_DRO_FACTOR:              /* 106 0x6a x dro counts inch factored */
  val->t_int = rVar.zDroFactor;
  break;

 case Z_DRO_INVERT:              /* 107 0x6b z dro invert */
  val->t_int = rVar.zDroInvert;
  break;

 case Z_USE_DRO:                 /* 108 0x6c z use dro for position */
  val->t_char = rVar.zUseDro;
  break;

 case Z_DONE_DELAY:              /* 109 0x6d z done to read dro delay */
  val->t_int = rVar.zDoneDelay;
  break;

 case Z_DRO_FINAL_DIST:          /* 110 0x6e z final approach distance */
  val->t_int = rVar.zDroFinalDist;
  break;

 case X_DRO_LOC:                 /* 111 0x6f x dro location */
  val->t_int = rVar.xDroLoc;
  break;

 case X_DRO_OFFSET:              /* 112 0x70 x dro to zero */
  val->t_int = rVar.xDroOffset;
  break;

 case X_DRO_COUNT_INCH:          /* 113 0x71 x dro scale */
  val->t_int = rVar.xDroCountInch;
  break;

 case X_DRO_FACTOR:              /* 114 0x72 x dro counts inch factored */
  val->t_int = rVar.xDroFactor;
  break;

 case X_DRO_INVERT:              /* 115 0x73 x dro invert */
  val->t_int = rVar.xDroInvert;
  break;

 case X_USE_DRO:                 /* 116 0x74 x use dro for position */
  val->t_char = rVar.xUseDro;
  break;

 case X_DONE_DELAY:              /* 117 0x75 x done to read dro delay */
  val->t_int = rVar.xDoneDelay;
  break;

 case X_DRO_FINAL_DIST:          /* 118 0x76 x final approach distance */
  val->t_int = rVar.xDroFinalDist;
  break;

 case X_HOME_STATUS:             /* 119 0x77 x home status */
  val->t_int = rVar.xHomeStatus;
  break;

 case Z_HOME_STATUS:             /* 120 0x78 z home status */
  val->t_int = rVar.zHomeStatus;
  break;

 case PROBE_SPEED:               /* 121 0x79 probe speed */
  val->t_float = rVar.probeSpeed;
  break;

 case PROBE_DIST:                /* 122 0x7a probe test distance */
  val->t_int = rVar.probeDist;
  break;

 case PROBE_INV:                 /* 123 0x7b invert polarity of probe */
  val->t_int = rVar.probeInv;
  break;

 case STEPPER_DRIVE:             /* 124 0x7c stepper driven spindle */
  val->t_char = rVar.stepperDrive;
  break;

 case MOTOR_TEST:                /* 125 0x7d use stepper to test motor */
  val->t_char = rVar.motorTest;
  break;

 case SPINDLE_ENCODER:           /* 126 0x7e motor with spindle enc */
  val->t_char = rVar.spindleEncoder;
  break;

 case SPINDLE_SYNC_BOARD:        /* 127 0x7f spindle sync board */
  val->t_char = rVar.spindleSyncBoard;
  break;

 case SPINDLE_INTERNAL_SYNC:     /* 128 0x80 spindle internal sync */
  val->t_char = rVar.spindleInternalSync;
  break;

 case TURN_SYNC:                 /* 129 0x81 sync type for turning */
  val->t_char = rVar.turnSync;
  break;

 case THREAD_SYNC:               /* 130 0x82 sync type for threading */
  val->t_char = rVar.threadSync;
  break;

 case RUNOUT_SYNC:               /* 131 0x83 sync type for runout */
  val->t_char = rVar.runoutSync;
  break;

 case CAP_TMR_ENABLE:            /* 132 0x84 enable capture timer */
  val->t_char = rVar.capTmrEnable;
  break;

 case CFG_FPGA:                  /* 133 0x85 using fpga */
  val->t_char = rVar.cfgFpga;
  break;

 case CFG_MEGA:                  /* 134 0x86 control link to mega */
  val->t_char = rVar.cfgMega;
  break;

 case CFG_MPG:                   /* 135 0x87 manual pulse generator */
  val->t_char = rVar.cfgMpg;
  break;

 case CFG_DRO:                   /* 136 0x88 digital readout */
  val->t_char = rVar.cfgDro;
  break;

 case CFG_LCD:                   /* 137 0x89 lcd display */
  val->t_char = rVar.cfgLcd;
  break;

 case CFG_FCY:                   /* 138 0x8a system clock speed */
  val->t_uint_t = rVar.cfgFcy;
  break;

 case CFG_SWITCH:                /* 139 0x8b spindle off on switch */
  val->t_int = rVar.cfgSwitch;
  break;

 case CFG_VAR_SPEED:             /* 140 0x8c spindle variable speed */
  val->t_int = rVar.cfgVarSpeed;
  break;

 case SETUP_DONE:                /* 141 0x8d setup done */
  val->t_char = rVar.setupDone;
  break;

 case ENC_PER_REV:               /* 142 0x8e spindle enc counts per rev */
  val->t_uint16_t = rVar.encPerRev;
  break;

 case ENC_ENABLE:                /* 143 0x8f encoder enable flag */
  val->t_char = rVar.encEnable;
  break;

 case ENC_PRE_SCALER:            /* 144 0x90 encoder prescaler */
  val->t_uint16_t = rVar.encPreScaler;
  break;

 case ENC_TIMER:                 /* 145 0x91 encoder timer counts */
  val->t_uint16_t = rVar.encTimer;
  break;

 case ENC_RUN_COUNT:             /* 146 0x92 encoder run count */
  val->t_int = rVar.encRunCount;
  break;

 case ENC_RUN:                   /* 147 0x93 encoder running flag */
  val->t_char = rVar.encRun;
  break;

 case ENC_COUNTER:               /* 148 0x94 encoder count in rev */
  val->t_int16_t = rVar.encCounter;
  break;

 case ENC_REV_COUNTER:           /* 149 0x95 encoder revolution counter */
  val->t_int32_t = rVar.encRevCounter;
  break;

 case RPM:                       /* 150 0x96 current measured rpm */
  val->t_int16_t = rVar.rpm;
  break;

 case FPGA_FREQUENCY:            /* 151 0x97 fpga clock frequency */
  val->t_int32_t = rVar.fpgaFrequency;
  break;

 case FREQ_MULT:                 /* 152 0x98 frequency multiplier */
  val->t_int16_t = rVar.freqMult;
  break;

 case X_CFG_REG:                 /* 153 0x99 xilinx cfg register */
  val->t_int16_t = rVar.xCfgReg;
  break;

 case L_SYNC_CYCLE:              /* 154 0x9a sync cycle length */
  val->t_uint16_t = rVar.lSyncCycle;
  break;

 case L_SYNC_OUTPUT:             /* 155 0x9b sync outputs per cycle */
  val->t_uint16_t = rVar.lSyncOutput;
  break;

 case L_SYNC_IN_PRE_SCALER:      /* 156 0x9c input sync prescaler */
  val->t_uint16_t = rVar.lSyncInPreScaler;
  break;

 case L_SYNC_OUT_PRE_SCALER:     /* 157 0x9d output sync prescaler */
  val->t_uint16_t = rVar.lSyncOutPreScaler;
  break;

 case L_X_SYNC_CYCLE:            /* 158 0x9e sync cycle length */
  val->t_uint16_t = rVar.lXSyncCycle;
  break;

 case L_X_SYNC_OUTPUT:           /* 159 0x9f sync outputs per cycle */
  val->t_uint16_t = rVar.lXSyncOutput;
  break;

 case L_X_SYNC_IN_PRE_SCALER:    /* 160 0xa0 input sync prescaler */
  val->t_uint16_t = rVar.lXSyncInPreScaler;
  break;

 case L_X_SYNC_OUT_PRE_SCALER:   /* 161 0xa1 output sync prescaler */
  val->t_uint16_t = rVar.lXSyncOutPreScaler;
  break;

 case TH_Z_START:                /* 162 0xa2 threading z start */
  val->t_int32_t = rVar.thZStart;
  break;

 case TH_X_START:                /* 163 0xa3 threading x start */
  val->t_int32_t = rVar.thXStart;
  break;

 case TAN_THREAD_ANGLE:          /* 164 0xa4 tan of threading angle */
  val->t_float = rVar.tanThreadAngle;
  break;

 case X_FEED:                    /* 165 0xa5 x feed */
  val->t_int32_t = rVar.xFeed;
  break;

 case RUNOUT_LIMIT:              /* 166 0xa6 encoder steps to runout */
  val->t_int = rVar.runoutLimit;
  break;

 case RUNOUT_DISTANCE:           /* 167 0xa7 runout distance */
  val->t_float = rVar.runoutDistance;
  break;

 case RUNOUT_DEPTH:              /* 168 0xa8 runout depth */
  val->t_float = rVar.runoutDepth;
  break;

 case JOG_DEBUG:                 /* 169 0xa9 jog interrupt debug */
  val->t_char = rVar.jogDebug;
  break;

 case PWM_FREQ:                  /* 170 0xaa spindle speed pwm frequency */
  val->t_uint_t = rVar.pwmFreq;
  break;

 case MIN_SPEED:                 /* 171 0xab min speed for current range */
  val->t_int16_t = rVar.minSpeed;
  break;

 case MAX_SPEED:                 /* 172 0xac max speed for current range */
  val->t_int16_t = rVar.maxSpeed;
  break;

 case CURRENT_OP:                /* 173 0xad current operation */
  val->t_char = rVar.currentOp;
  break;

 case LIMIT_OVERRIDE:            /* 174 0xae override limit switches */
  val->t_char = rVar.limitOverride;
  break;

 case COMMON_LIMITS:             /* 175 0xaf all limit switches one pin */
  val->t_char = rVar.commonLimits;
  break;

 case LIMITS_ENABLED:            /* 176 0xb0 limits enabled */
  val->t_char = rVar.limitsEnabled;
  break;

 case COMMON_HOME:               /* 177 0xb1 all home switches one pin */
  val->t_char = rVar.commonHome;
  break;

 case Z_LIM_ENA:                 /* 178 0xb2 z limit enable */
  val->t_char = rVar.zLimEna;
  break;

 case Z_LIM_NEG_INV:             /* 179 0xb3 z negative limit invert */
  val->t_char = rVar.zLimNegInv;
  break;

 case Z_LIM_POS_INV:             /* 180 0xb4 z Positive limit Invert */
  val->t_char = rVar.zLimPosInv;
  break;

 case Z_HOME_ENA:                /* 181 0xb5 z home enable */
  val->t_char = rVar.zHomeEna;
  break;

 case Z_HOME_INV:                /* 182 0xb6 z home invert */
  val->t_char = rVar.zHomeInv;
  break;

 case X_LIM_ENA:                 /* 183 0xb7 x limit enable */
  val->t_char = rVar.xLimEna;
  break;

 case X_LIM_NEG_INV:             /* 184 0xb8 x negative limit invert */
  val->t_char = rVar.xLimNegInv;
  break;

 case X_LIM_POS_INV:             /* 185 0xb9 x Positive limit Invert */
  val->t_char = rVar.xLimPosInv;
  break;

 case X_HOME_ENA:                /* 186 0xba x home enable */
  val->t_char = rVar.xHomeEna;
  break;

 case X_HOME_INV:                /* 187 0xbb x home invert */
  val->t_char = rVar.xHomeInv;
  break;

 case E_STOP_ENA:                /* 188 0xbc enable estop */
  val->t_char = rVar.eStopEna;
  break;

 case E_STOP_INV:                /* 189 0xbd invert estop signal */
  val->t_char = rVar.eStopInv;
  break;

 case CMD_PAUSED:                /* 190 0xbe move commands paused */
  val->t_char = rVar.cmdPaused;
  break;

 case ARC_RADIUS:                /* 191 0xbf arc radius */
  val->t_float = rVar.arcRadius;
  break;

 case ARC_X_CENTER:              /* 192 0xc0 arc x center */
  val->t_int = rVar.arcXCenter;
  break;

 case ARC_Z_CENTER:              /* 193 0xc1 arc z center */
  val->t_int = rVar.arcZCenter;
  break;

 case ARC_X_START:               /* 194 0xc2 arc x start */
  val->t_int = rVar.arcXStart;
  break;

 case ARC_Z_START:               /* 195 0xc3 arc z start */
  val->t_int = rVar.arcZStart;
  break;

 case ARC_X_END:                 /* 196 0xc4 arc x center */
  val->t_int = rVar.arcXEnd;
  break;

 case ARC_Z_END:                 /* 197 0xc5 arc z center */
  val->t_int = rVar.arcZEnd;
  break;

 case MEGA_VFD:                  /* 198 0xc6 mega vfd speed mode */
  val->t_char = rVar.megaVfd;
  break;

 case MEGA_SIM:                  /* 199 0xc7 mega encoder lines */
  val->t_char = rVar.megaSim;
  break;

 case USB_ENA:                   /* 200 0xc8 enable usb */
  val->t_char = rVar.usbEna;
  break;

 case DRO_STEP:                  /* 201 0xc9 step pulse drives dro */
  val->t_char = rVar.droStep;
  break;

 case MAX_PARM:                  /* 202 0xca maximum parameter */
  val->t_int16_t = rVar.maxParm;
  break;

 }
}
