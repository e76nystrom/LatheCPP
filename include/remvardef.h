
// spindle parameters

 EXT int16_t spSteps;           /* 0x00 spindle motor steps */
 EXT int16_t spMicro;           /* 0x01 spindle micro steps */
 EXT float spMinRpm;            /* 0x02 spindle minimum rpm */
 EXT float spMaxRpm;            /* 0x03 spindle maximum rpm */
 EXT float spRpm;               /* 0x04 spindle rpm */
 EXT float spAccelTime;         /* 0x05 spindle accel time */
 EXT float spAccel;             /* 0x06 spindle accel rpm/sec^2 */
 EXT float spJogMinRpm;         /* 0x07 spindle jog minimum rpm */
 EXT float spJogMaxRpm;         /* 0x08 spindle jog maximum rpm */
 EXT float spJogRpm;            /* 0x09 spindle jog rpm */
 EXT float spJogAccelTime;      /* 0x0a spindle jog accel time */
 EXT float spJogTimeInitial;    /* 0x0b spindle jog time initl */
 EXT float spJogTimeInc;        /* 0x0c spindle jog time increment */
 EXT float spJogTimeMax;        /* 0x0d spindle jog timemax */
 EXT char spJogDir;             /* 0x0e spindle direction */
 EXT char spDirFlag;            /* 0x0f spindle invert direction */
 EXT char spTestIndex;          /* 0x10 generate test index pulse */
 EXT char spTestEncoder;        /* 0x11 generate enc test pulse */

// z axis parameters

 EXT float zPitch;              /* 0x12 z axis leadscrew pitch */
 EXT float zRatio;              /* 0x13 z axis ratio */
 EXT int16_t zMicro;            /* 0x14 z axis micro steps */
 EXT int16_t zMotor;            /* 0x15 z axis motor steps */
 EXT float zAccelTime;          /* 0x16 z axis acceleration */
 EXT float zAccel;              /* 0x17 z accel rpm/sec^2 */
 EXT float zBacklash;           /* 0x18 z axis backlash */
 EXT int zStepFactor;           /* 0x19 z steps inch factored */
 EXT char zDirFlag;             /* 0x1a z invert direction */
 EXT char zMpgFlag;             /* 0x1b z invert mpg */

// x axis parameters

 EXT float xPitch;              /* 0x1c x axis leadscrew pitch */
 EXT float xRatio;              /* 0x1d x axis ratio */
 EXT int16_t xMicro;            /* 0x1e x axis micro steps */
 EXT int16_t xMotor;            /* 0x1f x axis motor steps */
 EXT float xAccelTime;          /* 0x20 x axis acceleration */
 EXT float xAccel;              /* 0x21 x accel rpm/sec^2 */
 EXT float xBacklash;           /* 0x22 x axis backlash */
 EXT int xStepFactor;           /* 0x23 x steps inch factored */
 EXT char xDirFlag;             /* 0x24 x invert direction */
 EXT char xMpgFlag;             /* 0x25 x invert mpg */
 EXT int xDiameter;             /* 0x26 x diameter */

// z move parameters

 EXT float zMoveMin;            /* 0x27 z move min speed */
 EXT float zMoveMax;            /* 0x28 z move max speed */

// z jog parameters

 EXT float zJogMin;             /* 0x29 z jog min speed */
 EXT float zJogMax;             /* 0x2a z jog max speed */
 EXT float zJogSpeed;           /* 0x2b z jog speed */

// x move parameters

 EXT float xMoveMin;            /* 0x2c x move min speed */
 EXT float xMoveMax;            /* 0x2d x move max speed */

// x jog parameters

 EXT float xJogMin;             /* 0x2e x jog min speed */
 EXT float xJogMax;             /* 0x2f x jog max speed */
 EXT float xJogSpeed;           /* 0x30 x jog speed */

// pass information

 EXT int16_t totalPasses;       /* 0x31 total passes */
 EXT int16_t currentPass;       /* 0x32 current passes */
 EXT int16_t mvStatus;          /* 0x33 movement status */

// z axis move values

 EXT float zMoveDist;           /* 0x34 z move distance */
 EXT float zMovePos;            /* 0x35 z move position */
 EXT int zJogDir;               /* 0x36 x jog direction */
 EXT float zSetLoc;             /* 0x37 z location to set */
 EXT int zLoc;                  /* 0x38 z dro location */
 EXT int zFlag;                 /* 0x39 z move flag */
 EXT int zAbsLoc;               /* 0x3a z absolute location */
 EXT int zMpgInc;               /* 0x3b z man pulse gen incr */
 EXT int zMpgMax;               /* 0x3c z man pulse max distance */

