//******************************************************************************
#ifdef STM32F4
#include "stm32f4xx_hal.h"
#endif
#ifdef STM32F7
#include "stm32f7xx_hal.h"
#endif
#ifdef STM32H7
#include "stm32h7xx_hal.h"
#endif

#include "main.h"
#include "lathe.h"
#include "stm32Info.h"

#include "serialio.h"
#include "lclcmd.h"
#include "lclcmdX.h"
#include "remcmd.h"
#include "i2cx.h"
#include "lcd.h"
#include "spix.h"
#include "Xilinx.h"
#include "zcontrol.h"
#include "xcontrol.h"
#include "latheX.h"
#include "condef.h"

void mainLoopSetup(void);
extern "C" int16_t mainLoop(void);
extern "C" void hard_fault_handler_c (unsigned int * hardfault_args);

void lcdDisplay(void);
void pinDisplay(void);

typedef struct
{
 const char *name;
 GPIO_TypeDef *port;
 int pin;
} T_PINDEF, *P_PINDEF;

#define PIN(name, pin) {#name, pin ## _GPIO_Port, pin ## _Pin}
#define DBGPIN(name) {#name, name ## _GPIO_Port, name ## _Pin}

T_PINDEF pinDef[] =
{
 PIN(StepZ, Step1),
 PIN(DirZ, Dir1),
#ifdef Step2a_Pin
 PIN(StepX, Step2a),
#endif
#ifdef Step2_Pin
 PIN(StepX, Step2),
#endif
#ifdef Step2b_Pin
 PIN(Step2b, Step2b),
#endif
 PIN(DirX, Dir2),
 PIN(Step3, Step3),
 PIN(Dir3, Dir3),
 PIN(Step4, Step4),
 PIN(Dir4, Dir4),
 PIN(StepSp, Step5),
 PIN(DirSp, Dir5),

#ifdef Index1_Pin
 PIN(Index1, Index1),
#endif
#ifdef Index2_Pin
 PIN(Index2, Index2),
#endif
#ifdef Index_Pin
 PIN(Index, Index),
#endif

 PIN(Pin1,  Pin1),
 PIN(Pin14, Pin14),
 PIN(Pin16, Pin16),
 PIN(Pin17, Pin17),

 PIN(Pin10, Pin10),
 PIN(Pin11, Pin11),
 PIN(Pin12, Pin12),
 PIN(Pin13, Pin13),
 PIN(Pin15, Pin15),

 PIN(ExtInt, ExtInt),
 PIN(ZFlag, ZFlag),
 PIN(XFlag, XFlag),
 PIN(Encoder, Encoder),
#ifdef Exti2_Pin
 PIN(Exti2, Exti2),
#endif

 PIN(DbgTx, DbgTx),
 PIN(DbgRx, DbgRx),
 PIN(RemTx, RemTx),
 PIN(RemRx, RemRx),

 PIN(JogA1, JogA1),
 PIN(JogB1, JogB1),
 PIN(JogA2, JogA2),
 PIN(JogB2, JogB2),

#ifdef Led1_Pin
 PIN(Led1, Led1),
#endif
#ifdef Led2_Pin
 PIN(Led2, Led2),
#endif
#ifdef Led3_Pin
 PIN(Led3, Led3),
#endif

 PIN(ZA, ZA),
 PIN(ZB, ZB),
 PIN(XA, XA),
 PIN(XB, XB),

#ifdef SPI_SEL_Pin
 PIN(SPI_SEL, SPI_SEL),
#endif
#ifdef SPI_SCK_Pin
 PIN(SPI_SCK, SPI_SCK),
#endif
#ifdef SPI_MISO_Pin
 PIN(SPI_MISO, SPI_MISO),
#endif
#ifdef SPI_MOSI_Pin
 PIN(SPI_MOSI, SPI_MOSI),
#endif

#ifdef I2C_SCL_Pin
 PIN(I2C_SCL, I2C_SCL),
#endif
#ifdef I2C_SDA_Pin
 PIN(I2C_SDA, I2C_SDA),
#endif

#ifdef PinA1_Pin
 PIN(PinA1, PinA1),
#endif
#ifdef PinA2_Pin
 PIN(PinA2, PinA2),
#endif
#ifdef PinA3_Pin
 PIN(PinA3, PinA3),
#endif
#ifdef PinA4_Pin
 PIN(PinA4, PinA4),
#endif
#ifdef PinA1_Pin
 PIN(PinA5, PinA5),
#endif
#ifdef PinA6_Pin
 PIN(PinA6, PinA6),
#endif
#ifdef PinA7_Pin
 PIN(PinA7, PinA7),
#endif
#ifdef PinA8_Pin
 PIN(PinA8, PinA8),
#endif
#ifdef PinA9_Pin
 PIN(PinA9, PinA9),
#endif
#ifdef PinA10_Pin
 PIN(PinA10, PinA10),
#endif
#ifdef PinA11_Pin
 PIN(PinA11, PinA11),
#endif
#ifdef PinA12_Pin
 PIN(PinA12, PinA12),
#endif
#ifdef PinA13_Pin
 PIN(PinA13, PinA13),
#endif
#ifdef PinA14_Pin
 PIN(PinA14, PinA14),
#endif
#ifdef PinA15_Pin
 PIN(PinA15, PinA15),
#endif
#ifdef PinA16_Pin
 PIN(PinA16, PinA16),
#endif
#ifdef PinA17_Pin
 PIN(PinA17, PinA17),
#endif

#include "dbgPin.h"
};

