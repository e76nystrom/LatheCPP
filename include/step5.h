#ifdef STEP5_TIM8

/* ---------------------------------------- */
/* step5 timer 8 16 bit pwm channel 4 */

#define STEP5_TIM TIM8

#define step5TmrISR(x) TIM8_UP_TIM13_IRQHandler(x)

#define step5TmrInit() __HAL_RCC_TIM8_CLK_ENABLE(); \
 STEP5_TIM->CR1 |= TIM_CR1_DIR;			    \
 STEP5_TIM->CR1 &= ~TIM_CR1_CEN
#define step5TmrStart() do {	\
  STEP5_TIM->EGR = TIM_EGR_UG;	\
  STEP5_TIM->CR1 |= TIM_CR1_CEN;	\
 } while (0)
#define step5TmrBDTR() STEP5_TIM->BDTR |= TIM_BDTR_MOE

#endif

#ifdef STEP5_TIM3

#define STEP5_TIM TIM3

#define step5TmrISR(x) TIM3_IRQHandler(x)

#define step5TmrInit() __HAL_RCC_TIM3_CLK_ENABLE(); \
 STEP5_TIM->CR1 |= TIM_CR1_DIR;			    \
 STEP5_TIM->CR1 &= ~TIM_CR1_CEN
#define step5TmrStart() STEP5_TIM->CR1 |= TIM_CR1_CEN
#define step5TmrBDTR() 

#endif

#ifdef STEP5_TIM

#define step5TmrClrIE()  STEP5_TIM->DIER &= ~TIM_IT_UPDATE
#define step5TmrSetIE()  STEP5_TIM->DIER |= TIM_IT_UPDATE
#define step5TmrClrIF()  STEP5_TIM->SR = ~TIM_FLAG_UPDATE
#define step5TmrStop()   STEP5_TIM->CR1 &= ~TIM_CR1_CEN
#define step5TmrScl(x)   STEP5_TIM->PSC = (x)
#define step5TmrRead()   STEP5_TIM->CNT
#define step5TmrClr()    STEP5_TIM->CNT = 0
#define step5TmrCnt(x)   STEP5_TIM->CNT = (x)
#define step5TmrMax(x)   STEP5_TIM->ARR = ((x) - 1)
#define step5TmrSet(x)   STEP5_TIM->ARR = (x)
#define step5TmrMaxRead() STEP5_TIM->ARR

#ifdef STEP5_PWM1
/* channel 1 */
#define step5TmrCCR(x) STEP5_TIM->CCR1 = ((x) - 1)
#define step5PWMMode() STEP5_TIM->CCMR1 = (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1)
#define step5PWMEna() step5TmrBDTR(); STEP5_TIM->CCER |= TIM_CCER_CC1E
#define step5PWMDis()  STEP5_TIM->CCER &= ~TIM_CCER_CC1E
#endif

#ifdef STEP5_PWM2
/* channel 2 */
#define step5TmrCCR(x) STEP5_TIM->CCR2 = ((x) - 1)
#define step5PWMMode() STEP5_TIM->CCMR1 = (TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1)
#define step5PWMEna()  step5TmrBDTR(); STEP5_TIM->CCER |= TIM_CCER_CC2E
#define step5PWMDis()  STEP5_TIM->CCER &= ~TIM_CCER_CC2E
#endif

#ifdef STEP5_PWM3
/* channel 3 */
#define step5TmrCCR(x) STEP5_TIM->CCR3 = ((x) - 1)
#define step5PWMMode() STEP5_TIM->CCMR2 = (TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1)
#define step5PWMEna()  step5TmrBDTR(); STEP5_TIM->CCER |= TIM_CCER_CC3E
#define step5PWMDis()  STEP5_TIM->CCER &= ~TIM_CCER_CC3E
#endif

#ifdef STEP5_PWM4
/* channel 4 */
#define step5TmrCCR(x) STEP5_TIM->CCR4 = ((x) - 1)
#define step5PWMMode() STEP5_TIM->CCMR2 = (TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1)
#define step5PWMEna()  step5TmrBDTR(); STEP5_TIM->CCER |= TIM_CCER_CC4E
#define step5PWMDis()  STEP5_TIM->CCER &= ~TIM_CCER_CC4E
#endif

#ifdef STEP5_NOPWM
#define step5TmrCCR(x)
#define step5PWMMode()
#define step5PWMEna()
#define step5PWMDis()
#endif

#endif
