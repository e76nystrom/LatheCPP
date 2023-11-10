enum REM_COMMANDS
{

// z motion commands

 C_ZMOVEABS,                    /* 0x00 start z movement */
 C_ZMOVEREL,                    /* 0x01 move z relative */
 C_ZJMOV,                       /* 0x02 start z jog */
 C_ZJSPEED,                     /* 0x03 start z jog at speed */
 C_ZSTOP,                       /* 0x04 stop z movement */
 C_ZSETLOC,                     /* 0x05  */
 C_ZHOMEFWD,                    /* 0x06 z home from positive side */
 C_ZHOMEREV,                    /* 0x07 z home from negative side */

// x motion commands

 C_XMOVEABS,                    /* 0x08 start x movement */
 C_XMOVEREL,                    /* 0x09 move x relative */
 C_XJMOV,                       /* 0x0a start z jog */
 C_XJSPEED,                     /* 0x0b start x jog at speed */
 C_XSTOP,                       /* 0x0c stop x movement */
 C_XSETLOC,                     /* 0x0d  */
 C_XHOMEFWD,                    /* 0x0e x home from positive side */
 C_XHOMEREV,                    /* 0x0f x home from negative side */

// spindle operations

 C_SPINDLE_START,               /* 0x10 start spindle */
 C_SPINDLE_STOP,                /* 0x11 stop spindle */
 C_SPINDLE_UPDATE,              /* 0x12 update spindle speed */
 C_SPINDLE_JOG,                 /* 0x13 spindle jog */
 C_SPINDLE_JOG_SPEED,           /* 0x14 spindle jog at speed */

// end operations

 C_CMD_PAUSE,                   /* 0x15 pause current operation */
 C_CMD_RESUME,                  /* 0x16 resume current operation */
 C_CMD_STOP,                    /* 0x17 stop current operation */
 C_CMD_DONE,                    /* 0x18 done current operation */
 C_CMD_MEASURE,                 /* 0x19 stop at end of current pass */

// setup operations

 C_CMD_CLEAR,                   /* 0x1a clear all tables */
 C_CMD_SETUP,                   /* 0x1b setup everything */
 C_CMD_SPSETUP,                 /* 0x1c setup spindle */
 C_CMD_SYNCSETUP,               /* 0x1d setup z and x axis synchronization */
 C_CMD_ZSETUP,                  /* 0x1e setup z axis */
 C_CMD_ZSYNSETUP,               /* 0x1f setup z axis sync */
 C_CMD_ZSETLOC,                 /* 0x20 setup z location */
 C_CMD_XSETUP,                  /* 0x21 setup x axis */
 C_CMD_XSYNSETUP,               /* 0x22 setup x axis sync */
 C_CMD_XSETLOC,                 /* 0x23 setup x location */

// state information

 C_READSTAT,                    /* 0x24 read status */
 C_READISTATE,                  /* 0x25 read states of state machines */

// load processor and xilinx parameters

 C_LOADVAL,                     /* 0x26 load parameters */
 C_LOADMULTI,                   /* 0x27 load multiple parameters */
 C_READVAL,                     /* 0x28 read parameters */
 C_LOADXREG,                    /* 0x29 load xilinx registers */
 C_READXREG,                    /* 0x2a read xilinx registers */

// move command operations

 C_CLEARQUE,                    /* 0x2b clear move que */
 C_QUEMOVE,                     /* 0x2c que move command */
 C_MOVEMULTI,                   /* 0x2d que move command */
 C_MOVEQUESTATUS,               /* 0x2e read move queue status */

// location and debug info

 C_READALL,                     /* 0x2f read all status info */
 C_READDBG,                     /* 0x30 read debug message */
 C_CLRDBG,                      /* 0x31 clear debug message buffer */

// encoder commands

 C_ENCSTART,                    /* 0x32 encoder start */
 C_ENCSTOP,                     /* 0x33 encoder stop */

//  mega commands 

 C_SET_MEGA_VAL,                /* 0x34 set mega value */
 C_READ_MEGA_VAL,               /* 0x35 get mega value */
};
