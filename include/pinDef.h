#if defined(__STM32F4xx_HAL_H) || defined(__STM32F7xx_HAL_H) || defined(STM32H7xx_HAL_H)
#if !defined(__PINDEF_H)
#define __PINDEF_H

#ifdef Index_Pin
#define idx_Pin
inline uint16_t idx() {return((Index_GPIO_Port->IDR & Index_Pin) != 0);}
inline uint16_t idxIsSet() {return((Index_GPIO_Port->IDR & Index_Pin) != 0);}
inline uint16_t idxIsClr() {return((Index_GPIO_Port->IDR & Index_Pin) == 0);}
#else
inline uint16_t idx() {return(0);}
inline uint16_t idxIsSet() {return(0);}
inline uint16_t idxIsClr() {return(0);}
#endif

#ifdef ZA_Pin
#define zA_Pin
inline uint16_t zA() {return((ZA_GPIO_Port->IDR & ZA_Pin) != 0);}
inline uint16_t zAIsSet() {return((ZA_GPIO_Port->IDR & ZA_Pin) != 0);}
inline uint16_t zAIsClr() {return((ZA_GPIO_Port->IDR & ZA_Pin) == 0);}
#else
inline uint16_t zA() {return(0);}
inline uint16_t zAIsSet() {return(0);}
inline uint16_t zAIsClr() {return(0);}
#endif

#ifdef ZB_Pin
#define zB_Pin
inline uint16_t zB() {return((ZB_GPIO_Port->IDR & ZB_Pin) != 0);}
inline uint16_t zBIsSet() {return((ZB_GPIO_Port->IDR & ZB_Pin) != 0);}
inline uint16_t zBIsClr() {return((ZB_GPIO_Port->IDR & ZB_Pin) == 0);}
#else
inline uint16_t zB() {return(0);}
inline uint16_t zBIsSet() {return(0);}
inline uint16_t zBIsClr() {return(0);}
#endif

#ifdef XA_Pin
#define xA_Pin
inline uint16_t xA() {return((XA_GPIO_Port->IDR & XA_Pin) != 0);}
inline uint16_t xAIsSet() {return((XA_GPIO_Port->IDR & XA_Pin) != 0);}
inline uint16_t xAIsClr() {return((XA_GPIO_Port->IDR & XA_Pin) == 0);}
#else
inline uint16_t xA() {return(0);}
inline uint16_t xAIsSet() {return(0);}
inline uint16_t xAIsClr() {return(0);}
#endif

#ifdef XB_Pin
#define xB_Pin
inline uint16_t xB() {return((XB_GPIO_Port->IDR & XB_Pin) != 0);}
inline uint16_t xBIsSet() {return((XB_GPIO_Port->IDR & XB_Pin) != 0);}
inline uint16_t xBIsClr() {return((XB_GPIO_Port->IDR & XB_Pin) == 0);}
#else
inline uint16_t xB() {return(0);}
inline uint16_t xBIsSet() {return(0);}
inline uint16_t xBIsClr() {return(0);}
#endif

#ifdef ZFLag_Pin
#define spEncDir_Pin
inline uint16_t spEncDir() {return((ZFLag_GPIO_Port->IDR & ZFLag_Pin) != 0);}
inline uint16_t spEncDirIsSet() {return((ZFLag_GPIO_Port->IDR & ZFLag_Pin) != 0);}
inline uint16_t spEncDirIsClr() {return((ZFLag_GPIO_Port->IDR & ZFLag_Pin) == 0);}
#else
inline uint16_t spEncDir() {return(0);}
inline uint16_t spEncDirIsSet() {return(0);}
inline uint16_t spEncDirIsClr() {return(0);}
#endif

#ifdef JogA1_Pin
#define jogA1_Pin
inline uint16_t jogA1() {return((JogA1_GPIO_Port->IDR & JogA1_Pin) != 0);}
inline uint16_t jogA1IsSet() {return((JogA1_GPIO_Port->IDR & JogA1_Pin) != 0);}
inline uint16_t jogA1IsClr() {return((JogA1_GPIO_Port->IDR & JogA1_Pin) == 0);}
#else
inline uint16_t jogA1() {return(0);}
inline uint16_t jogA1IsSet() {return(0);}
inline uint16_t jogA1IsClr() {return(0);}
#endif

