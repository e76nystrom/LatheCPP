#define __SERIALIO__

#ifdef STM32F4
#include "stm32f4xx_hal.h"
#endif
#ifdef STM32F7
#include <stm32f7xx_hal.h>
#endif
#ifdef STM32H7
#include "stm32h7xx_hal.h"
#endif

#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cstdarg>

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

#if defined(__SERIALIO_INC__)	// <-

#if !defined(EXT)
#define EXT extern
#endif

#define DBGMSG 2

enum RTN_VALUES
{
 NO_VAL,
 INT_VAL,
 FLOAT_VAL,
};

typedef union s_intFloat
{
 int i;
 float f;
} T_INT_FLOAT, *P_INT_FLOAT;

void newline();

#define MAXDIG 10		/* maximum input digits */

/* debug port routines */

int __attribute__((__weak__, __section__(".libc")))
write (int handle, const char *buffer, int len);

void putx(char c);
extern "C" void putstr(const char *p);
void sndhex(unsigned char *p, int size);
char getx();
unsigned char gethex();
char getstr(char *buf, int bufLen);
unsigned char getnum();
unsigned char getnumAll();
unsigned char getfloat();

unsigned char gethex(int *val);
unsigned char getnum(int *val);
unsigned char getnumAll(T_INT_FLOAT *val);
unsigned char getfloat(float *val);

char query(const char *format, ...);
char query(unsigned char (*get)(), const char *format, ...);
char query(unsigned char (*get)(int *), int *val, const char *format, ...);
char query(unsigned char (*get)(T_INT_FLOAT *), T_INT_FLOAT *val,
	   const char *format, ...);

void prtbuf(unsigned char *p, int size);
void prtibuf(int16_t *p, int size);

//#ifdef REMPORT

/* polled remote port routines */

void putx1(char c);
void putstr1(const char *p);

#if 0
void sndhex1(unsigned char *p, int size);
char gethex1();
char getx1();
char getstr1(char *buf, int bufLen);
unsigned char getnum1();
#endif

/* interrupt remote port routines */

void initRem();
void putRem(char ch);
void putstrRem(const char *p);
void sndhexRem(const unsigned char *p, int size);
int getRem();
char gethexRem(int *val);
char getstrRem(char *buf, int bufLen);
unsigned char getnumRem(T_INT_FLOAT *val);

//#endif

/* debug message routines */

#if DBGMSG
void dbgmsg(char dbg, int val);
void clrDbgBuf();
#else
#define dbgmsg(a, b)
#define dbgmsgx(a, b, c)
#endif	/* DBGMSG */

/* debug port buffered character routines */

extern "C" void remoteISR();

void initCharBuf();
void putBufChar(char ch);
void putBufCharIsr(char ch);
void putBufCharX(char ch);
void putBufStr(const char *s);
void putBufStrX(const char *s);
void sndhexIsr(unsigned char *p, int size);
void putBufStrIsr(const char *s);
int pollBufChar();
void flushBuf();

/* printf output */

extern "C" ssize_t _write (int fd  __attribute__((unused)),
			   const char* buf, size_t nbyte);

typedef struct s_serVar
{
 char dbgBuffer;

 char lineStart;
 char lineLen;
 char eolFlag;
 char remCmdRcv;

#if defined(MEGAPORT)
 char megaRspRcv;
#endif	/* MEGAPORT */
} T_SER_VAR, *P_SER_VAR;

EXT T_SER_VAR serial;

#if defined(MEGAPORT)

void initMega();
void putMega(char ch);
void putstrMega(const char *p);
void sndhexMega(const unsigned char *p, int size, unsigned char end);
int getMega();
char gethexMega(int *val);

#endif	/* MEGAPORT */

#if defined(STM32F4)

inline uint32_t dbgRxReady()
{
 return(DBGPORT->SR & USART_SR_RXNE);
}
inline uint32_t dbgRxRead()
{
 return(DBGPORT->DR);
}
inline uint32_t dbgRxOverrun()
{
 return(DBGPORT->SR & USART_SR_ORE);
}
inline uint32_t dbgTxEmpty()
{
 return(DBGPORT->SR & USART_SR_TXE);
}
inline void dbgTxSend(char ch)
{
 DBGPORT->DR = ch;
}
inline void dbgTxIntEna()
{
 DBGPORT->CR1 |= USART_CR1_TXEIE; /* enable transmit interrupt */
}
inline void dbgTxIntDis()
{
 DBGPORT->CR1 &= ~USART_CR1_TXEIE; /* disable transmit interrupt */
}

