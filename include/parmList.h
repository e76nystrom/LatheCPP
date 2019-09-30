enum PARM
{

// spindle parameters

 SP_STEPS,                      /* 0x00 spindle motor steps */
 SP_MICRO,                      /* 0x01 spindle micro steps */
 SP_MIN_RPM,                    /* 0x02 spindle minimum rpm */
 SP_MAX_RPM,                    /* 0x03 spindle maxmum rpm */
 SP_ACCEL_TIME,                 /* 0x04 spindle accel time */
 SP_ACCEL,                      /* 0x05 spindle accel rpm/sec^2 */
 SP_JOG_MIN_RPM,                /* 0x06 spindle jog minimum rpm */
 SP_JOG_MAX_RPM,                /* 0x07 spindle jog maxmum rpm */
 SP_JOG_RPM,                    /* 0x08 spindle jog rpm */
 SP_JOG_ACCEL_TIME,             /* 0x09 spindle jog accel time */
 SP_JOG_TIME_INITIAL,           /* 0x0a spindle jog time initial */
 SP_JOG_TIME_INC,               /* 0x0b spindle jog time increment */
 SP_JOG_TIME_MAX,               /* 0x0c spindle jog timemax */
 SP_JOG_DIR,                    /* 0x0d spindle direction */
 SP_DIR_FLAG,                   /* 0x0e spindle invert direction */
 SP_TEST_INDEX,                 /* 0x0f generate test index pulse */
 SP_TEST_ENCODER,               /* 0x10 generate encoder test pulse */

// z axis parameters

 Z_PITCH,                       /* 0x11 z axis leadscrew pitch */
 Z_RATIO,                       /* 0x12 z axis ratio */
 Z_MICRO,                       /* 0x13 z axis micro steps */
 Z_MOTOR,                       /* 0x14 z axis motor steps */
 Z_ACCEL_TIME,                  /* 0x15 z axis acceleration */
 Z_ACCEL,                       /* 0x16 z accel rpm/sec^2 */
 Z_BACKLASH,                    /* 0x17 z axis backlash */
 X_STEP_FACTOR,                 /* 0x18 x steps inch factored */
 Z_DIR_FLAG,                    /* 0x19 z invert direction */
 Z_MPG_FLAG,                    /* 0x1a z invert mpg */

// x axis parameters

 X_PITCH,                       /* 0x1b x axis leadscrew pitch */
 X_RATIO,                       /* 0x1c x axis ratio */
 X_MICRO,                       /* 0x1d x axis micro steps */
 X_MOTOR,                       /* 0x1e x axis motor steps */
 X_ACCEL_TIME,                  /* 0x1f x axis acceleration */
 X_ACCEL,                       /* 0x20 z accel rpm/sec^2 */
 X_BACKLASH,                    /* 0x21 x axis backlash */
 X_DIR_FLAG,                    /* 0x22 x invert direction */
 X_MPG_FLAG,                    /* 0x23 x invert mpg */
 X_DIAMETER,                    /* 0x24 x diameter */

// z move parameters

 Z_MOVE_MIN,                    /* 0x25 z move min speed */
 Z_MOVE_MAX,                    /* 0x26 z move max speed */

// z jog parameters

 Z_JOG_MIN,                     /* 0x27 z jog min speed */
 Z_JOG_MAX,                     /* 0x28 z jog max speed */
 Z_JOG_SPEED,                   /* 0x29 z jog speed */

// x move parameters

 X_MOVE_MIN,                    /* 0x2a x move min speed */
 X_MOVE_MAX,                    /* 0x2b x move max speed */

// x jog parameters

 X_JOG_MIN,                     /* 0x2c x jog min speed */
 X_JOG_MAX,                     /* 0x2d x jog max speed */
 X_JOG_SPEED,                   /* 0x2e x jog speed */

// pass information

 TOTAL_PASSES,                  /* 0x2f total passes */
 CURRENT_PASS,                  /* 0x30 current passes */
 MV_STATUS,                     /* 0x31 movement status */

// z axis move values

 Z_MOVE_DIST,                   /* 0x32 z move distance */
 Z_MOVE_POS,                    /* 0x33 z move position */
 Z_JOG_DIR,                     /* 0x34 x jog direction */
 Z_SET_LOC,                     /* 0x35 z location to set */
 Z_LOC,                         /* 0x36 z dro location */
 Z_FLAG,                        /* 0x37 z move flag */
 Z_ABS_LOC,                     /* 0x38 z absolute location */
 Z_MPG_INC,                     /* 0x39 z man pulse gen incr */
 Z_MPG_MAX,                     /* 0x3a z man pulse max distance */

// x axis move values

 X_MOVE_DIST,                   /* 0x3b x move distance */
 X_MOVE_POS,                    /* 0x3c x move position */
 X_JOG_DIR,                     /* 0x3d x jog direction */
 X_SET_LOC,                     /* 0x3e x location to set */
 X_LOC,                         /* 0x3f x dro location */
 X_FLAG,                        /* 0x40 x move flag */
 X_ABS_LOC,                     /* 0x41 x absolute location */
 X_MPG_INC,                     /* 0x42 X man pulse gen incr */
 X_MPG_MAX,                     /* 0x43 x man pulse max distance */

// common jog parameters

 JOG_TIME_INITIAL,              /* 0x44 jog time initial */
 JOG_TIME_INC,                  /* 0x45 jog time increment */
 JOG_TIME_MAX,                  /* 0x46 jog time max */

// taper parameters

 TAPER_CYCLE_DIST,              /* 0x47 taperCycleDist */

// index pulse variables

 INDEX_PRE_SCALER,              /* 0x48 index pre scaler */
 LAST_INDEX_PERIOD,             /* 0x49 last index period */
 INDEX_PERIOD,                  /* 0x4a index period */
 REV_COUNTER,                   /* 0x4b revolution counter */

// z home offset

 Z_HOME_OFFSET,                 /* 0x4c z home offset */

// z dro

 Z_DRO_POS,                     /* 0x4d z dro location */
 Z_DRO_OFFSET,                  /* 0x4e z dro to zero */
 Z_DRO_COUNT_INCH,              /* 0x4f z dro scale */
 Z_DRO_INVERT,                  /* 0x50 z dro invert */
 Z_USE_DRO,                     /* 0x51 z use dro for position */

// x home parameters

 X_HOME_SPEED,                  /* 0x52 x final homing speed */
 X_HOME_DIST,                   /* 0x53 x max homing distance */
 X_HOME_BACKOFF_DIST,           /* 0x54 x home backoff dist */
 X_HOME_DIR,                    /* 0x55 x homing direction */

// x home test parameters

 X_HOME_LOC,                    /* 0x56 x home test location */
 X_HOME_START,                  /* 0x57 x start of home signal */
 X_HOME_END,                    /* 0x58 x end of home signal */
 X_HOME_OFFSET,                 /* 0x59 x home offset */
 X_DRO_POS,                     /* 0x5a x dro location */
 X_DRO_OFFSET,                  /* 0x5b x dro to zero */
 X_DRO_COUNT_INCH,              /* 0x5c x dro scale */
 X_DRO_FACTOR,                  /* 0x5d x dro counts inch factored */
 X_DRO_INVERT,                  /* 0x5e x dro invert */
 X_USE_DRO,                     /* 0x5f x use dro for position */
 X_DONE_DELAY,                  /* 0x60 x done to read dro delay */

// x home or probe status

 X_HOME_DONE,                   /* 0x61 x home done */
 X_HOME_STATUS,                 /* 0x62 x home status */

// Z home or probe status

 Z_HOME_DONE,                   /* 0x63 z home done */
 Z_HOME_STATUS,                 /* 0x64 z home status */

// probe configuration

 PROBE_SPEED,                   /* 0x65 probe speed */
 PROBE_DIST,                    /* 0x66 probe test distance */
 PROBE_INV,                     /* 0x67 invert polarity of probe */

// configuration

 STEPPER_DRIVE,                 /* 0x68 stepper driven spindle */
 MOTOR_TEST,                    /* 0x69 use stepper drive to test motor */
 SPINDLE_ENCODER,               /* 0x6a motor drive with spindle encoder */
 SPINDLE_SYNC_BOARD,            /* 0x6b spindle sync board */
 TURN_SYNC,                     /* 0x6c synchronization type for turning */
 THREAD_SYNC,                   /* 0x6d synchronization type for threading */
 CAP_TMR_ENABLE,                /* 0x6e enable capture timer */
 CFG_XILINX,                    /* 0x6f using xilinx */
 CFG_MPG,                       /* 0x70 manual pulse generator */
 CFG_DRO,                       /* 0x71 digital readout */
 CFG_LCD,                       /* 0x72 lcd display */
 CFG_FCY,                       /* 0x73 system clock speed */
 CFG_SWITCH,                    /* 0x74 spindle off on switch */
 CFG_VAR_SPEED,                 /* 0x75 spindle variable speed */

// setup

 SETUP_DONE,                    /* 0x76 setup done */

// encoder counts per revolution

 ENC_PER_REV,                   /* 0x77 spindle encoder counts per revolution */

// test encoder setup variables

 ENC_ENABLE,                    /* 0x78 encoder enable flag */
 ENC_PRE_SCALER,                /* 0x79 encoder prescaler */
 ENC_TIMER,                     /* 0x7a encoder timer counts */
 ENC_RUN_COUNT,                 /* 0x7b encoder run count */

// test encoder status variables

 ENC_RUN,                       /* 0x7c encoder running flag */
 ENC_COUNTER,                   /* 0x7d encoder count in rev */
 ENC_REV_COUNTER,               /* 0x7e encoder revolution counter */

// measured spindle speed

 RPM,                           /* 0x7f current rpm */

// xilinx frequency variables

 X_FREQUENCY,                   /* 0x80 xilinx clock frequency */
 FREQ_MULT,                     /* 0x81 frequency multiplier */

// xilinx configuration register

 X_CFG_REG,                     /* 0x82 xilinx configuration register */

// sync parameters

 L_SYNC_CYCLE,                  /* 0x83 sync cycle length */
 L_SYNC_OUTPUT,                 /* 0x84 sync outputs per cycle */
 L_SYNC_PRESCALER,              /* 0x85 sync prescaler */

// threading variables

 TH_Z_START,                    /* 0x86 threading z start */
 TH_X_START,                    /* 0x87 threading x start */
 TAN_THREAD_ANGLE,              /* 0x88 tangent of threading angle */
 X_FEED,                        /* 0x89 x feed */
 RUNOUT_DISTANCE,               /* 0x8a runout distance */
 RUNOUT_DEPTH,                  /* 0x8b runout depth */

// jog debug

 JOG_DEBUG,                     /* 0x8c jog interrupt debug */

// motor and speed control

 PWM_FREQ,                      /* 0x8d spindle speed pwm frequency */
 MIN_SPEED,                     /* 0x8e minimum speed for current range */
 MAX_SPEED,                     /* 0x8f maximum speed for current range */

// current operation

 CURRENT_OP,                    /* 0x90 current operation */
 MAX_PARM,                      /* 0x91 maximum parameter */
};
