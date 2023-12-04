#if !defined(AXIS_STATUS_REG_INC)
#define AXIS_STATUS_REG_INC

// sFile

struct S_AXIS_STATUS_REG
{
 char c0;
 char c1;
};

struct S_AXIS_STATUS_REG axisStatusRegStr[] =
{
 {'D', 'N',}, /*    1  0 AX_DONE          axis done */
 {'Z', 'E',}, /*    2  1 AX_DIST_ZERO     axis distance zero */
 {'D', 'R',}, /*    4  2 AX_DONE_DRO      axis done dro */
 {'H', 'O',}, /*    8  3 AX_DONE_HOME     axis done home */
 {'L', 'I',}, /*   10  4 AX_DONE_LIMIT    axis done limit */
 {'P', 'R',}, /*   20  5 AX_DONE_PROBE    axis done probe */
 {'I', 'H',}, /*   40  6 AX_IN_HOME       axis home */
 {'I', '-',}, /*   80  7 AX_IN_MINUS      axis in minus limit */
 {'I', '+',}, /*  100  8 AX_IN_PLUS       axis in plus limit */
 {'I', 'P',}, /*  200  9 AX_IN_PROBE      axis in probe */
 {'I', 'F',}, /*  400 10 AX_IN_FLAG       axis in flag */
};

#define AXIS_STATUS_REG_SIZE 11

#endif  /* AXIS_STATUS_REG_INC */
