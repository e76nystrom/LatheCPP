
// z control states

enum Z_STATES
{
 ZIDLE,                         /*  0 x00 idle */
 ZWAITBKLS,                     /*  1 x01 wait for backlash move complete */
 ZSTARTMOVE,                    /*  2 x02 start z move */
 ZWAITMOVE,                     /*  3 x03 wait for move complete */
 ZDONE,                         /*  4 x04 clean up state */
};

#ifdef ENUM_Z_STATES

const char *zStatesList[] = 
{
 "ZIDLE",                       /*  0 x00 idle */
 "ZWAITBKLS",                   /*  1 x01 wait for backlash move complete */
 "ZSTARTMOVE",                  /*  2 x02 start z move */
 "ZWAITMOVE",                   /*  3 x03 wait for move complete */
 "ZDONE",                       /*  4 x04 clean up state */
};

#endif

// x control states

enum X_STATES
{
 XIDLE,                         /*  0 x00 idle */
 XWAITBKLS,                     /*  1 x01 wait for backlash move complete */
 XSTARTMOVE,                    /*  2 x02 start x move */
 XWAITMOVE,                     /*  3 x03 wait for move complete */
 XDELAY,                        /*  4 x04 wait for position to settle */
 XDONE,                         /*  5 x05 clean up state */
};

#ifdef ENUM_X_STATES

const char *xStatesList[] = 
{
 "XIDLE",                       /*  0 x00 idle */
 "XWAITBKLS",                   /*  1 x01 wait for backlash move complete */
 "XSTARTMOVE",                  /*  2 x02 start x move */
 "XWAITMOVE",                   /*  3 x03 wait for move complete */
 "XDELAY",                      /*  4 x04 wait for position to settle */
 "XDONE",                       /*  5 x05 clean up state */
};

#endif

// move control states

enum M_STATES
{
 M_IDLE,                        /*  0 x00 idle state */
 M_WAIT_Z,                      /*  1 x01 wait for z to complete */
 M_WAIT_X,                      /*  2 x02 wait for x to complete */
 M_WAIT_SPINDLE,                /*  3 x03 wait for spindle start */
 M_WAIT_SYNC_READY,             /*  4 x04 wait for sync */
 M_WAIT_SYNC_DONE,              /*  5 x05 wait for sync done */
 M_WAIT_MEASURE_DONE,           /*  6 x06 wait for measurment done */
 M_START_SYNC,                  /*  7 x07 start sync */
 M_WAIT_PROBE,                  /*  8 x08 wait for probe to complete */
 M_WAIT_MEASURE,                /*  9 x09 wait for measurement to complete */
 M_WAIT_SAFE_X,                 /* 10 x0a wait for move to safe x to complete */
 M_WAIT_SAFE_Z,                 /* 11 x0b wait for move to safe z to complete */
};

#ifdef ENUM_M_STATES

const char *mStatesList[] = 
{
 "M_IDLE",                      /*  0 x00 idle state */
 "M_WAIT_Z",                    /*  1 x01 wait for z to complete */
 "M_WAIT_X",                    /*  2 x02 wait for x to complete */
 "M_WAIT_SPINDLE",              /*  3 x03 wait for spindle start */
 "M_WAIT_SYNC_READY",           /*  4 x04 wait for sync */
 "M_WAIT_SYNC_DONE",            /*  5 x05 wait for sync done */
 "M_WAIT_MEASURE_DONE",         /*  6 x06 wait for measurment done */
 "M_START_SYNC",                /*  7 x07 start sync */
 "M_WAIT_PROBE",                /*  8 x08 wait for probe to complete */
 "M_WAIT_MEASURE",              /*  9 x09 wait for measurement to complete */
 "M_WAIT_SAFE_X",               /* 10 x0a wait for move to safe x to complete */
 "M_WAIT_SAFE_Z",               /* 11 x0b wait for move to safe z to complete */
};

#endif

// move control commands

