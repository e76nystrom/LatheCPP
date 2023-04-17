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

void info();
void bitState(const char *s, volatile uint32_t *p, uint32_t mask);

#if defined(ARDUINO_ARCH_STM32)
char query(unsigned char (*get)(), const char *format, ...);
#endif	/* ARDUINO_ARCH_STM32 */

#endif  /* STM32INFO_INC */	// ->
