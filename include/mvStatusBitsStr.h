#if !defined(INC_MV_STATUS_BITS)
#define INC_MV_STATUS_BITS

struct S_MV_STATUS_BITS
{
 char c0;
 char c1;
};

struct S_MV_STATUS_BITS mvStatusBitsStr[] =
{
 {'P', 'A',},            /*  0  0  movement paused */
 {'R', 'X',},            /*  1  1  pause x may change */
 {'R', 'Z',},            /*  2  2  pause z may change */
 {'A', 'C',},            /*  3  3  movement active */
 {'D', 'N',},            /*  4  4  movement active */
 {'X', 'L',},            /*  5  5  at limit switch */
 {'Z', 'L',},            /*  6  6  at limit switch */
 {'X', 'A',},            /*  7  7  x home active */
 {'X', 'H',},            /*  8  8  x home success */
 {'Z', 'A',},            /*  9  9  z home active */
 {'Z', 'H',},            /*  a 10  z home success */
 {'M', 'S',},            /*  b 11  pause for measurement */
 {'E', 'S',},            /*  c 12  estop */
 {},                     /*  d 13  */
};

#endif  /* MV_STATUS_BITS */
