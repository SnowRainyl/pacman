#include "button.h"
#include "LPC17xx.h"
#include "GLCD.h"
#include "PAC_MAN.h"
#include "timer/timer.h"
#include "system_LPC17xx.h" 
#include "RIT.h"

void EINT0_IRQHandler (void)	  	/* INT0														 */
{		
		static volatile uint32_t last_time = 0;
    for(int i=0;i<250;i++)
	{
		last_time++;
	};
		
    LPC_SC->EXTINT &= (1 << 0);
    gameState.isPaused = !gameState.isPaused;
    if(gameState.isPaused) {
        disable_timer(2);
				disable_RIT();
        GUI_Text(100, 133, (uint8_t *)"PAUSE", Red, Black);
    } else {
        enable_timer(2);
        enable_RIT();
        GUI_Text(100, 133, (uint8_t *)"     ", Black, Black);
    }
	
	
}


void EINT1_IRQHandler (void)	  	/* KEY1														 */
{
	NVIC_DisableIRQ(EINT1_IRQn);		/* disable Button interrupts			 */
	LPC_PINCON->PINSEL4    &= ~(1 << 22);     /* GPIO pin selection */
	LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt         */
}

void EINT2_IRQHandler (void)	  	/* KEY2														 */
{
	
  LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt         */    
}


