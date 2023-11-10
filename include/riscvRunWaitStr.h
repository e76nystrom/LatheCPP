struct S_RISCV_RUN_WAIT
{
 char c0;
 char c1;
};

struct S_RISCV_RUN_WAIT riscvRunWaitStr[] =
{
 {'N', 'O',},            /*  0  0  none */
 {'P', 'S',},            /*  1  1  wait pause */
 {'S', '+',},            /*  2  2  wait spindle start */
 {'S', '-',},            /*  3  3  wait spindle stop */
 {'W', 'X',},            /*  4  4  wait x done */
 {'W', 'Z',},            /*  5  5  wait z done */
};
