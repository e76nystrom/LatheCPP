#if !defined(RISCV_PARM)
#define RISCV_PARM
/* defines */

#define FLT (0x80)
#define SIZE_MASK (0x7)

enum RISCV_PARM_DEF
{
 R_MV_STATUS,                   /* 0x00  */
 R_JOG_PAUSE,                   /* 0x01  */
 R_CUR_PASS,                    /* 0x02  */
 R_P_RPM,                       /* 0x03  */
 R_P_X_LOC,                     /* 0x04  */
 R_P_Z_LOC,                     /* 0x05  */
 R_P_X_DRO,                     /* 0x06  */
 R_P_Z_DRO,                     /* 0x07  */
 R_X_JOG_INC,                   /* 0x08  */
 R_Z_JOG_INC,                   /* 0x09  */
};

#endif  /* RISCV_PARM */
