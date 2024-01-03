#if !defined(SYNC_CMD_INC)
#define SYNC_CMD_INC

struct S_SYNC_CMD
{
 char c0;
 char c1;
};

struct S_SYNC_CMD syncCmdStr[] =
{
 {'S', 'N',},            /*  0  0  sync with encoder */
 {'S', 'E',},            /*  1  1  sync with encoder */
 {'S', 'S',},            /*  2  2  sync with encoder scaler */
 {'E', 'S',},            /*  3  3  sync encoder runout encoder scaler */
 {'E', 'E',},            /*  4  4  sync encoder runout encoder */
};

#define SYNC_CMD_SIZE 5

#endif  /* SYNC_CMD_INC */
