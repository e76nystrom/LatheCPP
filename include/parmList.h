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
 Z_STEP_FACTOR,                 /* 0x18 z steps inch factored */
 Z_DIR_FLAG,                    /* 0x19 z invert direction */
 Z_MPG_FLAG,                    /* 0x1a z invert mpg */

// x axis parameters

 X_PITCH,                       /* 0x1b x axis leadscrew pitch */
 X_RATIO,                       /* 0x1c x axis ratio */
 X_MICRO,                       /* 0x1d x axis micro steps */
 X_MOTOR,                       /* 0x1e x axis motor steps */
 X_ACCEL_TIME,                  /* 0x1f x axis acceleration */
 X_ACCEL,                       /* 0x20 x accel rpm/sec^2 */
 X_BACKLASH,                    /* 0x21 x axis backlash */
 X_STEP_FACTOR,                 /* 0x22 x steps inch factored */
 X_DIR_FLAG,                    /* 0x23 x invert direction */
 X_MPG_FLAG,                    /* 0x24 x invert mpg */
 X_DIAMETER,                    /* 0x25 x diameter */

// z move parameters

 Z_MOVE_MIN,                    /* 0x26 z move min speed */
 Z_MOVE_MAX,                    /* 0x27 z move max speed */

// z jog parameters

 Z_JOG_MIN,                     /* 0x28 z jog min speed */
 Z_JOG_MAX,                     /* 0x29 z jog max speed */
 Z_JOG_SPEED,                   /* 0x2a z jog speed */

// x move parameters

 X_MOVE_MIN,                    /* 0x2b x move min speed */
 X_MOVE_MAX,                    /* 0x2c x move max speed */

// x jog parameters

 X_JOG_MIN,                     /* 0x2d x jog min speed */
 X_JOG_MAX,                     /* 0x2e x jog max speed */
 X_JOG_SPEED,                   /* 0x2f x jog speed */

// pass information

 TOTAL_PASSES,                  /* 0x30 total passes */
 CURRENT_PASS,                  /* 0x31 current passes */
 MV_STATUS,                     /* 0x32 movement status */

// z axis move values

 Z_MOVE_DIST,                   /* 0x33 z move distance */
 Z_MOVE_POS,                    /* 0x34 z move position */
 Z_JOG_DIR,                     /* 0x35 x jog direction */
 Z_SET_LOC,                     /* 0x36 z location to set */
 Z_LOC,                         /* 0x37 z dro location */
 Z_FLAG,                        /* 0x38 z move flag */
 Z_ABS_LOC,                     /* 0x39 z absolute location */
 Z_MPG_INC,                     /* 0x3a z man pulse gen incr */
 Z_MPG_MAX,                     /* 0x3b z man pulse max distance */

// x axis move values

 X_MOVE_DIST,                   /* 0x3c x move distance */
 X_MOVE_POS,                    /* 0x3d x move position */
 X_JOG_DIR,                     /* 0x3e x jog direction */
 X_SET_LOC,                     /* 0x3f x location to set */
 X_LOC,                         /* 0x40 x dro location */
 X_FLAG,                        /* 0x41 x move flag */
 X_ABS_LOC,                     /* 0x42 x absolute location */
 X_MPG_INC,                     /* 0x43 X man pulse gen incr */
 X_MPG_MAX,                     /* 0x44 x man pulse max distance */

// common jog parameters

 JOG_TIME_INITIAL,              /* 0x45 jog time initial */
 JOG_TIME_INC,                  /* 0x46 jog time increment */
 JOG_TIME_MAX,                  /* 0x47 jog time max */

// taper parameters

 TAPER_CYCLE_DIST,              /* 0x48 taperCycleDist */

// index pulse variables

 INDEX_PRE_SCALER,              /* 0x49 index pre scaler */
 LAST_INDEX_PERIOD,             /* 0x4a last index period */
 INDEX_PERIOD,                  /* 0x4b index period */
 REV_COUNTER,                   /* 0x4c revolution counter */

// z home offset

 Z_HOME_OFFSET,                 /* 0x4d z home offset */

// x home offset

 X_HOME_OFFSET,                 /* 0x4e x home offset */

// z home parameters

 Z_HOME_SPEED,                  /* 0x4f z final homing speed */
 Z_HOME_DIST,                   /* 0x50 z max homing distance */
 Z_HOME_BACKOFF_DIST,           /* 0x51 z home backoff dist */
 Z_HOME_DIR,                    /* 0x52 z homing direction */

// x home parameters

 X_HOME_SPEED,                  /* 0x53 x final homing speed */
 X_HOME_DIST,                   /* 0x54 x max homing distance */
 X_HOME_BACKOFF_DIST,           /* 0x55 x home backoff dist */
 X_HOME_DIR,                    /* 0x56 x homing direction */

// x home test parameters

 X_HOME_LOC,                    /* 0x57 x home test location */
 X_HOME_START,                  /* 0x58 x start of home signal */
 X_HOME_END,                    /* 0x59 x end of home signal */

// z dro

 Z_DRO_LOC,                     /* 0x5a z dro location */
 Z_DRO_OFFSET,                  /* 0x5b z dro to zero */
 Z_DRO_COUNT_INCH,              /* 0x5c z dro scale */
 Z_DRO_FACTOR,                  /* 0x5d x dro counts inch factored */
 Z_DRO_INVERT,                  /* 0x5e z dro invert */
 Z_USE_DRO,                     /* 0x5f z use dro for position */
 Z_DONE_DELAY,                  /* 0x60 z done to read dro delay */
 Z_DRO_FINAL_DIST,              /* 0x61 z final approach distance */

