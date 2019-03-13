#ifdef CMP_TMR_TIM9

#define cmpTmrISR(x) TIM1_BRK_TIM9_IRQHandler(x)

#define CMP_TIM TIM9

#define cmpTmrIsr(x) TIM1_BRK_TIM9_IRQHandler(x)

#define cmpTmrStart() __HAL_RCC_TIM9_CLK_ENABLE();	\
 CMP_TIM->CR1 |= TIM_CR1_CEN

#endif

#ifdef CMP_TMR_TIM12

#define cmpTmrISR(x) TIM8_BRK_TIM12_IRQHandler(x)

#define CMP_TIM TIM12

#define cmpTmrStart() __HAL_RCC_TIM12_CLK_ENABLE(); \
 CMP_TIM->CR1 |= TIM_CR1_CEN

#endif

#ifdef CMP_TIM

#define cmpTmrSetIE() CMP_TIM->DIER |= TIM_DIER_UIE
#define cmpTmrClrIE() CMP_TIM->DIER &= ~TIM_DIER_UIE
#define cmpTmrIF()    (CMP_TIM->SR & TIM_SR_UIF)
#define cmpTmrClrIF() CMP_TIM->SR = ~TIM_SR_UIF

#define cmpTmrStop()  CMP_TIM->CR1 &= ~TIM_CR1_CEN
#define cmpTmrScl(x)  CMP_TIM->PSC = (x)
#define cmpTmrRead()  CMP_TIM->CNT
#define cmpTmrCnt(x)  CMP_TIM->CNT = (x)
#define cmpTmrClrCnt() CMP_TIM->CNT = 0
#define cmpTmrMax(x)  CMP_TIM->ARR = (x - 1)
#define cmpTmrSet(x)  CMP_TIM->ARR = (x)
#define cmpTmrMaxRead() CMP_TIM->ARR

#define cmpTmrCap1EnaSet() CMP_TIM->CCER |= TIM_CCER_CC1E
#define cmpTmrCap1SetIE() CMP_TIM->DIER |= TIM_DIER_CC1IE
#define cmpTmrCap1ClrIE() CMP_TIM->DIER &= ~TIM_DIER_CC1IE
#define cmpTmrCap1IF() ((CMP_TIM->SR & TIM_SR_CC1IF) != 0)
#define cmpTmrCap1ClrIF() CMP_TIM->SR &= ~TIM_SR_CC1IF
#define cmpTmrCap1() CMP_TIM->CCR1

#define cmpTmrCap2EnaSet() CMP_TIM->CCER |= TIM_CCER_CC2E
#define cmpTmrCap2SetIE() CMP_TIM->DIER |= TIM_DIER_CC2IE
#define cmpTmrCap2ClrIE() CMP_TIM->DIER &= ~TIM_DIER_CC2IE
#define cmpTmrCap2IF() ((CMP_TIM->SR & TIM_SR_CC1IF) != 0)
#define cmpTmrCap2ClrIF() CMP_TIM->SR &= ~TIM_SR_CC1IF
#define cmpTmrCap2() CMP_TIM->CCR2

#define cmpTmrOCP1Clr() CMP_TIM->SR &= ~TIM_SR_CC1OF
#define cmpTmrOCP2Clr() CMP_TIM->SR &= ~TIM_SR_CC2OF

#endif
