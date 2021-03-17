/** 
Edit by modify: Ngoc Hang 
**/

#include <ST47_LCD_I2C.h>
extern I2C_HandleTypeDef hi2c2;  // change your handler here accordingly



void LCD_sendCommand (char cmd)
{
  char data_u, data_l;
	uint8_t data_t[4];
	data_u = (cmd&0xf0);
	data_l = ((cmd<<4)&0xf0);
	data_t[0] = data_u|0x0C;  //en=1, rs=0
	data_t[1] = data_u|0x08;  //en=0, rs=0
	data_t[2] = data_l|0x0C;  //en=1, rs=0
	data_t[3] = data_l|0x08;  //en=0, rs=0
	HAL_I2C_Master_Transmit (&hi2c2, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}

void LCD_sendData (char data)
{
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (data&0xf0);
	data_l = ((data<<4)&0xf0);
	data_t[0] = data_u|0x0D;  //en=1, rs=0
	data_t[1] = data_u|0x09;  //en=0, rs=0
	data_t[2] = data_l|0x0D;  //en=1, rs=0
	data_t[3] = data_l|0x09;  //en=0, rs=0
	HAL_I2C_Master_Transmit (&hi2c2, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}

void LCD_init (void)
{
	LCD_sendCommand (0x33); /* set 4-bits interface */
	LCD_sendCommand (0x32);
	HAL_Delay(50);
	LCD_sendCommand (0x28); /* start to set LCD function */
	HAL_Delay(50);
	LCD_sendCommand (0x01); /* clear display */
	HAL_Delay(50);
	LCD_sendCommand (0x06); /* set entry mode */
	HAL_Delay(50);
	LCD_sendCommand (0x0c); /* set display to on */
	HAL_Delay(50);
	LCD_sendCommand (0x02); /* move cursor to home and set data address to 0 */
	HAL_Delay(50);
	LCD_sendCommand (0x80);
}

void LCD_print (char *str)
{
	while (*str) LCD_sendData (*str++);
}

void LCD_clearDisplay (void)
{
	LCD_sendCommand (0x01); //clear display
}

void LCD_setCursor (int row, int col)
{
	uint8_t pos_Addr;
	if(row == 1) 
	{
		pos_Addr = 0x80 + row - 1 + col;
	}
	else
	{
		pos_Addr = 0x80 | (0x40 + col);
	}
	LCD_sendCommand(pos_Addr);
}
