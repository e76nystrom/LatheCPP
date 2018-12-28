#ifdef __STM32F4xx_HAL_H
#if !defined(__PINDEF_H)
#define __PINDEF_H

#ifdef Index1_Pin
inline uint16_t index1() {return((Index1_GPIO_Port->BSRR & Index1_Pin) != 0);}
inline uint16_t index1Set() {return((Index1_GPIO_Port->BSRR = Index1_Pin) != 0);}
inline uint16_t index1Clr() {return((Index1_GPIO_Port->BSRR = Index1_Pin) == 0);}
#else
inline uint16_t index1Set() {return(0);}
inline uint16_t index1Clr() {return(0);}
#endif

#ifdef Index2_Pin
inline uint16_t index2() {return((Index2_GPIO_Port->BSRR & Index2_Pin) != 0);}
inline uint16_t index2Set() {return((Index2_GPIO_Port->BSRR = Index2_Pin) != 0);}
inline uint16_t index2Clr() {return((Index2_GPIO_Port->BSRR = Index2_Pin) == 0);}
#else
inline uint16_t index2Set() {return(0);}
inline uint16_t index2Clr() {return(0);}
#endif

#ifdef ZA_Pin
inline uint16_t zA() {return((ZA_GPIO_Port->BSRR & ZA_Pin) != 0);}
inline uint16_t zASet() {return((ZA_GPIO_Port->BSRR = ZA_Pin) != 0);}
inline uint16_t zAClr() {return((ZA_GPIO_Port->BSRR = ZA_Pin) == 0);}
#else
inline uint16_t zASet() {return(0);}
inline uint16_t zAClr() {return(0);}
#endif

#ifdef ZB_Pin
inline uint16_t zB() {return((ZB_GPIO_Port->BSRR & ZB_Pin) != 0);}
inline uint16_t zBSet() {return((ZB_GPIO_Port->BSRR = ZB_Pin) != 0);}
inline uint16_t zBClr() {return((ZB_GPIO_Port->BSRR = ZB_Pin) == 0);}
#else
inline uint16_t zBSet() {return(0);}
inline uint16_t zBClr() {return(0);}
#endif

#ifdef XA_Pin
inline uint16_t xA() {return((XA_GPIO_Port->BSRR & XA_Pin) != 0);}
inline uint16_t xASet() {return((XA_GPIO_Port->BSRR = XA_Pin) != 0);}
inline uint16_t xAClr() {return((XA_GPIO_Port->BSRR = XA_Pin) == 0);}
#else
inline uint16_t xASet() {return(0);}
inline uint16_t xAClr() {return(0);}
#endif

#ifdef XB_Pin
inline uint16_t xB() {return((XB_GPIO_Port->BSRR & XB_Pin) != 0);}
inline uint16_t xBSet() {return((XB_GPIO_Port->BSRR = XB_Pin) != 0);}
inline uint16_t xBClr() {return((XB_GPIO_Port->BSRR = XB_Pin) == 0);}
#else
inline uint16_t xBSet() {return(0);}
inline uint16_t xBClr() {return(0);}
#endif

#ifdef ZFLag_Pin
inline uint16_t spEncDir() {return((ZFLag_GPIO_Port->BSRR & ZFLag_Pin) != 0);}
inline uint16_t spEncDirSet() {return((ZFLag_GPIO_Port->BSRR = ZFLag_Pin) != 0);}
inline uint16_t spEncDirClr() {return((ZFLag_GPIO_Port->BSRR = ZFLag_Pin) == 0);}
#else
inline uint16_t spEncDirSet() {return(0);}
inline uint16_t spEncDirClr() {return(0);}
#endif

#ifdef JogA1_Pin
inline uint16_t jogA1() {return((JogA1_GPIO_Port->BSRR & JogA1_Pin) != 0);}
inline uint16_t jogA1Set() {return((JogA1_GPIO_Port->BSRR = JogA1_Pin) != 0);}
inline uint16_t jogA1Clr() {return((JogA1_GPIO_Port->BSRR = JogA1_Pin) == 0);}
#else
inline uint16_t jogA1Set() {return(0);}
inline uint16_t jogA1Clr() {return(0);}
#endif