#if I2C
extern int lcdRow;
unsigned int lcdDelayStart;
unsigned int lcdRetryDelay;
#endif
#define LCD_DELAY 50U
#define LCD_RETRY_DELAY 25U

#define DATA_SIZE 1

#if DATA_SIZE
extern char __bss_start__;
extern char __bss_end__;
extern char __data_start__;
extern char __data_end__;
extern char __stack;
extern char __Main_Stack_Limit;
#endif

void mainLoopSetup(void)
{
 flushBuf();

 TIM3_Init();
 printf("TIM3_Init done\n");
 flushBuf();

//#if defined(SPINDLE_TIM8) || defined(STEP5_TIM8)
 if constexpr (SPINDLE_TIMER == 8)
 {
  TIM8_Init();
  printf("TIM8_Init done\n");
  flushBuf();
 }
// #endif

 unsigned int tmrClkFreq = HAL_RCC_GetPCLK2Freq() * 2;

 /* initialize timer 11 as index timer */

 indexTmrCnt(65535);
 indexTmrSet(65535);

// #ifdef USEC_SHARED_INDEX
 if constexpr (USEC_TIMER == INDEX_TIMER)
 {
  indexTmrScl((tmrClkFreq / 1000000U) - 1); /* load scaler */
  indexFreq = 1000000U;
 }
// #else
 {
  indexTmrScl(0);
  indexFreq = tmrClkFreq;
 }
// #endif

 indexTrkFreq = indexFreq * 6;
 indexTmrClrIF();
 indexTmrSetIE();
 indexTmrInit();
 indexTmrStart();

// #ifdef USEC_TMR_TIM6

 /* init timer 6 for use as a usec timer */

 if constexpr (USEC_TIMER != INDEX_TIMER)
 {
  usecTmrInit();		/* init timer */
  usecTmrScl((tmrClkFreq / 1000000U) - 1); /* load scaler */
  usecTmrSet(65535);		/* set to maximum */
  usecTmrStart();		/* start */
 }

 if constexpr (0)
  testOutputs(0);
}

void mainLoopSetupX(void)
{
}

#define LED_DELAY 500

#ifdef STM32H7
extern UART_HandleTypeDef huart7;
extern UART_HandleTypeDef huart3;
#endif

#ifdef STM32H7
// Not defined in CMSIS 4.00 headers - check if defined
// to allow for possible correction in later versions

#if !defined DWT_LSR_Present_Msk
#define DWT_LSR_Present_Msk ITM_LSR_Present_Msk
#endif

