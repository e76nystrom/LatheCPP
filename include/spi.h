#if 1	// <-

#if !defined(EXT)
#define EXT extern
#endif

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
#define LOAD(a,b) load(a, (int32_t) b)
#else
#define LOAD(a,b) load(a, (byte_long) ((int32_t) b))
#endif

#ifdef __cplusplus
inline void spisel(void);
inline void spirel(void);
#endif

#if 1
void load(char addr, int32_t val);
#else
void load(char addr, byte_long val);
#endif
void loadb(char addr, char val);
void read1(char addr);
void read(char addr);
unsigned char spisend(unsigned char);
unsigned char spiread(void);

EXT byte_long readval;
EXT int16_t spiw0;
EXT int16_t spiw1;

#ifdef __cplusplus

inline void spisel()
{
 SPIn->CR1 |= SPI_CR1_SPE;
 SPI_Sel_GPIO_Port->BSRR = (SPI_Sel_Pin << 16);
}

inline void spirel()
{
  SPI_Sel_GPIO_Port->BSRR = SPI_Sel_Pin;
  SPIn->CR1 &= ~SPI_CR1_SPE;
}

#else

#define SPI_SEL_BIT SPI_Sel_Pin
#define SPI_SEL_REG SPI_Sel_GPIO_Port->BSRR

#define spisel()  SPIn->CR1 |= SPI_CR1_SPE; \
 SPI_SEL_REG = (SPI_SEL_BIT << 16)
#define spirel() SPI_SEL_REG = SPI_SEL_BIT; \
 SPIn->CR1 &= ~SPI_CR1_SPE

#endif

#endif	// ->
