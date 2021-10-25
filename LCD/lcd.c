#include<avr/io.h>
#include<util/delay.h>
#include "LCD.h" // we can  do (#include "LCD.h") if the library function is not included or inbuilt.its basically for let the compailer know that this file is in main file itself.

int main()
{
InitLCD(); //

 while(1)
 {
 CursorPos(0,0);//to position the cursor of the LCD,first no. denotes the row and second one denotes the position from which it will start
SendString("hi ");
_delay_ms(1000);
CursorPos(0,0);//to position the cursor of the LCD,first no. denotes the row and second one denotes the position from which it will start
SendString("how are you ");
_delay_ms(1000);
CursorPos(0,1);//to position the cursor of the LCD,first no. denotes the row and second one denotes the position from which it will start
SendString("hope you are well ");
_delay_ms(1000);
CursorPos(0,0);//to position the cursor of the LCD,first no. denotes the row and second one denotes the position from which it will start
SendString("bye ");
_delay_ms(1000);
CursorPos(0,0);//to position the cursor of the LCD,first no. denotes the row and second one denotes the position from which it will start
SendString("welcome to future ");
_delay_ms(1000);
 }
}