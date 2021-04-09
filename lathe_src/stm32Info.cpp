#define __STM32INFO__
#include <stdio.h>

#if defined(STM32F1)
#include "stm32f1xx_hal.h"
#endif
#if defined(STM32F3)
#include "stm32f3xx_hal.h"
#endif
#if defined(STM32F4)
#include "stm32f4xx_hal.h"
#endif
#if defined(STM32F7)
#include "stm32f7xx_hal.h"
#endif
#if defined(STM32H7)
#include "stm32h7xx_hal.h"
#endif

#include "stm32Info.h"

#if defined(ARDUINO_ARCH_STM32)
#include "monitorSTM32.h"
#define flushBuf flush
#define newline newLine
#else
#include "config.h"
#include "serialio.h"
#define getNum getnum
#endif	/* ARDUINO_ARCH_AVR */

#if  defined(__STM32INFO_INC__)	// <-

typedef struct
{
 union
 {
  struct
  {
   char port;
   char num;
  };
  struct
  {
   uint16_t pinName;
  };
 };
} T_PIN_NAME;

T_PIN_NAME pinName(char *buf, GPIO_TypeDef *port, int pin);
char portName(GPIO_TypeDef *port);
#if defined(STM32F4) || defined(STM32F7) || defined(STM32H7)
char *gpioStr(char *buf, int size, T_PIN_NAME *pinInfo);
#endif
void gpioInfo(GPIO_TypeDef *gpio);
void tmrInfo(TIM_TypeDef *tmr);
void extiInfo(void);
void usartInfo(USART_TypeDef *usart, const char *str);
void i2cInfo(I2C_TypeDef *i2c, const char *str);
void rccInfo(void);
void pwrInfo(void);
void adcInfo(ADC_TypeDef *adc, char n);
void bkpInfo(void);
void afioInfo(void);
void rtcInfo(void);
#if defined(STM32F1)
void dmaInfo(DMA_TypeDef *dma);
void dmaChannelInfo(DMA_Channel_TypeDef *dmaC, char n);
#endif

void info(void);
void bitState(const char *s, volatile uint32_t *p, uint32_t mask);

#if defined(ARDUINO_ARCH_STM32)
char query(unsigned char (*get)(), const char *format, ...);
#endif	/* ARDUINO_ARCH_STM32 */

#endif	// ->
#ifdef __STM32INFO__

uint32_t lastFlags;

typedef struct
{
 GPIO_TypeDef *port;
 char name;
} T_GPIO, *P_GPIO;

T_GPIO gpio[] = 
{
 {GPIOA, 'A'},
 {GPIOB, 'B'},
 {GPIOC, 'C'},
#ifdef GPIOD
 {GPIOD, 'D'},
#endif
#ifdef GPIOE 
 {GPIOE, 'E'},
#endif
#ifdef GPIOF
 {GPIOF, 'F'},
#endif
#ifdef GPIOG
 {GPIOG, 'G'},
#endif
};

char portName(GPIO_TypeDef *port)
{
 for (unsigned int j = 0; j < sizeof(gpio) / sizeof(T_GPIO); j++)
 {
  if (port == gpio[j].port)
  {
   return(gpio[j].name);
  }
 }
 return('*');
}

T_PIN_NAME pinName(char *buf, GPIO_TypeDef *port, int pin)
{
 char pName = portName(port);
 T_PIN_NAME val;
 val.port = pName;
 int pinNum = 0;
 while (pin != 0)
 {
  if (pin & 1)
   break;
  pin >>= 1;
  pinNum++;
 }
 sprintf(buf, "P%c%d", pName, pinNum);
 val.num = pinNum;
 return(val);
}

#if defined(STM32F4) || defined(STM32F7) || defined(STM32H7)

char modeInfo[] = {'I', 'O', 'F', 'A'};
const char *typeInfo[] = {"PP", "OD", "  "};
const char *speedInfo[] = {"LS", "MS", "HS", "VH", "  "};
const char *pupdInfo[] = {"  ", "PU", "PD", "**"};

char *gpioStr(char *buf, int size, T_PIN_NAME *pinInfo)
{
 buf[0] = 0;
 GPIO_TypeDef *port;
 for (unsigned int j = 0; j < sizeof(gpio) / sizeof(T_GPIO); j++)
 {
  if (gpio[j].name == pinInfo->port)
  {
   port = gpio[j].port;
   int pin = pinInfo->num;
//   printf("port  %08x %2d %c %2d\n", (unsigned int) port, pin,
//	  pinInfo->port, pinInfo->num);

   int mode = (port->MODER >> (pin << 1)) & 3;
//   printf("mode  %08x %d\n", (unsigned int) port->MODER, mode);

   int outType = (port->OTYPER >> pin) & 1;
//   printf("type  %08x %d\n", (unsigned int) port->OTYPER, outType);

   int outSpeed = (port->OSPEEDR >> (pin << 1)) & 3;
//   printf("speed %08x %d\n", (unsigned int) port->OSPEEDR, outSpeed);

   int pupd = (port->PUPDR >> (pin << 1)) & 3;
//   printf("pupd  %08x %d\n", (unsigned int) port->PUPDR, pupd);

   int afr = (port->AFR[pin >> 3] >> ((pin << 2) & 0x1f)) & 0xf;

   char interrupt = ' ';
   if (mode == GPIO_MODE_INPUT)
   {
    outType = (sizeof(typeInfo) / sizeof(char *)) - 1;
    outSpeed = (sizeof(speedInfo) / sizeof(char *)) - 1;

    if ((EXTI->IMR >> pin) & 1)
    {
     int exti = (SYSCFG->EXTICR[pin >> 2] >> ((pin << 2) & 0xf)) & 0xf;
     if ((pinInfo->port - 'A') == exti)
      interrupt = 'I';
//     printf("exti %2d pinInfo->port - 'A' %d pin >> 2 %d pin << 2 %d\n",
//	    exti, pinInfo->port - 'A', pin >> 2, pin << 2);
    }
   }

//   printf("afr   %08x %d (pin >> 3) %d ((pin << 2) & 0x1f) %2d\n",
//	  (unsigned int) port->AFR[pin >> 3], afr,
//	  (pin >> 3), ((pin << 2) & 0x1f));
//   flushBuf();

   snprintf(buf, size, "%c %c %2s %2s %2s %2d",
	    interrupt, modeInfo[mode], typeInfo[outType],
	    speedInfo[outSpeed], pupdInfo[pupd], afr);
   break;
  }
 }
 return(buf);
}

