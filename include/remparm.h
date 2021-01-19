T_PARM remparm[] =
{

// spindle parameters

 PARM(spSteps),                 /* 0x00 spindle motor steps */
 PARM(spMicro),                 /* 0x01 spindle micro steps */
 PARM(spMinRpm),                /* 0x02 spindle minimum rpm */
 PARM(spMaxRpm),                /* 0x03 spindle maxmum rpm */
 PARM(spAccelTime),             /* 0x04 spindle accel time */
 PARM(spAccel),                 /* 0x05 spindle accel rpm/sec^2 */
 PARM(spJogMinRpm),             /* 0x06 spindle jog minimum rpm */
 PARM(spJogMaxRpm),             /* 0x07 spindle jog maxmum rpm */
 PARM(spJogRpm),                /* 0x08 spindle jog rpm */
 PARM(spJogAccelTime),          /* 0x09 spindle jog accel time */
 PARM(spJogTimeInitial),        /* 0x0a spindle jog time initial */
 PARM(spJogTimeInc),            /* 0x0b spindle jog time increment */
 PARM(spJogTimeMax),            /* 0x0c spindle jog timemax */
 PARM(spJogDir),                /* 0x0d spindle direction */
 PARM(spDirFlag),               /* 0x0e spindle invert direction */
 PARM(spTestIndex),             /* 0x0f generate test index pulse */
 PARM(spTestEncoder),           /* 0x10 generate encoder test pulse */

// z axis parameters

 PARM(zPitch),                  /* 0x11 z axis leadscrew pitch */
 PARM(zRatio),                  /* 0x12 z axis ratio */
 PARM(zMicro),                  /* 0x13 z axis micro steps */
 PARM(zMotor),                  /* 0x14 z axis motor steps */
 PARM(zAccelTime),              /* 0x15 z axis acceleration */
 PARM(zAccel),                  /* 0x16 z accel rpm/sec^2 */
 PARM(zBacklash),               /* 0x17 z axis backlash */
 PARM(zStepFactor),             /* 0x18 z steps inch factored */
 PARM(zDirFlag),                /* 0x19 z invert direction */
 PARM(zMpgFlag),                /* 0x1a z invert mpg */

// x axis parameters

 PARM(xPitch),                  /* 0x1b x axis leadscrew pitch */
 PARM(xRatio),                  /* 0x1c x axis ratio */
 PARM(xMicro),                  /* 0x1d x axis micro steps */
 PARM(xMotor),                  /* 0x1e x axis motor steps */
 PARM(xAccelTime),              /* 0x1f x axis acceleration */
 PARM(xAccel),                  /* 0x20 x accel rpm/sec^2 */
 PARM(xBacklash),               /* 0x21 x axis backlash */
 PARM(xStepFactor),             /* 0x22 x steps inch factored */
 PARM(xDirFlag),                /* 0x23 x invert direction */
 PARM(xMpgFlag),                /* 0x24 x invert mpg */
 PARM(xDiameter),               /* 0x25 x diameter */

// z move parameters

 PARM(zMoveMin),                /* 0x26 z move min speed */
 PARM(zMoveMax),                /* 0x27 z move max speed */

// z jog parameters

 PARM(zJogMin),                 /* 0x28 z jog min speed */
 PARM(zJogMax),                 /* 0x29 z jog max speed */
 PARM(zJogSpeed),               /* 0x2a z jog speed */

// x move parameters

 PARM(xMoveMin),                /* 0x2b x move min speed */
 PARM(xMoveMax),                /* 0x2c x move max speed */

// x jog parameters

 PARM(xJogMin),                 /* 0x2d x jog min speed */
 PARM(xJogMax),                 /* 0x2e x jog max speed */
 PARM(xJogSpeed),               /* 0x2f x jog speed */

// pass information

 PARM(totalPasses),             /* 0x30 total passes */
 PARM(currentPass),             /* 0x31 current passes */
 PARM(mvStatus),                /* 0x32 movement status */

// z axis move values

 PARM(zMoveDist),               /* 0x33 z move distance */
 PARM(zMovePos),                /* 0x34 z move position */
 PARM(zJogDir),                 /* 0x35 x jog direction */
 PARM(zSetLoc),                 /* 0x36 z location to set */
 PARM(zLoc),                    /* 0x37 z dro location */
 PARM(zFlag),                   /* 0x38 z move flag */
 PARM(zAbsLoc),                 /* 0x39 z absolute location */
 PARM(zMpgInc),                 /* 0x3a z man pulse gen incr */
 PARM(zMpgMax),                 /* 0x3b z man pulse max distance */

// x axis move values

 PARM(xMoveDist),               /* 0x3c x move distance */
 PARM(xMovePos),                /* 0x3d x move position */
 PARM(xJogDir),                 /* 0x3e x jog direction */
 PARM(xSetLoc),                 /* 0x3f x location to set */
 PARM(xLoc),                    /* 0x40 x dro location */
 PARM(xFlag),                   /* 0x41 x move flag */
 PARM(xAbsLoc),                 /* 0x42 x absolute location */
 PARM(xMpgInc),                 /* 0x43 X man pulse gen incr */
 PARM(xMpgMax),                 /* 0x44 x man pulse max distance */

// common jog parameters

 PARM(jogTimeInitial),          /* 0x45 jog time initial */
 PARM(jogTimeInc),              /* 0x46 jog time increment */
 PARM(jogTimeMax),              /* 0x47 jog time max */

// taper parameters

 PARM(taperCycleDist),          /* 0x48 taperCycleDist */

// index pulse variables

 PARM(indexPreScaler),          /* 0x49 index pre scaler */
 PARM(lastIndexPeriod),         /* 0x4a last index period */
 PARM(indexPeriod),             /* 0x4b index period */
 PARM(revCounter),              /* 0x4c revolution counter */

// z home offset

 PARM(zHomeOffset),             /* 0x4d z home offset */

// x home offset

 PARM(xHomeOffset),             /* 0x4e x home offset */

// z home parameters

 PARM(zHomeSpeed),              /* 0x4f z final homing speed */
 PARM(zHomeDist),               /* 0x50 z max homing distance */
 PARM(zHomeDistRev),            /* 0x51 z max reverse homing distance */
 PARM(zHomeDistBackoff),        /* 0x52 z home backoff dist */
 PARM(zHomeDir),                /* 0x53 z homing direction */

// x home parameters

 PARM(xHomeSpeed),              /* 0x54 x final homing speed */
 PARM(xHomeDist),               /* 0x55 x max homing distance */
 PARM(xHomeDistRev),            /* 0x56 x max reverse homing distance */
 PARM(xHomeDistBackoff),        /* 0x57 x home backoff dist */
 PARM(xHomeDir),                /* 0x58 x homing direction */

// x home test parameters

 PARM(xHomeLoc),                /* 0x59 x home test location */
 PARM(xHomeStart),              /* 0x5a x start of home signal */
 PARM(xHomeEnd),                /* 0x5b x end of home signal */

// z dro

 PARM(zDroLoc),                 /* 0x5c z dro location */
 PARM(zDroOffset),              /* 0x5d z dro to zero */
 PARM(zDroCountInch),           /* 0x5e z dro scale */
 PARM(zDroFactor),              /* 0x5f x dro counts inch factored */
 PARM(zDroInvert),              /* 0x60 z dro invert */
 PARM(zUseDro),                 /* 0x61 z use dro for position */
 PARM(zDoneDelay),              /* 0x62 z done to read dro delay */
 PARM(zDroFinalDist),           /* 0x63 z final approach distance */

// x dro

 PARM(xDroLoc),                 /* 0x64 x dro location */
 PARM(xDroOffset),              /* 0x65 x dro to zero */
 PARM(xDroCountInch),           /* 0x66 x dro scale */
 PARM(xDroFactor),              /* 0x67 x dro counts inch factored */
 PARM(xDroInvert),              /* 0x68 x dro invert */
 PARM(xUseDro),                 /* 0x69 x use dro for position */
 PARM(xDoneDelay),              /* 0x6a x done to read dro delay */
 PARM(xDroFinalDist),           /* 0x6b x final approach distance */

// x home or probe status

 PARM(xHomeStatus),             /* 0x6c x home status */

// Z home or probe status

 PARM(zHomeStatus),             /* 0x6d z home status */

// probe configuration

 PARM(probeSpeed),              /* 0x6e probe speed */
 PARM(probeDist),               /* 0x6f probe test distance */
 PARM(probeInv),                /* 0x70 invert polarity of probe */

// configuration

 PARM(stepperDrive),            /* 0x71 stepper driven spindle */
 PARM(motorTest),               /* 0x72 use stepper drive to test motor */
 PARM(spindleEncoder),          /* 0x73 motor drive with spindle encoder */
 PARM(spindleSyncBoard),        /* 0x74 spindle sync board */
 PARM(turnSync),                /* 0x75 synchronization type for turning */
 PARM(threadSync),              /* 0x76 synchronization type for threading */
 PARM(capTmrEnable),            /* 0x77 enable capture timer */
 PARM(cfgFpga),                 /* 0x78 using fpga */
 PARM(cfgMpg),                  /* 0x79 manual pulse generator */
 PARM(cfgDro),                  /* 0x7a digital readout */
 PARM(cfgLcd),                  /* 0x7b lcd display */
 PARM(cfgFcy),                  /* 0x7c system clock speed */
 PARM(cfgSwitch),               /* 0x7d spindle off on switch */
 PARM(cfgVarSpeed),             /* 0x7e spindle variable speed */

// setup

 PARM(setupDone),               /* 0x7f setup done */

// encoder counts per revolution

 PARM(encPerRev),               /* 0x80 spindle encoder counts per revolution */

// test encoder setup variables

 PARM(encEnable),               /* 0x81 encoder enable flag */
 PARM(encPreScaler),            /* 0x82 encoder prescaler */
 PARM(encTimer),                /* 0x83 encoder timer counts */
 PARM(encRunCount),             /* 0x84 encoder run count */

// test encoder status variables

 PARM(encRun),                  /* 0x85 encoder running flag */
 PARM(encCounter),              /* 0x86 encoder count in rev */
 PARM(encRevCounter),           /* 0x87 encoder revolution counter */

// measured spindle speed

 PARM(rpm),                     /* 0x88 current rpm */

// fpga frequency variables

 PARM(fpgaFrequency),           /* 0x89 fpga clock frequency */
 PARM(freqMult),                /* 0x8a frequency multiplier */

// xilinx configuration register

 PARM(xCfgReg),                 /* 0x8b xilinx configuration register */

// sync parameters

 PARM(lSyncCycle),              /* 0x8c sync cycle length */
 PARM(lSyncOutput),             /* 0x8d sync outputs per cycle */
 PARM(lSyncPrescaler),          /* 0x8e sync prescaler */

// threading variables

 PARM(thZStart),                /* 0x8f threading z start */
 PARM(thXStart),                /* 0x90 threading x start */
 PARM(tanThreadAngle),          /* 0x91 tangent of threading angle */
 PARM(xFeed),                   /* 0x92 x feed */
 PARM(runoutDistance),          /* 0x93 runout distance */
 PARM(runoutDepth),             /* 0x94 runout depth */

// jog debug

 PARM(jogDebug),                /* 0x95 jog interrupt debug */

// motor and speed control

 PARM(pwmFreq),                 /* 0x96 spindle speed pwm frequency */
 PARM(minSpeed),                /* 0x97 minimum speed for current range */
 PARM(maxSpeed),                /* 0x98 maximum speed for current range */

// current operation

 PARM(currentOp),               /* 0x99 current operation */

// global limits and home

 PARM(limitOverride),           /* 0x9a override limit switches */
 PARM(commonLimits),            /* 0x9b all limit switches on one pin */
 PARM(limitsEnabled),           /* 0x9c limits enabled */
 PARM(commonHome),              /* 0x9d all home switches on one pin */

// z limits and home

 PARM(zLimEna),                 /* 0x9e z limit enable */
 PARM(zLimNegInv),              /* 0x9f z negative limit invert */
 PARM(zLimPosInv),              /* 0xa0 z Positive limit Invert */
 PARM(zHomeEna),                /* 0xa1 z home enable */
 PARM(zHomeInv),                /* 0xa2 z home invert */

// x limits and home

 PARM(xLimEna),                 /* 0xa3 x limit enable */
 PARM(xLimNegInv),              /* 0xa4 x negative limit invert */
 PARM(xLimPosInv),              /* 0xa5 x Positive limit Invert */
 PARM(xHomeEna),                /* 0xa6 x home enable */
 PARM(xHomeInv),                /* 0xa7 x home invert */

// e stop

 PARM(eStopEna),                /* 0xa8 enable estop */
 PARM(eStopInv),                /* 0xa9 invert estop siganl */
 PARM(maxParm),                 /* 0xaa maximum parameter */
};
