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
 PARM(zDirFlag),                /* 0x18 z invert direction */
 PARM(zMpgFlag),                /* 0x19 z invert mpg */

// x axis parameters

 PARM(xPitch),                  /* 0x1a x axis leadscrew pitch */
 PARM(xRatio),                  /* 0x1b x axis ratio */
 PARM(xMicro),                  /* 0x1c x axis micro steps */
 PARM(xMotor),                  /* 0x1d x axis motor steps */
 PARM(xAccelTime),              /* 0x1e x axis acceleration */
 PARM(xAccel),                  /* 0x1f z accel rpm/sec^2 */
 PARM(xBacklash),               /* 0x20 x axis backlash */
 PARM(xDirFlag),                /* 0x21 x invert direction */
 PARM(xMpgFlag),                /* 0x22 x invert mpg */
 PARM(xDiameter),               /* 0x23 x diameter */

// z move parameters

 PARM(zMoveMin),                /* 0x24 z move min speed */
 PARM(zMoveMax),                /* 0x25 z move max speed */

// z jog parameters

 PARM(zJogMin),                 /* 0x26 z jog min speed */
 PARM(zJogMax),                 /* 0x27 z jog max speed */
 PARM(zJogSpeed),               /* 0x28 z jog speed */

// x move parameters

 PARM(xMoveMin),                /* 0x29 x move min speed */
 PARM(xMoveMax),                /* 0x2a x move max speed */

// x jog parameters

 PARM(xJogMin),                 /* 0x2b x jog min speed */
 PARM(xJogMax),                 /* 0x2c x jog max speed */
 PARM(xJogSpeed),               /* 0x2d x jog speed */

// pass information

 PARM(totalPasses),             /* 0x2e total passes */
 PARM(currentPass),             /* 0x2f current passes */
 PARM(mvStatus),                /* 0x30 movement status */

// z axis move values

 PARM(zMoveDist),               /* 0x31 z move distance */
 PARM(zMovePos),                /* 0x32 z move position */
 PARM(zJogDir),                 /* 0x33 x jog direction */
 PARM(zSetLoc),                 /* 0x34 z location to set */
 PARM(zLoc),                    /* 0x35 z dro location */
 PARM(zFlag),                   /* 0x36 z move flag */
 PARM(zAbsLoc),                 /* 0x37 z absolute location */
 PARM(zMpgInc),                 /* 0x38 z man pulse gen incr */
 PARM(zMpgMax),                 /* 0x39 z man pulse max distance */

// x axis move values

 PARM(xMoveDist),               /* 0x3a x move distance */
 PARM(xMovePos),                /* 0x3b x move position */
 PARM(xJogDir),                 /* 0x3c x jog direction */
 PARM(xSetLoc),                 /* 0x3d x location to set */
 PARM(xLoc),                    /* 0x3e x dro location */
 PARM(xFlag),                   /* 0x3f x move flag */
 PARM(xAbsLoc),                 /* 0x40 x absolute location */
 PARM(xMpgInc),                 /* 0x41 X man pulse gen incr */
 PARM(xMpgMax),                 /* 0x42 x man pulse max distance */

// common jog parameters

 PARM(jogTimeInitial),          /* 0x43 jog time initial */
 PARM(jogTimeInc),              /* 0x44 jog time increment */
 PARM(jogTimeMax),              /* 0x45 jog time max */

// taper parameters

 PARM(taperCycleDist),          /* 0x46 taperCycleDist */

// index pulse variables

 PARM(indexPreScaler),          /* 0x47 index pre scaler */
 PARM(lastIndexPeriod),         /* 0x48 last index period */
 PARM(indexPeriod),             /* 0x49 index period */
 PARM(revCounter),              /* 0x4a revolution counter */

// z home offset

 PARM(zHomeOffset),             /* 0x4b z home offset */

// z dro

 PARM(zDroPos),                 /* 0x4c z dro location */
 PARM(zDroOffset),              /* 0x4d z dro to zero */
 PARM(zDroCountInch),           /* 0x4e z dro scale */
 PARM(zDroInvert),              /* 0x4f z dro invert */

// x home parameters

 PARM(xHomeSpeed),              /* 0x50 x final homing speed */
 PARM(xHomeDist),               /* 0x51 x max homing distance */
 PARM(xHomeBackoffDist),        /* 0x52 x home backoff dist */
 PARM(xHomeDir),                /* 0x53 x homing direction */

