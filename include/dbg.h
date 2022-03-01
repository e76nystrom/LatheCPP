#if defined(__STM32F4xx_HAL_H) || defined(__STM32F7xx_HAL_H) || defined(STM32H7xx_HAL_H)
#if !defined(__DBG_H)
#define __DBG_H

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
constexpr auto DBGA0 = 1;
constexpr auto DBGA1 = 1;
constexpr auto DBGA2 = 1;
constexpr auto DBGA3 = 1;
constexpr auto DBGA4 = 1;
constexpr auto DBGA5 = 1;
constexpr auto DBGA6 = 1;
constexpr auto DBGA7 = 1;
constexpr auto DBGA8 = 1;
constexpr auto DBGA9 = 1;
constexpr auto DBGA10 = 1;
constexpr auto DBGA11 = 1;
constexpr auto DBGA12 = 1;
constexpr auto DBGA13 = 1;

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

#ifdef DbgA0_Pin
inline void dbgA0Ini() {}
inline void dbgA0Set() {DbgA0_GPIO_Port->BSRR = DbgA0_Pin;}
inline void dbgA0Clr() {DbgA0_GPIO_Port->BSRR = (DbgA0_Pin << 16);}
#else
inline void dbgA0Ini() {}
inline void dbgA0Set() {}
inline void dbgA0Clr() {}
#endif

#ifdef DbgA1_Pin
inline void dbgA1Ini() {}
inline void dbgA1Set() {DbgA1_GPIO_Port->BSRR = DbgA1_Pin;}
inline void dbgA1Clr() {DbgA1_GPIO_Port->BSRR = (DbgA1_Pin << 16);}
#else
inline void dbgA1Ini() {}
inline void dbgA1Set() {}
inline void dbgA1Clr() {}
#endif

#ifdef DbgA2_Pin
inline void dbgA2Ini() {}
inline void dbgA2Set() {DbgA2_GPIO_Port->BSRR = DbgA2_Pin;}
inline void dbgA2Clr() {DbgA2_GPIO_Port->BSRR = (DbgA2_Pin << 16);}
#else
inline void dbgA2Ini() {}
inline void dbgA2Set() {}
inline void dbgA2Clr() {}
#endif

#ifdef DbgA3_Pin
inline void dbgA3Ini() {}
inline void dbgA3Set() {DbgA3_GPIO_Port->BSRR = DbgA3_Pin;}
inline void dbgA3Clr() {DbgA3_GPIO_Port->BSRR = (DbgA3_Pin << 16);}
#else
inline void dbgA3Ini() {}
inline void dbgA3Set() {}
inline void dbgA3Clr() {}
#endif

#ifdef DbgA4_Pin
inline void dbgA4Ini() {}
inline void dbgA4Set() {DbgA4_GPIO_Port->BSRR = DbgA4_Pin;}
inline void dbgA4Clr() {DbgA4_GPIO_Port->BSRR = (DbgA4_Pin << 16);}
#else
inline void dbgA4Ini() {}
inline void dbgA4Set() {}
inline void dbgA4Clr() {}
#endif

#ifdef DbgA5_Pin
inline void dbgA5Ini() {}
inline void dbgA5Set() {DbgA5_GPIO_Port->BSRR = DbgA5_Pin;}
inline void dbgA5Clr() {DbgA5_GPIO_Port->BSRR = (DbgA5_Pin << 16);}
#else
inline void dbgA5Ini() {}
inline void dbgA5Set() {}
inline void dbgA5Clr() {}
#endif

#ifdef DbgA6_Pin
inline void dbgA6Ini() {}
inline void dbgA6Set() {DbgA6_GPIO_Port->BSRR = DbgA6_Pin;}
inline void dbgA6Clr() {DbgA6_GPIO_Port->BSRR = (DbgA6_Pin << 16);}
#else
inline void dbgA6Ini() {}
inline void dbgA6Set() {}
inline void dbgA6Clr() {}
#endif

#ifdef DbgA7_Pin
inline void dbgA7Ini() {}
inline void dbgA7Set() {DbgA7_GPIO_Port->BSRR = DbgA7_Pin;}
inline void dbgA7Clr() {DbgA7_GPIO_Port->BSRR = (DbgA7_Pin << 16);}
#else
inline void dbgA7Ini() {}
inline void dbgA7Set() {}
inline void dbgA7Clr() {}
#endif

