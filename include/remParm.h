#if !defined(REM_PARM_INC)
#define REM_PARM_INC
// cFile

/* defines */

#define FLT (0x80)
#define SIZE_MASK (0x7)

enum REM_PARM_DEF
{

// spindle parameters

 SP_STEPS,                      /* 0x00 spindle motor steps */
 SP_MICRO,                      /* 0x01 spindle micro steps */
 SP_MIN_RPM,                    /* 0x02 spindle minimum rpm */
 SP_MAX_RPM,                    /* 0x03 spindle maximum rpm */
 SP_RPM,                        /* 0x04 spindle rpm */
 SP_ACCEL_TIME,                 /* 0x05 spindle accel time */
 SP_ACCEL,                      /* 0x06 spindle accel rpm/sec^2 */
 SP_JOG_MIN_RPM,                /* 0x07 spindle jog minimum rpm */
 SP_JOG_MAX_RPM,                /* 0x08 spindle jog maximum rpm */
 SP_JOG_RPM,                    /* 0x09 spindle jog rpm */
 SP_JOG_ACCEL_TIME,             /* 0x0a spindle jog accel time */
 SP_JOG_TIME_INITIAL,           /* 0x0b spindle jog time initial */
 SP_JOG_TIME_INC,               /* 0x0c spindle jog time increment */
 SP_JOG_TIME_MAX,               /* 0x0d spindle jog time max */
 SP_JOG_DIR,                    /* 0x0e spindle direction */
 SP_DIR_INV,                    /* 0x0f spindle invert direction */
 SP_TEST_INDEX,                 /* 0x10 generate test index pulse */
 SP_TEST_ENCODER,               /* 0x11 generate enc test pulse */

// z axis parameters

 Z_PITCH,                       /* 0x12 z axis leadscrew pitch */
 Z_RATIO,                       /* 0x13 z axis ratio */
 Z_MICRO,                       /* 0x14 z axis micro steps */
 Z_MOTOR,                       /* 0x15 z axis motor steps */
 Z_ACCEL_TIME,                  /* 0x16 z axis acceleration */
 Z_ACCEL,                       /* 0x17 z accel rpm/sec^2 */
 Z_BACKLASH,                    /* 0x18 z axis backlash */
 Z_STEP_FACTOR,                 /* 0x19 z steps inch factored */
 Z_DIR_INV,                     /* 0x1a z invert direction */
 Z_MPG_INV,                     /* 0x1b z invert mpg */

// x axis parameters

 X_PITCH,                       /* 0x1c x axis leadscrew pitch */
 X_RATIO,                       /* 0x1d x axis ratio */
 X_MICRO,                       /* 0x1e x axis micro steps */
 X_MOTOR,                       /* 0x1f x axis motor steps */
 X_ACCEL_TIME,                  /* 0x20 x axis acceleration */
 X_ACCEL,                       /* 0x21 x accel rpm/sec^2 */
 X_BACKLASH,                    /* 0x22 x axis backlash */
 X_STEP_FACTOR,                 /* 0x23 x steps inch factored */
 X_DIR_INV,                     /* 0x24 x invert direction */
 X_MPG_INV,                     /* 0x25 x invert mpg */
 X_DIAMETER,                    /* 0x26 x diameter */

// z move parameters

 Z_MOVE_MIN,                    /* 0x27 z move min speed */
 Z_MOVE_MAX,                    /* 0x28 z move max speed */

// z jog parameters

 Z_JOG_MIN,                     /* 0x29 z jog min speed */
 Z_JOG_MAX,                     /* 0x2a z jog max speed */
 Z_JOG_SPEED,                   /* 0x2b z jog speed */

// x move parameters

 X_MOVE_MIN,                    /* 0x2c x move min speed */
 X_MOVE_MAX,                    /* 0x2d x move max speed */

// x jog parameters

 X_JOG_MIN,                     /* 0x2e x jog min speed */
 X_JOG_MAX,                     /* 0x2f x jog max speed */
 X_JOG_SPEED,                   /* 0x30 x jog speed */

// pass information