enum M_COMMANDS
{
 MOVE_Z,                        /*  0 x00 move z */
 MOVE_X,                        /*  1 x01 move x */
 SAVE_Z,                        /*  2 x02 save z */
 SAVE_X,                        /*  3 x03 save x */
 SAVE_Z_OFFSET,                 /*  4 x04 save z offset */
 SAVE_X_OFFSET,                 /*  5 x05 save x offset */
 SAVE_TAPER,                    /*  6 x06 save taper */
 MOVE_ZX,                       /*  7 x07 move x in sync with z */
 MOVE_XZ,                       /*  8 x08 move z in sync with x */
 TAPER_ZX,                      /*  9 x09 taper x */
 TAPER_XZ,                      /* 10 x0a taper z */
 START_SPINDLE,                 /* 11 x0b spindle start */
 STOP_SPINDLE,                  /* 12 x0c spindle stop */
 Z_SYN_SETUP,                   /* 13 x0d z sync setup */
 X_SYN_SETUP,                   /* 14 x0e x sync setup */
 PASS_NUM,                      /* 15 x0f set pass number */
 QUE_PAUSE,                     /* 16 x10 pause queue */
 MOVE_Z_OFFSET,                 /* 17 x11 move z offset */
 SAVE_FEED_TYPE,                /* 18 x12 save feed type */
 Z_FEED_SETUP,                  /* 19 x13 setup z feed */
 X_FEED_SETUP,                  /* 20 x14 setup x feed */
 SAVE_FLAGS,                    /* 21 x15 save thread flags */
 PROBE_Z,                       /* 22 x16 probe in z direction */
 PROBE_X,                       /* 23 x17 probe in x direction */
 SAVE_Z_DRO,                    /* 24 x18 save z dro reading */
 SAVE_X_DRO,                    /* 25 x19 save x dro reading */
 OP_DONE,                       /* 26 x1a operation done */
};

#ifdef ENUM_M_COMMANDS

const char *mCommandsList[] = 
{
 "MOVE_Z",                      /*  0 x00 move z */
 "MOVE_X",                      /*  1 x01 move x */
 "SAVE_Z",                      /*  2 x02 save z */
 "SAVE_X",                      /*  3 x03 save x */
 "SAVE_Z_OFFSET",               /*  4 x04 save z offset */
 "SAVE_X_OFFSET",               /*  5 x05 save x offset */
 "SAVE_TAPER",                  /*  6 x06 save taper */
 "MOVE_ZX",                     /*  7 x07 move x in sync with z */
 "MOVE_XZ",                     /*  8 x08 move z in sync with x */
 "TAPER_ZX",                    /*  9 x09 taper x */
 "TAPER_XZ",                    /* 10 x0a taper z */
 "START_SPINDLE",               /* 11 x0b spindle start */
 "STOP_SPINDLE",                /* 12 x0c spindle stop */
 "Z_SYN_SETUP",                 /* 13 x0d z sync setup */
 "X_SYN_SETUP",                 /* 14 x0e x sync setup */
 "PASS_NUM",                    /* 15 x0f set pass number */
 "QUE_PAUSE",                   /* 16 x10 pause queue */
 "MOVE_Z_OFFSET",               /* 17 x11 move z offset */
 "SAVE_FEED_TYPE",              /* 18 x12 save feed type */
 "Z_FEED_SETUP",                /* 19 x13 setup z feed */
 "X_FEED_SETUP",                /* 20 x14 setup x feed */
 "SAVE_FLAGS",                  /* 21 x15 save thread flags */
 "PROBE_Z",                     /* 22 x16 probe in z direction */
 "PROBE_X",                     /* 23 x17 probe in x direction */
 "SAVE_Z_DRO",                  /* 24 x18 save z dro reading */
 "SAVE_X_DRO",                  /* 25 x19 save x dro reading */
 "OP_DONE",                     /* 26 x1a operation done */
};

#endif

// move control operation

enum OPERATIONS
{
 OP_TURN,                       /*  0 x00 turn */
 OP_FACE,                       /*  1 x01 face */
 OP_CUTOFF,                     /*  2 x02 cutoff */
 OP_TAPER,                      /*  3 x03 taper */
 OP_THREAD,                     /*  4 x04 thread */
};

#ifdef ENUM_OPERATIONS

const char *operationsList[] = 
{
 "OP_TURN",                     /*  0 x00 turn */
 "OP_FACE",                     /*  1 x01 face */
 "OP_CUTOFF",                   /*  2 x02 cutoff */
 "OP_TAPER",                    /*  3 x03 taper */
 "OP_THREAD",                   /*  4 x04 thread */
};

