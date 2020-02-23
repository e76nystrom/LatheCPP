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

// z dro

 PARM(zDroPos),                 /* 0x4d z dro location */
 PARM(zDroOffset),              /* 0x4e z dro to zero */
 PARM(zDroCountInch),           /* 0x4f z dro scale */
 PARM(zDroInvert),              /* 0x50 z dro invert */
 PARM(zUseDro),                 /* 0x51 z use dro for position */

// x home parameters

 PARM(xHomeSpeed),              /* 0x52 x final homing speed */
 PARM(xHomeDist),               /* 0x53 x max homing distance */
 PARM(xHomeBackoffDist),        /* 0x54 x home backoff dist */
 PARM(xHomeDir),                /* 0x55 x homing direction */

// x home test parameters

 PARM(xHomeLoc),                /* 0x56 x home test location */
 PARM(xHomeStart),              /* 0x57 x start of home signal */
 PARM(xHomeEnd),                /* 0x58 x end of home signal */
 PARM(xHomeOffset),             /* 0x59 x home offset */
 PARM(xDroPos),                 /* 0x5a x dro location */
 PARM(xDroOffset),              /* 0x5b x dro to zero */
 PARM(xDroCountInch),           /* 0x5c x dro scale */
 PARM(xDroFactor),              /* 0x5d x dro counts inch factored */
 PARM(xDroInvert),              /* 0x5e x dro invert */
 PARM(xUseDro),                 /* 0x5f x use dro for position */
 PARM(xDoneDelay),              /* 0x60 x done to read dro delay */
 PARM(xDroFinalDist),           /* 0x61 x final approach distance */

// x home or probe status

 PARM(xHomeDone),               /* 0x62 x home done */
 PARM(xHomeStatus),             /* 0x63 x home status */

// Z home or probe status

 PARM(zHomeDone),               /* 0x64 z home done */
 PARM(zHomeStatus),             /* 0x65 z home status */

// probe configuration

 PARM(probeSpeed),              /* 0x66 probe speed */
 PARM(probeDist),               /* 0x67 probe test distance */
 PARM(probeInv),                /* 0x68 invert polarity of probe */

// configuration

 PARM(stepperDrive),            /* 0x69 stepper driven spindle */
 PARM(motorTest),               /* 0x6a use stepper drive to test motor */
 PARM(spindleEncoder),          /* 0x6b motor drive with spindle encoder */
 PARM(spindleSyncBoard),        /* 0x6c spindle sync board */
 PARM(turnSync),                /* 0x6d synchronization type for turning */
 PARM(threadSync),              /* 0x6e synchronization type for threading */
 PARM(capTmrEnable),            /* 0x6f enable capture timer */
 PARM(cfgFpga),                 /* 0x70 using fpga */
 PARM(cfgMpg),                  /* 0x71 manual pulse generator */
 PARM(cfgDro),                  /* 0x72 digital readout */
 PARM(cfgLcd),                  /* 0x73 lcd display */
 PARM(cfgFcy),                  /* 0x74 system clock speed */
 PARM(cfgSwitch),               /* 0x75 spindle off on switch */
 PARM(cfgVarSpeed),             /* 0x76 spindle variable speed */

// setup

 PARM(setupDone),               /* 0x77 setup done */

// encoder counts per revolution

 PARM(encPerRev),               /* 0x78 spindle encoder counts per revolution */

// test encoder setup variables

 PARM(encEnable),               /* 0x79 encoder enable flag */
 PARM(encPreScaler),            /* 0x7a encoder prescaler */
 PARM(encTimer),                /* 0x7b encoder timer counts */
 PARM(encRunCount),             /* 0x7c encoder run count */

// test encoder status variables

 PARM(encRun),                  /* 0x7d encoder running flag */
 PARM(encCounter),              /* 0x7e encoder count in rev */
 PARM(encRevCounter),           /* 0x7f encoder revolution counter */

// measured spindle speed

 PARM(rpm),                     /* 0x80 current rpm */

// fpga frequency variables

 PARM(fpgaFrequency),           /* 0x81 fpga clock frequency */
 PARM(freqMult),                /* 0x82 frequency multiplier */

// xilinx configuration register

 PARM(xCfgReg),                 /* 0x83 xilinx configuration register */

// sync parameters

 PARM(lSyncCycle),              /* 0x84 sync cycle length */
 PARM(lSyncOutput),             /* 0x85 sync outputs per cycle */
 PARM(lSyncPrescaler),          /* 0x86 sync prescaler */

// threading variables

 PARM(thZStart),                /* 0x87 threading z start */
 PARM(thXStart),                /* 0x88 threading x start */
 PARM(tanThreadAngle),          /* 0x89 tangent of threading angle */
 PARM(xFeed),                   /* 0x8a x feed */
 PARM(runoutDistance),          /* 0x8b runout distance */
 PARM(runoutDepth),             /* 0x8c runout depth */

// jog debug

 PARM(jogDebug),                /* 0x8d jog interrupt debug */

// motor and speed control

 PARM(pwmFreq),                 /* 0x8e spindle speed pwm frequency */
 PARM(minSpeed),                /* 0x8f minimum speed for current range */
 PARM(maxSpeed),                /* 0x90 maximum speed for current range */

// current operation

 PARM(currentOp),               /* 0x91 current operation */
 PARM(maxParm),                 /* 0x92 maximum parameter */
};
