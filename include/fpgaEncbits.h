#if !defined(FPGA_ENC_BITS)
#define FPGA_ENC_BITS

// cFile

// run control register

#define CTL_RESET            (1 << 0)   /* 0x001 reset */
#define CTL_TEST_CLOCK       (1 << 1)   /* 0x002 testclock */
#define CTL_SPARE            (1 << 2)   /* 0x004 spare */
#define R_CTL_SIZE           3

// debug control register

#define DBG_ENA              (1 << 0)   /* 0x001 enable debugging */
#define DBG_SEL              (1 << 1)   /* 0x002 select dbg encoder */
#define DBG_DIR              (1 << 2)   /* 0x004 debug direction */
#define DBG_COUNT            (1 << 3)   /* 0x008 gen count num dbg clks */
#define D_CTL_SIZE           4

#endif  /* FPGA_ENC_BITS */
