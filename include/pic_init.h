#ifndef PIC_INIT_H_
#define PIC_INIT_H_


#include <xc.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "extratypes.h"
#include "preprocessor.h"



// Connections

#define n_Tx		LATAbits.LATA6
#define p_Tx		LATAbits.LATA7

#if 0
#define Button		PORTBbits.RB0
#define BYP_button	PORTBbits.RB2
#define Auto_button	PORTBbits.RB1
#endif


#define Cap_10		LATCbits.LATC7
#define Cap_22		LATCbits.LATC3
#define Cap_47		LATCbits.LATC6
#define Cap_100		LATCbits.LATC2
#define Cap_220		LATCbits.LATC5
#define Cap_470		LATCbits.LATC1
#define Cap_1000	LATCbits.LATC4
#define Cap_sw		LATCbits.LATC0

#define Ind_005		LATBbits.LATB3
#define Ind_011		LATAbits.LATA2
#define Ind_022		LATBbits.LATB4
#define Ind_045		LATAbits.LATA3
#define Ind_1		LATBbits.LATB5
#define Ind_22		LATAbits.LATA5
#define Ind_45		LATAbits.LATA4



void pic_init(void);


#endif	/* !PIC_INIT_H_ */
