/* index pulse timer */

#ifdef INDEX_TMR_TIM10

//void indexTmrISR(void);

#define IDX_TIM TIM10

#define indexTmrStart() __HAL_RCC_TIM10_CLK_ENABLE(); \
 IDX_TIM->CR1 |= TIM_CR1_CEN

#endif

#ifdef INDEX_TMR_TIM11

#define IDX_TIM TIM11

#define indexTmrISR(x) TIM1_TRG_COM_TIM11_IRQHandler(x)

#define indexTmrStart() __HAL_RCC_TIM11_CLK_ENABLE(); \
 IDX_TIM->CR1 |= TIM_CR1_CEN

#endif

#ifdef IDX_TIM

#define indexTmrClrIE() IDX_TIM->DIER &= ~TIM_IT_UPDATE
#define indexTmrSetIE() IDX_TIM->DIER |= TIM_IT_UPDATE
#define indexTmrIF()    (IDX_TIM->SR & TIM_SR_UIF)
#define indexTmrClrIF() IDX_TIM->SR &= ~(TIM_FLAG_CC1 | TIM_FLAG_UPDATE)
#define indexTmrInit()  IDX_TIM->CR1 &= ~TIM_CR1_CEN
#define indexTmrCont()  IDX_TIM->CR1 |= TIM_CR1_CEN
#define indexTmrStop()  IDX_TIM->CR1 &= ~TIM_CR1_CEN
#define indexTmrScl(x)  IDX_TIM->PSC = (x)
#define indexTmrRead()  IDX_TIM->CNT
#define indexTmrClr()   IDX_TIM->CNT = 0
#define indexTmrCnt(x)  IDX_TIM->CNT = x
#define indexTmrMax(x)  IDX_TIM->ARR = ((x) - 1)
#define indexTmrSet(x)  IDX_TIM->ARR = (x)
#define indexTmrMaxRead() IDX_TIM->ARR

#ifdef PWM_SHARED_INDEX
#ifdef PWM_PWM1
/* channel 1 */
#define pwmTmrCCR(x) IDX_TIM->CCR1 =  ((x) - 1)
#define pwmPWMMode() IDX_TIM->CCMR1 = (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1)
#define pwmPWMEna()  IDX_TIM->CCER |= TIM_CCER_CC1E
#define pwmPWMDis()  IDX_TIM->CCER &= ~TIM_CCER_CC1E
#endif
#endif
#endif