#ifdef JogB1_Pin
#define jogB1_Pin
inline uint16_t jogB1() {return((JogB1_GPIO_Port->IDR & JogB1_Pin) != 0);}
inline uint16_t jogB1IsSet() {return((JogB1_GPIO_Port->IDR & JogB1_Pin) != 0);}
inline uint16_t jogB1IsClr() {return((JogB1_GPIO_Port->IDR & JogB1_Pin) == 0);}
#else
inline uint16_t jogB1() {return(0);}
inline uint16_t jogB1IsSet() {return(0);}
inline uint16_t jogB1IsClr() {return(0);}
#endif

#ifdef JogA2_Pin
#define jogA2_Pin
inline uint16_t jogA2() {return((JogA2_GPIO_Port->IDR & JogA2_Pin) != 0);}
inline uint16_t jogA2IsSet() {return((JogA2_GPIO_Port->IDR & JogA2_Pin) != 0);}
inline uint16_t jogA2IsClr() {return((JogA2_GPIO_Port->IDR & JogA2_Pin) == 0);}
#else
inline uint16_t jogA2() {return(0);}
inline uint16_t jogA2IsSet() {return(0);}
inline uint16_t jogA2IsClr() {return(0);}
#endif

#ifdef JogB2_Pin
#define jogB2_Pin
inline uint16_t jogB2() {return((JogB2_GPIO_Port->IDR & JogB2_Pin) != 0);}
inline uint16_t jogB2IsSet() {return((JogB2_GPIO_Port->IDR & JogB2_Pin) != 0);}
inline uint16_t jogB2IsClr() {return((JogB2_GPIO_Port->IDR & JogB2_Pin) == 0);}
#else
inline uint16_t jogB2() {return(0);}
inline uint16_t jogB2IsSet() {return(0);}
inline uint16_t jogB2IsClr() {return(0);}
#endif

#ifdef Step1_Pin
inline void stpZSet() {Step1_GPIO_Port->BSRR = Step1_Pin;}
inline void stpZClr() {Step1_GPIO_Port->BSRR = (Step1_Pin << 16);}
inline uint16_t stpZRead() {return((Step1_GPIO_Port->ODR & Step1_Pin) != 0);}
#else
inline void stpZSet() {}
inline void stpZClr() {}
inline uint16_t stpZ() {return(0);}
#endif

#ifdef Step2_Pin
inline void stpXSet() {Step2_GPIO_Port->BSRR = Step2_Pin;}
inline void stpXClr() {Step2_GPIO_Port->BSRR = (Step2_Pin << 16);}
inline uint16_t stpXRead() {return((Step2_GPIO_Port->ODR & Step2_Pin) != 0);}
#else
inline void stpXSet() {}
inline void stpXClr() {}
inline uint16_t stpX() {return(0);}
#endif

#ifdef Step3_Pin
inline void step3Set() {Step3_GPIO_Port->BSRR = Step3_Pin;}
inline void step3Clr() {Step3_GPIO_Port->BSRR = (Step3_Pin << 16);}
inline uint16_t step3Read() {return((Step3_GPIO_Port->ODR & Step3_Pin) != 0);}
#else
inline void step3Set() {}
inline void step3Clr() {}
inline uint16_t step3() {return(0);}
#endif

#ifdef Step4_Pin
inline void step4Set() {Step4_GPIO_Port->BSRR = Step4_Pin;}
inline void step4Clr() {Step4_GPIO_Port->BSRR = (Step4_Pin << 16);}
inline uint16_t step4Read() {return((Step4_GPIO_Port->ODR & Step4_Pin) != 0);}
#else
inline void step4Set() {}
inline void step4Clr() {}
inline uint16_t step4() {return(0);}
#endif

#ifdef Step5_Pin
inline void step5Set() {Step5_GPIO_Port->BSRR = Step5_Pin;}
inline void step5Clr() {Step5_GPIO_Port->BSRR = (Step5_Pin << 16);}
inline uint16_t step5Read() {return((Step5_GPIO_Port->ODR & Step5_Pin) != 0);}
#else
inline void step5Set() {}
inline void step5Clr() {}
inline uint16_t step5() {return(0);}
#endif

#ifdef Dir1_Pin
inline void dirZSet() {Dir1_GPIO_Port->BSRR = Dir1_Pin;}
inline void dirZClr() {Dir1_GPIO_Port->BSRR = (Dir1_Pin << 16);}
inline uint16_t dirZRead() {return((Dir1_GPIO_Port->ODR & Dir1_Pin) != 0);}
#else
inline void dirZSet() {}
inline void dirZClr() {}
inline uint16_t dirZ() {return(0);}
#endif

