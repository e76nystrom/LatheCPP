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
 PARM(xStepFactor),             /* 0x18 x steps inch factored */
 PARM(zDirFlag),                /* 0x19 z invert direction */
 PARM(zMpgFlag),                /* 0x1a z invert mpg */

// x axis parameters

 PARM(xPitch),                  /* 0x1b x axis leadscrew pitch */
 PARM(xRatio),                  /* 0x1c x axis ratio */
 PARM(xMicro),                  /* 0x1d x axis micro steps */
 PARM(xMotor),                  /* 0x1e x axis motor steps */
 PARM(xAccelTime),              /* 0x1f x axis acceleration */
 PARM(xAccel),                  /* 0x20 z accel rpm/sec^2 */
 PARM(xBacklash),               /* 0x21 x axis backlash */
 PARM(xDirFlag),                /* 0x22 x invert direction */
 PARM(xMpgFlag),                /* 0x23 x invert mpg */
 PARM(xDiameter),               /* 0x24 x diameter */

// z move parameters

 PARM(zMoveMin),                /* 0x25 z move min speed */
 PARM(zMoveMax),                /* 0x26 z move max speed */

// z jog parameters

 PARM(zJogMin),                 /* 0x27 z jog min speed */
 PARM(zJogMax),                 /* 0x28 z jog max speed */
 PARM(zJogSpeed),               /* 0x29 z jog speed */

// x move parameters

 PARM(xMoveMin),                /* 0x2a x move min speed */
 PARM(xMoveMax),                /* 0x2b x move max speed */

// x jog parameters

 PARM(xJogMin),                 /* 0x2c x jog min speed */
 PARM(xJogMax),                 /* 0x2d x jog max speed */
 PARM(xJogSpeed),               /* 0x2e x jog speed */

// pass information

 PARM(totalPasses),             /* 0x2f total passes */
 PARM(currentPass),             /* 0x30 current passes */
 PARM(mvStatus),                /* 0x31 movement status */

// z axis move values

 PARM(zMoveDist),               /* 0x32 z move distance */
 PARM(zMovePos),                /* 0x33 z move position */
 PARM(zJogDir),                 /* 0x34 x jog direction */
 PARM(zSetLoc),                 /* 0x35 z location to set */
 PARM(zLoc),                    /* 0x36 z dro location */
 PARM(zFlag),                   /* 0x37 z move flag */
 PARM(zAbsLoc),                 /* 0x38 z absolute location */
 PARM(zMpgInc),                 /* 0x39 z man pulse gen incr */
 PARM(zMpgMax),                 /* 0x3a z man pulse max distance */

// x axis move values

 PARM(xMoveDist),               /* 0x3b x move distance */
 PARM(xMovePos),                /* 0x3c x move position */
 PARM(xJogDir),                 /* 0x3d x jog direction */
 PARM(xSetLoc),                 /* 0x3e x location to set */
 PARM(xLoc),                    /* 0x3f x dro location */
 PARM(xFlag),                   /* 0x40 x move flag */
 PARM(xAbsLoc),                 /* 0x41 x absolute location */
 PARM(xMpgInc),                 /* 0x42 X man pulse gen incr */
 PARM(xMpgMax),                 /* 0x43 x man pulse max distance */

// common jog parameters

 PARM(jogTimeInitial),          /* 0x44 jog time initial */
 PARM(jogTimeInc),              /* 0x45 jog time increment */
 PARM(jogTimeMax),              /* 0x46 jog time max */

// taper parameters

 PARM(taperCycleDist),          /* 0x47 taperCycleDist */

// index pulse variables

 PARM(indexPreScaler),          /* 0x48 index pre scaler */
 PARM(lastIndexPeriod),         /* 0x49 last index period */
 PARM(indexPeriod),             /* 0x4a index period */
 PARM(revCounter),              /* 0x4b revolution counter */

// z home offset

 PARM(zHomeOffset),             /* 0x4c z home offset */

// x home offset

 PARM(xHomeOffset),             /* 0x4d x home offset */

// z home parameters

 PARM(zHomeSpeed),              /* 0x4e z final homing speed */
 PARM(zHomeDist),               /* 0x4f z max homing distance */
 PARM(zHomeBackoffDist),        /* 0x50 z home backoff dist */
 PARM(zHomeDir),                /* 0x51 z homing direction */

// x home parameters

 PARM(xHomeSpeed),              /* 0x52 x final homing speed */
 PARM(xHomeDist),               /* 0x53 x max homing distance */
 PARM(xHomeBackoffDist),        /* 0x54 x home backoff dist */
 PARM(xHomeDir),                /* 0x55 x homing direction */

// x home test parameters

 PARM(xHomeLoc),                /* 0x56 x home test location */
 PARM(xHomeStart),              /* 0x57 x start of home signal */
 PARM(xHomeEnd),                /* 0x58 x end of home signal */

// z dro

 PARM(zDroPos),                 /* 0x59 z dro location */
 PARM(zDroOffset),              /* 0x5a z dro to zero */
 PARM(zDroCountInch),           /* 0x5b z dro scale */
 PARM(zDroInvert),              /* 0x5c z dro invert */
 PARM(zUseDro),                 /* 0x5d z use dro for position */
 PARM(zDoneDelay),              /* 0x5e z done to read dro delay */
 PARM(zDroFinalDist),           /* 0x5f z final approach distance */

