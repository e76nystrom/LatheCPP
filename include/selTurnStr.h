#if !defined(SEL_TURN_INC)
#define SEL_TURN_INC

struct S_SEL_TURN
{
 char c0;
 char c1;
};

struct S_SEL_TURN selTurnStr[] =
{
 {'M', 'S',},            /*  0  0  Motor Speed */
 {'S', 'T',},            /*  1  1  Stepper */
 {'E', 'N',},            /*  2  2  Encoder */
 {'S', 'Y',},            /*  3  3  Sync */
 {'I', 'S',},            /*  4  4  Int Syn */
 {'E', 'S',},            /*  5  5  Ext Syn */
};

#define SEL_TURN_SIZE 6

#endif  /* SEL_TURN_INC */