inline uint32_t remRxReady()
{
 return(REMPORT->SR & USART_SR_RXNE);
}
inline uint32_t remRxRead()
{
 return(REMPORT->DR);
}
inline void remRxIntEna()
{
 REMPORT->CR1 |= USART_CR1_RXNEIE;
}
inline uint32_t remRxOverrun()
{
 return(REMPORT->SR & USART_SR_ORE);
}
inline uint32_t remTxEmpty()
{
 return(REMPORT->SR & USART_SR_TXE);
}
inline void remTxSend(char ch)
{
 REMPORT->DR = ch;
}
inline void remTxIntEna()
{
 REMPORT->CR1 |= USART_CR1_TXEIE; /* enable transmit interrupt */
}
inline void remTxIntDis()
{
 REMPORT->CR1 &= ~USART_CR1_TXEIE; /* disable transmit interrupt */
}

#if defined(MEGAPORT)

inline uint32_t megaRxReady()
{
 return(MEGAPORT->SR & USART_SR_RXNE);
}
inline uint32_t megaRxRead()
{
 return(MEGAPORT->DR);
}
inline void megaRxIntEna()
{
 MEGAPORT->CR1 |= USART_CR1_RXNEIE;
}
inline uint32_t megaRxOverrun()
{
 return(MEGAPORT->SR & USART_SR_ORE);
}
inline uint32_t megaTxEmpty()
{
 return(MEGAPORT->SR & USART_SR_TXE);
}
inline void megaTxSend(char ch)
{
 MEGAPORT->DR = ch;
}
inline void megaTxIntEna()
{
 MEGAPORT->CR1 |= USART_CR1_TXEIE; /* enable transmit interrupt */
}
inline void megaTxIntDis()
{
 MEGAPORT->CR1 &= ~USART_CR1_TXEIE; /* disable transmit interrupt */
}

#endif	/* MEGAPORT */

#endif	/* STM32F4 */

#if defined(STM32F7)

inline uint32_t dbgRxReady()
{
 return(DBGPORT->ISR & USART_ISR_RXNE);
}
inline uint32_t dbgRxRead()
{
 return(DBGPORT->RDR);
}
inline uint32_t dbgRxOverrun()
{
 return(DBGPORT->ISR & USART_ISR_ORE);
}
inline uint32_t dbgTxEmpty()
{
 return(DBGPORT->ISR & USART_ISR_TXE);
}
inline void dbgTxSend(char ch)
{
 DBGPORT->TDR = ch;
}
inline void dbgTxIntEna()
{
 DBGPORT->CR1 |= USART_CR1_TXEIE; /* enable transmit interrupt */
}
inline void dbgTxIntDis()
{
 DBGPORT->CR1 &= ~USART_CR1_TXEIE; /* disable transmit interrupt */
}

inline uint32_t remRxReady()
{
 return(REMPORT->ISR & USART_ISR_RXNE);
}
inline uint32_t remRxRead()
{
 return(REMPORT->RDR);
}
inline void remRxIntEna()
{
 REMPORT->CR1 |= USART_CR1_RXNEIE;
}
inline uint32_t remRxOverrun()
{
 return(REMPORT->ISR & USART_ISR_ORE);
}
inline uint32_t remTxEmpty()
{
 return(REMPORT->ISR & USART_ISR_TXE);
}
inline void remTxSend(char ch)
{
 REMPORT->TDR = ch;
}
inline void remTxIntEna()
{
 REMPORT->CR1 |= USART_CR1_TXEIE; /* enable transmit interrupt */
}
inline void remTxIntDis()
{
 REMPORT->CR1 &= ~USART_CR1_TXEIE; /* disable transmit interrupt */
}

#if defined(MEGAPORT)

