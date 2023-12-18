//#if !defined(INCLUDE)
#define __LCD__

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

#include <cstdio>
#include "i2cx.h"
#if !defined(ARDUINO_ARCH_STM32)
#include "config.h"
#include "serialio.h"
#endif	/* ARDUION_ARCH_STM32 */

#ifdef EXT
#undef EXT
#endif

#define EXT
#include "lcd.h"
#undef EXT

#if defined(ARDUINO_ARCH_STM32)

#define flushBuf flush

#undef EXT
#define EXT extern
#include "monitorSTM32.h"

#define SLAVE_ADDRESS 0x3f
#include "cyclectr.h"

#else  /* ARDUINO_ARCH_STM32 */

#if defined(STM32MON)

#define SLAVE_ADDRESS 0x3f
#include "cyclectr.h"

#else  /* STM32MON */

#include "lathe.h"

#endif	/* STM32MON */

#endif	/* ARDUINO_ARCH_STM32 */

#if defined(__LCD_INC__)	// <-

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCDX_5x8DOTS 0x00

// flags for backlight control
#define LCD_BACKLIGHT 0x08
#define LCD_NOBACKLIGHT 0x00

#define En 0b00000100 // Enable bit
#define Rw 0b00000010 // Read/Write bit
#define Rs 0b00000001 // Register select bit

void lcdInit();
void command(uint8_t val);
void pulseEnable(uint8_t val);

uint8_t *lcdWrite(uint8_t *buf, uint8_t data);
void lcdWrite(uint8_t data);
void setBacklight(int val);
void setCursor(uint8_t col, uint8_t row);
void setCursorBuf(uint8_t col, uint8_t row);
void lcdString(const char *str);

#endif	// ->
#ifdef __LCD__

uint8_t backLight;

//#if defined(STM32MON)
__STATIC_INLINE void delayUSecX(volatile uint32_t microseconds)
{
 uint32_t start = DWT->CYCCNT;
 microseconds *= (HAL_RCC_GetSysClockFreq() / 1000000);

 while ((DWT->CYCCNT - start) < microseconds)
  ;
#if 0
 uint32_t stop = DWT->CYCCNT;
 printf("delay %u start %u stop %u delta %u\n",
	(unsigned int) microseconds, (unsigned int) start,
	(unsigned int) stop, (unsigned int) (stop - start));
#endif
}
//#endif

void lcdInit()
{
 printf("lcdInit address %2x\n", (unsigned int) SLAVE_ADDRESS);
 flushBuf();
 startCnt();
 i2cError = 0;
 setBacklight(0);

 pulseEnable(LCD_FUNCTIONSET | LCD_8BITMODE);
 delayUSecX(4500);
 pulseEnable(LCD_FUNCTIONSET | LCD_8BITMODE);
 delayUSecX(200);
 pulseEnable(LCD_FUNCTIONSET | LCD_8BITMODE);
 delayUSecX(200);
 pulseEnable(LCD_FUNCTIONSET);
 delayUSecX(200);

 command(LCD_FUNCTIONSET | LCD_4BITMODE | LCD_2LINE | LCDX_5x8DOTS);
 delayUSecX(200);
 command(LCD_DISPLAYCONTROL | LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF);
 delayUSecX(200);
 command(LCD_CLEARDISPLAY);
 delayUSecX(200);
 setBacklight(1);
 command(LCD_ENTRYMODESET | LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT);
 delayUSecX(200);
}

void pulseEnable(uint8_t val)
{
 // printf("pulseEnable %02x\n", val);
 uint8_t tmp = val | LCD_BACKLIGHT;
 uint8_t buf[2];
 buf[0] = tmp | En;
 buf[1] = tmp & ~En;
 i2cWrite(buf, (unsigned long) sizeof(buf));
 i2cWaitBusy();
 }

void command(uint8_t val)
{
 // printf("command %02x\n", val);
 uint8_t tmp;
 uint8_t buf[4];
 tmp = (val & 0xf0) | LCD_BACKLIGHT;
 buf[0] = tmp | En;
 buf[1] = tmp & ~En;
 tmp = (val << 4) | LCD_BACKLIGHT;;
 buf[2] = tmp | En;
 buf[3] = tmp & ~En;
 i2cWrite(buf, (unsigned long) sizeof(buf));
 i2cWaitBusy();
}

uint8_t *lcdWrite(uint8_t *buf, uint8_t data)
{
 uint8_t tmp = (data & 0xf0) | LCD_BACKLIGHT;
 *buf++ = tmp | En;
 *buf++ = tmp & ~En;
 tmp = ((data << 4) & 0xf0) | LCD_BACKLIGHT;
 *buf++ = tmp | En;
 *buf++ = tmp & ~En;
  return(buf);
}

void lcdWrite(uint8_t data)
{
 uint8_t tmp = (data & 0xf0) | LCD_BACKLIGHT;
 i2cPut(tmp | En);
 i2cPut(tmp & ~En);
 tmp = ((data << 4) & 0xf0) | LCD_BACKLIGHT;
 i2cPut(tmp | En);
 i2cPut(tmp & ~En);
}

void setBacklight(int val)
{
 backLight = val ? LCD_BACKLIGHT : LCD_NOBACKLIGHT;
}

void setCursor(uint8_t col, uint8_t row)
{
 const char rowOffset[] = {0x00, 0x40, 0x14, 0x54};
 if (row >= 4)
  row = 3;
 command(LCD_SETDDRAMADDR | (col + rowOffset[row]));
}

void setCursorBuf(uint8_t col, uint8_t row)
{
 const char rowOffset[] = {0x00, 0x40, 0x14, 0x54};
 if (row >= 4)
  row = 3;
 lcdWrite(LCD_SETDDRAMADDR | (col + rowOffset[row]));
}

void lcdString(const char *str)
{
 uint8_t buf[80];
 uint8_t ch;
 uint8_t *p = buf;
 while (true)
 {
  ch = *str++;
  if (ch == 0)
   break;
  uint8_t tmp = (ch & 0xf0) | Rs | backLight;
  *p++ = tmp | En;
  *p++ = tmp;
  tmp = (ch << 4) | Rs | backLight;
  *p++ = tmp | En;
  *p++ = tmp;
 }
 i2cPutString(buf, p - buf);
}

#endif
