enum FPGALATHEREG
{

// phase control

 F_Ld_Phase_Len,                /* 0x00 phase length */
 F_Rd_Phase_Syn,                /* 0x01 read phase at sync pulse */
 F_Phase_Max,                   /* 0x02 number of phase registers */

// controller

 F_Ld_Ctrl_Data,                /* 0x00 load controller data */
 F_Ctrl_Cmd,                    /* 0x01 controller command */
 F_Ld_Seq,                      /* 0x02 load sequence */
 F_Rd_Seq,                      /* 0x03 read sequence */
 F_Rd_Ctr,                      /* 0x04 read counter */
 F_Ctrl_Max,                    /* 0x05 number of controller registers */

// reader

 F_Ld_Read_Data,                /* 0x00 load reader data */
 F_Read,                        /* 0x01 read data */
 F_Read_Max,                    /* 0x02 number of reader registers */

// PWM

 F_Ld_PWM_Max,                  /* 0x00 pwm counter maximum */
 F_Ld_PWM_Trig,                 /* 0x00 pwm trigger */
 F_PWM_Max,                     /* 0x01 number of pwm registers */

// encoder

 F_Ld_Enc_Cycle,                /* 0x00 load encoder cycle */
 F_Ld_Int_Cycle,                /* 0x01 load internal cycle */
 F_Rd_Cmp_Cyc_Clks,             /* 0x02 read cmp cycle clocks */
 F_Enc_Max,                     /* 0x03 number of encoder registers */

// debug frequency

 F_Ld_Dbg_Freq,                 /* 0x00 debug frequency */
 F_Ld_Dbg_Count,                /* 0x01 debug count */
 F_Dbg_Freq_Max,                /* 0x02 number of debug frequency regs */

// sync accel

 F_Ld_D,                        /* 0x00 axis d */
 F_Ld_Incr1,                    /* 0x01 axis incr1 */
 F_Ld_Incr2,                    /* 0x02 axis incr2 */
 F_Ld_Accel_Val,                /* 0x03 axis accel value */
 F_Ld_Accel_Count,              /* 0x04 axis accel count */
 F_Rd_XPos,                     /* 0x05 axis x pos */
 F_Rd_YPos,                     /* 0x06 axis y pos */
 F_Rd_Sum,                      /* 0x07 axis sum */
 F_Rd_Accel_Sum,                /* 0x08 axis accel sum */
 F_Rd_Accel_Ctr,                /* 0x09 axis accel counter */
 F_Sync_Max,                    /* 0x0a number of sync registers */

// distance registers

 F_Ld_Dist,                     /* 0x00 axis distance */
 F_Rd_Dist,                     /* 0x01 read axis distance */
 F_Rd_Acl_Steps,                /* 0x02 read accel steps */
 F_Dist_Max,                    /* 0x03 number of distance registers */

// location registers

 F_Ld_Loc,                      /* 0x00 axis location */
 F_Rd_Loc,                      /* 0x01 read axis location */
 F_Loc_Max,                     /* 0x02 number of location registers */

// dro registers

 F_Ld_Dro,                      /* 0x00 axis dro */
 F_Ld_Dro_End,                  /* 0x01 axis dro end */
 F_Ld_Dro_Limit,                /* 0x02 axis dro deceleration limit */
 F_Rd_Dro,                      /* 0x03 read axis dro */
 F_Dro_Max,                     /* 0x04 number of dro registers */

// jog registers

 F_Ld_Jog_Ctl,                  /* 0x00 jog control */
 F_Ld_Jog_Inc,                  /* 0x01 jog increment */
 F_Ld_Jog_Back,                 /* 0x02 jog backlash increment */
 F_Jog_Max,                     /* 0x03 number of jog registers */

// axis

 F_Rd_Axis_Status,              /* 0x00 axis status */
 F_Ld_Axis_Ctl,                 /* 0x01 axis control register */
 F_Ld_Freq,                     /* 0x02 frequency */
 F_Sync_Base,                   /* 0x03 sync registers */
 F_Dist_Base,                   /* 0x0d distance registers */
 F_Loc_Base,                    /* 0x10 location registers */
 F_Dro_Base,                    /* 0x12 dro registers */
 F_Jog_Base,                    /* 0x16 jog registers */
 F_Axis_Max,                    /* 0x19 number of axis registers */

// spindle

 F_Ld_Sp_Ctl,                   /* 0x00 spindle control register */
 F_Ld_Sp_Freq,                  /* 0x01 freq for step spindle */
 F_Sp_Sync_Base,                /* 0x02 spindle sync */
 F_Sp_Jog_Base,                 /* 0x0c spindle jog */

// register definitions

 F_Noop,                        /* 0x00 register 0 */

// status registers

 F_Rd_Status,                   /* 0x01 status register */
 F_Rd_Inputs,                   /* 0x02 inputs register */

// control registers

 F_Ld_Run_Ctl,                  /* 0x03 run control register */
 F_Ld_Sync_Ctl,                 /* 0x04 sync control register */
 F_Ld_Cfg_Ctl,                  /* 0x05 config control register */
 F_Ld_Clk_Ctl,                  /* 0x06 clock control register */
 F_Ld_Dsp_Reg,                  /* 0x07 display register */

// controller

 F_Ctrl_Base,                   /* 0x08 controller */

// reader

 F_Read_Base,                   /* 0x0d reader */

// debug frequency control

 F_Dbg_Freq_Base,               /* 0x0f dbg frequency */

// spindle speed

 F_Rd_Idx_Clks,                 /* 0x11 read clocks between index pulses */

// step spindle frequency generator


// pwm

 F_PWM_Base,                    /* 0x12 pwm control */

// base for modules

 F_Enc_Base,                    /* 0x14 encoder registers */
 F_Phase_Base,                  /* 0x17 phase registers */
 F_ZAxis_Base,                  /* 0x19 z axis registers */
 F_XAxis_Base,                  /* 0x32 x axis registers */
 F_Spindle_Base,                /* 0x4b spindle registers */
 F_Cmd_Max,                     /* 0x5a number of commands */
};
