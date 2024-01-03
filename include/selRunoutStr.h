#if !defined(SEL_RUNOUT_INC)
#define SEL_RUNOUT_INC

struct S_SEL_RUNOUT
{
 char c0;
 char c1;
};

struct S_SEL_RUNOUT selRunoutStr[] =
{
 {'N', 'O',},            /*  0  0  No Encoder */
 {'S', 'T',},            /*  1  1  Stepper */
 {'E', 'N',},            /*  2  2  Encoder */
 {'S', 'Y',},            /*  3  3  Syn */
 {'I', 'S',},            /*  4  4  Int Syn */
 {'E', 'S',},            /*  5  5  Ext Syn */
};

#define SEL_RUNOUT_SIZE 6

#endif  /* SEL_RUNOUT_INC */
