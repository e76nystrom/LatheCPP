#if !defined(MOVE_BIT_INC)
#define MOVE_BIT_INC

struct S_MOVE_BIT
{
 char c0;
 char c1;
};

struct S_MOVE_BIT moveBitStr[] =
{
 {'R', '0',},            /*  0  0  no command */
 {'R', '1',},            /*  1  1  no command */
 {'R', '2',},            /*  2  2  no command */
 {'S', 'S',},            /*  3  3  start on sync pulse */
 {'S', 'L',},            /*  4  4  start sync left */
 {'S', 'T',},            /*  5  5  taper on other axis */
 {'D', 'M',},            /*  6  6  distance update mode */
 {'F', 'H',},            /*  7  7  find home */
 {'C', 'H',},            /*  8  8  move off of home */
 {'F', 'P',},            /*  9  9  find probe */
 {'C', 'P',},            /*  a 10  move off of probe */
 {'D', 'P',},            /*  b 11  use dro for moving */
 {'D', 'U',},            /*  c 12  update internal position from dro */
 {'T', 'H',},            /*  d 13  thread enabled */
 {'R', 'O',},            /*  e 14  runout enabled */
 {'I', 'N',},            /*  f 15  internal operation */
 {'M', 'X',},            /* 10 16  number of bits */
};

#define MOVE_BIT_SIZE 17

#endif  /* MOVE_BIT_INC */
