#ifdef __STM32F4xx_HAL_H
#if !defined(__PINDEF_H)
#define __PINDEF_H

#ifdef Index1_Pin
inline uint16_t index1() {return((Index1_GPIO_Port->IDR & Index1_Pin) != 0);}
inline uint16_t index1IsSet() {return((Index1_GPIO_Port->IDR & Index1_Pin) != 0);}
inline uint16_t index1IsClr() {return((Index1_GPIO_Port->IDR & Index1_Pin) == 0);}
#else
inline uint16_t index1() {return(0);}
inline uint16_t index1IsSet() {return(0);}
inline uint16_t index1IsClr() {return(0);}
#endif

#ifdef Index2_Pin
inline uint16_t index2() {return((Index2_GPIO_Port->IDR & Index2_Pin) != 0);}
inline uint16_t index2IsSet() {return((Index2_GPIO_Port->IDR & Index2_Pin) != 0);}
inline uint16_t index2IsClr() {return((Index2_GPIO_Port->IDR & Index2_Pin) == 0);}
#else
inline uint16_t index2() {return(0);}
inline uint16_t index2IsSet() {return(0);}
inline uint16_t index2IsClr() {return(0);}
#endif

#ifdef ZA_Pin
inline uint16_t zA() {return((ZA_GPIO_Port->IDR & ZA_Pin) != 0);}
inline uint16_t zAIsSet() {return((ZA_GPIO_Port->IDR & ZA_Pin) != 0);}
inline uint16_t zAIsClr() {return((ZA_GPIO_Port->IDR & ZA_Pin) == 0);}
#else
inline uint16_t zA() {return(0);}
inline uint16_t zAIsSet() {return(0);}
inline uint16_t zAIsClr() {return(0);}
#endif

#ifdef ZB_Pin
inline uint16_t zB() {return((ZB_GPIO_Port->IDR & ZB_Pin) != 0);}
inline uint16_t zBIsSet() {return((ZB_GPIO_Port->IDR & ZB_Pin) != 0);}
inline uint16_t zBIsClr() {return((ZB_GPIO_Port->IDR & ZB_Pin) == 0);}
#else
inline uint16_t zB() {return(0);}
inline uint16_t zBIsSet() {return(0);}
inline uint16_t zBIsClr() {return(0);}
#endif

#ifdef XA_Pin
inline uint16_t xA() {return((XA_GPIO_Port->IDR & XA_Pin) != 0);}
inline uint16_t xAIsSet() {return((XA_GPIO_Port->IDR & XA_Pin) != 0);}
inline uint16_t xAIsClr() {return((XA_GPIO_Port->IDR & XA_Pin) == 0);}
#else
inline uint16_t xA() {return(0);}
inline uint16_t xAIsSet() {return(0);}
inline uint16_t xAIsClr() {return(0);}
#endif

#ifdef XB_Pin
inline uint16_t xB() {return((XB_GPIO_Port->IDR & XB_Pin) != 0);}
inline uint16_t xBIsSet() {return((XB_GPIO_Port->IDR & XB_Pin) != 0);}
inline uint16_t xBIsClr() {return((XB_GPIO_Port->IDR & XB_Pin) == 0);}
#else
inline uint16_t xB() {return(0);}
inline uint16_t xBIsSet() {return(0);}
inline uint16_t xBIsClr() {return(0);}
#endif

#ifdef ZFLag_Pin
inline uint16_t spEncDir() {return((ZFLag_GPIO_Port->IDR & ZFLag_Pin) != 0);}
inline uint16_t spEncDirIsSet() {return((ZFLag_GPIO_Port->IDR & ZFLag_Pin) != 0);}
inline uint16_t spEncDirIsClr() {return((ZFLag_GPIO_Port->IDR & ZFLag_Pin) == 0);}
#else
inline uint16_t spEncDir() {return(0);}
inline uint16_t spEncDirIsSet() {return(0);}
inline uint16_t spEncDirIsClr() {return(0);}
#endif

#ifdef JogA1_Pin
inline uint16_t jogA1() {return((JogA1_GPIO_Port->IDR & JogA1_Pin) != 0);}
inline uint16_t jogA1IsSet() {return((JogA1_GPIO_Port->IDR & JogA1_Pin) != 0);}
inline uint16_t jogA1IsClr() {return((JogA1_GPIO_Port->IDR & JogA1_Pin) == 0);}
#else
inline uint16_t jogA1() {return(0);}
inline uint16_t jogA1IsSet() {return(0);}
inline uint16_t jogA1IsClr() {return(0);}
#endif

#ifdef JogB1_Pin
inline uint16_t jogB1() {return((JogB1_GPIO_Port->IDR & JogB1_Pin) != 0);}
inline uint16_t jogB1IsSet() {return((JogB1_GPIO_Port->IDR & JogB1_Pin) != 0);}
inline uint16_t jogB1IsClr() {return((JogB1_GPIO_Port->IDR & JogB1_Pin) == 0);}
#else
inline uint16_t jogB1() {return(0);}
inline uint16_t jogB1IsSet() {return(0);}
inline uint16_t jogB1IsClr() {return(0);}
#endif