// x home test parameters

 PARM(xHomeLoc),                /* 0x54 x home test location */
 PARM(xHomeStart),              /* 0x55 x start of home signal */
 PARM(xHomeEnd),                /* 0x56 x end of home signal */
 PARM(xHomeOffset),             /* 0x57 x home offset */
 PARM(xDroPos),                 /* 0x58 x dro location */
 PARM(xDroOffset),              /* 0x59 x dro to zero */
 PARM(xDroCountInch),           /* 0x5a x dro scale */
 PARM(xDroInvert),              /* 0x5b x dro invert */

// x home or probe status

 PARM(xHomeDone),               /* 0x5c x home done */
 PARM(xHomeStatus),             /* 0x5d x home status */

// Z home or probe status

 PARM(zHomeDone),               /* 0x5e z home done */
 PARM(zHomeStatus),             /* 0x5f z home status */

// probe configuration

 PARM(probeSpeed),              /* 0x60 probe speed */
 PARM(probeDist),               /* 0x61 probe test distance */
 PARM(probeInv),                /* 0x62 invert polarity of probe */

// configuration

 PARM(stepperDrive),            /* 0x63 stepper driven spindle */
 PARM(motorTest),               /* 0x64 use stepper drive to test motor */
 PARM(spindleEncoder),          /* 0x65 motor drive with spindle encoder */
 PARM(spindleSyncBoard),        /* 0x66 spindle sync board */
 PARM(turnSync),                /* 0x67 synchronization type for turning */
 PARM(threadSync),              /* 0x68 synchronization type for threading */
 PARM(capTmrEnable),            /* 0x69 enable capture timer */
 PARM(cfgXilinx),               /* 0x6a using xilinx */
 PARM(cfgMpg),                  /* 0x6b manual pulse generator */
 PARM(cfgDro),                  /* 0x6c digital readout */
 PARM(cfgLcd),                  /* 0x6d lcd display */
 PARM(cfgFcy),                  /* 0x6e system clock speed */
 PARM(cfgSwitch),               /* 0x6f spindle off on switch */
 PARM(cfgVarSpeed),             /* 0x70 spindle variable speed */

// setup

 PARM(setupDone),               /* 0x71 setup done */

// encoder counts per revolution

 PARM(encPerRev),               /* 0x72 spindle encoder counts per revolution */

// test encoder setup variables

 PARM(encEnable),               /* 0x73 encoder enable flag */
 PARM(encPreScaler),            /* 0x74 encoder prescaler */
 PARM(encTimer),                /* 0x75 encoder timer counts */
 PARM(encRunCount),             /* 0x76 encoder run count */

// test encoder status variables

 PARM(encRun),                  /* 0x77 encoder running flag */
 PARM(encCounter),              /* 0x78 encoder count in rev */
 PARM(encRevCounter),           /* 0x79 encoder revolution counter */

// measured spindle speed

 PARM(rpm),                     /* 0x7a current rpm */

// xilinx frequency variables

 PARM(xFrequency),              /* 0x7b xilinx clock frequency */
 PARM(freqMult),                /* 0x7c frequency multiplier */

// xilinx configuration register

 PARM(xCfgReg),                 /* 0x7d xilinx configuration register */

// sync parameters

 PARM(lSyncCycle),              /* 0x7e sync cycle length */
 PARM(lSyncOutput),             /* 0x7f sync outputs per cycle */
 PARM(lSyncPrescaler),          /* 0x80 sync prescaler */

// threading variables

 PARM(thZStart),                /* 0x81 threading z start */
 PARM(thXStart),                /* 0x82 threading x start */
 PARM(tanThreadAngle),          /* 0x83 tangent of threading angle */
 PARM(xFeed),                   /* 0x84 x feed */
 PARM(runoutDistance),          /* 0x85 runout distance */
 PARM(runoutDepth),             /* 0x86 runout depth */

// jog debug

 PARM(jogDebug),                /* 0x87 jog interrupt debug */

// motor and speed control

 PARM(pwmFreq),                 /* 0x88 spindle speed pwm frequency */
 PARM(minSpeed),                /* 0x89 minimum speed for current range */
 PARM(maxSpeed),                /* 0x8a maximum speed for current range */

// current operation

 PARM(currentOp),               /* 0x8b current operation */
 PARM(maxParm),                 /* 0x8c maximum parameter */
};
