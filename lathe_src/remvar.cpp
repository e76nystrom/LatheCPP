//#if !defined(INCLUDE)
#include <stdint.h>          /* For uint16_t definition */
#if !defined(EXT)
#define EXT
#endif
//#endif

//#include "remvardef.h"
#include "remstruct.h"
#include "ctlbits.h"
#include "ctlstates.h"

typedef struct sParm
{
 // void *p;			/* pointer to parameter */
 char size;			/* parameter size */
} T_PARM, *P_PARM;

//#define PARM(x) {(void *) sizeof(x)}
#define PARM(x) {sizeof(rVar.x)}
