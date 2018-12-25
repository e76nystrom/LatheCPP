/* ---------------------------------------- */
/* step 1 timer 2 32 bit pwm channel 3 */

#define dirZFwd() (Dir1_GPIO_Port->BSRR = zAxis.dirFwd)
#define dirZRev() (Dir1_GPIO_Port->BSRR = zAxis.dirRev)

#ifdef STEP1_TIM2

#define Z_TIM TIM2

#define zTmrInit()  STEP_INIT(TIM2)
#define zTmrISR(x)  TIM2_IRQHandler(x)

#endif

#ifdef Z_TIM

#define zTmrClrIE() Z_TIM->DIER &= ~TIM_IT_UPDATE
#define zTmrSetIE() Z_TIM->DIER |= TIM_IT_UPDATE
#define zTmrTstIE() ((Z_TIM->DIER & TIM_IT_UPDATE) != 0)
#define zTmrClrIF() Z_TIM->SR = ~TIM_FLAG_UPDATE
#define zTmrStart() Z_TIM->CR1 |= TIM_CR1_CEN
#define zTmrPulse() Z_TIM->CR1 |= (TIM_CR1_OPM | TIM_CR1_CEN)
#define zTmrStop()  Z_TIM->CR1 &= ~(TIM_CR1_OPM | TIM_CR1_CEN)
#define zTmrScl(x)  Z_TIM->PSC = (x)
#define zTmrRead()  Z_TIM->CNT
#define zTmrClr()   Z_TIM->CNT = 0
#define zTmrCnt(x)  Z_TIM->CNT = (x)
#define zTmrMax(x)  Z_TIM->ARR = ((x) - 1)
#define zTmrSet(x)  Z_TIM->ARR = (x)
#define zTmrMaxRead() Z_TIM->ARR

#ifdef STEP1_PWM1
/* channel 1 */
#define zTmrCCR(x) Z_TIM->CCR1 = (x)
#define zPWMMode() Z_TIM->CCMR1 = (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1)
#define zPWMEna()  Z_TIM->CCER |= TIM_CCER_CC1E
#define zPWMDis()  Z_TIM->CCER &= ~TIM_CCER_CC1E
#define Z_CCR CCR1
#define Z_CCMR CCMR1
#endif

#ifdef STEP1_PWM2
/* channel 2 */
#define zTmrCCR(x) Z_TIM->CCR1 = (x)
#define zPWMMode() Z_TIM->CCMR1 = (TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1)
#define zPWMEna()  Z_TIM->CCER |= TIM_CCER_CC2E
#define zPWMDis()  Z_TIM->CCER &= ~TIM_CCER_CC2E
#define Z_CCR CCR2
#define Z_CCMR CCMR1
#endif

#ifdef STEP1_PWM3
/* channel 3 */
#define zTmrCCR(x) Z_TIM->CCR3 = (x)
#define zPWMMode() Z_TIM->CCMR2 = (TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1)
#define zPWMEna()  Z_TIM->CCER |= TIM_CCER_CC3E
#define zPWMDis()  Z_TIM->CCER &= ~TIM_CCER_CC3E
#define Z_CCR CCR3
#define Z_CCMR CCMR2
#endif

#ifdef STEP1_PWM4
/* channel 4 */
#define zTmrCCR(x) Z_TIM->CCR4 = (x)
#define zPWMMode() Z_TIM->CCMR2 = (TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1)
#define zPWMEna()  Z_TIM->CCER |= TIM_CCER_CC4E
#define zPWMDis()  Z_TIM->CCER &= ~TIM_CCER_CC4E
#define Z_CCR CCR4
#define Z_CCMR CCMR2
#endif

#ifdef SPINDLE_TIM3
/* timer 3 trigger 2 */
#define zTmrSlvEna() Z_TIM->SMCR = (TIM_SMCR_TS_1 | \
				   TIM_SMCR_SMS_2 | TIM_SMCR_SMS_1)
#endif
#ifdef SPINDLE_TIM8
/* timer 8 trigger 1 */
#define zTmrSlvEna() Z_TIM->SMCR = (TIM_SMCR_TS_0| \
				   TIM_SMCR_SMS_2 | TIM_SMCR_SMS_1)
#endif
#define zTmrSlvDis() Z_TIM->SMCR = 0

#endif
