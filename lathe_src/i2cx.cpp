//#if !defined(INCLUDE)
#define __I2C__
#include <stdio.h>
#include <limits.h>

#ifdef STM32F1
#include "stm32f1xx_hal.h"
#endif
#ifdef STM32F4
#include "stm32f4xx_hal.h"
#endif
#ifdef STM32H7
#include "stm32h7xx_hal.h"
#endif
#ifdef STM32F7
#include "stm32f7xx_hal.h"
#endif

#include "main.h"

#if defined(ARDUINO_ARCH_STM32)

#include "Arduino.h"
#include "serial.h"
#define flushBuf flush

#else  /* ARDUINO_ARCH_STM32 */

#if defined(STM32MON)

#include "current.h"
unsigned int millis(void);

#else  /* STM32MON */

#include "lathe.h"
#include "serialio.h"

#endif	/* STM32MON */

#endif	/* ARDUINO_ARCH_STM32 */

#if !defined(MAX_TIMEOUT)
#define MAX_TIMEOUT 100000
#endif	/* MAX_TIMEOUT */

#ifdef EXT
#undef EXT
#endif

#define EXT
#include "i2cx.h"
//#endif /* !defined(INCLUDE) */

#if  defined(__I2C_INC__)	// <-

#if !defined(EXT)
#define EXT extern
#endif

#if defined(STM32F4)
void i2cWrite(uint8_t);
#endif
void i2cWrite(uint8_t *data, uint16_t size);

void i2cWaitBusy(void);
void i2cPut(uint8_t ch);
void i2cPutString(uint8_t *p, int size);
void i2cSend(void);
void i2cControl(void);

enum I2C_STATES
{
 I_IDLE,                        /* 0 idle state */
 I_WAIT_START,			/* 1 wait for not busy to start */
 I_START,			/* 2 wait for start and send address */
 I_ADDRESS,			/* 3 wait for address and start data */
 I_SEND_DATA,			/* 4 send data */
 I_WAIT_DATA,			/* 5 wait for data to be sent */
 I_WAIT_STOP,			/* 6 wait for stop */
};

enum I2C_STATUS
{
 IS_DONE,			/* 0 done */
 IS_BUSY,			/* 1 busy */
 IS_TIMEOUT,			/* 2 timeout */
};

#define I2C_BUF_SIZE 256
#define I2C_TIMEOUT 500U

typedef struct
{
 int state;
 int lastState;
 int status;
 unsigned int startTime;
 unsigned int timeout;
 unsigned int maxTime;
 int fil;
 int emp;
 int count;
 uint8_t buffer[I2C_BUF_SIZE];
} T_I2C_CTL, *P_I2C_CTL;

EXT T_I2C_CTL i2cCtl;

#endif	// ->
#ifdef __I2C__

#if !defined(I2C_DEV)
#define I2C_DEV I2C1
#endif

I2C_TypeDef *i2cDev = I2C_DEV;

#if defined(STM32F1) || defined(STM32F4)
//void i2c_start(I2C_TypeDef* I2Cx, uint8_t address);

inline void i2c_SendData(I2C_TypeDef* I2Cx, uint8_t data)
{
 I2Cx->DR = data;
}

inline void i2c_stop(I2C_TypeDef* I2Cx)
{
 I2Cx->CR1 |= I2C_CR1_STOP;
}

inline bool i2cNotBusy()
{
 return((I2C_DEV->SR2 & I2C_SR2_BUSY) == 0);
}

inline bool i2cDataSent()
{
 return((I2C_DEV->SR1 == (I2C_SR1_BTF | I2C_SR1_TXE)) &&
	((I2C_DEV->SR2 & 0xff) == (I2C_SR2_MSL | I2C_SR2_BUSY | I2C_SR2_TRA)));
}
#endif	/* STM32F1 || STM32F4 */

#if defined(STM32H7) || defined(STM32F7)
inline void i2c_SendData(I2C_TypeDef* I2Cx, uint8_t data)
{
 I2Cx->TXDR = data;
}

#if 0
inline void i2c_stop(I2C_TypeDef* I2Cx)
{
}
#endif

inline void i2c_ResetCR2(I2C_TypeDef* I2Cx)
{
 I2Cx->CR2 &= ~((uint32_t)  (I2C_CR2_SADD | I2C_CR2_HEAD10R | I2C_CR2_NBYTES |
			     I2C_CR2_RELOAD | I2C_CR2_RD_WRN));
}

