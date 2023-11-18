#if !defined(MEGA_CMD_LIST)
#define MEGA_CMD_LIST

enum MEGA_COMMANDS
{
 MEGA_NONE,                     /* 0x00 no command */
 MEGA_SET_RPM,                  /* 0x01 set pwm for rpm */
 MEGA_GET_RPM,                  /* 0x02 get pwm value */
 MEGA_POLL,                     /* 0x03 poll mega info */
 MEGA_SET_VAL,                  /* 0x04 set mega value */
 MEGA_READ_VAL,                 /* 0x05 read mega value */
 MEGA_ENC_START,                /* 0x06 start mega encoder */
 MEGA_ENC_STOP,                 /* 0x07 stop mega encoder */
 MEGA_UPDATE_RPM,               /* 0x08 update rpm if active */
};

#endif  /* MEGA_CMD_LIST */
