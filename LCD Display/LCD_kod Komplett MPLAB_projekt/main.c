#include <p18f25k22.h>
#include <delays.h>
#include <stdlib.h>
#include "lcd.h"

//Configuration Bits---------------------------------------------------------
#pragma config FOSC=XT,HFOFST=OFF,PLLCFG=OFF,IESO=OFF,PRICLKEN=ON,WDTEN=OFF
#pragma config PWRTEN=ON,BOREN=OFF,MCLRE=EXTMCLR,LVP=OFF,DEBUG=OFF,STVREN=ON  

void init (void);

void main(void)
{	char ASCII_string[4];
	unsigned char character_code=0;
	
	init();	
	lcd_init();
	
	lcd_clear();
	lcd_goto(0);							// Select first line position 0
	lcd_writesc("Hello World");
	
	lcd_goto(0x0C);							// Select first line position 12		
	lcd_write('h');
	lcd_write('t');
	lcd_write('1');
	lcd_write('0'+3);
	
	while(1)
	{	itoa(character_code,ASCII_string);	// Integer To ASCII-string conversion
		lcd_goto(0x40);						// Select second line position 0
		lcd_writesc("   ");					// Clear position 0-2
		lcd_goto(0x40);						// Select second line position 0
		lcd_writesv(ASCII_string);			// Write character_code to LCD
		lcd_goto(0x45);						// Select second line position 5
		lcd_write(character_code);			// Write character to LCD
		character_code++;	
		Delay10KTCYx(50);					// Delay 0.5 s
	}
	
	while(1)
	{
		//LATAbits.LATA2 = 1;		//Enable
		//LATAbits.LATA2 = 0;		//disable
	
	
	}
}


void init(void)
{	
	ANSELA=0x00;
	ANSELB=0x00; 						//PortB digital
	TRISA=0x00;
	TRISB=0x00;						//PortB outputs	
}

