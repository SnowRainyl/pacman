/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <string.h>
#include "LPC17xx.h"
#include "timer.h"
#include "../GLCD/GLCD.h" 
#include "../TouchPanel/TouchPanel.h"
#include <stdio.h> /*for sprintf*/
#include "PAC_MAN.h"

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

static volatile uint32_t timer3_ticks = 0; 

void TIMER0_IRQHandler (void)
{
	
  LPC_TIM0->IR = 1;			/* clear interrupt flag */
  return;
}


/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER1_IRQHandler (void)
{
	
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}
void TIMER2_IRQHandler (void)
{
	if(last_second > 0) {
        last_second--;
        char str[20];
        sprintf(str, "%02d", last_second); 
        GUI_Text(8, 15, (uint8_t *)str, White, 0);
    } 
	else 
	{
        disable_timer(2);  
				LCD_Clear(Black);
        GUI_Text(88, 150, (uint8_t *)"Game Over!", Red, Black);
				disable_RIT();
    }
  LPC_TIM2->IR = 1;			/* clear interrupt flag */
  return;
}
void TIMER3_IRQHandler (void)
{
		
    LPC_TIM3->IR = 1;  

}

/******************************************************************************
**                            End Of File
******************************************************************************/
