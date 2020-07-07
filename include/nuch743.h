#ifdef NUCLEOH743

/*



*/

#define WD_ENA 1		/* watchdog enable */

#define REMPORT UART7

#define RemRx_Pin Uart7Rx_Pin
#define RemRx_GPIO_Port Uart7Rx_GPIO_Port
#define RemTx_Pin Uart7Tx_Pin
#define RemTx_GPIO_Port Uart7Tx_GPIO_Port

#define DBGPORT USART3

#define DbgRx_Pin Usart3Rx_Pin 
#define DbgRx_GPIO_Port Usart3Rx_GPIO_Port 
#define DbgTx_Pin Usart3Tx_Pin
#define DbgTx_GPIO_Port Usart3Tx_GPIO_Port

#define remoteISR(x) UART7_IRQHandler(x)
#define REMOTE_IRQn UART7_IRQn

#define indexISR(x) EXTI0_IRQHandler(x)
#define indexIRQn EXTI0_IRQn

#define encISR(x) EXTI2_IRQHandler(x)
#define encIRQn EXTI2_IRQn
#define encIRQ_Bit (1 << 0)

#define spSyncISR(x) EXTI1_IRQHandler(x)
#define spSyncIRQn EXTI1_IRQn

#define ENC_TEST 0		/* encoder test */

#define SPI 1
#define SPIn SPI3
#define I2C 0
#define I2Cn I2C1

#define PR PR1
#define SWIER SWIER1
#define IMR IMR1
#define IWDG IWDG1

#endif	/* defined(NUCLEO746) */