#ifdef DbgA8_Pin
inline void dbgA8Ini() {}
inline void dbgA8Set() {DbgA8_GPIO_Port->BSRR = DbgA8_Pin;}
inline void dbgA8Clr() {DbgA8_GPIO_Port->BSRR = (DbgA8_Pin << 16);}
#else
inline void dbgA8Ini() {}
inline void dbgA8Set() {}
inline void dbgA8Clr() {}
#endif

#ifdef DbgA9_Pin
inline void dbgA9Ini() {}
inline void dbgA9Set() {DbgA9_GPIO_Port->BSRR = DbgA9_Pin;}
inline void dbgA9Clr() {DbgA9_GPIO_Port->BSRR = (DbgA9_Pin << 16);}
#else
inline void dbgA9Ini() {}
inline void dbgA9Set() {}
inline void dbgA9Clr() {}
#endif

#ifdef DbgA10_Pin
inline void dbgA10Ini() {}
inline void dbgA10Set() {DbgA10_GPIO_Port->BSRR = DbgA10_Pin;}
inline void dbgA10Clr() {DbgA10_GPIO_Port->BSRR = (DbgA10_Pin << 16);}
#else
inline void dbgA10Ini() {}
inline void dbgA10Set() {}
inline void dbgA10Clr() {}
#endif

#ifdef DbgA11_Pin
inline void dbgA11Ini() {}
inline void dbgA11Set() {DbgA11_GPIO_Port->BSRR = DbgA11_Pin;}
inline void dbgA11Clr() {DbgA11_GPIO_Port->BSRR = (DbgA11_Pin << 16);}
#else
inline void dbgA11Ini() {}
inline void dbgA11Set() {}
inline void dbgA11Clr() {}
#endif

#ifdef DbgA12_Pin
inline void dbgA12Ini() {}
inline void dbgA12Set() {DbgA12_GPIO_Port->BSRR = DbgA12_Pin;}
inline void dbgA12Clr() {DbgA12_GPIO_Port->BSRR = (DbgA12_Pin << 16);}
#else
inline void dbgA12Ini() {}
inline void dbgA12Set() {}
inline void dbgA12Clr() {}
#endif

#ifdef DbgA13_Pin
inline void dbgA13Ini() {}
inline void dbgA13Set() {DbgA13_GPIO_Port->BSRR = DbgA13_Pin;}
inline void dbgA13Clr() {DbgA13_GPIO_Port->BSRR = (DbgA13_Pin << 16);}
#else
inline void dbgA13Ini() {}
inline void dbgA13Set() {}
inline void dbgA13Clr() {}
#endif

/* spindle isr time */
#ifdef Dbg0_Pin
inline void dbgSpIsrSet() {Dbg0_GPIO_Port->BSRR = Dbg0_Pin;}
inline void dbgSpIsrClr() {Dbg0_GPIO_Port->BSRR = (Dbg0_Pin << 16);}
inline uint16_t dbgSpIsrRead() {return((Dbg0_GPIO_Port->IDR & Dbg0_Pin) != 0);}
#else
inline void dbgSpIsrSet() {}
inline void dbgSpIsrClr() {}
inline uint16_t dbgSpIsrRead() {return(0);}
#endif

/* z isr time */
#ifdef Dbg1_Pin
inline void dbgZIsrSet() {Dbg1_GPIO_Port->BSRR = Dbg1_Pin;}
inline void dbgZIsrClr() {Dbg1_GPIO_Port->BSRR = (Dbg1_Pin << 16);}
inline uint16_t dbgZIsrRead() {return((Dbg1_GPIO_Port->IDR & Dbg1_Pin) != 0);}
#else
inline void dbgZIsrSet() {}
inline void dbgZIsrClr() {}
inline uint16_t dbgZIsrRead() {return(0);}
#endif

