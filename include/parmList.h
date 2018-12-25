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
 Z_DIR_FLAG,                    /* 0x18 z invert direction */
 Z_MPG_FLAG,                    /* 0x19 z invert mpg */

// x axis parameters

 X_PITCH,                       /* 0x1a x axis leadscrew pitch */
 X_RATIO,                       /* 0x1b x axis ratio */
 X_MICRO,                       /* 0x1c x axis micro steps */
 X_MOTOR,                       /* 0x1d x axis motor steps */
 X_ACCEL_TIME,                  /* 0x1e x axis acceleration */
 X_ACCEL,                       /* 0x1f z accel rpm/sec^2 */
 X_BACKLASH,                    /* 0x20 x axis backlash */
 X_DIR_FLAG,                    /* 0x21 x invert direction */
 X_MPG_FLAG,                    /* 0x22 x invert mpg */
 X_DIAMETER,                    /* 0x23 x diameter */

// z move parameters

 Z_MOVE_MIN,                    /* 0x24 z move min speed */
 Z_MOVE_MAX,                    /* 0x25 z move max speed */

// z jog parameters

 Z_JOG_MIN,                     /* 0x26 z jog min speed */
 Z_JOG_MAX,                     /* 0x27 z jog max speed */
 Z_JOG_SPEED,                   /* 0x28 z jog speed */

// x move parameters

 X_MOVE_MIN,                    /* 0x29 x move min speed */
 X_MOVE_MAX,                    /* 0x2a x move max speed */

// x jog parameters

 X_JOG_MIN,                     /* 0x2b x jog min speed */
 X_JOG_MAX,                     /* 0x2c x jog max speed */
 X_JOG_SPEED,                   /* 0x2d x jog speed */

// pass information

 TOTAL_PASSES,                  /* 0x2e total passes */
 CURRENT_PASS,                  /* 0x2f current passes */
 MV_STATUS,                     /* 0x30 movement status */

// z axis move values

 Z_MOVE_DIST,                   /* 0x31 z move distance */
 Z_MOVE_POS,                    /* 0x32 z move position */
 Z_JOG_DIR,                     /* 0x33 x jog direction */
 Z_SET_LOC,                     /* 0x34 z location to set */
 Z_LOC,                         /* 0x35 z dro location */
 Z_FLAG,                        /* 0x36 z move flag */
 Z_ABS_LOC,                     /* 0x37 z absolute location */
 Z_MPG_INC,                     /* 0x38 z man pulse gen incr */
 Z_MPG_MAX,                     /* 0x39 z man pulse max distance */

// x axis move values

 X_MOVE_DIST,                   /* 0x3a x move distance */
 X_MOVE_POS,                    /* 0x3b x move position */
 X_JOG_DIR,                     /* 0x3c x jog direction */
 X_SET_LOC,                     /* 0x3d x location to set */
 X_LOC,                         /* 0x3e x dro location */
 X_FLAG,                        /* 0x3f x move flag */
 X_ABS_LOC,                     /* 0x40 x absolute location */
 X_MPG_INC,                     /* 0x41 X man pulse gen incr */
 X_MPG_MAX,                     /* 0x42 x man pulse max distance */

// common jog parameters

 JOG_TIME_INITIAL,              /* 0x43 jog time initial */
 JOG_TIME_INC,                  /* 0x44 jog time increment */
 JOG_TIME_MAX,                  /* 0x45 jog time max */

// taper parameters

 TAPER_CYCLE_DIST,              /* 0x46 taperCycleDist */

// index pulse variables

 INDEX_PRE_SCALER,              /* 0x47 index pre scaler */
 LAST_INDEX_PERIOD,             /* 0x48 last index period */
 INDEX_PERIOD,                  /* 0x49 index period */
 REV_COUNTER,                   /* 0x4a revolution counter */

// z home offset

 Z_HOME_OFFSET,                 /* 0x4b z home offset */

// z dro

 Z_DRO_POS,                     /* 0x4c z dro location */
 Z_DRO_OFFSET,                  /* 0x4d z dro to zero */
 Z_DRO_INCH,                    /* 0x4e z dro scale */
 Z_DRO_INVERT,                  /* 0x4f z dro invert */

