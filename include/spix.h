#if 1	// <-

#if !defined(EXT)
#define EXT extern
#endif

#if defined(STM32MON) || defined(ARDUINO)
#define SPIn SPI2
#endif	/* ARDUINO */

typedef union
{
 char  ub[2];			/* char array */
 int16_t i;			/* integer */
} byte_int;

typedef union
{
 unsigned char b[4];		/* char array */
 int32_t i;			/* long integer */
} byte_long;

#if 1
#define LOAD(a, b) load(a, (int32_t) b)
#else
#define LOAD(a, b) load(a, (byte_long) ((int32_t) b))
#endif

#ifdef __cplusplus
void spisel(void);
void spirel(void);
#endif

#if 1
void load(char addr, int32_t val);
#else
void load(char addr, byte_long val);
#endif

void loadb(char addr, char val);

#if defined(STM32MON) || defined(ARDUINO)
char readb(char addr);
int read16(char addr);
int read24(char addr);
#else
void read1(char addr);
void read(char addr);
#endif

unsigned char spisend(unsigned char);
unsigned char spiread(void);

#if defined(STM32MON) || defined(ARDUINO)
#else
EXT byte_long readval;
#endif

EXT int16_t spiw0;
EXT int16_t spiw1;

#ifdef __cplusplus

#else

#define SPI_SEL_BIT SPI_SEL_Pin
#define SPI_SEL_REG SPI_SEL_GPIO_Port->BSRR

#define spisel()  SPIn->CR1 |= SPI_CR1_SPE; \
 SPI_SEL_REG = (SPI_SEL_BIT << 16)
#define spirel() SPI_SEL_REG = SPI_SEL_BIT; \
 SPIn->CR1 &= ~SPI_CR1_SPE

#endif

#endif	// ->
