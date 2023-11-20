#if !defined(RISCV_PARM)
#define RISCV_PARM
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
 R_P_X_LOC,                     /* 0x07  */
 R_P_Z_LOC,                     /* 0x08  */
 R_P_X_DRO,                     /* 0x09  */
 R_P_Z_DRO,                     /* 0x0a  */
 R_X_JOG_INC,                   /* 0x0b  */
 R_Z_JOG_INC,                   /* 0x0c  */
};

#endif  /* RISCV_PARM */
