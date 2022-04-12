#include "tfluna_settings.h"
#include "tfluna.h"
#include "IO_Macros.h"
#include "../libTWI/twi.h"

uint8_t transmitting = 0;

uint8_t txAddress = 0;
uint8_t txBuffer[TWI_BUFFER_LENGTH];
size_t txBufferIndex = 0;
size_t txBufferLength = 0;

uint8_t rxBuffer[TWI_BUFFER_LENGTH];
size_t rxBufferIndex = 0;
size_t rxBufferLength = 0;

uint8_t tfStatus;
uint8_t dataArray[ 6];
uint8_t regReply;


// PROTOTYPES

bool getData( int16_t * dist, int16_t * flux, int16_t * temp, uint8_t addr)
{
	tfStatus = TFL_READY;

	for (uint8_t reg = TFL_DIST_LO; reg <= TFL_TEMP_HI; reg++)
	{
		if ( !readReg( reg, addr)) return false;
		else dataArray[ reg] = regReply;
	}

	// Shift data to variables
	*dist = (dataArray[ 0] + ( dataArray[ 1] << 8));
	*flux = (dataArray[ 2] + ( dataArray[ 3] << 8));
	*temp = (dataArray[ 4] + ( dataArray[ 5] << 8));

	// Temp conversions
	// temp = int16_t( temp / 100);	// C
	// temp = uint8_t( temp * 9 / 5) + 32; // F
	
	if ( *flux < (int16_t)100)
	{
		tfStatus = TFL_WEAK;
		return false;
	}
	else if ( *flux == (int16_t)0xFFFF)
	{
		tfStatus = TFL_STRONG;
		return false;
	}
	else
	{
		tfStatus = TFL_READY;
		return true;
	}
}

//bool getData( int16_t * dist, uint8_t addr)
//{
//	static int16_t flux, temp;
//	return getData(&dist, &flux, &temp, addr);
//}

bool readReg( uint8_t nmbr, uint8_t addr)
{
	transmitting = 1;
	txAddress = addr;
	txBufferIndex = 0;
	txBufferLength = 0;

	if (transmitting)
	{
		txBuffer[txBufferIndex] = nmbr;
		++txBufferIndex;
		txBufferLength = txBufferIndex;
	}
	else 
	{
		twi_transmit(&nmbr, 1);
	}
	
	int8_t ret = twi_writeTo(txAddress, txBuffer, txBufferLength, 1, true);
	txBufferIndex = 0;
	txBufferLength = 0;
	transmitting = 0;

	if (ret != 0)
	{
		tfStatus = TFL_I2CWRITE;
		return false;
	}

	size_t size = 1;
	if (size > TWI_BUFFER_LENGTH)
	{
		size = TWI_BUFFER_LENGTH;
	}
	size_t read;
	if (twi_readFrom((int)addr, rxBuffer, size, true) == 0)
	{
		read = size;
	}
	else
	{
		read = 0;
	}
	rxBufferIndex = 0;
	rxBufferLength = read;

	int value = -1;
	if (rxBufferIndex < rxBufferLength)
	{
		value = rxBuffer[rxBufferIndex];
	}
	
	if (value == -1)
	{
		tfStatus = TFL_I2CREAD;
		return false;
	}

	value = -1;
	if (rxBufferIndex < rxBufferLength)
	{
		value = rxBuffer[rxBufferIndex];
		++rxBufferIndex;
	}
	regReply = (uint8_t)value;

	return true;
}

bool writeReg( uint8_t nmbr, uint8_t addr, uint8_t data)
{
	transmitting = 1;
	txAddress = addr;
	txBufferIndex = 0;
	txBufferLength = 0;

	if (transmitting)
	{
		txBuffer[txBufferIndex] = nmbr;
		++txBufferIndex;
		txBufferLength = txBufferIndex;
	}
	else
	{
		twi_transmit(&nmbr, 1);
	}
	
	if (transmitting)
	{
		txBuffer[txBufferIndex] = data;
		++txBufferIndex;
		txBufferLength = txBufferIndex;
	}
	else
	{
		twi_transmit(&data, 1);
	}

	int8_t ret = twi_writeTo(txAddress, txBuffer, txBufferLength, 1, true);
	txBufferIndex = 0;
	txBufferLength = 0;
	transmitting = 0;
	
	if (ret != 0)
	{
		tfStatus = TFL_I2CWRITE;
		return false;
	}
	else return true;
}

// PRINT STATUS
//void printStatus()
//{
//
//}

void flush(void)
{
	rxBufferIndex = 0;
	rxBufferLength = 0;
	txBufferIndex = 0;
	txBufferLength = 0;
}