#ifdef Dir2_Pin
inline void dirXSet() {Dir2_GPIO_Port->BSRR = Dir2_Pin;}
inline void dirXClr() {Dir2_GPIO_Port->BSRR = (Dir2_Pin << 16);}
inline uint16_t dirXRead() {return((Dir2_GPIO_Port->ODR & Dir2_Pin) != 0);}
#else
inline void dirXSet() {}
inline void dirXClr() {}
inline uint16_t dirX() {return(0);}
#endif

#ifdef Dir3_Pin
inline void dir3Set() {Dir3_GPIO_Port->BSRR = Dir3_Pin;}
inline void dir3Clr() {Dir3_GPIO_Port->BSRR = (Dir3_Pin << 16);}
inline uint16_t dir3Read() {return((Dir3_GPIO_Port->ODR & Dir3_Pin) != 0);}
#else
inline void dir3Set() {}
inline void dir3Clr() {}
inline uint16_t dir3() {return(0);}
#endif

#ifdef Dir4_Pin
inline void dir4Set() {Dir4_GPIO_Port->BSRR = Dir4_Pin;}
inline void dir4Clr() {Dir4_GPIO_Port->BSRR = (Dir4_Pin << 16);}
inline uint16_t dir4Read() {return((Dir4_GPIO_Port->ODR & Dir4_Pin) != 0);}
#else
inline void dir4Set() {}
inline void dir4Clr() {}
inline uint16_t dir4() {return(0);}
#endif

#ifdef Dir5_Pin
inline void dir5Set() {Dir5_GPIO_Port->BSRR = Dir5_Pin;}
inline void dir5Clr() {Dir5_GPIO_Port->BSRR = (Dir5_Pin << 16);}
inline uint16_t dir5Read() {return((Dir5_GPIO_Port->ODR & Dir5_Pin) != 0);}
#else
inline void dir5Set() {}
inline void dir5Clr() {}
inline uint16_t dir5() {return(0);}
#endif

#ifdef Pin1_Pin
inline void pin1Set() {Pin1_GPIO_Port->BSRR = Pin1_Pin;}
inline void pin1Clr() {Pin1_GPIO_Port->BSRR = (Pin1_Pin << 16);}
inline uint16_t pin1Read() {return((Pin1_GPIO_Port->ODR & Pin1_Pin) != 0);}
#else
inline void pin1Set() {}
inline void pin1Clr() {}
inline uint16_t pin1() {return(0);}
#endif

#ifdef Pin1_Pin
inline void spRunSet() {Pin1_GPIO_Port->BSRR = Pin1_Pin;}
inline void spRunClr() {Pin1_GPIO_Port->BSRR = (Pin1_Pin << 16);}
inline uint16_t spRunRead() {return((Pin1_GPIO_Port->ODR & Pin1_Pin) != 0);}
#else
inline void spRunSet() {}
inline void spRunClr() {}
inline uint16_t spRun() {return(0);}
#endif

#ifdef Pin14_Pin
inline void pin14Set() {Pin14_GPIO_Port->BSRR = Pin14_Pin;}
inline void pin14Clr() {Pin14_GPIO_Port->BSRR = (Pin14_Pin << 16);}
inline uint16_t pin14Read() {return((Pin14_GPIO_Port->ODR & Pin14_Pin) != 0);}
#else
inline void pin14Set() {}
inline void pin14Clr() {}
inline uint16_t pin14() {return(0);}
#endif

#ifdef Pin16_Pin
inline void pin16Set() {Pin16_GPIO_Port->BSRR = Pin16_Pin;}
inline void pin16Clr() {Pin16_GPIO_Port->BSRR = (Pin16_Pin << 16);}
inline uint16_t pin16Read() {return((Pin16_GPIO_Port->ODR & Pin16_Pin) != 0);}
#else
inline void pin16Set() {}
inline void pin16Clr() {}
inline uint16_t pin16() {return(0);}
#endif

#ifdef Pin17_Pin
inline void pin17Set() {Pin17_GPIO_Port->BSRR = Pin17_Pin;}
inline void pin17Clr() {Pin17_GPIO_Port->BSRR = (Pin17_Pin << 16);}
inline uint16_t pin17Read() {return((Pin17_GPIO_Port->ODR & Pin17_Pin) != 0);}
#else
inline void pin17Set() {}
inline void pin17Clr() {}
inline uint16_t pin17() {return(0);}
#endif

