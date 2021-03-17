/** 
Edit by modify: Ngoc Hang 
**/

#include "stm32f1xx_hal.h"

#define SLAVE_ADDRESS_LCD 0x4E // change this according to ur setup

void LCD_init(void);					// Initialize LCD
void LCD_sendCommand(char command);		// Send command to LCD
void LCD_sendData(char data);			// Send data to LCD
void LCD_print(char* str);				// Send string to LCD
void LCD_clearDisplay(void);			// Clear display
void LCD_setCursor(int row, int col);	// Set cursor