inline bool i2cNotBusy()
{
 return((I2C_DEV->ISR & I2C_ISR_BUSY) == 0);
}

inline bool i2cDataSent()
{
 return((I2C_DEV->ISR & I2C_ISR_TXIS) != 0);
}
#endif	/* STM32H7 */

#if defined(STM32F1) || defined(STM32F4)
#if 0
void i2c_start(I2C_TypeDef* I2Cx, uint8_t address)
{
 unsigned int timeout = 100 * (HAL_RCC_GetHCLKFreq() / 1000000);
 unsigned int start = getCycles();
 while ((I2Cx->SR2 & I2C_SR2_BUSY) != 0)
 {
  if ((getCycles() - start) > timeout)
  {
   printf("i2c_start busy timeout\n");
   return;
  }
 }
  
 I2Cx->CR1 |= I2C_CR1_START;
	  
 while ((I2Cx->SR1 & I2C_SR2_MSL) == 0) /* wait for master mode */
 {
  if ((getCycles() - start) > timeout)
  {
   printf("i2c_start master mode failed\n");
   return;
  }
 }
		
 address &= ~I2C_OAR1_ADD0;
 I2Cx->DR = address;
 while (1)
 {
  if ((I2Cx->SR1 == (I2C_SR1_ADDR | I2C_SR1_TXE))
  &&  ((I2Cx->SR2 & 0xff) == (I2C_SR2_MSL | I2C_SR2_BUSY | I2C_SR2_TRA)))
  {
   break;
  }
 }
}

void i2cWrite(uint8_t data)
{
 i2c_start(I2C_DEV, SLAVE_ADDRESS<<1);
 
 i2c_SendData(I2C_DEV, data);

 // wait for I2C1 EV8_2 --> byte has been transmitted
 // #define  I2C_EVENT_MASTER_BYTE_TRANSMITTED
 // ((uint32_t)0x00070084)  /* TRA, BUSY, MSL, TXE and BTF flags */
 while (1)
 {
  if ((I2C_DEV->SR1 == (I2C_SR1_BTF | I2C_SR1_TXE))
  &&  ((I2C_DEV->SR2 & 0xff) == (I2C_SR2_MSL | I2C_SR2_BUSY | I2C_SR2_TRA)))
  {
   break;
  }
 }

 i2c_stop(I2C_DEV);
}
#endif

void i2cWrite(uint8_t *data, uint16_t size)
{
 unsigned int timeout = 20;
 unsigned int start = millis();
 while ((I2C_DEV->SR2 & I2C_SR2_BUSY) != 0)
 {
  if ((millis() - start) > timeout)
  {
   printf("i2cWrite busy timeout\n");
   return;
  }
 }
  
 I2C_DEV->CR1 |= I2C_CR1_START;
	  
 while ((I2C_DEV->SR1 & I2C_SR2_MSL) == 0) /* wait for master mode */
 {
  if ((millis() - start) > timeout)
  {
   printf("i2cWrite master mode timeout\n");
   return;
  }
 }
		

 I2C_DEV->DR = SLAVE_ADDRESS<<1;

 while (1)
 {
  if ((I2C_DEV->SR1 == (I2C_SR1_ADDR | I2C_SR1_TXE))
  &&  ((I2C_DEV->SR2 & 0xff) == (I2C_SR2_MSL | I2C_SR2_BUSY | I2C_SR2_TRA)))
  {
   break;
  }
  if ((millis() - start) > timeout)
  {
   printf("i2cWrite address timeout\n");
   return;
  }
 }

 while (size > 0U)
 {
  size -= 1;
  i2c_SendData(I2C_DEV, *data++);

  while (1)
  {
   if ((I2C_DEV->SR1 == (I2C_SR1_BTF | I2C_SR1_TXE))
   &&  ((I2C_DEV->SR2 & 0xff) == (I2C_SR2_MSL | I2C_SR2_BUSY | I2C_SR2_TRA)))
   {
    break;
   }
   if ((millis() - start) > timeout)
   {
    printf("i2cWrite data timeout\n");
    return;
   }
  }
 }

 i2c_stop(I2C_DEV);
}

#endif	/* STM32F1 || STM32F4 */

