#if 1	// <-

#define ENCMAX (2540 * 8)
#define FCY 84000000

extern int16_t encState;		/* state of encoder */

void encInit(void);
void encStart(int tEna);
void encStop(void);

#endif	// ->
