#if !defined(CTL_STATES_INC)
#define CTL_STATES_INC

// mega poll response bits

enum POLL_MEGA
{
 M_POLL_ESTOP_NO = 0,           /*  0 x00 estop no in */
 M_POLL_ESTOP_NC = 1,           /*  1 x01 estop nc in */
 M_POLL_SP_FWD = 2,             /*  2 x02 spindle forward in */
 M_POLL_SP_REV = 3,             /*  3 x03 spindle reverse in */
 M_POLL_ESTOP = 4,              /*  4 x04 estop condition */
 M_POLL_WD_ENA = 5,             /*  5 x05 watchdog enabled */
 M_POLL_CP_ACTIVE = 6,          /*  6 x06 charge pump active */
 M_POLL_PWM_ACTIVE = 7,         /*  7 x07 pwm active */
 M_POLL_STEP_DIS = 8,           /*  8 x08 stepper disabled */
 M_POLL_ESTOP_RLY = 9,          /*  9 x09 estop relay */
 M_POLL_ESTOP_PC = 10,          /* 10 x0a estop pc */
};

#ifdef ENUM_POLL_MEGA

const char *pollMegaList[] = 
{
 "M_POLL_ESTOP_NO",             /*  0 x00 estop no in */
 "M_POLL_ESTOP_NC",             /*  1 x01 estop nc in */
 "M_POLL_SP_FWD",               /*  2 x02 spindle forward in */
 "M_POLL_SP_REV",               /*  3 x03 spindle reverse in */
 "M_POLL_ESTOP",                /*  4 x04 estop condition */
 "M_POLL_WD_ENA",               /*  5 x05 watchdog enabled */
 "M_POLL_CP_ACTIVE",            /*  6 x06 charge pump active */
 "M_POLL_PWM_ACTIVE",           /*  7 x07 pwm active */
 "M_POLL_STEP_DIS",             /*  8 x08 stepper disabled */
 "M_POLL_ESTOP_RLY",            /*  9 x09 estop relay */
 "M_POLL_ESTOP_PC",             /* 10 x0a estop pc */
};

#else

extern const char *pollMegaList[];

#endif

// mega vfd speed selector

enum VFDSPEED
{
 MEGA_SLOW_PWM = 0,             /*  0 x00 Slow PWM */
 MEGA_FAST_PWM = 1,             /*  1 x01 Fast PWM */
 MEGA_DIRECT_RPM = 2,           /*  2 x02 Set RPM */
};

#ifdef ENUM_VFDSPEED

const char *vfdSpeedList[] = 
{
 "MEGA_SLOW_PWM",               /*  0 x00 Slow PWM */
 "MEGA_FAST_PWM",               /*  1 x01 Fast PWM */
 "MEGA_DIRECT_RPM",             /*  2 x02 Set RPM */
};

#else

extern const char *vfdSpeedList[];

#endif

#endif  /* CTL_STATES_INC */
