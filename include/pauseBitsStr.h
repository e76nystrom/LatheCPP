#if !defined(INC_PAUSE_BITS)
#define INC_PAUSE_BITS

struct S_PAUSE_BITS
{
 char c0;
 char c1;
};

struct S_PAUSE_BITS pauseBitsStr[] =
{
 {'D', 'J',},            /*  0  0  jogging disabled */
 {'E', 'Z',},            /*  1  1  enable z job during pause */
 {'E', 'X',},            /*  2  2  enable x jog during pause */
 {'R', 'X',},            /*  3  3  read z after pause */
 {'R', 'Z',},            /*  4  4  read x after pause */
 {},                     /*  5  5  */
};

#endif  /* PAUSE_BITS */
