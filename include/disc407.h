#ifdef DISCOVERY407

/*

 1                1| 2                 1                1| 2                 1
 2                3| 4                 2                3| 4                 2
 3                5| 6                 3                5| 6                 3
 4          PC01  7| 8 PC00            4          PH00  7| 8 PH01            4
 5          PC03  9|10 PC02 Dbg5       5          PC14  9|10 PC15 XFlag      5
 6   Step2a PA01 11|12 PA00 Dbg0       6    JogB2 PE06 11|12 PC13 ZFlag      6
 7     Dbg3 PA03 13|14 PA02 Encoder    7   ExtInt PE04 13|14 PE05 JogA1      7
 8          PA05 15|16 PA04 Dbg1       8     Dbg9 PE02 15|16 PE03 Logic1     8
 9          PA07 17|18 PA06            9     Dbg7 PE00 17|18 PE01 Dbg8       9
10          PC05 19|20 PC04           10    Dbg12 PB08 19|20 PB09 I2C Sda   10
11     Dbg4 PB01 21|22 PB00 Index2    11               21|22                11
12               23|24 PB02           12  I2C Scl PB06 23|24 PB07 Dbg11     12
13          PE07 25|26 PE08 JogA2     13    Step3 PB04 25|26 PB05 SPI Mosi  13
12    Pin15 PE09 27|28 PE10 Dbg10     12    JogB1 PD07 27|28 PB03           12
11    Pin13 PE11 29|30 PE12 Dir2      11          PD05 29|30 PD06 SPI Sel   11
10       XB PE13 31|32 PE14 Step2b    10     Pin1 PD03 31|32 PD04           10
 9       XA PE15 33|34 PB10 Step1      9    Pin14 PD01 33|34 PD02 DbgRx      9
 8          PB11 35|36 PB12 Dir1       8    DbgTx PC12 35|36 PD00            8
 7          PB13 37|38 PB14 Pin16      7  SPI Sck PC10 37|38 PC11 SPI Miso   7
 6    Pin12 PB15 39|40 PD08 Dir3       6          PA14 39|40 PA15 Dbg3       6
 5    Pin11 PD09 41|42 PD10 Dir4       5          PA10 41|42 PA13            5
 4    Pin10 PD11 43|44 PD12 ZA         4    Pin17 PA08 43|44 PA09            4
 3    Step4 PD13 45|46 PD14 ZB         3     Dir5 PC08 45|46 PC09 Step5      3
 2   Index1 PD15 47|48                 2    RemTx PC06 47|48 PC07 RemRx      2
 1               49|50                 1               49|50                 1

*/

#define WD_ENA 1		/* watchdog enable */

#define DBGPORT UART5
#define REMPORT USART6

#define remoteISR(x) USART6_IRQHandler(x)
#define REMOTE_IRQn USART6_IRQn

#define indexISR(x) EXTI0_IRQHandler(x)
#define indexIRQn EXTI0_IRQn

#define encISR(x) EXTI1_IRQHandler(x)
#define encIRQn EXTI1_IRQn
#define encIRQ_Bit (1 << 1)

#define spSyncISR(x) EXTI4_IRQHandler(x)
#define spSyncIRQn EXTI4_IRQn

#define ENC_TEST 0		/* encoder test */
//#define ENC_TMR_TIM7		/* encoder timer 7 */

#include "i2c.h"
#define I2C_DEV I2C1
#define I2C_NAME "I2C1"
#define I2C_GPIO GPIOB
#define SLAVE_ADDRESS 0x3f
inline void mxI2CInit()
{
 MX_I2C1_Init();
}

#define SPI 1
#define SPIn SPI3
#define I2C 1
#define I2Cn I2C1

#endif	/* defined(DISCOVERY407) */
