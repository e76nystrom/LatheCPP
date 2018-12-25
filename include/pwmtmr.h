#ifdef PWM_TMR_TIM12

/* pwm output timer 12 16 bit pwm channel 1 */

#define PWM_TIM TIM12

#define pwmTmrISR(x)  TIM8_BRK_TIM12_IRQHandler(x)
#define pwmTmrInit()  __HAL_RCC_TIM14_CLK_ENABLE(); \
 PWM_TIM->CR1 &= ~TIM_CR1_CEN

#endif

#ifdef PWM_TIM

#define pwmTmrClrIE() PWM_TIM->DIER &= ~TIM_IT_UPDATE
#define pwmTmrSetIE() PWM_TIM->DIER |= TIM_IT_UPDATE
#define pwmTmrIF()    (PWM_TIM->SR & TIM_SR_UIF)
#define pwmTmrClrIF() PWM_TIM->SR = ~TIM_FLAG_UPDATE
#define pwmTmrStart() PWM_TIM->CR1 |= TIM_CR1_CEN
#define pwmTmrStop()  PWM_TIM->CR1 &= ~TIM_CR1_CEN
#define pwmTmrScl(x)  PWM_TIM->PSC = (x)
#define pwmTmrRead()  PWM_TIM->CNT
#define pwmTmrClr()   PWM_TIM->CNT = 0
#define pwmTmrCnt(x)  PWM_TIM->CNT = (x)
#define pwmTmrMax(x)  PWM_TIM->ARR = ((x) - 1)
#define pwmTmrSet(x)  PWM_TIM->ARR = (x)
#define pwmTmrMaxRead() PWM_TIM->ARR

#ifdef PWM_PWM1
/* channel 1 */
#define pwmTmrCCR(x) PWM_TIM->CCR1 =  ((x) - 1)
#define pwmPWMMode() PWM_TIM->CCMR1 = (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1)
#define pwmPWMEna()  PWM_TIM->CCER |= TIM_CCER_CC1E
#define pwmPWMDis()  PWM_TIM->CCER &= ~TIM_CCER_CC1E
#endif

#endif