#ifdef Pin10_Pin
#define pin10_Pin
inline uint16_t pin10() {return((Pin10_GPIO_Port->IDR & Pin10_Pin) != 0);}
inline uint16_t pin10IsSet() {return((Pin10_GPIO_Port->IDR & Pin10_Pin) != 0);}
inline uint16_t pin10IsClr() {return((Pin10_GPIO_Port->IDR & Pin10_Pin) == 0);}
#else
inline uint16_t pin10() {return(0);}
inline uint16_t pin10IsSet() {return(0);}
inline uint16_t pin10IsClr() {return(0);}
#endif

#ifdef Pin11_Pin
#define pin11_Pin
inline uint16_t pin11() {return((Pin11_GPIO_Port->IDR & Pin11_Pin) != 0);}
inline uint16_t pin11IsSet() {return((Pin11_GPIO_Port->IDR & Pin11_Pin) != 0);}
inline uint16_t pin11IsClr() {return((Pin11_GPIO_Port->IDR & Pin11_Pin) == 0);}
#else
inline uint16_t pin11() {return(0);}
inline uint16_t pin11IsSet() {return(0);}
inline uint16_t pin11IsClr() {return(0);}
#endif

#ifdef Pin12_Pin
#define pin12_Pin
inline uint16_t pin12() {return((Pin12_GPIO_Port->IDR & Pin12_Pin) != 0);}
inline uint16_t pin12IsSet() {return((Pin12_GPIO_Port->IDR & Pin12_Pin) != 0);}
inline uint16_t pin12IsClr() {return((Pin12_GPIO_Port->IDR & Pin12_Pin) == 0);}
#else
inline uint16_t pin12() {return(0);}
inline uint16_t pin12IsSet() {return(0);}
inline uint16_t pin12IsClr() {return(0);}
#endif

#ifdef Pin13_Pin
#define pin13_Pin
inline uint16_t pin13() {return((Pin13_GPIO_Port->IDR & Pin13_Pin) != 0);}
inline uint16_t pin13IsSet() {return((Pin13_GPIO_Port->IDR & Pin13_Pin) != 0);}
inline uint16_t pin13IsClr() {return((Pin13_GPIO_Port->IDR & Pin13_Pin) == 0);}
#else
inline uint16_t pin13() {return(0);}
inline uint16_t pin13IsSet() {return(0);}
inline uint16_t pin13IsClr() {return(0);}
#endif

#ifdef Pin15_Pin
#define pin15_Pin
inline uint16_t pin15() {return((Pin15_GPIO_Port->IDR & Pin15_Pin) != 0);}
inline uint16_t pin15IsSet() {return((Pin15_GPIO_Port->IDR & Pin15_Pin) != 0);}
inline uint16_t pin15IsClr() {return((Pin15_GPIO_Port->IDR & Pin15_Pin) == 0);}
#else
inline uint16_t pin15() {return(0);}
inline uint16_t pin15IsSet() {return(0);}
inline uint16_t pin15IsClr() {return(0);}
#endif

#ifdef Pin10_Pin
#define eStop_Pin
inline uint16_t eStop() {return((Pin10_GPIO_Port->IDR & Pin10_Pin) != 0);}
inline uint16_t eStopIsSet() {return((Pin10_GPIO_Port->IDR & Pin10_Pin) != 0);}
inline uint16_t eStopIsClr() {return((Pin10_GPIO_Port->IDR & Pin10_Pin) == 0);}
#else
inline uint16_t eStop() {return(0);}
inline uint16_t eStopIsSet() {return(0);}
inline uint16_t eStopIsClr() {return(0);}
#endif

#ifdef Pin11_Pin
#define limit_Pin
inline uint16_t limit() {return((Pin11_GPIO_Port->IDR & Pin11_Pin) != 0);}
inline uint16_t limitIsSet() {return((Pin11_GPIO_Port->IDR & Pin11_Pin) != 0);}
inline uint16_t limitIsClr() {return((Pin11_GPIO_Port->IDR & Pin11_Pin) == 0);}
#else
inline uint16_t limit() {return(0);}
inline uint16_t limitIsSet() {return(0);}
inline uint16_t limitIsClr() {return(0);}
#endif

#ifdef Pin12_Pin
#define xHome_Pin
inline uint16_t xHome() {return((Pin12_GPIO_Port->IDR & Pin12_Pin) != 0);}
inline uint16_t xHomeIsSet() {return((Pin12_GPIO_Port->IDR & Pin12_Pin) != 0);}
inline uint16_t xHomeIsClr() {return((Pin12_GPIO_Port->IDR & Pin12_Pin) == 0);}
#else
inline uint16_t xHome() {return(0);}
inline uint16_t xHomeIsSet() {return(0);}
inline uint16_t xHomeIsClr() {return(0);}
#endif

