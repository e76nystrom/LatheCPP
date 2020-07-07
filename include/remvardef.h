
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
 EXT int xStepFactor;           /* 0x18 x steps inch factored */
 EXT char zDirFlag;             /* 0x19 z invert direction */
 EXT char zMpgFlag;             /* 0x1a z invert mpg */

// x axis parameters

 EXT float xPitch;              /* 0x1b x axis leadscrew pitch */
 EXT float xRatio;              /* 0x1c x axis ratio */
 EXT int16_t xMicro;            /* 0x1d x axis micro steps */
 EXT int16_t xMotor;            /* 0x1e x axis motor steps */
 EXT float xAccelTime;          /* 0x1f x axis acceleration */
 EXT float xAccel;              /* 0x20 z accel rpm/sec^2 */
 EXT float xBacklash;           /* 0x21 x axis backlash */
 EXT char xDirFlag;             /* 0x22 x invert direction */
 EXT char xMpgFlag;             /* 0x23 x invert mpg */
 EXT int xDiameter;             /* 0x24 x diameter */

// z move parameters

 EXT float zMoveMin;            /* 0x25 z move min speed */
 EXT float zMoveMax;            /* 0x26 z move max speed */

// z jog parameters

 EXT float zJogMin;             /* 0x27 z jog min speed */
 EXT float zJogMax;             /* 0x28 z jog max speed */
 EXT float zJogSpeed;           /* 0x29 z jog speed */

// x move parameters

 EXT float xMoveMin;            /* 0x2a x move min speed */
 EXT float xMoveMax;            /* 0x2b x move max speed */

// x jog parameters

 EXT float xJogMin;             /* 0x2c x jog min speed */
 EXT float xJogMax;             /* 0x2d x jog max speed */
 EXT float xJogSpeed;           /* 0x2e x jog speed */

// pass information

 EXT int16_t totalPasses;       /* 0x2f total passes */
 EXT int16_t currentPass;       /* 0x30 current passes */
 EXT int16_t mvStatus;          /* 0x31 movement status */

// z axis move values

 EXT float zMoveDist;           /* 0x32 z move distance */
 EXT float zMovePos;            /* 0x33 z move position */
 EXT int zJogDir;               /* 0x34 x jog direction */
 EXT float zSetLoc;             /* 0x35 z location to set */
 EXT int zLoc;                  /* 0x36 z dro location */
 EXT int zFlag;                 /* 0x37 z move flag */
 EXT int zAbsLoc;               /* 0x38 z absolute location */
 EXT int zMpgInc;               /* 0x39 z man pulse gen incr */
 EXT int zMpgMax;               /* 0x3a z man pulse max distance */

// x axis move values

 EXT float xMoveDist;           /* 0x3b x move distance */
 EXT float xMovePos;            /* 0x3c x move position */
 EXT int xJogDir;               /* 0x3d x jog direction */
 EXT float xSetLoc;             /* 0x3e x location to set */
 EXT int xLoc;                  /* 0x3f x dro location */
 EXT int xFlag;                 /* 0x40 x move flag */
 EXT int xAbsLoc;               /* 0x41 x absolute location */
 EXT int xMpgInc;               /* 0x42 X man pulse gen incr */
 EXT int xMpgMax;               /* 0x43 x man pulse max distance */

// common jog parameters

 EXT float jogTimeInitial;      /* 0x44 jog time initial */
 EXT float jogTimeInc;          /* 0x45 jog time increment */
 EXT float jogTimeMax;          /* 0x46 jog time max */

// taper parameters

 EXT float taperCycleDist;      /* 0x47 taperCycleDist */

// index pulse variables

 EXT int indexPreScaler;        /* 0x48 index pre scaler */
 EXT unsigned int lastIndexPeriod;/* 0x49 last index period */
 EXT unsigned int indexPeriod;  /* 0x4a index period */
 EXT unsigned int revCounter;   /* 0x4b revolution counter */

// z home offset

 EXT int zHomeOffset;           /* 0x4c z home offset */

// z dro

 EXT int zDroPos;               /* 0x4d z dro location */
 EXT int zDroOffset;            /* 0x4e z dro to zero */
 EXT int zDroCountInch;         /* 0x4f z dro scale */
 EXT int zDroInvert;            /* 0x50 z dro invert */
 EXT char zUseDro;              /* 0x51 z use dro for position */

// x home parameters

 EXT float xHomeSpeed;          /* 0x52 x final homing speed */
 EXT float xHomeDist;           /* 0x53 x max homing distance */
 EXT float xHomeBackoffDist;    /* 0x54 x home backoff dist */
 EXT int xHomeDir;              /* 0x55 x homing direction */

// x home test parameters

 EXT int xHomeLoc;              /* 0x56 x home test location */
 EXT int xHomeStart;            /* 0x57 x start of home signal */
 EXT int xHomeEnd;              /* 0x58 x end of home signal */
 EXT int xHomeOffset;           /* 0x59 x home offset */
 EXT int xDroPos;               /* 0x5a x dro location */
 EXT int xDroOffset;            /* 0x5b x dro to zero */
 EXT int xDroCountInch;         /* 0x5c x dro scale */
 EXT int xDroFactor;            /* 0x5d x dro counts inch factored */
 EXT int xDroInvert;            /* 0x5e x dro invert */
 EXT char xUseDro;              /* 0x5f x use dro for position */
 EXT int xDoneDelay;            /* 0x60 x done to read dro delay */
 EXT int xDroFinalDist;         /* 0x61 x final approach distance */