#if defined(STM32H7) || defined(STM32F7)
void i2cWrite(uint8_t *data, uint16_t size)
{
 dbg4Set();
 unsigned int timeout = 20;
 unsigned int start = millis();
 while ((I2C_DEV->ISR & I2C_ISR_BUSY) != 0)
 {
  if ((millis() - start) > timeout)
  {
   printf("i2cWrite BUSY timeout\n");
   dbg4Clr();
   return;
  }
 }
  
 I2C_DEV->CR2 = (I2C_CR2_AUTOEND | (size << I2C_CR2_NBYTES_Pos) |
		 I2C_CR2_START | (SLAVE_ADDRESS<<1));
	  
 while (size > 0U)
 {
  size -= 1;
  while ((I2C_DEV->ISR & I2C_ISR_TXIS) == 0) /* wait for transmit done */
  {
   if ((millis() - start) > timeout)
   {
    printf("i2cWrite TXIS %08x\n", (unsigned int) I2C_DEV->ISR);
    dbg4Clr();
    return;
   }
  }

  I2C_DEV->TXDR = *data++;
 }

 while ((I2C_DEV->ISR & I2C_ISR_STOPF) == 0) /* wait for transmit done */
 {
  if ((millis() - start) > timeout)
  {
   printf("i2cWrite STOPF %08x\n", (unsigned int) I2C_DEV->ISR);
   dbg4Clr();
   return;
  }
 }

 
 i2c_ResetCR2(I2C_DEV);

 dbg4Clr();
}

#endif	/* STM32H7 */

void i2cWaitBusy(void)
{
 unsigned int timeout = 20;
 unsigned int start = millis();
 while (1)
 {
  if (i2cNotBusy())
   break;
  if ((millis() - start) > timeout)
  {
   printf("i2cWait BUSY timeout\n");
   return;
  }
 }
}

void i2cPut(uint8_t ch)
{
 P_I2C_CTL i2c = &i2cCtl;
 if (i2c->count < I2C_BUF_SIZE)
 {
  int fill = i2c->fil;		/* temp copy of fill pointer */
  i2c->buffer[fill++] = ch;	/* put character in buffer */
  if (fill >= I2C_BUF_SIZE)	/* if past end of buffer */
   fill = 0;			/* reset to zero */
  i2c->fil = fill;		/* save fill pointer */
  i2c->count++;			/* update count */
 }
}

void i2cPutString(uint8_t *p, int size)
{
 P_I2C_CTL i2c = &i2cCtl;
 if ((i2c->count + size) < I2C_BUF_SIZE) /* if string fits in buffer */
 {
  int fill = i2c->fil;		/* temp copy of fill pointer */
  uint8_t *dst = &i2c->buffer[fill]; /* get pointer to data buffer */
  // while (i2c->count < I2C_BUF_SIZE) /* if room */
  while (1)
  {
   --size;			/* count of size */
   if (size < 0)		/* if done */
    break;			/* exit */
   i2c->count++;		/* update count */
   *dst++ = *p++;		/* put character in buffer */
   fill++;			/* update index */
   if (fill >= I2C_BUF_SIZE)	/* if past end of buffer */
   {
    dst = i2c->buffer;		/* reset pointer */
    fill = 0;			/* reset to zero */
   }
  }
  i2c->fil = fill;		/* save index */
 }
}

void i2cSend(void)
{
 P_I2C_CTL i2c = &i2cCtl;
 i2c->timeout = I2C_TIMEOUT;
 i2c->startTime = millis();
 i2c->state = I_WAIT_START;
 i2c->status = IS_BUSY;
 i2c->lastState = I_IDLE;
}