#endif

void gpioInfo(GPIO_TypeDef *gpio)
{
 printf("gpio %x %c\n", (unsigned int) gpio, portName(gpio));
#if defined(STM32F3) || defined(STM32F4)
 printf("MODER   %8x ", (unsigned int) gpio->MODER);
 printf("OTYPER  %8x\n", (unsigned int) gpio->OTYPER);
 printf("OSPEEDR %8x ", (unsigned int) gpio->OSPEEDR);
 printf("PUPDR   %8x\n", (unsigned int) gpio->PUPDR);
#endif	/* STM32F3 */
#if defined(STM32F1)
 printf("CRL     %8x ", (unsigned int) gpio->CRL);
 printf("CRH     %8x\n", (unsigned int) gpio->CRH);
#endif	/* STM32F1 */
 printf("IDR     %8x ", (unsigned int) gpio->IDR);
 printf("ODR     %8x\n", (unsigned int) gpio->ODR);
 printf("BSRR    %8x ", (unsigned int) gpio->BSRR);
 printf("LCKR    %8x\n", (unsigned int) gpio->LCKR);
#if defined(STM32F3) || defined(STM32F4)
 printf("AFR[0]  %8x ", (unsigned int) gpio->AFR[0]);
 printf("AFR[1]  %8x\n", (unsigned int) gpio->AFR[1]);
#endif	/* STM32F3 */
 int i;
 printf("         ");
 for (i = 0; i < 16; i++)
  printf(" %2d", i);

 int val;
 
#if defined(STM32F3) || defined(STM32F4)
 printf("\nmoder    ");
 val = gpio->MODER;
 for (i = 0; i < 16; i++)
  printf(" %2d", (val >> (2 * i)) & 0x3);

 printf("\notyper   ");
 val = gpio->OTYPER;
 for (i = 0; i < 16; i++)
  printf(" %2d", (val >> i) & 0x1);

 printf("\nopspeedr ");
 val = gpio->OSPEEDR;
 for (i = 0; i < 16; i++)
  printf(" %2d", (val >> (2 * i)) & 0x3);

 printf("\npupdr    ");
 val = gpio->PUPDR;
 for (i = 0; i < 16; i++)
  printf(" %2d", (val >> (2 * i)) & 0x3);
#endif	/* STM32F3 */

#if defined(STM32F1)
 printf("\nmode     ");
 val = gpio->CRL;
 for (i = 0; i < 8; i++)
  printf(" %2d", (val >> (4 * i)) & 0x3);

 val = gpio->CRH;
 for (i = 0; i < 8; i++)
  printf(" %2d", (val >> (4 * i)) & 0x3);

 printf("\ncnf      ");
 val = gpio->CRL;
 for (i = 0; i < 8; i++)
  printf(" %2d", (val >> ((4 * i) + 2)) & 0x3);

 val = gpio->CRH;
 for (i = 0; i < 8; i++)
  printf(" %2d", (val >> ((4 * i) + 2)) & 0x3);
#endif	/* STM32F1 */
 
 printf("\nidr      ");
 val = gpio->IDR;
 for (i = 0; i < 16; i++)
  printf(" %2d", (val >> i) & 0x1);

 printf("\nodr      ");
 val = gpio->ODR;
 for (i = 0; i < 16; i++)
  printf(" %2d", (val >> i) & 0x1);

#if defined(STM32F3) || defined(STM32F4)
 printf("\nafr      ");
 val = gpio->AFR[0];
 for (i = 0; i < 8; i++)
  printf(" %2d", (val >> (4 * i)) & 0xf);
 val = gpio->AFR[1];
 for (i = 0; i < 8; i++)
  printf(" %2d", (val >> (4 * i)) & 0xf);
#endif	/* STM32F3 */
 printf("\n");
 flushBuf();
}

