#ifdef STEP3_TIM4

#define STEP3_TIM TIM4

#define step3TmrISR(x)  TIM4_IRQHandler(x)

#define step3TmrInit()  __HAL_RCC_TIM4_CLK_ENABLE(); \
 STEP3_TIM->CR1 |= TIM_CR1_DIR;			     \
 STEP3_TIM->CR1 &= ~TIM_CR1_CEN

#endif

#ifdef STEP3_TIM

#define step3TmrClrIE() STEP3_TIM->DIER &= ~TIM_IT_UPDATE
#define step3TmrSetIE() STEP3_TIM->DIER |= TIM_IT_UPDATE
#define step3TmrClrIF() STEP3_TIM->SR = ~TIM_FLAG_UPDATE
#define step3TmrIF()    (STEP3_TIM->SR & TIM_SR_UIF)
#define step3TmrStart() STEP3_TIM->CR1 |= TIM_CR1_CEN
#define step3TmrStop()  STEP3_TIM->CR1 &= ~TIM_CR1_CEN
#define step3TmrScl(x)  STEP3_TIM->PSC = (x)
#define step3TmrRead()  STEP3_TIM->CNT
#define step3TmrClr()   STEP3_TIM->CNT = 0
#define step3TmrCnt(x)  STEP3_TIM->CNT = (x)
#define step3TmrMax(x)  STEP3_TIM->ARR = ((x) - 1)
#define step3TmrSet(x)  STEP3_TIM->ARR = (x)
#define step3TmrMaxRead() STEP3_TIM->ARR

#ifdef STEP3_PWM1
/* channel 1 */
#define step3TmrCCR(x) STEP3_TIM->CCR1 = (x)
#define step3PWMMode() STEP3_TIM->CCMR1 = (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1)
#define step3PWMEna()  STEP3_TIM->CCER |= TIM_CCER_CC1E
#define step3PWMDis()  STEP3_TIM->CCER &= ~TIM_CCER_CC1E
#endif

#ifdef STEP3_PWM2
/* channel 2 */
#define step3TmrCCR(x) STEP3_TIM->CCR2 = (x)
#define step3PWMMode() STEP3_TIM->CCMR1 = (TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1)
#define step3PWMEna()  STEP3_TIM->CCER |= TIM_CCER_CC2E
#define step3PWMDis()  STEP3_TIM->CCER &= ~TIM_CCER_CC2E
#endif

#ifdef STEP3_PWM3
/* channel 3 */
#define step3TmrCCR(x) STEP3_TIM->CCR1 = (x)
#define step3PWMMode() STEP3_TIM->CCMR2 = (TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1)
#define step3PWMEna()  STEP3_TIM->CCER |= TIM_CCER_CC3E
#define step3PWMDis()  STEP3_TIM->CCER &= ~TIM_CCER_CC3E
#endif

#ifdef STEP3_PWM4
/* channel 4 */
#define step3TmrCCR(x) STEP3_TIM->CCR4 = (x)
#define step3PWMMode() STEP3_TIM->CCMR2 = (TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1)
#define step3PWMEna()  STEP3_TIM->CCER |= TIM_CCER_CC4E
#define step3PWMDis()  STEP3_TIM->CCER &= ~TIM_CCER_CC4E
#endif

#ifdef SPINDLE_TIM3
#ifdef STEP3_TIM4
/* timer 3 trigger 3 */
#define step3TmrSlvEna() X_TIM->SMCR = (TIM_SMCR_TS_1 | TIM_SMCR_TS_0 | \
				    TIM_SMCR_SMS_2 | TIM_SMCR_SMS_1)
#endif
#endif

#ifdef SPINDLE_TIM8
#ifdef STEP3_TIM4
/* timer 8 trigger 2 */
#define step3TmrSlvEna() X_TIM->SMCR = (TIM_SMCR_TS_1 | \
				    TIM_SMCR_SMS_2 | TIM_SMCR_SMS_1)
#endif
#endif

#endif
