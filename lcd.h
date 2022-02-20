 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.h
 *
 * Description: header file for the lcd driver
 *
 * Author: Mohamed Emad El-Dien
 *
 *******************************************************************************/


#ifndef LCD_H_
#define LCD_H_

#include "std_types.h"



/*******************************************************************************
                                 Some Definitions
 *******************************************************************************/

#define LCD_DATA_PORT  PORTC_ID
#define LCD_SETUP_PORT PORTD_ID
#define LCD_RS         PIN4_ID
#define LCD_RW         PIN5_ID
#define LCD_ENABLE     PIN6_ID
#define LCD_CURSOR_OFF                 0x0C
#define LCD_CURSOR_ON                  0x0E
#define LCD_SET_CURSOR_LOCATION        0x80




/*******************************************************************************
                       Functions Prototypes
 *******************************************************************************/
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str);
void LCD_moveCursor(uint8 row,uint8 col);
void LCD_displayCharacter(uint8 output);
void LCD_displayString(uint8 *output);
void LCD_init();
void LCD_sendCommand(uint8 command);
void LCD_integerToString(int data);
void LCD_clearScreen();

#endif /* LCD_H_ */
