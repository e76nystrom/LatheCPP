//#if !defined(INCLUDE)
#define __ENCODER__
#ifdef STM32F4
#include "stm32f4xx_hal.h"
#endif
#ifdef STM32F7
#include "stm32f7xx_hal.h"
#endif

#include "lathe.h"
#include "lclcmd.h"

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

void encInit(void)
{
 encPerRev = ENCMAX;		/* set encoder maximum */
 encPreScaler = 0;		/* prescale 1 */
 encTimer = FCY / encPerRev;	/* timer for one sync per second */
}

void encStart(int tEna)
{
 aClr();			/* clear outputs */
 bClr();
 syncClr();

 encTestTmrStop();		/* disable timer */
 encTestTmrClrIF();		/* clear interrupt flag */
 encTestTmrClr();		/* clear counter register */
 if (encPreScaler != 0)		/* if prescaler non zero */
  encTestTmrScl(encPreScaler);	/* load prescaler */
 encTestTmrMax(encTimer);	/* set timer period */
 if constexpr (0)
  tmrInfo(ENCTEST_TMR);
 encState = 0;
 encCounter = 0;
 encRevCounter = 0;
 encRun = true;

 if (tEna)
 {
  encTestTmrSetIE();		/* enable interrupt */
  encTestTmrStart();   		/* turn timer on */
 }
}

void encStop(void)
{
 encRun = false;		/* clear run flag */
 encTestTmrClrIE();		/* disable interrupt */
 encTestTmrStop();		/* stop timer */
 encTestTmrClrIF();		/* clear interrupt flag */
}

extern "C" void encTestTmrISR(void)
{
 encTestTmrClrIF();		/* clear interrupt */

 if constexpr(ENC_TEST)
 {
  if (encRun)
  {
   if (encRunCount != 0)	/* if encoder counting */
   {
    if (--encRunCount == 0)	/* if count is now zero */
    {
     encStop();			/* stop encoder */
    }
   }

   encCounter += 1;		/* update counter */
   if (encCounter >= encPerRev)	/* if at maximum */
   {
    encCounter = 0;		/* reset */
    encRevCounter += 1;		/* count a revolution */
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
