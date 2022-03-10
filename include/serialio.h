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
unsigned char gethex(void);
char getstr(char *buf, int bufLen);
unsigned char getnum(void);
unsigned char getnumAll(void);
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
#endif	/* DBGMSG == 2 */
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
void sndhexIsr(unsigned char *p, int size);
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
EXT char lineLen;
EXT char eolFlag;

#if defined(MEGAPORT)

void initMega(void);
void putMega(char ch);
void putstrMega(const char *p);
void sndhexMega(const unsigned char *p, int size);
int getMega(void);
char gethexMega(void);

EXT int32_t valMega;
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

#endif	/* DBGMSG == 2 */

EXT T_DBGMSG dbgdata[MAXDBGMSG];

EXT int16_t dbgcnt;
EXT uint16_t dbgfil;
EXT uint16_t dbgemp;

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
 uint32_t timer;
} T_MEGACTL, *P_MEGACTL;

EXT T_MEGACTL megaCtl;

#endif	/* MEGAPORT */

#endif	// ->
