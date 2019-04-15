#if !defined(INCLUDE)
#define __SERIALIO__
#include "stm32f4xx_hal.h"

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "main.h"
#include "config.h"
#include "dbg.h"

#ifdef REMPORT
#include "remcmd.h"
#include "remvar.h"
#endif

#ifdef EXT
#undef EXT
#endif

#define EXT
#include "serialio.h"
#endif	/* !defined(INCLUDE) */

#if defined(__SERIALIO_INC__)	// <-

#if !defined(EXT)
#define EXT extern
#endif

#define DBGMSG 2

void wdUpdate(void);

enum RTN_VALUES
{
 NO_VAL,
 INT_VAL,
 FLOAT_VAL,
};

void newline(void);

#define MAXDIG 10		/* maximum input digits */

/* debug port routines */

int __attribute__((__weak__, __section__(".libc")))
write (int handle, const char *buffer, int len);

void putx(char c);
void putstr(const char *p);
void sndhex(unsigned char *p, int size);
char getx(void);
char gethex(void);
char getstr(char *buf, int bufLen);
unsigned char getnum(void);
unsigned char getfloat(void);

char query(const char *format, ...);
char query(unsigned char (*get)(), const char *format, ...);

void prtbuf(unsigned char *p, int size);
void prtibuf(int16_t *p, int size);

//#ifdef REMPORT

/* polled remote port routines */

void putx1(char c);
void putstr1(const char *p);
void sndhex1(unsigned char *p, int size);
char gethex1(void);
char getx1(void);
char getstr1(char *buf, int bufLen);
unsigned char getnum1(void);

/* interrupt remote port routines */

void initRem(void);
void putRem(char ch);
void putstrRem(const char *p);
void sndhexRem(const unsigned char *p, int size);
int getRem(void);
char gethexRem(void);
char getstrRem(char *buf, int bufLen);
unsigned char getnumRem(void);

//#endif

/* debug message routines */

#if DBGMSG
#if DBGMSG == 2
void dbgmsg(char dbg, int32_t val);
#else
void dbgmsg(char *str, int32_t val);
void dbgmsgx(char *str, char reg, int32_t val);
#endif
void clrDbgBuf(void);
#else
#define dbgmsg(a, b)
#define dbgmsgx(a, b, c)
#endif	/* DBGMSG */

/* debug port buffered character routines */

extern "C" void remoteISR(void);

void initCharBuf(void);
void putBufChar(char ch);
void putBufCharIsr(char ch);
void putBufCharX(char ch);
void putBufStr(const char *s);
void putBufStrX(const char *s);
void putBufStrIsr(const char *s);
int pollBufChar(void);
void flushBuf(void);

/* printf output */

extern "C" ssize_t _write (int fd  __attribute__((unused)),
			   const char* buf, size_t nbyte);

EXT unsigned char *p;
EXT int32_t val;
EXT float fVal;

EXT int32_t valRem;
EXT float fValRem;

EXT char dbgBuffer;

EXT char lineStart;
EXT char eolFlag;

/* debug port macros */

#ifdef __cplusplus

inline void PUTX(char c)
{
 while ((DBGPORT->SR & USART_SR_TXE) == 0)
 {
  DBGPORT->DR = c;
 }
}

inline uint16_t chRdy()
{
 return((DBGPORT->SR & USART_SR_RXNE));
}

inline char chRead()
{
 return(DBGPORT->DR);
}

inline uint16_t chRdy1()
{
 return((REMPORT->SR & USART_SR_RXNE));
}

inline char chRead1()
{
 return(REMPORT->DR);
}

#else

#define PUTX(c) while ((DBGPORT->SR & USART_SR_TXE) == 0); DBGPORT->DR = c

#define chRdy() (DBGPORT->SR & USART_SR_RXNE)
#define chRead() DBGPORT->DR

/* remote port macros */

#define chRdy1() (REMPORT->SR & USART_SR_RXNE)
#define chRead1() REMPORT->DR

#endif

// #define SNDHEX(val) sndhex((unsigned char *) &val, sizeof(val))

#if DBGMSG

#define MAXDBGMSG 200

#if DBGMSG == 2

typedef struct
{
 char dbg;
 int32_t val;
 int32_t time;
} T_DBGMSG, *P_DBGMSG;

#else

