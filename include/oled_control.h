#ifndef OLED_CONTROL_H_
#define OLED_CONTROL_H_



#include <xc.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "extratypes.h"
#include "preprocessor.h"


// Software I2C connections

#define Soft_I2C_Scl			LATBbits.LATB6
#define Soft_I2C_Sda			LATBbits.LATB7
#define Soft_I2C_Scl_Direction	TRISBbits.TRISB6
#define Soft_I2C_Sda_Direction	TRISBbits.TRISB7



static char RS;
static char RW;
static char E;
static char LED;
static char nible;

static char led_addr;
static char led_type;
static char shift_line;

static char oled_shift;



void set_addressing(char, char);
void led_send(char);
void led_init(void);
void oled_init(void);
void send_command(char);
void set_addressing(char, char);
void led_wr_str(char, char, char*, char);
void oled_wr_str(char, char, char*, char);
void dysp_on(void);
void dysp_off(void);


void Soft_I2C_Init(void);
void Soft_I2C_Start(void);
void Soft_I2C_Write(uint8_t d);
void Soft_I2C_Stop(void);


#endif	/* !OLED_CONTROL_H_ */
