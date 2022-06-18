
// status register

#define ZAXISENA      (1 << 0)  /* 0x001 z axis enable flag */
#define ZAXISDONE     (1 << 1)  /* 0x002 z axis done */
#define ZAXISCURDIR   (1 << 2)  /* 0x004 z axis current dir */
#define XAXISDONE     (1 << 3)  /* 0x008 x axis done */
#define XAXISENA      (1 << 4)  /* 0x010 x axis enable flag */
#define XAXISCURDIR   (1 << 5)  /* 0x020 x axis current dir */
#define STESTOP       (1 << 6)  /* 0x040 emergency stop */
#define SPINDLEACTIVE  (1 << 7) /* 0x080 x axis current dir */
#define QUENOTEMPTY   (1 << 8)  /* 0x100 ctl queue not empty */
#define CTLBUSY       (1 << 9)  /* 0x200 controller busy */
#define SYNCACTIVE    (1 << 10) /* 0x400 sync active */
#define statusSize   11

// inputs register

#define INZHOME       (1 << 0)  /* 0x001 z home switch */
#define INZMINUS      (1 << 1)  /* 0x002 z limit minus */
#define INZPLUS       (1 << 2)  /* 0x004 z Limit Plus */
#define INXHOME       (1 << 3)  /* 0x008 x home switch */
#define INXMINUS      (1 << 4)  /* 0x010 x limit minus */
#define INXPLUS       (1 << 5)  /* 0x020 x Limit Plus */
#define INSPARE       (1 << 6)  /* 0x040 spare input */
#define INPROBE       (1 << 7)  /* 0x080 probe input */
#define INPIN10       (1 << 8)  /* 0x100 pin 10 */
#define INPIN11       (1 << 9)  /* 0x200 pin 11 */
#define INPIN12       (1 << 10) /* 0x400 pin 12 */
#define INPIN13       (1 << 11) /* 0x800 pin 13 */
#define INPIN15       (1 << 12) /* 0x1000 pin 15 */
#define inputsSize   13

// run control register

#define RUNENA        (1 << 0)  /* 0x001 run from controller data */
#define RUNINIT       (1 << 1)  /* 0x002 initialize controller */
#define READERINIT    (1 << 2)  /* 0x004 initialize reader */
#define runSize      3

// jog control register

#define JOGCONTINUOUS  (1 << 0) /* 0x001 jog continuous mode */
#define JOGBACKLASH   (1 << 1)  /* 0x002 jog backlash present */
#define jogSize      2

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
#define CTLDROEND     (1 << 8)  /* 0x100 use dro to end move */
#define CTLJOGENA     (1 << 9)  /* 0x200 enable jog */
#define CTLHOME       (1 << 10) /* 0x400 homing axis */
#define CTLIGNORELIM  (1 << 11) /* 0x800 ignore limits */
#define axisCtlSize  12

// axis status register

#define AXDONEDIST    (1 << 0)  /* 0x001 axis done distance */
#define AXDONEDRO     (1 << 1)  /* 0x002 axis done dro */
#define AXDONEHOME    (1 << 2)  /* 0x004 axis done home */
#define AXDONELIMIT   (1 << 3)  /* 0x008 axis done limit */
#define axisStatusSize 4

// configuration control register

#define CFGZDIRINV    (1 << 0)  /* 0x001 z direction inverted */
#define CFGXDIRINV    (1 << 1)  /* 0x002 x direction inverted */
#define CFGZDROINV    (1 << 2)  /* 0x004 z dro direction inverted */
#define CFGXDROINV    (1 << 3)  /* 0x008 x dro direction inverted */
#define CFGZJOGINV    (1 << 4)  /* 0x010 z jog direction inverted */
#define CFGXJOGINV    (1 << 5)  /* 0x020 x jog direction inverted */
#define CFGSPDIRINV   (1 << 6)  /* 0x040 spindle direction inverted */
#define CFGZHOMEINV   (1 << 7)  /* 0x080 z home inverted */
#define CFGZMINUSINV  (1 << 8)  /* 0x100 z minus inverted */
#define CFGZPLUSINV   (1 << 9)  /* 0x200 z plus inverted */
#define CFGXHOMEINV   (1 << 10) /* 0x400 x home inverted */
#define CFGXMINUSINV  (1 << 11) /* 0x800 x minus inverted */
#define CFGXPLUSINV   (1 << 12) /* 0x1000 x plus inverted */
#define CFGPROBEINV   (1 << 13) /* 0x2000 probe inverted */
#define CFGENCDIRINV  (1 << 14) /* 0x4000 invert encoder direction */
#define CFGESTOPENA   (1 << 15) /* 0x8000 estop enable */
#define CFGESTOPINV   (1 << 16) /* 0x10000 estop invert */
#define CFGENAENCDIR  (1 << 17) /* 0x20000 enable encoder direction */
#define CFGGENSYNC    (1 << 18) /* 0x40000 no encoder generate sync pulse */
#define CFGPWMENA     (1 << 19) /* 0x80000 pwm enable */
#define cfgCtlSize   20

// clock control register

#define CLKDBGFREQENA  (1 << 6) /* 0x040 enable debug frequency */
#define clkCtlSize   7

// sync control register

#define SYNPHASEINIT  (1 << 0)  /* 0x001 init phase counter */
#define SYNENCINIT    (1 << 1)  /* 0x002 init encoder */
#define SYNENCENA     (1 << 2)  /* 0x004 enable encoder */
#define synCtlSize   3

// spindle control register

#define SPINIT        (1 << 0)  /* 0x001 spindle init */
#define SPENA         (1 << 1)  /* 0x002 spindle enable */
#define SPDIR         (1 << 2)  /* 0x004 spindle direction */
#define SPJOGENABLE   (1 << 3)  /* 0x008 spindle jog enable */
#define spCtlSize    4
