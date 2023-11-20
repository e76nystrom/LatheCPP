#if !defined(CTL_STATES_INC)
#define CTL_STATES_INC

// axis control states

enum AXIS_STATES
{
 AXIS_IDLE = 0,                 /*  0 x00 idle */
 AXIS_WAIT_BACKLASH = 1,        /*  1 x01 wait for backlash move complete */
 AXIS_START_MOVE = 2,           /*  2 x02 start axis move */
 AXIS_WAIT_MOVE = 3,            /*  3 x03 wait for move complete */
 AXIS_DELAY = 4,                /*  4 x04 wait for position to settle */
 AXIS_DONE = 5,                 /*  5 x05 clean up state */
 AXIS_STATES = 6,               /*  6 x06 number of states */
};

#ifdef ENUM_AXIS_STATES

const char *axisStatesList[] = 
{
 "AXIS_IDLE",                   /*  0 x00 idle */
 "AXIS_WAIT_BACKLASH",          /*  1 x01 wait for backlash move complete */
 "AXIS_START_MOVE",             /*  2 x02 start axis move */
 "AXIS_WAIT_MOVE",              /*  3 x03 wait for move complete */
 "AXIS_DELAY",                  /*  4 x04 wait for position to settle */
 "AXIS_DONE",                   /*  5 x05 clean up state */
 "AXIS_STATES",                 /*  6 x06 number of states */
};

#else

extern const char *axisStatesList[];

#endif

// move control states

enum M_STATES
{
 M_IDLE = 0,                    /*  0 x00 idle state */
 M_WAIT_Z = 1,                  /*  1 x01 wait for z to complete */
 M_WAIT_X = 2,                  /*  2 x02 wait for x to complete */
 M_WAIT_SPINDLE = 3,            /*  3 x03 wait for spindle start */
 M_WAIT_SYNC_PARMS = 4,         /*  4 x04 wait for sync parameters */
 M_WAIT_SYNC_CMD = 5,           /*  5 x05 wait for sync command */
 M_START_SYNC = 6,              /*  6 x06 start sync */
 M_WAIT_SYNC_READY = 7,         /*  7 x07 wait for sync */
 M_WAIT_SYNC_DONE = 8,          /*  8 x08 wait for sync done */
 M_WAIT_MEASURE_DONE = 9,       /*  9 x09 wait for measurement done */
 M_WAIT_PROBE = 10,             /* 10 x0a wait for probe to complete */
 M_WAIT_MEASURE = 11,           /* 11 x0b wait for measurement to complete */
 M_WAIT_SAFE_X = 12,            /* 12 x0c wait for move to safe x to complete */
 M_WAIT_SAFE_Z = 13,            /* 13 x0d wait for move to safe z to complete */
 M_WAIT_ARC = 14,               /* 14 x0e wait for arc move to complete */
};

#ifdef ENUM_M_STATES

const char *mStatesList[] = 
{
 "M_IDLE",                      /*  0 x00 idle state */
 "M_WAIT_Z",                    /*  1 x01 wait for z to complete */
 "M_WAIT_X",                    /*  2 x02 wait for x to complete */
 "M_WAIT_SPINDLE",              /*  3 x03 wait for spindle start */
 "M_WAIT_SYNC_PARMS",           /*  4 x04 wait for sync parameters */
 "M_WAIT_SYNC_CMD",             /*  5 x05 wait for sync command */
 "M_START_SYNC",                /*  6 x06 start sync */
 "M_WAIT_SYNC_READY",           /*  7 x07 wait for sync */
 "M_WAIT_SYNC_DONE",            /*  8 x08 wait for sync done */
 "M_WAIT_MEASURE_DONE",         /*  9 x09 wait for measurement done */
 "M_WAIT_PROBE",                /* 10 x0a wait for probe to complete */
 "M_WAIT_MEASURE",              /* 11 x0b wait for measurement to complete */
 "M_WAIT_SAFE_X",               /* 12 x0c wait for move to safe x to complete */
 "M_WAIT_SAFE_Z",               /* 13 x0d wait for move to safe z to complete */
 "M_WAIT_ARC",                  /* 14 x0e wait for arc move to complete */
};

#else

extern const char *mStatesList[];

#endif

// move control commands

enum M_COMMANDS
{
 Q_MOVE_Z = 0,                  /*  0 x00 move z */
 Q_MOVE_X = 1,                  /*  1 x01 move x */
 Q_SAVE_Z = 2,                  /*  2 x02 save z */
 Q_SAVE_X = 3,                  /*  3 x03 save x */
 Q_SAVE_Z_OFFSET = 4,           /*  4 x04 save z offset */
 Q_SAVE_X_OFFSET = 5,           /*  5 x05 save x offset */
 Q_SAVE_TAPER = 6,              /*  6 x06 save taper */
 Q_MOVE_Z_X = 7,                /*  7 x07 move x in sync with z */
 Q_MOVE_X_Z = 8,                /*  8 x08 move z in sync with x */
 Q_TAPER_Z_X = 9,               /*  9 x09 taper x */
 Q_TAPER_X_Z = 10,              /* 10 x0a taper z */
 Q_START_SPINDLE = 11,          /* 11 x0b spindle start */
 Q_STOP_SPINDLE = 12,           /* 12 x0c spindle stop */
 Q_Z_SYN_SETUP = 13,            /* 13 x0d z sync setup */
 Q_X_SYN_SETUP = 14,            /* 14 x0e x sync setup */
 Q_SEND_SYNC_PARMS = 15,        /* 15 x0f send sync parameters */
 Q_SYNC_COMMAND = 16,           /* 16 x10 send sync command */
 Q_PASS_NUM = 17,               /* 17 x11 set pass number */
 Q_QUE_PAUSE = 18,              /* 18 x12 pause queue */
 Q_MOVE_Z_OFFSET = 19,          /* 19 x13 move z offset */
 Q_SAVE_FEED_TYPE = 20,         /* 20 x14 save feed type */
 Q_Z_FEED_SETUP = 21,           /* 21 x15 setup z feed */
 Q_X_FEED_SETUP = 22,           /* 22 x16 setup x feed */
 Q_SAVE_FLAGS = 23,             /* 23 x17 save thread flags */
 Q_PROBE_Z = 24,                /* 24 x18 probe in z direction */
 Q_PROBE_X = 25,                /* 25 x19 probe in x direction */
 Q_SAVE_Z_DRO = 26,             /* 26 x1a save z dro reading */
 Q_SAVE_X_DRO = 27,             /* 27 x1b save x dro reading */
 Q_QUE_PARM = 28,               /* 28 x1c save parameter in queue */
 Q_MOVE_ARC = 29,               /* 29 x1d move in an arc */
 Q_OP_DONE = 30,                /* 30 x1e operation done */
};

