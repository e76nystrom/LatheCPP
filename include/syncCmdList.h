#if !defined(SYNC_CMD_LIST)
#define SYNC_CMD_LIST

enum SYNC_COMMANDS
{
 SYNC_SETUP,                    /* 0x00 setup sync routine */
 SYNC_START,                    /* 0x01 start sync routine */
 SYNC_STOP,                     /* 0x02 stop sync routine */
 SYNC_LOADVAL,                  /* 0x03 load parameters */
 SYNC_LOADMULTI,                /* 0x04 load multiple parameters */
 SYNC_READVAL,                  /* 0x05 read parameters */
 SYNC_POLL,                     /* 0x06 poll sync board */
};

#endif  /* SYNC_CMD_LIST */
