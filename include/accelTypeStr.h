#if !defined(ACCEL_TYPE_INC)
#define ACCEL_TYPE_INC

struct S_ACCEL_TYPE
{
 char c0;
 char c1;
};

struct S_ACCEL_TYPE accelTypeStr[] =
{
 {'T', 'U',},            /*  0  0  */
 {'T', 'P',},            /*  1  1  */
 {'M', 'V',},            /*  2  2  */
 {'J', 'G',},            /*  3  3  */
 {'J', 'S',},            /*  4  4  */
};

#define ACCEL_TYPE_SIZE 5

#endif  /* ACCEL_TYPE_INC */
