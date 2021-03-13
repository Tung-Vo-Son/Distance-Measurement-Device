/*
 * ST47_TW10S.c
 *
 *  Created on: Mar 13, 2021
 *      Author: Vo Son Tung HUST
 *      TW10S Laser Distance Measurement Library
 */
#include "ST47_TW10S.h"

TW10S_Struct tw10s;
extern UART_HandleTypeDef huart1;

void TW10S_deleteBuffer(char* buffer)
{
	tw10s.count = 0;
	for(int i=0;i<strlen(buffer);i++)
	{
		buffer[i] = 0;
	}

}

uint8_t TW10S_sendCommand(char* command, char* response, uint32_t timeout)
{
	uint8_t result = 0;
	TW10S_deleteBuffer((char*)&tw10s.buffer);
	uint32_t time = HAL_GetTick();
	uint32_t time1 = HAL_GetTick();
	HAL_UART_Transmit(&huart1, (uint8_t*)command, strlen(command), 2000);
	HAL_UART_Transmit(&huart1,(uint8_t*)"\r\n",strlen("\r\n"),2000);
	while(result == 0)
	{
		while(HAL_UART_Receive(&huart1, tw10s.rx_data,1,1000) != HAL_OK)
		{
			if(HAL_GetTick() - time > timeout)
			{
				return 0;
			}
		}
		time = HAL_GetTick();
		tw10s.buffer[tw10s.count++] = tw10s.rx_data[0];
		while(HAL_GetTick() - time < timeout)
		{
			if(HAL_UART_Receive(&huart1, tw10s.rx_data, 1, 1000) == HAL_OK)
			{
				tw10s.buffer[tw10s.count++] = tw10s.rx_data[0];
				time1 = HAL_GetTick();
			}
			else
			{
				if(HAL_GetTick() - time1 > 100)
				{
					if(strstr((char*)tw10s.buffer,response) != NULL)
					{
						result = 1;
					}
					else
					{
						result = 0;
					}
					break;
				}
			}
		}
	}
	return result;
}

void stopMeasure()
{
	TW10S_sendCommand("iHALT", "STOP OK", 2000);
}

void laserOn()
{
	TW10S_sendCommand("iLD:1", "LASER OPEN", 2000);
}

void laserOff()
{
	TW10S_sendCommand("iLD:0", "LASER CLOSE", 2000);
}

void setOffset(uint8_t offset)
{
	char buff[20] = {0};
	sprintf(buff,"iSET:1,%d", offset);
	TW10S_sendCommand(buff, "OK", 2000);
}

void setRange(uint16_t range)
{
	char buff[20] = {0};
	sprintf(buff,"iSET:2,%d", range);
	TW10S_sendCommand(buff, "OK", 2000);
}

void setBaudrate(uint32_t baudrate)
{
	char buff[20] = {0};
	sprintf(buff,"iSET:3,%ld",baudrate);
	TW10S_sendCommand(buff, "OK", 2000);
}

void setProtocol(uint8_t protocol)
{
	char buff[20] = {0};
	sprintf(buff,"iSET:4,%d",protocol);
	TW10S_sendCommand(buff, "OK", 2000);
}
void setFormat(uint8_t format)
{
	char buff[20] = {0};
	sprintf(buff,"iSET:5,%d",format);
	TW10S_sendCommand(buff, "OK", 2000);
}
void setSlaveAddress(uint8_t address)
{
	char buff[20] = {0};
	sprintf(buff,"iSET:6,%d",address);
	TW10S_sendCommand(buff, "OK", 2000);
}
void setFrequency(uint8_t frequency)
{
	char buff[20] = {0};
	sprintf(buff,"iSET:7,%d",frequency);
	TW10S_sendCommand(buff, "OK", 2000);
}
void setPower(uint8_t power)
{
	char buff[20] = {0};
	sprintf(buff,"iSET:8,%d",power);
	TW10S_sendCommand(buff, "OK", 2000);
}
void setMeasure(uint8_t mode)
{
	TW10S_sendCommand("iSM", "OK", 5000);
}

float getDistance(uint8_t mode);


