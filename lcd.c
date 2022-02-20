 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.c
 *
 * Description: source file for the lcd driver
 *
 * Author: Mohamed Emad El-Dien
 *
 *******************************************************************************/



#include "lcd.h"
#include "gpio.h"
#include <util/delay.h>



/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/* For initializing the LCD */
void LCD_init()
{
	GPIO_setupPinDirection(LCD_SETUP_PORT,LCD_RS,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_SETUP_PORT,LCD_RW,PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_SETUP_PORT,LCD_ENABLE,PIN_OUTPUT);
	GPIO_setupPortDirection(LCD_DATA_PORT,PORT_OUTPUT);
	LCD_sendCommand(0x38); // 2 lines and 8-bit mode LCD
	LCD_sendCommand(0x0c); // Disabling the cursor
	LCD_clearScreen();
}


/* For sending commands to the LCD */
void LCD_sendCommand(uint8 command)
{
	GPIO_writePin(LCD_SETUP_PORT,LCD_RS,LOGIC_LOW);
	GPIO_writePin(LCD_SETUP_PORT,LCD_RW,LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(LCD_SETUP_PORT,LCD_ENABLE,LOGIC_HIGH);
	_delay_ms(1);
	GPIO_writePort(LCD_DATA_PORT,command);
	_delay_ms(1);
	GPIO_writePin(LCD_SETUP_PORT,LCD_ENABLE,LOGIC_LOW);
	_delay_ms(1);
}


void LCD_displayCharacter(uint8 output)
{
	GPIO_writePin(LCD_SETUP_PORT,LCD_RS,LOGIC_HIGH);
	GPIO_writePin(LCD_SETUP_PORT,LCD_RW,LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(LCD_SETUP_PORT,LCD_ENABLE,LOGIC_HIGH);
	_delay_ms(1);
	GPIO_writePort(LCD_DATA_PORT,output);
	_delay_ms(1);
	GPIO_writePin(LCD_SETUP_PORT,LCD_ENABLE,LOGIC_LOW);
	_delay_ms(1);
}


void LCD_displayString(uint8 *output)
{
	uint8 *ptr=output;
	while(*ptr != '\0')
	{
		LCD_displayCharacter(*ptr);
		ptr++;
	}
}

/* For displaying a number on the LCD */
void LCD_integerToString(int data)
{
	char buff[16];
	itoa(data,buff,10);
	LCD_displayString(buff);
}

void LCD_clearScreen()
{
	LCD_sendCommand(0x01);
}


/* For moving the cursor of the LCD, so that we can display anything in any place on the LCD */
void LCD_moveCursor(uint8 row,uint8 col)
{
	uint8 lcd_memory_address;

	/* Calculate the required address in the LCD DDRAM */
	switch(row)
	{
		case 0:
			lcd_memory_address=col;
				break;
		case 1:
			lcd_memory_address=col+0x40;
				break;
		case 2:
			lcd_memory_address=col+0x10;
				break;
		case 3:
			lcd_memory_address=col+0x50;
				break;
	}
	/* Move the LCD cursor to this specific address */
	LCD_sendCommand(lcd_memory_address | LCD_SET_CURSOR_LOCATION);
}


/* For displaying a string in a specific place on the LCD */
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str)
{
	LCD_moveCursor(row,col); /* go to to the required LCD position */
	LCD_displayString(Str); /* display the string */
}
