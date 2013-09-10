//Headerfiler---------------------------------------------------------------- 
//Studera .h-filer: C:\Program Files\Microchip\mplabc18\v3.38\h\ 
#include <p18f25k22.h> //Definition av register och registerbitar 
#include <delays.h>

//Configuration Bits--------------------------------------------------------- 
//Se i MPLAB: Help>Topics>Language Tools>PIC18 Config Settings 
#pragma config FOSC=XT, FCMEN=OFF //Extern Oscillator, FailSafe disabled 
#pragma config HFOFST=OFF //Delay until fosc stable 
#pragma config PLLCFG=OFF, IESO=OFF //PLL Off, Osc switchover disabled 
#pragma config PRICLKEN=ON //Primary clock enabled 
#pragma config PWRTEN=ON, BOREN=OFF //Power-Up timer enabled, BOR off 
#pragma config MCLRE=EXTMCLR, XINST=OFF//MCLR extern, I-set extension disabled 
#pragma config WDTEN=OFF, LVP=OFF //Watchdog timer & Low Volt prog disabled 
#pragma config DEBUG=OFF, STVREN=ON //Stack Full/Underflow will cause Reset

//Definitioner av konstanter-------------------------------------------------
#define LOW 0

void init(void);

void main(void)
{
	//Variabler
	
	
	init();	//Kalla på initieringsfunktionen
	
	//Main-loop
	while(1)
	{
		LATAbits.LATA0 = 1;
		LATAbits.LATA1 = 0;
		Delay1KTCYx(128);
		
		LATAbits.LATA0 = 0;
		LATAbits.LATA1 = 1;
		Delay1KTCYx(128);
		
	}
}

void init()
{
	ANSELA = 0x00;	//PORTA digitala
	TRISA = 0x00;	//PORTA Utgångar
	LATA = 0x00;	//Nolla utgångar
}