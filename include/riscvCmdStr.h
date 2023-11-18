#if !defined(INC_RISCV_CMD)
#define INC_RISCV_CMD

struct S_RISCV_CMD
{
 char c0;
 char c1;
};

struct S_RISCV_CMD riscvCmdStr[] =
{
 {'N', 'O',},            /*  0  0  no operation */
 {'O', 'S',},            /*  1  1  start */
 {'O', 'D',},            /*  2  2  done */
 {'S', 'U',},            /*  3  3  setup */
 {'R', 'E',},            /*  4  4  resume */
 {'S', 'P',},            /*  5  5  stop */
 {'S', 'X',},            /*  6  6  stop x */
 {'S', 'Z',},            /*  7  7  stop z */
 {'D', 'N',},            /*  8  8  done */
 {'L', 'X',},            /*  9  9  set x loc */
 {'L', 'Z',},            /*  a 10  set z loc */
 {'P', 'A',},            /*  b 11  pause */
 {'S', '+',},            /*  c 12  start spindle */
 {'S', '-',},            /*  d 13  stop spindle */
 {'P', 'S',},            /*  e 14  pass */
 {'S', 'A',},            /*  f 15  set accel parm */
 {'S', 'Q',},            /* 10 16  set accel parm queued */
 {'S', 'D',},            /* 11 17  set data */
 {'G', 'D',},            /* 12 18  set data */
 {'V', 'Z',},            /* 13 19  save z */
 {'V', 'X',},            /* 14 20  save x */
 {'I', 'Z',},            /* 15 21  save z steps inch */
 {'I', 'X',},            /* 16 22  save x steps inch */
 {'H', 'Z',},            /* 17 23  home offset z */
 {'H', 'X',},            /* 18 24  home offset x */
 {'J', 'Z',},            /* 19 25  jog move z */
 {'J', 'X',},            /* 1a 26  jog move x */
 {'M', 'Z',},            /* 1b 27  move z */
 {'M', 'X',},            /* 1c 28  move x */
 {'R', 'Z',},            /* 1d 29  move rel z */
 {'R', 'X',},            /* 1e 30  move rel x */
 {'R', 'A',},            /* 1f 31  read all status */
 {'R', 'D',},            /* 20 32  read all status */
 {'M', 'X',},            /* 21 33  max value */
};

#endif  /* RISCV_CMD */
