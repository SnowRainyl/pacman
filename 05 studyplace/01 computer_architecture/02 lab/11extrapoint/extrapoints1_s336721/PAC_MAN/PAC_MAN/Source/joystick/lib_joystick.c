/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           joystick.h
** Last modified Date:  2018-12-30
** Last Version:        V1.00
** Descriptions:        Atomic joystick init functions
** Correlated files:    lib_joystick.c, funct_joystick.c
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#include "LPC17xx.h"
#include "joystick.h"

/*----------------------------------------------------------------------------
  Function that initializes joysticks and switch them off
 *----------------------------------------------------------------------------*/

void joystick_init(void) {
	/* joystick up functionality */
  LPC_PINCON->PINSEL3 &= ~(3<<26);	//PIN mode GPIO (00b value per P1.29)  29 is up (shematic)11==gpio
	LPC_GPIO1->FIODIR   &= ~(1<<29);	//P1.25 Input (joysticks on PORT1 defined as Input)  0 is input 
	
	//right 28
	LPC_PINCON->PINSEL3 &= ~(3<<25);	//PIN mode GPIO (00b value per P1.29)  29 is up (shematic)11==gpio
	LPC_GPIO1->FIODIR   &= ~(1<<28);	//P1.25 Input (joysticks on PORT1 defined as Input)  0 is input 
	
	//left 27
	LPC_PINCON->PINSEL3 &= ~(3<<24);	//PIN mode GPIO (00b value per P1.29)  29 is up (shematic)11==gpio
	LPC_GPIO1->FIODIR   &= ~(1<<27);	//P1.25 Input (joysticks on PORT1 defined as Input)  0 is input 
	
	//down 26
	LPC_PINCON->PINSEL3 &= ~(3<<23);	//PIN mode GPIO (00b value per P1.29)  29 is up (shematic)11==gpio
	LPC_GPIO1->FIODIR   &= ~(1<<26);	//P1.25 Input (joysticks on PORT1 defined as Input)  0 is input 
	
	
}
