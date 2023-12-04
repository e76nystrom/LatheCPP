#if !defined(INPUTS_REG_INC)
#define INPUTS_REG_INC

// sFile

struct S_INPUTS_REG
{
 char c0;
 char c1;
};

struct S_INPUTS_REG inputsRegStr[] =
{
 {'1', '0',}, /*    1  0 IN_PIN10         pin 10 */
 {'1', '1',}, /*    2  1 IN_PIN11         pin 11 */
 {'1', '2',}, /*    4  2 IN_PIN12         pin 12 */
 {'1', '3',}, /*    8  3 IN_PIN13         pin 13 */
 {'1', '5',}, /*   10  4 IN_PIN15         pin 15 */
 {'Z', 'H',}, /*   20  5 IN_ZHOME         z home switch */
 {'Z', '-',}, /*   40  6 IN_ZMINUS        z limit minus */
 {'Z', '+',}, /*   80  7 IN_ZPLUS         z Limit Plus */
 {'X', 'H',}, /*  100  8 IN_XHOME         x home switch */
 {'X', '-',}, /*  200  9 IN_XMINUS        x limit minus */
 {'X', '+',}, /*  400 10 IN_XPLUS         x Limit Plus */
 {'P', 'R',}, /*  800 11 IN_PROBE         probe input */
 {'S', 'P',}, /* 1000 12 IN_SPARE         spare input */
};

#define INPUTS_REG_SIZE 13

#endif  /* INPUTS_REG_INC */
