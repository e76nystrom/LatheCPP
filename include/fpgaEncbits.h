
// run control register

#define CTLRESET      (1 << 0)  /* 0x001 reset */
#define CTLTESTCLOCK  (1 << 1)  /* 0x002 testclock */
#define CTLSPARE      (1 << 2)  /* 0x004 spare */
#define rCtlSize     3

// debug control register

#define DBGENA        (1 << 0)  /* 0x001 enable debugging */
#define DBGSEL        (1 << 1)  /* 0x002 select dbg encoder */
#define DBGDIR        (1 << 2)  /* 0x004 debug direction */
#define DBGCOUNT      (1 << 3)  /* 0x008 gen count num dbg clks */
#define dCtlSize     4
