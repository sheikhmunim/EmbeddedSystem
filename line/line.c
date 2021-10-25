#include<avr/io.h>
#include<avr/io.h>
#include<avr/interrupt.h>
#include<stdlib.h>
#include<util/delay.h>

//char adc_result[4];

int main(void)
{
    
	DDRB=0xff;           // setting the port B
    PORTB = 0b00000101;
    
	ADCSRA |= (1<<ADPS2); //| (1<<ADPS1)| (1<<ADPS0);
	ADMUX |= 1<<ADLAR;                             // setting for port D
	ADMUX |= 1<<REFS0; // INTERNAL REFERENCE VOLTAGE SELECTED
	 // PRESCALLER DEFINED
	//  LEFT SHIF REGISTER SELECTED FOR 8-BIT DATA
		ADCSRA |= 1<<ADIE;   // ADC INTERRUPTS ENABLE

	ADCSRA |= 1<<ADEN;  // ADC ENABLE
	//sei();
	
	sei();				// GLOBAL INTERUPTS ENABLE
	ADCSRA |= 1<<ADSC;  // ADC START CONVERTION
	
	
	while(1)
	{
	
	}

}

ISR(ADC_vect)
{   int thelow = ADCH;


	switch(ADMUX)
	{

	case 0x60:
		if(thelow>100)
			{ PORTB=0b00000010;	
			 }
		ADMUX = 0x61;
		break;
		
	
	case 0x61:
		if(thelow>100)
		{ PORTB=0b00001000;
		}
		ADMUX = 0x62;
		break;
		
	case 0x62:
	if(thelow>100)
	{ PORTB=0b00000100;
	}
	ADMUX = 0x60;
	
	break;
	
	default : 
			PORTB = 0x00;
			break;
		
}	
	
	
	
	
	
	ADCSRA |= 1<<ADSC;
}
