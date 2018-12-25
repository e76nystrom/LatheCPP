#ifdef STEP2B_TIM1

/* step 2 timer 1 16 bit */

#define STEP2B_TIM TIM1

void step2bTmrISR(void);

#define step2bTmrInit()  __HAL_RCC_TIM1_CLK_ENABLE(); \
 STEP2B_TIM->CR1 &= ~TIM_CR1_CEN
#define step2bTmrStart() do {	\
  TIM1->EGR = TIM_EGR_UG;	\
  TIM1->CR1 |= TIM_CR1_CEN;	\
 } while (0)
#define step2bTmrBDTR() STEP2B_TIM->BDTR |= TIM_BDTR_MOE

#endif	/* STEP2B_TIM1 */

#ifdef STEP2B_TIM

#define step2bTmrClrIE() STEP2B_TIM->DIER &= ~TIM_IT_UPDATE
#define step2bTmrSetIE() STEP2B_TIM->DIER |= TIM_IT_UPDATE
#define step2bTmrClrIF() STEP2B_TIM->SR = ~TIM_FLAG_UPDATE
#define step2bTmrIF()    (STEP2B_TIM->SR & TIM_SR_UIF)
#define step2bTmrPulse() STEP2B_TIM->CR1 |= (TIM_CR1_OPM | TIM_CR1_CEN)
#define step2bTmrStop()  STEP2B_TIM->CR1 &= ~(TIM_CR1_OPM | TIM_CR1_CEN)
#define step2bTmrScl(x)  STEP2B_TIM->PSC = (x)
#define step2bTmrRead()  STEP2B_TIM->CNT
#define step2bTmrClr()   STEP2B_TIM->CNT = 0
#define step2bTmrCnt(x)  STEP2B_TIM->CNT = (x)
#define step2bTmrMax(x)  STEP2B_TIM->ARR = ((x) - 1)
#define step2bTmrSet(x)  STEP2B_TIM->ARR = (x)
#define step2bTmrUpdCtr(x) STEP2B_TIM->ARR -= (x)
#define step2bTmrMaxRead() STEP2B_TIM->ARR

#ifdef STEP2B_PWM1
/* channel 1 */
#define step2bTmrCCR(x) STEP2B_TIM->CCR1 = (x)
#define step2bPWMMode() STEP2B_TIM->CCMR1 = \
  (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1)
#define step2bPWMEna()  step2bTmrBDTR(); STEP2B_TIM->CCER |= TIM_CCER_CC1E
#define step2bPWMDis()  STEP2B_TIM->CCER &= ~TIM_CCER_CC1E
#define STEP2BCCR CCR1
#define STEP2BCCMR CCMR1
#endif

#ifdef STEP2B_PWM2
/* channel 2 */
#define step2bTmrCCR(x) STEP2B_TIM->CCR1 = (x)
#define step2bPWMMode() STEP2B_TIM->CCMR1 = \
  (TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1)
#define step2bPWMEna()  step2bTmrBDTR(); STEP2B_TIM->CCER |= TIM_CCER_CC1E
#define step2bPWMDis()  STEP2B_TIM->CCER &= ~TIM_CCER_CC1E
#define STEP2BCCR CCR2
#define STEP2BCCMR CCMR1
#endif

#ifdef STEP2B_PWM3
/* channel 3 */
#define step2bTmrCCR(x) STEP2B_TIM->CCR3 = (x)
#define step2bPWMMode() STEP2B_TIM->CCMR2 = \
  (TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1)
#define step2bPWMEna()  step2bTmrBDTR(); STEP2B_TIM->CCER |= TIM_CCER_CC3E
#define step2bPWMDis()  STEP2B_TIM->CCER &= ~TIM_CCER_CC3E
#define STEP2BCCR CCR3
#define STEP2BCCMR CCMR2
#endif

#ifdef STEP2B_PWM4
/* channel 3 */
#define step2bTmrCCR(x) STEP2B_TIM->CCR4 = (x)
#define step2bPWMMode() STEP2B_TIM->CCMR2 = \
  (TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1)
#define step2bPWMEna()  step2bTmrBDTR(); STEP2B_TIM->CCER |= TIM_CCER_CC3E
#define step2bPWMDis()  STEP2B_TIM->CCER &= ~TIM_CCER_CC3E
#define STEP2BCCR CCR4
#define STEP2BCCMR CCMR2
#endif

#ifdef SPINDLE_TIM3
/* timer 1 trigger 1 */
#define step2bTmrSlvEna() STEP2B_TIM->SMCR = (TIM_SMCR_TS_0 | \
					      TIM_SMCR_SMS_2 | TIM_SMCR_SMS_1)
#endif

#ifdef SPINDLE_TIM8
/* timer 1 trigger 0 */
#define step2bTmrSlvEna() STEP2B_TIM->SMCR = ( \
					      TIM_SMCR_SMS_2 | TIM_SMCR_SMS_1)
#endif

#define step2bTmrSlvDis() STEP2B_TIM->SMCR = 0

#endif
