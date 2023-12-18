#if 1	// <-

#if !defined(EXT)
#define EXT extern
#endif

#if defined(STM32MON) || defined(ARDUINO)
#define SPIn SPI2
#endif	/* STM32MON || ARDUINO */

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
void spisel();
void spirel();
#endif

#if 1
void load(char addr, int32_t val);
#else
void load(char addr, byte_long val);
#endif

#if defined(SPI_SEL_Pin) && !defined(Sel_Pin)
void loadb(char addr, char val);

#if defined(STM32MON) || defined(ARDUINO)
char readb(char addr);
int read16(char addr);
int read24(char addr);
#else  /* ! (STM32MON || ARDUINO) */
void spiSendCmd(char cmd);
void read1(char addr);
void read(char addr);
#endif	/* STM32MON || ARDUINO */

#endif	/* SPI_SEL_Pin && !Sel_Pin*/

unsigned char spisend(unsigned char);
unsigned char spiread();

#if defined(CS0_Pin) || defined(Sel_Pin)

void loadb(int dev, char addr, char val);
char readb(int dev, char addr);
int read16(int dev, char addr);
int read24(int dev, char addr);

void spiSel(int dev);
void spiRel(int dev);
void load(int dev, char addr, int32_t val);
void loadb(int dev, char addr, char val);
char readb(int dev, char addr);
int read16(int dev, char addr);

#endif	/* CS0_Pin || Sel_Pin */

#if defined(CS0_Pin)

typedef struct sSpiSel
{
 GPIO_TypeDef *port;
 uint16_t pin;
} T_SPI_SEL, *P_SPI_SEL;

extern T_SPI_SEL spiPin[];

#endif	/* CS0_Pin */

#if defined(STM32MON) || defined(ARDUINO)
#else  /* ! (STM32MON || ARDUINO) */
EXT byte_long readval;
#endif	/* STM32MON || ARDUINO */

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

#endif	/* __cplusplus */

int spiSendRecv(char *txBuf, int txSize, char *rxBuf, int bufSize);

#if defined(SPI_ISR)

#define SPI_TX_SIZE 160
#define SPI_RX_SIZE 80

typedef struct
{
 int txFil;
 int txEmp;
 int txCount;
 char txBuf[SPI_TX_SIZE];
 int rxFil;
 int rxEmp;
 int rxCount;
 char rxBuf[SPI_RX_SIZE];
 int state;
 int txEna;
 int rxReady;
 uint32_t timer;
} T_SPICTL, *P_SPICTL;

EXT T_SPICTL spiCtl;

void putSPI(char ch);
int getSPI();

#if defined(SPI_MASTER)

void spiMasterStart();
void spiMasterReset();

#endif	/* SPI_MASTER */

extern "C" void spiISR();

#endif	/* SPI_ISR */

#endif	// ->
