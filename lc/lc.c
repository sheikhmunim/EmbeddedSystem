#include<avr/io.h>
#include<util/delay.h>
#define F_CPU = 8000000


#define LCD_DPORT PORTB
#define LCD_DDRB   DDRB
#define LCD_DPIN  PINB
#define LCD_CPORT PORTD
#define LCD_DDRD  DDRD
#define LCD_CPIN  PIND

#define LCD_RS    0
#define LCD_RW    1
#define LCD_EN     2

void lcdcommand( unsigned char cmd)
{
 LCD_DPORT = cmd;
 LCD_CPORT &= ~(1<<LCD_RS);
 LCD_CPORT &= ~(1<<LCD_RW);
 LCD_CPORT |= (1<<LCD_EN) ;
 _delay_us(1);
 LCD_CPORT &= ~(1<<LCD_EN) ;
 _delay_us(100);
 }
 
void lcddata(unsigned char data)
{
  LCD_DPORT = data;
  LCD_CPORT |= (1<<LCD_RS);
  LCD_CPORT &= ~(1<<LCD_RW);
  LCD_CPORT |= (1<<LCD_EN) ;
 _delay_us(1);
 LCD_CPORT &= ~(1<<LCD_EN) ;
 _delay_us(100);
 }
 
 
 void lcd_init()
 {
   LCD_DDRB = 0xFF;
   LCD_DDRD = 0xFF;
   
   LCD_CPORT &= ~(1<<LCD_EN);
   _delay_us(2000);
   lcdcommand(0x38);
   lcdcommand(0x0E);
   lcdcommand(0x01);
   _delay_us(2000);
   lcdcommand(0x06);
  }
  
  void lcd_gotoxy(unsigned char x,unsigned char y)
  {
    unsigned char firstcharAdr[] = { 0x80,0xC0,0x94,0xD4};
	lcdcommand(firstcharAdr[y-1] + x-1);
	_delay_us(100);
  }
  void lcd_print(char*str)
  {
  unsigned char i =0;
  while(str[i]!=0)
    { lcddata(str[i]);
	i++;
	}
  }

int main(void)
{
	lcd_init();
	lcd_gotoxy(1,1);
	lcd_print("hello Munim");
	lcd_gotoxy(1,2);
	lcd_print("Welcome to the future");
	while(1)
	return 0;
}
   