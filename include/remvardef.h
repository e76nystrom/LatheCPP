
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
 EXT char zDirFlag;             /* 0x18 z invert direction */
 EXT char zMpgFlag;             /* 0x19 z invert mpg */

// x axis parameters

 EXT float xPitch;              /* 0x1a x axis leadscrew pitch */
 EXT float xRatio;              /* 0x1b x axis ratio */
 EXT int16_t xMicro;            /* 0x1c x axis micro steps */
 EXT int16_t xMotor;            /* 0x1d x axis motor steps */
 EXT float xAccelTime;          /* 0x1e x axis acceleration */
 EXT float xAccel;              /* 0x1f z accel rpm/sec^2 */
 EXT float xBacklash;           /* 0x20 x axis backlash */
 EXT char xDirFlag;             /* 0x21 x invert direction */
 EXT char xMpgFlag;             /* 0x22 x invert mpg */
 EXT int xDiameter;             /* 0x23 x diameter */

// z move parameters

 EXT float zMoveMin;            /* 0x24 z move min speed */
 EXT float zMoveMax;            /* 0x25 z move max speed */

// z jog parameters

 EXT float zJogMin;             /* 0x26 z jog min speed */
 EXT float zJogMax;             /* 0x27 z jog max speed */
 EXT float zJogSpeed;           /* 0x28 z jog speed */

// x move parameters

 EXT float xMoveMin;            /* 0x29 x move min speed */
 EXT float xMoveMax;            /* 0x2a x move max speed */

// x jog parameters

 EXT float xJogMin;             /* 0x2b x jog min speed */
 EXT float xJogMax;             /* 0x2c x jog max speed */
 EXT float xJogSpeed;           /* 0x2d x jog speed */

// pass information

 EXT int16_t totalPasses;       /* 0x2e total passes */
 EXT int16_t currentPass;       /* 0x2f current passes */
 EXT int16_t mvStatus;          /* 0x30 movement status */

// z axis move values

 EXT float zMoveDist;           /* 0x31 z move distance */
 EXT float zMovePos;            /* 0x32 z move position */
 EXT int zJogDir;               /* 0x33 x jog direction */
 EXT float zSetLoc;             /* 0x34 z location to set */
 EXT int zLoc;                  /* 0x35 z dro location */
 EXT int zFlag;                 /* 0x36 z move flag */
 EXT int zAbsLoc;               /* 0x37 z absolute location */
 EXT int zMpgInc;               /* 0x38 z man pulse gen incr */
 EXT int zMpgMax;               /* 0x39 z man pulse max distance */

// x axis move values

 EXT float xMoveDist;           /* 0x3a x move distance */
 EXT float xMovePos;            /* 0x3b x move position */
 EXT int xJogDir;               /* 0x3c x jog direction */
 EXT float xSetLoc;             /* 0x3d x location to set */
 EXT int xLoc;                  /* 0x3e x dro location */
 EXT int xFlag;                 /* 0x3f x move flag */
 EXT int xAbsLoc;               /* 0x40 x absolute location */
 EXT int xMpgInc;               /* 0x41 X man pulse gen incr */
 EXT int xMpgMax;               /* 0x42 x man pulse max distance */

// common jog parameters

 EXT float jogTimeInitial;      /* 0x43 jog time initial */
 EXT float jogTimeInc;          /* 0x44 jog time increment */
 EXT float jogTimeMax;          /* 0x45 jog time max */

// taper parameters

 EXT float taperCycleDist;      /* 0x46 taperCycleDist */

// index pulse variables

 EXT int indexPreScaler;        /* 0x47 index pre scaler */
 EXT unsigned int lastIndexPeriod;/* 0x48 last index period */
 EXT unsigned int indexPeriod;  /* 0x49 index period */
 EXT unsigned int revCounter;   /* 0x4a revolution counter */

// z home offset

 EXT float zHomeOffset;         /* 0x4b z home offset */

// z dro

 EXT int zDroPos;               /* 0x4c z dro location */
 EXT float zDroOffset;          /* 0x4d z dro to zero */
 EXT int zDroInch;              /* 0x4e z dro scale */
 EXT int zDroInvert;            /* 0x4f z dro invert */

