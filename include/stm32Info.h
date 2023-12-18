#if !defined(STM32INFO_INC)	// <-
#define STM32INFO_INC

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
void tmrInfo(TIM_TypeDef *tmr, int flag);
void extiInfo();
void usartInfo(USART_TypeDef *usart, const char *str);
void i2cInfo(I2C_TypeDef *i2c, const char *str);
void spiInfo(SPI_TypeDef *spi, const char *str);
void rccInfo();
void pwrInfo();
void adcInfo(ADC_TypeDef *adc, char n);
void bkpInfo();
void afioInfo();
void rtcInfo();
#if defined(STM32F1)
void dmaInfo(DMA_TypeDef *dma);
void dmaChannelInfo(DMA_Channel_TypeDef *dmaC, char n);
#endif

enum tmrFlags
{T_CR1, T_CR2, T_SMCR, T_DIER, T_SR, T_EGR,
 T_CCMR1, T_CCMR2, T_CCER, T_CNT, T_PSC, T_ARR, T_RCR,
 T_CCR1, T_CCR2, T_CCR3, T_CCR4, T_BDTR, T_DCR, T_DMAR,
 T_RESERVED1, T_CCMR3, T_CCR5, T_CCR6, T_AF1, T_AF2, T_TISEL
};

#define T_MASK(x) (1 << T_##x)
#define T_CHECK(flag, x) (flag & (1 << T_##x))
#define T_NL() {n += 1; if ((n & 1) == 0) printf("\n");}
#define T_PRT(t, str) printf("%-6s %8lx ", #str, t->str)

#define TIM15_MASK \
 (T_MASK(CR1) \
  | T_MASK(CR2) \
  | T_MASK(DIER) \
  | T_MASK(SR) \
  | T_MASK(CCMR1) \
  | T_MASK(CCER) \
  | T_MASK(CNT) \
  | T_MASK(PSC) \
  | T_MASK(ARR) \
  | T_MASK(CCR1) \
  )

#define TIM17_MASK \
 (T_MASK(CR1) \
  | T_MASK(CR2) \
  | T_MASK(DIER) \
  | T_MASK(SR) \
  | T_MASK(CCMR1) \
  | T_MASK(CCER) \
  | T_MASK(CNT) \
  | T_MASK(PSC) \
  | T_MASK(ARR) \
  | T_MASK(CCR1) \
  )

void info();
//void bitState(const char *s, volatile unsigned long *p, unsigned long mask);

#if defined(ARDUINO_ARCH_STM32)
char query(unsigned char (*get)(), const char *format, ...);
#endif	/* ARDUINO_ARCH_STM32 */

#endif  /* STM32INFO_INC */	// ->
