
// spindle parameters

 EXT int16_t spSteps;           /* 0x00 spindle motor steps */
 EXT int16_t spMicro;           /* 0x01 spindle micro steps */
 EXT float spMinRpm;            /* 0x02 spindle minimum rpm */
 EXT float spMaxRpm;            /* 0x03 spindle maxmum rpm */
 EXT float spAccelTime;         /* 0x04 spindle accel time */
 EXT float spAccel;             /* 0x05 spindle accel rpm/sec^2 */
 EXT float spJogMinRpm;         /* 0x06 spindle jog minimum rpm */
 EXT float spJogMaxRpm;         /* 0x07 spindle jog maxmum rpm */
 EXT float spJogRpm;            /* 0x08 spindle jog rpm */
 EXT float spJogAccelTime;      /* 0x09 spindle jog accel time */
 EXT float spJogTimeInitial;    /* 0x0a spindle jog time initial */
 EXT float spJogTimeInc;        /* 0x0b spindle jog time increment */
 EXT float spJogTimeMax;        /* 0x0c spindle jog timemax */
 EXT char spJogDir;             /* 0x0d spindle direction */
 EXT char spDirFlag;            /* 0x0e spindle invert direction */
 EXT char spTestIndex;          /* 0x0f generate test index pulse */
 EXT char spTestEncoder;        /* 0x10 generate encoder test pulse */

// z axis parameters

 EXT float zPitch;              /* 0x11 z axis leadscrew pitch */
 EXT float zRatio;              /* 0x12 z axis ratio */
 EXT int16_t zMicro;            /* 0x13 z axis micro steps */
 EXT int16_t zMotor;            /* 0x14 z axis motor steps */
 EXT float zAccelTime;          /* 0x15 z axis acceleration */
 EXT float zAccel;              /* 0x16 z accel rpm/sec^2 */
 EXT float zBacklash;           /* 0x17 z axis backlash */
 EXT int zStepFactor;           /* 0x18 z steps inch factored */
 EXT char zDirFlag;             /* 0x19 z invert direction */
 EXT char zMpgFlag;             /* 0x1a z invert mpg */

// x axis parameters

 EXT float xPitch;              /* 0x1b x axis leadscrew pitch */
 EXT float xRatio;              /* 0x1c x axis ratio */
 EXT int16_t xMicro;            /* 0x1d x axis micro steps */
 EXT int16_t xMotor;            /* 0x1e x axis motor steps */
 EXT float xAccelTime;          /* 0x1f x axis acceleration */
 EXT float xAccel;              /* 0x20 x accel rpm/sec^2 */
 EXT float xBacklash;           /* 0x21 x axis backlash */
 EXT int xStepFactor;           /* 0x22 x steps inch factored */
 EXT char xDirFlag;             /* 0x23 x invert direction */
 EXT char xMpgFlag;             /* 0x24 x invert mpg */
 EXT int xDiameter;             /* 0x25 x diameter */

// z move parameters

 EXT float zMoveMin;            /* 0x26 z move min speed */
 EXT float zMoveMax;            /* 0x27 z move max speed */

// z jog parameters

 EXT float zJogMin;             /* 0x28 z jog min speed */
 EXT float zJogMax;             /* 0x29 z jog max speed */
 EXT float zJogSpeed;           /* 0x2a z jog speed */

// x move parameters

 EXT float xMoveMin;            /* 0x2b x move min speed */
 EXT float xMoveMax;            /* 0x2c x move max speed */

// x jog parameters

 EXT float xJogMin;             /* 0x2d x jog min speed */
 EXT float xJogMax;             /* 0x2e x jog max speed */
 EXT float xJogSpeed;           /* 0x2f x jog speed */

// pass information

 EXT int16_t totalPasses;       /* 0x30 total passes */
 EXT int16_t currentPass;       /* 0x31 current passes */
 EXT int16_t mvStatus;          /* 0x32 movement status */

// z axis move values

 EXT float zMoveDist;           /* 0x33 z move distance */
 EXT float zMovePos;            /* 0x34 z move position */
 EXT int zJogDir;               /* 0x35 x jog direction */
 EXT float zSetLoc;             /* 0x36 z location to set */
 EXT int zLoc;                  /* 0x37 z dro location */
 EXT int zFlag;                 /* 0x38 z move flag */
 EXT int zAbsLoc;               /* 0x39 z absolute location */
 EXT int zMpgInc;               /* 0x3a z man pulse gen incr */
 EXT int zMpgMax;               /* 0x3b z man pulse max distance */