typedef struct
{
 char str[12];
 int32_t val;
 int32_t time;
} T_DBGMSG, *P_DBGMSG;

#endif

EXT T_DBGMSG dbgdata[MAXDBGMSG];

EXT int16_t dbgcnt;
EXT uint16_t dbgfil;
EXT uint16_t dbgemp;

#endif	/* DBGMSG */

/* remote port interrupt driven routines */

#define TX_BUF_SIZE 140
#define RX_BUF_SIZE 80

typedef struct
{
 int tx_fil;
 int tx_emp;
 int tx_count;
 char tx_buffer[TX_BUF_SIZE];
 int rx_fil;
 int rx_emp;
 int rx_count;
 char rx_buffer[RX_BUF_SIZE];
 int state;
} T_REMCTL, *P_REMCTL;

EXT T_REMCTL remCtl;

#endif	// ->
#ifdef __SERIALIO__

/* polled debug port routines */

void newline(void)
{
 if (dbgBuffer)
 {
  putBufChar('\n');
  putBufChar('\r');
 }
 else
 {
  putx('\n');
  putx('\r');
 }
}

void putx(char c)
{
 while ((DBGPORT->SR & USART_SR_TXE) == 0)
  ;
 DBGPORT->DR = c;
}

void putstr(const char *p)
{
 while (1)
 {
  char ch = *p++;
  if (ch == 0)
   break;
  putx(ch);
  if (ch == '\n')
   putx('\r');
 }
}

void sndhex(unsigned char *p, int size)
{
 char tmp;
 char ch;

 p += size;
 while (size != 0)
 {
  --size;
  p--;
  tmp = *p;
  ch = tmp;
  ch >>= 4;
  ch &= 0xf;
  if (ch < 10)
   ch += '0';
  else
   ch += 'a' - 10;
//  while (utxbf1);
//  u1txreg = ch;
  PUTX(ch);

  tmp &= 0xf;
  if (tmp < 10)
   tmp += '0';
  else
   tmp += 'a' - 10;
//  while (utxbf1);
//  u1txreg = tmp;
  PUTX(tmp);
 }
}

char getx(void)
{
 while ((DBGPORT->SR & USART_SR_RXNE) == 0)
 {
  pollBufChar();
 }
 return(DBGPORT->DR);
}

char gethex(void)
{
 char ch;
 int count;

 val = 0;
 count = 0;
 while (count <= 8)
 {
  ch = getx();
  if ((ch >= '0')
  &&  (ch <= '9'))
  {
   putBufChar(ch);
   ch -= '0';
   count++;
  }
  else if ((ch >= 'a')
  &&       (ch <= 'f'))
  {
   putBufChar(ch);
   ch -= 'a' - 10;
   count++;
  }
  else if ((ch == 8)
       ||  (ch == 127))
  {
   if (count > 0)
   {
    --count;
    val >>= 4;
    putBufChar(8);
    putBufChar(' ');
    putBufChar(8);
   }
  }
  else if (ch == ' ')
  {
   putBufChar(ch);
   break;
  }
  else if (ch == '\r')
   break;
  else
   continue;
  val <<= 4;
  val += ch;
 }
 return(count != 0);
}

char getstr(char *buf,  int bufLen)
{
 int len = 0;
 char *p;
 char ch;
 p = buf;
 while (1)
 {
  ch = getx();
  if ((ch == '\n') || (ch == '\r'))
  {
   if (len < bufLen)
   {
    *p++ = 0;
   }
   newline();
   break;
  }
  else if ((ch == 8) || (ch == 127))
  {
   if (len > 0)
   {
    --len;
    --p;
    putBufChar(8);
    putBufChar(' ');
    putBufChar(8);
   }
  }
  else
  {
   if (len < bufLen)
   {
    putBufChar(ch);
    *p++ = ch;
    len++;
   }
  }
 }
 return(len);
}

