/* ---------------------------------------- */
/* step 4 timer 4 16 bit pwm channel 1 */

#ifdef STEP4_TIM3

#define STEP4_TIM TIM3

#define step4TmrISR(x)  TIM3_IRQHandler(x)

#define step4TmrInit()  __HAL_RCC_TIM3_CLK_ENABLE(); \
 STEP4_TIM->CR1 |= TIM_CR1_DIR;			     \
 STEP4_TIM->CR1 &= ~TIM_CR1_CEN
#define step4TmrStart()  STEP4_TIM->CR1 |= TIM_CR1_CEN
#define step4BDTR() 

#endif

#ifdef STEP4_TIM1

#define STEP4_TIM TIM1

void step4TmrISR(void);

#define step4TmrInit()  __HAL_RCC_TIM1_CLK_ENABLE(); \
 STEP4_TIM->CR1 |= TIM_CR1_DIR;			  \
 STEP4_TIM->CR1 &= ~TIM_CR1_CEN
#define step4TmrStart() do {	\
  STEP4_TIM->EGR = TIM_EGR_UG;	\
  STEP4_TIM->CR1 |= TIM_CR1_CEN;	\
 } while (0)
#define step4BDTR() STEP4_TIM->BDTR |= TIM_BDTR_MOE

#endif

#ifdef STEP4_TIM

#define step4TmrClrIE() STEP4_TIM->DIER &= ~TIM_IT_UPDATE
#define step4TmrSetIE() STEP4_TIM->DIER |= TIM_IT_UPDATE
#define step4TmrClrIF() STEP4_TIM->SR = ~TIM_FLAG_UPDATE
#define step4TmrStop()  STEP4_TIM->CR1 &= ~TIM_CR1_CEN
#define step4TmrScl(x)  STEP4_TIM->PSC = (x)
#define step4TmrRead()  STEP4_TIM->CNT
#define step4TmrClr()   STEP4_TIM->CNT = 0
#define step4TmrCnt(x)  STEP4_TIM->CNT = (x)
#define step4TmrMax(x)  STEP4_TIM->ARR = ((x) - 1)
#define step4TmrSet(x)  STEP4_TIM->ARR = (x)
#define step4TmrMaxRead() STEP4_TIM->ARR

#ifdef STEP4_PWM1
/* channel 1 */
#define step4TmrCCR(x) STEP4_TIM->CCR1 = (x)
#define step4PWMMode() STEP4_TIM->CCMR1 = (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1)
#define step4PWMEna()  step4BDTR(); STEP4_TIM->CCER |= TIM_CCER_CC1E
#define step4PWMDis()  STEP4_TIM->CCER &= ~TIM_CCER_CC1E
#endif

#ifdef STEP4_PWM2
/* channel 1 */
#define step4TmrCCR(x) STEP4_TIM->CCR2 = (x)
#define step4PWMMode() STEP4_TIM->CCMR1 = (TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1)
#define step4PWMEna()  step4BDTR(); STEP4_TIM->CCER |= TIM_CCER_CC2E
#define step4PWMDis()  STEP4_TIM->CCER &= ~TIM_CCER_CC2E
#endif

#ifdef STEP4_PWM3
/* channel 3 */
#define step4TmrCCR(x) STEP4_TIM->CCR3 = (x)
#define step4PWMMode() STEP4_TIM->CCMR2 = (TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1)
#define step4PWMEna()  step4BDTR(); STEP4_TIM->CCER |= TIM_CCER_CC3E
#define step4PWMDis()  STEP4_TIM->CCER &= ~TIM_CCER_CC1E
#endif

#ifdef STEP4_PWM4
/* channel 4 */
#define step4TmrCCR(x) STEP4_TIM->CCR4 = (x)
#define step4PWMMode() STEP4_TIM->CCMR2 = (TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1)
#define step4PWMEna()  step4BDTR(); STEP4_TIM->CCER |= TIM_CCER_CC4E
#define step4PWMDis()  STEP4_TIM->CCER &= ~TIM_CCER_CC2E
#endif

#endif
