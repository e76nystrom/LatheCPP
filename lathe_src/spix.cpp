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

#else  /* ! ARDUINO_ARCH_STM32 */

#if defined(STM32MON)

#include "main.h"
#include <stdio.h>
#include "serialio.h"
#include "cyclectr.h"
int print;

#else  /* ! STM32MON */

#if !defined(SYNC)

#include "lathe.h"
#include "Xilinx.h"
#include "serialio.h"
#include "pinDef.h"

#else  /* SYNC */

#include "main.h"
#include <stdio.h>
#include <stdint.h>
#include <config.h>
#include "serialio.h"
#include "remcmd.h"

#endif /* SYNC */
#endif	/* STM32MON */
#endif	/* ARDUINO_ARCH_STM32 */

#ifdef EXT
#undef EXT
#endif

#define EXT
#include "spix.h"

#if defined(__SPI_INC__)	// <-

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
#ifdef __SPI__

#if defined(CS0_Pin)

T_SPI_SEL spiPin[] =
{
 CS0_GPIO_Port, CS0_Pin,

#if defined(CS1_Pin)
 CS1_GPIO_Port, CS1_Pin,
#endif	/* CS1_Pin */

#if defined(CS2_Pin)
 CS2_GPIO_Port, CS2_Pin,
#endif	/* CS2_Pin */

#if defined(CS3_Pin)
 CS3_GPIO_Port, CS3_Pin,
#endif	/* CS3_Pin */
};

#endif	/* CS0_Pin */

#if defined(SPI_SEL_Pin) && !defined(Sel_Pin)

void spisel()
{
 SPIn->CR1 |= SPI_CR1_SPE;
 SPI_SEL_GPIO_Port->BSRR = (SPI_SEL_Pin << 16);
}

char spiRelTmp;

void spirel()
{
#if defined(CYCLE_CTR)
 //uint32_t start = getCycles();
#endif	/* CYCLE_CTR */

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
#endif	/* STM32F1 || STM32F4 || STM32F7 */

#if defined(STM32H7)
 while ((SPIn->SR & SPI_SR_EOT) == 0) /* wait for end of transfer*/
  ;
#endif	/* STM32H7 */

#if defined(CYCLE_CTR)
 //uint32_t t = getCycles() - start;
#endif	/* CYCLE_CTR */

 SPIn->CR1 &= ~SPI_CR1_SPE;
 SPI_SEL_GPIO_Port->BSRR = (SPI_SEL_Pin);

#if defined(CYCLE_CTR)
 //printf("spirel %02x t %u\n", (unsigned int) SPIn->SR, (unsigned int) t);
#endif	/* CYCLE_CTR */
}

#if 0

void spisel()
{
 spi1sel = 0;
}

void spirel()
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
//  dbgMsg(buf, val);
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
 // dbgMsg(buf, val.i);
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

void spiSendCmd(char cmd)
{
 spisel();
 spisend(cmd);
 spirel();
}

int spiSendRecv(char *txBuf, int txSize, char *rxBuf, int bufSize)
{
 char ch;
 int state = 0;
 int count = 0;
 int txCount = 0;

 spisel();
 while (true)
 {
  if (txSize != 0)
  {
   ch = spisend(*txBuf++);
   txSize -= 1;
  }
  else
  {
   ch = spisend(0);
   txCount += 1;
  }
  
  if (state == 0)
  {
   if (ch == '-')
   {
    state = 1;
   }
  }
  
  else
  {
   if (ch != 0)
   {
    if (count <= bufSize)
    {
     *rxBuf++ = ch;
     count += 1;
    }

    if (ch == '*')
    {
     state = 0;
     spirel();
     return(count);
    }
   }
  }
  if (txCount >= 40)
  {
   spirel();
   return(0);
  }
 }
}

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

#else  /* ! (STM32MON || ARDUINO) */

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

#if defined(XREADREG)

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

#endif	/* XREADREG */