/* x isr time */
#ifdef Dbg2_Pin
inline void dbgXIsrSet() {Dbg2_GPIO_Port->BSRR = Dbg2_Pin;}
inline void dbgXIsrClr() {Dbg2_GPIO_Port->BSRR = (Dbg2_Pin << 16);}
inline uint16_t dbgXIsrRead() {return((Dbg2_GPIO_Port->IDR & Dbg2_Pin) != 0);}
#else
inline void dbgXIsrSet() {}
inline void dbgXIsrClr() {}
inline uint16_t dbgXIsrRead() {return(0);}
#endif

/* spindle cycle counter update */
inline void dbgSpCycSet() {}
inline void dbgSpCycClr() {}
inline uint16_t dbgSpCycRead() {return(0);}

/* z encoder input */
inline void dbgZEncSet() {}
inline void dbgZEncClr() {}
inline uint16_t dbgZEncRead() {return(0);}

/* z encoder output */
inline void dbgZOutSet() {}
inline void dbgZOutClr() {}
inline uint16_t dbgZOutRead() {return(0);}

/* x encoder */
inline void dbgXEncSet() {}
inline void dbgXEncClr() {}
inline uint16_t dbgXEncRead() {return(0);}

/* x encoder output */
inline void dbgXOutSet() {}
inline void dbgXOutClr() {}
inline uint16_t dbgXOutRead() {return(0);}

/* toggle on compare input */
inline void dbgIntCSet() {}
inline void dbgIntCClr() {}
inline uint16_t dbgIntCRead() {return(0);}

/* toggle on output pulse */
inline void dbgIntPSet() {}
inline void dbgIntPClr() {}
inline uint16_t dbgIntPRead() {return(0);}

/* toggle on input cycle */
inline void dbgCycleSet() {}
inline void dbgCycleClr() {}
inline uint16_t dbgCycleRead() {return(0);}

/* end of internal pulse cycle */
inline void dbgCycEndSet() {}
inline void dbgCycEndClr() {}
inline uint16_t dbgCycEndRead() {return(0);}

/* length of capture isr */
inline void dbgCapIsrSet() {}
inline void dbgCapIsrClr() {}
inline uint16_t dbgCapIsrRead() {return(0);}

/* length of internal isr */
inline void dbgIntIsrSet() {}
inline void dbgIntIsrClr() {}
inline uint16_t dbgIntIsrRead() {return(0);}

/* z cycle counter update */
inline void dbgZCycSet() {}
inline void dbgZCycClr() {}
inline uint16_t dbgZCycRead() {return(0);}

/* x cycle counter update */
inline void dbgXCycSet() {}
inline void dbgXCycClr() {}
inline uint16_t dbgXCycRead() {return(0);}

/* spindle accel and decel */
inline void dbgSpStopSet() {}
inline void dbgSpStopClr() {}
inline uint16_t dbgSpStopRead() {return(0);}

/* z accel and decel */
inline void dbgZAccelSet() {}
inline void dbgZAccelClr() {}
inline uint16_t dbgZAccelRead() {return(0);}

/* x accel and decel */
inline void dbgXAccelSet() {}
inline void dbgXAccelClr() {}
inline uint16_t dbgXAccelRead() {return(0);}

/* x remainder */
inline void dbgXRemSet() {}
inline void dbgXRemClr() {}
inline uint16_t dbgXRemRead() {return(0);}

/* spindle rev counter */
inline void dbgSpRevSet() {}
inline void dbgSpRevClr() {}
inline uint16_t dbgSpRevRead() {return(0);}

/* runout start */
inline void dbgRunoutSet() {}
inline void dbgRunoutClr() {}
inline uint16_t dbgRunoutRead() {return(0);}

/* z taper */
inline void dbgZTaperSet() {}
inline void dbgZTaperClr() {}
inline uint16_t dbgZTaperRead() {return(0);}

/* x taper */
inline void dbgXTaperSet() {}
inline void dbgXTaperClr() {}
inline uint16_t dbgXTaperRead() {return(0);}

/* slave start */
inline void dbgSlvSet() {}
inline void dbgSlvClr() {}
inline uint16_t dbgSlvRead() {return(0);}

/* step 2b isr */
inline void dbgS2bIsrSet() {}
inline void dbgS2bIsrClr() {}
inline uint16_t dbgS2bIsrRead() {return(0);}

