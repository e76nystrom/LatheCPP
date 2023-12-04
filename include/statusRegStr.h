#if !defined(STATUS_REG_INC)
#define STATUS_REG_INC

// sFile

struct S_STATUS_REG
{
 char c0;
 char c1;
};

struct S_STATUS_REG statusRegStr[] =
{
 {'Z', 'E',}, /*    1  0 Z_AXIS_ENA       z axis enable flag */
 {'Z', 'D',}, /*    2  1 Z_AXIS_DONE      z axis done */
 {'Z', 'd',}, /*    4  2 Z_AXIS_CUR_DIR   z axis current dir */
 {'X', 'E',}, /*    8  3 X_AXIS_ENA       x axis enable flag */
 {'X', 'D',}, /*   10  4 X_AXIS_DONE      x axis done */
 {'X', 'd',}, /*   20  5 X_AXIS_CUR_DIR   x axis current dir */
 {'E', 'S',}, /*   40  6 ST_ESTOP         emergency stop */
 {'S', '+',}, /*   80  7 SPINDLE_ACTIVE   spindle active */
 {'S', 'A',}, /*  100  8 SYNC_ACTIVE      sync active */
};

#define STATUS_REG_SIZE 9

#endif  /* STATUS_REG_INC */