// x home parameters

 EXT float xHomeSpeed;          /* 0x50 x final homing speed */
 EXT float xHomeDist;           /* 0x51 x max homing distance */
 EXT float xHomeBackoffDist;    /* 0x52 x home backoff dist */
 EXT int xHomeDir;              /* 0x53 x homing direction */

// x home test parameters

 EXT int xHomeLoc;              /* 0x54 x home test location */
 EXT int xHomeStart;            /* 0x55 x start of home signal */
 EXT int xHomeEnd;              /* 0x56 x end of home signal */
 EXT float xHomeOffset;         /* 0x57 x home offset */
 EXT int xDroPos;               /* 0x58 x dro location */
 EXT float xDroOffset;          /* 0x59 x dro to zero */
 EXT int xDroInch;              /* 0x5a x dro scale */
 EXT int xDroInvert;            /* 0x5b x dro invert */

// x home or probe status

 EXT int xHomeDone;             /* 0x5c x home done */
 EXT int xHomeStatus;           /* 0x5d x home status */

// Z home or probe status

 EXT int zHomeDone;             /* 0x5e z home done */
 EXT int zHomeStatus;           /* 0x5f z home status */

// probe configuration

 EXT float probeSpeed;          /* 0x60 probe speed */
 EXT int probeDist;             /* 0x61 probe test distance */
 EXT int probeInv;              /* 0x62 invert polarity of probe */

// configuration

 EXT char stepperDrive;         /* 0x63 stepper driven spindle */
 EXT char motorTest;            /* 0x64 use stepper drive to test motor */
 EXT char spindleEncoder;       /* 0x65 motor drive with spindle encoder */
 EXT char spindleSyncBoard;     /* 0x66 spindle sync board */
 EXT char spindleSync;          /* 0x67 spindle sync direct */
 EXT char useEncoder;           /* 0x68 config for use encoder interrupt directly */
 EXT char encoderDirect;        /* 0x69 use encoder interrupt directly */
 EXT char capTmrEnable;         /* 0x6a enable capture timer */
 EXT char cfgXilinx;            /* 0x6b using xilinx */
 EXT char cfgMpg;               /* 0x6c manual pulse generator */
 EXT char cfgDro;               /* 0x6d digital readout */
 EXT char cfgLcd;               /* 0x6e lcd display */
 EXT int cfgFcy;                /* 0x6f system clock speed */

// setup

 EXT char setupDone;            /* 0x70 setup done */

// encoder counts per revolution

 EXT uint16_t encPerRev;        /* 0x71 spindle encoder counts per revolution */

// test encoder setup variables

 EXT char encEnable;            /* 0x72 encoder enable flag */
 EXT uint16_t encPreScaler;     /* 0x73 encoder prescaler */
 EXT uint16_t encTimer;         /* 0x74 encoder timer counts */
 EXT int encRunCount;           /* 0x75 encoder run count */

// test encoder status variables

 EXT char encRun;               /* 0x76 encoder running flag */
 EXT int16_t encCounter;        /* 0x77 encoder count in rev */
 EXT int32_t encRevCounter;     /* 0x78 encoder revolution counter */

// measured spindle speed

 EXT int16_t rpm;               /* 0x79 current rpm */

// xilinx frequency variables

 EXT int32_t xFrequency;        /* 0x7a xilinx clock frequency */
 EXT int16_t freqMult;          /* 0x7b frequency multiplier */

// xilinx configuration register

 EXT int16_t xCfgReg;           /* 0x7c xilinx configuration register */

// sync parameters

 EXT uint16_t lSyncCycle;       /* 0x7d sync cycle length */
 EXT uint16_t lSyncOutput;      /* 0x7e sync outputs per cycle */
 EXT uint16_t lSyncPrescaler;   /* 0x7f sync prescaler */

// threading variables

 EXT int32_t thZStart;          /* 0x80 threading z start */
 EXT int32_t thXStart;          /* 0x81 threading x start */
 EXT float tanThreadAngle;      /* 0x82 tangent of threading angle */
 EXT int16_t xFeed;             /* 0x83 x feed */
 EXT float runoutDistance;      /* 0x84 runout distance */
 EXT float runoutDepth;         /* 0x85 runout depth */

// jog debug

 EXT char jogDebug;             /* 0x86 jog interrupt debug */

// max parameter number

 EXT int16_t maxParm;           /* 0x87 maximum parameter */
