#if !defined(FPGA_ENC)
#define FPGA_ENC

enum FPGAENC
{
 F_Noop             = 0,        /* 0x00 register 0 */
 F_Ld_Run_Ctl       = 1,        /* 0x01 load run control register */
 F_Ld_Dbg_Ctl       = 2,        /* 0x02 load debug control register */
 F_Ld_Enc_Cycle     = 3,        /* 0x03 load encoder cycle */
 F_Ld_Int_Cycle     = 4,        /* 0x04 load internal cycle */
 F_Rd_Cmp_Cyc_C     = 5,        /* 0x05 read cmp cycle clocks */
 F_Ld_Dbg_Freq      = 6,        /* 0x06 load debug frequency */
 F_Ld_Dbg_Count     = 7,        /* 0x07 load debug clocks */
};

#endif  /* FPGA_ENC */