// x axis move values

 EXT float xMoveDist;           /* 0x3d x move distance */
 EXT float xMovePos;            /* 0x3e x move position */
 EXT int xJogDir;               /* 0x3f x jog direction */
 EXT float xSetLoc;             /* 0x40 x location to set */
 EXT int xLoc;                  /* 0x41 x dro location */
 EXT int xFlag;                 /* 0x42 x move flag */
 EXT int xAbsLoc;               /* 0x43 x absolute location */
 EXT int xMpgInc;               /* 0x44 X man pulse gen incr */
 EXT int xMpgMax;               /* 0x45 x man pulse max distance */

// common jog parameters

 EXT float jogTimeInitial;      /* 0x46 jog time initial */
 EXT float jogTimeInc;          /* 0x47 jog time increment */
 EXT float jogTimeMax;          /* 0x48 jog time max */

// taper parameters

 EXT float taperCycleDist;      /* 0x49 taperCycleDist */

// index pulse variables

 EXT int indexPreScaler;        /* 0x4a index pre scaler */
 EXT unsigned int lastIndexPeriod;/* 0x4b last index period */
 EXT unsigned int indexPeriod;  /* 0x4c index period */
 EXT unsigned int revCounter;   /* 0x4d revolution counter */

// z home offset

 EXT int zHomeOffset;           /* 0x4e z home offset */

// x home offset

 EXT int xHomeOffset;           /* 0x4f x home offset */

// z home parameters

 EXT float zHomeSpeed;          /* 0x50 z final homing speed */
 EXT float zHomeDist;           /* 0x51 z max homing distance */
 EXT float zHomeDistRev;        /* 0x52 z max rev homing distance */
 EXT float zHomeDistBackoff;    /* 0x53 z home backoff dist */
 EXT int zHomeDir;              /* 0x54 z homing direction */

// x home parameters

 EXT float xHomeSpeed;          /* 0x55 x final homing speed */
 EXT float xHomeDist;           /* 0x56 x max homing distance */
 EXT float xHomeDistRev;        /* 0x57 x max rev homing distance */
 EXT float xHomeDistBackoff;    /* 0x58 x home backoff dist */
 EXT int xHomeDir;              /* 0x59 x homing direction */

// x home test parameters

 EXT int xHomeLoc;              /* 0x5a x home test location */
 EXT int xHomeStart;            /* 0x5b x start of home signal */
 EXT int xHomeEnd;              /* 0x5c x end of home signal */

// z dro

 EXT int zDroLoc;               /* 0x5d z dro location */
 EXT int zDroOffset;            /* 0x5e z dro to zero */
 EXT int zDroCountInch;         /* 0x5f z dro scale */
 EXT int zDroFactor;            /* 0x60 x dro counts inch factored */
 EXT int zDroInvert;            /* 0x61 z dro invert */
 EXT char zUseDro;              /* 0x62 z use dro for position */
 EXT int zDoneDelay;            /* 0x63 z done to read dro delay */
 EXT int zDroFinalDist;         /* 0x64 z final approach distance */

// x dro

 EXT int xDroLoc;               /* 0x65 x dro location */
 EXT int xDroOffset;            /* 0x66 x dro to zero */
 EXT int xDroCountInch;         /* 0x67 x dro scale */
 EXT int xDroFactor;            /* 0x68 x dro counts inch factored */
 EXT int xDroInvert;            /* 0x69 x dro invert */
 EXT char xUseDro;              /* 0x6a x use dro for position */
 EXT int xDoneDelay;            /* 0x6b x done to read dro delay */
 EXT int xDroFinalDist;         /* 0x6c x final approach distance */

// x home or probe status

 EXT int xHomeStatus;           /* 0x6d x home status */

// Z home or probe status

 EXT int zHomeStatus;           /* 0x6e z home status */

// probe configuration

 EXT float probeSpeed;          /* 0x6f probe speed */
 EXT int probeDist;             /* 0x70 probe test distance */
 EXT int probeInv;              /* 0x71 invert polarity of probe */

// configuration

 EXT char stepperDrive;         /* 0x72 stepper driven spindle */
 EXT char motorTest;            /* 0x73 use stepper to test motor */
 EXT char spindleEncoder;       /* 0x74 motor with spindle enc */
 EXT char spindleSyncBoard;     /* 0x75 spindle sync board */
 EXT char turnSync;             /* 0x76 sync type for turning */
 EXT char threadSync;           /* 0x77 sync type for threading */
 EXT char capTmrEnable;         /* 0x78 enable capture timer */
 EXT char cfgFpga;              /* 0x79 using fpga */
 EXT char cfgMega;              /* 0x7a control link to mega */
 EXT char cfgMpg;               /* 0x7b manual pulse generator */
 EXT char cfgDro;               /* 0x7c digital readout */
 EXT char cfgLcd;               /* 0x7d lcd display */
 EXT int cfgFcy;                /* 0x7e system clock speed */
 EXT int cfgSwitch;             /* 0x7f spindle off on switch */
 EXT int cfgVarSpeed;           /* 0x80 spindle variable speed */

