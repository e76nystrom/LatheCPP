#if !defined(FPGA_CLK_SEL_INC)
#define FPGA_CLK_SEL_INC

struct S_FPGA_CLK_SEL
{
 char c0;
 char c1;
};

struct S_FPGA_CLK_SEL fpgaClkSelStr[] =
{
 {'N', 'O',},            /*  0  0   */
 {'F', 'R',},            /*  1  1   */
 {'C', 'H',},            /*  2  2   */
 {'I', 'C',},            /*  3  3   */
 {'S', 'F',},            /*  4  4   */
 {'S', 'C',},            /*  5  5   */
 {'S', 'P',},            /*  6  6   */
 {},                     /*  7  7  */
};

#define FPGA_CLK_SEL_SIZE 8

#endif  /* FPGA_CLK_SEL_INC */
