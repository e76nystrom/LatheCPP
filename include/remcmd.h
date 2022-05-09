#if 1	// <-

#if !defined(EXT)
#define EXT extern
#endif

#define REM_ISR 1		/* remote port using isr */
#define DBG_LOAD 1

void remcmd();
void loadVal();

#include "remCmdList.h"
#include "remParmList.h"
#include "ctlbits.h"

#endif	// ->
