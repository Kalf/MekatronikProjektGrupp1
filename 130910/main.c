/* INCLUDED FILES */
#include <p18f25k22.h>
#include <delays.h>
#include <pwm.h>
#include <math.h>
#include "lcd.h"

/* DEFINES */
#define HIGH 1
#define LOW 0

/* COFIGURATION BITS */
#pragma config FOSC=XT, FCMEN=OFF //Extern Oscillator, FailSafe disabled 
#pragma config HFOFST=OFF //Delay until fosc stable 
#pragma config PLLCFG=OFF, IESO=OFF //PLL Off, Osc switchover disabled 
#pragma config PRICLKEN=ON //Primary clock enabled 
#pragma config PWRTEN=ON, BOREN=OFF //Power-Up timer enabled, BOR off 
#pragma config MCLRE=EXTMCLR, XINST=OFF//MCLR extern, I-set extension disabled 
#pragma config WDTEN=OFF, LVP=OFF //Watchdog timer & Low Volt prog disabled 
#pragma config DEBUG=OFF, STVREN=ON //Stack Full/Underflow will cause Reset

/* FUNCTION DECLARATION */
void init(void);

/* MAIN LOOP */

void main(void)
{
	/* LOCAL VARIABLES */
	
	/* MAIN PROGRAM */
	init();				//initiate system
	
	/* MAIN LOOP */
	while(1)
	{
		lcd_goto(0);	//Set LCD cursor to 0,0
		lcd_writesc("Welcome!");
	}
}

/* INIT FUNCTION */
void init(void)
{
	TRISB = 0;							//PortB as outputs
	ANSELB=0x00; 						//PortB digital
	lcd_init();							//Initiate LCD
}