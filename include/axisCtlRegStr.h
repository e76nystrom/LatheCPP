#if !defined(AXIS_CTL_REG_INC)
#define AXIS_CTL_REG_INC

// sFile

struct S_AXIS_CTL_REG
{
 char c0;
 char c1;
};

struct S_AXIS_CTL_REG axisCtlRegStr[] =
{
 {'I', 'N',}, /*    1  0 CTL_INIT         reset flag */
 {'S', 'T',}, /*    2  1 CTL_START        start */
 {'B', 'K',}, /*    4  2 CTL_BACKLASH     backlash move no pos upd */
 {'W', 'S',}, /*    8  3 CTL_WAIT_SYNC    wait for sync to start */
 {'+', '-',}, /*   10  4 CTL_DIR          direction */
 {'S', 'L',}, /*   20  5 CTL_SET_LOC      set location */
 {'C', 'H',}, /*   40  6 CTL_CH_DIRECT    ch input direct */
 {'S', 'L',}, /*   80  7 CTL_SLAVE        slave ctl by other axis */
 {'D', 'E',}, /*  100  8 CTL_DRO_END      use dro to end move */
 {'D', 'M',}, /*  200  9 CTL_DIST_MODE    distance udpdate mode */
 {'J', 'C',}, /*  400 10 CTL_JOG_CMD      jog with commands */
 {'J', 'M',}, /*  800 11 CTL_JOG_MPG      jog with mpg */
 {'H', 'O',}, /* 1000 12 CTL_HOME         homing axis */
 {'H', 'P',}, /* 2000 13 CTL_HOME_POL     home signal polarity */
 {'P', 'R',}, /* 4000 14 CTL_PROBE        probe enable */
 {'U', 'L',}, /* 8000 15 CTL_USE_LIMITS   use limits */
};

#define AXIS_CTL_REG_SIZE 16

#endif  /* AXIS_CTL_REG_INC */