// x dro

 X_DRO_LOC,                     /* 0x62 x dro location */
 X_DRO_OFFSET,                  /* 0x63 x dro to zero */
 X_DRO_COUNT_INCH,              /* 0x64 x dro scale */
 X_DRO_FACTOR,                  /* 0x65 x dro counts inch factored */
 X_DRO_INVERT,                  /* 0x66 x dro invert */
 X_USE_DRO,                     /* 0x67 x use dro for position */
 X_DONE_DELAY,                  /* 0x68 x done to read dro delay */
 X_DRO_FINAL_DIST,              /* 0x69 x final approach distance */

// x home or probe status

 X_HOME_DONE,                   /* 0x6a x home done */
 X_HOME_STATUS,                 /* 0x6b x home status */

// Z home or probe status

 Z_HOME_DONE,                   /* 0x6c z home done */
 Z_HOME_STATUS,                 /* 0x6d z home status */

// probe configuration

 PROBE_SPEED,                   /* 0x6e probe speed */
 PROBE_DIST,                    /* 0x6f probe test distance */
 PROBE_INV,                     /* 0x70 invert polarity of probe */

// configuration

 STEPPER_DRIVE,                 /* 0x71 stepper driven spindle */
 MOTOR_TEST,                    /* 0x72 use stepper drive to test motor */
 SPINDLE_ENCODER,               /* 0x73 motor drive with spindle encoder */
 SPINDLE_SYNC_BOARD,            /* 0x74 spindle sync board */
 TURN_SYNC,                     /* 0x75 synchronization type for turning */
 THREAD_SYNC,                   /* 0x76 synchronization type for threading */
 CAP_TMR_ENABLE,                /* 0x77 enable capture timer */
 CFG_FPGA,                      /* 0x78 using fpga */
 CFG_MPG,                       /* 0x79 manual pulse generator */
 CFG_DRO,                       /* 0x7a digital readout */
 CFG_LCD,                       /* 0x7b lcd display */
 CFG_FCY,                       /* 0x7c system clock speed */
 CFG_SWITCH,                    /* 0x7d spindle off on switch */
 CFG_VAR_SPEED,                 /* 0x7e spindle variable speed */

// setup

 SETUP_DONE,                    /* 0x7f setup done */

// encoder counts per revolution

 ENC_PER_REV,                   /* 0x80 spindle encoder counts per revolution */

// test encoder setup variables

 ENC_ENABLE,                    /* 0x81 encoder enable flag */
 ENC_PRE_SCALER,                /* 0x82 encoder prescaler */
 ENC_TIMER,                     /* 0x83 encoder timer counts */
 ENC_RUN_COUNT,                 /* 0x84 encoder run count */

// test encoder status variables

 ENC_RUN,                       /* 0x85 encoder running flag */
 ENC_COUNTER,                   /* 0x86 encoder count in rev */
 ENC_REV_COUNTER,               /* 0x87 encoder revolution counter */

// measured spindle speed

 RPM,                           /* 0x88 current rpm */

// fpga frequency variables

 FPGA_FREQUENCY,                /* 0x89 fpga clock frequency */
 FREQ_MULT,                     /* 0x8a frequency multiplier */

// xilinx configuration register

 X_CFG_REG,                     /* 0x8b xilinx configuration register */

// sync parameters

 L_SYNC_CYCLE,                  /* 0x8c sync cycle length */
 L_SYNC_OUTPUT,                 /* 0x8d sync outputs per cycle */
 L_SYNC_PRESCALER,              /* 0x8e sync prescaler */

// threading variables

 TH_Z_START,                    /* 0x8f threading z start */
 TH_X_START,                    /* 0x90 threading x start */
 TAN_THREAD_ANGLE,              /* 0x91 tangent of threading angle */
 X_FEED,                        /* 0x92 x feed */
 RUNOUT_DISTANCE,               /* 0x93 runout distance */
 RUNOUT_DEPTH,                  /* 0x94 runout depth */

// jog debug

 JOG_DEBUG,                     /* 0x95 jog interrupt debug */

// motor and speed control

 PWM_FREQ,                      /* 0x96 spindle speed pwm frequency */
 MIN_SPEED,                     /* 0x97 minimum speed for current range */
 MAX_SPEED,                     /* 0x98 maximum speed for current range */

// current operation

 CURRENT_OP,                    /* 0x99 current operation */

// global limits and home

 LIMIT_OVERRIDE,                /* 0x9a override limit switches */
 COMMON_LIMITS,                 /* 0x9b all limit switches on one pin */
 LIMITS_ENABLED,                /* 0x9c limits enabled */
 COMMON_HOME,                   /* 0x9d all home switches on one pin */

// z limits and home

 Z_LIM_ENA,                     /* 0x9e z limit enable */
 Z_LIM_NEG_INV,                 /* 0x9f z negative limit invert */
 Z_LIM_POS_INV,                 /* 0xa0 z Positive limit Invert */
 Z_HOME_ENA,                    /* 0xa1 z home enable */
 Z_HOME_INV,                    /* 0xa2 z home invert */

// x limits and home

 X_LIM_ENA,                     /* 0xa3 x limit enable */
 X_LIM_NEG_INV,                 /* 0xa4 x negative limit invert */
 X_LIM_POS_INV,                 /* 0xa5 x Positive limit Invert */
 X_HOME_ENA,                    /* 0xa6 x home enable */
 X_HOME_INV,                    /* 0xa7 x home invert */

// e stop

 E_STOP_ENA,                    /* 0xa8 enable estop */
 E_STOP_INV,                    /* 0xa9 invert estop siganl */
 MAX_PARM,                      /* 0xaa maximum parameter */
};
