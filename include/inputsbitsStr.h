#if !defined(INC_INPUTS_BITS)
#define INC_INPUTS_BITS

struct S_INPUTS_BITS
{
 char c0;
 char c1;
};

struct S_INPUTS_BITS inputsBitsStr[] =
{
 {'1', '0',},            /*  0  0  pin 10 */
 {'1', '1',},            /*  1  1  pin 11 */
 {'1', '2',},            /*  2  2  pin 12 */
 {'1', '3',},            /*  3  3  pin 13 */
 {'1', '5',},            /*  4  4  pin 15 */
 {'Z', 'H',},            /*  5  5  z home switch */
 {'Z', '-',},            /*  6  6  z limit minus */
 {'Z', '+',},            /*  7  7  z Limit Plus */
 {'X', 'H',},            /*  8  8  x home switch */
 {'X', '-',},            /*  9  9  x limit minus */
 {'X', '+',},            /*  a 10  x Limit Plus */
 {'P', 'R',},            /*  b 11  probe input */
 {'S', 'P',},            /*  c 12  spare input */
 {'M', 'X',},            /*  d 13  spare input */
};

#endif  /* INPUTS_BITS */
