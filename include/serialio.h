#if 1	// <-

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
