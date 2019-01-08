/* usec timer */

#ifdef USEC_TMR_TIM6

#define USEC_TIM TIM6

#ifdef __cplusplus
#ifdef __STM32F4xx_HAL_RCC_EX_H

inline void usecTmrStart()
{
 __HAL_RCC_TIM6_CLK_ENABLE();
 USEC_TIM->CR1 |= TIM_CR1_CEN;
}

#endif
#else

#define usecTmrStart() __HAL_RCC_TIM6_CLK_ENABLE(); \
 USEC_TIM->CR1 |= TIM_CR1_CEN

#endif
#endif

#ifdef USEC_TIM_TIM10

#define USEC_TIM TIM10

#ifdef __cplusplus
#ifdef __STM32F4xx_HAL_RCC_EX_H

inline void usecTmrStart()
{
 __HAL_RCC_TIM10_CLK_ENABLE();
 USEC_TIM->CR1 |= TIM_CR1_CEN;
}

#endif
#else

#define usecTmrStart() __HAL_RCC_TIM10_CLK_ENABLE(); \
 USEC_TIM->CR1 |= TIM_CR1_CEN

#endif
#endif

#ifdef USEC_TIM
#ifdef __cplusplus

inline void usecTmrInit()
{
 USEC_TIM->CR1 &= ~TIM_CR1_CEN;
}

inline void usecTmrScl(uint16_t x)
{
 USEC_TIM->PSC = x;
}

inline uint16_t usecTmrRead()
{
 return(USEC_TIM->CNT);
}

inline void usecTmrSet(uint16_t x)
{
 USEC_TIM->ARR = x;
}

#else

#define usecTmrInit()  USEC_TIM->CR1 &= ~TIM_CR1_CEN
#define usecTmrScl(x)  USEC_TIM->PSC = (x)
#define usecTmrRead()  USEC_TIM->CNT
#define usecTmrSet(x)  USEC_TIM->ARR = (x)

#endif
#endif

#ifdef USEC_SHARED_INDEX
#ifdef __cplusplus

inline uint16_t usecTmrRead()
{
 return(INDEX_TIM->CNT);
}

#else

#define usecTmrRead()  INDEX_TIM->CNT

#endif
#endif

