#if !defined(CTL_BITS_INC)
#define CTL_BITS_INC

// common move command bits

#define CMD_MSK      (7 << 0)    /* 0x07 move mask */
#define SYN_START    (1 << 3)    /* 0x08 start on sync pulse */
#define SYN_LEFT     (1 << 4)    /* 0x10 start sync left */
#define SYN_TAPER    (1 << 5)    /* 0x20 taper on other axis */
#define DIST_MODE    (1 << 6)    /* 0x40 distance update mode */
#define FIND_HOME    (1 << 7)    /* 0x80 find home */
#define CLEAR_HOME   (1 << 8)    /* 0x100 move off of home */
#define FIND_PROBE   (1 << 9)    /* 0x200 find probe */
#define CLEAR_PROBE  (1 << 10)   /* 0x400 move off of probe */
#define DRO_POS      (1 << 11)   /* 0x800 use dro for moving */
#define DRO_UPD      (1 << 12)   /* 0x1000 update internal position from dro */
#define ENA_THREAD   (1 << 13)   /* 0x2000 runout enabled */
#define ENA_RUNOUT   (1 << 14)   /* 0x4000 runout enabled */
#define INTERNAL_OP  (1 << 15)   /* 0x8000 internal operation */

// common definitions

#define DIR_POS      1           /* 0x01 positive direction */
#define DIR_NEG      -1          /* 0x-1 negative direction */

// z direction

#define ZPOS         1           /* 0x01 z in positive direction */
#define ZNEG         -1          /* 0x-1 z in negative direction */

// x direction

#define XPOS         1           /* 0x01 x in positive direction */
#define XNEG         -1          /* 0x-1 x in negative direction */

// feed types

#define FEED_PITCH   0           /* 0x00 feed inch per rev */
#define FEED_TPI     1           /* 0x01 feed threads per inch */
#define FEED_METRIC  2           /* 0x02 feed mm per rev */

// home flag

#define HOME_SET     (1 << 0)    /* 0x01  */
#define HOME_CLR     (1 << 1)    /* 0x02  */
#define PROBE_SET    (1 << 2)    /* 0x04  */
#define PROBE_CLR    (1 << 3)    /* 0x08  */

// home direction

#define HOME_FWD     0           /* 0x00  */
#define HOME_REV     1           /* 0x01  */

// home status

#define HOME_ACTIVE  0           /* 0x00  */
#define HOME_SUCCESS 1           /* 0x01  */
#define HOME_FAIL    2           /* 0x02  */

// probe status

#define PROBE_SUCCESS 1          /* 0x01  */
#define PROBE_FAIL   2           /* 0x02  */

// movement status

#define MV_PAUSE     (1 << 0)    /* 0x01 movement paused */
#define MV_READ_X    (1 << 1)    /* 0x02 pause x may change */
#define MV_READ_Z    (1 << 2)    /* 0x04 pause z may change */
#define MV_ACTIVE    (1 << 3)    /* 0x08 movement active */
#define MV_DONE      (1 << 4)    /* 0x10 movement active */
#define MV_X_LIMIT   (1 << 5)    /* 0x20 at limit switch */
#define MV_Z_LIMIT   (1 << 6)    /* 0x40 at limit switch */
#define MV_X_HOME_ACTIVE (1 << 7) /* 0x80 x home active */
#define MV_X_HOME    (1 << 8)    /* 0x100 x home success */
#define MV_Z_HOME_ACTIVE (1 << 9) /* 0x200 z home active */
#define MV_Z_HOME    (1 << 10)   /* 0x400 z home success */
#define MV_MEASURE   (1 << 11)   /* 0x800 pause for measurement */
#define MV_ESTOP     (1 << 12)   /* 0x1000 estop */

// pause flags

#define DISABLE_JOG  (1 << 0)    /* 0x01 jogging disabled */
#define PAUSE_ENA_Z_JOG (1 << 1) /* 0x02 enable z job during pause */
#define PAUSE_ENA_X_JOG (1 << 2) /* 0x04 enable x jog during pause */
#define PAUSE_READ_Z (1 << 3)    /* 0x08 read z after pause */
#define PAUSE_READ_X (1 << 4)    /* 0x10 read x after pause */

