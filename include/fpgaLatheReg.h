#if !defined(FPGA_LATHE_REG)
#define FPGA_LATHE_REG

enum FPGALATHEREG
{

// phase control

 F_Ld_Phase_Len     = 0,        /* 0x00 'LLN' phase length */
 F_Rd_Phase_Syn     = 1,        /* 0x01 'RSY' read phase at sync pulse */
 F_Phase_Max        = 2,        /* 0x02 number of phase registers */

// controller

 F_Ld_Ctrl_Data     = 0,        /* 0x00 'LCD' load controller data */
 F_Ctrl_Cmd         = 1,        /* 0x01 'CMD' controller command */
 F_Ld_Seq           = 2,        /* 0x02 'LSQ' load sequence */
 F_Rd_Seq           = 3,        /* 0x03 'RSQ' read sequence */
 F_Rd_Ctr           = 4,        /* 0x04 'RCT' read counter */
 F_Ctrl_Max         = 5,        /* 0x05 number of controller registers */

// reader

 F_Ld_Read_Data     = 0,        /* 0x00 'LDR' load reader data */
 F_Read             = 1,        /* 0x01 'RD'  read data */
 F_Read_Max         = 2,        /* 0x02 number of reader registers */

// PWM

 F_Ld_PWM_Max       = 0,        /* 0x00 'MAX' pwm counter maximum */
 F_Ld_PWM_Trig      = 0,        /* 0x00 'TRG' pwm trigger */
 F_PWM_Max          = 1,        /* 0x01 number of pwm registers */

// encoder

 F_Ld_Enc_Cycle     = 0,        /* 0x00 'LEC' load encoder cycle */
 F_Ld_Int_Cycle     = 1,        /* 0x01 'LIC' load internal cycle */
 F_Rd_Cmp_Cyc_C     = 2,        /* 0x02 'RCC' read cmp cycle clocks */
 F_Enc_Max          = 3,        /* 0x03 number of encoder registers */

// debug frequency

 F_Ld_Dbg_Freq      = 0,        /* 0x00 'DBF' debug frequency */
 F_Ld_Dbg_Count     = 1,        /* 0x01 'DBC' debug count */
 F_Dbg_Freq_Max     = 2,        /* 0x02 number of debug frequency regs */

// sync accel

 F_Ld_D             = 0,        /* 0x00 'LIS' axis initial sum */
 F_Ld_Incr1         = 1,        /* 0x01 'LI1' axis incr1 */
 F_Ld_Incr2         = 2,        /* 0x02 'LI2' axis incr2 */
 F_Ld_Accel_Val     = 3,        /* 0x03 'LAV' axis accel value */
 F_Ld_Accel_Count   = 4,        /* 0x04 'LAC' axis accel count */
 F_Rd_XPos          = 5,        /* 0x05 'RX'  axis x pos */
 F_Rd_YPos          = 6,        /* 0x06 'RY'  axis y pos */
 F_Rd_Sum           = 7,        /* 0x07 'RSU' axis sum */
 F_Rd_Accel_Sum     = 8,        /* 0x08 'RAS' axis accel sum */
 F_Rd_Accel_Ctr     = 9,        /* 0x09 'RAC' axis accel counter */
 F_Ld_Dist          = 10,       /* 0x0a 'LDS' axis distance */
 F_Ld_Max_Dist      = 11,       /* 0x0b 'LMD' jog maximum distance */
 F_Ld_Backlash      = 12,       /* 0x0c 'LB'  jog backlash */
 F_Rd_Dist          = 13,       /* 0x0d 'RDS' read axis distance */
 F_Rd_Accel_Steps   = 14,       /* 0x0e 'RAS' read accel steps */
 F_Ld_Loc           = 15,       /* 0x0f 'LLC' axis location */
 F_Rd_Loc           = 16,       /* 0x10 'RLC' read axis location */
 F_Ld_Mpg_Delta     = 17,       /* 0x11 'LMD' Mpg delta values */
 F_Ld_Mpg_Dist      = 18,       /* 0x12 'LMS' Mpg dist values */
 F_Ld_Mpg_Div       = 19,       /* 0x13 'LMV' Mpg div values */
 F_Ld_Dro           = 20,       /* 0x14 'LDR' axis dro */
 F_Ld_Dro_End       = 21,       /* 0x15 'LDE' axis dro end */
 F_Ld_Dro_Limit     = 22,       /* 0x16 'LDL' axis dro decel limit */
 F_Rd_Dro           = 23,       /* 0x17 'RDR' read axis dro */
 F_Sync_Max         = 24,       /* 0x18 number of sync registers */

// jog registers