#ifdef JogB1_Pin
inline uint16_t jogB1() {return((JogB1_GPIO_Port->BSRR & JogB1_Pin) != 0);}
inline uint16_t jogB1Set() {return((JogB1_GPIO_Port->BSRR = JogB1_Pin) != 0);}
inline uint16_t jogB1Clr() {return((JogB1_GPIO_Port->BSRR = JogB1_Pin) == 0);}
#else
inline uint16_t jogB1Set() {return(0);}
inline uint16_t jogB1Clr() {return(0);}
#endif

#ifdef JogA2_Pin
inline uint16_t jogA2() {return((JogA2_GPIO_Port->BSRR & JogA2_Pin) != 0);}
inline uint16_t jogA2Set() {return((JogA2_GPIO_Port->BSRR = JogA2_Pin) != 0);}
inline uint16_t jogA2Clr() {return((JogA2_GPIO_Port->BSRR = JogA2_Pin) == 0);}
#else
inline uint16_t jogA2Set() {return(0);}
inline uint16_t jogA2Clr() {return(0);}
#endif

#ifdef JogB2_Pin
inline uint16_t jogB2() {return((JogB2_GPIO_Port->BSRR & JogB2_Pin) != 0);}
inline uint16_t jogB2Set() {return((JogB2_GPIO_Port->BSRR = JogB2_Pin) != 0);}
inline uint16_t jogB2Clr() {return((JogB2_GPIO_Port->BSRR = JogB2_Pin) == 0);}
#else
inline uint16_t jogB2Set() {return(0);}
inline uint16_t jogB2Clr() {return(0);}
#endif

#ifdef Step1_Pin
inline void stpZSet() {Step1_GPIO_Port->BSRR = Step1_Pin;}
inline void stpZClr() {Step1_GPIO_Port->BSRR = (Step1_Pin << 16);}
#else
inline void stpZSet() {}
inline void stpZClr() {}
#endif

#ifdef Step2_Pin
inline void stpXSet() {Step2_GPIO_Port->BSRR = Step2_Pin;}
inline void stpXClr() {Step2_GPIO_Port->BSRR = (Step2_Pin << 16);}
#else
inline void stpXSet() {}
inline void stpXClr() {}
#endif

#ifdef Step3_Pin
inline void step3Set() {Step3_GPIO_Port->BSRR = Step3_Pin;}
inline void step3Clr() {Step3_GPIO_Port->BSRR = (Step3_Pin << 16);}
#else
inline void step3Set() {}
inline void step3Clr() {}
#endif

#ifdef Step4_Pin
inline void step4Set() {Step4_GPIO_Port->BSRR = Step4_Pin;}
inline void step4Clr() {Step4_GPIO_Port->BSRR = (Step4_Pin << 16);}
#else
inline void step4Set() {}
inline void step4Clr() {}
#endif

#ifdef Step5_Pin
inline void step5Set() {Step5_GPIO_Port->BSRR = Step5_Pin;}
inline void step5Clr() {Step5_GPIO_Port->BSRR = (Step5_Pin << 16);}
#else
inline void step5Set() {}
inline void step5Clr() {}
#endif

#ifdef Dir1_Pin
inline void dirZSet() {Dir1_GPIO_Port->BSRR = Dir1_Pin;}
inline void dirZClr() {Dir1_GPIO_Port->BSRR = (Dir1_Pin << 16);}
#else
inline void dirZSet() {}
inline void dirZClr() {}
#endif

#ifdef Dir2_Pin
inline void dirXSet() {Dir2_GPIO_Port->BSRR = Dir2_Pin;}
inline void dirXClr() {Dir2_GPIO_Port->BSRR = (Dir2_Pin << 16);}
#else
inline void dirXSet() {}
inline void dirXClr() {}
#endif

