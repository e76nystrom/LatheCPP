#if !defined(MOVE_CMD_INC)
#define MOVE_CMD_INC

struct S_MOVE_CMD
{
 char c0;
 char c1;
};

struct S_MOVE_CMD moveCmdStr[] =
{
 {'N', 'O',},            /*  0  0  no command */
 {'M', 'V',},            /*  1  1  move a set distance */
 {'J', 'G',},            /*  2  2  move while cmd are present */
 {'S', 'Y',},            /*  3  3  move dist synchronized to rotation */
 {'M', 'X',},            /*  4  4  rapid move */
 {'C', 'S',},            /*  5  5  jog at speed */
 {'J', 'S',},            /*  6  6  slow jog for home or probe */
};

#define MOVE_CMD_SIZE 7

#endif  /* MOVE_CMD_INC */
