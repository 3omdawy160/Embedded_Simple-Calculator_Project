/*********************************************************************
 * Name        : SimpleCalculator.c
 * Author      : Mohamed Emad El-Dien
 * Description : Testing a Simple Calculator with a LCD and a Keypad
 * Date        : 2/16/2022
 *
 *********************************************************************/


#include "keypad.h"
#include "gpio.h"
#include "lcd.h"
#include <util/delay.h>


/*******************************************************************************
                      Functions Prototypes(Private)
 *******************************************************************************/
static uint32 calculate(uint32 operand1,uint32 operand2,uint8 operator); // A static (private) function for calculating the result of two operands



/* As you can see, this Simple Calculator only works with two operands, and any of the two operands can consist of more than one digit */

int main(void)
{

	uint8 key;/* This variable is used to get the key pressed by the user from the Keypad */
	uint8 operator;/* This is the operator which the user entered */
	uint32 operand1=1,operand2=1; /* These are the two operands which we will do the mathematical operation on */
	uint32 value=0; /* This is the result value of the operation */
	uint8 op1=1,op2=0; /* These two variables are used to specify whether the user is entering the first operand or the second one */
	uint8 counter1=0,counter2=0; /* These two variables are used to calculate the operands value if any operand consists of more than one digit */

	LCD_init(); /* For initializing the LCD */

	for(;;)
	{

		key = KEYPAD_getPressedKey(); /* Getting the pressed key by the user */

		if((key > 9) || (key < 0)) /* In case the pressed key was an operation  */
		{
			if(key == 13) /* In case the pressed key was the reset key (ON/C) */
			{
				/* Therefore we want to clear the screen, move the cursor to the beginning of the LCD, clear both operands and also resetting the op1 and op2 */
				LCD_clearScreen();
				LCD_moveCursor(0,0);
				operand1=0;
				operand2=0;
				op1=1;
				op2=0;
			}
			else if(key == '=')
			{
				/* Here is when the user want to get the value of the operation he just entered, therefore we want to calculate it, display it on the LCD screen
				   under the entered operation, give a delay for 1 second, then we will clear the screen, reset both operands and also we will make op1=1
				   to start the calculation of the first operand of the upcoming operation */

				value = calculate(operand1,operand2,operator);
				LCD_moveCursor(1,0);
				LCD_integerToString(value);
				_delay_ms(1000);
				LCD_clearScreen();
				LCD_moveCursor(0,0);
				op1=1;
				op2=0;
				operand1=0;
				operand2=0;
			}
			else
			{
				/* Here we want to first start calculating the second operand because of course the first operand will be calculated as the user is entering
				   the operator, therefore we made op1=0 and op2=1, also we want to display the operator entered by the user */

				operator = key;
				op1=0;
				op2=1;
				LCD_displayCharacter(operator);
				_delay_ms(500);
			}
		}
		else /* In case the user entered a number, therefore this number will be one of the operands */
		{
			/* The upcoming equations are just math operations to be able to calculate both operands if any one of them is consisted of more than one digit */

			if(op1)
			{
				operand1 = operand1*counter1 + key;
				counter1 = 10;
			}
			else if(op2)
			{
				operand2 = operand2*counter2 + key;
				counter2 = 10;
			}
			LCD_integerToString(key); /* Just displaying the operands on the LCD screen */
			_delay_ms(500);
		}
	}
}



/*******************************************************************************
                       Functions Definitions
 *******************************************************************************/

static uint32 calculate(uint32 operand1,uint32 operand2,uint8 operator)
{
	uint32 value;

	switch(operator)
	{
	case '*':
		value = operand1 * operand2;
		break;
	case '%':
		value = operand1 / operand2;
		break;
	case '+':
		value = operand1 + operand2;
		break;
	case '-':
		value = operand1 - operand2;
		break;
	}
	return value;
}