#if 0
void gpioInfo(GPIO_TypeDef *gpio)
{
 printf("gpio %x %c\n",(unsigned int) gpio, portName(gpio));
#if defined(STM32F4)
 printf("MODER   %8x ",(unsigned int) gpio->MODER);
 printf("OTYPER  %8x\n",(unsigned int) gpio->OTYPER);
 printf("OSPEEDR %8x ",(unsigned int) gpio->OSPEEDR);
 printf("PUPDR   %8x\n",(unsigned int) gpio->PUPDR);
 printf("IDR     %8x ",(unsigned int) gpio->IDR);
 printf("ODR     %8x\n",(unsigned int) gpio->ODR);
 printf("BSRR    %8x ",(unsigned int) gpio->BSRR);
 printf("LCKR    %8x\n",(unsigned int) gpio->LCKR);
 printf("AFR[0]  %8x ",(unsigned int) gpio->AFR[0]);
 printf("AFR[1]  %8x\n",(unsigned int) gpio->AFR[1]);
 int i;
 printf("         ");
 for (i = 0; i < 16; i++)
  printf(" %2d", i);

 printf("\nmoder    ");
 int val = gpio->MODER;
 for (i = 0; i < 16; i++)
  printf(" %2d", (val >> (2 * i)) & 0x3);

 printf("\notyper   ");
 val = gpio->OTYPER;
 for (i = 0; i < 16; i++)
  printf(" %2d", (val >> i) & 0x1);

 printf("\nopspeedr ");
 val = gpio->OSPEEDR;
 for (i = 0; i < 16; i++)
  printf(" %2d", (val >> (2 * i)) & 0x3);

 printf("\npupdr    ");
 val = gpio->PUPDR;
 for (i = 0; i < 16; i++)
  printf(" %2d", (val >> (2 * i)) & 0x3);

 printf("\nidr      ");
 val = gpio->IDR;
 for (i = 0; i < 16; i++)
  printf(" %2d", (val >> i) & 0x1);

 printf("\nodr      ");
 val = gpio->ODR;
 for (i = 0; i < 16; i++)
  printf(" %2d", (val >> i) & 0x1);

 printf("\nafr      ");
 val = gpio->AFR[0];
 for (i = 0; i < 8; i++)
  printf(" %2d", (val >> (4 * i)) & 0xf);
 val = gpio->AFR[1];
 for (i = 0; i < 8; i++)
  printf(" %2d", (val >> (4 * i)) & 0xf);
#endif
 printf("\n");
 flushBuf();
}
#endif	/* 0 */

typedef struct
{
 TIM_TypeDef *tmr;
 char num;
} T_TIM, *P_TIM;

T_TIM tim[] =
{
 {TIM1,  1},
 {TIM2,  2},
 {TIM3,  3},
 {TIM4,  4},
#ifdef TIM5
 {TIM5,  5},
#endif
#ifdef TIM6
 {TIM6,  6},
#endif
#ifdef TIM7
 {TIM7,  7},
#endif
#ifdef TIM8
 {TIM8,  8},
#endif
#ifdef TIM9
 {TIM9,  9},
#endif
#ifdef TIM10
 {TIM10, 10},
#endif
#ifdef TIM11
 {TIM11, 11},
#endif
#ifdef TIM12
 {TIM12, 12},
#endif
#ifdef TIM13
 {TIM13, 13},
#endif
#ifdef TIM14
 {TIM14, 14},
#endif
};

char timNum(TIM_TypeDef *tmr);

char timNum(TIM_TypeDef *tmr)
{
 for (unsigned int j = 0; j < sizeof(tim) / sizeof(T_TIM); j++)
 {
  if (tmr == tim[j].tmr)
  {
   return(tim[j].num);
  }
 }
 return(0);
}

void tmrInfo(TIM_TypeDef *tmr)
{
 printf("tmr %x TIM%d\n",(unsigned int) tmr, timNum(tmr));
 printf("CR1   %8x ",(unsigned int) tmr->CR1);
 printf("CR2   %8x\n",(unsigned int) tmr->CR2);
 printf("SMCR  %8x ",(unsigned int) tmr->SMCR);
 printf("DIER  %8x\n",(unsigned int) tmr->DIER);
 printf("SR    %8x ",(unsigned int) tmr->SR);
 printf("EGR   %8x\n",(unsigned int) tmr->EGR);
 printf("CCMR1 %8x ",(unsigned int) tmr->CCMR1);
 printf("CCMR2 %8x\n",(unsigned int) tmr->CCMR2);
 printf("CCER  %8x ",(unsigned int) tmr->CCER);
 printf("CNT   %8x\n",(unsigned int) tmr->CNT);
 printf("PSC   %8x ",(unsigned int) tmr->PSC);
 printf("ARR   %8x\n",(unsigned int) tmr->ARR);
 printf("RCR   %8x ",(unsigned int) tmr->RCR);
 printf("CCR1  %8x\n",(unsigned int) tmr->CCR1);
 printf("CCR2  %8x ",(unsigned int) tmr->CCR2);
 printf("CCR3  %8x\n",(unsigned int) tmr->CCR3);
 printf("CCR4  %8x ",(unsigned int) tmr->CCR4);
 printf("BDTR  %8x\n",(unsigned int) tmr->BDTR);
 printf("DCR   %8x ",(unsigned int) tmr->DCR);
#if defined(__STM32F4xx_HAL_H) || defined(__STM32F7xx_HAL_H)
 printf("OR    %8x\n",(unsigned int) tmr->OR);
#endif
#if defined(STM32F1) ||  defined(STM32H7)
 newline();
#endif
 flushBuf();
}

