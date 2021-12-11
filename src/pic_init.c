// pic_init unit for Micro C PRO
// David Fainitski for ATU-100 project
// PIC1938 Microchip



#include <xc.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "extratypes.h"
#include "preprocessor.h"

#include "pic_init.h"



void pic_init(void) {
	asm("CLRWDT");
	WDTCONbits.WDTPS4 = 0;
	WDTCONbits.WDTPS3 = 1;
	WDTCONbits.WDTPS2 = 0; // 1 sec WDT
	WDTCONbits.WDTPS1 = 1;
	WDTCONbits.WDTPS0 = 0;
	asm("CLRWDT");

	ANSELA = 0;
	ANSA0 = 1; // analog inputs
	ANSA1 = 1;
	ANSELB = 0; // all as digital

	C1ON = 0; // Disable comparators
	C2ON = 0;

	OSCCON = 0b01111000; // 16 MHz oscillator

	PORTA = 0;
	PORTB = 0;
	PORTC = 0;
	LATA = 0b01000000; // PORT6 /Tx_req to 1
	LATB = 0;
	LATC = 0;
	TRISA = 0b00000011;
	TRISB = 0b00000111;
	TRISC = 0b00000000; //
	//
	ADC_Init();
	//

#if 0
	ADCON1.B0 = 1; // ADC with the internal reference
	ADCON1.B1 = 1;
#else
	ADCON1bits.ADPREF0 = 1;
	ADCON1bits.ADPREF1 = 1;
#endif

	OPTION_REGbits.nWPUEN = 0;

	WPUBbits.WPUB0 = 1; // PORTB0 Pull-up resistor
	WPUBbits.WPUB1 = 1; // PORTB1 Pull-up resistor
	WPUBbits.WPUB2 = 1; // PORTB2 Pull-up resistor

	//interrupt setting
	GIE= 0;

}