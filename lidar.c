#include <stdint.h>
#include <avr/io.h>
//#include <avr/interrupt.h>
#include <util/delay.h>
#include "IO_Macros.h"
#include "libTfLuna/tfluna.h"
#include "libTfLuna/tfluna_settings.h"
#include "libLCD/hd44780.h"
#include "libTWI/twi.h"

/* GLOBALS
 *
 */
// PROTOTYPE
void my_delay_ms(unsigned int delay);

int16_t tfAddr = TFL_DEF_ADR;
uint16_t tfFrame = TFL_DEF_FPS;

int16_t tfDist;
int16_t tfFlux;
int16_t tfTemp;

uint8_t tfCount = 0;


int main(void)
{
	LCD_Setup();

	uint8_t line;
	for (line = 0; line < 2; line++)
	{
		LCD_GotoXY(0, line);
		if (line == 0)
		{
			LCD_PrintString("ECE 387 line: ");
			LCD_PrintInteger(LCD_GetY());
		}
		else 
		{
			LCD_PrintString("LCD[");
			LCD_PrintInteger(LCD_GetY());
			LCD_PrintString("] working!!!");
		}
	}

	/* delay before start */
	my_delay_ms(1000);
	LCD_Clear();
	my_delay_ms(20);

	// (SDA, SCL)
	twi_init();
	flush();

	while (1)
	{
		if (getData(&tfDist, &tfFlux, &tfTemp, tfAddr))
		{
			LCD_Clear();
			LCD_GotoXY(0,0);
			LCD_PrintString("Distance =");
			LCD_GotoXY(0,1);
			LCD_PrintInteger(tfDist);
		}
		
		if (tfCount < 10) ++tfCount;
		else
		{
			tfCount = 0;
		}
		_delay_ms(100);
	}
}

/* 
 * Handles larger delays the _delay_ms can't do by itself (not sure how accurate)  
 * Note no DBC as this function is used in the DBC !!! 
 *
 * borrowed from : https://www.avrfreaks.net/forum/delayms-problem 
 * */
void my_delay_ms(unsigned int delay) 
{
	unsigned int i;

	for (i=0; i<(delay/10); i++) 
	{
		_delay_ms(10);
	}
	for (i=0; i<(delay % 10); i++) 
	{
		_delay_ms(1);
	}
}

