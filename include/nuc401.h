#ifdef NUCLEO401

/*

 1    ZFlag PC10  1| 2 PC11 Pin15      1    JogB2 PC09  1| 2 PC08 Step5      1
 2       XB PC12  3| 4 PD02 Index1     2    Pin16 PB08  3| 4 PC06 RemTx      2
 3                5| 6                 3    Step3 PB09  5| 6 PC05 JogB1      3
 4                7| 8                 4                7| 8                 4
 5                9|10                 5                9|10                 5
 6               11|12                 6    Step1 PA05 11|12 PA12 Dir5       6
 7          PA13 13|14                 7    JogA2 PA06 13|14 PA11 Pin17      7
 8          PA14 15|16                 8    JogA1 PA07 15|16 PB12 XFlag      8
 9    Pin13 PA15 17|18                 9  I2C_Scl PB06 17|18                 9
10               19|20                10    RemRx PC07 19|20                10
 9  I2C_Sda PB07 21|22                 9    DbgTx PA09 21|22 PB02 Pin1       9
 8       XA PC13 23|24                 8 TIM1_CH1 PA08 23|24 PB01 Pin14      8
 7       ZA PC14 25|26                 7     Dir1 PB10 25|26 PB15 Dir4       7
 6       ZB PC15 27|28 PA00 Step2      6     Dir2 PB04 27|28 PB14 Dbg0       6
 5          PH00 29|30 PA01 ExtInt     5     Dir3 PB05 29|30 PB13 SPI_Sck    5
 4          PH01 31|32 PA04 Index2     4          PB03 31|32                 4
 3               33|34 PB00 Step4      3    DbgRx PA10 33|34 PC04 SPI_Sel    3
 2 SPI_Mosi PC02 35|36 PC01 Pin11      2  Encoder PA02 35|36                 2
 1 SPI_Miso PC03 37|38 PC00 Pin12      1    Pin10 PA03 37|38                 1

*/

#define WD_ENA 1		/* watchdog enable */

#define DBGPORT USART1
#define REMPORT USART6

#define remoteISR(x) USART6_IRQHandler(x)
#define REMOTE_IRQn USART6_IRQn

#define index1ISR(x) EXTI2_IRQHandler(x)
#define index1IRQn EXTI2_IRQn

#define index2ISR(x) EXTI4_IRQHandler(x)
#define index2IRQn EXTI4_IRQn

#define encISR(x) EXTI0_IRQHandler(x)
#define encIRQn EXTI0_IRQn
#define encIRQ_Bit (0 << 1)

#define spEncISR(x) EXTI1_IRQHandler(x)
#define spEncIRQn EXTI1_IRQn

// #define STEP1_TIM2		/* step 1 z axis timer 2 */
// #define STEP1_PWM1		/* step 1 pwm 1 */

// #define STEP2_TIM5		/* step 2 x axis timer 5 */
// #define STEP2_PWM1		/* step 2 pwm 1 */

// #define STEP3_TIM4		/* step 3 timer 4 */
// #define STEP3_PWM4		/* step 3 pwm 4 */

// #define STEP4_TIM1		/* step 4 timer 1 */
// #define STEP4_PWM1		/* step 4 pwm 1 */

// #define SPINDLE_TIM3		/* spindle timer 3 */
// #define SPINDLE_PWM3		/* spindle pwm 3 */

// #define PWM_SHARED_INDEX	/* pwm shared with index timer 10 */
// #define PWM_PWM1		/* pwm timer pwm 1 */

// #define USEC_SHARED_INDEX	/* usec shared with index timer 10 */

// #define INDEX_TMR_TIM10		/* index timer 10 */

// #define ENCODER_MULT 1		/* encoder pulse multiplier */

// #define CMP_TMR_TIM9		/* compare timer 9 */

// #define INT_TMR_TIM11		/* internal timer 11 */
// #define INT_TMR_PWM 0		/* internal timer pwm ena / dis */

#define ENC_TEST 0		/* encoder test */

// #if ENC_TEST
// #define ENC_TMR_TIM4		/* encoder timer 4 */
// #endif

#define SPI 1
#define SPIn SPI2
#define I2C 0
#define I2Cn I2C1

#define DBG_PINS		/* use function pins for debug */

#ifdef Dbg0_Pin
#define DBG0_TYPE OUT_PIN
#endif

#define Dbg1_Pin Pin1_Pin
#define Dbg1_GPIO_Port Pin1_GPIO_Port
#define DBG1_TYPE OUT_PIN

#define Dbg2_Pin Pin14_Pin
#define Dbg2_GPIO_Port Pin14_GPIO_Port
#define DBG2_TYPE OUT_PIN

#define Dbg3_Pin XFlag_Pin
#define Dbg3_GPIO_Port XFlag_GPIO_Port
#define DBG3_TYPE XILINX_PIN

#if 1
#define Dbg4_Pin SPI_Miso_Pin	/* spi miso */
#define Dbg4_GPIO_Port SPI_Miso_GPIO_Port
#define DBG4_TYPE SPI_PIN

#define Dbg5_Pin SPI_Mosi_Pin	/* spi mosi */
#define Dbg5_GPIO_Port SPI_Mosi_GPIO_Port
#define DBG5_TYPE SPI_PIN

#define Dbg6_Pin SPI_Sck_Pin	/* spi sck */
#define Dbg6_GPIO_Port SPI_Sck_GPIO_Port
#define DBG6_TYPE SPI_PIN

#define Dbg7_Pin SPI_Sel_Pin	/* spi sel */
#define Dbg7_GPIO_Port SPI_Sel_GPIO_Port
#define DBG7_TYPE SPI_PIN
#endif

#if 1
#define Dbg8_Pin I2C_Scl_Pin	/* i2c1 scl */
#define Dbg8_GPIO_Port I2C_Scl_GPIO_Port
#define DBG8_TYPE I2C_PIN

#define Dbg9_Pin I2C_Sda_Pin	/* i2c1 sda */
#define Dbg9_GPIO_Port I2C_Sda_GPIO_Port
#define DBG9_TYPE I2C_PIN
#endif

#if 1
#define Dbg10_Pin Dir4_Pin
#define Dbg10_GPIO_Port Dir4_GPIO_Port
#define DBG10_TYPE OUT_PIN
#endif

#if 1
#define Dbg11_Pin Dir3_Pin
#define Dbg11_GPIO_Port Dir3_GPIO_Port
#define DBG11_TYPE OUT_PIN
#endif

#endif	/* defined(NUCLEO401) */
