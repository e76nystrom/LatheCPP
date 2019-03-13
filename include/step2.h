#define dirXFwd() (Dir2_GPIO_Port->BSRR = xAxis.dirFwd)
#define dirXRev() (Dir2_GPIO_Port->BSRR = xAxis.dirRev)

#ifdef STEP2_TIM5

/* step 2 timer 5 32 bit */

#define X_TIM ((TIM_TypeDef *) TIM5_BASE)

#define xTmrISR(x)  TIM5_IRQHandler(x)

#define xTmrInit()  __HAL_RCC_TIM5_CLK_ENABLE(); \
 X_TIM->CR1 |= TIM_CR1_DIR;			     \
 X_TIM->CR1 &= ~TIM_CR1_CEN
#define xTmrStart() X_TIM->CR1 |= TIM_CR1_CEN
#define xTmrBDTR()

#endif

#ifdef STEP2_TIM1

/* step 2 timer 1 16 bit */

#define X_TIM TIM1

void xTmrISR(void);

#define xTmrInit()  __HAL_RCC_TIM1_CLK_ENABLE(); \
 X_TIM->CR1 |= TIM_CR1_DIR;			     \
 X_TIM->CR1 &= ~TIM_CR1_CEN
#define xTmrStart() do {	\
  TIM1->EGR = TIM_EGR_UG;	\
  TIM1->CR1 |= TIM_CR1_CEN;	\
 } while (0)
#define xTmrBDTR() SP_TIM->BDTR |= TIM_BDTR_MOE

#endif

#ifdef X_TIM

#define xTmrClrIE() X_TIM->DIER &= ~TIM_IT_UPDATE
#define xTmrSetIE() X_TIM->DIER |= TIM_IT_UPDATE
#define xTmrClrIF() X_TIM->SR = ~TIM_FLAG_UPDATE
#define xTmrIF()    (X_TIM->SR & TIM_SR_UIF)
#define xTmrPulse() X_TIM->CR1 |= (TIM_CR1_OPM | TIM_CR1_CEN)
#define xTmrStop()  X_TIM->CR1 &= ~(TIM_CR1_OPM | TIM_CR1_CEN)
#define xTmrScl(x)  X_TIM->PSC = (x)
#define xTmrRead()  X_TIM->CNT
#define xTmrClr()   X_TIM->CNT = 0
#define xTmrCnt(x)  X_TIM->CNT = (x)
#define xTmrMax(x)  X_TIM->ARR = ((x) - 1)
#define xTmrSet(x)  X_TIM->ARR = (x)
#define xTmrUpdCtr(x) X_TIM->ARR -= (x)
#define xTmrMaxRead() X_TIM->ARR

#ifdef STEP2_PWM1
/* channel 1 */
#define xTmrCCR(x) X_TIM->CCR1 = (x)
#define xTmrPWMMode() X_TIM->CCMR1 = (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1)
#define xTmrPWMEna()  xTmrBDTR(); X_TIM->CCER |= TIM_CCER_CC1E
#define xTmrPWMDis()  X_TIM->CCER &= ~TIM_CCER_CC1E
#define X_CCR CCR1
#define X_CCMR CCMR1
#endif

#ifdef STEP2_PWM2
/* channel 2 */
#define xTmrCCR(x) X_TIM->CCR2 = (x)
#define xTmrPWMMode() X_TIM->CCMR2 = (TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1)
#define xTmrPWMEna()  xTmrBDTR(); X_TIM->CCER |= TIM_CCER_CC2E
#define xTmrPWMDis()  X_TIM->CCER &= ~TIM_CCER_CC2E
#define X_CCR CCR2
#define X_CCMR CCMR1
#endif

#ifdef STEP2_PWM3
/* channel 3 */
#define xTmrCCR(x) X_TIM->CCR3 = (x)
#define xTmrPWMMode() X_TIM->CCMR2 = (TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1)
#define xTmrPWMEna()  xTmrBDTR(); X_TIM->CCER |= TIM_CCER_CC3E
#define xTmrPWMDis()  X_TIM->CCER &= ~TIM_CCER_CC3E
#define X_CCR CCR3
#define X_CCMR CCMR2
#endif

#ifdef STEP2_PWM4
/* channel 3 */
#define xTmrCCR(x) X_TIM->CCR4 = (x)
#define xTmrPWMMode() X_TIM->CCMR2 = (TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1)
#define xTmrPWMEna()  xTmrBDTR(); X_TIM->CCER |= TIM_CCER_CC4E
#define xTmrPWMDis()  X_TIM->CCER &= ~TIM_CCER_CC4E
#define X_CCR CCR4
#define X_CCMR CCMR2
#endif

#ifdef SPINDLE_TIM3
#ifdef STEP2_TIM5
/* timer 3 trigger 2 */
#define xTmrSlvEna() X_TIM->SMCR = (TIM_SMCR_TS_1 | \
				    TIM_SMCR_SMS_2 | TIM_SMCR_SMS_1)
#endif
#if STEP2_TIM1
/* timer 3 trigger 0 */
#define xTmrSlvEna() X_TIM->SMCR = ( \
				    TIM_SMCR_SMS_2 | TIM_SMCR_SMS_1)
#endif
#endif

#ifdef SPINDLE_TIM8
#ifdef STEP2_TIM5
/* timer 8 trigger 3 */
#define xTmrSlvEna() X_TIM->SMCR = (TIM_SMCR_TS_1 | TIM_SMCR_TS_0 | \
				    TIM_SMCR_SMS_2 | TIM_SMCR_SMS_1)
#endif
#ifdef STEP2_TIM1
/* timer 8 trigger 0 */
#define xTmrSlvEna() X_TIM->SMCR = ( \
				    TIM_SMCR_SMS_2 | TIM_SMCR_SMS_1)
#endif
#endif

#define xTmrSlvDis() X_TIM->SMCR = 0

#endif
