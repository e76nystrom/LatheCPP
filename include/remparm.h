T_PARM remparm[] =
{

// spindle parameters

 PARM(spSteps),                 /* 0x00 spindle motor steps */
 PARM(spMicro),                 /* 0x01 spindle micro steps */
 PARM(spMinRpm),                /* 0x02 spindle minimum rpm */
 PARM(spMaxRpm),                /* 0x03 spindle maximum rpm */
 PARM(spRpm),                   /* 0x04 spindle rpm */
 PARM(spAccelTime),             /* 0x05 spindle accel time */
 PARM(spAccel),                 /* 0x06 spindle accel rpm/sec^2 */
 PARM(spJogMinRpm),             /* 0x07 spindle jog minimum rpm */
 PARM(spJogMaxRpm),             /* 0x08 spindle jog maximum rpm */
 PARM(spJogRpm),                /* 0x09 spindle jog rpm */
 PARM(spJogAccelTime),          /* 0x0a spindle jog accel time */
 PARM(spJogTimeInitial),        /* 0x0b spindle jog time initl */
 PARM(spJogTimeInc),            /* 0x0c spindle jog time increment */
 PARM(spJogTimeMax),            /* 0x0d spindle jog timemax */
 PARM(spJogDir),                /* 0x0e spindle direction */
 PARM(spDirFlag),               /* 0x0f spindle invert direction */
 PARM(spTestIndex),             /* 0x10 generate test index pulse */
 PARM(spTestEncoder),           /* 0x11 generate enc test pulse */

// z axis parameters

 PARM(zPitch),                  /* 0x12 z axis leadscrew pitch */
 PARM(zRatio),                  /* 0x13 z axis ratio */
 PARM(zMicro),                  /* 0x14 z axis micro steps */
 PARM(zMotor),                  /* 0x15 z axis motor steps */
 PARM(zAccelTime),              /* 0x16 z axis acceleration */
 PARM(zAccel),                  /* 0x17 z accel rpm/sec^2 */
 PARM(zBacklash),               /* 0x18 z axis backlash */
 PARM(zStepFactor),             /* 0x19 z steps inch factored */
 PARM(zDirFlag),                /* 0x1a z invert direction */
 PARM(zMpgFlag),                /* 0x1b z invert mpg */

// x axis parameters

 PARM(xPitch),                  /* 0x1c x axis leadscrew pitch */
 PARM(xRatio),                  /* 0x1d x axis ratio */
 PARM(xMicro),                  /* 0x1e x axis micro steps */
 PARM(xMotor),                  /* 0x1f x axis motor steps */
 PARM(xAccelTime),              /* 0x20 x axis acceleration */
 PARM(xAccel),                  /* 0x21 x accel rpm/sec^2 */
 PARM(xBacklash),               /* 0x22 x axis backlash */
 PARM(xStepFactor),             /* 0x23 x steps inch factored */
 PARM(xDirFlag),                /* 0x24 x invert direction */
 PARM(xMpgFlag),                /* 0x25 x invert mpg */
 PARM(xDiameter),               /* 0x26 x diameter */

// z move parameters

 PARM(zMoveMin),                /* 0x27 z move min speed */
 PARM(zMoveMax),                /* 0x28 z move max speed */

// z jog parameters

 PARM(zJogMin),                 /* 0x29 z jog min speed */
 PARM(zJogMax),                 /* 0x2a z jog max speed */
 PARM(zJogSpeed),               /* 0x2b z jog speed */

// x move parameters

 PARM(xMoveMin),                /* 0x2c x move min speed */
 PARM(xMoveMax),                /* 0x2d x move max speed */

// x jog parameters

 PARM(xJogMin),                 /* 0x2e x jog min speed */
 PARM(xJogMax),                 /* 0x2f x jog max speed */
 PARM(xJogSpeed),               /* 0x30 x jog speed */

// pass information

 PARM(totalPasses),             /* 0x31 total passes */
 PARM(currentPass),             /* 0x32 current passes */
 PARM(mvStatus),                /* 0x33 movement status */

// z axis move values

 PARM(zMoveDist),               /* 0x34 z move distance */
 PARM(zMovePos),                /* 0x35 z move position */
 PARM(zJogDir),                 /* 0x36 x jog direction */
 PARM(zSetLoc),                 /* 0x37 z location to set */
 PARM(zLoc),                    /* 0x38 z dro location */
 PARM(zFlag),                   /* 0x39 z move flag */
 PARM(zAbsLoc),                 /* 0x3a z absolute location */
 PARM(zMpgInc),                 /* 0x3b z man pulse gen incr */
 PARM(zMpgMax),                 /* 0x3c z man pulse max distance */

// x axis move values

 PARM(xMoveDist),               /* 0x3d x move distance */
 PARM(xMovePos),                /* 0x3e x move position */
 PARM(xJogDir),                 /* 0x3f x jog direction */
 PARM(xSetLoc),                 /* 0x40 x location to set */
 PARM(xLoc),                    /* 0x41 x dro location */
 PARM(xFlag),                   /* 0x42 x move flag */
 PARM(xAbsLoc),                 /* 0x43 x absolute location */
 PARM(xMpgInc),                 /* 0x44 X man pulse gen incr */
 PARM(xMpgMax),                 /* 0x45 x man pulse max distance */

// common jog parameters

 PARM(jogTimeInitial),          /* 0x46 jog time initial */
 PARM(jogTimeInc),              /* 0x47 jog time increment */
 PARM(jogTimeMax),              /* 0x48 jog time max */

// taper parameters

 PARM(taperCycleDist),          /* 0x49 taperCycleDist */

// index pulse variables

 PARM(indexPreScaler),          /* 0x4a index pre scaler */
 PARM(lastIndexPeriod),         /* 0x4b last index period */
 PARM(indexPeriod),             /* 0x4c index period */
 PARM(revCounter),              /* 0x4d revolution counter */

// z home offset

 PARM(zHomeOffset),             /* 0x4e z home offset */

// x home offset

 PARM(xHomeOffset),             /* 0x4f x home offset */

// z home parameters

 PARM(zHomeSpeed),              /* 0x50 z final homing speed */
 PARM(zHomeDist),               /* 0x51 z max homing distance */
 PARM(zHomeDistRev),            /* 0x52 z max rev homing distance */
 PARM(zHomeDistBackoff),        /* 0x53 z home backoff dist */
 PARM(zHomeDir),                /* 0x54 z homing direction */

// x home parameters

 PARM(xHomeSpeed),              /* 0x55 x final homing speed */
 PARM(xHomeDist),               /* 0x56 x max homing distance */
 PARM(xHomeDistRev),            /* 0x57 x max rev homing distance */
 PARM(xHomeDistBackoff),        /* 0x58 x home backoff dist */
 PARM(xHomeDir),                /* 0x59 x homing direction */

// x home test parameters

 PARM(xHomeLoc),                /* 0x5a x home test location */
 PARM(xHomeStart),              /* 0x5b x start of home signal */
 PARM(xHomeEnd),                /* 0x5c x end of home signal */

// z dro

 PARM(zDroLoc),                 /* 0x5d z dro location */
 PARM(zDroOffset),              /* 0x5e z dro to zero */
 PARM(zDroCountInch),           /* 0x5f z dro scale */
 PARM(zDroFactor),              /* 0x60 x dro counts inch factored */
 PARM(zDroInvert),              /* 0x61 z dro invert */
 PARM(zUseDro),                 /* 0x62 z use dro for position */
 PARM(zDoneDelay),              /* 0x63 z done to read dro delay */
 PARM(zDroFinalDist),           /* 0x64 z final approach distance */

// x dro

 PARM(xDroLoc),                 /* 0x65 x dro location */
 PARM(xDroOffset),              /* 0x66 x dro to zero */
 PARM(xDroCountInch),           /* 0x67 x dro scale */
 PARM(xDroFactor),              /* 0x68 x dro counts inch factored */
 PARM(xDroInvert),              /* 0x69 x dro invert */
 PARM(xUseDro),                 /* 0x6a x use dro for position */
 PARM(xDoneDelay),              /* 0x6b x done to read dro delay */
 PARM(xDroFinalDist),           /* 0x6c x final approach distance */

// x home or probe status

 PARM(xHomeStatus),             /* 0x6d x home status */

// Z home or probe status

 PARM(zHomeStatus),             /* 0x6e z home status */

// probe configuration

 PARM(probeSpeed),              /* 0x6f probe speed */
 PARM(probeDist),               /* 0x70 probe test distance */
 PARM(probeInv),                /* 0x71 invert polarity of probe */

// configuration

 PARM(stepperDrive),            /* 0x72 stepper driven spindle */
 PARM(motorTest),               /* 0x73 use stepper to test motor */
 PARM(spindleEncoder),          /* 0x74 motor with spindle enc */
 PARM(spindleSyncBoard),        /* 0x75 spindle sync board */
 PARM(turnSync),                /* 0x76 sync type for turning */
 PARM(threadSync),              /* 0x77 sync type for threading */
 PARM(capTmrEnable),            /* 0x78 enable capture timer */
 PARM(cfgFpga),                 /* 0x79 using fpga */
 PARM(cfgMega),                 /* 0x7a control link to mega */
 PARM(cfgMpg),                  /* 0x7b manual pulse generator */
 PARM(cfgDro),                  /* 0x7c digital readout */
 PARM(cfgLcd),                  /* 0x7d lcd display */
 PARM(cfgFcy),                  /* 0x7e system clock speed */
 PARM(cfgSwitch),               /* 0x7f spindle off on switch */
 PARM(cfgVarSpeed),             /* 0x80 spindle variable speed */

// setup

 PARM(setupDone),               /* 0x81 setup done */

// encoder counts per revolution

 PARM(encPerRev),               /* 0x82 spindle enc counts per rev */

// test encoder setup variables

 PARM(encEnable),               /* 0x83 encoder enable flag */
 PARM(encPreScaler),            /* 0x84 encoder prescaler */
 PARM(encTimer),                /* 0x85 encoder timer counts */
 PARM(encRunCount),             /* 0x86 encoder run count */

// test encoder status variables

 PARM(encRun),                  /* 0x87 encoder running flag */
 PARM(encCounter),              /* 0x88 encoder count in rev */
 PARM(encRevCounter),           /* 0x89 encoder revolution counter */

// measured spindle speed

 PARM(rpm),                     /* 0x8a current measured rpm */

// fpga frequency variables

 PARM(fpgaFrequency),           /* 0x8b fpga clock frequency */
 PARM(freqMult),                /* 0x8c frequency multiplier */

// xilinx configuration register

 PARM(xCfgReg),                 /* 0x8d xilinx cfg register */

// sync parameters

 PARM(lSyncCycle),              /* 0x8e sync cycle length */
 PARM(lSyncOutput),             /* 0x8f sync outputs per cycle */
 PARM(lSyncPrescaler),          /* 0x90 sync prescaler */

// threading variables

 PARM(thZStart),                /* 0x91 threading z start */
 PARM(thXStart),                /* 0x92 threading x start */
 PARM(tanThreadAngle),          /* 0x93 tan of threading angle */
 PARM(xFeed),                   /* 0x94 x feed */
 PARM(runoutDistance),          /* 0x95 runout distance */
 PARM(runoutDepth),             /* 0x96 runout depth */

// jog debug

 PARM(jogDebug),                /* 0x97 jog interrupt debug */

// motor and speed control

 PARM(pwmFreq),                 /* 0x98 spindle speed pwm frequency */
 PARM(minSpeed),                /* 0x99 min speed for current range */
 PARM(maxSpeed),                /* 0x9a max speed for current range */

// current operation

 PARM(currentOp),               /* 0x9b current operation */

// global limits and home

 PARM(limitOverride),           /* 0x9c override limit switches */
 PARM(commonLimits),            /* 0x9d all limit switches one pin */
 PARM(limitsEnabled),           /* 0x9e limits enabled */
 PARM(commonHome),              /* 0x9f all home switches one pin */

// z limits and home

 PARM(zLimEna),                 /* 0xa0 z limit enable */
 PARM(zLimNegInv),              /* 0xa1 z negative limit invert */
 PARM(zLimPosInv),              /* 0xa2 z Positive limit Invert */
 PARM(zHomeEna),                /* 0xa3 z home enable */
 PARM(zHomeInv),                /* 0xa4 z home invert */

// x limits and home

 PARM(xLimEna),                 /* 0xa5 x limit enable */
 PARM(xLimNegInv),              /* 0xa6 x negative limit invert */
 PARM(xLimPosInv),              /* 0xa7 x Positive limit Invert */
 PARM(xHomeEna),                /* 0xa8 x home enable */
 PARM(xHomeInv),                /* 0xa9 x home invert */

// e stop

 PARM(eStopEna),                /* 0xaa enable estop */
 PARM(eStopInv),                /* 0xab invert estop siganl */

// command pause

 PARM(cmdPaused),               /* 0xac move commands paused */

// arc parameters

 PARM(arcRadius),               /* 0xad arc radius */
 PARM(arcXCenter),              /* 0xae arc x center */
 PARM(arcZCenter),              /* 0xaf arc z center */
 PARM(arcXStart),               /* 0xb0 arc x start */
 PARM(arcZStart),               /* 0xb1 arc z start */
 PARM(arcXEnd),                 /* 0xb2 arc x center */
 PARM(arcZEnd),                 /* 0xb3 arc z center */
 PARM(maxParm),                 /* 0xb4 maximum parameter */
};