#ifdef JogA2_Pin
inline uint16_t jogA2() {return((JogA2_GPIO_Port->IDR & JogA2_Pin) != 0);}
inline uint16_t jogA2IsSet() {return((JogA2_GPIO_Port->IDR & JogA2_Pin) != 0);}
inline uint16_t jogA2IsClr() {return((JogA2_GPIO_Port->IDR & JogA2_Pin) == 0);}
#else
inline uint16_t jogA2() {return(0);}
inline uint16_t jogA2IsSet() {return(0);}
inline uint16_t jogA2IsClr() {return(0);}
#endif

#ifdef JogB2_Pin
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
inline uint16_t pin10() {return((Pin10_GPIO_Port->IDR & Pin10_Pin) != 0);}
inline uint16_t pin10IsSet() {return((Pin10_GPIO_Port->IDR & Pin10_Pin) != 0);}
inline uint16_t pin10IsClr() {return((Pin10_GPIO_Port->IDR & Pin10_Pin) == 0);}
#else
inline uint16_t pin10() {return(0);}
inline uint16_t pin10IsSet() {return(0);}
inline uint16_t pin10IsClr() {return(0);}
#endif

#ifdef Pin11_Pin
inline uint16_t pin11() {return((Pin11_GPIO_Port->IDR & Pin11_Pin) != 0);}
inline uint16_t pin11IsSet() {return((Pin11_GPIO_Port->IDR & Pin11_Pin) != 0);}
inline uint16_t pin11IsClr() {return((Pin11_GPIO_Port->IDR & Pin11_Pin) == 0);}
#else
inline uint16_t pin11() {return(0);}
inline uint16_t pin11IsSet() {return(0);}
inline uint16_t pin11IsClr() {return(0);}
#endif

#ifdef Pin12_Pin
inline uint16_t pin12() {return((Pin12_GPIO_Port->IDR & Pin12_Pin) != 0);}
inline uint16_t pin12IsSet() {return((Pin12_GPIO_Port->IDR & Pin12_Pin) != 0);}
inline uint16_t pin12IsClr() {return((Pin12_GPIO_Port->IDR & Pin12_Pin) == 0);}
#else
inline uint16_t pin12() {return(0);}
inline uint16_t pin12IsSet() {return(0);}
inline uint16_t pin12IsClr() {return(0);}
#endif

#ifdef Pin13_Pin
inline uint16_t pin13() {return((Pin13_GPIO_Port->IDR & Pin13_Pin) != 0);}
inline uint16_t pin13IsSet() {return((Pin13_GPIO_Port->IDR & Pin13_Pin) != 0);}
inline uint16_t pin13IsClr() {return((Pin13_GPIO_Port->IDR & Pin13_Pin) == 0);}
#else
inline uint16_t pin13() {return(0);}
inline uint16_t pin13IsSet() {return(0);}
inline uint16_t pin13IsClr() {return(0);}
#endif

#ifdef Pin15_Pin
inline uint16_t pin15() {return((Pin15_GPIO_Port->IDR & Pin15_Pin) != 0);}
inline uint16_t pin15IsSet() {return((Pin15_GPIO_Port->IDR & Pin15_Pin) != 0);}
inline uint16_t pin15IsClr() {return((Pin15_GPIO_Port->IDR & Pin15_Pin) == 0);}
#else
inline uint16_t pin15() {return(0);}
inline uint16_t pin15IsSet() {return(0);}
inline uint16_t pin15IsClr() {return(0);}
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
inline uint16_t ready() {return((XFlag_GPIO_Port->IDR & XFlag_Pin) != 0);}
inline uint16_t readyIsSet() {return((XFlag_GPIO_Port->IDR & XFlag_Pin) != 0);}
inline uint16_t readyIsClr() {return((XFlag_GPIO_Port->IDR & XFlag_Pin) == 0);}
#else
inline uint16_t ready() {return(0);}
inline uint16_t readyIsSet() {return(0);}
inline uint16_t readyIsClr() {return(0);}
#endif

#ifdef XFlag_Pin
inline uint16_t xFlagX() {return((XFlag_GPIO_Port->IDR & XFlag_Pin) != 0);}
inline uint16_t xFlagXIsSet() {return((XFlag_GPIO_Port->IDR & XFlag_Pin) != 0);}
inline uint16_t xFlagXIsClr() {return((XFlag_GPIO_Port->IDR & XFlag_Pin) == 0);}
#else
inline uint16_t xFlagX() {return(0);}
inline uint16_t xFlagXIsSet() {return(0);}
inline uint16_t xFlagXIsClr() {return(0);}
#endif

#ifdef ZFlag_Pin
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

#endif /* __PINDEF_H */
#endif /* __STM32F4xx_HAL_H */