// x dro

 PARM(xDroPos),                 /* 0x60 x dro location */
 PARM(xDroOffset),              /* 0x61 x dro to zero */
 PARM(xDroCountInch),           /* 0x62 x dro scale */
 PARM(xDroFactor),              /* 0x63 x dro counts inch factored */
 PARM(xDroInvert),              /* 0x64 x dro invert */
 PARM(xUseDro),                 /* 0x65 x use dro for position */
 PARM(xDoneDelay),              /* 0x66 x done to read dro delay */
 PARM(xDroFinalDist),           /* 0x67 x final approach distance */

// x home or probe status

 PARM(xHomeDone),               /* 0x68 x home done */
 PARM(xHomeStatus),             /* 0x69 x home status */

// Z home or probe status

 PARM(zHomeDone),               /* 0x6a z home done */
 PARM(zHomeStatus),             /* 0x6b z home status */

// probe configuration

 PARM(probeSpeed),              /* 0x6c probe speed */
 PARM(probeDist),               /* 0x6d probe test distance */
 PARM(probeInv),                /* 0x6e invert polarity of probe */

// configuration

 PARM(stepperDrive),            /* 0x6f stepper driven spindle */
 PARM(motorTest),               /* 0x70 use stepper drive to test motor */
 PARM(spindleEncoder),          /* 0x71 motor drive with spindle encoder */
 PARM(spindleSyncBoard),        /* 0x72 spindle sync board */
 PARM(turnSync),                /* 0x73 synchronization type for turning */
 PARM(threadSync),              /* 0x74 synchronization type for threading */
 PARM(capTmrEnable),            /* 0x75 enable capture timer */
 PARM(cfgFpga),                 /* 0x76 using fpga */
 PARM(cfgMpg),                  /* 0x77 manual pulse generator */
 PARM(cfgDro),                  /* 0x78 digital readout */
 PARM(cfgLcd),                  /* 0x79 lcd display */
 PARM(cfgFcy),                  /* 0x7a system clock speed */
 PARM(cfgSwitch),               /* 0x7b spindle off on switch */
 PARM(cfgVarSpeed),             /* 0x7c spindle variable speed */

// setup

 PARM(setupDone),               /* 0x7d setup done */

// encoder counts per revolution

 PARM(encPerRev),               /* 0x7e spindle encoder counts per revolution */

// test encoder setup variables

 PARM(encEnable),               /* 0x7f encoder enable flag */
 PARM(encPreScaler),            /* 0x80 encoder prescaler */
 PARM(encTimer),                /* 0x81 encoder timer counts */
 PARM(encRunCount),             /* 0x82 encoder run count */

// test encoder status variables

 PARM(encRun),                  /* 0x83 encoder running flag */
 PARM(encCounter),              /* 0x84 encoder count in rev */
 PARM(encRevCounter),           /* 0x85 encoder revolution counter */

// measured spindle speed

 PARM(rpm),                     /* 0x86 current rpm */

// fpga frequency variables

 PARM(fpgaFrequency),           /* 0x87 fpga clock frequency */
 PARM(freqMult),                /* 0x88 frequency multiplier */

// xilinx configuration register

 PARM(xCfgReg),                 /* 0x89 xilinx configuration register */

// sync parameters

 PARM(lSyncCycle),              /* 0x8a sync cycle length */
 PARM(lSyncOutput),             /* 0x8b sync outputs per cycle */
 PARM(lSyncPrescaler),          /* 0x8c sync prescaler */

// threading variables

 PARM(thZStart),                /* 0x8d threading z start */
 PARM(thXStart),                /* 0x8e threading x start */
 PARM(tanThreadAngle),          /* 0x8f tangent of threading angle */
 PARM(xFeed),                   /* 0x90 x feed */
 PARM(runoutDistance),          /* 0x91 runout distance */
 PARM(runoutDepth),             /* 0x92 runout depth */

// jog debug

 PARM(jogDebug),                /* 0x93 jog interrupt debug */

// motor and speed control

 PARM(pwmFreq),                 /* 0x94 spindle speed pwm frequency */
 PARM(minSpeed),                /* 0x95 minimum speed for current range */
 PARM(maxSpeed),                /* 0x96 maximum speed for current range */

// current operation

 PARM(currentOp),               /* 0x97 current operation */

// global limits and home

 PARM(limitOverride),           /* 0x98 override limit switches */
 PARM(commonLimits),            /* 0x99 all limit switches on one pin */
 PARM(limitsEnabled),           /* 0x9a limits enabled */
 PARM(commonHome),              /* 0x9b all home switches on one pin */

// z limits and home

 PARM(zLimEna),                 /* 0x9c z limit enable */
 PARM(zLimNegInv),              /* 0x9d z negative limit invert */
 PARM(zLimPosInv),              /* 0x9e z Positive limit Invert */
 PARM(zHomeEna),                /* 0x9f z home enable */
 PARM(zHomeInv),                /* 0xa0 z home invert */

// x limits and home

 PARM(xLimEna),                 /* 0xa1 x limit enable */
 PARM(xLimNegInv),              /* 0xa2 x negative limit invert */
 PARM(xLimPosInv),              /* 0xa3 x Positive limit Invert */
 PARM(xHomeEna),                /* 0xa4 x home enable */
 PARM(xHomeInv),                /* 0xa5 x home invert */

// e stop

 PARM(eStopEna),                /* 0xa6 enable estop */
 PARM(eStopInv),                /* 0xa7 invert estop siganl */
 PARM(maxParm),                 /* 0xa8 maximum parameter */
};
