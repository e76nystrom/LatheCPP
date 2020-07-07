#if !defined(INCLUDE)
#define __I2C__
#include <stdio.h>
#include <limits.h>

#include "../spl_include/stm32f4xx.h"
#include <stm32f4xx_i2c.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>

#define GPIO_PIN_0  ((uint16_t)0x0001U)  /* Pin 0 selected  */
#define GPIO_PIN_1  ((uint16_t)0x0002U)  /* Pin 1 selected  */
#define GPIO_PIN_2  ((uint16_t)0x0004U)  /* Pin 2 selected  */
#define GPIO_PIN_3  ((uint16_t)0x0008U)  /* Pin 3 selected  */
#define GPIO_PIN_4  ((uint16_t)0x0010U)  /* Pin 4 selected  */
#define GPIO_PIN_5  ((uint16_t)0x0020U)  /* Pin 5 selected  */
#define GPIO_PIN_6  ((uint16_t)0x0040U)  /* Pin 6 selected  */
#define GPIO_PIN_7  ((uint16_t)0x0080U)  /* Pin 7 selected  */
#define GPIO_PIN_8  ((uint16_t)0x0100U)  /* Pin 8 selected  */
#define GPIO_PIN_9  ((uint16_t)0x0200U)  /* Pin 9 selected  */
#define GPIO_PIN_10 ((uint16_t)0x0400U)  /* Pin 10 selected */
#define GPIO_PIN_11 ((uint16_t)0x0800U)  /* Pin 11 selected */
#define GPIO_PIN_12 ((uint16_t)0x1000U)  /* Pin 12 selected */
#define GPIO_PIN_13 ((uint16_t)0x2000U)  /* Pin 13 selected */
#define GPIO_PIN_14 ((uint16_t)0x4000U)  /* Pin 14 selected */
#define GPIO_PIN_15 ((uint16_t)0x8000U)  /* Pin 15 selected */

#include "main.h"
#include "lathe.h"
#include "serialio.h"

#ifdef EXT
#undef EXT
#endif

#define EXT
#include "latheI2C.h"
#endif	/* !defined(INCLUDE) */

#if  defined(__I2C_INC__)	// <-

#if !defined(EXT)
#define EXT extern
#endif

int i2c(void);
void initI2c(void);
void i2cWrite(uint8_t data);
void i2cSendData(uint8_t *data, int size);

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

#define I2C_BUF_SIZE 128
#define I2C_TIMEOUT 500U

typedef struct
{
 int state;
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

void i2c_start(I2C_TypeDef* I2Cx, uint8_t address, uint8_t direction);
void i2c_write(I2C_TypeDef* I2Cx, uint8_t data);
uint8_t i2c_read_ack(I2C_TypeDef* I2Cx);
uint8_t i2c_read_nack(I2C_TypeDef* I2Cx);
void i2c_stop(I2C_TypeDef* I2Cx);

#define SLAVE_ADDRESS 0x27 // the slave address (example)

void initI2c(void)
{
 GPIO_InitTypeDef GPIO_InitStruct;
 I2C_InitTypeDef I2C_InitStruct;
	
 // enable APB1 peripheral clock for I2C1
 RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);

#if 0
 // enable clock for SCL and SDA pins
 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
#endif

 GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
 GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
// GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
 GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;

 GPIO_InitStruct.GPIO_Pin = I2C_SCL_Pin;
 GPIO_Init(I2C_SCL_GPIO_Port, &GPIO_InitStruct);

 GPIO_InitStruct.GPIO_Pin = I2C_SDA_Pin;
 GPIO_Init(I2C_SDA_GPIO_Port, &GPIO_InitStruct);
	
 // Connect I2C1 pins to AF  
 GPIO_PinAFConfig(I2C_SCL_GPIO_Port, I2C_SCL_Pin, GPIO_AF_I2C1); // SCL
 GPIO_PinAFConfig(I2C_SDA_GPIO_Port, I2C_SDA_Pin, GPIO_AF_I2C1); // SDA

 // configure I2C1 
 // 100kHz
 I2C_InitStruct.I2C_ClockSpeed = 100000;
 // I2C mode
 I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
 // 50% duty cycle --> standard
 I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
 // own address, not relevant in master mode
 I2C_InitStruct.I2C_OwnAddress1 = 0x00;
 // disable acknowledge when reading (can be changed later on)
 I2C_InitStruct.I2C_Ack = I2C_Ack_Disable;
 // set address length to 7 bit addresses
 I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
 I2C_Init(I2C1, &I2C_InitStruct); // init I2C1
	
 // enable I2C1
 I2C_Cmd(I2C1, ENABLE);
}

