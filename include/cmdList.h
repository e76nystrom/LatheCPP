enum COMMANDS
{

// z motion commands

 ZMOVEABS,                      /* 0x00 start z movement */
 ZMOVEREL,                      /* 0x01 move z relative */
 ZJMOV,                         /* 0x02 start z jog */
 ZJSPEED,                       /* 0x03 start z jog at speed */
 ZSTOP,                         /* 0x04 stop z movement */
 ZSETLOC,                       /* 0x05  */

// x motion commands

 XMOVEABS,                      /* 0x06 start x movement */
 XMOVEREL,                      /* 0x07 move x relative */
 XJMOV,                         /* 0x08 start z jog */
 XJSPEED,                       /* 0x09 start x jog at speed */
 XSTOP,                         /* 0x0a stop x movement */
 XSETLOC,                       /* 0x0b  */
 XHOMEAXIS,                     /* 0x0c x home axis */

// spindle operations

 SPINDLE_START,                 /* 0x0d start spindle */
 SPINDLE_JOG,                   /* 0x0e spindle jog */
 SPINDLE_JOG_SPEED,             /* 0x0f spindle jog at speed */
 SPINDLE_STOP,                  /* 0x10 stop spindle */

// end operations

 CMD_PAUSE,                     /* 0x11 pause current operation */
 CMD_RESUME,                    /* 0x12 resume current operation */
 CMD_STOP,                      /* 0x13 stop current operation */
 CMD_MEASURE,                   /* 0x14 stop at end of current pass */

// setup operations

 CMD_CLEAR,                     /* 0x15 clear all tables */
 CMD_SETUP,                     /* 0x16 setup everything */
 CMD_SPSETUP,                   /* 0x17 setup spindle */
 CMD_SYNCSETUP,                 /* 0x18 setup z and x axis synchronization */
 CMD_ZSETUP,                    /* 0x19 setup z axis */
 CMD_ZSYNSETUP,                 /* 0x1a setup z axis sync */
 CMD_XSETUP,                    /* 0x1b setup x axis */
 CMD_XSYNSETUP,                 /* 0x1c setup z axis sync */

// state information

 READSTAT,                      /* 0x1d read status */
 READISTATE,                    /* 0x1e read states of state machines */

// load processor and xilinx parameters

 LOADVAL,                       /* 0x1f load parameters */
 LOADMULTI,                     /* 0x20 load multiple parameters */
 READVAL,                       /* 0x21 read parameters */
 LOADXREG,                      /* 0x22 load xilinx registers */
 READXREG,                      /* 0x23 read xilinx registers */

// move command operations

 CLEARQUE,                      /* 0x24 clear move que */
 QUEMOVE,                       /* 0x25 que move command */
 MOVEQUESTATUS,                 /* 0x26 read move queue status */

// location and debug info

 READALL,                       /* 0x27 read all status info */
 READDBG,                       /* 0x28 read debug message */
 CLRDBG,                        /* 0x29 clear debug message buffer */

// encoder commands

 ENCSTART,                      /* 0x2a encoder start */
 ENCSTOP,                       /* 0x2b encoder stop */
};
