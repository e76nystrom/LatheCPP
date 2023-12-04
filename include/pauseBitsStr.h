#if !defined(PAUSE_BITS_INC)
#define PAUSE_BITS_INC

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

#define PAUSE_BITS_SIZE 6

#endif  /* PAUSE_BITS_INC */