// setup

 EXT char setupDone;            /* 0x81 setup done */

// encoder counts per revolution

 EXT uint16_t encPerRev;        /* 0x82 spindle enc counts per rev */

// test encoder setup variables

 EXT char encEnable;            /* 0x83 encoder enable flag */
 EXT uint16_t encPreScaler;     /* 0x84 encoder prescaler */
 EXT uint16_t encTimer;         /* 0x85 encoder timer counts */
 EXT int encRunCount;           /* 0x86 encoder run count */

// test encoder status variables

 EXT char encRun;               /* 0x87 encoder running flag */
 EXT int16_t encCounter;        /* 0x88 encoder count in rev */
 EXT int32_t encRevCounter;     /* 0x89 encoder revolution counter */

// measured spindle speed

 EXT int16_t rpm;               /* 0x8a current measured rpm */

// fpga frequency variables

 EXT int32_t fpgaFrequency;     /* 0x8b fpga clock frequency */
 EXT int16_t freqMult;          /* 0x8c frequency multiplier */

// xilinx configuration register

 EXT int16_t xCfgReg;           /* 0x8d xilinx cfg register */

// z sync parameters

 EXT uint16_t lSyncCycle;       /* 0x8e sync cycle length */
 EXT uint16_t lSyncOutput;      /* 0x8f sync outputs per cycle */
 EXT uint16_t lSyncPrescaler;   /* 0x90 sync prescaler */

// x sync parameters

 EXT uint16_t lXSyncCycle;      /* 0x91 sync cycle length */
 EXT uint16_t lXSyncOutput;     /* 0x92 sync outputs per cycle */
 EXT uint16_t lXSyncPrescaler;  /* 0x93 sync prescaler */

// threading variables

 EXT int32_t thZStart;          /* 0x94 threading z start */
 EXT int32_t thXStart;          /* 0x95 threading x start */
 EXT float tanThreadAngle;      /* 0x96 tan of threading angle */
 EXT int16_t xFeed;             /* 0x97 x feed */
 EXT float runoutDistance;      /* 0x98 runout distance */
 EXT float runoutDepth;         /* 0x99 runout depth */

// jog debug

 EXT char jogDebug;             /* 0x9a jog interrupt debug */

// motor and speed control

 EXT int16_t pwmFreq;           /* 0x9b spindle speed pwm frequency */
 EXT int16_t minSpeed;          /* 0x9c min speed for current range */
 EXT int16_t maxSpeed;          /* 0x9d max speed for current range */

// current operation

 EXT char currentOp;            /* 0x9e current operation */

// global limits and home

 EXT char limitOverride;        /* 0x9f override limit switches */
 EXT char commonLimits;         /* 0xa0 all limit switches one pin */
 EXT char limitsEnabled;        /* 0xa1 limits enabled */
 EXT char commonHome;           /* 0xa2 all home switches one pin */

// z limits and home

 EXT char zLimEna;              /* 0xa3 z limit enable */
 EXT char zLimNegInv;           /* 0xa4 z negative limit invert */
 EXT char zLimPosInv;           /* 0xa5 z Positive limit Invert */
 EXT char zHomeEna;             /* 0xa6 z home enable */
 EXT char zHomeInv;             /* 0xa7 z home invert */

// x limits and home

 EXT char xLimEna;              /* 0xa8 x limit enable */
 EXT char xLimNegInv;           /* 0xa9 x negative limit invert */
 EXT char xLimPosInv;           /* 0xaa x Positive limit Invert */
 EXT char xHomeEna;             /* 0xab x home enable */
 EXT char xHomeInv;             /* 0xac x home invert */

// e stop

 EXT char eStopEna;             /* 0xad enable estop */
 EXT char eStopInv;             /* 0xae invert estop siganl */

// command pause

 EXT char cmdPaused;            /* 0xaf move commands paused */

// arc parameters

 EXT float arcRadius;           /* 0xb0 arc radius */
 EXT int arcXCenter;            /* 0xb1 arc x center */
 EXT int arcZCenter;            /* 0xb2 arc z center */
 EXT int arcXStart;             /* 0xb3 arc x start */
 EXT int arcZStart;             /* 0xb4 arc z start */
 EXT int arcXEnd;               /* 0xb5 arc x center */
 EXT int arcZEnd;               /* 0xb6 arc z center */
 EXT int16_t maxParm;           /* 0xb7 maximum parameter */
