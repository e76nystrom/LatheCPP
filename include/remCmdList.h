#if !defined(REM_CMD_LIST)
#define REM_CMD_LIST

enum REM_COMMANDS
{

// z motion commands

 C_Z_MOVE_ABS,                  /* 0x00 start z movement */
 C_Z_MOVE_REL,                  /* 0x01 move z relative */
 C_Z_J_MOV,                     /* 0x02 start z jog */
 C_Z_J_SPEED,                   /* 0x03 start z jog at speed */
 C_Z_STOP,                      /* 0x04 stop z movement */
 C_Z_SET_LOC,                   /* 0x05  */
 C_Z_HOME_FWD,                  /* 0x06 z home from positive side */
 C_Z_HOME_REV,                  /* 0x07 z home from negative side */

// x motion commands

 C_X_MOVE_ABS,                  /* 0x08 start x movement */
 C_X_MOVE_REL,                  /* 0x09 move x relative */
 C_X_J_MOV,                     /* 0x0a start z jog */
 C_X_J_SPEED,                   /* 0x0b start x jog at speed */
 C_X_STOP,                      /* 0x0c stop x movement */
 C_X_SET_LOC,                   /* 0x0d  */
 C_X_HOME_FWD,                  /* 0x0e x home from positive side */
 C_X_HOME_REV,                  /* 0x0f x home from negative side */

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
 C_CMD_SP_SETUP,                /* 0x1c setup spindle */
 C_CMD_SYNC_SETUP,              /* 0x1d setup z and x axis synchronization */
 C_CMD_Z_SETUP,                 /* 0x1e setup z axis */
 C_CMD_Z_SYN_SETUP,             /* 0x1f setup z axis sync */
 C_CMD_Z_SET_LOC,               /* 0x20 setup z location */
 C_CMD_X_SETUP,                 /* 0x21 setup x axis */
 C_CMD_X_SYN_SETUP,             /* 0x22 setup x axis sync */
 C_CMD_X_SET_LOC,               /* 0x23 setup x location */

// state information

 C_READ_STAT,                   /* 0x24 read status */
 C_READ_I_STATE,                /* 0x25 read states of state machines */

// load processor and xilinx parameters

 C_LOAD_VAL,                    /* 0x26 load parameters */
 C_LOAD_MULTI,                  /* 0x27 load multiple parameters */
 C_READ_VAL,                    /* 0x28 read parameters */
 C_LOAD_X_REG,                  /* 0x29 load xilinx registers */
 C_READ_X_REG,                  /* 0x2a read xilinx registers */

// move command operations

 C_CLEAR_QUE,                   /* 0x2b clear move que */
 C_QUE_MOVE,                    /* 0x2c que move command */
 C_MOVE_MULTI,                  /* 0x2d que move command */
 C_MOVE_QUE_STATUS,             /* 0x2e read move queue status */

// location and debug info

 C_READ_ALL,                    /* 0x2f read all status info */
 C_READ_DBG,                    /* 0x30 read debug message */
 C_CLR_DBG,                     /* 0x31 clear debug message buffer */

// encoder commands

 C_ENC_START,                   /* 0x32 encoder start */
 C_ENC_STOP,                    /* 0x33 encoder stop */

//  mega commands 

 C_SET_MEGA_VAL,                /* 0x34 set mega value */
 C_READ_MEGA_VAL,               /* 0x35 get mega value */
 C_SEND_DONE,                   /* 0x36 send commands done */
};

#endif  /* REM_CMD_LIST */