#if !defined DWT_LSR_Access_Msk
#define DWT_LSR_Access_Msk ITM_LSR_Access_Msk
#endif

#define CoreDebug_DEMCR_TrcEna CoreDebug_DEMCR_TRCENA_Msk
#define DWT_LAR_KEY 0xC5ACCE55

void dwtAccessEnable(unsigned ena)
{
 uint32_t lsr = DWT->LSR;

 printf("lsr %08x\n", (unsigned int) lsr);

 CoreDebug->DEMCR |= CoreDebug_DEMCR_TrcEna;
 if ((lsr & DWT_LSR_Present_Msk) != 0)
 {
  if (ena)
  {
   if ((lsr & DWT_LSR_Access_Msk) != 0) //locked: access need unlock
   {
    DWT->LAR = DWT_LAR_KEY;
   }
  }
  else
  {
   if ((lsr & DWT_LSR_Access_Msk) == 0) //unlocked
   {
    DWT->LAR = 0;
   }
  }
 }
}

#endif

//#define main mainLoop

int16_t mainLoop(void)
{
 unsigned char ch;
 IRQn_Type extInt[] =
 {
  EXTI0_IRQn,
  EXTI1_IRQn,
  EXTI2_IRQn,
  EXTI3_IRQn,
  EXTI4_IRQn,
  EXTI9_5_IRQn,
  EXTI15_10_IRQn
 };

#ifdef Led1_Pin
 uint32_t ledUpdTime = millis();
 led1Set();
#endif

 startSet();

#if defined(STM32F4) || defined(STM32F7)
 DBGMCU->APB1FZ = DBGMCU_APB1_FZ_DBG_IWDG_STOP; /* stop wd on debug */
#endif
#if defined(STM32H7)
 printf("DWT_CTRL %x\n", (unsigned int) DWT->CTRL);
 dwtAccessEnable(1);
 resetCnt();
 startCnt();
 stopCnt();
 printf("cycles %u\n", getCycles());
 DBGMCU->APB1LFZ1 |= (DBGMCU_APB1LFZ1_DBG_TIM2 | DBGMCU_APB1LFZ1_DBG_TIM5 |
		      DBGMCU_APB1LFZ1_DBG_TIM6 | DBGMCU_APB1LFZ1_DBG_TIM12);
 DBGMCU->APB2FZ1 |= (DBGMCU_APB2FZ1_DBG_TIM8 | DBGMCU_APB2FZ1_DBG_TIM15 |
		     DBGMCU_APB2FZ1_DBG_TIM16 | DBGMCU_APB2FZ1_DBG_TIM17);
 DBGMCU->APB4FZ1 |= DBGMCU_APB4FZ1_DBG_IWDG1;

 printf("IDCODE   %08x CR %08x\n",
	(unsigned int) DBGMCU->IDCODE, (unsigned int) DBGMCU->CR);
 printf("APB3FZ1  %08x\n", (unsigned int) DBGMCU->APB3FZ1);
 printf("APB1LFZ1 %08x\n", (unsigned int) DBGMCU->APB1LFZ1);
 printf("APB1HFZ1 %08x\n", (unsigned int) DBGMCU->APB1HFZ1);
 printf("APB2FZ1  %08x\n", (unsigned int) DBGMCU->APB2FZ1);
 printf("APB4FZ1  %08x\n", (unsigned int) DBGMCU->APB4FZ1);
#endif

 IRQn_Type *p = extInt;		/* external interrupt list */
 int i = sizeof(extInt) / sizeof(IRQn_Type); /* sizeof list */
 while (--i >= 0)		/* while not at end of list */
  HAL_NVIC_DisableIRQ(*p++);	/* disable external interrupt */

#if REM_ISR
 initRem();
#else
 HAL_NVIC_DisableIRQ(REMOTE_IRQn);
#endif

 tpi = 0.0;
 zTaperDist = 0.0;
 taper = 0.0;
 zDist = 0;
 xDist = 0;

#ifdef STM32H7
 uint8_t startMsg[] = "start main loop\n\r";
 HAL_UART_Transmit(&huart3, startMsg, sizeof(startMsg), HAL_MAX_DELAY);
#endif

 initCharBuf();

 putstr("start main loop\n");
 #if DATA_SIZE
 unsigned int bss = (unsigned int) (&__bss_end__ - &__bss_start__);
 unsigned int data = (unsigned int) (&__data_end__ - &__data_start__);
 printf("data %u bss %u total %u\n", data, bss, data + bss);
 printf("stack %08x stackLimit %08x sp %08x\n",
	(unsigned int) &__stack, (unsigned int) &__Main_Stack_Limit,
	getSP());
 #endif

#ifdef STM32H7
 uint8_t remMsg[] = "start remcmd\n\r";
 HAL_UART_Transmit(&huart7, remMsg, sizeof(remMsg), HAL_MAX_DELAY);
#endif

 putstr1("start remcmd\n");
 unsigned int sysClock = HAL_RCC_GetSysClockFreq();
 unsigned int clockFreq = HAL_RCC_GetHCLKFreq();
 unsigned int FCY = HAL_RCC_GetPCLK2Freq() * 2;
 rVar.cfgFcy = FCY;
 clocksMin = (uint64_t) FCY * 60;
 printf("sys clock %u clock frequency %u FCY %u %x\n",
	sysClock, clockFreq, FCY, (unsigned int) &rVar.cfgFcy);
 printf("sysTick load %d\n", (int) SysTick->LOAD);

#if 1
 printf("spindle timer %d pwm %d\n", SPINDLE_TIMER, SPINDLE_TMR_PWM);
#else
 printf("spindle timer ");

#ifdef SPINDLE_TIM3
 printf("3 pwm ");
#endif
#ifdef SPINDLE_TIM8
 printf("8 pwm");
#endif

#ifdef SPINDLE_PWM1
 printf("1\n");
#endif
#ifdef SPINDLE_PWM2
 printf("2\n");
#endif
#ifdef SPINDLE_PWM3
 printf("3\n");
#endif
#ifdef SPINDLE_PWM4
 printf("4\n");
#endif
#endif

 pinDisplay();

 lcdActive = 0;
#if I2C
 lcdDelayStart = 0;
 lcdRetryDelay = 0;
#endif

 while (1)			/* main loop */
 {
  newline();
  while (1)			/* input background loop */
  {
#ifdef Led1_Pin
   uint32_t t = millis();
   if ((t - ledUpdTime) > LED_DELAY) /* if time to flash led */
   {
    ledUpdTime = t;
    if (led1Read())
     led1Clr();
    else
     led1Set();
   }
#endif

   if (rVar.setupDone)		/* setup complete */
   {
    if ((millis() - remcmdUpdateTime) > remcmdTimeout) /* if timed out */
    {
     remcmdTimeout = MAX_TIMEOUT; /* set to maximum */
#if 0
     allStop();			/* stop everything */
     clearAll();		/* clear everything */
#endif
     printf("remcmd timeout expired\n");
    }

    if (eStopIsSet())		/* if emergency stop */
    {
     if ((rVar.mvStatus & MV_ESTOP) != 0) /* if flag not set */
     {
      rVar.mvStatus |= MV_ESTOP; /* set estop flag */
      clearCmd();		/* stop everything */
     }
    }
    else			/* if estop input clear */
    {
     rVar.mvStatus &= ~MV_ESTOP; /* clear estop flag */
    }

    procMove();			/* process move command */

    if (rVar.cfgFpga == 0)
     axisCtl();			/* poll processor axis control routines */
    else
     axisCtlX();		/* poll xilinx axis control routines */

#if I2C
    if (lcdActive)
     lcdDisplay();
#endif
   }

   pollBufChar();		/* check for data to output */
   if (dbgRxReady())		/* if character available */
   {
    ch = dbgRxRead();		/* return it */
    if (ch == 0x11)		/* if xon */
     continue;			/* no echo */
    if (ch == 0x13)		/* if xoff */
     continue;			/* no echo */
    dbgTxSend(ch);		/* echo input */
    break;
   }

#if REM_ISR == 0
   if (remRxReady())		/* if character on remote link */
   {
    ch = remRxRead();		/* read character */
    if (ch == 1)		/* if control a */
    {
     remcmd();			/* process remote command */
    }
   }
   else
   {
    pollBufChar();		/* check for data to output */
    if (dbgRxReady())		/* if character available */
    {
     ch = dbgRxRead();		/* return it */
     if (ch == 3)		/* if control c */
     {
      setupDone = 1;		/* force setup done */
     }
    }
   }
#endif
  }

  flushBuf();
  if (rVar.cfgFpga == 0)
   lclcmd(ch);			/* local commands */
  else
   lclcmdX(ch);
  flushBuf();
#if REM_ISR == 0
  if (remcmdTimeout < UINT_MAX)
   remcmdUpdateTime = millis();
#endif
 }
}

