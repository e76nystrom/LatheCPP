#ifdef SPINDLE_TIM8

#define SP_TIM TIM8
#define SP_TIMER 8

#define spindleTmrISR(x) TIM8_UP_TIM13_IRQHandler(x)

#define spindleTmrInit() __HAL_RCC_TIM8_CLK_ENABLE(); \
 SP_TIM->CR1 |= TIM_CR1_DIR;			      \
 SP_TIM->CR1 &= ~TIM_CR1_CEN
#define spindleTmrStart() do {	\
  SP_TIM->EGR = TIM_EGR_UG;	\
  SP_TIM->CR1 |= TIM_CR1_CEN;	\
 } while (0)
#define spindleTmrBDTR() SP_TIM->BDTR |= TIM_BDTR_MOE

#define DIR_SPIN_PORT Dir5_GPIO_Port
#define DIR_SPIN_BIT Dir5_Pin

#endif /* SPINDLE_TIM8 */

#ifdef SPINDLE_TIM3

#define SP_TIM TIM3
#define SP_TIMER 3

#define spindleTmrISR(x) TIM3_IRQHandler(x)

#define spindleTmrInit() __HAL_RCC_TIM3_CLK_ENABLE(); \
 SP_TIM->CR1 |= TIM_CR1_DIR;			      \
 SP_TIM->CR1 &= ~TIM_CR1_CEN
#define spindleTmrStart() SP_TIM->CR1 |= TIM_CR1_CEN
#define spindleTmrBDTR() 

#define DIR_SPIN_PORT Dir3_GPIO_Port
#define DIR_SPIN_BIT Dir3_Pin

#endif /* SPINDLE_TIM3 */

#ifdef SP_TIM

#define spindleTmrClrIE()  SP_TIM->DIER &= ~TIM_IT_UPDATE
#define spindleTmrSetIE()  SP_TIM->DIER |= TIM_IT_UPDATE
#define spindleTmrClrIF()  SP_TIM->SR = ~TIM_FLAG_UPDATE
#define spindleTmrStop()   SP_TIM->CR1 &= ~TIM_CR1_CEN
#define spindleTmrScl(x)   SP_TIM->PSC = (x)
#define spindleTmrRead()   SP_TIM->CNT
#define spindleTmrClr()    SP_TIM->CNT = 0
#define spindleTmrCnt(x)   SP_TIM->CNT = (x)
#define spindleTmrMax(x)   SP_TIM->ARR = ((x) - 1)
#define spindleTmrSet(x)   SP_TIM->ARR = (x)
#define spindleTmrMaxRead() SP_TIM->ARR

#ifdef SPINDLE_PWM1
/* channel 1 */
#define spindleTmrCCR(x) SP_TIM->CCR1 = ((x) - 1)
#define spindlePWMMode() SP_TIM->CCMR1 = (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1)
#define spindlePWMEna() spindleTmrBDTR(); SP_TIM->CCER |= TIM_CCER_CC1E
#define spindlePWMDis()  SP_TIM->CCER &= ~TIM_CCER_CC1E
#ifdef SPINDLE_TIM3
#define STEP3_PWM1
#endif
#ifdef SPINDLE_TIM8
#define STEP5_PWM1
#endif
#endif /* SPINDLE_PWM1 */

#ifdef SPINDLE_PWM2
/* channel 2 */
#define spindleTmrCCR(x) SP_TIM->CCR2 = ((x) - 1)
#define spindlePWMMode() SP_TIM->CCMR1 = (TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1)
#define spindlePWMEna()  spindleTmrBDTR(); SP_TIM->CCER |= TIM_CCER_CC2E
#define spindlePWMDis()  SP_TIM->CCER &= ~TIM_CCER_CC2E
#ifdef SPINDLE_TIM3
#define STEP3_PWM2
#endif
#ifdef SPINDLE_TIM8
#define STEP5_PWM2
#endif
#endif /* SPINDLE_PWM2 */

#ifdef SPINDLE_PWM3
/* channel 3 */
#define spindleTmrCCR(x) SP_TIM->CCR3 = ((x) - 1)
#define spindlePWMMode() SP_TIM->CCMR2 = (TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1)
#define spindlePWMEna()  spindleTmrBDTR(); SP_TIM->CCER |= TIM_CCER_CC3E
#define spindlePWMDis()  SP_TIM->CCER &= ~TIM_CCER_CC3E
#ifdef SPINDLE_TIM3
#define STEP3_PWM3
#endif
#ifdef SPINDLE_TIM8
#define STEP5_PWM3
#endif
#endif /* SPINDLE_PWM3 */

#ifdef SPINDLE_PWM4
/* channel 4 */
#define spindleTmrCCR(x) SP_TIM->CCR4 = ((x) - 1)
#define spindlePWMMode() SP_TIM->CCMR2 = (TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1)
#define spindlePWMEna()  spindleTmrBDTR(); SP_TIM->CCER |= TIM_CCER_CC4E
#define spindlePWMDis()  SP_TIM->CCER &= ~TIM_CCER_CC4E
#ifdef SPINDLE_TIM3
#define STEP3_PWM4
#endif
#ifdef SPINDLE_TIM8
#define STEP5_PWM4
#endif
#endif  /* SPINDLE_PWM4 */

#ifdef SPINDLE_NOPWM
#define spindleTmrCCR(x)
#define spindlePWMMode()
#define spindlePWMEna()
#define spindlePWMDis()
#endif

#endif /* SP_TIM */

#define SP_FWD 1		/* spindle forward */
#define SP_REV -1		/* spindle reverse */

#define dirSpinFwd() DIR_SPIN_PORT->BSRR = spA.dirFwd
#define dirSpinRev() DIR_SPIN_PORT->BSRR = spA.dirRev