void extiBit(const char *label, uint32_t val)
{
 printf("\n%6s", label);
 for (int i = 0; i <= 22; i++)
  printf(" %2d", (int) ((val >> i) & 0x1));
}

void extiInfo(void)
{
 printf("EXTI %x\n",(unsigned int) EXTI);
 int i;
 printf("      ");
 for (i = 0; i <= 22; i++)
  printf(" %2d", i);

#if defined(__STM32F4xx_HAL_H) || defined(__STM32F7xx_HAL_H)
 printf("\nIMR   ");
 int val = EXTI->IMR;
 for (i = 0; i <= 22; i++)
  printf(" %2d", (val >> i) & 0x1);

 printf("\nEMR   ");
 val = EXTI->EMR;
 for (i = 0; i <= 22; i++)
  printf(" %2d", (val >> i) & 0x1);

 printf("\nRTSR  ");
 val = EXTI->RTSR;
 for (i = 0; i <= 22; i++)
  printf(" %2d", (val >> i) & 0x1);

 printf("\nFTSR  ");
 val = EXTI->FTSR;
 for (i = 0; i <= 22; i++)
  printf(" %2d", (val >> i) & 0x1);

 printf("\nSWIER ");
 val = EXTI->SWIER;
 for (i = 0; i <= 22; i++)
  printf(" %2d", (val >> i) & 0x1);

 printf("\nPR    ");
 val = EXTI->PR;
 for (i = 0; i <= 22; i++)
  printf(" %2d", (val >> i) & 0x1);

 printf("\nSYSCFG %x\n",(unsigned int) SYSCFG);
 printf("      ");
 for (i = 0; i < 16; i++)
  printf(" %2d", i);

 printf("\nEXTICR");
 int mask = EXTI->IMR;
 for (i = 0; i < 4; i++)
 {
  val = SYSCFG->EXTICR[i];
  int j;
  for (j = 0; j < 4; j++)
  {
   printf("  %c", (mask & 1) ? 'a' + ((val >> (4 * j)) & 0xf) : ' ');
   mask >>= 1;
  }
 }
#endif
#if defined(STM32H743xx_H)
 extiBit("RTSR1", EXTI->RTSR1);
 extiBit("FTSR1", EXTI->FTSR1);
 extiBit("SWIER1", EXTI->SWIER1);
 extiBit("D3PMR1", EXTI->D3PMR1);
 extiBit("IMR1", EXTI->IMR1);
 extiBit("EMR1", EXTI->EMR1);
 extiBit("PR1", EXTI->PR1);
#endif
 printf("\n");
 flushBuf();
}

void usartInfo(USART_TypeDef *usart, const char *str)
{
 printf("usart %x %s\n",(unsigned int) usart, str);
#ifdef STM32F4
 printf("SR   %8x ",(unsigned int) usart->SR);
 printf("DR   %8x\n",(unsigned int) usart->DR);
#endif
#ifdef STM32F7
 printf("ISR  %8x ",(unsigned int) usart->ISR);
 printf("RDR  %8x\n",(unsigned int) usart->RDR);
#endif
 printf("BRR  %8x ",(unsigned int) usart->BRR);
 printf("CR1  %8x\n",(unsigned int) usart->CR1);
 printf("CR2  %8x ",(unsigned int) usart->CR2);
 printf("CR3  %8x\n",(unsigned int) usart->CR3);
 printf("GTPR %8x\n",(unsigned int) usart->GTPR);
 flushBuf();
}

#if 0
void i2cInfo(I2C_TypeDef *i2c, const char *str)
{
 printf("I2C %08x %s\n", (unsigned int) i2c, str);
 printf("CR1   %8x ", (unsigned int) i2c->CR1);
 printf("CR2   %8x\n", (unsigned int) i2c->CR2);
 printf("OAR1  %8x ", (unsigned int) i2c->OAR1);
 printf("OAR2  %8x\n", (unsigned int) i2c->OAR2);
 printf("SR1   %8x ", (unsigned int) i2c->SR1);
 printf("SR2   %8x\n", (unsigned int) i2c->SR2);
 printf("DR    %8x ", (unsigned int) i2c->DR);
 printf("CCR   %8x\n", (unsigned int) i2c->CCR);
 printf("TRISE %8x\n", (unsigned int) i2c->TRISE);
 flushBuf();
}
#endif

void i2cInfo(I2C_TypeDef *i2c, const char *str)
{
 printf("i2c %x %s\n",(unsigned int) i2c, str);
 printf("CR1      %8x ",  (unsigned int) i2c->CR1);
 printf("CR2      %8x\n", (unsigned int) i2c->CR2);
 printf("OAR1     %8x ",  (unsigned int) i2c->OAR1);
 printf("OAR2     %8x\n", (unsigned int) i2c->OAR2);
#if defined(STM32F1) || defined(STM32F3) || defined(STM32F4)
 printf("SR1      %8x ",  (unsigned int) i2c->SR1);
 printf("SR2      %8x\n", (unsigned int) i2c->SR2);
 printf("DR       %8x ",  (unsigned int) i2c->DR);
 printf("CCR      %8x\n", (unsigned int) i2c->CCR);
 printf("TRISE    %8x\n", (unsigned int) i2c->TRISE);
#endif
#ifdef STM32H7
 printf("TIMINGR  %8x ",  (unsigned int) i2c->TIMINGR);
 printf("TIMEOUTR %8x\n", (unsigned int) i2c->TIMEOUTR);
 printf("ISR      %8x ",  (unsigned int) i2c->ISR);
 printf("ICR      %8x\n", (unsigned int) i2c->ICR);
 printf("PECR     %8x\n", (unsigned int) i2c->PECR);
 printf("RXDR     %8x ",  (unsigned int) i2c->RXDR);
 printf("TXDR     %8x\n", (unsigned int) i2c->TXDR);
#endif
 flushBuf();
}

