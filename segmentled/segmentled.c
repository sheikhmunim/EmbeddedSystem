#include<avr/io.h>
#include<util/delay.h>
int main(void)
{
int value[10] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x10,0x7F};
DDRA= 0xFF;
while(1)
{
   for(int i=0;i<10;i++)
   
     {
	 
	 PORTA = value[i];
	 _delay_ms(1000);
	 
	 }





}







}