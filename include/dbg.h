constexpr auto DBG0 = 1;
constexpr auto DBG1 = 1;
constexpr auto DBG2 = 1;
constexpr auto DBG3 = 1;
constexpr auto DBG4 = 1;
constexpr auto DBG5 = 1;
constexpr auto DBG6 = 1;
constexpr auto DBG7 = 1;
constexpr auto DBG8 = 1;
constexpr auto DBG9 = 1;
constexpr auto DBG10 = 1;
constexpr auto DBG11 = 1;
constexpr auto DBG12 = 1;

#ifdef __STM32F4xx_HAL_H

#ifdef Dbg0_Pin
inline void dbg0Ini() {}
inline void dbg0Set() {Dbg0_GPIO_Port->BSRR = Dbg0_Pin;}
inline void dbg0Clr() {Dbg0_GPIO_Port->BSRR = (Dbg0_Pin << 16);}
#else
inline void dbg0Ini() {}
inline void dbg0Set() {}
inline void dbg0Clr() {}
#endif

#ifdef Dbg1_Pin
inline void dbg1Ini() {}
inline void dbg1Set() {Dbg1_GPIO_Port->BSRR = Dbg1_Pin;}
inline void dbg1Clr() {Dbg1_GPIO_Port->BSRR = (Dbg1_Pin << 16);}
#else
inline void dbg1Ini() {}
inline void dbg1Set() {}
inline void dbg1Clr() {}
#endif

#ifdef Dbg2_Pin
inline void dbg2Ini() {}
inline void dbg2Set() {Dbg2_GPIO_Port->BSRR = Dbg2_Pin;}
inline void dbg2Clr() {Dbg2_GPIO_Port->BSRR = (Dbg2_Pin << 16);}
#else
inline void dbg2Ini() {}
inline void dbg2Set() {}
inline void dbg2Clr() {}
#endif

#ifdef Dbg3_Pin
inline void dbg3Ini() {}
inline void dbg3Set() {Dbg3_GPIO_Port->BSRR = Dbg3_Pin;}
inline void dbg3Clr() {Dbg3_GPIO_Port->BSRR = (Dbg3_Pin << 16);}
#else
inline void dbg3Ini() {}
inline void dbg3Set() {}
inline void dbg3Clr() {}
#endif

#ifdef Dbg4_Pin
inline void dbg4Ini() {}
inline void dbg4Set() {Dbg4_GPIO_Port->BSRR = Dbg4_Pin;}
inline void dbg4Clr() {Dbg4_GPIO_Port->BSRR = (Dbg4_Pin << 16);}
#else
inline void dbg4Ini() {}
inline void dbg4Set() {}
inline void dbg4Clr() {}
#endif

#ifdef Dbg5_Pin
inline void dbg5Ini() {}
inline void dbg5Set() {Dbg5_GPIO_Port->BSRR = Dbg5_Pin;}
inline void dbg5Clr() {Dbg5_GPIO_Port->BSRR = (Dbg5_Pin << 16);}
#else
inline void dbg5Ini() {}
inline void dbg5Set() {}
inline void dbg5Clr() {}
#endif

#ifdef Dbg6_Pin
inline void dbg6Ini() {}
inline void dbg6Set() {Dbg6_GPIO_Port->BSRR = Dbg6_Pin;}
inline void dbg6Clr() {Dbg6_GPIO_Port->BSRR = (Dbg6_Pin << 16);}
#else
inline void dbg6Ini() {}
inline void dbg6Set() {}
inline void dbg6Clr() {}
#endif

#ifdef Dbg7_Pin
inline void dbg7Ini() {}
inline void dbg7Set() {Dbg7_GPIO_Port->BSRR = Dbg7_Pin;}
inline void dbg7Clr() {Dbg7_GPIO_Port->BSRR = (Dbg7_Pin << 16);}
#else
inline void dbg7Ini() {}
inline void dbg7Set() {}
inline void dbg7Clr() {}
#endif

