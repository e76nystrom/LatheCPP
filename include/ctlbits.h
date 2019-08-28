
// common move command bits

#define CMD_MSK      (7 << 0)    /* 0x07 move mask */
#define CMD_MOV      (1 << 0)    /* 0x01 move a set distance */
#define CMD_JOG      (2 << 0)    /* 0x02 move while cmd are present */
#define CMD_SYN      (3 << 0)    /* 0x03 move dist synchronized to rotation */
#define CMD_MAX      (4 << 0)    /* 0x04 rapid move */
#define CMD_SPEED    (5 << 0)    /* 0x05 jog at speed */
#define JOGSLOW      (6 << 0)    /* 0x06 slow jog for home or probe */

// common definitions

#define DIR_POS      1           /* 0x01 positive direction */
#define DIR_NEG      -1          /* 0x-1 negative direction */

// z move command bits

#define Z_SYN_START  (1 << 4)    /* 0x10 start on sync pulse */
#define Z_SYN_LEFT   (1 << 5)    /* 0x20 start sync left */
#define X_SYN_TAPER  (1 << 6)    /* 0x40 taper on x */

// z direction

#define ZPOS         1           /* 0x01 z in positive direction */
#define ZNEG         -1          /* 0x-1 z in negative direction */

// x move command bits

#define X_SYN_START  (1 << 4)    /* 0x10 start on sync pulse */
#define Z_SYN_TAPER  (1 << 5)    /* 0x20 taper on z */
#define XFIND_HOME   (1 << 6)    /* 0x40 find home */
#define XCLEAR_HOME  (1 << 7)    /* 0x80 move off of home */
#define FIND_PROBE   (1 << 8)    /* 0x100 find home */
#define CLEAR_PROBE  (1 << 9)    /* 0x200 move off of home */
#define DRO_POS      (1 << 10)   /* 0x400 use dro for moving */

// x direction

#define XPOS         1           /* 0x01 x in positive direction */
#define XNEG         -1          /* 0x-1 x in negative direction */

// feed types

#define FEED_PITCH   0           /* 0x00 feed inch per rev */
#define FEED_TPI     1           /* 0x01 feed threads per inch */
#define FEED_METRIC  2           /* 0x02 feed mm per rev */

// home flag

#define FIND_HOME    (1 << 0)    /* 0x01  */
#define CLEAR_HOME   (1 << 1)    /* 0x02  */
#define PROBE_SET    (1 << 2)    /* 0x04  */
#define PROBE_CLR    (1 << 3)    /* 0x08  */

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
#define MV_HOME_ACTIVE (1 << 4)  /* 0x10 home active */
#define MV_XHOME     (1 << 5)    /* 0x20 X home success */
#define MV_MEASURE   (1 << 6)    /* 0x40 pause for measurement */

// pause flags

#define PAUSE_ENA_Z_JOG (1 << 0) /* 0x01 enable z job during pause */
#define PAUSE_ENA_X_JOG (1 << 1) /* 0x02 enable x jog during pause */
#define DISABLE_JOG  (1 << 2)    /* 0x04 jogging disabled */
#define PAUSE_READ_X (1 << 3)    /* 0x08 read x after pause */
#define PAUSE_READ_Z (1 << 4)    /* 0x10 read z after pause */

// thread flags

#define TH_THREAD    (1 << 0)    /* 0x01 threading */
#define TH_INTERNAL  (1 << 1)    /* 0x02 internal threads */
#define TH_LEFT      (1 << 2)    /* 0x04 left hand thread */
#define TH_RUNOUT    (1 << 3)    /* 0x08 runout with thread */

// parameters for op_done

#define PARM_START   0           /* 0x00 start of operation */
#define PARM_DONE    1           /* 0x01 done operation */

// isr active flags

#define SYNC_ACTIVE_EXT (1 << 0) /* 0x01 active for sync board */
#define SYNC_ACTIVE_TMR (1 << 1) /* 0x02 active for internal timer */
#define SYNC_ACTIVE_ENC (1 << 2) /* 0x04 active for encoder */
#define SYNC_ACTIVE_STEP (1 << 3) /* 0x08 active for stepper */

// encoder direct flags

#define Z_ENCODER_DIRECT (1 << 0) /* 0x01 z sync directly from encoder */
#define X_ENCODER_DIRECT (1 << 1) /* 0x02 x sync directly from encoder */