inline uint32_t megaRxReady()
{
 return(MEGAPORT->ISR & USART_ISR_RXNE);
}
inline uint32_t megaRxRead()
{
 return(MEGAPORT->RDR);
}
inline void megaRxIntEna()
{
 MEGAPORT->CR1 |= USART_CR1_RXNEIE;
}
inline uint32_t megaRxOverrun()
{
 return(MEGAPORT->ISR & USART_ISR_ORE);
}
inline uint32_t megaTxEmpty()
{
 return(MEGAPORT->ISR & USART_ISR_TXE);
}
inline void megaTxSend(char ch)
{
 MEGAPORT->TDR = ch;
}
inline void megaTxIntEna()
{
 MEGAPORT->CR1 |= USART_CR1_TXEIE; /* enable transmit interrupt */
}
inline void megaTxIntDis()
{
 MEGAPORT->CR1 &= ~USART_CR1_TXEIE; /* disable transmit interrupt */
}

#endif	/* MEGAPORT */

#endif	/* STM32F7 */

#if defined(STM32H7)

inline uint32_t dbgRxReady()
{
 return(DBGPORT->ISR & USART_ISR_RXNE_RXFNE);
}
inline uint32_t dbgRxRead()
{
 return(DBGPORT->RDR);
}
inline uint32_t dbgRxOverrun()
{
 return(DBGPORT->ISR & USART_ISR_ORE);
}
inline uint32_t dbgTxEmpty()
{
 return(DBGPORT->ISR & USART_ISR_TXE_TXFNF);
}
inline void dbgTxSend(char ch)
{
 DBGPORT->TDR = ch;
}
inline void dbgTxIntEna()
{
 DBGPORT->CR1 |= USART_CR1_TXEIE; /* enable transmit interrupt */
}
inline void dbgTxIntDis()
{
 DBGPORT->CR1 &= ~USART_CR1_TXEIE; /* disable transmit interrupt */
}

inline uint32_t remRxReady()
{
 return(REMPORT->ISR & USART_ISR_RXNE_RXFNE);
}
inline uint32_t remRxRead()
{
 return(REMPORT->RDR);
}
inline void remRxIntEna()
{
 REMPORT->CR1 |= USART_CR1_RXNEIE;
}
inline uint32_t remRxOverrun()
{
 return(REMPORT->ISR & USART_ISR_ORE);
}
inline void remClrRxOverrun()
{
 REMPORT->ICR = USART_ICR_ORECF;
}
inline uint32_t remTxEmpty()
{
 return(REMPORT->ISR & USART_ISR_TXE_TXFNF);
}
inline void remTxSend(char ch)
{
 REMPORT->TDR = ch;
}
inline void remTxIntEna()
{
 REMPORT->CR1 |= USART_CR1_TXEIE; /* enable transmit interrupt */
}
inline void remTxIntDis()
{
 REMPORT->CR1 &= ~USART_CR1_TXEIE; /* disable transmit interrupt */
}

#if defined(MEGAPORT)

inline uint32_t megaRxReady()
{
 return(MEGAPORT->ISR & USART_ISR_RXNE_RXFNE);
}
inline uint32_t megaRxRead()
{
 return(MEGAPORT->RDR);
}
inline void megaRxIntEna()
{
 MEGAPORT->CR1 |= USART_CR1_RXNEIE;
}
inline uint32_t megaRxOverrun()
{
 return(MEGAPORT->ISR & USART_ISR_ORE);
}
inline uint32_t megaTxEmpty()
{
 return(MEGAPORT->ISR & USART_ISR_TXE_TXFNF);
}
inline void megaTxSend(char ch)
{
 MEGAPORT->TDR = ch;
}
inline void megaTxIntEna()
{
 MEGAPORT->CR1 |= USART_CR1_TXEIE; /* enable transmit interrupt */
}
inline void megaTxIntDis()
{
 MEGAPORT->CR1 &= ~USART_CR1_TXEIE; /* disable transmit interrupt */
}

#endif	/* MEGAPORT */

#endif	/* STM32H7 */

// #define SNDHEX(val) sndhex((unsigned char *) &val, sizeof(val))

#if DBGMSG

#define MAXDBGMSG 200

typedef struct
{
 char dbg;
 int32_t val;
 uint32_t time;
} T_DBGMSG, *P_DBGMSG;

typedef struct s_dbgQue
{
 int16_t count;
 uint16_t fil;
 uint16_t emp;
 T_DBGMSG data[MAXDBGMSG];
} T_DBG_QUE, *P_DBG_QUE;

EXT T_DBG_QUE dbgQue;

#endif	/* DBGMSG */

/* remote port interrupt driven routines */

