#if !defined(FPGA_LATHE)
#define FPGA_LATHE

enum FPGALATHE
{

// phase control

 F_Ld_Phase_Len     = 0,        /* 0x00 'LLN' phase length */
 F_Rd_Phase_Syn     = 1,        /* 0x01 'RSY' read phase at sync pulse */
 F_Phase_Max        = 2,        /* 0x02 number of phase registers */

// PWM

 F_Ld_PWM_Max       = 0,        /* 0x00 'MAX' pwm counter maximum */
 F_Ld_PWM_Trig      = 1,        /* 0x01 'TRG' pwm trigger */
 F_PWM_Max          = 2,        /* 0x02 number of pwm registers */

// encoder

 F_Ld_Enc_Prescale  = 0,        /* 0x00 'EPS' load encoder prescale */
 F_Ld_Enc_Cycle     = 1,        /* 0x01 'LEC' load encoder cycle */
 F_Ld_Int_Cycle     = 2,        /* 0x02 'LIC' load internal cycle */
 F_Rd_Cmp_Cyc_Clks  = 3,        /* 0x03 'RCC' read cmp cycle clocks */
 F_Enc_Max          = 4,        /* 0x04 number of encoder registers */

// debug frequency

 F_Ld_Dbg_Freq      = 0,        /* 0x00 'DBF' debug frequency */
 F_Ld_Dbg_Count     = 1,        /* 0x01 'DBC' debug clock count */
 F_Ld_Sync_Count    = 2,        /* 0x02 'DBS' debug sync length */
 F_Dbg_Freq_Max     = 3,        /* 0x03 number of debug frequency regs */

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
 F_Rd_Dist          = 12,       /* 0x0c 'RDS' read axis distance */
 F_Rd_Accel_Steps   = 13,       /* 0x0d 'RAS' read accel steps */
 F_Ld_Loc           = 14,       /* 0x0e 'LLC' axis location */
 F_Rd_Loc           = 15,       /* 0x0f 'RLC' read axis location */
 F_Ld_Dro           = 16,       /* 0x10 'LDR' axis dro */
 F_Ld_Dro_End       = 17,       /* 0x11 'LDE' axis dro end */
 F_Ld_Dro_Limit     = 18,       /* 0x12 'LDL' axis dro decel limit */
 F_Rd_Dro           = 19,       /* 0x13 'RDR' read axis dro */
 F_Sync_Max         = 20,       /* 0x14 number of sync registers */

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
 F_Axis_Max         = 24,       /* 0x18 num of axis regs */

// spindle

 F_Ld_Sp_Ctl        = 0,        /* 0x00 'LCT' spindle control reg */
 F_Ld_Sp_Freq       = 1,        /* 0x01 'LFR' freq for step spindle */
 F_Sp_Jog_Base      = 2,        /* 0x02 'J' spindle jog */
 F_Sp_Sync_Base     = 5,        /* 0x05 spindle sync */

// runout

 F_Ld_RunOut_Ctl    = 0,        /* 0x00 'CTL' runout control reg */
 F_Ld_Run_Limit     = 1,        /* 0x01 'LIM' runout limit */

// register definitions

 F_Noop             = 0,        /* 0x00 'NO' reg 0 */

// status registers

 F_Rd_Status        = 1,        /* 0x01 'RSTS' status reg */
 F_Rd_Inputs        = 2,        /* 0x02 'RINP' inputs reg */

// control registers

 F_Ld_Sync_Ctl      = 3,        /* 0x03 'LSYN' sync control reg */
 F_Ld_Cfg_Ctl       = 4,        /* 0x04 'LCFG' config control reg */
 F_Ld_Clk_Ctl       = 5,        /* 0x05 'LCLK' clock control reg */
 F_Ld_Out_Reg       = 6,        /* 0x06 'LDOU' output reg */
 F_Ld_Dsp_Reg       = 7,        /* 0x07 'LDSP' display reg */

// debug frequency control

 F_Dbg_Freq_Base    = 8,        /* 0x08 'D' dbg frequency */

// spindle speed

 F_Rd_Idx_Clks      = 11,       /* 0x0b 'RIDX' clocks per index */

// pwm

 F_PWM_Base         = 12,       /* 0x0c 'P' pwm control */

// base for modules

 F_Enc_Base         = 14,       /* 0x0e 'E' encoder registers */
 F_Phase_Base       = 18,       /* 0x12 'H' phase registers */
 F_RunOut_Base      = 20,       /* 0x14 'R' runout registers */
 F_ZAxis_Base       = 22,       /* 0x16 'Z' z axis registers */
 F_XAxis_Base       = 46,       /* 0x2e 'X' x axis registers */
 F_Spindle_Base     = 70,       /* 0x46 'S' spindle registers */
 F_Cmd_Max          = 95,       /* 0x5f number of commands */
};

#endif  /* FPGA_LATHE */
