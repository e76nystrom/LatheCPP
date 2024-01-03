#if !defined(SYNC_CMDS_INC)
#define SYNC_CMDS_INC

struct S_SYNC_CMDS
{
 char c0;
 char c1;
};

struct S_SYNC_CMDS syncCmdsStr[] =
{
 {'S', 'N',},            /*  0  0  sync with encoder */
 {'S', 'E',},            /*  1  1  sync with encoder */
 {'S', 'S',},            /*  2  2  sync with encoder scaler */
 {'E', 'S',},            /*  3  3  sync encoder runout encoder scaler */
 {'E', 'E',},            /*  4  4  sync encoder runout encoder */
};

#define SYNC_CMDS_SIZE 5

#endif  /* SYNC_CMDS_INC */
