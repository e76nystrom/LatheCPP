enum COMMANDS
{

// z motion commands

 ZMOVEABS,                      /* 0x00 start z movement */
 ZMOVEREL,                      /* 0x01 move z relative */
 ZJMOV,                         /* 0x02 start z jog */
 ZJSPEED,                       /* 0x03 start z jog at speed */
 ZSTOP,                         /* 0x04 stop z movement */
 ZSETLOC,                       /* 0x05  */
 ZHOMEFWD,                      /* 0x06 z home from positive side */
 ZHOMEREV,                      /* 0x07 z home from negative side */

// x motion commands

 XMOVEABS,                      /* 0x08 start x movement */
 XMOVEREL,                      /* 0x09 move x relative */
 XJMOV,                         /* 0x0a start z jog */
 XJSPEED,                       /* 0x0b start x jog at speed */
 XSTOP,                         /* 0x0c stop x movement */
 XSETLOC,                       /* 0x0d  */
 XHOMEFWD,                      /* 0x0e x home from positive side */
 XHOMEREV,                      /* 0x0f x home from negative side */

// spindle operations

 SPINDLE_START,                 /* 0x10 start spindle */
 SPINDLE_JOG,                   /* 0x11 spindle jog */
 SPINDLE_JOG_SPEED,             /* 0x12 spindle jog at speed */
 SPINDLE_STOP,                  /* 0x13 stop spindle */

// end operations

 CMD_PAUSE,                     /* 0x14 pause current operation */
 CMD_RESUME,                    /* 0x15 resume current operation */
 CMD_STOP,                      /* 0x16 stop current operation */
 CMD_MEASURE,                   /* 0x17 stop at end of current pass */

// setup operations

 CMD_CLEAR,                     /* 0x18 clear all tables */
 CMD_SETUP,                     /* 0x19 setup everything */
 CMD_SPSETUP,                   /* 0x1a setup spindle */
 CMD_SYNCSETUP,                 /* 0x1b setup z and x axis synchronization */
 CMD_ZSETUP,                    /* 0x1c setup z axis */
 CMD_ZSYNSETUP,                 /* 0x1d setup z axis sync */
 CMD_XSETUP,                    /* 0x1e setup x axis */
 CMD_XSYNSETUP,                 /* 0x1f setup z axis sync */

// state information

 READSTAT,                      /* 0x20 read status */
 READISTATE,                    /* 0x21 read states of state machines */

// load processor and xilinx parameters

 LOADVAL,                       /* 0x22 load parameters */
 LOADMULTI,                     /* 0x23 load multiple parameters */
 READVAL,                       /* 0x24 read parameters */
 LOADXREG,                      /* 0x25 load xilinx registers */
 READXREG,                      /* 0x26 read xilinx registers */

// move command operations

 CLEARQUE,                      /* 0x27 clear move que */
 QUEMOVE,                       /* 0x28 que move command */
 MOVEQUESTATUS,                 /* 0x29 read move queue status */

// location and debug info

 READALL,                       /* 0x2a read all status info */
 READDBG,                       /* 0x2b read debug message */
 CLRDBG,                        /* 0x2c clear debug message buffer */

// encoder commands

 ENCSTART,                      /* 0x2d encoder start */
 ENCSTOP,                       /* 0x2e encoder stop */
};
