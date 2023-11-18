#if !defined(INC_MPG_STATE)
#define INC_MPG_STATE

struct S_MPG_STATE
{
 char c0;
 char c1;
};

struct S_MPG_STATE mpgStateStr[] =
{
 {'D', 'S',},            /*  0  0  disabled */
 {'C', 'Q',},            /*  1  1  check queue */
 {'D', 'C',},            /*  2  2  wait for direction change */
 {'W', 'B',},            /*  3  3  wait for backlash */
};

#endif  /* MPG_STATE */
