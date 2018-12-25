#if not defined(Probe_Pin)
#define Probe_GPIO_Port Pin12_GPIO_Port
#define Probe_Pin Pin12_Pin
#endif

#if PROBE_TEST == 0
#define probeSet() (((Pin12_GPIO_Port->BSRR & Pin12_Pin) != 0) ^ probeInv)
#define probeClr() (((Pin12_GPIO_Port->BSRR & Pin12_Pin) == 0) ^ probeInv)
#define setProbeDist()
#define clrProbeDist()
#define updProbeDist()
#else
#define probeSet() (probeDist == 0)
#define probeClr() (probeDist > 0)
#define setProbeDist(val) probeDist = val >= 0 ? val : -val
#define clrProbeDist() probeDist = 0
#define updProbeDist() if (probeDist > 0) --probeDist
#endif
