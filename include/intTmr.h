#ifdef INT_TMR_TIM11

#define INT_TIM TIM11

//void intTmrISR(void);

#define intTmrStart() __HAL_RCC_TIM11_CLK_ENABLE(); \
 INT_TIM->CR1 |= TIM_CR1_CEN
#define intTmrBDTR()
#endif

#ifdef INT_TMR_TIM1

#define INT_TIM TIM1

void intTmrISR(void);

#define intTmrStart() __HAL_RCC_TIM1_CLK_ENABLE(); \
 INT_TIM->CR1 |= TIM_CR1_CEN
#define intTmrBDTR() INT_TIM->BDTR |= TIM_BDTR_MOE

#endif

#ifdef INT_TMR_TIM4

#define INT_TIM TIM4

#define intTmrISR(x) TIM4_IRQHandler(x)

#define intTmrStart() __HAL_RCC_TIM4_CLK_ENABLE(); \
 INT_TIM->CR1 |= TIM_CR1_CEN

#endif

#ifdef INT_TIM

#define intTmrClrIE() INT_TIM->DIER &= ~TIM_IT_UPDATE
#define intTmrSetIE() INT_TIM->DIER |= TIM_IT_UPDATE
#define intTmrIF()    (INT_TIM->SR & TIM_FLAG_UPDATE)
#define intTmrClrIF() INT_TIM->SR = ~TIM_FLAG_UPDATE
#define intTmrInit()  INT_TIM->CR1 &= ~TIM_CR1_CEN
#define intTmrPulse() INT_TIM->CR1 |= (TIM_CR1_OPM | TIM_CR1_CEN)
#define intTmrStop()  INT_TIM->CR1 &= ~(TIM_CR1_OPM | TIM_CR1_CEN)
#define intTmrActive() ((INT_TIM2->CR1 & TIM_CR1_CEN) != 0)
#define intTmrScl(x)  INT_TIM->PSC = (x)
#define intTmrRead()  INT_TIM->CNT
#define intTmrCnt(x)  INT_TIM->CNT = (x)
#define intTmrClr()   INT_TIM->CNT = 0
#define intTmrMax(x)  INT_TIM->ARR = (x - 1)
#define intTmrSet(x)  INT_TIM->ARR = (x)
#define intTmrMaxRead() INT_TIM->ARR

#if INT_TMR_PWM

#ifdef INT_TIM_PWM1
/* channel 1 */
#define intTmrCCR(x) INT_TIM->CCR1 = (x)
#define intTmrPWMMode() INT_TIM->CCMR1 = (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1)
#define intTmrPWMEna()  intTmrBDTR(); \
 INT_TIM->CCER |= TIM_CCER_CC1E
#define intTmrPWMDis()  INT_TIM->CCER &= ~TIM_CCER_CC1E
#endif

#ifdef INT_TIM_PWM4
/* channel 4 */
#define intTmrCCR(x) INT_TIM->CCR4 = (x)
#define intTmrPWMMode() INT_TIM->CCMR2 = (TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1)
#define intTmrPWMEna()  intTmrBDTR(); \
 INT_TIM->CCER |= TIM_CCER_CC4E
#define intTmrPWMDis()  INT_TIM->CCER &= ~TIM_CCER_CC4E
#endif

#endif

#endif
