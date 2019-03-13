/* index pulse timer */

#ifdef INDEX_TMR_TIM10

//void indexTmrISR(void);

#define INDEX_TIM TIM10

#define indexTmrInit() __HAL_RCC_TIM10_CLK_ENABLE(); \
 INDEX_TIM->CR1 |= TIM_CR1_CEN

#endif

#ifdef INDEX_TMR_TIM11

#define INDEX_TIM TIM11

#define indexTmrISR(x) TIM1_TRG_COM_TIM11_IRQHandler(x)

#define indexTmrStart() __HAL_RCC_TIM11_CLK_ENABLE(); \
 INDEX_TIM->CR1 |= TIM_CR1_CEN

#endif

#ifdef INDEX_TIM

#define indexTmrClrIE() INDEX_TIM->DIER &= ~TIM_IT_UPDATE
#define indexTmrSetIE() INDEX_TIM->DIER |= TIM_IT_UPDATE
#define indexTmrIF()    (INDEX_TIM->SR & TIM_SR_UIF)
#define indexTmrClrIF() INDEX_TIM->SR &= ~(TIM_FLAG_CC1 | TIM_FLAG_UPDATE)
#define indexTmrInit()  INDEX_TIM->CR1 &= ~TIM_CR1_CEN
#define indexTmrStart()  INDEX_TIM->CR1 |= TIM_CR1_CEN
#define indexTmrStop()  INDEX_TIM->CR1 &= ~TIM_CR1_CEN
#define indexTmrScl(x)  INDEX_TIM->PSC = (x)
#define indexTmrRead()  INDEX_TIM->CNT
#define indexTmrCntClr() INDEX_TIM->CNT = 0
#define indexTmrCnt(x)  INDEX_TIM->CNT = x
#define indexTmrMax(x)  INDEX_TIM->ARR = ((x) - 1)
#define indexTmrSet(x)  INDEX_TIM->ARR = (x)
#define indexTmrMaxRead() INDEX_TIM->ARR

#ifdef PWM_SHARED_INDEX
#ifdef PWM_PWM1
/* channel 1 */
#define pwmTmrCCR(x) INDEX_TIM->CCR1 =  ((x) - 1)
#define pwmPWMMode() INDEX_TIM->CCMR1 = (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1)
#define pwmPWMEna()  INDEX_TIM->CCER |= TIM_CCER_CC1E
#define pwmPWMDis()  INDEX_TIM->CCER &= ~TIM_CCER_CC1E
#endif
#endif
#endif
