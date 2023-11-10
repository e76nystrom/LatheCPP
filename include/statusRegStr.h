struct S_STATUS
{
 char c0;
 char c1;
};

struct S_STATUS statusRegStr[] =
{
 {'Z', 'E',}, /*    1  0 Z_AXIS_ENA       z axis enable flag */
 {'Z', 'D',}, /*    2  1 Z_AXIS_DONE      z axis done */
 {'Z', 'd',}, /*    4  2 Z_AXIS_CUR_DIR   z axis current dir */
 {'X', 'E',}, /*    8  3 X_AXIS_ENA       x axis enable flag */
 {'X', 'D',}, /*   10  4 X_AXIS_DONE      x axis done */
 {'X', 'd',}, /*   20  5 X_AXIS_CUR_DIR   x axis current dir */
 {'E', 'S',}, /*   40  6 ST_ESTOP         emergency stop */
 {'S', '+',}, /*   80  7 SPINDLE_ACTIVE   spindle active */
 {'Q', '+',}, /*  100  8 QUE_NOT_EMPTY    ctl queue not empty */
 {'C', 'B',}, /*  200  9 CTL_BUSY         controller busy */
 {'S', 'A',}, /*  400 10 SYNC_ACTIVE      sync active */
};