#ifdef PinA2_Pin
#define pinA2_Pin
inline uint16_t pinA2() {return((PinA2_GPIO_Port->IDR & PinA2_Pin) != 0);}
inline uint16_t pinA2IsSet() {return((PinA2_GPIO_Port->IDR & PinA2_Pin) != 0);}
inline uint16_t pinA2IsClr() {return((PinA2_GPIO_Port->IDR & PinA2_Pin) == 0);}
#else
inline uint16_t pinA2() {return(0);}
inline uint16_t pinA2IsSet() {return(0);}
inline uint16_t pinA2IsClr() {return(0);}
#endif

#ifdef PinA3_Pin
#define pinA3_Pin
inline uint16_t pinA3() {return((PinA3_GPIO_Port->IDR & PinA3_Pin) != 0);}
inline uint16_t pinA3IsSet() {return((PinA3_GPIO_Port->IDR & PinA3_Pin) != 0);}
inline uint16_t pinA3IsClr() {return((PinA3_GPIO_Port->IDR & PinA3_Pin) == 0);}
#else
inline uint16_t pinA3() {return(0);}
inline uint16_t pinA3IsSet() {return(0);}
inline uint16_t pinA3IsClr() {return(0);}
#endif

#ifdef PinA4_Pin
#define pinA4_Pin
inline uint16_t pinA4() {return((PinA4_GPIO_Port->IDR & PinA4_Pin) != 0);}
inline uint16_t pinA4IsSet() {return((PinA4_GPIO_Port->IDR & PinA4_Pin) != 0);}
inline uint16_t pinA4IsClr() {return((PinA4_GPIO_Port->IDR & PinA4_Pin) == 0);}
#else
inline uint16_t pinA4() {return(0);}
inline uint16_t pinA4IsSet() {return(0);}
inline uint16_t pinA4IsClr() {return(0);}
#endif

#ifdef PinA5_Pin
#define pinA5_Pin
inline uint16_t pinA5() {return((PinA5_GPIO_Port->IDR & PinA5_Pin) != 0);}
inline uint16_t pinA5IsSet() {return((PinA5_GPIO_Port->IDR & PinA5_Pin) != 0);}
inline uint16_t pinA5IsClr() {return((PinA5_GPIO_Port->IDR & PinA5_Pin) == 0);}
#else
inline uint16_t pinA5() {return(0);}
inline uint16_t pinA5IsSet() {return(0);}
inline uint16_t pinA5IsClr() {return(0);}
#endif

#ifdef PinA5_Pin
#define pinA6_Pin
inline uint16_t pinA6() {return((PinA5_GPIO_Port->IDR & PinA5_Pin) != 0);}
inline uint16_t pinA6IsSet() {return((PinA5_GPIO_Port->IDR & PinA5_Pin) != 0);}
inline uint16_t pinA6IsClr() {return((PinA5_GPIO_Port->IDR & PinA5_Pin) == 0);}
#else
inline uint16_t pinA6() {return(0);}
inline uint16_t pinA6IsSet() {return(0);}
inline uint16_t pinA6IsClr() {return(0);}
#endif

#ifdef PinA7_Pin
#define pinA7_Pin
inline uint16_t pinA7() {return((PinA7_GPIO_Port->IDR & PinA7_Pin) != 0);}
inline uint16_t pinA7IsSet() {return((PinA7_GPIO_Port->IDR & PinA7_Pin) != 0);}
inline uint16_t pinA7IsClr() {return((PinA7_GPIO_Port->IDR & PinA7_Pin) == 0);}
#else
inline uint16_t pinA7() {return(0);}
inline uint16_t pinA7IsSet() {return(0);}
inline uint16_t pinA7IsClr() {return(0);}
#endif

#ifdef PinA8_Pin
#define pinA8_Pin
inline uint16_t pinA8() {return((PinA8_GPIO_Port->IDR & PinA8_Pin) != 0);}
inline uint16_t pinA8IsSet() {return((PinA8_GPIO_Port->IDR & PinA8_Pin) != 0);}
inline uint16_t pinA8IsClr() {return((PinA8_GPIO_Port->IDR & PinA8_Pin) == 0);}
#else
inline uint16_t pinA8() {return(0);}
inline uint16_t pinA8IsSet() {return(0);}
inline uint16_t pinA8IsClr() {return(0);}
#endif

