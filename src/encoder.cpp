#if !defined(INCLUDE)
#include "stm32f4xx_hal.h"

#include "lathe.h"

#include "lclcmd.h"
#if !defined(EXT)
#define EXT
#endif
#endif

#define ENCMAX (2540 * 8)
#define FCY 84000000

extern int16_t encState;		/* state of encoder */

void encInit(void);
void encStart(int tEna);
void encStop(void);

#if ENC_TEST

#if !defined(INCLUDE)

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
#if 0
 tmrInfo(TIM9);
#endif
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

void encTestTmrISR(void)
{
 encTestTmrClrIF();		/* clear interrupt */
 if (encRun)
 {
  if (encRunCount != 0)		/* if encoder counting */
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
#endif
#endif
