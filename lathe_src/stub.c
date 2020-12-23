#if defined(STM32F4)
#include "stm32f4xx_hal.h"
#endif
#if defined(STM32H7)
#include "stm32h7xx_hal.h"
#endif

#include <sys/types.h>

ssize_t _write (int fd, const char* buf, size_t nbyte);

void _init(void);
caddr_t _sbrk(int incr);
void _close(void);
int _fstat(void);
int _isatty(void);
void _lseek(void);
void _read(void);
void _kill(void);
void _getpid(void);

void _init(void)
{
}

caddr_t _sbrk(int incr)
{
 extern char _end;		/* Defined by the linker */
 static char *heap_end;
 char *prev_heap_end;
 char *sp = (char *)&sp;

 if (heap_end == 0)
 {
  heap_end = &_end;
 }
 prev_heap_end = heap_end;
 heap_end += incr;
 if (heap_end > sp)
 {
  _write (1, "Heap and stack collision\n", 25);
//  errno = ENOMEM;
  return (caddr_t)-1;
 }
 return (caddr_t) prev_heap_end;
}

void _close(void)
{
}

int _fstat(void)
{
 return(0);
}

int _isatty(void)
{
 return(1);
}

void _lseek(void)
{
}

void _read(void)
{
}

void _kill(void)
{
}

void _getpid(void)
{
}