#ifdef PinA9_Pin
#define pinA9_Pin
inline uint16_t pinA9() {return((PinA9_GPIO_Port->IDR & PinA9_Pin) != 0);}
inline uint16_t pinA9IsSet() {return((PinA9_GPIO_Port->IDR & PinA9_Pin) != 0);}
inline uint16_t pinA9IsClr() {return((PinA9_GPIO_Port->IDR & PinA9_Pin) == 0);}
#else
inline uint16_t pinA9() {return(0);}
inline uint16_t pinA9IsSet() {return(0);}
inline uint16_t pinA9IsClr() {return(0);}
#endif

#ifdef PinA10_Pin
#define pinA10_Pin
inline uint16_t pinA10() {return((PinA10_GPIO_Port->IDR & PinA10_Pin) != 0);}
inline uint16_t pinA10IsSet() {return((PinA10_GPIO_Port->IDR & PinA10_Pin) != 0);}
inline uint16_t pinA10IsClr() {return((PinA10_GPIO_Port->IDR & PinA10_Pin) == 0);}
#else
inline uint16_t pinA10() {return(0);}
inline uint16_t pinA10IsSet() {return(0);}
inline uint16_t pinA10IsClr() {return(0);}
#endif

#ifdef PinA11_Pin
#define pinA11_Pin
inline uint16_t pinA11() {return((PinA11_GPIO_Port->IDR & PinA11_Pin) != 0);}
inline uint16_t pinA11IsSet() {return((PinA11_GPIO_Port->IDR & PinA11_Pin) != 0);}
inline uint16_t pinA11IsClr() {return((PinA11_GPIO_Port->IDR & PinA11_Pin) == 0);}
#else
inline uint16_t pinA11() {return(0);}
inline uint16_t pinA11IsSet() {return(0);}
inline uint16_t pinA11IsClr() {return(0);}
#endif

#ifdef PinA12_Pin
#define pinA12_Pin
inline uint16_t pinA12() {return((PinA12_GPIO_Port->IDR & PinA12_Pin) != 0);}
inline uint16_t pinA12IsSet() {return((PinA12_GPIO_Port->IDR & PinA12_Pin) != 0);}
inline uint16_t pinA12IsClr() {return((PinA12_GPIO_Port->IDR & PinA12_Pin) == 0);}
#else
inline uint16_t pinA12() {return(0);}
inline uint16_t pinA12IsSet() {return(0);}
inline uint16_t pinA12IsClr() {return(0);}
#endif

#ifdef PinA13_Pin
#define pinA13_Pin
inline uint16_t pinA13() {return((PinA13_GPIO_Port->IDR & PinA13_Pin) != 0);}
inline uint16_t pinA13IsSet() {return((PinA13_GPIO_Port->IDR & PinA13_Pin) != 0);}
inline uint16_t pinA13IsClr() {return((PinA13_GPIO_Port->IDR & PinA13_Pin) == 0);}
#else
inline uint16_t pinA13() {return(0);}
inline uint16_t pinA13IsSet() {return(0);}
inline uint16_t pinA13IsClr() {return(0);}
#endif

#ifdef PinA15_Pin
#define pinA15_Pin
inline uint16_t pinA15() {return((PinA15_GPIO_Port->IDR & PinA15_Pin) != 0);}
inline uint16_t pinA15IsSet() {return((PinA15_GPIO_Port->IDR & PinA15_Pin) != 0);}
inline uint16_t pinA15IsClr() {return((PinA15_GPIO_Port->IDR & PinA15_Pin) == 0);}
#else
inline uint16_t pinA15() {return(0);}
inline uint16_t pinA15IsSet() {return(0);}
inline uint16_t pinA15IsClr() {return(0);}
#endif

#ifdef PinA11_Pin
#define xPosLim_Pin
inline uint16_t xPosLim() {return((PinA11_GPIO_Port->IDR & PinA11_Pin) != 0);}
inline uint16_t xPosLimIsSet() {return((PinA11_GPIO_Port->IDR & PinA11_Pin) != 0);}
inline uint16_t xPosLimIsClr() {return((PinA11_GPIO_Port->IDR & PinA11_Pin) == 0);}
#else
inline uint16_t xPosLim() {return(0);}
inline uint16_t xPosLimIsSet() {return(0);}
inline uint16_t xPosLimIsClr() {return(0);}
#endif