#define CON_SIZE (sizeof(conDef) / sizeof(T_CONDEF))
#define CON_PINS (CON_SIZE / 2)

void pinDisplay(void)
{
 printf("CON_SIZE %d CON_PINS %d\n", CON_SIZE, CON_PINS);
 P_PINDEF pin = pinDef;
 for (unsigned int i = 0; i < (sizeof(pinDef) / sizeof(T_PINDEF)); i++)
 {
  char t0[8];
  T_PIN_NAME val;
  val = pinName(t0, pin->port, pin->pin);
//  printf("port %08x pin %08x gpio %c pin %2d\n",
//	 (unsigned int) pin->port, (unsigned int) pin->pin,
//	 val.port, val.num);

  P_CONDEF con = conDef;
  const char *connector = "";
  unsigned int j;
  for (j = 0; j < CON_SIZE; j++)
  {
   if ((val.port == con->port)
   &&  (val.num == con->pin))
   {
    connector = j < CON_PINS ? "L" : "R";
    if (j > CON_PINS)
     j -= CON_PINS;
    j += 1;
    break;
   }
   con++;
  }

  char t1[6];
  char t2[40];
  sprintf(t1, "%s %d", connector, j);
  printf("%-14s %-5s %-4s %s\n",
	 pin->name, t0, t1, gpioStr(t2, sizeof(t2), &val));
  flushBuf();
  pin++;
 }
}

