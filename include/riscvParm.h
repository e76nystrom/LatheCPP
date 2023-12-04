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
 R_PWM_CTR,                     /* 0x06 pwm counter maxy */
 R_Z_STEPS_INCH,                /* 0x07 steps per inch */
 R_Z_SAVED_LOC,                 /* 0x08 saved for que op */
 R_Z_HOME_OFFSET,               /* 0x09 home offset */
 R_Z_LOC,                       /* 0x0a location */
 R_Z_DRO,                       /* 0x0b dro */
 R_Z_JOG_INC,                   /* 0x0c jog increment */
 R_Z_HOME_STATUS,               /* 0x0d home status */
 R_Z_HOME_FIND_FWD,             /* 0x0e max homing distance */
 R_Z_HOME_FIND_REV,             /* 0x0f max rev homing distance */
 R_Z_HOME_BACKOFF,              /* 0x10 home backoff dist */
 R_Z_HOME_SLOW,                 /* 0x11 home backoff dist */
 R_Z_TEST_LIM_MIN,              /* 0x12 test minimum limit */
 R_Z_TEST_LIM_MAX,              /* 0x13 test maximum limit */
 R_Z_TEST_HOME_MIN,             /* 0x14 test home minimum */
 R_Z_TEST_HOME_MAX,             /* 0x15 test home maximum */
 R_Z_TEST_PROBE,                /* 0x16 test probe position */
 R_X_STEPS_INCH,                /* 0x17 steps per inch */
 R_X_SAVED_LOC,                 /* 0x18 saved for que op */
 R_X_HOME_OFFSET,               /* 0x19 home offset */
 R_X_LOC,                       /* 0x1a location */
 R_X_DRO,                       /* 0x1b dro */
 R_X_JOG_INC,                   /* 0x1c jog increment */
 R_X_HOME_STATUS,               /* 0x1d home status */
 R_X_HOME_FIND_FWD,             /* 0x1e max homing distance */
 R_X_HOME_FIND_REV,             /* 0x1f max rev homing distance */
 R_X_HOME_BACKOFF,              /* 0x20 home backoff dist */
 R_X_HOME_SLOW,                 /* 0x21 home backoff dist */
 R_X_TEST_LIM_MIN,              /* 0x22 test minimum limit */
 R_X_TEST_LIM_MAX,              /* 0x23 test maximum limit */
 R_X_TEST_HOME_MIN,             /* 0x24 test home minimum */
 R_X_TEST_HOME_MAX,             /* 0x25 test home maximum */
 R_X_TEST_PROBE,                /* 0x26 test probe position */
};

#endif  /* RISCV_PARM_INC */