#ifdef PinA12_Pin
#define xNegLim_Pin
inline uint16_t xNegLim() {return((PinA12_GPIO_Port->IDR & PinA12_Pin) != 0);}
inline uint16_t xNegLimIsSet() {return((PinA12_GPIO_Port->IDR & PinA12_Pin) != 0);}
inline uint16_t xNegLimIsClr() {return((PinA12_GPIO_Port->IDR & PinA12_Pin) == 0);}
#else
inline uint16_t xNegLim() {return(0);}
inline uint16_t xNegLimIsSet() {return(0);}
inline uint16_t xNegLimIsClr() {return(0);}
#endif

#ifdef PinA13_Pin
#define xAHome_Pin
inline uint16_t xAHome() {return((PinA13_GPIO_Port->IDR & PinA13_Pin) != 0);}
inline uint16_t xAHomeIsSet() {return((PinA13_GPIO_Port->IDR & PinA13_Pin) != 0);}
inline uint16_t xAHomeIsClr() {return((PinA13_GPIO_Port->IDR & PinA13_Pin) == 0);}
#else
inline uint16_t xAHome() {return(0);}
inline uint16_t xAHomeIsSet() {return(0);}
inline uint16_t xAHomeIsClr() {return(0);}
#endif

#ifdef PinA2_Pin
#define zPosLim_Pin
inline uint16_t zPosLim() {return((PinA2_GPIO_Port->IDR & PinA2_Pin) != 0);}
inline uint16_t zPosLimIsSet() {return((PinA2_GPIO_Port->IDR & PinA2_Pin) != 0);}
inline uint16_t zPosLimIsClr() {return((PinA2_GPIO_Port->IDR & PinA2_Pin) == 0);}
#else
inline uint16_t zPosLim() {return(0);}
inline uint16_t zPosLimIsSet() {return(0);}
inline uint16_t zPosLimIsClr() {return(0);}
#endif

#ifdef PinA3_Pin
#define zNegLim_Pin
inline uint16_t zNegLim() {return((PinA3_GPIO_Port->IDR & PinA3_Pin) != 0);}
inline uint16_t zNegLimIsSet() {return((PinA3_GPIO_Port->IDR & PinA3_Pin) != 0);}
inline uint16_t zNegLimIsClr() {return((PinA3_GPIO_Port->IDR & PinA3_Pin) == 0);}
#else
inline uint16_t zNegLim() {return(0);}
inline uint16_t zNegLimIsSet() {return(0);}
inline uint16_t zNegLimIsClr() {return(0);}
#endif

#ifdef PinA4_Pin
#define zAHome_Pin
inline uint16_t zAHome() {return((PinA4_GPIO_Port->IDR & PinA4_Pin) != 0);}
inline uint16_t zAHomeIsSet() {return((PinA4_GPIO_Port->IDR & PinA4_Pin) != 0);}
inline uint16_t zAHomeIsClr() {return((PinA4_GPIO_Port->IDR & PinA4_Pin) == 0);}
#else
inline uint16_t zAHome() {return(0);}
inline uint16_t zAHomeIsSet() {return(0);}
inline uint16_t zAHomeIsClr() {return(0);}
#endif

#ifdef PinA16_Pin
inline void pinA16Set() {PinA16_GPIO_Port->BSRR = PinA16_Pin;}
inline void pinA16Clr() {PinA16_GPIO_Port->BSRR = (PinA16_Pin << 16);}
inline uint16_t pinA16Read() {return((PinA16_GPIO_Port->ODR & PinA16_Pin) != 0);}
#else
inline void pinA16Set() {}
inline void pinA16Clr() {}
inline uint16_t pinA16() {return(0);}
#endif

#ifdef PinA17_Pin
inline void pinA17Set() {PinA17_GPIO_Port->BSRR = PinA17_Pin;}
inline void pinA17Clr() {PinA17_GPIO_Port->BSRR = (PinA17_Pin << 16);}
inline uint16_t pinA17Read() {return((PinA17_GPIO_Port->ODR & PinA17_Pin) != 0);}
#else
inline void pinA17Set() {}
inline void pinA17Clr() {}
inline uint16_t pinA17() {return(0);}
#endif

#ifdef ZFlag_Pin
inline void startSet() {ZFlag_GPIO_Port->BSRR = ZFlag_Pin;}
inline void startClr() {ZFlag_GPIO_Port->BSRR = (ZFlag_Pin << 16);}
inline uint16_t startRead() {return((ZFlag_GPIO_Port->ODR & ZFlag_Pin) != 0);}
#else
inline void startSet() {}
inline void startClr() {}
inline uint16_t start() {return(0);}
#endif