/*
  01234567890123456789
  Z -00.0000 X -0.0000
  H          X -0.0000
  Z -00.0000 X -0.0000
  RPM 000 Pass 00/00 S
 */

void lcdDisplay(void)
{
#if I2C
 if (i2cCtl.state != I_IDLE)	/* if i2c active */
 {
  i2cControl();			/* call i2c control routine */
 }
 else
 {
  if (lcdDelayStart == 0)
  {
#if 1
   setCursor(0, lcdRow);
   lcdDelayStart = millis();
#else
   if (lcdRetryDelay == 0)
   {
    if (setCursor(0, lcdRow))
    {
    }
    else
    {
//     lcdRetryDelay = millis();
    }
    lcdDelayStart = millis();
   }
   else
   {
    if ((millis() - lcdRetryDelay) > LCD_RETRY_DELAY)
    {
     lcdRetryDelay = 0;
    }
   }
#endif
  }
  else
  {
   if ((millis() - lcdDelayStart) > LCD_DELAY)
   {
    char buf[32];
    switch(lcdRow)
    {
    case 0:
     sprintf(buf, "Z %8.4f X %7.4f",
	     ((float) (rVar.zLoc - rVar.zHomeOffset)) / zAxis.stepsInch,
	     ((float) (rVar.xLoc - rVar.xHomeOffset)) / xAxis.stepsInch);
     lcdRow = 1;
     break;

    case 1:
    {
     char h = rVar.xHomeStatus == HOME_SUCCESS ? 'H' : ' ';
     char p = rVar.cmdPaused ? 'P' : ' ';
     sprintf(buf, "%c%c         D %7.4f", h, p,
	     2.0 * fabsf(((float) (rVar.xLoc - rVar.xHomeOffset)) /
			 xAxis.stepsInch));
     if (rVar.cfgDro)
      lcdRow = 2;
     else
      lcdRow = 3;
    }
     break;

    case 2:
     if (rVar.cfgDro)
      sprintf(buf, "Z %8.4f X %7.4f",
	      ((float) (rVar.zDroLoc - rVar.zDroOffset)) / rVar.zDroCountInch,
	      ((float) xDro()) / rVar.xDroCountInch);
     lcdRow = 3;
     break;

    case 3:
    {
     int rpm;
     if (rVar.indexPeriod != 0)
      rpm = (int) (((float) rVar.cfgFcy / rVar.indexPeriod) * 60 + 0.5);
     else
      rpm = 0;
     char spring = ' ';
     if (springInfo)
     {
      if (springInfo & 0x100)
       spring = 'S';
      else
       spring = (springInfo & 0xff) + '0';
     }
     sprintf(buf, "RPM %3hu Pass %2hhu/%2hhu %c",
	     (uint16_t) rpm, (unsigned char) rVar.currentPass,
	     (unsigned char) rVar.totalPasses, spring);
    }
    lcdRow = 0;
    break;

    default:
     lcdRow = 0;
    }
    lcdString(buf);
    i2cSend();
    lcdDelayStart = 0;
   }
  }
 }
#endif
}

