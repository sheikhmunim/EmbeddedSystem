//##########################################################################################
//	 LIBRARY FOR 1602A 16*2 LCD DISPLAY   Author:- Samiran Patra 	©RoboElements
//				For More Details On circuit visit www.roboelements.com/tutorials
//##########################################################################################
#ifndef LCD
#define LCD

#include<avr/io.h>
#include<stdlib.h>
#include<util/delay.h>

#define DDR_LCD					DDRB			//Set Data direction for LCD
#define LCD_PORT 				PORTB			//Set Port for Data Transfer in LCD
#define DDR_Control_PORT		DDRD			//Set Data direction for control of LCD
#define LCD_Control_PORT		PORTD			//Set Port for control of LCD
#define Enable 					2				//Set Pin for Enable Switch
#define RW 						1				//Set Pin for Read/Write Switch
#define RS 						0				//Set Pin for Resistor Switch

//##########################################################################################
//	End of Define Statements
//##########################################################################################

char ColumnPosition[2] = {0, 64};			//Array to store the position of columns
uint8_t attributes = 0b00001110;

void InitLCD(void);							//Function to initialize the LCD at the start of operation
void CursorPos(uint8_t x, uint8_t y);		//Function to Position Cursor at a particular location
void ClrScr(void);							//Function to clear the screen
void SendCmd(unsigned char cmd);			//Function to send a Command to the LCD
void SendChar(unsigned char character);		//Function to send a Character to the LCD
void SendString(char *str);					//Function to send a String to the LCD
void SendInteger(int value);				//Function to send Integer to the LCD
void SendDecimal(double value, int width, int precision);
	//Function to send Decimal Values to the LCD; 
	//width is the total no of characters to be displayed including negative signs
	//precison is the no. of digits after the decimal point 
void DisplayOnOff(uint8_t value);				//Function to turn LCD display On or Off
void CursorOnOff(uint8_t value);				//Function to turn Cursor in LCD On or Off
void CursorBlink(uint8_t value);				//Function to turn cursor blinking On or Off
void CheckBusy(void);						//Function to check if LCD is ready for receiving data
void FlashLCD(void);						//Function to flash the enable switch on and off

//############################################################################################
//	End of Prototyping
//############################################################################################


void CheckBusy()
{
	DDR_LCD= 0x00;							//Set Data Direction for LCD to Input
	LCD_Control_PORT|= 1<<RW;				//Set LCD to Read Mode; R/w pin High
	LCD_Control_PORT&= ~1<<RS;				//Set LCD to Read Commands; RS pin Low

	while (LCD_PORT >= 0x80)				//Condition Checking; if LCD sends back a value < 80 then it is busy
	{
		FlashLCD();
	}

	DDR_LCD= 0xFF; 							//Set Data Direction for LCD to Output, for further operations
}

void FlashLCD()
{
	LCD_Control_PORT|= 1<<Enable;			//Enable Pin High
	_delay_ms(5);
	LCD_Control_PORT&= ~1<<Enable;			//Enable Pin Low
}

void SendCmd(unsigned char cmd)
{
	CheckBusy();
	LCD_PORT = cmd;
	LCD_Control_PORT&= ~ ((1<<RW)|(1<<RS));	//write mode; command mode
	FlashLCD();
	LCD_PORT = 0x00;
}

void SendChar(unsigned char character)
{
	CheckBusy();
	LCD_PORT = character;
	LCD_Control_PORT&= ~ (1<<RW);
	LCD_Control_PORT|= 1<<RS;
	FlashLCD();
	LCD_PORT = 0x00;
}

void SendString(char *str)
{
	while(*str > 0)
	{
		SendChar(*str++);
	}
}

void SendInteger(int value)
{
	char ch[16];
	itoa(value,ch,10);
	SendString(ch);
}

void SendDecimal(double value, int width, int precision)
{
	char ch[16];
	dtostrf(value,width,precision,ch);
	SendString(ch);
}

void DisplayOnOff(uint8_t value)			
{
	CheckBusy();
	if(value==0)
	{
		attributes &= ~(1<<2);
		SendCmd(attributes);
	}
	else
	{
		attributes |= (1<<2);
		SendCmd(attributes);
	}
}

void CursorOnOff(uint8_t value)				
{
	CheckBusy();
	if(value==0)
	{
		attributes &= ~(1<<1);
		SendCmd(attributes);
	}
	else
	{
		attributes |= (1<<1);
		SendCmd(attributes);
	}
}

void CursorBlink(uint8_t value)	
{
	CheckBusy();
	if(value==0)
	{
		attributes &= ~(1<<0);
		SendCmd(attributes);
	}
	else
	{
		attributes |= (1<<0);
		SendCmd(attributes);
	}
}			

void CursorPos(uint8_t x, uint8_t y)
{
	SendCmd(0x80 + ColumnPosition[x] + (y));
}

void InitLCD()
{
	DDR_Control_PORT |= 1<<Enable | 1<<RW | 1<<RS;
	_delay_ms(50);

	SendCmd(0x01); 								//Clear Screen 0x01 = 00000001
	_delay_ms(2);
	SendCmd(0x38);								//Selecting 8- bit Mode
	_delay_us(50);
	SendCmd(0b00001110);						//Set attributes on 1st three bits: {Display-ON/OF, Cursor-ON/OFF, Cursor-Blink-ON/OFF}
	_delay_us(50);
}

void ClrScr(void)
{
	SendCmd(0x01);
	_delay_ms(2);
}

#endif