#ifdef ENUM_M_COMMANDS

const char *mCommandsList[] = 
{
 "Q_MOVE_Z",                    /*  0 x00 move z */
 "Q_MOVE_X",                    /*  1 x01 move x */
 "Q_SAVE_Z",                    /*  2 x02 save z */
 "Q_SAVE_X",                    /*  3 x03 save x */
 "Q_SAVE_Z_OFFSET",             /*  4 x04 save z offset */
 "Q_SAVE_X_OFFSET",             /*  5 x05 save x offset */
 "Q_SAVE_TAPER",                /*  6 x06 save taper */
 "Q_MOVE_Z_X",                  /*  7 x07 move x in sync with z */
 "Q_MOVE_X_Z",                  /*  8 x08 move z in sync with x */
 "Q_TAPER_Z_X",                 /*  9 x09 taper x */
 "Q_TAPER_X_Z",                 /* 10 x0a taper z */
 "Q_START_SPINDLE",             /* 11 x0b spindle start */
 "Q_STOP_SPINDLE",              /* 12 x0c spindle stop */
 "Q_Z_SYN_SETUP",               /* 13 x0d z sync setup */
 "Q_X_SYN_SETUP",               /* 14 x0e x sync setup */
 "Q_SEND_SYNC_PARMS",           /* 15 x0f send sync parameters */
 "Q_SYNC_COMMAND",              /* 16 x10 send sync command */
 "Q_PASS_NUM",                  /* 17 x11 set pass number */
 "Q_QUE_PAUSE",                 /* 18 x12 pause queue */
 "Q_MOVE_Z_OFFSET",             /* 19 x13 move z offset */
 "Q_SAVE_FEED_TYPE",            /* 20 x14 save feed type */
 "Q_Z_FEED_SETUP",              /* 21 x15 setup z feed */
 "Q_X_FEED_SETUP",              /* 22 x16 setup x feed */
 "Q_SAVE_FLAGS",                /* 23 x17 save thread flags */
 "Q_PROBE_Z",                   /* 24 x18 probe in z direction */
 "Q_PROBE_X",                   /* 25 x19 probe in x direction */
 "Q_SAVE_Z_DRO",                /* 26 x1a save z dro reading */
 "Q_SAVE_X_DRO",                /* 27 x1b save x dro reading */
 "Q_QUE_PARM",                  /* 28 x1c save parameter in queue */
 "Q_MOVE_ARC",                  /* 29 x1d move in an arc */
 "Q_OP_DONE",                   /* 30 x1e operation done */
};

#else

extern const char *mCommandsList[];

#endif

// move control operation

enum OPERATIONS
{
 OP_TURN = 0,                   /*  0 x00 turn */
 OP_FACE = 1,                   /*  1 x01 face */
 OP_CUTOFF = 2,                 /*  2 x02 cutoff */
 OP_TAPER = 3,                  /*  3 x03 taper */
 OP_THREAD = 4,                 /*  4 x04 thread */
 OP_ARC = 5,                    /*  5 x05 arc */
};

#ifdef ENUM_OPERATIONS

const char *operationsList[] = 
{
 "OP_TURN",                     /*  0 x00 turn */
 "OP_FACE",                     /*  1 x01 face */
 "OP_CUTOFF",                   /*  2 x02 cutoff */
 "OP_TAPER",                    /*  3 x03 taper */
 "OP_THREAD",                   /*  4 x04 thread */
 "OP_ARC",                      /*  5 x05 arc */
};

#else

extern const char *operationsList[];

#endif

// home control states

enum H_STATES
{
 H_IDLE = 0,                    /*  0 x00 idle state */
 H_HOME = 1,                    /*  1 x01 found home switch */
 H_OFF_HOME = 2,                /*  2 x02 off home switch */
 H_BACKOFF = 3,                 /*  3 x03 backoff dist from switch */
 H_SLOW = 4,                    /*  4 x04 found home slowly */
};

#ifdef ENUM_H_STATES

const char *hStatesList[] = 
{
 "H_IDLE",                      /*  0 x00 idle state */
 "H_HOME",                      /*  1 x01 found home switch */
 "H_OFF_HOME",                  /*  2 x02 off home switch */
 "H_BACKOFF",                   /*  3 x03 backoff dist from switch */
 "H_SLOW",                      /*  4 x04 found home slowly */
};

#else

extern const char *hStatesList[];

#endif

// debug axis message types

enum D_AXIS_MESSAGE
{
 D_BASE = 0,                    /*  0 x00 axis base */
 D_MVCM = 1,                    /*  1 x01 move command */
 D_ACTL = 2,                    /*  2 x02 axisctl */
 D_MOV = 3,                     /*  3 x03 move location */
 D_CUR = 4,                     /*  4 x04 current location */
 D_LOC = 5,                     /*  5 x05 end location */
 D_DST = 6,                     /*  6 x06 distance */
 D_STP = 7,                     /*  7 x07 steps */
 D_ST = 8,                      /*  8 x08 state */
 D_BSTP = 9,                    /*  9 x09 backlash steps */
 D_DRO = 10,                    /* 10 x0a dro location */
 D_PDRO = 11,                   /* 11 x0b pass dro location */
 D_EXP = 12,                    /* 12 x0c expected location */
 D_ERR = 13,                    /* 13 x0d error with respect to dro */
 D_WT = 14,                     /* 14 x0e wait */
 D_DN = 15,                     /* 15 x0f done */
 D_EST = 16,                    /* 16 x10 spindle encoder start count */
 D_EDN = 17,                    /* 17 x11 spindle encoder done count */
 D_X = 18,                      /* 18 x12  */
 D_Y = 19,                      /* 19 x13  */
 D_IDXD = 20,                   /* 20 x14 dro at index pulse */
 D_IDXP = 21,                   /* 21 x15 position at index pulse */
 D_AMAX = 22,                   /* 22 x16 axis maximum */
};

