#include <stdint.h>          /* For uint16_t definition */
#if !defined(EXT)
#define EXT
#endif

#include "remstruct.h"
#include "ctlbits.h"
#include "ctlstates.h"

typedef struct sParm
{
 char size;			/* parameter size */
} T_PARM, *P_PARM;

#define PARM(x) {sizeof(rVar.x)}