#endif	/* STM32MON || ARDUINO */

#endif	/* SPI_SEL_Pin && !Sel_Pin */

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

#endif	/* STM32F1 || STM32F4 || STM32F7 */

#if defined(STM32H7)
 spi->TXDR = c;
 while ((spi->SR & SPI_SR_TXP) == 0)
  spiw0++;
 while ((spi->SR & SPI_SR_RXP) == 0)
  spiw1++;
 c = spi->RXDR;
#endif	/* STM32H7 */

 return(c);
}

unsigned char spiread()
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
#endif	/* STM32F1 || STM32F4 || STM32F7 */

#if defined(STM32H7)
 spi->TXDR = 0;
 while ((spi->SR & SPI_SR_TXP) == 0)
  spiw0++;
 while ((spi->SR & SPI_SR_RXP) == 0)
  spiw1++;
 char c = spi->RXDR;
#endif	/* STM32H7 */

 return(c);
}

#if defined(CS0_Pin)

void spisel(int dev)
{
 SPIn->CR1 |= SPI_CR1_SPE;
 P_SPI_SEL sel = &spiPin[dev];
 GPIO_TypeDef *port = sel->port;
 port->BSRR = (sel->pin << 16);
}

char spiRelTmp;

void spirel(int dev)
{
#if defined(CYCLE_CTR)
 //uint32_t start = getCycles();
#endif	/* CYCLE_CTR */

#if defined(STM32F1) || defined(STM32F4) || defined(STM32F7)
 while ((SPIn->SR & SPI_SR_TXE) == 0) /* wait for transmit done */
  ;
 while ((SPIn->SR & SPI_SR_BSY) != 0) /* wait for not busy */
 {
  if ((SPIn->SR & SPI_SR_RXNE) != 0)
   spiRelTmp = SPIn->DR;
 }
#endif	/* STM32F1 || STM32F4 || STM32F7 */

#if defined(STM32H7)
 while ((SPIn->SR & SPI_SR_EOT) == 0) /* wait for end of transfer*/
  ;
#endif	/* STM32H7 */

#if defined(CYCLE_CTR)
 //uint32_t t = getCycles() - start;
#endif	/* CYCLE_CTR */

 SPIn->CR1 &= ~SPI_CR1_SPE;

 SPIn->CR1 |= SPI_CR1_SPE;
 P_SPI_SEL sel = &spiPin[dev];
 GPIO_TypeDef *port = sel->port;
 port->BSRR = sel->pin;

#if defined(CYCLE_CTR)
 //printf("spirel %02x t %u\n", (unsigned int) SPIn->SR, (unsigned int) t);
#endif	/* CYCLE_CTR */
}

#endif	/* CS0_Pin */

#if defined(Sel_Pin)

void spisel(int dev)
{
 SPIn->CR1 |= SPI_CR1_SPE;
 if (dev == 0)
  Sel_GPIO_Port->BSRR = (Sel_Pin << 16);
 else
  Sel_GPIO_Port->BSRR = Sel_Pin;
 SPI_SEL_GPIO_Port->BSRR = (SPI_SEL_Pin << 16);
}

char spiRelTmp;

void spirel(int dev)
{
#if defined(CYCLE_CTR)
 //uint32_t start = getCycles();
#endif	/* CYCLE_CTR */

#if defined(STM32F1) || defined(STM32F4) || defined(STM32F7)
 while ((SPIn->SR & SPI_SR_TXE) == 0) /* wait for transmit done */
  ;
 while ((SPIn->SR & SPI_SR_BSY) != 0) /* wait for not busy */
 {
  if ((SPIn->SR & SPI_SR_RXNE) != 0)
   spiRelTmp = SPIn->DR;
 }
#endif	/* STM32F1 || STM32F4 || STM32F7 */

#if defined(STM32H7)
 while ((SPIn->SR & SPI_SR_EOT) == 0) /* wait for end of transfer*/
  ;
#endif	/* STM32H7 */

#if defined(CYCLE_CTR)
 //uint32_t t = getCycles() - start;
#endif	/* CYCLE_CTR */

 SPIn->CR1 &= ~SPI_CR1_SPE;

 SPIn->CR1 |= SPI_CR1_SPE;

 SPI_SEL_GPIO_Port->BSRR = SPI_SEL_Pin;

#if defined(CYCLE_CTR)
 //printf("spirel %02x t %u\n", (unsigned int) SPIn->SR, (unsigned int) t);
#endif	/* CYCLE_CTR */
}