// x home parameters

 X_HOME_SPEED,                  /* 0x50 x final homing speed */
 X_HOME_DIST,                   /* 0x51 x max homing distance */
 X_HOME_BACKOFF_DIST,           /* 0x52 x home backoff dist */
 X_HOME_DIR,                    /* 0x53 x homing direction */

// x home test parameters

 X_HOME_LOC,                    /* 0x54 x home test location */
 X_HOME_START,                  /* 0x55 x start of home signal */
 X_HOME_END,                    /* 0x56 x end of home signal */
 X_HOME_OFFSET,                 /* 0x57 x home offset */
 X_DRO_POS,                     /* 0x58 x dro location */
 X_DRO_OFFSET,                  /* 0x59 x dro to zero */
 X_DRO_INCH,                    /* 0x5a x dro scale */
 X_DRO_INVERT,                  /* 0x5b x dro invert */

// x home or probe status

 X_HOME_DONE,                   /* 0x5c x home done */
 X_HOME_STATUS,                 /* 0x5d x home status */

// Z home or probe status

 Z_HOME_DONE,                   /* 0x5e z home done */
 Z_HOME_STATUS,                 /* 0x5f z home status */

// probe configuration

 PROBE_SPEED,                   /* 0x60 probe speed */
 PROBE_DIST,                    /* 0x61 probe test distance */
 PROBE_INV,                     /* 0x62 invert polarity of probe */

// configuration

 STEPPER_DRIVE,                 /* 0x63 stepper driven spindle */
 MOTOR_TEST,                    /* 0x64 use stepper drive to test motor */
 SPINDLE_ENCODER,               /* 0x65 motor drive with spindle encoder */
 SPINDLE_SYNC_BOARD,            /* 0x66 spindle sync board */
 SPINDLE_SYNC,                  /* 0x67 spindle sync direct */
 USE_ENCODER,                   /* 0x68 config for use encoder interrupt directly */
 ENCODER_DIRECT,                /* 0x69 use encoder interrupt directly */
 CAP_TMR_ENABLE,                /* 0x6a enable capture timer */
 CFG_XILINX,                    /* 0x6b using xilinx */
 CFG_MPG,                       /* 0x6c manual pulse generator */
 CFG_DRO,                       /* 0x6d digital readout */
 CFG_LCD,                       /* 0x6e lcd display */
 CFG_FCY,                       /* 0x6f system clock speed */

// setup

 SETUP_DONE,                    /* 0x70 setup done */

// encoder counts per revolution

 ENC_PER_REV,                   /* 0x71 spindle encoder counts per revolution */

// test encoder setup variables

 ENC_ENABLE,                    /* 0x72 encoder enable flag */
 ENC_PRE_SCALER,                /* 0x73 encoder prescaler */
 ENC_TIMER,                     /* 0x74 encoder timer counts */
 ENC_RUN_COUNT,                 /* 0x75 encoder run count */

// test encoder status variables

 ENC_RUN,                       /* 0x76 encoder running flag */
 ENC_COUNTER,                   /* 0x77 encoder count in rev */
 ENC_REV_COUNTER,               /* 0x78 encoder revolution counter */

// measured spindle speed

 RPM,                           /* 0x79 current rpm */

// xilinx frequency variables

 X_FREQUENCY,                   /* 0x7a xilinx clock frequency */
 FREQ_MULT,                     /* 0x7b frequency multiplier */

// xilinx configuration register

 X_CFG_REG,                     /* 0x7c xilinx configuration register */

// sync parameters

 L_SYNC_CYCLE,                  /* 0x7d sync cycle length */
 L_SYNC_OUTPUT,                 /* 0x7e sync outputs per cycle */
 L_SYNC_PRESCALER,              /* 0x7f sync prescaler */

// threading variables

 TH_Z_START,                    /* 0x80 threading z start */
 TH_X_START,                    /* 0x81 threading x start */
 TAN_THREAD_ANGLE,              /* 0x82 tangent of threading angle */
 X_FEED,                        /* 0x83 x feed */
 RUNOUT_DISTANCE,               /* 0x84 runout distance */
 RUNOUT_DEPTH,                  /* 0x85 runout depth */

// jog debug

 JOG_DEBUG,                     /* 0x86 jog interrupt debug */

// max parameter number

 MAX_PARM,                      /* 0x87 maximum parameter */
};
