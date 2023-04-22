#if !defined(REMCMD_INC)	// <-
#define REMCMD_INC

#if !defined(EXT)
#define EXT extern
#endif

#if defined(USB)
#define REM_USB 0
#endif  /* USB */

#define REM_ISR 1		/* remote port using isr */
#define DBG_LOAD 1

void remCmd();
void loadVal();

#include "remCmdList.h"
#include "remParmList.h"
#include "ctlbits.h"

#endif  /* REMCMD_INC */	// ->