void rccInfo(void)
{
#if defined(STM32F1)
 printf("RCC %08x\n", (unsigned int) RCC);
 printf("CR       %8x ",  (unsigned int) RCC->CR);
 printf("CFGR     %8x\n", (unsigned int) RCC->CFGR);
 printf("APB2RSTR %8x ",  (unsigned int) RCC->APB2RSTR);
 printf("APB1RSTR %8x\n", (unsigned int) RCC->APB1RSTR);
 printf("APB2ENR  %8x ",  (unsigned int) RCC->APB2ENR);
 printf("APB1ENR  %8x\n", (unsigned int) RCC->APB1ENR);
 printf("CIR      %8x ",  (unsigned int) RCC->CIR);
 printf("AHBENR   %8x\n", (unsigned int) RCC->AHBENR);
 printf("BDCR     %8x ",  (unsigned int) RCC->BDCR);
 printf("CSR      %8x\n", (unsigned int) RCC->CSR);
#endif
#ifdef STM32F4
 printf("CR         %8x ",  (unsigned int) RCC->CR);
 printf("PLLCFGR    %8x\n", (unsigned int) RCC->PLLCFGR);

 printf("CFGR       %8x ",  (unsigned int) RCC->CFGR);
 printf("CIR        %8x\n", (unsigned int) RCC->CIR);

 printf("AHB1RSTR   %8x ",  (unsigned int) RCC->AHB1RSTR);
 printf("AHB2RSTR   %8x ",  (unsigned int) RCC->AHB2RSTR);
 printf("AHB3RSTR   %8x\n", (unsigned int) RCC->AHB3RSTR);

 printf("APB1RSTR   %8x ",  (unsigned int) RCC->APB1RSTR);
 printf("APB2RSTR   %8x\n", (unsigned int) RCC->APB2RSTR);

 printf("AHB1ENR    %8x ",  (unsigned int) RCC->AHB1RSTR);
 printf("AHB2ENR    %8x ",  (unsigned int) RCC->AHB1RSTR);
 printf("AHB3ENR    %8x\n", (unsigned int) RCC->AHB1RSTR);

 printf("APB1ENR    %8x ",  (unsigned int) RCC->APB1ENR);
 printf("APB2ENR    %8x\n", (unsigned int) RCC->APB2ENR);

 printf("AHB1LPENR  %8x ",  (unsigned int) RCC->AHB1LPENR);
 printf("AHB2LPENR  %8x ",  (unsigned int) RCC->AHB2LPENR);
 printf("AHB3LPENR  %8x\n", (unsigned int) RCC->AHB3LPENR);

 printf("APB1LPENR  %8x ",  (unsigned int) RCC->APB1LPENR);
 printf("APB2LPENR  %8x\n", (unsigned int) RCC->APB2LPENR);

 printf("BDCR       %8x ",  (unsigned int) RCC->BDCR);
 printf("CSR        %8x\n", (unsigned int) RCC->CSR);

 printf("SSCGR      %8x ",  (unsigned int) RCC->BDCR);
 printf("PLLI2SCFGR %8x\n", (unsigned int) RCC->CSR);
#endif
#ifdef STM32H7
 printf("CR         %8x ",  (unsigned int) RCC->CR);
 printf("HSICFGR    %8x\n", (unsigned int) RCC->HSICFGR);

 printf("CRRCR      %8x ",  (unsigned int) RCC->CRRCR);
 printf("CSICFGR    %8x ",  (unsigned int) RCC->CSICFGR);
 printf("CFGR       %8x\n", (unsigned int) RCC->CFGR);

 printf("D1CFGR     %8x ",  (unsigned int) RCC->D1CFGR);
 printf("D2CFGR     %8x ",  (unsigned int) RCC->D2CFGR);
 printf("D3CFGR     %8x\n", (unsigned int) RCC->D3CFGR);

 printf("PLLCKSELR  %8x ",  (unsigned int) RCC->PLLCKSELR);
 printf("PLLCFGR    %8x\n", (unsigned int) RCC->PLLCFGR);

 printf("PLL1DIVR   %8x ",  (unsigned int) RCC->PLL1DIVR);
 printf("PLL1FRACR  %8x\n", (unsigned int) RCC->PLL1FRACR);

 printf("PLL2DIVR   %8x ",  (unsigned int) RCC->PLL2DIVR);
 printf("PLL2FRACR  %8x\n", (unsigned int) RCC->PLL2FRACR);

 printf("PLL3DIVR   %8x ",  (unsigned int) RCC->PLL3DIVR);
 printf("PLL3FRACR  %8x\n", (unsigned int) RCC->PLL3FRACR);

 printf("D1CCIPR    %8x ",  (unsigned int) RCC->D1CCIPR);
 printf("D2CCIP1R   %8x ",  (unsigned int) RCC->D2CCIP1R);
 printf("D2CCIP2R   %8x ",  (unsigned int) RCC->D2CCIP2R);
 printf("D3CCIPR    %8x\n", (unsigned int) RCC->D3CCIPR);

 printf("CIER       %8x ",  (unsigned int) RCC->CIER);
 printf("CIFR       %8x\n", (unsigned int) RCC->CIFR);

 printf("CICR       %8x ",  (unsigned int) RCC->CICR);
 printf("BDCR       %8x ",  (unsigned int) RCC->BDCR);
 printf("CSR        %8x\n", (unsigned int) RCC->CSR);

 printf("AHB3RSTR   %8x ",  (unsigned int) RCC->AHB3RSTR);
 printf("AHB1RSTR   %8x ",  (unsigned int) RCC->AHB1RSTR);
 printf("AHB2RSTR   %8x\n", (unsigned int) RCC->AHB2RSTR);
 printf("AHB4RSTR   %8x ",  (unsigned int) RCC->AHB4RSTR);
 printf("APB3RSTR   %8x\n", (unsigned int) RCC->APB3RSTR);

 printf("APB1LRSTR  %8x ",  (unsigned int) RCC->APB1LRSTR);
 printf("APB1HRSTR  %8x ",  (unsigned int) RCC->APB1HRSTR);
 printf("APB2RSTR   %8x ",  (unsigned int) RCC->APB2RSTR);
 printf("APB4RSTR   %8x\n", (unsigned int) RCC->APB4RSTR);

 printf("GCR        %8x ",  (unsigned int) RCC->GCR);
 printf("D3AMR      %8x ",  (unsigned int) RCC->D3AMR);
 printf("RSR        %8x\n", (unsigned int) RCC->RSR);

 printf("AHB3ENR    %8x ",  (unsigned int) RCC->AHB3ENR);
 printf("AHB1ENR    %8x ",  (unsigned int) RCC->AHB1ENR);
 printf("AHB2ENR    %8x ",  (unsigned int) RCC->AHB2ENR);
 printf("AHB4ENR    %8x\n", (unsigned int) RCC->AHB4ENR);

 printf("APB3ENR    %8x ",  (unsigned int) RCC->APB3ENR);
 printf("APB1LENR   %8x ",  (unsigned int) RCC->APB1LENR);
 printf("APB1HENR   %8x\n", (unsigned int) RCC->APB1HENR);
 printf("APB2ENR    %8x ",  (unsigned int) RCC->APB2ENR);
 printf("APB4ENR    %8x\n", (unsigned int) RCC->APB4ENR);

 printf("AHB3LPENR  %8x ",  (unsigned int) RCC->AHB3LPENR);
 printf("AHB1LPENR  %8x ",  (unsigned int) RCC->AHB1LPENR);
 printf("AHB2LPENR  %8x ",  (unsigned int) RCC->AHB2LPENR);
 printf("AHB4LPENR  %8x ",  (unsigned int) RCC->AHB4LPENR);

 printf("APB3LPENR  %8x ",  (unsigned int) RCC->APB3LPENR);
 printf("APB1LLPENR %8x ",  (unsigned int) RCC->APB1LLPENR);
 printf("APB1HLPENR %8x\n", (unsigned int) RCC->APB1HLPENR);
 printf("APB2LPENR  %8x ",  (unsigned int) RCC->APB2LPENR);
 printf("APB4LPENR  %8x\n", (unsigned int) RCC->APB4LPENR);
 #endif
}