/* This function issues a start condition and 
 * transmits the slave address + R/W bit
 * 
 * Parameters:
 * 		I2Cx --> the I2C peripheral e.g. I2C1
 * 		address --> the 7 bit slave address
 * 		direction --> the tranmission direction can be:
 *			I2C_Direction_Tranmitter for Master transmitter mode
 *			I2C_Direction_Receiver for Master receiver
 */

void i2c_start(I2C_TypeDef* I2Cx, uint8_t address, uint8_t direction)
{
 // wait until I2C1 is not busy anymore
 while (I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY))
  ;
  
 // Send I2C1 START condition 
 I2C_GenerateSTART(I2Cx, ENABLE);
	  
 // wait for I2C1 EV5 --> Slave has acknowledged start condition
 while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT))
  ;
		
 // Send slave Address for write 
 I2C_Send7bitAddress(I2Cx, address, direction);
	  
 /* wait for I2C1 EV6, check if 
  * either Slave has acknowledged Master transmitter or
  * Master receiver mode, depending on the transmission
  * direction
  */ 
 if (direction == I2C_Direction_Transmitter)
 {
  while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
   ;
 }
 else if (direction == I2C_Direction_Receiver)
 {
  while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
   ;
 }
}

/* This function transmits one byte to the slave device
 * Parameters:
 *		I2Cx --> the I2C peripheral e.g. I2C1 
 *		data --> the data byte to be transmitted
 */

void i2c_write(I2C_TypeDef* I2Cx, uint8_t data)
{
 I2C_SendData(I2Cx, data);

 // wait for I2C1 EV8_2 --> byte has been transmitted
 while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  ;
}

/* This function reads one byte from the slave device 
 * and acknowledges the byte (requests another byte)
 */

uint8_t i2c_read_ack(I2C_TypeDef* I2Cx)
{
 // enable acknowledge of recieved data
 I2C_AcknowledgeConfig(I2Cx, ENABLE);

 // wait until one byte has been received
 while ( !I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED) )
  ;

 // read data from I2C data register and return data byte
 uint8_t data = I2C_ReceiveData(I2Cx);
 return data;
}

/* This function reads one byte from the slave device
 * and doesn't acknowledge the recieved data 
 */

uint8_t i2c_read_nack(I2C_TypeDef* I2Cx)
{
 // disabe acknowledge of received data
 // nack also generates stop condition after last byte received
 // see reference manual for more info
 I2C_AcknowledgeConfig(I2Cx, DISABLE);

 I2C_GenerateSTOP(I2Cx, ENABLE);

 // wait until one byte has been received
 while ( !I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED) )
  ;

 // read data from I2C data register and return data byte
 uint8_t data = I2C_ReceiveData(I2Cx);
 return data;
}

/* This funtion issues a stop condition and therefore
 * releases the bus
 */

void i2c_stop(I2C_TypeDef* I2Cx)
{
 // Send I2C1 STOP Condition 
 I2C_GenerateSTOP(I2Cx, ENABLE);
}

void i2cWrite(uint8_t data)
{
 // start a transmission in Master transmitter mode
 i2c_start(I2C1, SLAVE_ADDRESS<<1, I2C_Direction_Transmitter);

 I2C_SendData(I2C1, data);

 // wait for I2C1 EV8_2 --> byte has been transmitted
 while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
  ;

 // stop the transmission
 i2c_stop(I2C1);
}

