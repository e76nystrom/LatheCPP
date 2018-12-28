#if !defined(INCLUDE)
#include "stm32f4xx_hal.h"

#include "lathe.h"

#include "Xilinx.h"
#include "serialio.h"
#define EXT
#endif

typedef union
{
 char  ub[2];			/* char array */
 int16_t i;			/* interger */
} byte_int;

typedef union
{
 unsigned char b[4];		/* char array */
 int32_t i;			/* long interger */
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

#if !defined(INCLUDE)

#if 0

void spisel(void)
{
 spi1sel = 0;
}


void spirel(void)
{
 SPI_SEL_REG = SPI_SEL_BIT;
 SPIn->CR1 &= ~SPI_CR1_SPE;
 int i;
 for (i = 0; i < 100; i++)
  ;
}
#endif

#if 1
void load(char addr, int32_t val)
{
 if (print & 8)
  printf("load %x %lx\n\r",addr,val);
 char buf[8];
 sprintf(buf,"lx %02x",addr);
 // dbgmsg(buf,val);
 spisel();
 spisend(addr);
 byte_long tmp;
 tmp.i = val;
 spisend(tmp.b[3]);
 spisend(tmp.b[2]);
 spisend(tmp.b[1]);
 spisend(tmp.b[0]);
#if 0
 while ((SPIn->SR & SPI_SR_BSY) != 0)
  ;
 unsigned int time = HAL_GetTick() + 2;	/* save time */
 while (time != HAL_GetTick())
  ;
#endif
 spirel();
}
#else
void load(char addr, byte_long val)
{
 if (print & 8)
  printf("load %x %lx\n\r",addr,val.i);
 char buf[8];
 sprintf(buf,"lx %02x",addr);
 // dbgmsg(buf,val.i);
 spisel();
 spisend(addr);
 spisend(val.b[3]);
 spisend(val.b[2]);
 spisend(val.b[1]);
 spisend(val.b[0]);
#if 0
 while ((SPIn->SR & SPI_SR_BSY) != 0)
  ;
 unsigned int time = HAL_GetTick() + 2;	/* save time */
 while (time != HAL_GetTick())
  ;
#endif
 spirel();
}
#endif

void loadb(char addr, char val)
{
 if (print & 8)
  printf("load %x %x\n\r",addr,val);
 spisel();
 spisend(addr);
 spisend(val);
 spirel();
}

void read1(char addr)
{
 spisel();			/* select again */
 spisend(addr);			/* set read address */
 readval.b[3] = spiread();	/* read first byte */
 readval.b[2] = spiread();
 readval.b[1] = spiread();
 readval.b[0] = spiread();
#if 0
 while ((SPIn->SR & SPI_SR_BSY) != 0)
  ;
 unsigned int time = HAL_GetTick() + 2;	/* save time */
 while (time != HAL_GetTick())
  ;
#endif
 spirel();			/* and release */
 if (print & 8)
  printf("read %x %lx\n\r",addr,readval.i);
}

void read(char addr)
{
 spisel();			/* select */
 spisend(addr);			/* output address */
 spisend(0);			/* output one byte to load register */
 spirel();			/* release */

 spisel();			/* select again */
 spisend(XREADREG);		/* set read address */
 readval.b[3] = spiread();	/* read first byte */
 readval.b[2] = spiread();
 readval.b[1] = spiread();
 readval.b[0] = spiread();
 spirel();			/* and release */
 if (print & 8)
  printf("read %x %lx\n\r",addr,readval.i);
}

unsigned char spisend(unsigned char c)
{

 spiw0 = 0;
 spiw1 = 0;
#if 0
 char rsp;
 spi1buf = c;
 while (spi1tbf)
  spiw0++;
 while (!spi1rbf)
  spiw1++;
 rsp = spi1buf;			/* read data response */
#else
 SPI_TypeDef *spi = SPIn;
 spi->DR = c;
 while ((spi->SR & SPI_SR_TXE) == 0)
  spiw0++;
 while ((spi->SR & SPI_SR_RXNE) == 0)
  spiw1++;
 c = spi->DR;
 return(c);
#endif
}

unsigned char spiread(void)
{
 spiw0 = 0;
 spiw1 = 0;
#if 0
 spi1buf = 0;
 while (spi1tbf)
  spiw0++;
 while (!spi1rbf)
  spiw1++;
 return(spi1buf);
#else
 SPI_TypeDef *spi = SPIn;
 spi->DR = 0;
 while ((spi->SR & SPI_SR_TXE) == 0)
  spiw0++;
 while ((spi->SR & SPI_SR_RXNE) == 0)
  spiw1++;
 char c = spi->DR;
 return(c);
#endif
}

#endif