 TOTAL_PASSES,                  /* 0x31 total passes */
 CURRENT_PASS,                  /* 0x32 current passes */
 MV_STATUS,                     /* 0x33 movement status */

// z axis move values

 Z_MOVE_DIST,                   /* 0x34 z move distance */
 Z_MOVE_POS,                    /* 0x35 z move position */
 Z_JOG_DIR,                     /* 0x36 x jog direction */
 Z_SET_LOC,                     /* 0x37 z location to set */
 Z_LOC,                         /* 0x38 z dro location */
 Z_FLAG,                        /* 0x39 z move flag */
 Z_ABS_LOC,                     /* 0x3a z absolute location */
 Z_MPG_INC,                     /* 0x3b z man pulse gen incr */
 Z_MPG_MAX,                     /* 0x3c z man pulse max distance */

// x axis move values

 X_MOVE_DIST,                   /* 0x3d x move distance */
 X_MOVE_POS,                    /* 0x3e x move position */
 X_JOG_DIR,                     /* 0x3f x jog direction */
 X_SET_LOC,                     /* 0x40 x location to set */
 X_LOC,                         /* 0x41 x dro location */
 X_FLAG,                        /* 0x42 x move flag */
 X_ABS_LOC,                     /* 0x43 x absolute location */
 X_MPG_INC,                     /* 0x44 X man pulse gen incr */
 X_MPG_MAX,                     /* 0x45 x man pulse max distance */

// common jog parameters

 JOG_TIME_INITIAL,              /* 0x46 jog time initial */
 JOG_TIME_INC,                  /* 0x47 jog time increment */
 JOG_TIME_MAX,                  /* 0x48 jog time max */

// taper parameters

 TAPER_CYCLE_DIST,              /* 0x49 taperCycleDist */

// index pulse variables

 INDEX_PRE_SCALER,              /* 0x4a index pre scaler */
 LAST_INDEX_PERIOD,             /* 0x4b last index period */
 INDEX_PERIOD,                  /* 0x4c index period */
 REV_COUNTER,                   /* 0x4d revolution counter */

// z home offset

 Z_HOME_OFFSET,                 /* 0x4e z home offset */

// x home offset

 X_HOME_OFFSET,                 /* 0x4f x home offset */

// z home parameters

 Z_HOME_SPEED,                  /* 0x50 z final homing speed */
 Z_HOME_DIST,                   /* 0x51 z max homing distance */
 Z_HOME_DIST_REV,               /* 0x52 z max rev homing distance */
 Z_HOME_DIST_BACKOFF,           /* 0x53 z home backoff dist */
 Z_HOME_DIR,                    /* 0x54 z homing direction */

// z limit test parameters

 Z_TEST_LIMIT_MIN,              /* 0x55 z test limit minimum */
 Z_TEST_LIMIT_MAX,              /* 0x56 z test limit maximum */
 Z_TEST_HOME_MIN,               /* 0x57 z test home minimum */
 Z_TEST_HOME_MAX,               /* 0x58 z test home maximum */
 Z_TEST_PROBE,                  /* 0x59 z test probe */

// x home parameters

 X_HOME_SPEED,                  /* 0x5a x final homing speed */
 X_HOME_DIST,                   /* 0x5b x max homing distance */
 X_HOME_DIST_REV,               /* 0x5c x max rev homing distance */
 X_HOME_DIST_BACKOFF,           /* 0x5d x home backoff dist */
 X_HOME_DIR,                    /* 0x5e x homing direction */

// x home test parameters

 X_HOME_LOC,                    /* 0x5f x home test location */
 X_HOME_START,                  /* 0x60 x start of home signal */
 X_HOME_END,                    /* 0x61 x end of home signal */

// x limit test parameters

 X_TEST_LIMIT_MIN,              /* 0x62 x test limit minimum */
 X_TEST_LIMIT_MAX,              /* 0x63 x test limit maximum */
 X_TEST_HOME_MIN,               /* 0x64 x test home minimum */
 X_TEST_HOME_MAX,               /* 0x65 x test home maximum */
 X_TEST_PROBE,                  /* 0x66 x test probe */

// z dro