// x home or probe status

 EXT int xHomeDone;             /* 0x62 x home done */
 EXT int xHomeStatus;           /* 0x63 x home status */

// Z home or probe status

 EXT int zHomeDone;             /* 0x64 z home done */
 EXT int zHomeStatus;           /* 0x65 z home status */

// probe configuration

 EXT float probeSpeed;          /* 0x66 probe speed */
 EXT int probeDist;             /* 0x67 probe test distance */
 EXT int probeInv;              /* 0x68 invert polarity of probe */

// configuration

 EXT char stepperDrive;         /* 0x69 stepper driven spindle */
 EXT char motorTest;            /* 0x6a use stepper drive to test motor */
 EXT char spindleEncoder;       /* 0x6b motor drive with spindle encoder */
 EXT char spindleSyncBoard;     /* 0x6c spindle sync board */
 EXT char turnSync;             /* 0x6d synchronization type for turning */
 EXT char threadSync;           /* 0x6e synchronization type for threading */
 EXT char capTmrEnable;         /* 0x6f enable capture timer */
 EXT char cfgFpga;              /* 0x70 using fpga */
 EXT char cfgMpg;               /* 0x71 manual pulse generator */
 EXT char cfgDro;               /* 0x72 digital readout */
 EXT char cfgLcd;               /* 0x73 lcd display */
 EXT int cfgFcy;                /* 0x74 system clock speed */
 EXT int cfgSwitch;             /* 0x75 spindle off on switch */
 EXT int cfgVarSpeed;           /* 0x76 spindle variable speed */

// setup

 EXT char setupDone;            /* 0x77 setup done */

// encoder counts per revolution

 EXT uint16_t encPerRev;        /* 0x78 spindle encoder counts per revolution */

// test encoder setup variables

 EXT char encEnable;            /* 0x79 encoder enable flag */
 EXT uint16_t encPreScaler;     /* 0x7a encoder prescaler */
 EXT uint16_t encTimer;         /* 0x7b encoder timer counts */
 EXT int encRunCount;           /* 0x7c encoder run count */

// test encoder status variables

 EXT char encRun;               /* 0x7d encoder running flag */
 EXT int16_t encCounter;        /* 0x7e encoder count in rev */
 EXT int32_t encRevCounter;     /* 0x7f encoder revolution counter */

// measured spindle speed

 EXT int16_t rpm;               /* 0x80 current rpm */

// fpga frequency variables

 EXT int32_t fpgaFrequency;     /* 0x81 fpga clock frequency */
 EXT int16_t freqMult;          /* 0x82 frequency multiplier */

// xilinx configuration register

 EXT int16_t xCfgReg;           /* 0x83 xilinx configuration register */

// sync parameters

 EXT uint16_t lSyncCycle;       /* 0x84 sync cycle length */
 EXT uint16_t lSyncOutput;      /* 0x85 sync outputs per cycle */
 EXT uint16_t lSyncPrescaler;   /* 0x86 sync prescaler */

// threading variables

 EXT int32_t thZStart;          /* 0x87 threading z start */
 EXT int32_t thXStart;          /* 0x88 threading x start */
 EXT float tanThreadAngle;      /* 0x89 tangent of threading angle */
 EXT int16_t xFeed;             /* 0x8a x feed */
 EXT float runoutDistance;      /* 0x8b runout distance */
 EXT float runoutDepth;         /* 0x8c runout depth */

// jog debug

 EXT char jogDebug;             /* 0x8d jog interrupt debug */

// motor and speed control

 EXT int16_t pwmFreq;           /* 0x8e spindle speed pwm frequency */
 EXT int16_t minSpeed;          /* 0x8f minimum speed for current range */
 EXT int16_t maxSpeed;          /* 0x90 maximum speed for current range */

// current operation

 EXT char currentOp;            /* 0x91 current operation */

// limit override

 EXT char limitOverride;        /* 0x92 override limit switches */
 EXT char zLimEna;              /* 0x93 z limit enable */
 EXT char zLimNegInv;           /* 0x94 z negative limit invert */
 EXT char zLimPosInv;           /* 0x95 z Positive limit Invert */
 EXT char zHomeEna;             /* 0x96 z home enable */
 EXT char zHomeInv;             /* 0x97 z home invert */
 EXT char xLimEna;              /* 0x98 x limit enable */
 EXT char xLimNegInv;           /* 0x99 x negative limit invert */
 EXT char xLimPosInv;           /* 0x9a x Positive limit Invert */
 EXT char xHomeEna;             /* 0x9b x home enable */
 EXT char xHomeInv;             /* 0x9c x home invert */
 EXT char eStopEna;             /* 0x9d enable estop */
 EXT char eStopInv;             /* 0x9e invert estop siganl */
 EXT int16_t maxParm;           /* 0x9f maximum parameter */
