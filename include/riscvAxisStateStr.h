#if !defined(RISCV_AXIS_STATE_INC)
#define RISCV_AXIS_STATE_INC

struct S_RISCV_AXIS_STATE
{
 char c0;
 char c1;
};

struct S_RISCV_AXIS_STATE riscvAxisStateStr[] =
{
 {'I', 'D',},            /*  0  0  idle */
 {'W', 'B',},            /*  1  1  wait backlash */
 {'W', 'D',},            /*  2  2  wait done */
 {'W', 'T',},            /*  3  3  wait taper */
 {'W', 'R',},            /*  4  4  wait runout */
};

#define RISCV_AXIS_STATE_SIZE 5

#endif  /* RISCV_AXIS_STATE_INC */