#define REM_TX_SIZE 140
#define REM_RX_SIZE 80

typedef struct
{
 int tx_fil;
 int tx_emp;
 int tx_count;
 char tx_buffer[REM_TX_SIZE];
 int rx_fil;
 int rx_emp;
 int rx_count;
 char rx_buffer[REM_RX_SIZE];
 int state;
} T_REMCTL, *P_REMCTL;

EXT T_REMCTL remCtl;

#if defined(MEGAPORT)

#define MEGA_TX_SIZE 40
#define MEGA_RX_SIZE 40

enum MEGA_STATE
{
 MEGA_ST_IDLE,
 MEGA_ST_START,
 MEGA_ST_DATA,
};

typedef struct
{
 int tx_fil;
 int tx_emp;
 int tx_count;
 char tx_buffer[MEGA_TX_SIZE];
 int rx_fil;
 int rx_emp;
 int rx_count;
 char rx_buffer[MEGA_RX_SIZE];
 int state;
 int txWait;
 uint32_t timer;
} T_MEGACTL, *P_MEGACTL;

EXT T_MEGACTL megaCtl;

#endif	/* MEGAPORT */

#endif	// ->
#ifdef __SERIALIO__

void wdUpdate();
unsigned int millis();

/* polled debug port routines */

void newline()
{
 if (serial.dbgBuffer)
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
 while (dbgTxEmpty() == 0)
  ;
 dbgTxSend(c);
}

void putstr(const char *p)
{
 while (true)
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
  dbgTxSend(ch);

  tmp &= 0xf;
  if (tmp < 10)
   tmp += '0';
  else
   tmp += 'a' - 10;
//  while (utxbf1);
//  u1txreg = tmp;
  dbgTxSend(tmp);
 }
}

char getx()
{
 while (dbgRxReady() == 0)
 {
  pollBufChar();
 }
 return(dbgRxRead());
}

unsigned char gethex(int *val)
{
 char ch;
 int count;

 int tmpVal = 0;
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
    tmpVal >>= 4;
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
  tmpVal <<= 4;
  tmpVal += ch;
 }
 *val = tmpVal;
 return(count != 0);
}

char getstr(char *buf,  int bufLen)
{
 int len = 0;
 char *p;
 char ch;
 p = buf;
 while (true)
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

unsigned char getnum(int *val)
{
 char ch;			/* input character */
 char chbuf[MAXDIG];		/* input digit buffer */
 unsigned char chidx;		/* input character index */
 unsigned char count;		/* input character count */
 char neg;			/* negative flag */
 char hex;			/* hex flag */

 neg = 0;
 hex = 0;
 int tmpVal = 0;
 chidx = 0;
 count = 0;
 while (true)
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
     tmpVal = (tmpVal << 4) + chbuf[count];
     count++;
    }
   }
   else
   {
    while (count < chidx)
    {
     tmpVal = tmpVal * 10 + chbuf[count];
     count++;
    }
   }
   if (neg)
    tmpVal = -tmpVal;
   *val = tmpVal;
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

unsigned char getfloat(float *val)
{
 char chbuf[MAXDIG];		/* input digit buffer */

 char len = getstr(chbuf, sizeof(chbuf));
 if (len != 0)
 {
  *val = strtof((const char *) chbuf, nullptr);
  return(1);
 }
 return(0);
}