/* step 3 isr */
inline void dbgS3IsrSet() {}
inline void dbgS3IsrClr() {}
inline uint16_t dbgS3IsrRead() {return(0);}

/* step 4 isr */
inline void dbgS4IsrSet() {}
inline void dbgS4IsrClr() {}
inline uint16_t dbgS4IsrRead() {return(0);}

/* step 5 isr */
inline void dbgS5IsrSet() {}
inline void dbgS5IsrClr() {}
inline uint16_t dbgS5IsrRead() {return(0);}

/* jog isr transition put in queue */
inline void dbgJogIsrSet() {}
inline void dbgJogIsrClr() {}
inline uint16_t dbgJogIsrRead() {return(0);}

/* jog idle queue checked */
inline void dbgJogMPG0Set() {}
inline void dbgJogMPG0Clr() {}
inline uint16_t dbgJogMPG0Read() {return(0);}

/* jog moving all cases */
inline void dbgJogMPG1Set() {}
inline void dbgJogMPG1Clr() {}
inline uint16_t dbgJogMPG1Read() {return(0);}

/* jog moving isr done start again */
inline void dbgJogMPG2Set() {}
inline void dbgJogMPG2Clr() {}
inline uint16_t dbgJogMPG2Read() {return(0);}

/* jog moving add to current distance */
inline void dbgJogMPG3Set() {}
inline void dbgJogMPG3Clr() {}
inline uint16_t dbgJogMPG3Read() {return(0);}

/* axis control */
inline void dbgAxisCtlSet() {}
inline void dbgAxisCtlClr() {}
inline uint16_t dbgAxisCtlRead() {return(0);}

/* x dro isr */
inline void dbgXDroSet() {}
inline void dbgXDroClr() {}
inline uint16_t dbgXDroRead() {return(0);}

/* x stop */
inline void dbgXStopSet() {}
inline void dbgXStopClr() {}
inline uint16_t dbgXStopRead() {return(0);}

/* x done */
inline void dbgXDoneSet() {}
inline void dbgXDoneClr() {}
inline uint16_t dbgXDoneRead() {return(0);}

/* x move using dro */
inline void dbgXUpdDroSet() {}
inline void dbgXUpdDroClr() {}
inline uint16_t dbgXUpdDroRead() {return(0);}

/* x dro final */
inline void dbgXFinalDroSet() {}
inline void dbgXFinalDroClr() {}
inline uint16_t dbgXFinalDroRead() {return(0);}

/* z dro isr */
inline void dbgZDroSet() {}
inline void dbgZDroClr() {}
inline uint16_t dbgZDroRead() {return(0);}

/* z stop */
inline void dbgZStopSet() {}
inline void dbgZStopClr() {}
inline uint16_t dbgZStopRead() {return(0);}

/* z done */
inline void dbgZDoneSet() {}
inline void dbgZDoneClr() {}
inline uint16_t dbgZDoneRead() {return(0);}

/* arc update */
inline void dbgArcUpdSet() {}
inline void dbgArcUpdClr() {}
inline uint16_t dbgArcUpdRead() {return(0);}

/* arc step */
inline void dbgArcStepSet() {}
inline void dbgArcStepClr() {}
inline uint16_t dbgArcStepRead() {return(0);}

/* encoder isr */
inline void dbgEncIsrSet() {}
inline void dbgEncIsrClr() {}
inline uint16_t dbgEncIsrRead() {return(0);}

/* remote command */
inline void dbgRemCmdSet() {}
inline void dbgRemCmdClr() {}
inline uint16_t dbgRemCmdRead() {return(0);}

/* z position error */
#ifdef Dbg3_Pin
inline void dbgZPosErrSet() {Dbg3_GPIO_Port->BSRR = Dbg3_Pin;}
inline void dbgZPosErrClr() {Dbg3_GPIO_Port->BSRR = (Dbg3_Pin << 16);}
inline uint16_t dbgZPosErrRead() {return((Dbg3_GPIO_Port->IDR & Dbg3_Pin) != 0);}
#else
inline void dbgZPosErrSet() {}
inline void dbgZPosErrClr() {}
inline uint16_t dbgZPosErrRead() {return(0);}
#endif

#endif /* __DBG_H */
#endif /* __STM32F4xx_HAL_H */
