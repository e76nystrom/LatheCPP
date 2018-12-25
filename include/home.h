#if not defined(XHome_Pin)
#define XHome_GPIO_Port Pin11_GPIO_Port
#define XHome_Pin Pin11_Pin
#endif

#if HOME_TEST == 0
#define xHomeSet() ((Pin11_GPIO_Port->BSRR & Pin11_Pin) == 0)
#define xHomeClr() ((Pin11_GPIO_Port->BSRR & Pin11_Pin) != 0)
#define xUpdHomeLoc()
#else
#define xHomeSet() ((xHomeEnd <= xHomeLoc) && (xHomeLoc <= xHomeStart))
#define xHomeClr() ((xHomeLoc  < xHomeEnd) || (xHomeStart <  xHomeLoc))
#define xUpdHomeLoc() xHomeLoc += xIsr.dir
#endif	/* HOME_TEST */