#ifdef Dir3_Pin
inline void dir3Set() {Dir3_GPIO_Port->BSRR = Dir3_Pin;}
inline void dir3Clr() {Dir3_GPIO_Port->BSRR = (Dir3_Pin << 16);}
#else
inline void dir3Set() {}
inline void dir3Clr() {}
#endif

#ifdef Dir4_Pin
inline void dir4Set() {Dir4_GPIO_Port->BSRR = Dir4_Pin;}
inline void dir4Clr() {Dir4_GPIO_Port->BSRR = (Dir4_Pin << 16);}
#else
inline void dir4Set() {}
inline void dir4Clr() {}
#endif

#ifdef Dir5_Pin
inline void dir5Set() {Dir5_GPIO_Port->BSRR = Dir5_Pin;}
inline void dir5Clr() {Dir5_GPIO_Port->BSRR = (Dir5_Pin << 16);}
#else
inline void dir5Set() {}
inline void dir5Clr() {}
#endif

#ifdef Pin1_Pin
inline void pin1Set() {Pin1_GPIO_Port->BSRR = Pin1_Pin;}
inline void pin1Clr() {Pin1_GPIO_Port->BSRR = (Pin1_Pin << 16);}
#else
inline void pin1Set() {}
inline void pin1Clr() {}
#endif

#ifdef Pin14_Pin
inline void pin14Set() {Pin14_GPIO_Port->BSRR = Pin14_Pin;}
inline void pin14Clr() {Pin14_GPIO_Port->BSRR = (Pin14_Pin << 16);}
#else
inline void pin14Set() {}
inline void pin14Clr() {}
#endif

#ifdef Pin16_Pin
inline void pin16Set() {Pin16_GPIO_Port->BSRR = Pin16_Pin;}
inline void pin16Clr() {Pin16_GPIO_Port->BSRR = (Pin16_Pin << 16);}
#else
inline void pin16Set() {}
inline void pin16Clr() {}
#endif

#ifdef Pin17_Pin
inline void pin17Set() {Pin17_GPIO_Port->BSRR = Pin17_Pin;}
inline void pin17Clr() {Pin17_GPIO_Port->BSRR = (Pin17_Pin << 16);}
#else
inline void pin17Set() {}
inline void pin17Clr() {}
#endif

#ifdef Pin10_Pin
inline uint16_t pin10() {return((Pin10_GPIO_Port->BSRR & Pin10_Pin) != 0);}
inline uint16_t pin10Set() {return((Pin10_GPIO_Port->BSRR = Pin10_Pin) != 0);}
inline uint16_t pin10Clr() {return((Pin10_GPIO_Port->BSRR = Pin10_Pin) == 0);}
#else
inline uint16_t pin10Set() {return(0);}
inline uint16_t pin10Clr() {return(0);}
#endif

#ifdef Pin11_Pin
inline uint16_t pin11() {return((Pin11_GPIO_Port->BSRR & Pin11_Pin) != 0);}
inline uint16_t pin11Set() {return((Pin11_GPIO_Port->BSRR = Pin11_Pin) != 0);}
inline uint16_t pin11Clr() {return((Pin11_GPIO_Port->BSRR = Pin11_Pin) == 0);}
#else
inline uint16_t pin11Set() {return(0);}
inline uint16_t pin11Clr() {return(0);}
#endif

#ifdef Pin12_Pin
inline uint16_t pin12() {return((Pin12_GPIO_Port->BSRR & Pin12_Pin) != 0);}
inline uint16_t pin12Set() {return((Pin12_GPIO_Port->BSRR = Pin12_Pin) != 0);}
inline uint16_t pin12Clr() {return((Pin12_GPIO_Port->BSRR = Pin12_Pin) == 0);}
#else
inline uint16_t pin12Set() {return(0);}
inline uint16_t pin12Clr() {return(0);}
#endif

