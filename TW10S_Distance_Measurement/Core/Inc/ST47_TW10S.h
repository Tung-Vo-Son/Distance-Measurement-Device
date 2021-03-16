/*
 * ST47_TW10S.h
 *
 *  Created on: Mar 13, 2021
 *      Author: Vo Son Tung HUST
 *      TW10S Laser Distance Measurement Library
 */

#ifndef INC_ST47_TW10S_H_
#define INC_ST47_TW10S_H_

#include "main.h"
#include "string.h"
#include "stdio.h"

typedef struct
{
	uint8_t status;
	uint8_t laser;
	uint8_t mode;
	uint8_t flags;
	uint8_t rx_data[1];
	uint8_t buffer[20];
	uint8_t count;
}TW10S_Struct;

typedef enum
{
	SINGLE_MODE,
	CONTINOUS_MODE,
	FAST_MODE
}TW10S_Mode;

void TW10S_deleteBuffer(char* buffer);
uint8_t TW10S_sendCommand(char* command, char* response, uint32_t timeout);
void stopMeasure(void);
void laserOn(void);
void laserOff(void);
void setOffset(uint8_t offset);
void setRange(uint16_t range);
void setBaudrate(uint32_t baudrate);
void setProtocol(uint8_t protocol);
void setFormat(uint8_t format);
void setSlaveAddress(uint8_t address);
void setFrequency(uint8_t frequency);
void setPower(uint8_t power);
void setMode(uint8_t mode);
float getDistance();


#endif /* INC_ST47_TW10S_H_ */
