
// mega poll response bits

enum POLL_MEGA
{
 M_POLL_ESTOP_NO,               /*  0 x00 estop no in */
 M_POLL_ESTOP_NC,               /*  1 x01 estop nc in */
 M_POLL_SP_FWD,                 /*  2 x02 spindle forward in */
 M_POLL_SP_REV,                 /*  3 x03 spindle reverse in */
 M_POLL_ESTOP,                  /*  4 x04 estop condition */
 M_POLL_WD_ENA,                 /*  5 x05 watchdog enabled */
 M_POLL_CP_ACTIVE,              /*  6 x06 charge pump active */
 M_POLL_PWM_ACTIVE,             /*  7 x07 pwm active */
 M_POLL_STEP_DIS,               /*  8 x08 stepper disabled */
 M_POLL_ESTOP_RLY,              /*  9 x09 estop relay */
 M_POLL_ESTOP_PC,               /* 10 x0a estop pc */
};

#ifdef ENUM_POLL_MEGA

const char *pollMegaList[] = 
{
};

#else

extern const char *pollMegaList[];

#endif