#ifdef ENUM_D_AXIS_MESSAGE

const char *DAxisMessageList[] = 
{
 "D_BASE",                      /*  0 x00 axis base */
 "D_MVCM",                      /*  1 x01 move command */
 "D_ACTL",                      /*  2 x02 axisctl */
 "D_MOV",                       /*  3 x03 move location */
 "D_CUR",                       /*  4 x04 current location */
 "D_LOC",                       /*  5 x05 end location */
 "D_DST",                       /*  6 x06 distance */
 "D_STP",                       /*  7 x07 steps */
 "D_ST",                        /*  8 x08 state */
 "D_BSTP",                      /*  9 x09 backlash steps */
 "D_DRO",                       /* 10 x0a dro location */
 "D_PDRO",                      /* 11 x0b pass dro location */
 "D_EXP",                       /* 12 x0c expected location */
 "D_ERR",                       /* 13 x0d error with respect to dro */
 "D_WT",                        /* 14 x0e wait */
 "D_DN",                        /* 15 x0f done */
 "D_EST",                       /* 16 x10 spindle encoder start count */
 "D_EDN",                       /* 17 x11 spindle encoder done count */
 "D_X",                         /* 18 x12  */
 "D_Y",                         /* 19 x13  */
 "D_IDXD",                      /* 20 x14 dro at index pulse */
 "D_IDXP",                      /* 21 x15 position at index pulse */
 "D_AMAX",                      /* 22 x16 axis maximum */
};

#else

extern const char *DAxisMessageList[];

#endif

// debug message types

enum D_MESSAGE
{
 D_PASS = 0,                    /*  0 x00 'PASS' pass done */
 D_DONE = 1,                    /*  1 x01 'DONE' all operations done */
 D_TEST = 2,                    /*  2 x02 'TEST' test message */
 D_HST = 3,                     /*  3 x03 'HST ' home state */
 D_MSTA = 4,                    /*  4 x04 'MSTA' move state */
 D_MCMD = 5,                    /*  5 x05 'MCMD' move command */
 D_XBASE = 6,                   /*  6 x06 'XBAS' x base */
 D_XMVCM = 7,                   /*  7 x07 'XMVC' x move command */
 D_XACTL = 8,                   /*  8 x08 'XCTL' x axis ctl */
 D_XMOV = 9,                    /*  9 x09 'XMOV' x move to location */
 D_XCUR = 10,                   /* 10 x0a 'XCUR' x current location */
 D_XLOC = 11,                   /* 11 x0b 'XLOC' x end location */
 D_XDST = 12,                   /* 12 x0c 'XDST' x distance */
 D_XSTP = 13,                   /* 13 x0d 'XSTP' x steps */
 D_XST = 14,                    /* 14 x0e 'XSTA' x state */
 D_XBSTP = 15,                  /* 15 x0f 'XBLS' x backlash steps */
 D_XDRO = 16,                   /* 16 x10 'XDRO' x dro location */
 D_XPDRO = 17,                  /* 17 x11 'XPDR' x pass dro location */
 D_XEXP = 18,                   /* 18 x12 'XEXP' x expected location */
 D_XERR = 19,                   /* 19 x13 'XERR' x error with respect to dro */
 D_XWT = 20,                    /* 20 x14 'XWT ' x wait */
 D_XDN = 21,                    /* 21 x15 'XDN ' x done */
 D_XEST = 22,                   /* 22 x16 'XEST' x spindle encoder start count */
 D_XEDN = 23,                   /* 23 x17 'XEDN' x spindle encoder done count */
 D_XX = 24,                     /* 24 x18 'XX  ' x  */
 D_XY = 25,                     /* 25 x19 'XY  ' x  */
 D_XIDXD = 26,                  /* 26 x1a 'XIDR' x dro at index pulse */
 D_XIDXP = 27,                  /* 27 x1b 'XIPO' x position at index pulse */
 D_ZBASE = 28,                  /* 28 x1c 'ZBAS' Z base */
 D_ZMVCM = 29,                  /* 29 x1d 'ZMVC' z move command */
 D_ZACTL = 30,                  /* 30 x1e 'ZCTL' z axis ctl */
 D_ZMOV = 31,                   /* 31 x1f 'ZMOV' z move location */
 D_ZCUR = 32,                   /* 32 x20 'ZCUR' x current location */
 D_ZLOC = 33,                   /* 33 x21 'ZLOC' z end location */
 D_ZDST = 34,                   /* 34 x22 'ZDST' z distance */
 D_ZSTP = 35,                   /* 35 x23 'ZSTP' z steps */
 D_ZST = 36,                    /* 36 x24 'ZSTA' z state */
 D_ZBSTP = 37,                  /* 37 x25 'ZBLS' z backlash steps */
 D_ZDRO = 38,                   /* 38 x26 'ZDRO' z dro location */
 D_ZPDRO = 39,                  /* 39 x27 'ZPDR' z pass dro location */
 D_ZEXP = 40,                   /* 40 x28 'ZEXP' z expected location */
 D_ZERR = 41,                   /* 41 x29 'ZERR' z error with respect to dro */
 D_ZWT = 42,                    /* 42 x2a 'ZWT ' z wait */
 D_ZDN = 43,                    /* 43 x2b 'ZDN ' z done */
 D_ZEST = 44,                   /* 44 x2c 'ZEST' z spindle encoder start count */
 D_ZEDN = 45,                   /* 45 x2d 'ZEDN' Z spindle encoder done count */
 D_ZX = 46,                     /* 46 x2e 'ZX  ' z  */
 D_ZY = 47,                     /* 47 x2f 'ZY  ' z  */
 D_ZIDXD = 48,                  /* 48 x30 'ZIDR' z dro at index pulse */
 D_ZIDXP = 49,                  /* 49 x31 'ZIPO' z position at index pulse */
 D_MAX = 50,                    /* 50 x32 'MAX ' debug maximum */
};