unsigned char getnum(void)
{
 char ch;			/* input character */
 char chbuf[MAXDIG];		/* input digit buffer */
 unsigned char chidx;		/* input character index */
 unsigned char count;		/* input character count */
 char neg;			/* negative flag */
 char hex;			/* hex flag */

 neg = 0;
 hex = 0;
 val = 0;
 chidx = 0;
 count = 0;
 while (1)
 {
  ch = getx();
  if ((ch >= '0')
  &&  (ch <= '9'))
  {
   if (chidx < MAXDIG)
   {
    putBufChar(ch);
    chbuf[chidx] = ch - '0';
    chidx++;
   }
  }
  else if ((ch >= 'a')
  &&       (ch <= 'f'))
  {
   if (chidx < MAXDIG)
   {
    hex = 1;
    putBufChar(ch);
    chbuf[chidx] = ch - 'a' + 10;
    chidx++;
   }
  }
  else if ((ch == 8)
       ||  (ch == 127))
  {
   if (chidx > 0)
   {
    --chidx;
    putBufChar(8);
    putBufChar(' ');
    putBufChar(8);
   }
  }
  else if ((ch == '\r')
       ||  (ch == ' '))
  {
   if (hex)
   {
    while (count < chidx)
    {
     val = (val << 4) + chbuf[count];
     count++;
    }
   }
   else
   {
    while (count < chidx)
    {
     val = val * 10 + chbuf[count];
     count++;
    }
   }
   if (neg)
    val = -val;
   return(count);
  }
  else if (chidx == 0)
  {
   if (ch == '-')
   {
    putBufChar(ch);
    neg = 1;
   }
   else if (ch == 'x')
   {
    putBufChar(ch);
    hex = 1;
   }
  }
  else
   printf("%d ", ch);
 }
}

unsigned char getfloat(void)
{
 char chbuf[MAXDIG];		/* input digit buffer */
 
 char len = getstr(chbuf, sizeof(chbuf));
 if (len != 0)
 {
  fVal = atof(chbuf);
  return(1);
 }
 return(0);
}

char query(const char *format, ...)
{
 va_list args;
 va_start(args, format);
 vprintf(format, args);
 va_end(args);
 flushBuf();
 char ch = getx();
 putx(ch);
 newline();
 return(ch);
}

char query(unsigned char (*get)(), const char *format, ...)
{
 va_list args;
 va_start(args, format);
 vprintf(format, args);
 va_end(args);
 flushBuf();
 char ch = get();
 newline();
 return(ch);
}

void prtbuf(unsigned char *p, int size)
{
 char col;

 col = 16;			/* number of columns */
 while (size != 0)		/* while not done */
 {
  --size;			/* count off data sent */
  if (col == 16)		/* if column 0 */
  {
   printf("%8x  ", (unsigned int) p); /* output address */
  }
  printf("%2x", *p++);		/* output value */
   --col;			/* count off a column */
  if (col)			/* if not end of line */
  {
   if ((col & 1) == 0)		/* if even column */
    printf(" ");		/* output a space */
  }
  else				/* if end of line */
  {
   col = 16;			/* reset column counter */
   if (size != 0)		/* if not done */
    printf("\n");
  }
 }
}

void prtibuf(int16_t *p, int size)
{
 char col;

 col = 8;			/* number of columns */
 size >>= 1;			/* make into a count of integers */
 while (size != 0)		/* while not done */
 {
  --size;			/* count off data sent */
  if (col == 8)			/* if column 0 */
  {
   printf("%8x  ", (unsigned int) p); /* output address */
  }
  printf("%4x", *p++);		/* output value */
   --col;			/* count off a column */
  if (col == 0)			/* if not end of line */
  {
   col = 8;			/* reset column counter */
   if (size != 0)		/* if not done */
    printf("\n");
  }
  else
   printf(" ");
 }
}

#ifdef REMPORT

/* polled remote port routines */

void putx1(char c)
{
 while ((REMPORT->SR & USART_SR_TXE) == 0)
  ;
 REMPORT->DR = c;
}

void putstr1(const char *p)
{
 while (1)
 {
  char ch = *p++;
  if (ch == 0)
   break;
  putx1(ch);
  if (ch == '\n')
   putx1('\r');
 }
}

void sndhex1(unsigned char *p, int size)
{
 char tmp;
 char ch;

 p += size;
 while (size != 0)
 {
  --size;
  p--;
  tmp = *p;
  ch = tmp;
  ch >>= 4;
  ch &= 0xf;
  if (ch < 10)
   ch += '0';
  else
   ch += 'a' - 10;
  putx1(ch);

  tmp &= 0xf;
  if (tmp < 10)
   tmp += '0';
  else
   tmp += 'a' - 10;
  putx1(tmp);
 }
}

