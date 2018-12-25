#ifdef ENC_TMR_TIM7

/* encoder simulator timer 7 16 bit */

#define ENC_TMR TIM7

#define encTestTmrISR(x)  TIM7_IRQHandler(x)

#define encTestTmrInit()  __HAL_RCC_TIM7_CLK_ENABLE(); \
 ENC_TMR->CR1 &= ~TIM_CR1_CEN
#define encTestTmrStart() ENC_TMR->CR1 |= TIM_CR1_CEN

#endif

#ifdef ENC_TMR_TIM1

#define ENC_TMR TIM1

void encTestTmrISR(void);

#define encTestInit()  __HAL_RCC_TIM1_CLK_ENABLE(); \
 X_TIM->CR1 &= ~TIM_CR1_CEN
#define encTestStart() do {	\
  TIM1->EGR = TIM_EGR_UG;	\
  TIM1->CR1 |= TIM_CR1_CEN;	\
 } while (0)

#endif

#ifdef ENC_TMR

#define encTestTmrClrIE() ENC_TMR->DIER &= ~TIM_IT_UPDATE
#define encTestTmrSetIE() ENC_TMR->DIER |= TIM_IT_UPDATE
#define encTestTmrClrIF() ENC_TMR->SR = ~TIM_FLAG_UPDATE
#define encTestTmrStop()  ENC_TMR->CR1 &= ~TIM_CR1_CEN
#define encTestTmrScl(x)  ENC_TMR->PSC = (x)
#define encTestTmrRead()  ENC_TMR->CNT
#define encTestTmrClr()   ENC_TMR->CNT = 0
#define encTestTmrMax(x)  ENC_TMR->ARR = (x - 1)
#define encTestTmrMaxRead() ENC_TMR->ARR

#endif
