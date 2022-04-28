#if 1	// <-

#if !defined(EXT)
#define EXT extern
#endif

#define REM_ISR 1		/* remote port using isr */

#if REM_ISR
#define putrem putRem
#define putstrrem putstrRem
#define sndhexrem sndhexRem
#define getrem getRem
#define gethexrem() gethexRem()
#define getnumrem getnumRem
#define getstrrem getstrRem
#else
#define putrem putx1
#define putstrrem putstr1
#define sndhexrem sndhex1
#define getrem get1
#define gethexrem gethex1
#define getnumrem getnum1
#define getstrrem getstr1
#endif

#define DBG_LOAD 1

void remcmd(void);
void loadVal(void);

#include "remCmdList.h"
#include "remParmList.h"
#include "ctlbits.h"

#endif	// ->