#endif

// home control states

enum H_STATES
{
 H_IDLE,                        /*  0 x00 idle state */
 H_CHECK_ONHOME,                /*  1 x01  */
 H_WAIT_FINDHOME,               /*  2 x02  */
 H_BACKOFF_HOME,                /*  3 x03  */
 H_WAIT_BACKOFF,                /*  4 x04  */
 H_WAIT_SLOWFIND,               /*  5 x05  */
};

#ifdef ENUM_H_STATES

const char *hStatesList[] = 
{
 "H_IDLE",                      /*  0 x00 idle state */
 "H_CHECK_ONHOME",              /*  1 x01  */
 "H_WAIT_FINDHOME",             /*  2 x02  */
 "H_BACKOFF_HOME",              /*  3 x03  */
 "H_WAIT_BACKOFF",              /*  4 x04  */
 "H_WAIT_SLOWFIND",             /*  5 x05  */
};

#endif

// debug message types

enum D_MESSAGE
{
 D_PASS,                        /*  0 x00 pass done */
 D_DONE,                        /*  1 x01 all operations done */
 D_TEST,                        /*  2 x02 test message */
 D_XMOV,                        /*  3 x03 x move location */
 D_XLOC,                        /*  4 x04 x location */
 D_XDST,                        /*  5 x05 x distance */
 D_XSTP,                        /*  6 x06 x steps */
 D_XST,                         /*  7 x07 x state */
 D_XBSTP,                       /*  8 x08 x backlash steps */
 D_XDRO,                        /*  9 x09 x dro location */
 D_XPDRO,                       /* 10 x0a x pass dro location */
 D_XEXP,                        /* 11 x0b x expected location */
 D_XWT,                         /* 12 x0c x wait */
 D_XDN,                         /* 13 x0d x done */
 D_XEST,                        /* 14 x0e x spindle encoder start count */
 D_XEDN,                        /* 15 x0f x spindle encoder done count */
 D_XX,                          /* 16 x10 x  */
 D_XY,                          /* 17 x11 x  */
 D_ZMOV,                        /* 18 x12 z move location */
 D_ZLOC,                        /* 19 x13 z location */
 D_ZDST,                        /* 20 x14 z distance */
 D_ZSTP,                        /* 21 x15 z steps */
 D_ZST,                         /* 22 x16 z state */
 D_ZBSTP,                       /* 23 x17 z backlash steps */
 D_ZDRO,                        /* 24 x18 z dro location */
 D_ZPDRO,                       /* 25 x19 z pass dro location */
 D_ZEXP,                        /* 26 x1a z expected location */
 D_ZWT,                         /* 27 x1b z wait */
 D_ZDN,                         /* 28 x1c z done */
 D_ZEST,                        /* 29 x1d z spindle encoder start count */
 D_ZEDN,                        /* 30 x1e Z spindle encoder done count */
 D_ZX,                          /* 31 x1f z  */
 D_ZY,                          /* 32 x20 z  */
 D_HST,                         /* 33 x21 home state */
 D_MSTA,                        /* 34 x22 move state */
 D_MCMD,                        /* 35 x23 move command */
};

#ifdef ENUM_D_MESSAGE

