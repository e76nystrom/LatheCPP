#ifdef CORE407V

/*

 1     Dbg2 PB12  1| 2 PB13 Dbg3       1               50|49                 1
 2    Pin16 PB14  3| 4 PB15 T6         2    DbgRx PB11 48|47 PB10 DbgTx      2
 3     Dbg9 PD08  5| 6 PD09 Dbg10      3    ZFlag PE15 46|45 PE14 T5         3
 4       XB PD10  7| 8 PD11 XA         4    XFlag PE13 44|43 PE12 T4         4
 5       ZB PD12  9|10 PD13 Step3      5    Pin14 PE11 42|41 PE10 T3         5
 6       ZA PD14 11|12 PD15 Dbg11      6    JogB2 PE09 40|39 PE08 T2         6
 7    RemTx PC06 13|14 PC07 RemRx      7    JogA2 PE07 38|37 PB02 Index2     7
 8    Step4 PC08 15|16 PC09 Step5      8     Dbg1 PB01 36|35 PB00 Dbg0       8
 9   Step2b PA08 17|18 PA09 T7         9     Dbg6 PC05 34|33 PC04 Dbg5       9
10   OTG_ID PA10 19|20 PA11 OTG_DM    10      T11 PA07 32|31 PA06 Dbg7      10
11   OTG_DP PA12 21|22 PA13 SWDIO     11    Step1 PA05 30|29 PA04 Pin1      11
12               23|24                12               28|27                12
13               25|26 PA14 SWCLK     13   Step2a PA03 26|25 PA02 Encoder   13
12     JTDI PA15 27|28 PC10 SPI_Sck   12       T1 PA01 24|23 PA00 T0        12
11 SPI_Miso PC11 29|30 PC12 Uart5Tx   11               22|21                11
10    Pin12 PD00 31|32 PD01 Pin13     10               20|19                10
 9  Uart5Rx PD02 33|34 PD03 T8         9     Dir1 PC03 18|17 PC02 SPI_Sel    9
 8    Pin10 PD04 35|36 PD05 Dir3       8     Dir5 PC01 16|15 PC00 Dir2       8
 7    Pin11 PD06 37|38 PD07 Dir4       7               14|13                 7
 6      SWO PB03 39|40 PB04 JTRST      6               12|11                 6
 5 SPI_Mosi PB05 41|42 PB06 I2C_Scl    5               10| 9 PC15            5
 4  I2C_Sda PB07 43|44                 4          PC14  8| 7 PC13 Dbg8       4
 3      T10 PB08 45|46 PB09 T9         3                6| 5 PE06 JogA1      3
 2    Pin15 PE00 47|48 PE01 Index1     2    JogB1 PE05  4| 3 PE04 ExtInt     2
 1               49|50                 1    Pin17 PE03  2| 1 PE02 Dbg4       1

*/

#define WD_ENA 1		/* watchdog enable */

#define REMPORT USART6
#define DBGPORT USART3

#define remoteISR(x) USART6_IRQHandler(x)
#define REMOTE_IRQn USART6_IRQn

#define indexISR(x) EXTI2_IRQHandler(x)
#define indexIRQn EXTI2_IRQn
#define INDEX_PIN Index2_Pin

#define encISR(x) EXTI0_IRQHandler(x)
#define encIRQn EXTI0_IRQn
#define encIRQ_Bit (1 << 0)

#define spSyncISR(x) EXTI4_IRQHandler(x)
#define spSyncIRQn EXTI4_IRQn

#include "i2c.h"
#define I2C_DEV I2C1
#define I2C_NAME "I2C1"
#define I2C_GPIO GPIOB
#define SLAVE_ADDRESS 0x7e
inline void mxI2CInit()
{
 MX_I2C1_Init();
}

#define ENC_TEST 0		/* encoder test */

#define SPI 1
#define SPIn SPI3
#define I2C 1
#define I2Cn I2C1

#endif	/* defined(CORE407V) */