unsigned char getnumAll(T_INT_FLOAT *val)
{
 char chbuf[MAXDIG];		/* input digit buffer */

 char len = getstr(chbuf, sizeof(chbuf));
 if (len != 0)
 {
  char *p = chbuf;
  int i;
  for (i = 0; i < len; i++)
  {
   char ch = *p++;
   if (ch == '.')
   {
    val->f = strtof((const char *) chbuf, nullptr);
    return(FLOAT_VAL);
   }
   if ((ch == 'x') || (ch == 'X'))
   {
    val->i = strtol(p, nullptr, 16);
    return(INT_VAL);
   }
  }
  val->i = strtol((const char *) chbuf, nullptr, 10);
  return(INT_VAL);
 }
 return(NO_VAL);
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

char query(unsigned char (*get)(int *), int *val, const char *format, ...)
{
 va_list args;
 va_start(args, format);
 vprintf(format, args);
 va_end(args);
 flushBuf();
 char ch = get(val);
 newline();
 return(ch);
}

char query(unsigned char (*get)(T_INT_FLOAT *), T_INT_FLOAT *val,
	   const char *format, ...)
{
 va_list args;
 va_start(args, format);
 vprintf(format, args);
 va_end(args);
 flushBuf();
 char ch = get(val);
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

#if defined(REMPORT)

/* polled remote port routines */

void putx1(char c)
{
 while (remTxEmpty() == 0)
  ;
 remTxSend(c);
}

void putstr1(const char *p)
{
 while (true)
 {
  char ch = *p++;
  if (ch == 0)
   break;
  putx1(ch);
  if (ch == '\n')
   putx1('\r');
 }
}

#if 0
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

char getx1()
{
 while (remRxReady() == 0)
  pollBufChar();
 return(remRxRead());
}

char getstr1(char *buf, int bufLen)
{
 int len = 0;
 char *p;
 char ch;
 p = buf;
 while (true)
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

char gethex1(int *val)
{
 char ch;
 int count;

 int tmpVal = 0;
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
    tmpVal >>= 4;
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
  tmpVal <<= 4;
  tmpVal += ch;
 }
 *val = tmpVal;
 return(count != 0);
}

unsigned char getnum1(T_INT_FLOAT *val)
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
    val->f = strtof((const char *) chbuf, 0);
    return(FLOAT_VAL);
   }
   if ((ch == 'x') || (ch == 'X'))
   {
    val->i = strtol(p, nullptr, 16);
    return(INT_VAL);
   }
  }
  val->i = atoi(chbuf);
  return(INT_VAL);
 }
 return(NO_VAL);
}
#endif

void initRem()
{
 memset(&remCtl, 0, sizeof(remCtl));
 remRxIntEna();
}

extern "C" void remoteISR()
{
 P_REMCTL u = &remCtl;
 if (remRxReady())		/* if received character */
 {
  char ch = remRxRead();	/* read character */
  if (u->state == 0)		/* if waiting for start */
  {
   if (ch == 1)			/* if start of message received */
   {
    u->state = 1;		/* set to start receiving */
   }
  }
  else				/* if receiving data */
  {
   if (u->rx_count < REM_RX_SIZE) /* if room in buffer */
   {
    int fill = u->rx_fil;	/* temp copy of fill pointer */
    u->rx_buffer[fill++] = ch;	/* put character in buffer */
    if (fill >= REM_RX_SIZE)	/* if past end of buffer */
     fill = 0;			/* reset to zero */
    u->rx_fil = fill;		/* save fill pointer */
    u->rx_count++;		/* update count */

    if (ch == '\r')		/* if end of command */
    {
     u->state = 0;		/* set to waiting for start */
#if 1
     NVIC_ClearPendingIRQ(REMOTE_IRQn); /* clear pending interrupt */
     remcmd();			/* process remote command */
#else
     serial.remCmdRcv = 1;
#endif
    }
   }
  }
 }

 if (remRxOverrun())		/* if overrun error */
 {
#if defined(STM32F4)
  if (remRxRead())		/* read character */
  {
  }
#endif /* STM32F4 */
#if defined(STM32H7)
  remClrRxOverrun();
#endif /* STM32H7 */
 }

 if (remTxEmpty())		/* if transmit empty */
 {
  if (u->tx_count != 0)		/* if anything in buffer */
  {
   int emp = u->tx_emp;		/* temp copy of empty pointer */
   remTxSend(u->tx_buffer[emp++]); /* send character */
   if (emp >= REM_TX_SIZE)	/* if at buffer end */
    emp = 0;			/* reset to start */
   u->tx_emp = emp;		/* save empty pointer */
   --u->tx_count;		/* count it off */
  }
  else				/* if nothing to send */
   remTxIntDis();		/* disable transmit interrupt */
 }
}

void putRem(char ch)
{
 P_REMCTL u = &remCtl;
 if (u->tx_count < REM_TX_SIZE) /* if room for data */
 {
  int fill = u->tx_fil;		/* temp copy of fill pointer */
  u->tx_buffer[fill++] = ch;	/* put character in buffer */
  if (fill >= REM_TX_SIZE)	/* if past end of buffer */
   fill = 0;			/* reset to zero */
  u->tx_fil = fill;		/* save fill pointer */

  __disable_irq();
  u->tx_count++;		/* update count */
  __enable_irq();
  remTxIntEna();		/* enable transmit interrupt */
 }
}

