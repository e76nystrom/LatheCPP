#if !defined(FPGA_LATHE)
#define FPGA_LATHE

// RiscV control register

#define RISCV_DATA         (1 << 0)     /* 0x001 riscv data active */
#define RISCV_SPI          (1 << 1)     /* 0x002 riscv spi active */
#define RISCV_CTL_SIZE     2

// status register

#define Z_AXIS_ENA         (1 << 0)     /* 0x001 'ZE' z axis enable flag */
#define Z_AXIS_DONE        (1 << 1)     /* 0x002 'ZD' z axis done */
#define Z_AXIS_CUR_DIR     (1 << 2)     /* 0x004 'Zd' z axis current dir */
#define X_AXIS_ENA         (1 << 3)     /* 0x008 'XE' x axis enable flag */
#define X_AXIS_DONE        (1 << 4)     /* 0x010 'XD' x axis done */
#define X_AXIS_CUR_DIR     (1 << 5)     /* 0x020 'Xd' x axis current dir */
#define ST_ESTOP           (1 << 6)     /* 0x040 'ES' emergency stop */
#define SPINDLE_ACTIVE     (1 << 7)     /* 0x080 'S+' spindle active */
#define QUE_NOT_EMPTY      (1 << 8)     /* 0x100 'Q+' ctl queue not empty */
#define CTL_BUSY           (1 << 9)     /* 0x200 'CB' controller busy */
#define SYNC_ACTIVE        (1 << 10)    /* 0x400 'SA' sync active */
#define STATUS_SIZE        11

// inputs register

#define IN_ZHOME           (1 << 0)     /* 0x001 z home switch */
#define IN_ZMINUS          (1 << 1)     /* 0x002 z limit minus */
#define IN_ZPLUS           (1 << 2)     /* 0x004 z Limit Plus */
#define IN_XHOME           (1 << 3)     /* 0x008 x home switch */
#define IN_XMINUS          (1 << 4)     /* 0x010 x limit minus */
#define IN_XPLUS           (1 << 5)     /* 0x020 x Limit Plus */
#define IN_SPARE           (1 << 6)     /* 0x040 spare input */
#define IN_PROBE           (1 << 7)     /* 0x080 probe input */
#define IN_PIN10           (1 << 8)     /* 0x100 pin 10 */
#define IN_PIN11           (1 << 9)     /* 0x200 pin 11 */
#define IN_PIN12           (1 << 10)    /* 0x400 pin 12 */
#define IN_PIN13           (1 << 11)    /* 0x800 pin 13 */
#define IN_PIN15           (1 << 12)    /* 0x1000 pin 15 */
#define INPUTS_SIZE        13

// run control register

#define RUN_ENA            (1 << 0)     /* 0x001 run from controller data */
#define RUN_INIT           (1 << 1)     /* 0x002 initialize controller */
#define READER_INIT        (1 << 2)     /* 0x004 initialize reader */
#define RUN_SIZE           3

// jog control register

#define JOG_CONTINUOUS     (1 << 0)     /* 0x001 jog continuous mode */
#define JOG_BACKLASH       (1 << 1)     /* 0x002 jog backlash present */
#define JOG_SIZE           2

// axis control register

#define CTL_INIT           (1 << 0)     /* 0x001 reset flag */
#define CTL_START          (1 << 1)     /* 0x002 start */
#define CTL_BACKLASH       (1 << 2)     /* 0x004 backlash move no pos upd */
#define CTL_WAIT_SYNC      (1 << 3)     /* 0x008 wait for sync to start */
#define CTL_DIR            (1 << 4)     /* 0x010 direction */
#define CTL_SET_LOC        (1 << 5)     /* 0x020 set location */
#define CTL_CH_DIRECT      (1 << 6)     /* 0x040 ch input direct */
#define CTL_SLAVE          (1 << 7)     /* 0x080 slave ctl by other axis */
#define CTL_DRO_END        (1 << 8)     /* 0x100 use dro to end move */
#define CTL_DIST_MODE      (1 << 9)     /* 0x200 distance udpdate mode */
#define CTL_JOG_CMD        (1 << 10)    /* 0x400 jog with commands */
#define CTL_JOG_MPG        (1 << 11)    /* 0x800 jog with mpg */
#define CTL_HOME           (1 << 12)    /* 0x1000 homing axis */
#define CTL_USE_LIMITS     (1 << 13)    /* 0x2000 use limits */
#define AXIS_CTL_SIZE      14

// axis status register

#define AX_DONE_DIST       (1 << 0)     /* 0x001 axis done distance */
#define AX_DONE_DRO        (1 << 1)     /* 0x002 axis done dro */
#define AX_DONE_HOME       (1 << 2)     /* 0x004 axis done home */
#define AX_DONE_LIMIT      (1 << 3)     /* 0x008 axis done limit */
#define AX_DIST_ZERO       (1 << 4)     /* 0x010 axis distance zero */
#define AXIS_STATUS_SIZE   5

// configuration control register

