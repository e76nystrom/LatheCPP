#if !defined(RISCV_PARM_INC)
#define RISCV_PARM_INC
// cFile

/* defines */

#define FLT (0x80)
#define SIZE_MASK (0x7)

enum RISCV_PARM_DEF
{
 R_MV_STATUS,                   /* 0x00 move status */
 R_JOG_PAUSE,                   /* 0x01 jog pause */
 R_CUR_PASS,                    /* 0x02 current pass */
 R_CFG_VAL,                     /* 0x03 fpga configuration value */
 R_P_RPM,                       /* 0x04 spindle rpm */
 R_PWM_DIV,                     /* 0x05 pwm divider */
 R_PWM_CTR,                     /* 0x06 pwm counter max */
 R_SYN_ENC_PRE_SCALER,          /* 0x07 encoder prescaler */
 R_SYN_ENC_CYCLE,               /* 0x08 encoder cycle len */
 R_SYN_OUT_CYCLE,               /* 0x09 output cycle len */
 R_TURN_SYNC,                   /* 0x0a turn sync */
 R_THREAD_SYNC,                 /* 0x0b thread sync */
 R_RUNOUT_SYNC,                 /* 0x0c runout sync */
 R_THREAD_FLAGS,                /* 0x0d threading flags */
 R_RUNOUT_DIST,                 /* 0x0e runout distance */
 R_RUNOUT_DEPTH,                /* 0x0f runout depth */
 R_Z_STEPS_INCH,                /* 0x10 steps per inch */
 R_Z_SAVED_LOC,                 /* 0x11 saved for que op */
 R_Z_HOME_OFFSET,               /* 0x12 home offset */
 R_Z_LOC,                       /* 0x13 location */
 R_Z_DRO,                       /* 0x14 dro */
 R_Z_JOG_INC,                   /* 0x15 jog increment */
 R_Z_HOME_STATUS,               /* 0x16 home status */
 R_Z_HOME_FIND_FWD,             /* 0x17 max homing distance */
 R_Z_HOME_FIND_REV,             /* 0x18 max rev homing distance */
 R_Z_HOME_BACKOFF,              /* 0x19 home backoff dist */
 R_Z_HOME_SLOW,                 /* 0x1a home backoff dist */
 R_Z_TEST_LIM_MIN,              /* 0x1b test minimum limit */
 R_Z_TEST_LIM_MAX,              /* 0x1c test maximum limit */
 R_Z_TEST_HOME_MIN,             /* 0x1d test home minimum */
 R_Z_TEST_HOME_MAX,             /* 0x1e test home maximum */
 R_Z_TEST_PROBE,                /* 0x1f test probe position */
 R_X_STEPS_INCH,                /* 0x20 steps per inch */
 R_X_SAVED_LOC,                 /* 0x21 saved for que op */
 R_X_HOME_OFFSET,               /* 0x22 home offset */
 R_X_LOC,                       /* 0x23 location */
 R_X_DRO,                       /* 0x24 dro */
 R_X_JOG_INC,                   /* 0x25 jog increment */
 R_X_HOME_STATUS,               /* 0x26 home status */
 R_X_HOME_FIND_FWD,             /* 0x27 max homing distance */
 R_X_HOME_FIND_REV,             /* 0x28 max rev homing distance */
 R_X_HOME_BACKOFF,              /* 0x29 home backoff dist */
 R_X_HOME_SLOW,                 /* 0x2a home backoff dist */
 R_X_TEST_LIM_MIN,              /* 0x2b test minimum limit */
 R_X_TEST_LIM_MAX,              /* 0x2c test maximum limit */
 R_X_TEST_HOME_MIN,             /* 0x2d test home minimum */
 R_X_TEST_HOME_MAX,             /* 0x2e test home maximum */
 R_X_TEST_PROBE,                /* 0x2f test probe position */
};

#endif  /* RISCV_PARM_INC */
