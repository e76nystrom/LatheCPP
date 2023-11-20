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
 {'N', 'D',},            /*  9  9  send data done */
 {'L', 'X',},            /*  a 10  set x loc */
 {'L', 'Z',},            /*  b 11  set z loc */
 {'P', 'A',},            /*  c 12  pause */
 {'S', '+',},            /*  d 13  start spindle */
 {'S', '-',},            /*  e 14  stop spindle */
 {'U', 'S',},            /*  f 15  update spindle speed */
 {'P', 'S',},            /* 10 16  pass */
 {'S', 'A',},            /* 11 17  set accel parm */
 {'S', 'Q',},            /* 12 18  set accel parm queued */
 {'S', 'D',},            /* 13 19  set data */
 {'G', 'D',},            /* 14 20  set data */
 {'V', 'Z',},            /* 15 21  save z */
 {'V', 'X',},            /* 16 22  save x */
 {'I', 'Z',},            /* 17 23  save z steps inch */
 {'I', 'X',},            /* 18 24  save x steps inch */
 {'H', 'Z',},            /* 19 25  home offset z */
 {'H', 'X',},            /* 1a 26  home offset x */
 {'J', 'Z',},            /* 1b 27  jog move z */
 {'J', 'X',},            /* 1c 28  jog move x */
 {'M', 'Z',},            /* 1d 29  move z */
 {'M', 'X',},            /* 1e 30  move x */
 {'R', 'Z',},            /* 1f 31  move rel z */
 {'R', 'X',},            /* 20 32  move rel x */
 {'R', 'A',},            /* 21 33  read all status */
 {'R', 'D',},            /* 22 34  read all status */
 {'M', 'X',},            /* 23 35  max value */
};

#endif  /* RISCV_CMD */