// x axis move values

 EXT float xMoveDist;           /* 0x3c x move distance */
 EXT float xMovePos;            /* 0x3d x move position */
 EXT int xJogDir;               /* 0x3e x jog direction */
 EXT float xSetLoc;             /* 0x3f x location to set */
 EXT int xLoc;                  /* 0x40 x dro location */
 EXT int xFlag;                 /* 0x41 x move flag */
 EXT int xAbsLoc;               /* 0x42 x absolute location */
 EXT int xMpgInc;               /* 0x43 X man pulse gen incr */
 EXT int xMpgMax;               /* 0x44 x man pulse max distance */

// common jog parameters

 EXT float jogTimeInitial;      /* 0x45 jog time initial */
 EXT float jogTimeInc;          /* 0x46 jog time increment */
 EXT float jogTimeMax;          /* 0x47 jog time max */

// taper parameters

 EXT float taperCycleDist;      /* 0x48 taperCycleDist */

// index pulse variables

 EXT int indexPreScaler;        /* 0x49 index pre scaler */
 EXT unsigned int lastIndexPeriod;/* 0x4a last index period */
 EXT unsigned int indexPeriod;  /* 0x4b index period */
 EXT unsigned int revCounter;   /* 0x4c revolution counter */

// z home offset

 EXT int zHomeOffset;           /* 0x4d z home offset */

// x home offset

 EXT int xHomeOffset;           /* 0x4e x home offset */

// z home parameters

 EXT float zHomeSpeed;          /* 0x4f z final homing speed */
 EXT float zHomeDist;           /* 0x50 z max homing distance */
 EXT float zHomeBackoffDist;    /* 0x51 z home backoff dist */
 EXT int zHomeDir;              /* 0x52 z homing direction */

// x home parameters

 EXT float xHomeSpeed;          /* 0x53 x final homing speed */
 EXT float xHomeDist;           /* 0x54 x max homing distance */
 EXT float xHomeBackoffDist;    /* 0x55 x home backoff dist */
 EXT int xHomeDir;              /* 0x56 x homing direction */

// x home test parameters

 EXT int xHomeLoc;              /* 0x57 x home test location */
 EXT int xHomeStart;            /* 0x58 x start of home signal */
 EXT int xHomeEnd;              /* 0x59 x end of home signal */

// z dro

 EXT int zDroPos;               /* 0x5a z dro location */
 EXT int zDroOffset;            /* 0x5b z dro to zero */
 EXT int zDroCountInch;         /* 0x5c z dro scale */
 EXT int zDroFactor;            /* 0x5d x dro counts inch factored */
 EXT int zDroInvert;            /* 0x5e z dro invert */
 EXT char zUseDro;              /* 0x5f z use dro for position */
 EXT int zDoneDelay;            /* 0x60 z done to read dro delay */
 EXT int zDroFinalDist;         /* 0x61 z final approach distance */

// x dro

 EXT int xDroPos;               /* 0x62 x dro location */
 EXT int xDroOffset;            /* 0x63 x dro to zero */
 EXT int xDroCountInch;         /* 0x64 x dro scale */
 EXT int xDroFactor;            /* 0x65 x dro counts inch factored */
 EXT int xDroInvert;            /* 0x66 x dro invert */
 EXT char xUseDro;              /* 0x67 x use dro for position */
 EXT int xDoneDelay;            /* 0x68 x done to read dro delay */
 EXT int xDroFinalDist;         /* 0x69 x final approach distance */

// x home or probe status

 EXT int xHomeDone;             /* 0x6a x home done */
 EXT int xHomeStatus;           /* 0x6b x home status */

// Z home or probe status

 EXT int zHomeDone;             /* 0x6c z home done */
 EXT int zHomeStatus;           /* 0x6d z home status */

// probe configuration

 EXT float probeSpeed;          /* 0x6e probe speed */
 EXT int probeDist;             /* 0x6f probe test distance */
 EXT int probeInv;              /* 0x70 invert polarity of probe */

