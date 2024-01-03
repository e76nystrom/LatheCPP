#if !defined(SEL_THREAD_INC)
#define SEL_THREAD_INC

struct S_SEL_THREAD
{
 char c0;
 char c1;
};

struct S_SEL_THREAD selThreadStr[] =
{
 {'N', 'O',},            /*  0  0  No Encoder */
 {'S', 'T',},            /*  1  1  Stepper */
 {'E', 'N',},            /*  2  2  Encoder */
 {'S', 'Y',},            /*  3  3  Syn */
 {'I', 'S',},            /*  4  4  Syn */
 {'E', 'S',},            /*  5  5  Syn */
};

#define SEL_THREAD_SIZE 6

#endif  /* SEL_THREAD_INC */