void putstrRem(const char *p)
{
 while (true)
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

int getRem()
{
 P_REMCTL u = &remCtl;
 if (u->rx_count != 0)		/* if anything in buffer */
 {
  int emp = u->rx_emp;		/* temp copy of empty pointer */
  unsigned char ch = u->rx_buffer[emp++]; /* send character */
  if (emp >= REM_RX_SIZE)	/* if at buffer end */
   emp = 0;			/* reset to start */
  u->rx_emp = emp;		/* save empty pointer */

  __disable_irq();
  --u->rx_count;		/* count it off */
  __enable_irq();
  return(ch);
 }
 return(-1);			/* nothing in buffer */
}

char gethexRem(int *val)
{
 char ch;
 int count;

 int tmpVal = 0;
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
   tmpVal <<= 4;
   tmpVal += ch;
  }
  else
   return(0);
 }
 *val = tmpVal;
 return(count != 0);
}

char getstrRem(char *buf, int bufLen)
{
 int len = 0;
 char *p;
 char ch;
 p = buf;
 while (true)
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

unsigned char getnumRem(T_INT_FLOAT *val)
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
    val->f = strtof((const char *) chbuf, nullptr);
    return(FLOAT_VAL);
   }
   if ((ch == 'x') || (ch == 'X'))
   {
    val->i = strtol(p, nullptr, 16);
    return(INT_VAL);
   }
  }
  val->i = strtol((const char *) chbuf, nullptr, 10);
  return(INT_VAL);
 }
 return(NO_VAL);
}

/* debug output buffer routines */

#define CHAR_BUF_SIZE 4096
typedef struct sCharBuf
{
 int fil;
 int emp;
 int count;
 unsigned int overflow;
 char buf[CHAR_BUF_SIZE];
} T_CHAR_BUF, *P_CHAR_BUF;

T_CHAR_BUF charBuf;

#define ISR_BUF_SIZE 1024
int isrFil;
int isrEmp;
int isrCount;
unsigned int isrOverflow;
char isrBuf[ISR_BUF_SIZE];

#endif	/* REMPORT */

#if defined(MEGAPORT)

void megaRsp();

void initMega()
{
 memset(&megaCtl, 0, sizeof(megaCtl));
 megaCtl.state = MEGA_ST_IDLE;
 megaRxIntEna();
}

extern "C" void megaISR()
{
 P_MEGACTL u = &megaCtl;
 if (megaRxReady())		/* if received character */
 {
  dbgMegaRxSet();
  char ch = megaRxRead();	/* read character */
  if (u->state == MEGA_ST_IDLE) /* if waiting for start */
  {
   if (ch == '-')		/* if start of message received */
   {
    putBufStrIsr("da");
    u->state = MEGA_ST_DATA;	/* set to start receiving */
   }
  }
  else if (u->state == MEGA_ST_DATA) /* if receiving data */
  {
   if (u->rx_count < MEGA_RX_SIZE) /* if room in buffer */
   {
    int fill = u->rx_fil;	/* temp copy of fill pointer */
    u->rx_buffer[fill++] = ch;	/* put character in buffer */
    if (fill >= MEGA_RX_SIZE)	/* if past end of buffer */
     fill = 0;			/* reset to zero */
    u->rx_fil = fill;		/* save fill pointer */
    u->rx_count++;		/* update count */

    if (ch == '*')		/* if end of command */
    {
     u->state = MEGA_ST_IDLE;	/* set to waiting for start */
#if 0     
     NVIC_ClearPendingIRQ(MEGA_IRQn); /* clear pending interrupt */
     megaRsp();			/* process mega command */
#else
     serial.megaRspRcv = 1;
#endif
    }
   }
  }
  dbgMegaRxClr();
 }

 if (megaRxOverrun())		/* if overrun error */
 {
  if (megaRxRead())		/* read character */
  {
  }
 }

 if (megaTxEmpty())		/* if transmit empty */
 {
  dbgMegaTxSet();
  if ((u->tx_count != 0)	/* if characters in buffer */
  &&  (u->txWait == 0))		/* and not waiting */
  {
   int emp = u->tx_emp;		/* temp copy of empty pointer */
   char ch = u->tx_buffer[emp++]; /* read character */
   megaTxSend(ch);		/* send character */
   if (emp >= MEGA_TX_SIZE)	/* if at buffer end */
    emp = 0;			/* reset to start */
   u->tx_emp = emp;		/* save empty pointer */
   --u->tx_count;		/* count it off */
   if (ch == '\r')		/* if end of message */
   {
    u->timer = millis();	/* set message timeout */
    if (u->tx_count != 0)	/* if more data */
    {
     putBufStrIsr("ws");
     u->txWait = true;		/* set transmit wait */
     dbgMegaWaitSet();
    }
   }
  }
  else				/* if nothing to send */
   megaTxIntDis();		/* disable transmit interrupt */
  dbgMegaTxClr();
 }
}