#define CFG_ZDIR_INV       (1 << 0)     /* 0x001 z dir inverted */
#define CFG_XDIR_INV       (1 << 1)     /* 0x002 x dir inverted */
#define CFG_ZDRO_INV       (1 << 2)     /* 0x004 z dro dir inverted */
#define CFG_XDRO_INV       (1 << 3)     /* 0x008 x dro dir inverted */
#define CFG_ZMPG_INV       (1 << 4)     /* 0x010 z mpg dir inverted */
#define CFG_XMPG_INV       (1 << 5)     /* 0x020 x mpg dir inverted */
#define CFG_SP_DIR_INV     (1 << 6)     /* 0x040 spindle dir inverted */
#define CFG_ZHOME_INV      (1 << 7)     /* 0x080 z home inverted */
#define CFG_ZMINUS_INV     (1 << 8)     /* 0x100 z minus inverted */
#define CFG_ZPLUS_INV      (1 << 9)     /* 0x200 z plus inverted */
#define CFG_XHOME_INV      (1 << 10)    /* 0x400 x home inverted */
#define CFG_XMINUS_INV     (1 << 11)    /* 0x800 x minus inverted */
#define CFG_XPLUS_INV      (1 << 12)    /* 0x1000 x plus inverted */
#define CFG_PROBE_INV      (1 << 13)    /* 0x2000 probe inverted */
#define CFG_ENC_DIR_INV    (1 << 14)    /* 0x4000 invert encoder dir */
#define CFG_ESTOP_ENA      (1 << 15)    /* 0x8000 estop enable */
#define CFG_ESTOP_INV      (1 << 16)    /* 0x10000 estop invert */
#define CFG_ENA_ENC_DIR    (1 << 17)    /* 0x20000 enable encoder dir */
#define CFG_GEN_SYNC       (1 << 18)    /* 0x40000 generate sync pulse */
#define CFG_PWM_ENA        (1 << 19)    /* 0x80000 pwm enable */
#define CFG_DRO_STEP       (1 << 20)    /* 0x100000 step pulse to dro */
#define CFG_CTL_SIZE       21

// clock control register

#define Z_FREQ_SEL         (0x7 << 0)   /* 0x007 z Frequency select */
#define X_FREQ_SEL         (0x7 << 3)   /* 0x038 x Frequency select */
#define Z_FREQ_SHIFT       (0 << 0)     /* 0x000 z Frequency shift */
#define X_FREQ_SHIFT       (3 << 0)     /* 0x003 x Frequency shift */
#define CLK_MASK           (7 << 0)     /* 0x007 clock mask */
#define CLK_NONE           (0 << 0)     /* 0x000  */
#define CLK_FREQ           (1 << 0)     /* 0x004  */
#define CLK_CH             (2 << 0)     /* 0x008  */
#define CLK_INT_CLK        (3 << 0)     /* 0x00c  */
#define CLK_SLV_FREQ       (4 << 0)     /* 0x010  */
#define CLK_SLV_CH         (5 << 0)     /* 0x014  */
#define CLK_SPINDLE        (6 << 0)     /* 0x018  */
#define CLK_DBG_FREQ       (7 << 0)     /* 0x01c  */
#define Z_CLK_NONE         (0 << 0)     /* 0x000  */
#define Z_CLK_ZFREQ        (1 << 0)     /* 0x004  */
#define Z_CLK_CH           (2 << 0)     /* 0x008  */
#define Z_CLK_INT_CLK      (3 << 0)     /* 0x00c  */
#define Z_CLK_XFREQ        (4 << 0)     /* 0x010  */
#define Z_CLK_XCH          (5 << 0)     /* 0x014  */
#define Z_CLK_SPINDLE      (6 << 0)     /* 0x018  */
#define Z_CLK_DBG_FREQ     (7 << 0)     /* 0x01c  */
#define X_CLK_NONE         (0 << 3)     /* 0x000  */
#define X_CLK_XFREQ        (1 << 3)     /* 0x020  */
#define X_CLK_CH           (2 << 3)     /* 0x040  */
#define X_CLK_INT_CLK      (3 << 3)     /* 0x060  */
#define X_CLK_ZFREQ        (4 << 3)     /* 0x080  */
#define X_CLK_ZCH          (5 << 3)     /* 0x0a0  */
#define X_CLK_SPINDLE      (6 << 3)     /* 0x0c0  */
#define X_CLK_DBG_FREQ     (7 << 3)     /* 0x0e0  */
#define CLK_DBG_FREQ_ENA   (1 << 6)     /* 0x040 enable debug frequency */
#define CLK_CTL_SIZE       7

// sync control register

#define SYN_PHASE_INIT     (1 << 0)     /* 0x001 init phase counter */
#define SYN_ENC_INIT       (1 << 1)     /* 0x002 init encoder */
#define SYN_ENC_ENA        (1 << 2)     /* 0x004 enable encoder */
#define SYN_CTL_SIZE       3

// spindle control register

#define SP_INIT            (1 << 0)     /* 0x001 spindle init */
#define SP_ENA             (1 << 1)     /* 0x002 spindle enable */
#define SP_DIR             (1 << 2)     /* 0x004 spindle direction */
#define SP_JOG_ENABLE      (1 << 3)     /* 0x008 spindle jog enable */
#define SP_CTL_SIZE        4

#endif  /* FPGA_LATHE */