// configuration

 EXT char stepperDrive;         /* 0x71 stepper driven spindle */
 EXT char motorTest;            /* 0x72 use stepper drive to test motor */
 EXT char spindleEncoder;       /* 0x73 motor drive with spindle encoder */
 EXT char spindleSyncBoard;     /* 0x74 spindle sync board */
 EXT char turnSync;             /* 0x75 synchronization type for turning */
 EXT char threadSync;           /* 0x76 synchronization type for threading */
 EXT char capTmrEnable;         /* 0x77 enable capture timer */
 EXT char cfgFpga;              /* 0x78 using fpga */
 EXT char cfgMpg;               /* 0x79 manual pulse generator */
 EXT char cfgDro;               /* 0x7a digital readout */
 EXT char cfgLcd;               /* 0x7b lcd display */
 EXT int cfgFcy;                /* 0x7c system clock speed */
 EXT int cfgSwitch;             /* 0x7d spindle off on switch */
 EXT int cfgVarSpeed;           /* 0x7e spindle variable speed */

// setup

 EXT char setupDone;            /* 0x7f setup done */

// encoder counts per revolution

 EXT uint16_t encPerRev;        /* 0x80 spindle encoder counts per revolution */

// test encoder setup variables

 EXT char encEnable;            /* 0x81 encoder enable flag */
 EXT uint16_t encPreScaler;     /* 0x82 encoder prescaler */
 EXT uint16_t encTimer;         /* 0x83 encoder timer counts */
 EXT int encRunCount;           /* 0x84 encoder run count */

// test encoder status variables

 EXT char encRun;               /* 0x85 encoder running flag */
 EXT int16_t encCounter;        /* 0x86 encoder count in rev */
 EXT int32_t encRevCounter;     /* 0x87 encoder revolution counter */

// measured spindle speed

 EXT int16_t rpm;               /* 0x88 current rpm */

// fpga frequency variables

 EXT int32_t fpgaFrequency;     /* 0x89 fpga clock frequency */
 EXT int16_t freqMult;          /* 0x8a frequency multiplier */

// xilinx configuration register

 EXT int16_t xCfgReg;           /* 0x8b xilinx configuration register */

// sync parameters

 EXT uint16_t lSyncCycle;       /* 0x8c sync cycle length */
 EXT uint16_t lSyncOutput;      /* 0x8d sync outputs per cycle */
 EXT uint16_t lSyncPrescaler;   /* 0x8e sync prescaler */

// threading variables

 EXT int32_t thZStart;          /* 0x8f threading z start */
 EXT int32_t thXStart;          /* 0x90 threading x start */
 EXT float tanThreadAngle;      /* 0x91 tangent of threading angle */
 EXT int16_t xFeed;             /* 0x92 x feed */
 EXT float runoutDistance;      /* 0x93 runout distance */
 EXT float runoutDepth;         /* 0x94 runout depth */

// jog debug

 EXT char jogDebug;             /* 0x95 jog interrupt debug */

// motor and speed control

 EXT int16_t pwmFreq;           /* 0x96 spindle speed pwm frequency */
 EXT int16_t minSpeed;          /* 0x97 minimum speed for current range */
 EXT int16_t maxSpeed;          /* 0x98 maximum speed for current range */

// current operation

 EXT char currentOp;            /* 0x99 current operation */

// global limits and home

 EXT char limitOverride;        /* 0x9a override limit switches */
 EXT char commonLimits;         /* 0x9b all limit switches on one pin */
 EXT char limitsEnabled;        /* 0x9c limits enabled */
 EXT char commonHome;           /* 0x9d all home switches on one pin */

// z limits and home

 EXT char zLimEna;              /* 0x9e z limit enable */
 EXT char zLimNegInv;           /* 0x9f z negative limit invert */
 EXT char zLimPosInv;           /* 0xa0 z Positive limit Invert */
 EXT char zHomeEna;             /* 0xa1 z home enable */
 EXT char zHomeInv;             /* 0xa2 z home invert */

// x limits and home

 EXT char xLimEna;              /* 0xa3 x limit enable */
 EXT char xLimNegInv;           /* 0xa4 x negative limit invert */
 EXT char xLimPosInv;           /* 0xa5 x Positive limit Invert */
 EXT char xHomeEna;             /* 0xa6 x home enable */
 EXT char xHomeInv;             /* 0xa7 x home invert */

// e stop

 EXT char eStopEna;             /* 0xa8 enable estop */
 EXT char eStopInv;             /* 0xa9 invert estop siganl */
 EXT int16_t maxParm;           /* 0xaa maximum parameter */
