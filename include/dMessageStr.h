#if !defined(D_MESSAGE_INC)
#define D_MESSAGE_INC

struct S_D_MESSAGE
{
 char c0;
 char c1;
 char c2;
 char c3;
};

struct S_D_MESSAGE dMessageStr[] =
{
 {'P', 'A', 'S', 'S',},  /*  0  0  pass done */
 {'D', 'O', 'N', 'E',},  /*  1  1  all operations done */
 {'T', 'E', 'S', 'T',},  /*  2  2  test message */
 {'H', 'S', 'T', ' ',},  /*  3  3  home state */
 {'M', 'S', 'T', 'A',},  /*  4  4  move state */
 {'M', 'C', 'M', 'D',},  /*  5  5  move command */
 {'X', 'B', 'A', 'S',},  /*  6  6  x base */
 {'X', 'M', 'V', 'C',},  /*  7  7  x move command */
 {'X', 'C', 'T', 'L',},  /*  8  8  x axis ctl */
 {'X', 'M', 'O', 'V',},  /*  9  9  x move to location */
 {'X', 'C', 'U', 'R',},  /*  a 10  x current location */
 {'X', 'L', 'O', 'C',},  /*  b 11  x end location */
 {'X', 'D', 'S', 'T',},  /*  c 12  x distance */
 {'X', 'S', 'T', 'P',},  /*  d 13  x steps */
 {'X', 'S', 'T', 'A',},  /*  e 14  x state */
 {'X', 'B', 'L', 'S',},  /*  f 15  x backlash steps */
 {'X', 'D', 'R', 'O',},  /* 10 16  x dro location */
 {'X', 'P', 'D', 'R',},  /* 11 17  x pass dro location */
 {'X', 'E', 'X', 'P',},  /* 12 18  x expected location */
 {'X', 'E', 'R', 'R',},  /* 13 19  x error with respect to dro */
 {'X', 'W', 'T', ' ',},  /* 14 20  x wait */
 {'X', 'D', 'N', ' ',},  /* 15 21  x done */
 {'X', 'E', 'S', 'T',},  /* 16 22  x spindle encoder start count */
 {'X', 'E', 'D', 'N',},  /* 17 23  x spindle encoder done count */
 {'X', 'X', ' ', ' ',},  /* 18 24  x  */
 {'X', 'Y', ' ', ' ',},  /* 19 25  x  */
 {'X', 'I', 'D', 'R',},  /* 1a 26  x dro at index pulse */
 {'X', 'I', 'P', 'O',},  /* 1b 27  x position at index pulse */
 {'Z', 'B', 'A', 'S',},  /* 1c 28  Z base */
 {'Z', 'M', 'V', 'C',},  /* 1d 29  z move command */
 {'Z', 'C', 'T', 'L',},  /* 1e 30  z axis ctl */
 {'Z', 'M', 'O', 'V',},  /* 1f 31  z move location */
 {'Z', 'C', 'U', 'R',},  /* 20 32  x current location */
 {'Z', 'L', 'O', 'C',},  /* 21 33  z end location */
 {'Z', 'D', 'S', 'T',},  /* 22 34  z distance */
 {'Z', 'S', 'T', 'P',},  /* 23 35  z steps */
 {'Z', 'S', 'T', 'A',},  /* 24 36  z state */
 {'Z', 'B', 'L', 'S',},  /* 25 37  z backlash steps */
 {'Z', 'D', 'R', 'O',},  /* 26 38  z dro location */
 {'Z', 'P', 'D', 'R',},  /* 27 39  z pass dro location */
 {'Z', 'E', 'X', 'P',},  /* 28 40  z expected location */
 {'Z', 'E', 'R', 'R',},  /* 29 41  z error with respect to dro */
 {'Z', 'W', 'T', ' ',},  /* 2a 42  z wait */
 {'Z', 'D', 'N', ' ',},  /* 2b 43  z done */
 {'Z', 'E', 'S', 'T',},  /* 2c 44  z spindle encoder start count */
 {'Z', 'E', 'D', 'N',},  /* 2d 45  Z spindle encoder done count */
 {'Z', 'X', ' ', ' ',},  /* 2e 46  z  */
 {'Z', 'Y', ' ', ' ',},  /* 2f 47  z  */
 {'Z', 'I', 'D', 'R',},  /* 30 48  z dro at index pulse */
 {'Z', 'I', 'P', 'O',},  /* 31 49  z position at index pulse */
 {'M', 'A', 'X', ' ',},  /* 32 50  debug maximum */
};

#define D_MESSAGE_SIZE 51

#endif  /* D_MESSAGE_INC */