void i2cControl(void)
{
 P_I2C_CTL i2c = &i2cCtl;

 if (i2c->state != I_IDLE)
 {
  unsigned int delta = millis() - i2c->startTime;
  if (delta > i2c->timeout)
  {
   printf("timeout\n");
   flushBuf();
#if defined(STM32F4)
   printf("state %d count %3d sr2 %08x sr1 %08x*\n",
	  i2c->state, i2c->count,
	  (unsigned int) I2C_DEV->SR2, (unsigned int) I2C_DEV->SR1);
#endif
#if defined(STM32H7) || defined(STM32F7)
  printf("state %d count %3d isr %08x*\n", i2c->state, i2c->count,
	 (unsigned int) I2C_DEV->ISR);
#endif
   flushBuf();
#if defined(STM32F4)
   i2c_stop(I2C_DEV);
#endif
   i2c->emp = 0;
   i2c->fil = 0;
   i2c->count = 0;
   i2c->state = I_IDLE;
   i2c->lastState = I_IDLE;
   i2c->status = IS_TIMEOUT;
   return;
  }
  if (delta > i2c->maxTime)
   i2c->maxTime = delta;
 }

#if 0
 if (i2c->state != i2c->lastState)
 {
  i2c->lastState = i2c->state;
#if defined(STM32F4)
  printf("state %d count %d sr2 %08x sr1 %08x\n", i2c->state, i2c->count,
	 (unsigned int) I2C_DEV->SR2, (unsigned int) I2C_DEV->SR1);
#endif
#if defined(STM32H7) || defined(STM32F7)
  printf("state %d count %d isr %08x*\n", i2c->state, i2c->count,
	 (unsigned int) I2C_DEV->ISR);
#endif
  flushBuf();
 }
#endif
 switch(i2c->state)		/* dispatch on state */
 {
 case I_IDLE:			/* 0x00 idle state */
  break;

 case I_WAIT_START:		/* 0x01 wait to start */
//  if ((I2C_DEV->SR2 & I2C_SR2_BUSY) == 0)
  if (i2cNotBusy())
  {
#if defined(STM32F4)
   I2C_DEV->CR1 |= I2C_CR1_START;
   i2c->state = I_START;
#endif
#if defined(STM32H7) || defined(STM32F7)
   I2C_DEV->CR2 = (I2C_CR2_AUTOEND | (i2c->count << I2C_CR2_NBYTES_Pos) |
		   I2C_CR2_START | (SLAVE_ADDRESS<<1));
   i2c->state = I_WAIT_DATA;
#endif
   i2c->startTime = millis();
  }
  break;

 case I_START:			/* 0x02 wait for start and send address */
#if defined(STM32F4)
  if ((I2C_DEV->SR1 == I2C_SR1_SB)
  &&  ((I2C_DEV->SR2 & 0xff) == (I2C_SR2_MSL | I2C_SR2_BUSY)))
  {
   I2C_DEV->DR = SLAVE_ADDRESS << 1;
   i2c->state = I_ADDRESS;
   i2c->startTime = millis();
  }
#endif
  break;

 case I_ADDRESS:		/* 0x03 wait for address and send data */
#if defined(STM32F4)
  if ((I2C_DEV->SR1 == (I2C_SR1_ADDR | I2C_SR1_TXE))
  &&  ((I2C_DEV->SR2 & 0xff) == (I2C_SR2_MSL | I2C_SR2_BUSY | I2C_SR2_TRA)))
  {
   i2c->state = I_SEND_DATA;
  }
#endif
  break;

 case I_SEND_DATA:		/* 0x04 send data */
  if (i2c->count != 0)
  {
   --i2c->count;
   int emp = i2c->emp;
#if defined(STM32F4)
   I2C_DEV->DR = i2c->buffer[emp++];
#endif
#if defined(STM32H7) || defined(STM32F7)
   I2C_DEV->TXDR = i2c->buffer[emp++];
#endif
   if (emp >= I2C_BUF_SIZE)
    emp = 0;
   i2c->emp = emp;
   i2c->startTime = millis();
#if defined(STM32F4)
   i2c->state = I_WAIT_DATA;
#endif
#if defined(STM32H7) || defined(STM32F7)
   if (i2c->count == 0)
    i2c->state = I_WAIT_STOP;
   else
    i2c->state = I_WAIT_DATA;
#endif
  }
#if defined(STM32F4)
  else
  {
   I2C_DEV->CR1 |= I2C_CR1_STOP;
   i2c->status = IS_DONE;
   i2c->timeout = MAX_TIMEOUT;
   i2c->state = I_IDLE;
  }
#endif
  break;

 case I_WAIT_DATA:		/* 0x05 wait for data to be send */
//  if ((I2C_DEV->SR1 == (I2C_SR1_BTF | I2C_SR1_TXE))
//  &&  ((I2C_DEV->SR2 & 0xff) == (I2C_SR2_MSL | I2C_SR2_BUSY | I2C_SR2_TRA)))
  if (i2cDataSent())
  {
   i2c->state = I_SEND_DATA;
  }
  break;

 case I_WAIT_STOP:		/* 0x06 wait for stop */
#if defined(STM32H7) || defined(STM32F7)
  if ((I2C_DEV->ISR & I2C_ISR_STOPF) != 0) /* it stopped */
  {
   i2c_ResetCR2(I2C_DEV);
   i2c->status = IS_DONE;
   i2c->timeout = MAX_TIMEOUT;
   i2c->state = I_IDLE;
  }
#endif
  break;
 }
}

#endif	/* __I2C__ */
