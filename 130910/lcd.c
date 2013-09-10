/*
 *	LCD interface for MPLAB C18 compiler
 *	
 *
 *	This code will interface to a standard LCD controller
 *	like the Hitachi HD44780. It uses it in 4 bit mode, delay mode, with
 *	the hardware connected as follows (the standard 14 pin 
 *	LCD connector is used).
 *	
 *	Default Settings:
 *	LCD D4-D7 data pins are connected to PORTB pins RB0-RB3 
 *	LCD EN pin is connected to PORTB pin RB4 
 *  LCD RS pin is connected to PORTB pin RB5  
 *	LCD_RW pin is connected to ground
 *  Fosc=4 MHz
 *	
 *	To use these routine:
 *  Include lcd.h in main source file
 *  Add lcd.c to project source files
 *  Choose LCD_EN, LCD_RS and LCD_Dx pins in the #defines below
 *  Adjust LCD_STROBE() if Fosc > 8MHz
 *  Adjust delay_50us() if Fosc <> 4MHz
 *  Set up the used port I/O to digital outputs (ANSEL, ADCON, TRIS).
 *	Call lcd_init(), then call other routines as required.
 *
 */
 
#include <delays.h>
#include "lcd.h"

#define LCD_D4 LATBbits.LATB4			//LCD Databit D4
#define LCD_D5 LATBbits.LATB5			//LCD Databit D5
#define LCD_D6 LATBbits.LATB6			//LCD Databit D6
#define LCD_D7 LATBbits.LATB7			//LCD Databit D7

#define LCD_EN LATBbits.LATB2			//LCD Enable
#define	LCD_RS LATBbits.LATB0			//LCD Register Select

#define	LCD_STROBE() {LCD_EN=1; LCD_EN=0;}												// Use when Fosc<=8 MHz. 
//#define LCD_STROBE() {LCD_EN=1;Nop(); LCD_EN=0;}										// Uncomment if 8MHz<Fosc<=16MHz
//#define LCD_STROBE() {LCD_EN=1;Nop();Nop();Nop(); LCD_EN=0;}							// Uncomment if 16MHz<Fosc<=32MHz 
//#define LCD_STROBE() {LCD_EN=1;Nop();Nop();Nop();Nop();Nop();Nop();Nop(); LCD_EN=0;}	// Uncomment if 32MHz<Fosc<=64MHz 			

#define delay_50us() Delay10TCYx(5)		//Delay by 50 us = 50 TCY at Fosc=4 MHz.



/*Delay 2ms */
void delay_2ms(void)
{	unsigned char cnt1;
	for (cnt1=0;cnt1<=34;cnt1++)
	delay_50us();
}


/*Delay 100ms */
void delay_100ms(void)
{	unsigned char cnt2;
	for (cnt2=0;cnt2<=49;cnt2++)
	delay_2ms();
}



/* Write a byte to the LCD in 4 bit mode */
void lcd_write(unsigned char c)
{	if(c & 0x80) LCD_D7=1; else LCD_D7=0;
	if(c & 0x40) LCD_D6=1; else LCD_D6=0;
	if(c & 0x20) LCD_D5=1; else LCD_D5=0;
	if(c & 0x10) LCD_D4=1; else LCD_D4=0;
	LCD_STROBE();
	if(c & 0x08) LCD_D7=1; else LCD_D7=0;
	if(c & 0x04) LCD_D6=1; else LCD_D6=0;
	if(c & 0x02) LCD_D5=1; else LCD_D5=0;
	if(c & 0x01) LCD_D4=1; else LCD_D4=0;
	LCD_STROBE();
	delay_50us();
}


/*Clear and home the LCD*/
void lcd_clear(void)
{	LCD_RS = 0;
	lcd_write(0x01);
	LCD_RS=1;
	delay_2ms();
}


/* Write a string constant to the LCD */
void lcd_writesc( rom const char * s)
{	while(*s != '\0')
		lcd_write(*s++);
}


/* Write a string variable to the LCD */
void lcd_writesv( char * s)
{	while(*s != '\0')
		lcd_write(*s++);
}


/* Go to the specified position*/
void lcd_goto(unsigned char pos)
{	LCD_RS = 0;
	lcd_write(0x80+pos);
	LCD_RS=1;
}


/* Write a command to the LCD*/
void lcd_cmd(unsigned char command)
{	LCD_RS = 0;
	lcd_write(command);
	LCD_RS=1;
}


/* Initialise the LCD - put into 4 bit mode */
void lcd_init(void)
{	LCD_RS = 0;	
	LCD_EN = 0;
	delay_100ms();			// Wait 100ms after power applied
	LCD_D4 = 1;		
	LCD_D5 = 1; 
	LCD_STROBE();	
	delay_2ms();			// Wait 6ms
	delay_2ms();
	delay_2ms();
	LCD_STROBE();	
	delay_2ms();
	LCD_STROBE();	
	delay_2ms();
	LCD_D4 = 0;				// Set 4 bit mode
	LCD_STROBE();	
	delay_50us();	
	lcd_cmd(0b00101000);	// Set interface length 4-bit, 2-line, 5x8 dots display
	lcd_cmd(0b00001100);	// Display On, Cursor OFF, Cursor Blink OFF
	lcd_cmd(0b00000110);	// Set entry Mode
	lcd_clear();			// Clear screen
}
