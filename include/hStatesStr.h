#if !defined(H_STATES_INC)
#define H_STATES_INC

struct S_H_STATES
{
 char c0;
 char c1;
};

struct S_H_STATES hStatesStr[] =
{
 {'H', 'I',},            /*  0  0  idle state */
 {'H', 'F',},            /*  1  1  found home switch */
 {'O', 'F',},            /*  2  2  off home switch */
 {'B', 'F',},            /*  3  3  backoff dist from switch */
 {'H', 'S',},            /*  4  4  found home slowly */
};

#define H_STATES_SIZE 5

#endif  /* H_STATES_INC */
