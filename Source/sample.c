/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            The GLCD application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-7
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             Paolo Bernardi
** Modified date:           03/01/2020
** Version:                 v2.0
** Descriptions:            basic program for LCD and Touch Panel teaching
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "LPC17xx.h"
#include "GLCD/GLCD.h" 
#include "TouchPanel/TouchPanel.h"
#include "timer/timer.h"
#include "PAC_MAN.h"
#include "joystick.h"
#include "RIT.h"
#include "button.h"

int last_second = 60; //count down initial value
#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif
//0-239,0-319

int main(void)
{
  SystemInit();  												/* System Initialization (i.e., PLL)  */
  LCD_Initialization();
	BUTTON_init();
  TP_Init();

	
	LCD_Clear(Black);
	
	GUI_Text(0, 0, (uint8_t *) " Game Over In", White, 0);
	GUI_Text(140, 0, (uint8_t *) "SCORE", White, 0);
	GUI_Text(8, 15, (uint8_t *) "60s", White, 0);
	GUI_Text(140, 15, (uint8_t *) "0", White, 0);
	//timer0  use to random power pills
	//timer1  use to random power pills
	//timer2  count down 60s
	init_timer(0, 0x4E2 );
	init_timer(1, 0x4E2 ); 
	init_timer(2, 0x393870); //150ms suitable for simulator 0x393870     0x23C3460==>suitable for landtiger board
	enable_timer(1);
	enable_timer(0);
	
	
	joystick_init();											/* Joystick Initialization            */
	init_RIT(0x6DDD0);										/* RIT Initialization 18 msec       	*/
	enable_RIT();													/* RIT enabled												*/
	
	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);			

	
	initGame(&gameState);
  drawMaze(&gameState);
  drawPacMan(&gameState);
	GUI_Text(78, 263, (uint8_t *) "remain lives", White, 0);
	updatelives(gameState.lives);
	enable_timer(2);
	if(gameState.isPaused)
		{
				disable_timer(2);
				disable_RIT();
        GUI_Text(100, 133, (uint8_t *)"PAUSE", Red, Black);
		}
  while (1)	
  {
		__ASM("wfi");
  }
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