#ifdef ENUM_D_MESSAGE

const char *dMessageList[] = 
{
 "D_PASS",                      /*  0 x00 'PASS' pass done */
 "D_DONE",                      /*  1 x01 'DONE' all operations done */
 "D_TEST",                      /*  2 x02 'TEST' test message */
 "D_HST",                       /*  3 x03 'HST ' home state */
 "D_MSTA",                      /*  4 x04 'MSTA' move state */
 "D_MCMD",                      /*  5 x05 'MCMD' move command */
 "D_XBASE",                     /*  6 x06 'XBAS' x base */
 "D_XMVCM",                     /*  7 x07 'XMVC' x move command */
 "D_XACTL",                     /*  8 x08 'XCTL' x axis ctl */
 "D_XMOV",                      /*  9 x09 'XMOV' x move to location */
 "D_XCUR",                      /* 10 x0a 'XCUR' x current location */
 "D_XLOC",                      /* 11 x0b 'XLOC' x end location */
 "D_XDST",                      /* 12 x0c 'XDST' x distance */
 "D_XSTP",                      /* 13 x0d 'XSTP' x steps */
 "D_XST",                       /* 14 x0e 'XSTA' x state */
 "D_XBSTP",                     /* 15 x0f 'XBLS' x backlash steps */
 "D_XDRO",                      /* 16 x10 'XDRO' x dro location */
 "D_XPDRO",                     /* 17 x11 'XPDR' x pass dro location */
 "D_XEXP",                      /* 18 x12 'XEXP' x expected location */
 "D_XERR",                      /* 19 x13 'XERR' x error with respect to dro */
 "D_XWT",                       /* 20 x14 'XWT ' x wait */
 "D_XDN",                       /* 21 x15 'XDN ' x done */
 "D_XEST",                      /* 22 x16 'XEST' x spindle encoder start count */
 "D_XEDN",                      /* 23 x17 'XEDN' x spindle encoder done count */
 "D_XX",                        /* 24 x18 'XX  ' x  */
 "D_XY",                        /* 25 x19 'XY  ' x  */
 "D_XIDXD",                     /* 26 x1a 'XIDR' x dro at index pulse */
 "D_XIDXP",                     /* 27 x1b 'XIPO' x position at index pulse */
 "D_ZBASE",                     /* 28 x1c 'ZBAS' Z base */
 "D_ZMVCM",                     /* 29 x1d 'ZMVC' z move command */
 "D_ZACTL",                     /* 30 x1e 'ZCTL' z axis ctl */
 "D_ZMOV",                      /* 31 x1f 'ZMOV' z move location */
 "D_ZCUR",                      /* 32 x20 'ZCUR' x current location */
 "D_ZLOC",                      /* 33 x21 'ZLOC' z end location */
 "D_ZDST",                      /* 34 x22 'ZDST' z distance */
 "D_ZSTP",                      /* 35 x23 'ZSTP' z steps */
 "D_ZST",                       /* 36 x24 'ZSTA' z state */
 "D_ZBSTP",                     /* 37 x25 'ZBLS' z backlash steps */
 "D_ZDRO",                      /* 38 x26 'ZDRO' z dro location */
 "D_ZPDRO",                     /* 39 x27 'ZPDR' z pass dro location */
 "D_ZEXP",                      /* 40 x28 'ZEXP' z expected location */
 "D_ZERR",                      /* 41 x29 'ZERR' z error with respect to dro */
 "D_ZWT",                       /* 42 x2a 'ZWT ' z wait */
 "D_ZDN",                       /* 43 x2b 'ZDN ' z done */
 "D_ZEST",                      /* 44 x2c 'ZEST' z spindle encoder start count */
 "D_ZEDN",                      /* 45 x2d 'ZEDN' Z spindle encoder done count */
 "D_ZX",                        /* 46 x2e 'ZX  ' z  */
 "D_ZY",                        /* 47 x2f 'ZY  ' z  */
 "D_ZIDXD",                     /* 48 x30 'ZIDR' z dro at index pulse */
 "D_ZIDXP",                     /* 49 x31 'ZIPO' z position at index pulse */
 "D_MAX",                       /* 50 x32 'MAX ' debug maximum */
};

#else

extern const char *dMessageList[];

#endif

// pylathe update events

