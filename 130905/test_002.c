//Headerfiler---------------------------------------------------------------- 
//Studera .h-filer: C:\Program Files\Microchip\mplabc18\v3.38\h\ 
#include <p18f25k22.h> //Definition av register och registerbitar 
#include <delays.h>
#include <timers.h>
#include <pwm.h>

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
	unsigned int duty_cycle;
	
	init();	//Kalla p� initieringsfunktionen
	
	//Main-loop
	while(1)
	{
		LATBbits.LATB0=LOW; //Bit0 PORTB=0 
		duty_cycle=0;
		while(duty_cycle <= 1023)
		{
			duty_cycle++;
		SetDCPWM5(duty_cycle);
 		Delay1KTCYx(64);
		}
		
	}
}

void init()
{
	ANSELA = 0x00;	//PORTA digitala
	ANSELB = 0x00;	//PORTB digitala
	TRISA = 0x00;	//PORTA Utg�ngar
	TRISB = 0x00;	//PORTB Utg�ngar
	LATA = 0x00;	//Nolla utg�ngar
	LATB = 0xFF;
	TRISAbits.RA4=0;	//CCP5pin = PWM utg�ng
	OpenTimer2(TIMER_INT_OFF & T2_PS_1_1 & T2_POST_1_1);	//Timer2= on, ingen interrupt, prescaler = 1 postscaler=1
	OpenPWM5(0xFF,CCP_5_SEL_TMR12);	//PWM-period=256us om 4MHz oscilator, anv�nd timer2 f�r pwm
}