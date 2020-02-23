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

// axis

 F_Ld_Axis_Ctl,                 /* 0x00 axis control register */
 F_Ld_Freq,                     /* 0x01 frequency */
 F_Sync_Base,                   /* 0x02 sync registers */
 F_Dist_Base,                   /* 0x0c distance registers */
 F_Loc_Base,                    /* 0x0f location registers */
 F_Axis_Max,                    /* 0x11 number of axis registers */

// register definitions

 F_Noop,                        /* 0x00 register 0 */

// status registers

 F_Rd_Status,                   /* 0x01 status register */

// control registers

 F_Ld_Run_Ctl,                  /* 0x02 run control register */
 F_Ld_Sync_Ctl,                 /* 0x03 sync control register */
 F_Ld_Cfg_Ctl,                  /* 0x04 config control register */
 F_Ld_Clk_Ctl,                  /* 0x05 clock control register */
 F_Ld_Dsp_Reg,                  /* 0x06 display register */

// controller

 F_Ctrl_Base,                   /* 0x07 controller */

// reader

 F_Read_Base,                   /* 0x0c reader */

// debug frequency control

 F_Dbg_Freq_Base,               /* 0x0e dbg frequency */

// spindle speed

 F_Rd_Idx_Clks,                 /* 0x10 read clocks between index pulses */

// pwm

 F_PWM_Base,                    /* 0x11 pwm control */

// base for modules

 F_Enc_Base,                    /* 0x13 encoder registers */
 F_Phase_Base,                  /* 0x16 phase registers */
 F_ZAxis_Base,                  /* 0x18 z axis registers */
 F_XAxis_Base,                  /* 0x29 x axis registers */
 F_Cmd_Max,                     /* 0x3a number of commands */
};
