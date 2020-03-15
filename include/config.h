#if !defined(CONFIG)
#define CONFIG

#define DBGTRK 1
#define DBG_P     1		/* general debug */
#define DBG_SETUP 1		/* setup */
#define DBG_MOVOP 1		/* move operation */
#define DBG_QUE   1		/* que operation */
#define DBG_TMR   0		/* debug timers */
#define DBG_START 1		/* debug z and x start */
#define DBG_JOG   1		/* debug jogging */
#define DBG_DISABLE 0		/* disable debugging */
#define HOME_TEST 0		/* test homing without hardware */
#define PROBE_TEST 1		/* test probe without hardware */
#define SP_ENC 0		/* encode signals from spindle isr */
#define ACCEL_TIME 0		/* 0 - accel units/sec^2, 1 = accel time */

#define SPI_PIN 1 << 1
#define I2C_PIN 1 << 2
#define XILINX_PIN 0
#define DIR_PIN 0
#define OUT_PIN 0

//#define MIN_INDEX_RPM 60

//#define JTIMEINITIAL 0.75	/* initial jog time */
//#define JTIMEINC 0.15		/* incremental jog time */
//#define JTIMEMAX 1.0		/* maximum jog time */

#if 0

TIM1_BRK_TIM9_IRQHandler	/* 9 TIM1 Break and TIM9 */         
TIM1_UP_TIM10_IRQHandler	/* 1 & 10 TIM1 Update and TIM10 */         
TIM1_TRG_COM_TIM11_IRQHandler   /* 11 TIM1 Trigger, Commutation & TIM11 */
TIM1_CC_IRQHandler		/* TIM1 Capture Compare */
TIM2_IRQHandler			/* 2 TIM2 */
TIM3_IRQHandler			/* 3 TIM3 */
TIM4_IRQHandler			/* 4 TIM4 */
TIM5_IRQHandler			/* 5 TIM5 */
TIM6_DAC_IRQHandler		/* TIM6 and DAC1 & 2 underrun error */
TIM7_IRQHandler			/* 7 TIM7 */
TIM8_BRK_TIM12_IRQHandler	/* 12 TIM8 Break and TIM12 */
TIM8_UP_TIM13_IRQHandler	/* TIM8 Update and TIM13 */
TIM8_TRG_COM_TIM14_IRQHandler   /* TIM8 Trigger, Commutation & TIM14 */
TIM8_CC_IRQHandler		/* TIM8 Capture Compare */

#endif

/* timers

board	disc407	core407	num446	nuc401	nucBrd
step1	2	2	2	2	2
step2	5 | 1	5 | 1	5 | 1	5	5  | 1	jmp
step3	4	4	4	4	4
step4	3	3	3	1	3  | 1	jmp
step5	8	8	8	3 	8  | 3	sw
pwm	12	12	12	10	12 | 10 jmp
usec	6	6	6	10	6  | 10 sw
index	10	10	10	10	10
compare	9	9	9	9	9
int	11	11	11	11	11
enctst	7	7	7	1	7  | 1	sw

*/

#include "disc407.h"
#include "core407.h"
#include "nuc446.h"
#include "nuc401.h"
#include "nuc746.h"
#define SPINDLE_MICRO_STEPS 64
#define SPINDLE_MOTOR_STEPS 200

#define Z_LS_PITCH 0.1
#define Z_MICRO_STEPS 8
#define Z_MOTOR_STEPS 200

#define X_LS_PITCH 0.1
#define X_MICRO_STEPS 8
#define X_MOTOR_STEPS 200

#endif	/* defined(CONFIG) */
