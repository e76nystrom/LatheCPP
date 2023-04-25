/* defines */

#define FLT (0x80)
#define SIZE_MASK (0x7)

unsigned char remParm[] =
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