void putMega(char ch)
{
 P_MEGACTL u = &megaCtl;
 if (u->tx_count < MEGA_TX_SIZE) /* if room for data */
 {
  int fill = u->tx_fil;		/* temp copy of fill pointer */
  u->tx_buffer[fill++] = ch;	/* put character in buffer */
  if (fill >= MEGA_TX_SIZE)	/* if past end of buffer */
   fill = 0;			/* reset to zero */
  u->tx_fil = fill;		/* save fill pointer */

  __disable_irq();
  u->tx_count++;		/* update count */
  if (!u->txWait)		/* if not waiting */
   megaTxIntEna();		/* enable transmit interrupt */
  __enable_irq();
 }
}

void putstrMega(const char *p)
{
 while (true)
 {
  char ch = *p++;
  if (ch == 0)
   break;
  putMega(ch);
  if (ch == '\n')
   putMega('\r');
 }
}

void sndhexMega(const unsigned char *p, int size, unsigned char end)
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
   putMega(ch);
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
   putMega(tmp);
  }
 }
 if (zeros == 0)
  putMega('0');
 putMega(end);
}

int getMega()
{
 P_MEGACTL u = &megaCtl;
 if (u->rx_count != 0)		/* if anything in buffer */
 {
  int emp = u->rx_emp;		/* temp copy of empty pointer */
  unsigned char ch = u->rx_buffer[emp++]; /* send character */
  if (emp >= MEGA_RX_SIZE)	/* if at buffer end */
   emp = 0;			/* reset to start */
  u->rx_emp = emp;		/* save empty pointer */

  __disable_irq();
  --u->rx_count;		/* count it off */
  __enable_irq();
  return(ch);
 }
 return(-1);			/* nothing in buffer */
}

char gethexMega(int *val)
{
 char ch;
 int count;

 int tmpVal = 0;
 count = 0;
 while (count <= 8)
 {
  int tmp = getMega();
  if (tmp > 0)
  {
   ch = (char) tmp;
   if ((ch >= '0')
   &&  (ch <= '9'))
   {
    //putMega(ch);
    ch -= '0';
   }
   else if ((ch >= 'a')
   &&       (ch <= 'f'))
   {
    //putMega(ch);
    ch -= 'a' - 10;
   }
   else if ((ch == ' ') || (ch == '\r'))
    break;
//   else if (ch == ' ')
//   {
//    //putMega(ch);
//    break;
//   }
//   else if (ch == '\r')
//    break;
   else
    continue;

   count++;
   tmpVal <<= 4;
   tmpVal += ch;
  }
  else
   return(0);
 }
 *val = tmpVal;
 return(count != 0);
}

#endif	/* MEGAPORT */

void initCharBuf()
{
 serial.dbgBuffer = 1;
 charBuf.fil = 0;
 charBuf.emp = 0;
 charBuf.count = 0;
 charBuf.overflow = 0;
 serial.lineStart = 1;
 serial.lineLen = 0;
 serial.eolFlag = 1;

 isrFil = 0;
 isrEmp = 0;
 isrCount = 0;
 isrOverflow = 0;
}

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