#if 0
void rccInfo()
{
 printf("RCC %08x\n", (unsigned int) RCC);
 printf("CR       %8x ",  (unsigned int) RCC->CR);
 printf("CFGR     %8x\n", (unsigned int) RCC->CFGR);
 printf("APB2RSTR %8x ",  (unsigned int) RCC->APB2RSTR);
 printf("APB1RSTR %8x\n", (unsigned int) RCC->APB1RSTR);
 printf("APB2ENR  %8x ",  (unsigned int) RCC->APB2ENR);
 printf("APB1ENR  %8x\n", (unsigned int) RCC->APB1ENR);
 printf("CIR      %8x ",  (unsigned int) RCC->CIR);
 printf("AHBENR   %8x\n", (unsigned int) RCC->AHBENR);
 printf("BDCR     %8x ",  (unsigned int) RCC->BDCR);
 printf("CSR      %8x\n", (unsigned int) RCC->CSR);
}
#endif

void adcInfo(ADC_TypeDef *adc, char n)
{
 printf("ADC%d %08x  DR %08x\n",
	n, (unsigned int) adc, (unsigned int) &adc->DR);
#if defined(STM32F1)
 printf("SR    %8x\n", (unsigned int) adc->SR);
 printf("CR1   %8x ", (unsigned int) adc->CR1);
 printf("CR2   %8x\n", (unsigned int) adc->CR2);
 printf("HTR   %8x ", (unsigned int) adc->HTR);
 printf("LTR   %8x\n", (unsigned int) adc->LTR);
 printf("L     %8x ", (unsigned int) ((adc->SQR1 >> 20) & 0xf));
 printf("DR    %8x\n", (unsigned int) adc->DR);
 int i;
 printf("     ");
 for (i = 0; i < 16; i++)
  printf(" %2d", i);
 printf("\n");

 printf("SMPR ");
 int32_t tmp = adc->SMPR2;
 for (i = 0; i < 10; i++)
 {
  printf(" %2u", (unsigned int) (tmp & 7));
  tmp >>= 3;
 }
 tmp = adc->SMPR1;
 for (i = 0; i < 6; i++)
 {
  printf(" %2u", (unsigned int) (tmp & 7));
  tmp >>= 3;
 }
 printf("\n");

 printf("SQR  ");
 tmp = adc->SQR3;
 for (i = 0; i < 6; i++)
 {
  printf(" %2u", (unsigned int) (tmp & 7));
  tmp >>= 5;
 }
 tmp = adc->SQR2;
 for (i = 0; i < 6; i++)
 {
  printf(" %2u", (unsigned int) (tmp & 7));
  tmp >>= 5;
 }
 tmp = adc->SQR1;
 for (i = 0; i < 4; i++)
 {
  printf(" %2u", (unsigned int) (tmp & 7));
  tmp >>= 5;
 }
 printf("\n");
#endif	/* STM32F1 */
#if defined(STM32F3)
 printf("ISR   %8x ", (unsigned int) adc->ISR);
 printf("IER   %8x\n", (unsigned int) adc->IER);
 printf("CR    %8x ", (unsigned int) adc->CR);
 printf("CFGR  %8x\n", (unsigned int) adc->CFGR);
 printf("CAL   %8x ", (unsigned int) adc->CALFACT);
 printf("DR    %8x\n", (unsigned int) adc->DR);
 int i;
 printf("     ");
 for (i = 0; i < 16; i++)
  printf(" %2d", i);
 printf("\n");

 printf("SMPR ");
 int32_t tmp = adc->SMPR1;
 for (i = 0; i < 10; i++)
 {
  printf(" %2u", (unsigned int) (tmp & 7));
  tmp >>= 3;
 }
 tmp = adc->SMPR2;
 for (i = 0; i < 9; i++)
 {
  printf(" %2u", (unsigned int) (tmp & 7));
  tmp >>= 3;
 }
 printf("\n");

 printf("SQR  ");
 tmp = adc->SQR1;
 for (i = 0; i < 6; i++)
 {
  printf(" %2u", (unsigned int) (tmp & 0xf));
  tmp >>= 6;
 }
 tmp = adc->SQR2;
 for (i = 0; i < 6; i++)
 {
  printf(" %2u", (unsigned int) (tmp & 0x4));
  tmp >>= 6;
 }
 tmp = adc->SQR3;
 for (i = 0; i < 6; i++)
 {
  printf(" %2u", (unsigned int) (tmp & 0xf));
  tmp >>= 6;
 }
 tmp = adc->SQR4;
 for (i = 0; i < 2; i++)
 {
  printf(" %2u", (unsigned int) (tmp & 0xf));
  tmp >>= 6;
 }
 printf("\n");
#endif	/* STM32F3 */
 flushBuf();
}