char getx1(void)
{
 while ((REMPORT->SR & USART_SR_RXNE) == 0)
  pollBufChar();
 return(REMPORT->DR);
}

char getstr1(char *buf, int bufLen)
{
 int len = 0;
 char *p;
 char ch;
 p = buf;
 while (1)
 {
  ch = getx1();
  if ((ch == ' ') || (ch == '\n'))
  {
   putx1(ch);
   if (ch == '\n')
    putx1('\r');
   if (len < bufLen)
   {
    *p++ = 0;
   }
   break;
  }
  else if ((ch == 8) || (ch == 127))
  {
   if (len > 0)
   {
    --len;
    --p;
    putx1(8);
    putx1(' ');
    putx1(8);
   }
  }
  else
  {
   if (len < bufLen)
   {
    putx1(ch);
    *p++ = ch;
    len++;
   }
  }
 }
 return(len);
}

char gethex1(void)
{
 char ch;
 int count;

 valRem = 0;
 count = 0;
 while (count <= 8)
 {
  ch = getx1();
  if ((ch >= '0')
  &&  (ch <= '9'))
  {
   putx1(ch);
   ch -= '0';
   count++;
  }
  else if ((ch >= 'a')
  &&       (ch <= 'f'))
  {
   putx1(ch);
   ch -= 'a' - 10;
   count++;
  }
  else if ((ch == 8)
       ||  (ch == 127))
  {
   if (count > 0)
   {
    --count;
    valRem >>= 4;
    putx1(8);
    putx1(' ');
    putx1(8);
   }
  }
  else if (ch == ' ')
  {
   putx1(ch);
   break;
  }
  else if (ch == '\r')
   break;
  else
   continue;
  valRem <<= 4;
  valRem += ch;
 }
 return(count != 0);
}

unsigned char getnum1(void)
{
 char chbuf[MAXDIG];		/* input digit buffer */
 
 char len = getstr1(chbuf, sizeof(chbuf));
 if (len != 0)
 {
  char *p = chbuf;
  int i;
  for (i = 0; i < len; i++)
  {
   char ch = *p++;
   if (ch == '.')
   {
    fValRem = atof(chbuf);
    return(FLOAT_VAL);
   }
   if ((ch == 'x') || (ch == 'X'))
   {
    char *endptr;
    valRem = strtol(p, &endptr, 16);
    return(INT_VAL);
   }
  }
  valRem = atoi(chbuf);
  return(INT_VAL);
 }
 return(NO_VAL);
}

void initRem(void)
{
 memset(&remCtl, 0, sizeof(remCtl));
 REMPORT->CR1 |= USART_CR1_RXNEIE;
}

extern "C" void remoteISR(void)
{
 P_REMCTL u = &remCtl;
 if (REMPORT->SR & USART_SR_RXNE) /* if received character */
 {
  char ch = REMPORT->DR;	/* read character */
  if (u->state == 0)		/* if waiting for start */
  {
   if (ch == 1)			/* if start of message received */
   {
    u->state = 1;		/* set to start receiving */
   }
  }
  else				/* if receiving data */
  {
   if (u->rx_count < RX_BUF_SIZE) /* if room in buffer */
   {
    int fill = u->rx_fil;	/* temp copy of fill pointer */
    u->rx_buffer[fill++] = ch;	/* put character in buffer */
    if (fill >= RX_BUF_SIZE)	/* if past end of buffer */
     fill = 0;			/* reset to zero */
    u->rx_fil = fill;		/* save fill pointer */
    u->rx_count++;		/* update count */

    if (ch == '\r')		/* if end of command */
    {
     u->state = 0;		/* set to waiting for start */
     NVIC_ClearPendingIRQ(REMOTE_IRQn); /* clear pending interrupt */
     remcmd();			/* process remote command */
    }
   }
  }
 }
 if (REMPORT->SR & USART_SR_ORE) /* if overrun errror */
 {
  if (REMPORT->DR)		/* read character */
  {
  }
 }
 if (REMPORT->SR & USART_SR_TXE) /* if transmit empty */
 {
  if (u->tx_count != 0)		/* if anything in buffer */
  {
   int emp = u->tx_emp;		/* temp copy of empty pointer */
   REMPORT->DR = u->tx_buffer[emp++]; /* send character */
   if (emp >= TX_BUF_SIZE)	/* if at buffer end */
    emp = 0;			/* reset to start */
   u->tx_emp = emp;		/* save empty pointer */
   --u->tx_count;		/* count it off */
  }
  else				/* if nothing to send */
   REMPORT->CR1 &= ~USART_CR1_TXEIE; /* disable transmit interrupt */
 }
}

