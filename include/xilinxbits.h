
// z control register

#define ZRESET        (1 << 0)  /* 0x001 reset flag */
#define ZSTART        (1 << 1)  /* 0x002 start z */
#define ZSRC_SYN      (1 << 2)  /* 0x004 run z synchronized */
#define ZSRC_FRQ      (0 << 2)  /* 0x000 run z from clock source */
#define ZDIR_IN       (1 << 3)  /* 0x008 move z in positive dir */
#define ZDIR_POS      (1 << 3)  /* 0x008 move z in positive dir */
#define ZDIR_NEG      (0 << 3)  /* 0x000 move z in negative dir */
#define ZSET_LOC      (1 << 4)  /* 0x010 set z location */
#define ZBACKLASH     (1 << 5)  /* 0x020 backlash move no pos upd */
#define ZWAIT_SYNC    (1 << 6)  /* 0x040 wait for sync to start */
#define zCtlSize     7

// x control register

#define XRESET        (1 << 0)  /* 0x001 x reset */
#define XSTART        (1 << 1)  /* 0x002 start x */
#define XSRC_SYN      (1 << 2)  /* 0x004 run x synchronized */
#define XSRC_FRQ      (0 << 2)  /* 0x000 run x from clock source */
#define XDIR_IN       (1 << 3)  /* 0x008 move x in positive dir */
#define XDIR_POS      (1 << 3)  /* 0x008 x positive direction */
#define XDIR_NEG      (0 << 3)  /* 0x000 x negative direction */
#define XSET_LOC      (1 << 4)  /* 0x010 set x location */
#define XBACKLASH     (1 << 5)  /* 0x020 x backlash move no pos upd */
#define xCtlSize     6

// taper control register

#define TENA          (1 << 0)  /* 0x001 taper enable */
#define TZ            (1 << 1)  /* 0x002 one for taper z */
#define TX            (0 << 1)  /* 0x000 zero for taper x */
#define tCtlSize     2

// position control register

#define PRESET        (1 << 0)  /* 0x001 reset position */
#define PLIMIT        (1 << 1)  /* 0x002 set flag on limit reached */
#define PZERO         (1 << 2)  /* 0x004 set flag on zero reached */
#define pCtlSize     3

// configuration register

#define ZSTEP_POL     (1 << 0)  /* 0x001 z step pulse polarity */
#define ZDIR_POL      (1 << 1)  /* 0x002 z direction polarity */
#define XSTEP_POL     (1 << 2)  /* 0x004 x step pulse polarity */
#define XDIR_POL      (1 << 3)  /* 0x008 x direction polarity */
#define ENC_POL       (1 << 4)  /* 0x010 encoder dir polarity */
#define ZPULSE_MULT   (1 << 5)  /* 0x020 enable pulse multiplier */
#define cCtlSize     6

// debug control register

#define DBG_ENA       (1 << 0)  /* 0x001 enable debugging */
#define DBG_SEL       (1 << 1)  /* 0x002 select dbg encoder */
#define DBG_DIR       (1 << 2)  /* 0x004 debug direction */
#define DBG_COUNT     (1 << 3)  /* 0x008 gen count num dbg clks */
#define DBG_INIT      (1 << 4)  /* 0x010 init z modules */
#define DBG_RSYN      (1 << 5)  /* 0x020 running in sync mode */
#define DBG_MOVE      (1 << 6)  /* 0x040 used debug clock for move */
#define dCtlSize     7

// status register

#define S_Z_DONE_INT  (1 << 0)  /* 0x001 z done interrupt */
#define S_X_DONE_INT  (1 << 1)  /* 0x002 x done interrupt */
#define S_DBG_DONE    (1 << 2)  /* 0x004 debug done */
#define S_Z_START     (1 << 3)  /* 0x008 z start */
#define S_X_START     (1 << 4)  /* 0x010 x start */
#define S_ENC_DIR_IN  (1 << 5)  /* 0x020 encoder direction in */
#define statSize     6