#if defined(SMT32F1)
void dmaInfo(DMA_TypeDef *dma)
{
 printf("DMA1 %08x\n", (unsigned int) dma);
 printf("ISR   %8x ", (unsigned int) dma->ISR);
 printf("IFCR  %8x\n", (unsigned int) dma->IFCR);
 flushBuf();
}
#endif

#if defined(STM32F1)
void dmaChannelInfo(DMA_Channel_TypeDef *dmaC, char n)
{
 printf("DMA_Channel%d %08x\n", n, (unsigned int) dmaC);
 printf("CCR   %8x ", (unsigned int) dmaC->CCR);
 printf("CNDTR %8x\n", (unsigned int) dmaC->CNDTR);
 printf("CPAR  %8x ", (unsigned int) dmaC->CPAR);
 printf("CMAR  %8x\n", (unsigned int) dmaC->CMAR);
 flushBuf();
}
#endif

void afioInfo(void)
{
#if defined(STM32F1)
 printf("AFIO %x\n", (unsigned int) AFIO);
 printf("EVCR      %8x ",  (unsigned int) AFIO->EVCR);
 printf("MAPR      %8x\n", (unsigned int) AFIO->MAPR);
 printf("EXTICR[0] %8x ",  (unsigned int) AFIO->EXTICR[0]);
 printf("EXTICR[1] %8x\n", (unsigned int) AFIO->EXTICR[1]);
 printf("EXTICR[2] %8x ",  (unsigned int) AFIO->EXTICR[2]);
 printf("EXTICR[3] %8x\n", (unsigned int) AFIO->EXTICR[3]);
 printf("MAPR2     %8x\n", (unsigned int) AFIO->MAPR2);
#endif
}

void bkpInfo(void)
{
#if defined(STM32F1)
 printf("BKP %x\n", (unsigned int) BKP);
 printf("RTCCR     %8x ",  (unsigned int) BKP->RTCCR);
 printf("CR        %8x\n", (unsigned int) BKP->CR);
 printf("CSR       %8x\n", (unsigned int) BKP->CSR);
#endif
}