#ifdef Pin13_Pin
inline uint16_t pin13() {return((Pin13_GPIO_Port->BSRR & Pin13_Pin) != 0);}
inline uint16_t pin13Set() {return((Pin13_GPIO_Port->BSRR = Pin13_Pin) != 0);}
inline uint16_t pin13Clr() {return((Pin13_GPIO_Port->BSRR = Pin13_Pin) == 0);}
#else
inline uint16_t pin13Set() {return(0);}
inline uint16_t pin13Clr() {return(0);}
#endif

#ifdef Pin15_Pin
inline uint16_t pin15() {return((Pin15_GPIO_Port->BSRR & Pin15_Pin) != 0);}
inline uint16_t pin15Set() {return((Pin15_GPIO_Port->BSRR = Pin15_Pin) != 0);}
inline uint16_t pin15Clr() {return((Pin15_GPIO_Port->BSRR = Pin15_Pin) == 0);}
#else
inline uint16_t pin15Set() {return(0);}
inline uint16_t pin15Clr() {return(0);}
#endif

#ifdef Start_Pin
inline void startSet() {Start_GPIO_Port->BSRR = Start_Pin;}
inline void startClr() {Start_GPIO_Port->BSRR = (Start_Pin << 16);}
#else
inline void startSet() {}
inline void startClr() {}
#endif

#ifdef Ready_Pin
inline uint16_t ready() {return((Ready_GPIO_Port->BSRR & Ready_Pin) != 0);}
inline uint16_t readySet() {return((Ready_GPIO_Port->BSRR = Ready_Pin) != 0);}
inline uint16_t readyClr() {return((Ready_GPIO_Port->BSRR = Ready_Pin) == 0);}
#else
inline uint16_t readySet() {return(0);}
inline uint16_t readyClr() {return(0);}
#endif

#ifdef XFlag_Pin
inline uint16_t xFlagX() {return((XFlag_GPIO_Port->BSRR & XFlag_Pin) != 0);}
inline uint16_t xFlagXSet() {return((XFlag_GPIO_Port->BSRR = XFlag_Pin) != 0);}
inline uint16_t xFlagXClr() {return((XFlag_GPIO_Port->BSRR = XFlag_Pin) == 0);}
#else
inline uint16_t xFlagXSet() {return(0);}
inline uint16_t xFlagXClr() {return(0);}
#endif

#ifdef ZFlag_Pin
inline uint16_t zFlagX() {return((ZFlag_GPIO_Port->BSRR & ZFlag_Pin) != 0);}
inline uint16_t zFlagXSet() {return((ZFlag_GPIO_Port->BSRR = ZFlag_Pin) != 0);}
inline uint16_t zFlagXClr() {return((ZFlag_GPIO_Port->BSRR = ZFlag_Pin) == 0);}
#else
inline uint16_t zFlagXSet() {return(0);}
inline uint16_t zFlagXClr() {return(0);}
#endif

#ifdef Pin1_Pin
inline void aSet() {Pin1_GPIO_Port->BSRR = Pin1_Pin;}
inline void aClr() {Pin1_GPIO_Port->BSRR = (Pin1_Pin << 16);}
#else
inline void aSet() {}
inline void aClr() {}
#endif

#ifdef Pin14_Pin
inline void bSet() {Pin14_GPIO_Port->BSRR = Pin14_Pin;}
inline void bClr() {Pin14_GPIO_Port->BSRR = (Pin14_Pin << 16);}
#else
inline void bSet() {}
inline void bClr() {}
#endif

#ifdef Pin17_Pin
inline void syncSet() {Pin17_GPIO_Port->BSRR = Pin17_Pin;}
inline void syncClr() {Pin17_GPIO_Port->BSRR = (Pin17_Pin << 16);}
#else
inline void syncSet() {}
inline void syncClr() {}
#endif

#endif /* __PINDEF_H */
#endif /* __STM32F4xx_HAL_H */