enum EV_EVENTS
{
 EV_ZLOC = 0,                   /*  0 x00 z location */
 EV_XLOC = 1,                   /*  1 x01 x location */
 EV_RPM = 2,                    /*  2 x02 rpm */
 EV_READ_ALL = 3,               /*  3 x03 all values */
 EV_ERROR = 4,                  /*  4 x04 event error */
 EV_MAX = 5,                    /*  5 x05 maximum event */
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

#else

extern const char *evEventsList[];

#endif

// turning sync selector

enum SEL_TURN
{
 SEL_TU_SPEED = 0,              /*  0 x00 Motor Speed */
 SEL_TU_STEP = 1,               /*  1 x01 Stepper */
 SEL_TU_ENC = 2,                /*  2 x02 Encoder */
 SEL_TU_ISYN = 3,               /*  3 x03 Int Syn */
 SEL_TU_ESYN = 4,               /*  4 x04 Ext Syn */
 SEL_TU_SYN = 5,                /*  5 x05 Sync */
};

#ifdef ENUM_SEL_TURN

const char *selTurnList[] = 
{
 "SEL_TU_SPEED",                /*  0 x00 Motor Speed */
 "SEL_TU_STEP",                 /*  1 x01 Stepper */
 "SEL_TU_ENC",                  /*  2 x02 Encoder */
 "SEL_TU_ISYN",                 /*  3 x03 Int Syn */
 "SEL_TU_ESYN",                 /*  4 x04 Ext Syn */
 "SEL_TU_SYN",                  /*  5 x05 Sync */
};

#else

extern const char *selTurnList[];

#endif

// threading sync selector

enum SEL_THREAD
{
 SEL_TH_NO_ENC = 0,             /*  0 x00 No Encoder */
 SEL_TH_STEP = 1,               /*  1 x01 Stepper */
 SEL_TH_ENC = 2,                /*  2 x02 Encoder */
 SEL_TH_ISYN_RENC = 3,          /*  3 x03 Int Syn, Runout Enc */
 SEL_TH_ESYN_RENC = 4,          /*  4 x04 Ext Syn, Runout Enc */
 SEL_TH_ESYN_RSYN = 5,          /*  5 x05 Ext Syn, Runout Syn */
 SEL_TH_SYN = 6,                /*  6 x06 Syn, Runout Syn */
};

#ifdef ENUM_SEL_THREAD

const char *selThreadList[] = 
{
 "SEL_TH_NO_ENC",               /*  0 x00 No Encoder */
 "SEL_TH_STEP",                 /*  1 x01 Stepper */
 "SEL_TH_ENC",                  /*  2 x02 Encoder */
 "SEL_TH_ISYN_RENC",            /*  3 x03 Int Syn, Runout Enc */
 "SEL_TH_ESYN_RENC",            /*  4 x04 Ext Syn, Runout Enc */
 "SEL_TH_ESYN_RSYN",            /*  5 x05 Ext Syn, Runout Syn */
 "SEL_TH_SYN",                  /*  6 x06 Syn, Runout Syn */
};

#else

extern const char *selThreadList[];

#endif

// arc config selector

enum SEL_ARC_TYPE
{
 SEL_ARC_END = 0,               /*  0 x00 End */
 SEL_ARC_CORNER = 1,            /*  1 x01 Corner */
 SEL_ARC_SMALL = 2,             /*  2 x02 Small Ball */
 SEL_ARC_LARGE = 3,             /*  3 x03 Large Ball */
 SEL_ARC_SMALL_STEM = 4,        /*  4 x04 Small Stem */
 SEL_ARC_LARGE_STEM = 5,        /*  5 x05 Large Stem */
};

#ifdef ENUM_SEL_ARC_TYPE

const char *selArcTypeList[] = 
{
 "SEL_ARC_END",                 /*  0 x00 End */
 "SEL_ARC_CORNER",              /*  1 x01 Corner */
 "SEL_ARC_SMALL",               /*  2 x02 Small Ball */
 "SEL_ARC_LARGE",               /*  3 x03 Large Ball */
 "SEL_ARC_SMALL_STEM",          /*  4 x04 Small Stem */
 "SEL_ARC_LARGE_STEM",          /*  5 x05 Large Stem */
};

#else

extern const char *selArcTypeList[];

#endif

// mpg control states

enum MPG_STATE
{
 MPG_DISABLED = 0,              /*  0 x00 'DS' disabled */
 MPG_CHECK_QUE = 1,             /*  1 x01 'CQ' check queue */
 MPG_DIR_CHANGE_WAIT = 2,       /*  2 x02 'DC' wait for direction change */
 MPG_WAIT_BACKLASH = 3,         /*  3 x03 'WB' wait for backlash */
};

#ifdef ENUM_MPG_STATE

const char *mpgStateList[] = 
{
 "MPG_DISABLED",                /*  0 x00 'DS' disabled */
 "MPG_CHECK_QUE",               /*  1 x01 'CQ' check queue */
 "MPG_DIR_CHANGE_WAIT",         /*  2 x02 'DC' wait for direction change */
 "MPG_WAIT_BACKLASH",           /*  3 x03 'WB' wait for backlash */
};

#else

extern const char *mpgStateList[];

#endif

// riscv actions

enum RISCV_CMD
{
 R_NONE = 0,                    /*  0 x00 'NO' no operation */
 R_OP_START = 1,                /*  1 x01 'OS' start */
 R_OP_DONE = 2,                 /*  2 x02 'OD' done */
 R_SETUP = 3,                   /*  3 x03 'SU' setup */
 R_RESUME = 4,                  /*  4 x04 'RE' resume */
 R_STOP = 5,                    /*  5 x05 'SP' stop */
 R_STOP_X = 6,                  /*  6 x06 'SX' stop x */
 R_STOP_Z = 7,                  /*  7 x07 'SZ' stop z */
 R_DONE = 8,                    /*  8 x08 'DN' done */
 R_SEND_DONE = 9,               /*  9 x09 'ND' send data done */
 R_SET_LOC_X = 10,              /* 10 x0a 'LX' set x loc */
 R_SET_LOC_Z = 11,              /* 11 x0b 'LZ' set z loc */
 R_PAUSE = 12,                  /* 12 x0c 'PA' pause */
 R_START_SPIN = 13,             /* 13 x0d 'S+' start spindle */
 R_STOP_SPIN = 14,              /* 14 x0e 'S-' stop spindle */
 R_UPDATE_SPIN = 15,            /* 15 x0f 'US' update spindle speed */
 R_PASS = 16,                   /* 16 x10 'PS' pass */
 R_SET_ACCEL = 17,              /* 17 x11 'SA' set accel parm */
 R_SET_ACCEL_Q = 18,            /* 18 x12 'SQ' set accel parm queued */
 R_SET_DATA = 19,               /* 19 x13 'SD' set data */
 R_GET_DATA = 20,               /* 20 x14 'GD' set data */
 R_SAVE_Z = 21,                 /* 21 x15 'VZ' save z */
 R_SAVE_X = 22,                 /* 22 x16 'VX' save x */
 R_STEPS_Z = 23,                /* 23 x17 'IZ' save z steps inch */
 R_STEPS_X = 24,                /* 24 x18 'IX' save x steps inch */
 R_HOFS_Z = 25,                 /* 25 x19 'HZ' home offset z */
 R_HOFS_X = 26,                 /* 26 x1a 'HX' home offset x */
 R_JOG_Z = 27,                  /* 27 x1b 'JZ' jog move z */
 R_JOG_X = 28,                  /* 28 x1c 'JX' jog move x */
 R_MOVE_Z = 29,                 /* 29 x1d 'MZ' move z */
 R_MOVE_X = 30,                 /* 30 x1e 'MX' move x */
 R_MOVE_REL_Z = 31,             /* 31 x1f 'RZ' move rel z */
 R_MOVE_REL_X = 32,             /* 32 x20 'RX' move rel x */
 R_READ_ALL = 33,               /* 33 x21 'RA' read all status */
 R_READ_DBG = 34,               /* 34 x22 'RD' read all status */
 R_MAX_CMD = 35,                /* 35 x23 'MX' max value */
};

#ifdef ENUM_RISCV_CMD

const char *riscvCmdList[] = 
{
 "R_NONE",                      /*  0 x00 'NO' no operation */
 "R_OP_START",                  /*  1 x01 'OS' start */
 "R_OP_DONE",                   /*  2 x02 'OD' done */
 "R_SETUP",                     /*  3 x03 'SU' setup */
 "R_RESUME",                    /*  4 x04 'RE' resume */
 "R_STOP",                      /*  5 x05 'SP' stop */
 "R_STOP_X",                    /*  6 x06 'SX' stop x */
 "R_STOP_Z",                    /*  7 x07 'SZ' stop z */
 "R_DONE",                      /*  8 x08 'DN' done */
 "R_SEND_DONE",                 /*  9 x09 'ND' send data done */
 "R_SET_LOC_X",                 /* 10 x0a 'LX' set x loc */
 "R_SET_LOC_Z",                 /* 11 x0b 'LZ' set z loc */
 "R_PAUSE",                     /* 12 x0c 'PA' pause */
 "R_START_SPIN",                /* 13 x0d 'S+' start spindle */
 "R_STOP_SPIN",                 /* 14 x0e 'S-' stop spindle */
 "R_UPDATE_SPIN",               /* 15 x0f 'US' update spindle speed */
 "R_PASS",                      /* 16 x10 'PS' pass */
 "R_SET_ACCEL",                 /* 17 x11 'SA' set accel parm */
 "R_SET_ACCEL_Q",               /* 18 x12 'SQ' set accel parm queued */
 "R_SET_DATA",                  /* 19 x13 'SD' set data */
 "R_GET_DATA",                  /* 20 x14 'GD' set data */
 "R_SAVE_Z",                    /* 21 x15 'VZ' save z */
 "R_SAVE_X",                    /* 22 x16 'VX' save x */
 "R_STEPS_Z",                   /* 23 x17 'IZ' save z steps inch */
 "R_STEPS_X",                   /* 24 x18 'IX' save x steps inch */
 "R_HOFS_Z",                    /* 25 x19 'HZ' home offset z */
 "R_HOFS_X",                    /* 26 x1a 'HX' home offset x */
 "R_JOG_Z",                     /* 27 x1b 'JZ' jog move z */
 "R_JOG_X",                     /* 28 x1c 'JX' jog move x */
 "R_MOVE_Z",                    /* 29 x1d 'MZ' move z */
 "R_MOVE_X",                    /* 30 x1e 'MX' move x */
 "R_MOVE_REL_Z",                /* 31 x1f 'RZ' move rel z */
 "R_MOVE_REL_X",                /* 32 x20 'RX' move rel x */
 "R_READ_ALL",                  /* 33 x21 'RA' read all status */
 "R_READ_DBG",                  /* 34 x22 'RD' read all status */
 "R_MAX_CMD",                   /* 35 x23 'MX' max value */
};

#else

extern const char *riscvCmdList[];

#endif

// riscv axis name

enum RISCV_AXIS_NAME_TYPE
{
 RA_NONE = 0,                   /*  0 x00  */
 RA_Z_AXIS = 1,                 /*  1 x01  */
 RA_X_AXIS = 2,                 /*  2 x02  */
};

#ifdef ENUM_RISCV_AXIS_NAME_TYPE

const char *RiscvAxisNameTypeList[] = 
{
 "RA_NONE",                     /*  0 x00  */
 "RA_Z_AXIS",                   /*  1 x01  */
 "RA_X_AXIS",                   /*  2 x02  */
};

#else

extern const char *RiscvAxisNameTypeList[];

#endif

// riscv data

enum RISCV_DATA_TYPE
{
 RD_NONE = 0,                   /*  0 x00  */
 RD_Z_BACKLASH = 1,             /*  1 x01  */
 RD_X_BACKLASH = 2,             /*  2 x02  */
};

#ifdef ENUM_RISCV_DATA_TYPE

const char *RiscvDataTypeList[] = 
{
 "RD_NONE",                     /*  0 x00  */
 "RD_Z_BACKLASH",               /*  1 x01  */
 "RD_X_BACKLASH",               /*  2 x02  */
};

#else

extern const char *RiscvDataTypeList[];

#endif

// accel types

enum ACCEL_TYPE
{
 A_TURN = 0,                    /*  0 x00 'TU' */
 A_TAPER = 1,                   /*  1 x01 'TP' */
 A_MOVE = 2,                    /*  2 x02 'MV' */
 A_JOG = 3,                     /*  3 x03 'JG' */
 A_SLOW = 4,                    /*  4 x04 'JS' */
};

#ifdef ENUM_ACCEL_TYPE

const char *accelTypeList[] = 
{
 "A_TURN",                      /*  0 x00 'TU' */
 "A_TAPER",                     /*  1 x01 'TP' */
 "A_MOVE",                      /*  2 x02 'MV' */
 "A_JOG",                       /*  3 x03 'JG' */
 "A_SLOW",                      /*  4 x04 'JS' */
};

#else

extern const char *accelTypeList[];

#endif

// riscv accel types

enum AXIS_ACCEL_TYPE
{
 RP_Z_TURN = 0,                 /*  0 x00 'ZT' */
 RP_Z_TAPER = 1,                /*  1 x01 'ZP' */
 RP_Z_MOVE = 2,                 /*  2 x02 'ZM' */
 RP_Z_JOG = 3,                  /*  3 x03 'ZJ' */
 RP_Z_SLOW = 4,                 /*  4 x04 'ZS' */
 RP_X_TURN = 5,                 /*  5 x05 'XT' */
 RP_X_TAPER = 6,                /*  6 x06 'XP' */
 RP_X_MOVE = 7,                 /*  7 x07 'XM' */
 RP_X_JOG = 8,                  /*  8 x08 'XJ' */
 RP_X_SLOW = 9,                 /*  9 x09 'XS' */
 RP_MAX = 10,                   /* 10 x0a  */
};

#ifdef ENUM_AXIS_ACCEL_TYPE

const char *axisAccelTypeList[] = 
{
 "RP_Z_TURN",                   /*  0 x00 'ZT' */
 "RP_Z_TAPER",                  /*  1 x01 'ZP' */
 "RP_Z_MOVE",                   /*  2 x02 'ZM' */
 "RP_Z_JOG",                    /*  3 x03 'ZJ' */
 "RP_Z_SLOW",                   /*  4 x04 'ZS' */
 "RP_X_TURN",                   /*  5 x05 'XT' */
 "RP_X_TAPER",                  /*  6 x06 'XP' */
 "RP_X_MOVE",                   /*  7 x07 'XM' */
 "RP_X_JOG",                    /*  8 x08 'XJ' */
 "RP_X_SLOW",                   /*  9 x09 'XS' */
 "RP_MAX",                      /* 10 x0a  */
};

#else

extern const char *axisAccelTypeList[];

#endif

// riscv accel axis base index

enum ACCEL_BASE
{
 RP_Z_BASE = 0,                 /*  0 x00  */
 RP_X_BASE = 5,                 /*  5 x05  */
};

#ifdef ENUM_ACCEL_BASE

const char *accelBaseList[] = 
{
 "RP_Z_BASE",                   /*  0 x00  */
 "RP_X_BASE",                   /*  5 x05  */
};

#else

extern const char *accelBaseList[];

#endif

// riscv axis states

enum RISCV_AXIS_STATE_TYPE
{
 RS_IDLE = 0,                   /*  0 x00  */
 RS_WAIT_BACKLASH = 1,          /*  1 x01  */
 RS_WAIT = 2,                   /*  2 x02  */
 RS_WAIT_TAPER = 3,             /*  3 x03  */
};

#ifdef ENUM_RISCV_AXIS_STATE_TYPE

const char *RiscvAxisStateTypeList[] = 
{
 "RS_IDLE",                     /*  0 x00  */
 "RS_WAIT_BACKLASH",            /*  1 x01  */
 "RS_WAIT",                     /*  2 x02  */
 "RS_WAIT_TAPER",               /*  3 x03  */
};

#else

extern const char *RiscvAxisStateTypeList[];

#endif

// riscv accel parameters

enum RISCV_SYNC_PARM_TYPE
{
 RP_INITIAL_SUM = 0,            /*  0 x00  */
 RP_INCR1 = 1,                  /*  1 x01  */
 RP_INCR2 = 2,                  /*  2 x02  */
 RP_ACCEL_VAL = 3,              /*  3 x03  */
 RP_ACCEL_COUNT = 4,            /*  4 x04  */
 RP_FREQ_DIV = 5,               /*  5 x05  */
};

#ifdef ENUM_RISCV_SYNC_PARM_TYPE

const char *RiscvSyncParmTypeList[] = 
{
 "RP_INITIAL_SUM",              /*  0 x00  */
 "RP_INCR1",                    /*  1 x01  */
 "RP_INCR2",                    /*  2 x02  */
 "RP_ACCEL_VAL",                /*  3 x03  */
 "RP_ACCEL_COUNT",              /*  4 x04  */
 "RP_FREQ_DIV",                 /*  5 x05  */
};

#else

extern const char *RiscvSyncParmTypeList[];

#endif

// riscv run wait states

enum RISCV_RUN_WAIT
{
 RW_NONE = 0,                   /*  0 x00 'NO' none */
 RW_PAUSE = 1,                  /*  1 x01 'PS' wait pause */
 RW_SPIN_START = 2,             /*  2 x02 'S+' wait spindle start */
 RW_SPIN_STOP = 3,              /*  3 x03 'S-' wait spindle stop */
 RW_WAIT_X = 4,                 /*  4 x04 'WX' wait x done */
 RW_WAIT_Z = 5,                 /*  5 x05 'WZ' wait z done */
};

#ifdef ENUM_RISCV_RUN_WAIT

const char *riscvRunWaitList[] = 
{
 "RW_NONE",                     /*  0 x00 'NO' none */
 "RW_PAUSE",                    /*  1 x01 'PS' wait pause */
 "RW_SPIN_START",               /*  2 x02 'S+' wait spindle start */
 "RW_SPIN_STOP",                /*  3 x03 'S-' wait spindle stop */
 "RW_WAIT_X",                   /*  4 x04 'WX' wait x done */
 "RW_WAIT_Z",                   /*  5 x05 'WZ' wait z done */
};

#else

extern const char *riscvRunWaitList[];

#endif

// commands in ctlbits

enum MOVE_CMD
{
 M_CMD_NONE = 0,                /*  0 x00 no command */
 M_CMD_MOV = 1,                 /*  1 x01 move a set distance */
 M_CMD_JOG = 2,                 /*  2 x02 move while cmd are present */
 M_CMD_SYN = 3,                 /*  3 x03 move dist synchronized to rotation */
 M_CMD_MAX = 4,                 /*  4 x04 rapid move */
 M_CMD_SPEED = 5,               /*  5 x05 jog at speed */
 M_JOG_SLOW = 6,                /*  6 x06 slow jog for home or probe */
};

#ifdef ENUM_MOVE_CMD

const char *moveCmdList[] = 
{
 "M_CMD_NONE",                  /*  0 x00 no command */
 "M_CMD_MOV",                   /*  1 x01 move a set distance */
 "M_CMD_JOG",                   /*  2 x02 move while cmd are present */
 "M_CMD_SYN",                   /*  3 x03 move dist synchronized to rotation */
 "M_CMD_MAX",                   /*  4 x04 rapid move */
 "M_CMD_SPEED",                 /*  5 x05 jog at speed */
 "M_JOG_SLOW",                  /*  6 x06 slow jog for home or probe */
};

#else

extern const char *moveCmdList[];

#endif

// riscv run wait states

enum MOVE_BIT
{
 M_RSV_0 = 0,                   /*  0 x00 no command */
 M_RSV_1 = 1,                   /*  1 x01 no command */
 M_RSV_2 = 2,                   /*  2 x02 no command */
 M_SYN_START = 3,               /*  3 x03 start on sync pulse */
 M_SYN_LEFT = 4,                /*  4 x04 start sync left */
 M_SYN_TAPER = 5,               /*  5 x05 taper on other axis */
 M_DIST_MODE = 6,               /*  6 x06 distance update mode */
 M_FIND_HOME = 7,               /*  7 x07 find home */
 M_CLEAR_HOME = 8,              /*  8 x08 move off of home */
 M_FIND_PROBE = 9,              /*  9 x09 find probe */
 M_CLEAR_PROBE = 10,            /* 10 x0a move off of probe */
 M_DRO_POS = 11,                /* 11 x0b use dro for moving */
 M_DRO_UPD = 12,                /* 12 x0c update internal position from dro */
 M_BIT_MAX = 13,                /* 13 x0d number of bits */
};

#ifdef ENUM_MOVE_BIT

const char *moveBitList[] = 
{
 "M_RSV_0",                     /*  0 x00 no command */
 "M_RSV_1",                     /*  1 x01 no command */
 "M_RSV_2",                     /*  2 x02 no command */
 "M_SYN_START",                 /*  3 x03 start on sync pulse */
 "M_SYN_LEFT",                  /*  4 x04 start sync left */
 "M_SYN_TAPER",                 /*  5 x05 taper on other axis */
 "M_DIST_MODE",                 /*  6 x06 distance update mode */
 "M_FIND_HOME",                 /*  7 x07 find home */
 "M_CLEAR_HOME",                /*  8 x08 move off of home */
 "M_FIND_PROBE",                /*  9 x09 find probe */
 "M_CLEAR_PROBE",               /* 10 x0a move off of probe */
 "M_DRO_POS",                   /* 11 x0b use dro for moving */
 "M_DRO_UPD",                   /* 12 x0c update internal position from dro */
 "M_BIT_MAX",                   /* 13 x0d number of bits */
};

#else

extern const char *moveBitList[];

#endif

// movement status

enum MV_STATUS_BITS
{
 R_MV_PAUSE = 0,                /*  0 x00 'PA' movement paused */
 R_MV_READ_X = 1,               /*  1 x01 'RX' pause x may change */
 R_MV_READ_Z = 2,               /*  2 x02 'RZ' pause z may change */
 R_MV_ACTIVE = 3,               /*  3 x03 'AC' movement active */
 R_MV_DONE = 4,                 /*  4 x04 'DN' movement active */
 R_MV_XLIMIT = 5,               /*  5 x05 'XL' at limit switch */
 R_MV_ZLIMIT = 6,               /*  6 x06 'ZL' at limit switch */
 R_MV_XHOME_ACTIVE = 7,         /*  7 x07 'XA' x home active */
 R_MV_XHOME = 8,                /*  8 x08 'XH' x home success */
 R_MV_ZHOME_ACTIVE = 9,         /*  9 x09 'ZA' z home active */
 R_MV_ZHOME = 10,               /* 10 x0a 'ZH' z home success */
 R_MV_MEASURE = 11,             /* 11 x0b 'MS' pause for measurement */
 R_MV_ESTOP = 12,               /* 12 x0c 'ES' estop */
 R_MV_MAX = 13,                 /* 13 x0d number of bits */
};

#ifdef ENUM_MV_STATUS_BITS

const char *mvStatusBitsList[] = 
{
 "R_MV_PAUSE",                  /*  0 x00 'PA' movement paused */
 "R_MV_READ_X",                 /*  1 x01 'RX' pause x may change */
 "R_MV_READ_Z",                 /*  2 x02 'RZ' pause z may change */
 "R_MV_ACTIVE",                 /*  3 x03 'AC' movement active */
 "R_MV_DONE",                   /*  4 x04 'DN' movement active */
 "R_MV_XLIMIT",                 /*  5 x05 'XL' at limit switch */
 "R_MV_ZLIMIT",                 /*  6 x06 'ZL' at limit switch */
 "R_MV_XHOME_ACTIVE",           /*  7 x07 'XA' x home active */
 "R_MV_XHOME",                  /*  8 x08 'XH' x home success */
 "R_MV_ZHOME_ACTIVE",           /*  9 x09 'ZA' z home active */
 "R_MV_ZHOME",                  /* 10 x0a 'ZH' z home success */
 "R_MV_MEASURE",                /* 11 x0b 'MS' pause for measurement */
 "R_MV_ESTOP",                  /* 12 x0c 'ES' estop */
 "R_MV_MAX",                    /* 13 x0d number of bits */
};

#else

extern const char *mvStatusBitsList[];

#endif

// pause flags

enum PAUSE_BITS
{
 R_DISABLE_JOG = 0,             /*  0 x00 'DJ' jogging disabled */
 R_PAUSE_ENA_Z_JOG = 1,         /*  1 x01 'EZ' enable z job during pause */
 R_PAUSE_ENA_X_JOG = 2,         /*  2 x02 'EX' enable x jog during pause */
 R_PAUSE_READ_Z = 3,            /*  3 x03 'RX' read z after pause */
 R_PAUSE_READ_X = 4,            /*  4 x04 'RZ' read x after pause */
 R_PAUSE_MAX = 5,               /*  5 x05 number of bits */
};

#ifdef ENUM_PAUSE_BITS

const char *pauseBitsList[] = 
{
 "R_DISABLE_JOG",               /*  0 x00 'DJ' jogging disabled */
 "R_PAUSE_ENA_Z_JOG",           /*  1 x01 'EZ' enable z job during pause */
 "R_PAUSE_ENA_X_JOG",           /*  2 x02 'EX' enable x jog during pause */
 "R_PAUSE_READ_Z",              /*  3 x03 'RX' read z after pause */
 "R_PAUSE_READ_X",              /*  4 x04 'RZ' read x after pause */
 "R_PAUSE_MAX",                 /*  5 x05 number of bits */
};

#else

extern const char *pauseBitsList[];

#endif

#endif  /* CTL_STATES_INC */
