#if !defined(SYNC_PARM_INC)
#define SYNC_PARM_INC
// cFile

/* defines */

#define FLT (0x80)
#define SIZE_MASK (0x7)

enum SYNC_PARM_DEF
{
 SYNC_CYCLE,                    /* 0x00 sync cycle length */
 SYNC_OUTPUT,                   /* 0x01 sync outputs per cycle */
 SYNC_PRESCALER,                /* 0x02 sync prescaler */
 SYNC_ENCODER,                  /* 0x03 sync encoder pulses */
 SYNC_MAX_PARM,                 /* 0x04 sync maximum parameter */
};

#endif  /* SYNC_PARM_INC */