#ifdef Dbg8_Pin
inline void dbg8Ini() {}
inline void dbg8Set() {Dbg8_GPIO_Port->BSRR = Dbg8_Pin;}
inline void dbg8Clr() {Dbg8_GPIO_Port->BSRR = (Dbg8_Pin << 16);}
#else
inline void dbg8Ini() {}
inline void dbg8Set() {}
inline void dbg8Clr() {}
#endif

#ifdef Dbg9_Pin
inline void dbg9Ini() {}
inline void dbg9Set() {Dbg9_GPIO_Port->BSRR = Dbg9_Pin;}
inline void dbg9Clr() {Dbg9_GPIO_Port->BSRR = (Dbg9_Pin << 16);}
#else
inline void dbg9Ini() {}
inline void dbg9Set() {}
inline void dbg9Clr() {}
#endif

#ifdef Dbg10_Pin
inline void dbg10Ini() {}
inline void dbg10Set() {Dbg10_GPIO_Port->BSRR = Dbg10_Pin;}
inline void dbg10Clr() {Dbg10_GPIO_Port->BSRR = (Dbg10_Pin << 16);}
#else
inline void dbg10Ini() {}
inline void dbg10Set() {}
inline void dbg10Clr() {}
#endif

#ifdef Dbg11_Pin
inline void dbg11Ini() {}
inline void dbg11Set() {Dbg11_GPIO_Port->BSRR = Dbg11_Pin;}
inline void dbg11Clr() {Dbg11_GPIO_Port->BSRR = (Dbg11_Pin << 16);}
#else
inline void dbg11Ini() {}
inline void dbg11Set() {}
inline void dbg11Clr() {}
#endif

#ifdef Dbg12_Pin
inline void dbg12Ini() {}
inline void dbg12Set() {Dbg12_GPIO_Port->BSRR = Dbg12_Pin;}
inline void dbg12Clr() {Dbg12_GPIO_Port->BSRR = (Dbg12_Pin << 16);}
#else
inline void dbg12Ini() {}
inline void dbg12Set() {}
inline void dbg12Clr() {}
#endif

/* spindle isr time */
#ifdef Dbg0_Pin
inline void dbgSpIsrSet() {Dbg0_GPIO_Port->BSRR = Dbg0_Pin;}
inline void dbgSpIsrClr() {Dbg0_GPIO_Port->BSRR = (Dbg0_Pin << 16);}
#else
inline void dbgSpIsrSet() {}
inline void dbgSpIsrClr() {}
#endif

/* z isr time */
#ifdef Dbg1_Pin
inline void dbgZIsrSet() {Dbg1_GPIO_Port->BSRR = Dbg1_Pin;}
inline void dbgZIsrClr() {Dbg1_GPIO_Port->BSRR = (Dbg1_Pin << 16);}
#else
inline void dbgZIsrSet() {}
inline void dbgZIsrClr() {}
#endif

/* x isr time */
#ifdef Dbg2_Pin
inline void dbgXIsrSet() {Dbg2_GPIO_Port->BSRR = Dbg2_Pin;}
inline void dbgXIsrClr() {Dbg2_GPIO_Port->BSRR = (Dbg2_Pin << 16);}
#else
inline void dbgXIsrSet() {}
inline void dbgXIsrClr() {}
#endif

/* spindle cycle counter update */
inline void dbgSpCycSet() {}
inline void dbgSpCycClr() {}

/* z encoder input */
#ifdef Dbg3_Pin
inline void dbgZEncSet() {Dbg3_GPIO_Port->BSRR = Dbg3_Pin;}
inline void dbgZEncClr() {Dbg3_GPIO_Port->BSRR = (Dbg3_Pin << 16);}
#else
inline void dbgZEncSet() {}
inline void dbgZEncClr() {}
#endif

/* z encoder output */
inline void dbgZOutSet() {}
inline void dbgZOutClr() {}

/* x encoder */
inline void dbgXEncSet() {}
inline void dbgXEncClr() {}

/* x encoder output */
inline void dbgXOutSet() {}
inline void dbgXOutClr() {}

/* toggle on compare input */
inline void dbgIntCSet() {}
inline void dbgIntCClr() {}

/* toggle on output pulse */
inline void dbgIntPSet() {}
inline void dbgIntPClr() {}