void sndhexIsr(unsigned char *p, int size)
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
  putBufCharIsr(ch);

  tmp &= 0xf;
  if (tmp < 10)
   tmp += '0';
  else
   tmp += 'a' - 10;
  putBufCharIsr(tmp);
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
 if (charBuf.count < CHAR_BUF_SIZE)
 {
  charBuf.count++;
  __enable_irq();
  charBuf.buf[charBuf.fil] = ch;
  charBuf.fil++;
  if (charBuf.fil >= CHAR_BUF_SIZE)
   charBuf.fil = 0;
 }
 else
 {
  __enable_irq();
  charBuf.overflow++;
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

int pollBufChar()
{
 if (WD_ENA)
  IWDG->KR = 0xAAAA;		/* update hardware watchdog */

#if 0
 if (serial.remCmdRcv != 0)
 {
  remcmd();
  serial.remCmdRcv = 0;
 }
#endif

#if defined(MEGAPORT)
 if (serial.megaRspRcv != 0)
 {
  dbgMegaRspSet();
  megaRsp();
  serial.megaRspRcv = 0;
  dbgMegaRspClr();
 }
#endif	 /* MEGAPORT */

 if (rVar.setupDone)
  wdUpdate();

 if (dbgTxEmpty() != 0)
 {
  if (serial.lineStart)
  {
   switch (serial.lineStart)
   {
   case 1:
    if (isrCount != 0)
    {
     dbgTxSend('*');
     serial.lineStart = 2;
     serial.lineLen = 0;
    }
    else
     serial.lineStart = 0;
    break;

   case 2:
    if (isrCount > 0)
    {
     dbgTxSend(isrBuf[isrEmp]);
     isrEmp++;
     if (isrEmp >= ISR_BUF_SIZE)
      isrEmp = 0;
     __disable_irq();
     --isrCount;
     __enable_irq();
     serial.lineLen += 1;
     if (serial.lineLen >= 80)
     {
      serial.lineLen = 0;
      serial.lineStart = 3;
     }
    }
    else
     serial.lineStart = 3;
    break;

   case 3:
    dbgTxSend('\n');
     serial.lineStart = 4;
     break;

   case 4:
    dbgTxSend('\r');
     serial.lineStart = 1;
     break;
   }
  }
  else
  {
   __disable_irq();
   if (charBuf.count > 0)
   {
    --charBuf.count;
     __enable_irq();
    char ch = charBuf.buf[charBuf.emp];
    dbgTxSend(ch);
    if (ch == '\r')
     serial.eolFlag = 1;
    else
     serial.eolFlag = 0;
    charBuf.emp++;
    if (charBuf.emp >= CHAR_BUF_SIZE)
     charBuf.emp = 0;
   }
   else
   {
    serial.lineStart = serial.eolFlag;
    if (charBuf.fil != charBuf.emp)
    {
     __enable_irq();
     serial.dbgBuffer = 0;
     printf("**charOverflow %u charCount %d charFil %d charEmp %d\n",
	    charBuf.overflow, charBuf.count, charBuf.fil, charBuf.emp);
     charBuf.emp = 0;
     charBuf.fil = 0;
     charBuf.overflow = 0;
     serial.dbgBuffer = 1;
    }
    else
     __enable_irq();
   }
  }
  return(charBuf.count);
 }
 return(-1);
}

void flushBuf()
{
 fflush(stdout);
 while (charBuf.count != 0)
  pollBufChar();
}

/* debug message queue */

#if DBGMSG

void dbgmsg(char dbg, int val)
{
 P_DBGMSG p;

 if (dbgQue.count < MAXDBGMSG)	/* if buffer not full */
 {
  dbgQue.count++;		/* update message count */
  p = &dbgQue.data[dbgQue.fil];	/* get place to put msg */
  dbgQue.fil++;			/* update fill pointer */
  if (dbgQue.fil >= MAXDBGMSG)	/* if at end */
  {
   dbgQue.fil = 0;		/* set to zero */
  }
  p->time = HAL_GetTick();	/* save time */
  p->dbg = dbg;			/* save message type */
  p->val = val;			/* save value */
 }
}

void clrDbgBuf()
{
 memset(&dbgQue.data, 0, sizeof(dbgQue.data));
 dbgQue.count = 0;
 dbgQue.fil = 0;
 dbgQue.emp = 0;
}

#endif	/* DBGMSG */

/* printf output */

ssize_t _write(int fd  __attribute__((unused)), const char* buf, size_t nbyte)
{
 auto count = (ssize_t) nbyte;

 if (serial.dbgBuffer)
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
 return((ssize_t) nbyte);
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
  if (serial.dbgBuffer)
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

  default:
   break;
 }
 return (len);
}

#endif	/* __SERIALIO__ */