 F_Ld_Jog_Ctl       = 0,        /* 0x00 'CT' jog control */
 F_Ld_Jog_Inc       = 1,        /* 0x01 'IN' jog increment */
 F_Ld_Jog_Back      = 2,        /* 0x02 'JB' jog backlash increment */
 F_Jog_Max          = 3,        /* 0x03 number of jog registers */

// axis

 F_Rd_Axis_Status   = 0,        /* 0x00 'RAS' read axis status */
 F_Ld_Axis_Ctl      = 1,        /* 0x01 'LAC' set axis control reg */
 F_Rd_Axis_Ctl      = 2,        /* 0x02 'RAC' read axis control reg */
 F_Ld_Freq          = 3,        /* 0x03 'LFR' frequency */
 F_Sync_Base        = 4,        /* 0x04 sync registers */
 F_Axis_Max         = 28,       /* 0x1c num of axis regs */

// spindle

 F_Ld_Sp_Ctl        = 0,        /* 0x00 'LCT' spindle control reg */
 F_Ld_Sp_Freq       = 1,        /* 0x01 'LFR' freq for step spindle */
 F_Sp_Jog_Base      = 2,        /* 0x02 'J' spindle jog */
 F_Sp_Sync_Base     = 5,        /* 0x05 spindle sync */

// register definitions

 F_Noop             = 0,        /* 0x00 'NO' reg 0 */

// status registers

 F_Rd_Status        = 1,        /* 0x01 'RSTS' status reg */
 F_Rd_Inputs        = 2,        /* 0x02 'RINP' inputs reg */

// control registers

 F_Ld_Run_Ctl       = 3,        /* 0x03 'LRUN' set run control reg */
 F_Rd_Run_Ctl       = 4,        /* 0x04 'RRUN' read run control reg */
 F_Ld_Sync_Ctl      = 5,        /* 0x05 'LSYN' sync control reg */
 F_Ld_Cfg_Ctl       = 6,        /* 0x06 'LCFG' config control reg */
 F_Ld_Clk_Ctl       = 7,        /* 0x07 'LCLK' clock control reg */
 F_Ld_Dsp_Reg       = 8,        /* 0x08 'LDSP' display reg */

// controller

 F_Ctrl_Base        = 9,        /* 0x09 'C' controller */

// reader

 F_Read_Base        = 14,       /* 0x0e 'R' reader */

// debug frequency control

 F_Dbg_Freq_Base    = 16,       /* 0x10 'D' dbg frequency */

// spindle speed

 F_Rd_Idx_Clks      = 18,       /* 0x12 'RIDX' clocks per index */

// step spindle frequency generator


// pwm

 F_PWM_Base         = 19,       /* 0x13 'P' pwm control */

// base for modules

 F_Enc_Base         = 21,       /* 0x15 'E' encoder registers */
 F_Phase_Base       = 24,       /* 0x18 'H' phase registers */
 F_ZAxis_Base       = 26,       /* 0x1a 'Z' z axis registers */
 F_XAxis_Base       = 54,       /* 0x36 'X' x axis registers */
 F_Spindle_Base     = 82,       /* 0x52 'S' spindle registers */
 F_Cmd_Max          = 111,      /* 0x6f number of commands */
};

#endif  /* FPGA_LATHE_REG */