void rtcInfo(void)
{
#if defined(STM32F1)
 printf("RTC %x\n", (unsigned int) RTC);
 printf("CRH       %8x ",  (unsigned int) RTC->CRH);
 printf("CRL       %8x\n", (unsigned int) RTC->CRL);
 printf("PRLH      %8x ",  (unsigned int) RTC->PRLH);
 printf("PRLL      %8x\n", (unsigned int) RTC->PRLL);
 printf("DIVH      %8x ",  (unsigned int) RTC->DIVH);
 printf("DIVL      %8x\n", (unsigned int) RTC->DIVL);
 printf("CNTH      %8x ",  (unsigned int) RTC->CNTH);
 printf("CNTL      %8x\n", (unsigned int) RTC->CNTL);
 printf("ALRH      %8x ",  (unsigned int) RTC->ALRH);
 printf("ALRL      %8x\n", (unsigned int) RTC->ALRL);
#endif
}

void pwrInfo(void)
{
 printf("PWR %x\n", (unsigned int) PWR);
#if defined(STM32F1) || defined(STM32F4)
 printf("CR        %8x ",  (unsigned int) PWR->CR);
 printf("CSR       %8x\n", (unsigned int) PWR->CSR);
#endif /* STM32F1 || STM32F4 */
#if defined(STM32H7)
 printf("CR1        %8x ",  (unsigned int) PWR->CR1);
 printf("CSR1       %8x\n", (unsigned int) PWR->CSR1);
 printf("CR2        %8x ",  (unsigned int) PWR->CR2);
 printf("CR3        %8x\n", (unsigned int) PWR->CR3);
 printf("CPUCR2     %8x ",  (unsigned int) PWR->CPUCR);
 printf("D3CR       %8x\n", (unsigned int) PWR->D3CR);
 printf("WKUPCR     %8x ",  (unsigned int) PWR->WKUPCR);
 printf("WKUPFR     %8x\n", (unsigned int) PWR->WKUPFR);
 printf("WKUPEPR    %8x\n", (unsigned int) PWR->WKUPEPR);
#endif /* STM32F7 */
}

#if defined(ARDUINO_ARCH_STM32)

extern unsigned char getNum();
extern int val;

char query(unsigned char (*get)(), const char *format, ...)
{
 va_list args;
 va_start(args, format);
 vprintf(format, args);
 va_end(args);
 flushBuf();
 char ch = get();
 newLine();
 return(ch);
}

#endif	/* ARDUINO_ARCH_STM32 */

void info()
{
 if (query(&getNum, " flag [0x%x]: ", lastFlags) == 0)
 {
  val = lastFlags;
 }
 else
 {
  lastFlags = val;
 }
 newline();
 flushBuf();
 if (val & 0x01)
  tmrInfo(TIM1);
#ifdef TIM2
 if (val & 0x02)
  tmrInfo(TIM2);
#endif
#ifdef TIM3
 if (val & 0x04)
  tmrInfo(TIM3);
#endif
#ifdef TIM4
 if (val & 0x08)
  tmrInfo(TIM4);
#endif
#ifdef TIM5
 if (val & 0x10)
  tmrInfo(TIM5);
#endif

 if (val & 0x20)
 {
#ifdef TIM6
  tmrInfo(TIM6);
#endif
#ifdef TIM7
  tmrInfo(TIM7);
#endif
 }

#ifdef TIM8
 if (val & 0x40)
  tmrInfo(TIM8);
#endif

 if (val & 0x80)
 {
#ifdef TIM9
  tmrInfo(TIM9);
#endif
#ifdef TIM15
  tmrInfo(TIM15);
#endif
 }

 if (val & 0x100)
 {
#ifdef TIM10
  tmrInfo(TIM10);
#endif
#ifdef TIM16
  tmrInfo(TIM16);
#endif
 }
  
 if (val & 0x200)
 {
#ifdef TIM11
  tmrInfo(TIM11);
#endif
#ifdef TIM17
  tmrInfo(TIM17);
#endif
 }
  
#ifdef TIM12
 if (val & 0x400)
  tmrInfo(TIM12);
#endif

 if (val & 0x800)		/* exti */
  extiInfo();

 if (val & 0x01000)
  gpioInfo(GPIOA);
 if (val & 0x02000)
  gpioInfo(GPIOB);
 if (val & 0x04000)
  gpioInfo(GPIOC);
#ifdef GPIOD
 if (val & 0x08000)
  gpioInfo(GPIOD);
#endif
#ifdef GPIOE
 if (val & 0x10000)
  gpioInfo(GPIOE);
#endif
#ifdef GPIOF
 if (val & 0x20000)
  gpioInfo(GPIOF);
#endif
#ifdef GPIOG
 if (val & 0x40000)
  gpioInfo(GPIOH);
#endif

 if (val & 0x100000)
  usartInfo(USART1, "DBG");
 if (val & 0x200000)
  usartInfo(USART3, "WIFI");

#ifdef I2C1
 if (val & 0x400000)
  i2cInfo(I2C1, "I2C1");
#endif

 if (val & 0x800000)
 {
  adcInfo(ADC1, '1');
  newline();
  adcInfo(ADC2, '2');
 }
 if (val & 0x1000000)
 {
  rtcInfo();
 }
 if (val & 0x2000000)
 {
  pwrInfo();
  newline();
  bkpInfo();
  newline();
  afioInfo();
 }
}

void bitState(const char *s, volatile uint32_t *p, uint32_t mask)
{
 printf("%s %c\n", s, ((*p & mask) == 0) ? '0' : '1');
}

#endif	/* __STM32INFO */
