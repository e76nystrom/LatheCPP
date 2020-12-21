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

#if !defined(I2C_DEV)
#define I2C_DEV I2C1
#endif

#if !defined(EXT)
#define EXT extern
#endif

void initI2c(void);
void i2cWrite(uint8_t data);

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

#if !defined(SLAVE_ADDRESS)
#define SLAVE_ADDRESS 0x27 // the slave address (example)
#endif	/* SLAVE_ADDRESS */

#endif	// ->
#ifdef __I2C__

#if defined(STM32F1) || defined(STM32F4)
void i2c_start(I2C_TypeDef* I2Cx, uint8_t address);

inline void i2c_SendData(I2C_TypeDef* I2Cx, uint8_t data)
{
 I2Cx->DR = data;
}

inline void i2c_stop(I2C_TypeDef* I2Cx)
{
 I2Cx->CR1 |= I2C_CR1_STOP;
}
#endif

#if defined(STM32H7)
void i2c_start(I2C_TypeDef* I2Cx, uint8_t address, int size);

inline void i2c_SendData(I2C_TypeDef* I2Cx, uint8_t data)
{
 I2Cx->TXDR = data;
}

inline void i2c_stop(I2C_TypeDef* I2Cx)
{
}

inline void i2c_ResetCR2(I2C_TypeDef* I2Cx)
{
 I2Cx->Instance->CR2 &= ~((uint32_t)
			  (I2C_CR2_SADD | I2C_CR2_HEAD10R | I2C_CR2_NBYTES |
			   I2C_CR2_RELOAD | I2C_CR2_RD_WRN)));
}
#endif	/* STM32H7 */

#if defined(STM32F1) || defined(STM32F4)
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
#endif	/* STM32F1 || STM32F4 */

#if defined(STM32H7)
void i2c_start(I2C_TypeDef* I2Cx, uint8_t address, int size)
{
 unsigned int timeout = 100 * (HAL_RCC_GetHCLKFreq() / 1000000);
 unsigned int start = getCycles();
 while ((I2Cx->ISR & I2C_ISR_BUSY) != 0)
 {
  if ((getCycles() - start) > timeout)
  {
   printf("i2c_start busy timeout\n");
   return;
  }
 }
  
 I2CX->CR2 = I2C_CR2_AUTOEND | (size << 16) | I2C_CR2_START | address;
	  
 while ((I2Cx->ISR & I2C_ISR_TXIS) == 0) /* wait for transmit done */
 {
  if ((getCycles() - start) > timeout)
  {
   printf("i2c_start master mode failed\n");
   return;
  }
 }
}

void i2cWrite(uint8_t data)
{
 i2c_start(I2C_DEV, SLAVE_ADDRESS<<1, size);
 
 i2c_SendData(I2C_DEV, data);

 while ((I2Cx->ISR & I2C_ISR_TXIS) == 0) /* wait for transmit done */
  ;

 i2c_ResetCR2(I2Cx)
}
#endif	/* STM32H7 */

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
 int fill = i2c->fil;		/* temp copy of fill pointer */
 uint8_t *dst = &i2c->buffer[fill]; /* get pointer to data buffer */
 while (i2c->count < I2C_BUF_SIZE) /* if room */
 {
  --size;			/* count of size */
  if (size < 0)			/* if done */
   break;			/* exit */
  i2c->count++;			/* update count */
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

void i2cSend(void)
{
 P_I2C_CTL i2c = &i2cCtl;
 i2c->timeout = I2C_TIMEOUT;
 i2c->startTime = millis();
 i2c->state = I_WAIT_START;
 i2c->status = IS_BUSY;
 i2c->lastState = I_IDLE;
}

#if defined(STM32F1) || defined(STM32F4)
void i2cControl(void)
{
 P_I2C_CTL i2c = &i2cCtl;

 if (i2c->state != I_IDLE)
 {
  unsigned int delta = millis() - i2c->startTime;
  if (delta > i2c->timeout)
  {
   printf("state %d count %d sr2 %08x sr1 %08x*\n",
	  i2c->state, i2c->count,
	  (unsigned int) I2C_DEV->SR2, (unsigned int) I2C_DEV->SR1);
   flushBuf();
   printf("timeout\n");
   flushBuf();
   i2c_stop(I2C_DEV);
//   I2C_DEV->CR1 |= I2C_CR1_STOP;
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
  printf("state %d count %d sr2 %08x sr1 %08x*\n",
	 i2c->state, i2c->count,
	 (unsigned int) I2C_DEV->SR2, (unsigned int) I2C_DEV->SR1);
  flushBuf();
 }
#endif
 switch(i2c->state)		/* dispatch on state */
 {
 case I_IDLE:			/* 0x00 idle state */
  break;

 case I_WAIT_START:		/* 0x01 wait to start */
  if ((I2C_DEV->SR2 & I2C_SR2_BUSY) == 0)
  {
   I2C_DEV->CR1 |= I2C_CR1_START;
   i2c->state = I_START;
   i2c->startTime = millis();
  }
  break;

 case I_START:			/* 0x02 wait for start and send address */
  if ((I2C_DEV->SR1 == I2C_SR1_SB)
  &&  ((I2C_DEV->SR2 & 0xff) == (I2C_SR2_MSL | I2C_SR2_BUSY)))
  {
   I2C_DEV->DR = SLAVE_ADDRESS << 1;
   i2c->state = I_ADDRESS;
   i2c->startTime = millis();
  }
  break;

 case I_ADDRESS:		/* 0x03 wait for address and send data */
  if ((I2C_DEV->SR1 == (I2C_SR1_ADDR | I2C_SR1_TXE))
  &&  ((I2C_DEV->SR2 & 0xff) == (I2C_SR2_MSL | I2C_SR2_BUSY | I2C_SR2_TRA)))
  {
   i2c->state = I_SEND_DATA;
  }
  break;
  /* fall through to send data */

 case I_SEND_DATA:		/* 0x04 send data */
  if (i2c->count != 0)
  {
   --i2c->count;
   int emp = i2c->emp;
   I2C_DEV->DR = i2c->buffer[emp++];
   if (emp >= I2C_BUF_SIZE)
    emp = 0;
   i2c->emp = emp;
   i2c->startTime = millis();
   i2c->state = I_WAIT_DATA;
  }
  else
  {
   I2C_DEV->CR1 |= I2C_CR1_STOP;
   i2c->timeout = MAX_TIMEOUT;
   i2c->state = I_IDLE;
   i2c->status = IS_DONE;
  }
  break;

 case I_WAIT_DATA:		/* 0x05 wait for data to be send */
  if ((I2C_DEV->SR1 == (I2C_SR1_BTF | I2C_SR1_TXE))
  &&  ((I2C_DEV->SR2 & 0xff) == (I2C_SR2_MSL | I2C_SR2_BUSY | I2C_SR2_TRA)))
  {
   i2c->state = I_SEND_DATA;
  }
  break;
 }
}
#endif	/* STM32F1 || STM32F4 */

#if defined(STM32H7)

#endif	/* STM32H7 */

#endif	/* __I2C__ */
