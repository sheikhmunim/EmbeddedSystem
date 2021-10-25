#include<avr/io.h>
#include<util/delay.h>
#include<util/delay.h>

int main(void)
{
//DDR data direction registor
DDRB=0b11111111;
DDRA=0b11111111;

while(1)
{
PORTB=0xff;
_delay_ms(2000);


PORTB=0x00;
_delay_ms(1000);

PORTA =0x00;
_delay_ms(2000);

PORTA=0xff;
_delay_ms(1000);



PORTB =0x00;
_delay_ms(1000);

PORTB=0xff;
_delay_ms(1000);


PORTA=0b11111111;
_delay_ms(1000);

PORTB =0x00;
_delay_ms(1000);

PORTB=0xff;
_delay_ms(1000);


PORTA=0b11111111;
_delay_ms(1000);

PORTB =0x00;
_delay_ms(1000);

PORTB=0xff;
_delay_ms(1000);


PORTA=0b11111111;
_delay_ms(1000);







}            //output is always 1 and input is always 0

}