#endif	/* Sel_Pin */

#if defined(CS0_Pin) || defined(Sel_Pin)

void load(int dev, char addr, int32_t val)
{
// if (print & 8)
//  printf("load %x %x\n", (unsigned int) addr, (unsigned int) val);
//  char buf[8];
//  sprintf(buf, "lx %02x", addr);
//  dbgMsg(buf, val);
 spisel(dev);
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

 spirel(dev);
}

void loadb(int dev, char addr, char val)
{
// if (print & 8)
//  printf("load %02x %02x\n",
//  (unsigned int) addr, (unsigned int) val);
 spisel(dev);
 spisend(addr);
 spisend(val);
 spirel(dev);
}

char readb(int dev, char addr)
{
 spisel(dev);			/* select again */
 spisend(addr);			/* set read address */
 char rtnVal = spiread();
 spirel(dev);			/* and release */
 if (print & 8)
  printf("read %02x %02x\n",
	 (unsigned int) addr, (unsigned int) rtnVal);
 return(rtnVal);
}

int read16(int dev, char addr)
{
 spisel(dev);			/* select again */
 spisend(addr);			/* set read address */
 byte_long rtnVal;
 rtnVal.i = 0;
 rtnVal.b[1] = spiread();
 rtnVal.b[0] = spiread();
 spirel(dev);
 if (print & 8)
  printf("read %02x %04x\n",
	 (unsigned int) addr, (unsigned int) rtnVal.i);
 return(rtnVal.i);
}

int read24(int dev, char addr)
{
 spisel(dev);			/* select again */
 spisend(addr);			/* set read address */
 byte_long rtnVal;
 rtnVal.i = 0;
 rtnVal.b[2] = spiread();
 rtnVal.b[1] = spiread();
 rtnVal.b[0] = spiread();
 spirel(dev);
 if (print & 8)
  printf("read %02x %06x\n",
	 (unsigned int) addr, (unsigned int) rtnVal.i);
 return(rtnVal.i);
}

#endif	/* CS0_Pin || Sel_Pin */

#if defined(SPI_ISR)

#if defined SPI_SLAVE

extern "C" void spiISR()
{
 SPI_TypeDef *spi = SPIn;
 if (spi->SR & SPI_SR_RXNE)	/* if receive not empty */
 {
  char ch = spi->DR;
  if (spiCtl.state == 0)
  {
   if (ch == 1)
   {
    spiCtl.state = 1;
    if (spiCtl.txCount != 0)
    {
     spiCtl.txCount = 0;
     spiCtl.txFil = 0;
     spiCtl.txEmp = 0;
    }     
   }
  }

  if (spiCtl.state != 0)
  {
   if (spiCtl.rxCount < SPI_RX_SIZE)
   {
    int fil = spiCtl.rxFil;
    spiCtl.rxBuf[fil] = ch;
    fil += 1;
    if (fil >= SPI_RX_SIZE)
     fil = 0;
    spiCtl.rxFil = fil;
    spiCtl.rxCount += 1;
   }
 
   if (ch == '\r')
   {
    spiCtl.state = 0;
    remCmd(&spiAction);
    spi->CR2 |= SPI_CR2_TXEIE;
    spiCtl.txEna = 1;
   }
  }
 }

 if (spi->SR & SPI_SR_TXE)	/* if transmitter empty */
 {
  if ((spiCtl.txEna != 0)
  &&  (spiCtl.txCount > 0))
  {
   int emp = spiCtl.txEmp;
   spi->DR = spiCtl.txBuf[emp];
   emp += 1;
   if (emp >= SPI_TX_SIZE)
    emp = 0;
   spiCtl.txEmp = emp;
   spiCtl.txCount -= 1;
   if (spiCtl.txCount == 0)
    spiCtl.txEna = 0;
  }
  else
  {
   spi->DR = 0;
   spi->CR2 &= ~SPI_CR2_TXEIE;
  }
 }
}

