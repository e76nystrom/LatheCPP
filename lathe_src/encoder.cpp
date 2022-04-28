//#if !defined(INCLUDE)
#define __ENCODER__
#ifdef STM32F4
#include "stm32f4xx_hal.h"
#endif
#ifdef STM32F7
#include "stm32f7xx_hal.h"
#endif
#ifdef STM32H7
#include "stm32h7xx_hal.h"
#endif

#include "lathe.h"
#include "lclcmd.h"
#include "stm32Info.h"

#ifdef EXT
#undef EXT
#endif

#define EXT
#include "encoder.h"
//#endif

#if defined(__ENCODER_INC__)	// <-

#define ENCMAX (2540 * 8)
#define FCY 84000000

extern int16_t encState;		/* state of encoder */

void encInit(void);
void encStart(int tEna);
void encStop(void);

#endif	// ->
#ifdef __ENCODER__

#if ENC_TEST

#if !defined(aSet)
#define aSet()
#endif
#if !defined(aClr)
#define aClr()
#endif

#if !defined(bSet)
#define bSet()
#endif
#if !defined(bClr)
#define bClr()
#endif

#if !defined(syncSet)
#define syncSet()
#endif
#if !defined(syncClr)
#define syncClr()
#endif


void encInit(void)
{
 rVar.encPerRev = ENCMAX;		/* set encoder maximum */
 rVar.encPreScaler = 0;		/* prescale 1 */
 rVar.encTimer = FCY / rVar.encPerRev;	/* timer for one sync per second */
}

void encStart(int tEna)
{
 aClr();			/* clear outputs */
 bClr();
 syncClr();

 encTestTmrStop();		/* disable timer */
 encTestTmrClrIF();		/* clear interrupt flag */
 encTestTmrCntClr();		/* clear counter register */
 if (rVar.encPreScaler != 0)		/* if prescaler non zero */
  encTestTmrScl(rVar.encPreScaler);	/* load prescaler */
 encTestTmrMax(rVar.encTimer);	/* set timer period */
 if constexpr (0)
  tmrInfo(ENCTEST_TMR);
 encState = 0;
 rVar.encCounter = 0;
 rVar.encRevCounter = 0;
 rVar.encRun = true;

 if (tEna)
 {
  encTestTmrSetIE();		/* enable interrupt */
  encTestTmrStart();   		/* turn timer on */
 }
}

void encStop(void)
{
 rVar.encRun = false;		/* clear run flag */
 encTestTmrClrIE();		/* disable interrupt */
 encTestTmrStop();		/* stop timer */
 encTestTmrClrIF();		/* clear interrupt flag */
}

extern "C" void encTestTmrISR(void)
{
 encTestTmrClrIF();		/* clear interrupt */

 if constexpr(ENC_TEST)
 {
  if (rVar.encRun)
  {
   if (rVar.encRunCount != 0)	/* if encoder counting */
   {
    if (--rVar.encRunCount == 0) /* if count is now zero */
    {
     encStop();			/* stop encoder */
    }
   }

   rVar.encCounter += 1;		/* update counter */
   if (rVar.encCounter >= rVar.encPerRev)	/* if at maximum */
   {
    rVar.encCounter = 0;		/* reset */
    rVar.encRevCounter += 1;		/* count a revolution */
    syncSet();			/* set the sync bit */
   }
   else				/* if not at maximum */
   {
    syncClr();			/* clear sync bit */
   }

   switch (encState)		/* select on state */
   {
   case 0:
    aSet();
    break;
   case 1:
    bSet();
    break;
   case 2:
    aClr();
    break;
   case 3:
    bClr();
    break;
   }
   encState += 1;		/* update state */
   encState &= 0x3;		/* mas in range */
  }
 }
}

#endif

#endif