#ifdef XFlag_Pin
#define ready_Pin
inline uint16_t ready() {return((XFlag_GPIO_Port->IDR & XFlag_Pin) != 0);}
inline uint16_t readyIsSet() {return((XFlag_GPIO_Port->IDR & XFlag_Pin) != 0);}
inline uint16_t readyIsClr() {return((XFlag_GPIO_Port->IDR & XFlag_Pin) == 0);}
#else
inline uint16_t ready() {return(0);}
inline uint16_t readyIsSet() {return(0);}
inline uint16_t readyIsClr() {return(0);}
#endif

#ifdef XFlag_Pin
#define xFlagX_Pin
inline uint16_t xFlagX() {return((XFlag_GPIO_Port->IDR & XFlag_Pin) != 0);}
inline uint16_t xFlagXIsSet() {return((XFlag_GPIO_Port->IDR & XFlag_Pin) != 0);}
inline uint16_t xFlagXIsClr() {return((XFlag_GPIO_Port->IDR & XFlag_Pin) == 0);}
#else
inline uint16_t xFlagX() {return(0);}
inline uint16_t xFlagXIsSet() {return(0);}
inline uint16_t xFlagXIsClr() {return(0);}
#endif

#ifdef ZFlag_Pin
#define zFlagX_Pin
inline uint16_t zFlagX() {return((ZFlag_GPIO_Port->IDR & ZFlag_Pin) != 0);}
inline uint16_t zFlagXIsSet() {return((ZFlag_GPIO_Port->IDR & ZFlag_Pin) != 0);}
inline uint16_t zFlagXIsClr() {return((ZFlag_GPIO_Port->IDR & ZFlag_Pin) == 0);}
#else
inline uint16_t zFlagX() {return(0);}
inline uint16_t zFlagXIsSet() {return(0);}
inline uint16_t zFlagXIsClr() {return(0);}
#endif

#ifdef Pin1_Pin
inline void aSet() {Pin1_GPIO_Port->BSRR = Pin1_Pin;}
inline void aClr() {Pin1_GPIO_Port->BSRR = (Pin1_Pin << 16);}
inline uint16_t aRead() {return((Pin1_GPIO_Port->ODR & Pin1_Pin) != 0);}
#else
inline void aSet() {}
inline void aClr() {}
inline uint16_t a() {return(0);}
#endif

#ifdef Pin14_Pin
inline void bSet() {Pin14_GPIO_Port->BSRR = Pin14_Pin;}
inline void bClr() {Pin14_GPIO_Port->BSRR = (Pin14_Pin << 16);}
inline uint16_t bRead() {return((Pin14_GPIO_Port->ODR & Pin14_Pin) != 0);}
#else
inline void bSet() {}
inline void bClr() {}
inline uint16_t b() {return(0);}
#endif

#ifdef Pin17_Pin
inline void syncSet() {Pin17_GPIO_Port->BSRR = Pin17_Pin;}
inline void syncClr() {Pin17_GPIO_Port->BSRR = (Pin17_Pin << 16);}
inline uint16_t syncRead() {return((Pin17_GPIO_Port->ODR & Pin17_Pin) != 0);}
#else
inline void syncSet() {}
inline void syncClr() {}
inline uint16_t sync() {return(0);}
#endif

#ifdef Led1_Pin
inline void led1Set() {Led1_GPIO_Port->BSRR = Led1_Pin;}
inline void led1Clr() {Led1_GPIO_Port->BSRR = (Led1_Pin << 16);}
inline uint16_t led1Read() {return((Led1_GPIO_Port->ODR & Led1_Pin) != 0);}
#else
inline void led1Set() {}
inline void led1Clr() {}
inline uint16_t led1() {return(0);}
#endif

#ifdef Led2_Pin
inline void led2Set() {Led2_GPIO_Port->BSRR = Led2_Pin;}
inline void led2Clr() {Led2_GPIO_Port->BSRR = (Led2_Pin << 16);}
inline uint16_t led2Read() {return((Led2_GPIO_Port->ODR & Led2_Pin) != 0);}
#else
inline void led2Set() {}
inline void led2Clr() {}
inline uint16_t led2() {return(0);}
#endif

#ifdef Led3_Pin
inline void led3Set() {Led3_GPIO_Port->BSRR = Led3_Pin;}
inline void led3Clr() {Led3_GPIO_Port->BSRR = (Led3_Pin << 16);}
inline uint16_t led3Read() {return((Led3_GPIO_Port->ODR & Led3_Pin) != 0);}
#else
inline void led3Set() {}
inline void led3Clr() {}
inline uint16_t led3() {return(0);}
#endif

#endif /* __PINDEF_H */
#endif /* __STM32F4xx_HAL_H */