#endif	/* SPI_SLAVE */

#if defined(SPI_MASTER)

void spiMasterStart()
{
 spiCtl.state = 0;
 spiCtl.timer = millis();
#if defined(STM32F4)
 SPIn->CR2 |= SPI_CR2_TXEIE | SPI_CR2_RXNEIE;
#endif
#if defined(STM32H7)
#endif
 SPIn->CR1 |= SPI_CR1_SPE;
 spiSelClr();
}

void spiMasterReset()
{
 spiSelSet();
 SPIn->CR1 &= ~SPI_CR1_SPE;
#if defined(STM32F4)
 SPIn->CR2 &= ~(SPI_CR2_TXEIE | SPI_CR2_RXNEIE);
#endif
 spiCtl.state = 0;
}

extern "C" void spiISR()
{
 dbgSpiIsrSet();
 SPI_TypeDef *spi = SPIn;
#if defined(STM32F4)
 if (spi->SR & SPI_SR_RXNE)	/* if receive not empty */
 {
  char ch = spi->DR;
  if (spiCtl.state == 0)
  {
   if (ch == '-')
   {
    spiCtl.state = 1;
   }
  }

  if (spiCtl.state != 0)
  {
   if (spiCtl.rxCount < SPI_RX_SIZE)
   {
    int fil = spiCtl.rxFil;
    spiCtl.rxBuf[fil] = ch;
    fil += 1;
    if (fil >= SPI_RX_SIZE)
     fil = 0;
    spiCtl.rxFil = fil;
    spiCtl.rxCount += 1;
   }
 
   if (ch == '*')
   {
    SPIn->CR1 &= ~SPI_CR1_SPE;
    SPIn->CR2 &= ~(SPI_CR2_TXEIE | SPI_CR2_RXNEIE);
    spiSelSet();
    spiCtl.state = 0;
    syncResp();
    //spiCtl.rxReady = 1;
   }
  }
 }

 if (spi->SR & SPI_SR_TXE)	/* if transmitter empty */
 {
  if (spiCtl.txCount > 0)
  {
   int emp = spiCtl.txEmp;
   spi->DR = spiCtl.txBuf[emp];
   emp += 1;
   if (emp >= SPI_TX_SIZE)
    emp = 0;
   spiCtl.txEmp = emp;
   spiCtl.txCount -= 1;
  }
  else
  {
   spi->DR = 0;
  }
 }
#endif
 dbgSpiIsrClr();
}

#endif	/* SPI_MASTER */

void putSPI(char ch)
{ 
 if (spiCtl.txCount < SPI_TX_SIZE)
 {
  int fil = spiCtl.txFil;
  spiCtl.txBuf[fil] = ch;
  fil += 1;
  if (fil >= SPI_TX_SIZE)
   fil = 0;
  spiCtl.txFil = fil;
  spiCtl.txCount += 1;
 }
}

int getSPI()
{
 int ch = -1;
 if (spiCtl.rxCount != 0)
 {
  int emp = spiCtl.rxEmp;
  ch = spiCtl.rxBuf[emp];
  emp += 1;
  if (emp >= SPI_RX_SIZE)
   emp = 0;
  spiCtl.rxEmp = emp;
  spiCtl.rxCount -= 1;
 }
 return(ch);
}

#endif	/* SPI_ISR */

#endif	/* __SPI__ */