 Z_DRO_LOC,                     /* 0x67 z dro location */
 Z_DRO_OFFSET,                  /* 0x68 z dro to zero */
 Z_DRO_COUNT_INCH,              /* 0x69 z dro scale */
 Z_DRO_FACTOR,                  /* 0x6a x dro counts inch factored */
 Z_DRO_INVERT,                  /* 0x6b z dro invert */
 Z_USE_DRO,                     /* 0x6c z use dro for position */
 Z_DONE_DELAY,                  /* 0x6d z done to read dro delay */
 Z_DRO_FINAL_DIST,              /* 0x6e z final approach distance */

// x dro

 X_DRO_LOC,                     /* 0x6f x dro location */
 X_DRO_OFFSET,                  /* 0x70 x dro to zero */
 X_DRO_COUNT_INCH,              /* 0x71 x dro scale */
 X_DRO_FACTOR,                  /* 0x72 x dro counts inch factored */
 X_DRO_INVERT,                  /* 0x73 x dro invert */
 X_USE_DRO,                     /* 0x74 x use dro for position */
 X_DONE_DELAY,                  /* 0x75 x done to read dro delay */
 X_DRO_FINAL_DIST,              /* 0x76 x final approach distance */

// x home or probe status

 X_HOME_STATUS,                 /* 0x77 x home status */

// Z home or probe status

 Z_HOME_STATUS,                 /* 0x78 z home status */

// probe configuration

 PROBE_SPEED,                   /* 0x79 probe speed */
 PROBE_DIST,                    /* 0x7a probe test distance */
 PROBE_INV,                     /* 0x7b invert polarity of probe */

// configuration

 STEPPER_DRIVE,                 /* 0x7c stepper driven spindle */
 MOTOR_TEST,                    /* 0x7d use stepper to test motor */
 SPINDLE_ENCODER,               /* 0x7e motor with spindle enc */
 SPINDLE_SYNC_BOARD,            /* 0x7f spindle sync board */
 SPINDLE_INTERNAL_SYNC,         /* 0x80 spindle internal sync */
 TURN_SYNC,                     /* 0x81 sync type for turning */
 THREAD_SYNC,                   /* 0x82 sync type for threading */
 RUNOUT_SYNC,                   /* 0x83 sync type for runout */
 CAP_TMR_ENABLE,                /* 0x84 enable capture timer */
 CFG_FPGA,                      /* 0x85 using fpga */
 CFG_MEGA,                      /* 0x86 control link to mega */
 CFG_MPG,                       /* 0x87 manual pulse generator */
 CFG_DRO,                       /* 0x88 digital readout */
 CFG_LCD,                       /* 0x89 lcd display */
 CFG_FCY,                       /* 0x8a system clock speed */
 CFG_SWITCH,                    /* 0x8b spindle off on switch */
 CFG_VAR_SPEED,                 /* 0x8c spindle variable speed */

// setup

 SETUP_DONE,                    /* 0x8d setup done */

// encoder counts per revolution

 ENC_PER_REV,                   /* 0x8e spindle enc counts per rev */

// test encoder setup variables

 ENC_ENABLE,                    /* 0x8f encoder enable flag */
 ENC_PRE_SCALER,                /* 0x90 encoder prescaler */
 ENC_TIMER,                     /* 0x91 encoder timer counts */
 ENC_RUN_COUNT,                 /* 0x92 encoder run count */

// test encoder status variables

 ENC_RUN,                       /* 0x93 encoder running flag */
 ENC_COUNTER,                   /* 0x94 encoder count in rev */
 ENC_REV_COUNTER,               /* 0x95 encoder revolution counter */

// measured spindle speed

 RPM,                           /* 0x96 current measured rpm */

// fpga frequency variables

