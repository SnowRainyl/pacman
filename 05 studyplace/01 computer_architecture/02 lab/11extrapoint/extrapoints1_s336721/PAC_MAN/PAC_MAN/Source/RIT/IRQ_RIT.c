/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "LPC17xx.h"
#include "GLCD.h"
#include "PAC_MAN.h"
#include "RIT.h"
/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

volatile Direction g_nextDirection = DIR_NONE;
volatile int g_directionChanged = 0;

void RIT_IRQHandler (void)
{					
	static int up=0;
	static int joystic_down=0;
	static int left=0;
	static int right=0;
	static int position=0;	
	
	if((LPC_GPIO1->FIOPIN & (1<<29)) == 0){	
		/* Joytick UP pressed */
		up++;
		switch(up){
			case 1:
				g_nextDirection = DIR_UP;
				g_directionChanged = 1;
				updatePacMan(&gameState);
				break;
			case 60:	//3sec = 3000ms/50ms = 60
				NVIC_EnableIRQ(EINT1_IRQn);							 /* enable Button interrupts			*/
				LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 0 pin selection */
				break;
			default:
				break;
		}
	}
	
	else if((LPC_GPIO1->FIOPIN & (1<<28)) == 0)
	{
		//right
		right++;
		switch(right){
			case 1:
				g_nextDirection = DIR_RIGHT;
				g_directionChanged = 1;
				updatePacMan(&gameState);
				break;
			case 60:	//3sec = 3000ms/50ms = 60
				NVIC_EnableIRQ(EINT1_IRQn);							 /* enable Button interrupts			*/
				LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 0 pin selection */
				break;
			default:
				break;
		}
		
		
	}
	else if((LPC_GPIO1->FIOPIN & (1<<27)) == 0)
	{
		//left
		left++;
		switch(left){
			case 1:
				g_nextDirection = DIR_LEFT;
				g_directionChanged = 1;
				updatePacMan(&gameState);
				break;
			case 60:	//3sec = 3000ms/50ms = 60
				NVIC_EnableIRQ(EINT1_IRQn);							 /* enable Button interrupts			*/
				LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 0 pin selection */
				break;
			default:
				break;
		}
		
	}
	else if((LPC_GPIO1->FIOPIN & (1<<26)) == 0)
	{
		//down
		joystic_down ++;
		switch(joystic_down){
			case 1:
				g_nextDirection = DIR_DOWN;
				g_directionChanged = 1;
				updatePacMan(&gameState);
				break;
			case 500:	//3sec = 3000ms/50ms = 60
				NVIC_EnableIRQ(EINT1_IRQn);							 /* enable Button interrupts			*/
				LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 0 pin selection */
				break;
			default:
				break;
		}
	}
	else{
			up=0;
			joystic_down=0;
			right=0;
			left=0;
		
			NVIC_EnableIRQ(EINT1_IRQn);							 /* enable Button interrupts			*/
			LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 0 pin selection */
	}
	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