void i2cSendData(uint8_t *data, int size)
{
 if (size != 0)
 {
  // start a transmission in Master transmitter mode
  i2c_start(I2C1, SLAVE_ADDRESS<<1, I2C_Direction_Transmitter);

  while (--size >= 0)
   i2c_write(I2C1, *data++);

  // stop the transmission
  i2c_stop(I2C1);
 }
}

int i2c(void)
{
// initI2c(); // initialize I2C peripheral
	
 // start a transmission in Master transmitter mode
 i2c_start(I2C1, SLAVE_ADDRESS<<1, I2C_Direction_Transmitter);

 // write one byte to the slave
 i2c_write(I2C1, 0x20);

 // write another byte to the slave
 i2c_write(I2C1, 0x03);

 // stop the transmission
 i2c_stop(I2C1);

 return(0);
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
}

void i2cControl(void)
{
 P_I2C_CTL i2c = &i2cCtl;

 if (i2c->state != I_IDLE)
 {
  unsigned int delta = millis() - i2c->startTime;
  if (delta > i2c->timeout)
  {
   printf("state %d count %d sr2 %08x sr1 %08x*\n",
	  i2c->state, i2c->count, I2C1->SR2, I2C1->SR1);
   flushBuf();
   printf("timeout\n");
   flushBuf();
   I2C1->CR1 |= I2C_CR1_STOP;
   i2c->emp = 0;
   i2c->fil = 0;
   i2c->count = 0;
   i2c->state = I_IDLE;
   i2c->status = IS_TIMEOUT;
   return;
  }
  if (delta > i2c->maxTime)
   i2c->maxTime = delta;
 }

#if 0
 printf("state %d count %d sr2 %08x sr1 %08x*\n",
	i2c->state, i2c->count, I2C1->SR2, I2C1->SR1);
 flushBuf();
#endif
 switch(i2c->state)		/* dispatch on state */
 {
 case I_IDLE:			/* 0x00 idle state */
  break;

 case I_WAIT_START:		/* 0x01 wait to start */
  if ((I2C1->SR2 & I2C_SR2_BUSY) == 0)
  {
   I2C1->CR1 |= I2C_CR1_START;
   i2c->state = I_START;
   i2c->startTime = millis();
  }
  break;

 case I_START:			/* 0x02 wait for start and send address */
  if ((I2C1->SR1 == I2C_SR1_SB)
  &&  ((I2C1->SR2 & 0xff) == (I2C_SR2_MSL | I2C_SR2_BUSY)))
  {
   I2C1->DR = SLAVE_ADDRESS << 1;
   i2c->state = I_ADDRESS;
   i2c->startTime = millis();
  }
  break;

 case I_ADDRESS:		/* 0x03 wait for address and send data */
  if ((I2C1->SR1 == (I2C_SR1_ADDR | I2C_SR1_TXE))
  &&  ((I2C1->SR2 & 0xff) == (I2C_SR2_MSL | I2C_SR2_BUSY | I2C_SR2_TRA)))
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
   I2C1->DR = i2c->buffer[emp++];
   if (emp >= I2C_BUF_SIZE)
    emp = 0;
   i2c->emp = emp;
   i2c->startTime = millis();
   i2c->state = I_WAIT_DATA;
  }
  else
  {
   I2C1->CR1 |= I2C_CR1_STOP;
   i2c->timeout = MAX_TIMEOUT;
   i2c->state = I_IDLE;
   i2c->status = IS_DONE;
  }
  break;

 case I_WAIT_DATA:		/* 0x05 wait for data to be send */
  if ((I2C1->SR1 == (I2C_SR1_BTF | I2C_SR1_TXE))
  &&  ((I2C1->SR2 & 0xff) == (I2C_SR2_MSL | I2C_SR2_BUSY | I2C_SR2_TRA)))
  {
   i2c->state = I_SEND_DATA;
  }
  break;
 }
}

#endif