/* toggle on input cycle */
#ifdef Dbg6_Pin
inline void dbgCycleSet() {Dbg6_GPIO_Port->BSRR = Dbg6_Pin;}
inline void dbgCycleClr() {Dbg6_GPIO_Port->BSRR = (Dbg6_Pin << 16);}
#else
inline void dbgCycleSet() {}
inline void dbgCycleClr() {}
#endif

/* end of internal pulse cycle */
#ifdef Dbg7_Pin
inline void dbgCycEndSet() {Dbg7_GPIO_Port->BSRR = Dbg7_Pin;}
inline void dbgCycEndClr() {Dbg7_GPIO_Port->BSRR = (Dbg7_Pin << 16);}
#else
inline void dbgCycEndSet() {}
inline void dbgCycEndClr() {}
#endif

/* length of capture isr */
#ifdef Dbg8_Pin
inline void dbgCapIsrSet() {Dbg8_GPIO_Port->BSRR = Dbg8_Pin;}
inline void dbgCapIsrClr() {Dbg8_GPIO_Port->BSRR = (Dbg8_Pin << 16);}
#else
inline void dbgCapIsrSet() {}
inline void dbgCapIsrClr() {}
#endif

/* length of internal isr */
#ifdef Dbg9_Pin
inline void dbgIntIsrSet() {Dbg9_GPIO_Port->BSRR = Dbg9_Pin;}
inline void dbgIntIsrClr() {Dbg9_GPIO_Port->BSRR = (Dbg9_Pin << 16);}
#else
inline void dbgIntIsrSet() {}
inline void dbgIntIsrClr() {}
#endif

/* z cycle counter update */
inline void dbgZCycSet() {}
inline void dbgZCycClr() {}

/* x cycle counter update */
inline void dbgXCycSet() {}
inline void dbgXCycClr() {}

/* spindle accel and decel */
inline void dbgSpStopSet() {}
inline void dbgSpStopClr() {}

/* z accel and decel */
inline void dbgZAccelSet() {}
inline void dbgZAccelClr() {}

/* x accel and decel */
inline void dbgXAccelSet() {}
inline void dbgXAccelClr() {}

/* x remainder */
inline void dbgXRemSet() {}
inline void dbgXRemClr() {}

/* spindle rev counter */
inline void dbgSpRevSet() {}
inline void dbgSpRevClr() {}

/* runout start */
#ifdef Dbg4_Pin
inline void dbgRunoutSet() {Dbg4_GPIO_Port->BSRR = Dbg4_Pin;}
inline void dbgRunoutClr() {Dbg4_GPIO_Port->BSRR = (Dbg4_Pin << 16);}
#else
inline void dbgRunoutSet() {}
inline void dbgRunoutClr() {}
#endif

/* z taper */
inline void dbgZTaperSet() {}
inline void dbgZTaperClr() {}

/* x taper */
inline void dbgXTaperSet() {}
inline void dbgXTaperClr() {}

/* slave start */
inline void dbgSlvSet() {}
inline void dbgSlvClr() {}

/* step 2b isr */
inline void dbgS2bIsrSet() {}
inline void dbgS2bIsrClr() {}

/* step 3 isr */
inline void dbgS3IsrSet() {}
inline void dbgS3IsrClr() {}

/* step 4 isr */
inline void dbgS4IsrSet() {}
inline void dbgS4IsrClr() {}

/* step 5 isr */
inline void dbgS5IsrSet() {}
inline void dbgS5IsrClr() {}

/* jog isr transition put in queue */
inline void dbgJogIsrSet() {}
inline void dbgJogIsrClr() {}

/* jog idle queue checked */
inline void dbgJogMPG0Set() {}
inline void dbgJogMPG0Clr() {}

/* jog moving all cases */
inline void dbgJogMPG1Set() {}
inline void dbgJogMPG1Clr() {}

/* jog moving isr done start again */
inline void dbgJogMPG2Set() {}
inline void dbgJogMPG2Clr() {}

/* jog moving add to current distance */
inline void dbgJogMPG3Set() {}
inline void dbgJogMPG3Clr() {}

/* axis control */
inline void dbgAxisCtlSet() {}
inline void dbgAxisCtlClr() {}

#endif