void putRem(char ch)
{
 P_REMCTL u = &remCtl;
 if (u->tx_count < TX_BUF_SIZE) /* if room for data */
 {
  int fill = u->tx_fil;		/* temp copy of fill pointer */
  u->tx_buffer[fill++] = ch;	/* put character in buffer */
  if (fill >= TX_BUF_SIZE)	/* if past end of buffer */
   fill = 0;			/* reset to zero */
  u->tx_fil = fill;		/* save fill pointer */
  u->tx_count++;		/* update count */
  REMPORT->CR1 |= USART_CR1_TXEIE; /* enable transmit interrupt */
 }
}

void putstrRem(const char *p)
{
 while (1)
 {
  char ch = *p++;
  if (ch == 0)
   break;
  putRem(ch);
  if (ch == '\n')
   putRem('\r');
 }
}

void sndhexRem(const unsigned char *p, int size)
{
 char tmp;
 char ch;
 int zeros = 0;

 p += size;
 while (size != 0)
 {
  --size;
  p--;
  tmp = *p;
  ch = tmp;
  ch >>= 4;
  ch &= 0xf;
  if ((ch != 0)
  ||  zeros)
  {
   zeros = 1;
   if (ch < 10)
    ch += '0';
   else
    ch += 'a' - 10;
   putRem(ch);
  }

  tmp &= 0xf;
  if ((tmp != 0)
  ||  zeros)
  {
   zeros = 1;
   if (tmp < 10)
    tmp += '0';
   else
    tmp += 'a' - 10;
   putRem(tmp);
  }
 }
 if (zeros == 0)
  putRem('0');
}

int getRem(void)
{
 P_REMCTL u = &remCtl;
 if (u->rx_count != 0)		/* if anything in buffer */
 {
  int emp = u->rx_emp;		/* temp copy of empty pointer */
  unsigned char ch = u->rx_buffer[emp++]; /* send character */
  if (emp >= RX_BUF_SIZE)	/* if at buffer end */
   emp = 0;			/* reset to start */
  u->rx_emp = emp;		/* save empty pointer */
  --u->rx_count;		/* count it off */
  return(ch);
 }
 return(-1);			/* nothing in buffer */
}

char gethexRem(void)
{
 char ch;
 int count;

 valRem = 0;
 count = 0;
 while (count <= 8)
 {
  int tmp = getRem();
  if (tmp > 0)
  {
   ch = (char) tmp;
   if ((ch >= '0')
   &&  (ch <= '9'))
   {
    putRem(ch);
    ch -= '0';
    count++;
   }
   else if ((ch >= 'a')
   &&       (ch <= 'f'))
   {
    putRem(ch);
    ch -= 'a' - 10;
    count++;
   }
   else if (ch == ' ')
   {
    putRem(ch);
    break;
   }
   else if (ch == '\r')
    break;
   else
    continue;
   valRem <<= 4;
   valRem += ch;
  }
  else
   return(0);
 }
 return(count != 0);
}

char getstrRem(char *buf, int bufLen)
{
 int len = 0;
 char *p;
 char ch;
 p = buf;
 while (1)
 {
  int tmp = getRem();
  if (tmp > 0)
  {
   ch = (char) tmp;
   if ((ch == ' ') || (ch == '\n'))
   {
    putRem(ch);
    if (ch == '\n')
     putRem('\r');
    if (len < bufLen)
    {
     *p++ = 0;
    }
    break;
   }
   else
   {
    if (len < bufLen)
    {
     putRem(ch);
     *p++ = ch;
     len++;
    }
   }
  }
  else
  {
   len = 0;
   break;
  }
 }
 return(len);
}