void hard_fault_handler_c (unsigned int * hardfault_args)
{
 unsigned int stacked_r0;
 unsigned int stacked_r1;
 unsigned int stacked_r2;
 unsigned int stacked_r3;
 unsigned int stacked_r12;
 unsigned int stacked_lr;
 unsigned int stacked_pc;
 unsigned int stacked_psr;

 stacked_r0 = ((unsigned long) hardfault_args[0]);
 stacked_r1 = ((unsigned long) hardfault_args[1]);
 stacked_r2 = ((unsigned long) hardfault_args[2]);
 stacked_r3 = ((unsigned long) hardfault_args[3]);

 stacked_r12 = ((unsigned long) hardfault_args[4]);
 stacked_lr = ((unsigned long) hardfault_args[5]);
 stacked_pc = ((unsigned long) hardfault_args[6]);
 stacked_psr = ((unsigned long) hardfault_args[7]);

 dbgBuffer = 0;

 printf("\n\n[Hard fault handler - all numbers in hex]\n");
 printf("R0 = %x\n", stacked_r0);
 printf("R1 = %x\n", stacked_r1);
 printf("R2 = %x\n", stacked_r2);
 printf("R3 = %x\n", stacked_r3);
 printf("R12 = %x\n", stacked_r12);
 printf("LR [R14] = %x  subroutine call return address\n", stacked_lr);
 printf("PC [R15] = %x  program counter\n", stacked_pc);
 printf("PSR = %x\n", stacked_psr);
 printf("BFAR = %x\n", (*((volatile unsigned int *) (0xE000ED38))));
 printf("CFSR = %x\n", (*((volatile unsigned int *) (0xE000ED28))));
 printf("HFSR = %x\n", (*((volatile unsigned int *) (0xE000ED2C))));
 printf("DFSR = %x\n", (*((volatile unsigned int *) (0xE000ED30))));
 printf("AFSR = %x\n", (*((volatile unsigned int *) (0xE000ED3C))));
 printf("SCB_SHCSR = %x\n", (unsigned int) SCB->SHCSR);

 while (1);
}

#if 0
 flushBuf();
 P_DBG d = dbgDef;
 for (unsigned int i = 0; i < (sizeof(dbgDef) / sizeof(T_DBG)); i++)
 {
  P_GPIO g = gpio;
  for (unsigned int j = 0; j < (sizeof(gpio) / sizeof(T_GPIO)); j++)
  {
   if (d->port == g->port)
   {
    int mask = 1;
    int k;
    for (k = 0; k < 15; k++)
    {
     if (mask == d->pin)
     {
      printf("dbg%d p%s%d\n", i, g->name, k);
      break;
     }
     mask <<= 1;
    }
    break;
   }
   g++;
  }
  d++;
 }
#endif