// thread flags

#define TH_THREAD    (1 << 0)    /* 0x01 threading */
#define TH_INTERNAL  (1 << 1)    /* 0x02 internal threads */
#define TH_LEFT      (1 << 2)    /* 0x04 left hand thread */
#define TH_RUNOUT    (1 << 3)    /* 0x08 runout with thread */

// parameters for op_done

#define PARM_START   0           /* 0x00 start of operation */
#define PARM_DONE    1           /* 0x01 done operation */

// encoder direct flags

#define Z_ENCODER_DIRECT (1 << 0) /* 0x01 z sync directly from encoder */
#define X_ENCODER_DIRECT (1 << 1) /* 0x02 x sync directly from encoder */

// point by point movement commands

#define PCMD_INCX_HLDZ_S1 (0 << 0) /* 0x00 step x hold z then step 1 */
#define PCMD_INCX_HLDZ_SN (1 << 0) /* 0x01 step x hold z 1 then step z */
#define PCMD_HLDX_S1_INCZ (2 << 0) /* 0x02 step x hold z then step 1 */
#define PCMD_HLDX_SN_INCZ (3 << 0) /* 0x03 hold x 1 then step x increment z */
#define PCMD_EXTEND  (4 << 0)    /* 0x04 extend command */
#define PCMD_SPARE_0 (5 << 0)    /* 0x05 spare 0 */
#define PCMD_SPARE_1 (5 << 0)    /* 0x05 spare 1 */
#define PCMD_SET_DIR (7 << 0)    /* 0x07 set direction */
#define PCMD_X_NEG   (1 << 0)    /* 0x01 mov x negative */
#define PCMD_Z_NEG   (1 << 1)    /* 0x02 mov z negative */
#define PCMD_DIR_FLAG (1 << 2)   /* 0x04 direction flag */
#define PCMD_CMD_MASK (7 << 0)   /* 0x07 command mask */
#define PEXT_OFFSET  (8)         /* 0x08  */
#define PEXT_INCX    (0 << 0)    /* 0x00 step x */
#define PEXT_INCZ    (1 << 0)    /* 0x01 step z */
#define PEXT_INCX_INCZ (2 << 0)  /* 0x02 step x and z */
#define PEXT_INCX2_INCZ (3 << 0) /* 0x03 step x 2 step z */
#define PCMD_RPT_SHIFT (3)       /* 0x03 repeat mask */
#define PCMD_RPT_SHORT (32)      /* 0x20 repeat short */
#define PCMD_RPT_MASK (0x1f << PCMD_RPT_SHIFT) /* 0xf8 repeat shift */

// isr active flags

#define A_S          6           /* 0x06 shift for arc syn */
#define SYNC_ACTIVE_EXT (1 << 0) /* 0x01 sync board */
#define SYNC_ACTIVE_TMR (1 << 1) /* 0x02 internal timer */
#define SYNC_ACTIVE_ENC (1 << 2) /* 0x04 encoder */
#define SYNC_ACTIVE_STEP (1 << 3) /* 0x08 stepper */
#define SYNC_ACTIVE_TAPER (1 << 4) /* 0x10 taper */
#define SYNC_ACTIVE_THREAD (1 << 5) /* 0x20 threading */
#define ARC_ACTIVE_EXT (SYNC_ACTIVE_EXT << A_S) /* 0x40 arc sync board */
#define ARC_ACTIVE_TMR (SYNC_ACTIVE_TMR << A_S) /* 0x80 arc int tmr */
#define ARC_ACTIVE_ENC (SYNC_ACTIVE_ENC << A_S) /* 0x100 arc encoder */
#define ARC_ACTIVE_STEP (SYNC_ACTIVE_STEP << A_S) /* 0x200 arc stepper */

#endif  /* CTL_BITS_INC */