unsigned char getnumRem(void)
{
 char chbuf[MAXDIG];		/* input digit buffer */
 
 char len = getstrRem(chbuf, sizeof(chbuf));
 if (len != 0)
 {
  char *p = chbuf;
  int i;
  for (i = 0; i < len; i++)
  {
   char ch = *p++;
   if (ch == '.')
   {
    fValRem = atof(chbuf);
    return(FLOAT_VAL);
   }
   if ((ch == 'x') || (ch == 'X'))
   {
    char *endptr;
    valRem = strtol(p, &endptr, 16);
    return(INT_VAL);
   }
  }
  valRem = atoi(chbuf);
  return(INT_VAL);
 }
 return(NO_VAL);
}

/* debug output buffer routines */

#define CHAR_BUF_SIZE 4096
int charFil;
int charEmp;
int charCount;
unsigned int charOverflow;
char charBuf[CHAR_BUF_SIZE];

#define ISR_BUF_SIZE 64
int isrFil;
int isrEmp;
int isrCount;
unsigned int isrOverflow;
char isrBuf[ISR_BUF_SIZE];

#endif

void initCharBuf(void)
{
 dbgBuffer = 1;
 charFil = 0;
 charEmp = 0;
 charCount = 0;
 charOverflow = 0;
 lineStart = 1;
 eolFlag = 1;

 isrFil = 0;
 isrEmp = 0;
 isrCount = 0;
 isrOverflow = 0;
}

void delayUSec(unsigned short delay);

void putBufStr(const char *s)
{
 char ch;
 while ((ch = *s++) != 0)
 {
  putBufChar(ch);
  if (ch == '\n')
   putBufChar('\r');
 }
}

void putBufStrX(const char *s)
{
 char ch;
 while ((ch = *s++) != 0)
 {
  putBufCharX(ch);
  if (ch == '\n')
   putBufCharX('\r');
 }
}

void putBufStrIsr(const char *s)
{
 char ch;
 while ((ch = *s++) != 0)
 {
  putBufCharIsr(ch);
  if (ch == '\n')
   putBufCharIsr('\r');
 }
}

void putBufChar(char ch)
{
 __disable_irq();
 if (charCount < CHAR_BUF_SIZE)
 {
  charCount++;
  __enable_irq();
  charBuf[charFil] = ch;
  charFil++;
  if (charFil >= CHAR_BUF_SIZE)
   charFil = 0;
 }
 else
 {
  __enable_irq();
  charOverflow++;
 }
 
 pollBufChar();
}

void putBufCharIsr(char ch)
{
 if (isrCount < ISR_BUF_SIZE)
 {
  isrCount++;
  isrBuf[isrFil] = ch;
  isrFil++;
  if (isrFil >= ISR_BUF_SIZE)
   isrFil = 0;
 }
 else
  isrOverflow++;
}

void putBufCharX(char ch)
{
 if (isrCount < ISR_BUF_SIZE)
 {
  __disable_irq();
  isrCount++;
  isrBuf[isrFil] = ch;
  isrFil++;
  if (isrFil >= ISR_BUF_SIZE)
   isrFil = 0;
  __enable_irq();
 }
}

int pollBufChar(void)
{
 if (WD_ENA)
  IWDG->KR = 0xAAAA;		/* update hardware watchdog */

 if (setupDone)
  wdUpdate();

 if ((DBGPORT->SR & USART_SR_TXE) != 0)
 {
  if (lineStart)
  {
   switch (lineStart)
   {
   case 1:
    if (isrCount != 0)
    {
     DBGPORT->DR = '*';
     lineStart = 2;
    }
    else
     lineStart = 0;
    break;
    
   case 2:
    if (isrCount > 0)
    {
     DBGPORT->DR = isrBuf[isrEmp];
     isrEmp++;
     if (isrEmp >= ISR_BUF_SIZE)
      isrEmp = 0;
     __disable_irq();
     --isrCount;
     __enable_irq();
    }
    else
     lineStart = 3;
    break;

   case 3:
     DBGPORT->DR = '\n';
     lineStart = 4;
     break;

   case 4:
     DBGPORT->DR = '\r';
     lineStart = 0;
     break;
   }
  }
  else
  {
   __disable_irq();
   if (charCount > 0)
   {
    --charCount;
     __enable_irq();
    char ch = charBuf[charEmp];
    DBGPORT->DR = ch;
    if (ch == '\r')
     eolFlag = 1;
    else
     eolFlag = 0;
    charEmp++;
    if (charEmp >= CHAR_BUF_SIZE)
     charEmp = 0;
   }
   else
   {
    lineStart = eolFlag;
    if (charFil != charEmp)
    {
     __enable_irq();
     dbgBuffer = 0;
     printf("**charOverflow %u charCount %d charFil %d charEmp %d\n",
	    charOverflow, charCount, charFil, charEmp);
     charEmp = 0;
     charFil = 0;
     charOverflow = 0;
     dbgBuffer = 1;
    }
    else
     __enable_irq();
   }
  }
  return(charCount);
 }
 return(-1);
}

