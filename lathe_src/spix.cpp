//#if !defined(INCLUDE)
#define __SPI__

#ifdef STM32F1
#include "stm32f1xx_hal.h"
#endif
#ifdef STM32F4
#include "stm32f4xx_hal.h"
#endif
#ifdef STM32F7
#include "stm32f7xx_hal.h"
#endif
#ifdef STM32H7
#include "stm32h7xx_hal.h"
#endif

#if defined(ARDUINO_ARCH_STM32)

#include "Arduino.h"
#include "serial.h"
#include "main.h"
#define flushBuf flush
int print;

#else

#if defined(STM32MON)

#include "main.h"
#include <stdio.h>
#include "serialio.h"
#include "cyclectr.h"
int print;

#else

#include "lathe.h"
#include "Xilinx.h"
#include "serialio.h"

#endif	/* STM32MON */
#endif	/* ARDUINI_ARCH_STM32 */

#ifdef EXT
#undef EXT
#endif

#define EXT
#include "spix.h"
//#endif

#if defined(__SPI_INC__)	// <-

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
#ifdef __SPI__

void spisel(void)
{
 SPIn->CR1 |= SPI_CR1_SPE;
 SPI_SEL_GPIO_Port->BSRR = (SPI_SEL_Pin << 16);
}

char spiRelTmp;

void spirel(void)
{
#if defined(CYCLE_CTR)
 //uint32_t start = getCycles();
#endif
// while ((SPIn->SR & SPI_SR_RXNE) == 0) /* wait for receive done */
//  ;
#if defined(STM32F1) || defined(STM32F4) || defined(STM32F7)
 while ((SPIn->SR & SPI_SR_TXE) == 0) /* wait for transmit done */
  ;
 while ((SPIn->SR & SPI_SR_BSY) != 0) /* wait for not busy */
 {
  if ((SPIn->SR & SPI_SR_RXNE) != 0)
   spiRelTmp = SPIn->DR;
 }
#endif
#if defined(STM32H7)
 while ((SPIn->SR & SPI_SR_EOT) == 0) /* wait for end of transfer*/
  ;
#endif
#if defined(CYCLE_CTR)
 //uint32_t t = getCycles() - start;
#endif
 SPIn->CR1 &= ~SPI_CR1_SPE;
 SPI_SEL_GPIO_Port->BSRR = SPI_SEL_Pin;
#if defined(CYCLE_CTR)
 //printf("spirel %02x t %u\n", (unsigned int) SPIn->SR, (unsigned int) t);
#endif
}

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
// if (print & 8)
//  printf("load %x %x\n", (unsigned int) addr, (unsigned int) val);
//  char buf[8];
//  sprintf(buf, "lx %02x", addr);
//  dbgmsg(buf, val);
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
  printf("load %x %lx\n",
	 (unsigned int) addr, (unsigned int) val.i);
 // char buf[8];
 // sprintf(buf, "lx %02x", addr);
 // dbgmsg(buf, val.i);
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
// if (print & 8)
//  printf("load %02x %02x\n",
//  (unsigned int) addr, (unsigned int) val);
 spisel();
 spisend(addr);
 spisend(val);
 spirel();
}

#if defined(STM32MON) || defined(ARDUINO)
char readb(char addr)
{
 spisel();			/* select again */
 spisend(addr);			/* set read address */
 char rtnVal = spiread();
 spirel();			/* and release */
 if (print & 8)
  printf("read %02x %02x\n",
	 (unsigned int) addr, (unsigned int) rtnVal);
 return(rtnVal);
}

int read16(char addr)
{
 spisel();			/* select again */
 spisend(addr);			/* set read address */
 byte_long rtnVal;
 rtnVal.i = 0;
 rtnVal.b[1] = spiread();
 rtnVal.b[0] = spiread();
 spirel();
 if (print & 8)
  printf("read %02x %04x\n",
	 (unsigned int) addr, (unsigned int) rtnVal.i);
 return(rtnVal.i);
}

int read24(char addr)
{
 spisel();			/* select again */
 spisend(addr);			/* set read address */
 byte_long rtnVal;
 rtnVal.i = 0;
 rtnVal.b[2] = spiread();
 rtnVal.b[1] = spiread();
 rtnVal.b[0] = spiread();
 spirel();
 if (print & 8)
  printf("read %02x %06x\n",
	 (unsigned int) addr, (unsigned int) rtnVal.i);
 return(rtnVal.i);
}

#else

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
// if (print & 8)
//  printf("read %x %x\n",
//	 (unsigned int) addr, (unsigned int) readval.i);
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
// if (print & 8)
//  printf("read %x %x\n",
//	 (unsigned int) addr, (unsigned int) readval.i);
}

#endif

unsigned char spisend(unsigned char c)
{
 spiw0 = 0;
 spiw1 = 0;

 SPI_TypeDef *spi = SPIn;

#if defined(STM32F1) || defined(STM32F4) || defined(STM32F7)
 spi->DR = c;
 while ((spi->SR & SPI_SR_TXE) == 0)
  spiw0++;
 while ((spi->SR & SPI_SR_RXNE) == 0)
  spiw1++;
 c = spi->DR;

#endif

#if defined(STM32H7)
 spi->TXDR = c;
 while ((spi->SR & SPI_SR_TXP) == 0)
  spiw0++;
 while ((spi->SR & SPI_SR_RXP) == 0)
  spiw1++;
 c = spi->RXDR;
#endif 

 return(c);
}

unsigned char spiread(void)
{
 spiw0 = 0;
 spiw1 = 0;

 SPI_TypeDef *spi = SPIn;

#if defined(STM32F1) || defined(STM32F4) || defined(STM32F7)
 spi->DR = 0;
 while ((spi->SR & SPI_SR_TXE) == 0)
  spiw0++;
 while ((spi->SR & SPI_SR_RXNE) == 0)
  spiw1++;
 char c = spi->DR;
#endif

#if defined(STM32H7)
 spi->TXDR = 0;
 while ((spi->SR & SPI_SR_TXP) == 0)
  spiw0++;
 while ((spi->SR & SPI_SR_RXP) == 0)
  spiw1++;
 char c = spi->RXDR;
#endif 

 return(c);
}

#endif