const char *dMessageList[] = 
{
 "D_PASS",                      /*  0 x00 pass done */
 "D_DONE",                      /*  1 x01 all operations done */
 "D_TEST",                      /*  2 x02 test message */
 "D_XMOV",                      /*  3 x03 x move location */
 "D_XLOC",                      /*  4 x04 x location */
 "D_XDST",                      /*  5 x05 x distance */
 "D_XSTP",                      /*  6 x06 x steps */
 "D_XST",                       /*  7 x07 x state */
 "D_XBSTP",                     /*  8 x08 x backlash steps */
 "D_XDRO",                      /*  9 x09 x dro location */
 "D_XPDRO",                     /* 10 x0a x pass dro location */
 "D_XEXP",                      /* 11 x0b x expected location */
 "D_XWT",                       /* 12 x0c x wait */
 "D_XDN",                       /* 13 x0d x done */
 "D_XEST",                      /* 14 x0e x spindle encoder start count */
 "D_XEDN",                      /* 15 x0f x spindle encoder done count */
 "D_XX",                        /* 16 x10 x  */
 "D_XY",                        /* 17 x11 x  */
 "D_ZMOV",                      /* 18 x12 z move location */
 "D_ZLOC",                      /* 19 x13 z location */
 "D_ZDST",                      /* 20 x14 z distance */
 "D_ZSTP",                      /* 21 x15 z steps */
 "D_ZST",                       /* 22 x16 z state */
 "D_ZBSTP",                     /* 23 x17 z backlash steps */
 "D_ZDRO",                      /* 24 x18 z dro location */
 "D_ZPDRO",                     /* 25 x19 z pass dro location */
 "D_ZEXP",                      /* 26 x1a z expected location */
 "D_ZWT",                       /* 27 x1b z wait */
 "D_ZDN",                       /* 28 x1c z done */
 "D_ZEST",                      /* 29 x1d z spindle encoder start count */
 "D_ZEDN",                      /* 30 x1e Z spindle encoder done count */
 "D_ZX",                        /* 31 x1f z  */
 "D_ZY",                        /* 32 x20 z  */
 "D_HST",                       /* 33 x21 home state */
 "D_MSTA",                      /* 34 x22 move state */
 "D_MCMD",                      /* 35 x23 move command */
};

#endif

// pylathe update events

enum EV_EVENTS
{
 EV_ZLOC,                       /*  0 x00 z location */
 EV_XLOC,                       /*  1 x01 x location */
 EV_RPM,                        /*  2 x02 rpm */
 EV_READ_ALL,                   /*  3 x03 all values */
 EV_ERROR,                      /*  4 x04 event error */
 EV_MAX,                        /*  5 x05 maximum event */
};

#ifdef ENUM_EV_EVENTS

const char *evEventsList[] = 
{
 "EV_ZLOC",                     /*  0 x00 z location */
 "EV_XLOC",                     /*  1 x01 x location */
 "EV_RPM",                      /*  2 x02 rpm */
 "EV_READ_ALL",                 /*  3 x03 all values */
 "EV_ERROR",                    /*  4 x04 event error */
 "EV_MAX",                      /*  5 x05 maximum event */
};

#endif

// turning sync selector

enum SEL_TURN
{
 SEL_TU_SPEED,                  /*  0 x00 Motor Speed */
 SEL_TU_STEP,                   /*  1 x01 Stepper */
 SEL_TU_ENC,                    /*  2 x02 Encoder */
 SEL_TU_ISYN,                   /*  3 x03 Int Syn */
 SEL_TU_ESYN,                   /*  4 x04 Ext Syn */
};

#ifdef ENUM_SEL_TURN

const char *selTurnList[] = 
{
 "SEL_TU_SPEED",                /*  0 x00 Motor Speed */
 "SEL_TU_STEP",                 /*  1 x01 Stepper */
 "SEL_TU_ENC",                  /*  2 x02 Encoder */
 "SEL_TU_ISYN",                 /*  3 x03 Int Syn */
 "SEL_TU_ESYN",                 /*  4 x04 Ext Syn */
};

#endif

// threading sync selector

enum SEL_THREAD
{
 SEL_TH_NO_ENC,                 /*  0 x00 No Encoder */
 SEL_TH_STEP,                   /*  1 x01 Stepper */
 SEL_TH_ENC,                    /*  2 x02 Encoder Direct */
 SEL_TH_ISYN_RENC,              /*  3 x03 Int Syn, Runout Enc */
 SEL_TH_ESYN_RENC,              /*  4 x04 Ext Syn, Runout Enc */
 SEL_TH_ESYN_RSYN,              /*  5 x05 Ext Syn, Runout Syn */
};

#ifdef ENUM_SEL_THREAD

const char *selThreadList[] = 
{
 "SEL_TH_NO_ENC",               /*  0 x00 No Encoder */
 "SEL_TH_STEP",                 /*  1 x01 Stepper */
 "SEL_TH_ENC",                  /*  2 x02 Encoder Direct */
 "SEL_TH_ISYN_RENC",            /*  3 x03 Int Syn, Runout Enc */
 "SEL_TH_ESYN_RENC",            /*  4 x04 Ext Syn, Runout Enc */
 "SEL_TH_ESYN_RSYN",            /*  5 x05 Ext Syn, Runout Syn */
};

#endif
