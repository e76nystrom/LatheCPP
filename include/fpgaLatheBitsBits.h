
// status register

#define ZAXISENA      (1 << 0)  /* 0x001 z axis enable flag */
#define ZAXISDONE     (1 << 1)  /* 0x002 z axis done */
#define XAXISENA      (1 << 2)  /* 0x004 x axis enable flag */
#define XAXISDONE     (1 << 3)  /* 0x008 x axis done */
#define QUEEMPTY      (1 << 4)  /* 0x010 controller queue empty */
#define CTLIDLE       (1 << 5)  /* 0x020 controller idle */
#define SYNCACTIVE    (1 << 6)  /* 0x040 sync active */
#define statusSize   7

// run control register

#define RUNENA        (1 << 0)  /* 0x001 run from controller data */
#define RUNINIT       (1 << 1)  /* 0x002 initialize controller */
#define READERINIT    (1 << 2)  /* 0x004 initialize reader */
#define runSize      3

// axis control register

#define CTLINIT       (1 << 0)  /* 0x001 reset flag */
#define CTLSTART      (1 << 1)  /* 0x002 start */
#define CTLBACKLASH   (1 << 2)  /* 0x004 backlash move no pos upd */
#define CTLWAITSYNC   (1 << 3)  /* 0x008 wait for sync to start */
#define CTLDIR        (1 << 4)  /* 0x010 direction */
#define CTLDIRPOS     (1 << 4)  /* 0x010 move in positive dir */
#define CTLDIRNEG     (0 << 4)  /* 0x000 move in negative dir */
#define CTLSETLOC     (1 << 5)  /* 0x020 set location */
#define CTLCHDIRECT   (1 << 6)  /* 0x040 ch input direct */
#define CTLSLAVE      (1 << 7)  /* 0x080 slave controlled by other axis */
#define axisCtlSize  8

// configuration control register

#define CFGZDIR       (1 << 0)  /* 0x001 z direction inverted */
#define CFGXDIR       (1 << 1)  /* 0x002 x direction inverted */
#define CFGSPDIR      (1 << 2)  /* 0x004 spindle directiion inverted */
#define CFGENCDIR     (1 << 3)  /* 0x008 invert encoder direction */
#define CFGENAENCDIR  (1 << 4)  /* 0x010 enable encoder direction */
#define CFGGENSYNC    (1 << 5)  /* 0x020 no encoder generate sync pulse */
#define cfgCtlSize   6

// clock control register

#define CLKNONE       (0 << 0)  /* 0x000  */
#define CLKFREQ       (1 << 0)  /* 0x001  */
#define CLKCH         (2 << 0)  /* 0x002  */
#define CLKINTCLK     (3 << 0)  /* 0x003  */
#define CLKSLVFREQ    (4 << 0)  /* 0x004  */
#define CLKSLVCH      (5 << 0)  /* 0x005  */
#define CLKSPARE      (6 << 0)  /* 0x006  */
#define CLKDBGFREQ    (7 << 0)  /* 0x007  */
#define ZFREQSEL      (7 << 0)  /* 0x007 z Frequency select */
#define ZCLKNONE      (0 << 0)  /* 0x000  */
#define ZCLKZFREQ     (1 << 0)  /* 0x001  */
#define ZCLKCH        (2 << 0)  /* 0x002  */
#define ZCLKINTCLK    (3 << 0)  /* 0x003  */
#define ZCLKXFREQ     (4 << 0)  /* 0x004  */
#define ZCLKXCH       (5 << 0)  /* 0x005  */
#define ZCLKSPARE     (6 << 0)  /* 0x006  */
#define ZCLKDBGFREQ   (7 << 0)  /* 0x007  */
#define XFREQSEL      (7 << 3)  /* 0x038 x Frequency select */
#define XCLKNONE      (0 << 0)  /* 0x000  */
#define XCLKXFREQ     (1 << 3)  /* 0x008  */
#define XCLKCH        (2 << 3)  /* 0x010  */
#define XCLKINTCLK    (3 << 3)  /* 0x018  */
#define XCLKZFREQ     (4 << 3)  /* 0x020  */
#define XCLKZCH       (5 << 3)  /* 0x028  */
#define XCLKSPARE     (6 << 0)  /* 0x006  */
#define XCLKDBGFREQ   (7 << 3)  /* 0x038  */
#define CLKDBGFREQENA  (1 << 6) /* 0x040 enable debug frequency */
#define clkCtlSize   7

// sync control register

#define SYNPHASEINIT  (1 << 0)  /* 0x001 init phase counter */
#define SYNENCINIT    (1 << 1)  /* 0x002 init encoder */
#define SYNENCENA     (1 << 2)  /* 0x004 enable encoder */
#define synCtlSize   3