 FPGA_FREQUENCY,                /* 0x97 fpga clock frequency */
 FREQ_MULT,                     /* 0x98 frequency multiplier */

// xilinx configuration register

 X_CFG_REG,                     /* 0x99 xilinx cfg register */

// z sync parameters

 L_SYNC_CYCLE,                  /* 0x9a sync cycle length */
 L_SYNC_OUTPUT,                 /* 0x9b sync outputs per cycle */
 L_SYNC_IN_PRE_SCALER,          /* 0x9c input sync prescaler */
 L_SYNC_OUT_PRE_SCALER,         /* 0x9d output sync prescaler */

// x sync parameters

 L_X_SYNC_CYCLE,                /* 0x9e sync cycle length */
 L_X_SYNC_OUTPUT,               /* 0x9f sync outputs per cycle */
 L_X_SYNC_IN_PRE_SCALER,        /* 0xa0 input sync prescaler */
 L_X_SYNC_OUT_PRE_SCALER,       /* 0xa1 output sync prescaler */

// threading variables

 TH_Z_START,                    /* 0xa2 threading z start */
 TH_X_START,                    /* 0xa3 threading x start */
 TAN_THREAD_ANGLE,              /* 0xa4 tan of threading angle */
 X_FEED,                        /* 0xa5 x feed */
 RUNOUT_DIST,                   /* 0xa6 runout distance */
 RUNOUT_DEPTH,                  /* 0xa7 runout depth */

// jog debug

 JOG_DEBUG,                     /* 0xa8 jog interrupt debug */

// motor and speed control

 PWM_FREQ,                      /* 0xa9 spindle speed pwm frequency */
 MIN_SPEED,                     /* 0xaa min speed for current range */
 MAX_SPEED,                     /* 0xab max speed for current range */

// current operation

 CURRENT_OP,                    /* 0xac current operation */

// global limits and home

 LIMIT_OVERRIDE,                /* 0xad override limit switches */
 COMMON_LIMITS,                 /* 0xae all limit switches one pin */
 LIMITS_ENABLED,                /* 0xaf limits enabled */
 COMMON_HOME,                   /* 0xb0 all home switches one pin */

// z limits and home

 Z_LIM_ENA,                     /* 0xb1 z limit enable */
 Z_LIM_NEG_INV,                 /* 0xb2 z negative limit invert */
 Z_LIM_POS_INV,                 /* 0xb3 z Positive limit Invert */
 Z_HOME_ENA,                    /* 0xb4 z home enable */
 Z_HOME_INV,                    /* 0xb5 z home invert */

// x limits and home

 X_LIM_ENA,                     /* 0xb6 x limit enable */
 X_LIM_NEG_INV,                 /* 0xb7 x negative limit invert */
 X_LIM_POS_INV,                 /* 0xb8 x Positive limit Invert */
 X_HOME_ENA,                    /* 0xb9 x home enable */
 X_HOME_INV,                    /* 0xba x home invert */

// e stop

 E_STOP_ENA,                    /* 0xbb enable estop */
 E_STOP_INV,                    /* 0xbc invert estop signal */

// command pause

 CMD_PAUSED,                    /* 0xbd move commands paused */

// arc parameters

 ARC_RADIUS,                    /* 0xbe arc radius */
 ARC_X_CENTER,                  /* 0xbf arc x center */
 ARC_Z_CENTER,                  /* 0xc0 arc z center */
 ARC_X_START,                   /* 0xc1 arc x start */
 ARC_Z_START,                   /* 0xc2 arc z start */
 ARC_X_END,                     /* 0xc3 arc x center */
 ARC_Z_END,                     /* 0xc4 arc z center */
 MEGA_VFD,                      /* 0xc5 mega vfd speed mode */
 MEGA_SIM,                      /* 0xc6 mega encoder lines */
 USB_ENA,                       /* 0xc7 enable usb */
 DRO_STEP,                      /* 0xc8 step pulse drives dro */
 MAX_PARM,                      /* 0xc9 maximum parameter */
};

#endif  /* REM_PARM_INC */