void flushBuf(void)
{
 fflush(stdout);
 while (charCount != 0)
  pollBufChar();
}

/* debug message queue */

#if DBGMSG

#if DBGMSG == 2

void dbgmsg(char dbg, int32_t val)
{
 P_DBGMSG p;

 if (dbgcnt < MAXDBGMSG)	/* if buffer not full */
 {
  dbgcnt++;			/* update message count */
  p = &dbgdata[dbgfil];		/* get place to put msg */
  dbgfil++;			/* update fill pointer */
  if (dbgfil >= MAXDBGMSG)	/* if at end */
  {
   dbgfil = 0;			/* set to zero */
  }
  p->time = HAL_GetTick();	/* save time */
  p->dbg = dbg;			/* save message type */
  p->val = val;			/* save value */
 }
}

#else

void dbgmsg(char *str, int32_t val)
{
 P_DBGMSG p;

 if (dbgcnt < MAXDBGMSG)	/* if buffer not full */
 {
  dbgcnt++;			/* update message count */
  p = &dbgdata[dbgfil];		/* get place to put msg */
  dbgfil++;			/* update fill pointer */
  if (dbgfil >= MAXDBGMSG)	/* if at end */
  {
   dbgfil = 0;			/* set to zero */
  }
  p->time = HAL_GetTick();	/* save time */
  strncpy(p->str, str, sizeof(p->str)); /* save string */
  p->val = val;			/* save value */
 }
}

void dbgmsgx(char *str, char reg, int32_t val)
{
 P_DBGMSG p;

 if (dbgcnt < MAXDBGMSG)	/* if buffer not full */
 {
  dbgcnt++;			/* update message count */
  p = &dbgdata[dbgfil];		/* get place to put msg */
  dbgfil++;			/* update fill pointer */
  if (dbgfil >= MAXDBGMSG)	/* if at end */
  {
   dbgfil = 0;			/* set to zero */
  }
  char *d = p->str;
  int size = sizeof(p->str);
  while (--size >= 0)
   *d++ = *str++;
  *d++ = ' ';

  char tmp = reg;
  tmp >>= 4;
  tmp &= 0xf;
  if (tmp < 10)
   tmp += '0';
  else
   tmp += 'a' - 10;
  *d++ = tmp;

  reg &= 0xf;
  if (reg < 10)
   reg += '0';
  else
   reg += 'a' - 10;
  *d++ = reg;
  *d++ = 0;

  p->val = val;			/* save value */
 }
}

#endif

void clrDbgBuf(void)
{
 memset(&dbgdata, 0, sizeof(dbgdata));
 dbgcnt = 0;
 dbgfil = 0;
 dbgemp = 0;
}

#endif	/* DBGMSG */

/* printf output */

ssize_t _write(int fd  __attribute__((unused)), const char* buf, size_t nbyte)
{
 int count = (int) nbyte;

 if (dbgBuffer)
 {
  while (--count >= 0)
  {
   char ch = *buf++;
   putBufChar(ch);
   if (ch == '\n')
    putBufChar('\r');
  }
 }
 else
 {
  while (--count >= 0)
  {
   char ch = *buf++;
   putx(ch);
   if (ch == '\n')
    putx('\r');
  }
 }
 return(nbyte);
}

#define STDIN   0
#define STDOUT  1
#define STDERR  2
 
int __attribute__((__weak__, __section__(".libc")))
write (int handle, const char *buffer, int len)
{
 int i = len;
 switch (handle)
 {
 case STDOUT:
 case STDERR:
  if (dbgBuffer)
  {
   while (--i >= 0)
    putBufChar(*buffer++);
  }
  else
  {
   while (--i >= 0)
    putx(*buffer++);
  }
  break;
 }
 return (len);
}

#endif	/* INCLUDE */
