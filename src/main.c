/**
 * \file main.c
 * \brief ATU-100 EXT firmware for PIC16F1938 main program
 *
 * \version		3.2.1
 * \author		Gerad Munsch <gmunsch@kd9qzo.com>
 * \date			December 2021
 * \author		David Fainitski
 * \date			2016
 */

#include <xc.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "extratypes.h"
#include "preprocessor.h"
#include "common.h"

#include "eeprom_map.h"
#include "oled_control.h"
#include "pic_init.h"
#include "main.h"



/* ================================================================================================================== *
 *   VARIABLES                                                                                                        *
 * ================================================================================================================= */

int SWR_fixed_old = 0;
int work_int;
unsigned char work_char;
unsigned char work_str[7];
unsigned char work_str_2[7];

float Forward;

int Power = 0;
int Power_old = 10000;
int SWR_old = 10000;

bit_byte_t ind;
bit_byte_t cap;

char type;
char Soft_tune = 0;
char Auto = 0;
char Track = 0;
char bypas = 0;
char cap_mem = 0;
char ind_mem = 0;
char SW_mem = 0;
char Auto_mem = 0;

int Auto_delta;

char Restart = 0;
char Test = 0;
char lcd_prep_short = 0;
char L = 1;
char but = 0;

int Cap1;
int Cap2;
int Cap3;
int Cap4;
int Cap5;
int Cap6;
int Cap7;

int Ind1;
int Ind2;
int Ind3;
int Ind4;
int Ind5;
int Ind6;
int Ind7;

char Dysp_delay = 0;
int dysp_cnt = 0;
float dysp_cnt_mult = 2.3;

char Loss_mode = 0;
char Fid_loss;

char dysp = 1;

bool tune_btn_release;



#if 0
void interrupt() {
}
#endif


void main() {
	if (STATUS.B4 == 0) {
		Restart = 1;
	}

	pic_init();

	Delay_ms(300);
	CLEAR_WDT();
	cells_init();
	Soft_I2C_Init();
	if (type == 0) { // 2-colors led  reset
		LATBbits.LATB6 = 1;
		LATBbits.LATB7 = 1;
	}
	dysp_cnt = Dysp_delay * dysp_cnt_mult;

	Delay_ms(300);
	CLEAR_WDT();

	if ((PORTBbits.RB1 == 0) && (PORTBbits.RB2 == 0)) { // Test mode
		Test = 1;
		Auto = 0;
	}

	if (L_q == 5)L_mult = 1;
	else if (L_q == 6) L_mult = 2;
	else if (L_q == 7) L_mult = 4;

	if (C_q == 5) C_mult = 1;
	else if (C_q == 6) C_mult = 2;
	else if (C_q == 7) C_mult = 4;

	Delay_ms(300);
	CLEAR_WDT();
	Delay_ms(300);
	CLEAR_WDT();
	Delay_ms(300);
	CLEAR_WDT();
	Delay_ms(300);
	CLEAR_WDT();
	Delay_ms(300);
	CLEAR_WDT();

	led_init();

	if (PORTBbits.RB1 == 0 && PORTBbits.RB2 == 0 && PORTBbits.RB0 == 0) { // Fast Test mode (loop)
		if (type == 4 || type == 5) led_wr_str(0, 12, "FAST TEST", 9); // 128*64
		else if (type != 0) led_wr_str(0, 3, "FAST TEST", 9); // 1602 | 128*32
		set_cap(255);
		if (L_invert == 0) {
			set_ind(255);
		} else {
			set_ind(0);
		}
		set_sw(1);

		CLEAR_WDT();

		while (1) {
			Delay_ms(500);
			CLEAR_WDT();
		}
	}

	CLEAR_WDT();

	if (Button(&PORTB, 0, 100, 0)) {									/* Feed line loss input */
		if (type == 4 || type == 5) {									/* 128x64 OLED display */
			led_wr_str(0, 6, "Feed Loss", 10);
			led_wr_str(2, 6, "input", 5);
			led_wr_str(4, 6 + 3 * 12, "dB", 2);
		} else if (type != 0) {											/* 16x2 character LCD & 128x32 OLED display */
			led_wr_str(0, 0, "Feed Loss input", 16);
			led_wr_str(1, 3, "dB", 2);
		}
		Fid_loss = Bcd2Dec(EEPROM_Read(0x34));
		show_loss();

		while (1) {
			if (Button(&PORTB, 2, 50, 0)) {								// BYP button
				if (Fid_loss < 99) {
					Fid_loss++;
					show_loss();
					EEPROM_Write(0x34, Dec2Bcd(Fid_loss));
				}
				while (Button(&PORTB, 2, 50, 0)) {
					CLEAR_WDT();
				}
			}

			if (Button(&PORTB, 1, 50, 0)) {								// AUTO button
				if (Fid_loss > 0) {
					Fid_loss--;
					show_loss();
					EEPROM_Write(0x34, Dec2Bcd(Fid_loss));
				}
				while (Button(&PORTB, 1, 50, 0)) {
					CLEAR_WDT();
				}
			}

			CLEAR_WDT();
		} // while
	} //  Fider loss input

	if (Test == 0) {
		cap.byte = (uint8_t)EEPROM_Read(255);
		ind.byte = (uint8_t)EEPROM_Read(254);
		SW = (uint8_t)EEPROM_Read(253);
		swr_a = EEPROM_Read(252) * 256;
		swr_a += EEPROM_Read(251);
		set_ind(ind.byte);
		set_cap(cap.byte);
		set_sw(SW);
		if (Restart == 1) {
			lcd_prep_short = 1;
		}
		lcd_prep();
	} else {
		Test_init();
	}

	lcd_ind();
	tune_btn_release = 1;



	//*******************************

	while (1) {
		CLEAR_WDT();
		lcd_pwr();

		if (Test == 0) button_proc();
		else button_proc_test();

		if (dysp_cnt != 0) dysp_cnt--;
		else if (Test == 0 && Dysp_delay != 0 && dysp == 1) {
			if (Relay_off) {
				set_ind(0);
				set_cap(0);
				set_SW(0);
			}
			dysp = 0;
			dysp_off();
		}

		// next While code
	}
}


//***************** Routines *****************

void button_proc_test(void) {
	if (Button(&PORTB, 0, 50, 0)) { // Tune btn
		Delay_ms(250);
		CLEAR_WDT();
		if (PORTBbits.RB0 == 1) { // short press button
			if (SW == 0) SW = 1;
			else SW = 0;
			set_sw(SW);
			lcd_ind();
		} else { // long press button
			if (L == 1) L = 0;
			else L = 1;
			if (L == 1) {
				if (type == 4 || type == 5) // 128*64 OLED
					led_wr_str(0, 16 + 12 * 8, "l", 1);
				else if (type != 0) // 1602 LCD & 128*32 OLED
					led_wr_str(0, 8, "l", 1);
			} else {
				if (type == 4 || type == 5) // 128*64 OLED
					led_wr_str(0, 16 + 12 * 8, "c", 1);
				else if (type != 0) // 1602 LCD & 128*32 OLED
					led_wr_str(0, 8, "c", 1);
			}
		}
		while (Button(&PORTB, 0, 50, 0)) {
			lcd_pwr();
			CLEAR_WDT();
		}
	} // END Tune btn

	if (Button(&PORTB, 2, 50, 0)) { // BYP button
		CLEAR_WDT();

		while (PORTBbits.RB2 == 0) {
			if (L && ind.byte < 32 * L_mult - 1) {
				ind.byte++;
				set_ind(ind.byte);
			} else if (!L && cap.byte < 32 * L_mult - 1) {
				cap.byte++;
				set_cap(cap.byte);
			}
			lcd_ind();
			lcd_pwr();
			Delay_ms(30);

			CLEAR_WDT();
		}
	} // end of BYP button

	if (Button(&PORTB, 1, 50, 0) && (bypas == 0)) { // Auto button
		CLEAR_WDT();

		while (PORTBbits.RB1 == 0) {
			if (L && ind.byte > 0) {
				ind.byte--;
				set_ind(ind.byte);
			} else if (!L && cap.byte > 0) {
				cap.byte--;
				set_cap(cap.byte);
			}
			lcd_ind();
			lcd_pwr();
			Delay_ms(30);
			CLEAR_WDT();
		}
	}
	return;
}


void button_proc(void) {
	if ((tune_btn_release == 0) && Button(&PORTB, 0, 50, 1)) {
		tune_btn_release = 1;
	}

	if ((tune_btn_release == 0) && Button(&PORTB, 0, 50, 0)) {
		dysp_cnt = Dysp_delay * dysp_cnt_mult;
	}

	if ((Button(&PORTB, 0, 50, 0) && tune_btn_release) || Soft_tune) {
		if (dysp == 0) { // dysplay ON
			if (Relay_off == 1) {
				set_ind(ind.byte);
				set_cap(cap.byte);
				set_SW(SW);
			}
			dysp = 1;
			dysp_on();
			dysp_cnt = Dysp_delay * dysp_cnt_mult;
			return;
		}
		dysp_cnt = Dysp_delay * dysp_cnt_mult;
		Delay_ms(250);
		CLEAR_WDT();
		if (Soft_tune == 0 & PORTBbits.RB0 == 1) { // short press button
			show_reset();
			bypas = 0;
		} else { // long press button
			p_Tx = 1; //
			n_Tx = 0; // TX request
			Delay_ms(250); //
			btn_push();
			bypas = 0;
			Soft_tune = 0;
			tune_btn_release = 0;
		}
	}

	if (Button(&PORTB, 2, 50, 0)) { // BYP button
		if (dysp == 0) { // dysplay ON
			if (Relay_off == 1) {
				set_ind(ind.byte);
				set_cap(cap.byte);
				set_SW(SW);
			}
			dysp = 1;
			dysp_on();
			dysp_cnt = Dysp_delay * dysp_cnt_mult;
			return;
		}
		dysp_cnt = Dysp_delay * dysp_cnt_mult;
		CLEAR_WDT();
		if (bypas == 0) {
			bypas = 1;
			cap_mem = cap.byte;
			ind_mem = ind.byte;
			SW_mem = SW;
			cap.byte = 0;
			if (L_invert) {
				ind.byte = 255;
			} else {
				ind.byte = 0;
			}
			SW = 1;
			set_ind(ind.byte);
			set_cap(cap.byte);
			set_SW(SW);
			if (Loss_mode == 0) {
				lcd_ind();
			}
			Auto_mem = Auto;
			Auto = 0;
		} else {
			bypas = 0;
			cap.byte = cap_mem;
			ind.byte = ind_mem;
			SW = SW_mem;
			set_cap(cap.byte);
			set_ind(ind.byte);
			set_SW(SW);
			if (Loss_mode == 0) {
				lcd_ind();
			}
			Auto = Auto_mem;
		}

		if ((type == 4) || (type == 5)) { // 128*64 OLED
			if (Auto && !bypas) led_wr_str(0, 16 + 8 * 12, ".", 1);
			else if (!Auto && bypas) led_wr_str(0, 16 + 8 * 12, "_", 1);
			else led_wr_str(0, 16 + 8 * 12, " ", 1);
		} else if (type != 0) { //  1602 LCD  or 128*32 OLED
			if (Auto && !bypas) led_wr_str(0, 8, ".", 1);
			else if (!Auto && bypas) led_wr_str(0, 8, "_", 1);
			else led_wr_str(0, 8, " ", 1);
		}

		CLEAR_WDT();

		while (Button(&PORTB, 2, 50, 0)) {
			lcd_pwr();
			CLEAR_WDT();
		}
	}

	if (Button(&PORTB, 1, 50, 0) && (bypas == 0)) { // Auto button
		if (dysp == 0) { // dysplay ON
			if (Relay_off == 1) {
				set_ind(ind.byte);
				set_cap(cap.byte);
				set_SW(SW);
			}
			dysp = 1;
			dysp_on();
			dysp_cnt = Dysp_delay * dysp_cnt_mult;
			return;
		}
		dysp_cnt = Dysp_delay * dysp_cnt_mult;
		CLEAR_WDT();
		if (Auto == 0) {
			Auto = 1;
		} else {
			Auto = 0;
		}

		EEPROM_Write(EEPROM_AUTO_MODE, Auto);

		if ((type == 4) || (type == 5)) { // 128*64 OLED
			if (Auto & !bypas) led_wr_str(0, 16 + 8 * 12, ".", 1);
			else if (!Auto && bypas) led_wr_str(0, 16 + 8 * 12, "_", 1);
			else led_wr_str(0, 16 + 8 * 12, " ", 1);
		} else if (type != 0) { //  1602 LCD  or 128*32 OLED
			if (Auto && !bypas) led_wr_str(0, 8, ".", 1);
			else if (!Auto && bypas) led_wr_str(0, 8, "_", 1);
			else led_wr_str(0, 8, " ", 1);
		}
		CLEAR_WDT();
		while (Button(&PORTB, 1, 50, 0)) {
			lcd_pwr();
			CLEAR_WDT();
		}
	}
	return;
}

void show_reset() {
	atu_reset();
	SW = 1;
	set_sw(SW);
	EEPROM_Write(255, 0);
	EEPROM_Write(254, 0);
	EEPROM_Write(253, 1);
	EEPROM_Write(252, 0);
	EEPROM_Write(251, 0);
	lcd_ind();
	Loss_mode = 0;
	p_Tx = 0;
	n_Tx = 1;
	SWR = 0;
	PWR = 0;
	SWR_fixed_old = 0;
	if (type == 4 | type == 5) { // 128*64 OLED
		led_wr_str(2, 16, "RESET   ", 8);
		CLEAR_WDT();
		delay_ms(600);
		led_wr_str(2, 16, "SWR=0.00", 8);
		CLEAR_WDT();
	} else if (type != 0) {// 1602 LCD & 128*32 OLED
		led_wr_str(1, 0, "RESET   ", 8);
		CLEAR_WDT();
		delay_ms(600);
		led_wr_str(1, 0, "SWR=0.00", 8);
		CLEAR_WDT();
	} else {
		LATBbits.LATB6 = 1;
		LATBbits.LATB7 = 1;
	}
	SWR_old = 10000;
	Power_old = 10000;
	lcd_pwr();
	return;
}

void btn_push() {
	CLEAR_WDT();

	if ((type == 4) || (type == 5)) { // 128*64 OLED
		led_wr_str(2, 16 + 12 * 4, "TUNE", 4);
	} else if (type != 0) { // 1602 LCD & 128*32 OLED
		led_wr_str(1, 4, "TUNE", 4);
	} else {
		LATBbits.LATB6 = 1;
		LATBbits.LATB7 = 1;
	}

	tune();

	if (type == 0) { // real-time 2-colors led work
		if (swr <= 150) {
			LATBbits.LATB6 = 0;
			LATBbits.LATB7 = 1;
		}// Green
		else if (swr <= 250) {
			PORTBbits.RB6 = 0;
			PORTBbits.RB7 = 0;
		}// Orange
		else {
			PORTBbits.RB6 = 1;
			PORTBbits.RB7 = 0;
		} // Red
	} else if ((Loss_mode == 0) || (Loss_ind == 0)) {
		lcd_ind();
	}
	EEPROM_Write(255, cap.byte);
	EEPROM_Write(254, ind.byte);
	EEPROM_Write(253, SW);
	EEPROM_Write(252, swr_a / 256);
	EEPROM_Write(251, swr_a % 256);
	SWR_old = 10000;
	Power_old = 10000;
	lcd_pwr();
	SWR_fixed_old = SWR;

	p_Tx = 0;
	n_Tx = 1;

	CLEAR_WDT();

	return;
}

void lcd_prep() {
	CLEAR_WDT();

	if (type == 4 | type == 5) { // 128*64 OLED
		if (lcd_prep_short == 0) {
			led_wr_str(0, 22, "ATU-100", 7);
			led_wr_str(2, 6, "EXT board", 9);
			led_wr_str(4, 16, "by N7DDC", 8);
			led_wr_str(6, 4, "FW ver 3.2", 10);
			CLEAR_WDT();
			Delay_ms(600);
			CLEAR_WDT();
			Delay_ms(500);
			CLEAR_WDT();
			led_wr_str(0, 16, "        ", 8);
			led_wr_str(2, 4, "          ", 10);
			led_wr_str(4, 16, "        ", 8);
			led_wr_str(6, 4, "          ", 10);
		}
		Delay_ms(150);
		if (P_High == 1) led_wr_str(0, 16, "PWR=  0W", 8);
		else led_wr_str(0, 16, "PWR=0.0W", 8);
		led_wr_str(2, 16, "SWR=0.00", 8);
		if (Auto) led_wr_str(0, 16 + 8 * 12, ".", 1);
	} else if (type != 0) { // 1602 LCD & 128*32 OLED
		if (lcd_prep_short == 0) {
			led_wr_str(0, 4, "ATU-100", 7);
			led_wr_str(1, 3, "EXT board", 9);
			CLEAR_WDT();
			Delay_ms(700);
			CLEAR_WDT();
			Delay_ms(500);
			CLEAR_WDT();
			led_wr_str(0, 4, "by N7DDC", 8);
			led_wr_str(1, 3, "FW ver 3.2", 10);
			CLEAR_WDT();
			Delay_ms(600);
			CLEAR_WDT();
			Delay_ms(500);
			CLEAR_WDT();
			led_wr_str(0, 4, "        ", 8);
			led_wr_str(1, 3, "          ", 10);
		}
		Delay_ms(150);
		if (P_High == 1) led_wr_str(0, 0, "PWR=  0W", 8);
		else led_wr_str(0, 0, "PWR=0.0W", 8);
		led_wr_str(1, 0, "SWR=0.00", 8);
		if (Auto) led_wr_str(0, 8, ".", 1);
	}
	CLEAR_WDT();
	lcd_ind();
	return;
}

void lcd_swr(int swr) {
	CLEAR_WDT();

	if (swr != SWR_old) {
		SWR_old = swr;
		if (SWR == 0) { // Low power
			if ((type == 4) || (type == 5)) {				/* 128x64 OLED */
				led_wr_str(2, 16 + 4 * 12, "0.00", 4);
			} else if (type != 0) {							/* 1602 & 128x32 OLED */
				led_wr_str(1, 4, "0.00", 4);
			} else if (type == 0) {							/* real-time 2-colors led work */
				LATBbits.LATB6 = 1;
				LATBbits.LATB7 = 1;
			}
			SWR_old = 0;
		} else {
			IntToStr(swr, work_str);
			work_str_2[0] = work_str[3];
			work_str_2[1] = '.';
			work_str_2[2] = work_str[4];
			work_str_2[3] = work_str[5];

			if ((type == 4) || (type == 5)) {
				led_wr_str(2, 16 + 4 * 12, work_str_2, 4);
			} else if (type != 0) {
				led_wr_str(1, 4, work_str_2, 4);
			} else if (type == 0) {
				if (swr <= 150) {							/* Green */
					LATBbits.LATB6 = 0;
					LATBbits.LATB7 = 1;
				} else if (swr <= 250) {					/* Orange */
					PORTBbits.RB6 = 0;
					PORTBbits.RB7 = 0;
				} else {									/* Red */
					PORTBbits.RB6 = 1;
					PORTBbits.RB7 = 0;
				}
			}
		}
	}

	CLEAR_WDT();

	return;
}

void button_delay() {
	if ((Button(&PORTB, 0, 25, 0)) | (Button(&PORTB, 1, 25, 0)) | (Button(&PORTB, 2, 25, 0))) {
		but = 1;
	}
	return;
}

void show_pwr(int Power, int SWR) {
	int p_ant;
	int eff;
	float a;
	float b;

	a = 100;

	CLEAR_WDT();

	if ((Test == 0) && (Loss_ind == 1) && (Power >= 10)) {
		if (Loss_mode == 0) { // prepare
			if (type == 4 || type == 5) { // 128*64 OLED
				if (P_High == 1) led_wr_str(4, 16, "ANT=  0W", 8);
				else led_wr_str(4, 16, "ANT=0.0W", 8);
				led_wr_str(6, 16, "EFF=  0%", 8);
			} else if (type == 2 || type == 3) { // 128*32 OLED
				if (P_High == 1) led_wr_str(0, 9, "ANT=  0W", 8);
				else led_wr_str(0, 9, "ANT=0.0W", 8);
				led_wr_str(1, 9, "EFF=  0%", 8);
			} else if (type == 1) { // 1602 LCD
				if (P_High == 1) led_wr_str(0, 9, "AN=  0W", 7);
				else led_wr_str(0, 9, "AN=0.0W", 7);
				led_wr_str(1, 9, "EFF= 0%", 7);
			}
		}
		Loss_mode = 1;
	} else {
		if (Loss_mode == 1) {
			lcd_ind();
		}
		Loss_mode = 0;
	}

	CLEAR_WDT();

	if (Power != Power_old) {
		Power_old = Power;

		if (P_High == 0) {
			if (Power >= 100) {											// > 10W
				Power += 5;												// rounding to 1W
				IntToStr(Power, work_str);
				work_str_2[0] = work_str[2];
				work_str_2[1] = work_str[3];
				work_str_2[2] = work_str[4];
				work_str_2[3] = 'W';
			} else {
				IntToStr(Power, work_str);
				if (work_str[4] != ' ') {
					work_str_2[0] = work_str[4];
				} else {
					work_str_2[0] = '0';
				}

				work_str_2[1] = '.';

				if (work_str[5] != ' ') {
					work_str_2[2] = work_str[5];
				} else {
					work_str_2[2] = '0';
				}

				work_str_2[3] = 'W';
			}
		} else {														// High Power
			if (Power < 999) {											// 0W - 999W
				IntToStr(Power, work_str);
				work_str_2[0] = work_str[3];
				work_str_2[1] = work_str[4];
				work_str_2[2] = work_str[5];
				work_str_2[3] = 'W';
			} else {
				IntToStr(Power, work_str);
				work_str_2[0] = work_str[2];
				work_str_2[1] = work_str[3];
				work_str_2[2] = work_str[4];
				work_str_2[3] = work_str[5];
			}
		}

		if (type == 4 || type == 5) {									/* 128x64 OLED display */
			led_wr_str(0, 16 + 4 * 12, work_str_2, 4);
		} else if (type != 0) {											/* 16x2 character LCD & 128x32 OLED display */
			led_wr_str(0, 4, work_str_2, 4);
		}

		CLEAR_WDT();

		/* Loss indication */
		if (Loss_mode == 1) {
			if (ind.byte == 0 && cap.byte == 0) {
				swr_a = SWR;
			}

			a = 1.0 / ((swr_a / 100.0 + 100.0 / swr_a) * Fid_loss / 10.0 * 0.115 + 1.0);	// Feed line loss
			b = 4.0 / (2.0 + SWR / 100.0 + 100.0 / SWR);									// SWR loss

			if (a >= 1.0) {
				a = 1.0;
			}
			if (b >= 1.0) {
				b = 1.0;
			}

			p_ant = Power * a * b;
			eff = a * b * 100;

			if (eff >= 100) {
				eff = 99;
			}

			if (P_High == 0) {
				if (p_ant >= 100) { // > 10 W
					p_ant += 5; // rounding to 1 W
					IntToStr(p_ant, work_str);
					work_str_2[0] = work_str[2];
					work_str_2[1] = work_str[3];
					work_str_2[2] = work_str[4];
					work_str_2[3] = 'W';
				} else {
					IntToStr(p_ant, work_str);
					if (work_str[4] != ' ') work_str_2[0] = work_str[4];
					else work_str_2[0] = '0';
					work_str_2[1] = '.';
					if (work_str[5] != ' ') work_str_2[2] = work_str[5];
					else work_str_2[2] = '0';
					work_str_2[3] = 'W';
				}
			} else { // High Power
				if (p_ant < 999) { // 0 - 1500 Watts
					IntToStr(p_ant, work_str);
					work_str_2[0] = work_str[3];
					work_str_2[1] = work_str[4];
					work_str_2[2] = work_str[5];
					work_str_2[3] = 'W';
				} else {
					IntToStr(p_ant, work_str);
					work_str_2[0] = work_str[2];
					work_str_2[1] = work_str[3];
					work_str_2[2] = work_str[4];
					work_str_2[3] = work_str[5];
				}
			}
			if (type == 4 | type == 5) led_wr_str(4, 16 + 4 * 12, work_str_2, 4); // 128*64 OLED
			else if (type == 2 | type == 3) led_wr_str(0, 13, work_str_2, 4); // 128*32
			else if (type != 0) led_wr_str(0, 12, work_str_2, 4); // 1602

			IntToStr(eff, work_str);
			work_str_2[0] = work_str[4];
			work_str_2[1] = work_str[5];
			if (type == 4 | type == 5) led_wr_str(6, 16 + 5 * 12, work_str_2, 2);
			else if (type == 2 | type == 3) led_wr_str(1, 14, work_str_2, 2);
			else if (type == 1) led_wr_str(1, 13, work_str_2, 2);
		}
	}
	CLEAR_WDT();
	return;
}

void lcd_pwr() {
	int p = 0;
	char peak_cnt;
	int delta = Auto_delta - 100;
	char cnt;
	int SWR_fixed;
	PWR = 0;
	CLEAR_WDT();

	if (dysp == 0 & Relay_off == 1) {
		get_pwr();
		if (PWR >= 10) {
			set_ind(ind.byte);
			set_cap(cap.byte);
			set_SW(SW);

			dysp = 1;
			dysp_on(); // dysplay ON
			dysp_cnt = Dysp_delay * dysp_cnt_mult;
		}
		return;
	}

	// peak detector
	cnt = 120;
	for (peak_cnt = 0; peak_cnt < cnt; peak_cnt++) {
		if (PORTBbits.RB1 == 0 | PORTBbits.RB2 == 0 | (PORTBbits.RB0 == 0 & tune_btn_release)) {
			button_delay();
			if (but == 1) {
				but = 0;
				return;
			}
		}
		get_pwr();
		if (PWR > p) {
			p = PWR;
			SWR_fixed = SWR;
		}
		Delay_ms(3);
	}

	CLEAR_WDT();

	if (p >= 100) {
		p = (p + 5) / 10;
		p *= 10;
	} // round to 1 W if more then 100 W

	Power = p;
	if (Power < 10) SWR_fixed = 0;
	lcd_swr(SWR_fixed);
	if (Power >= 10 & Dysp_delay > 0) {
		dysp_cnt = Dysp_delay * dysp_cnt_mult;
	}

	if (Auto && SWR_fixed >= Auto_delta && ((SWR_fixed > SWR_fixed_old && (SWR_fixed - SWR_fixed_old) > delta) || (SWR_fixed < SWR_fixed_old && (SWR_fixed_old - SWR_fixed) > delta) || SWR_fixed_old == 999))
		Soft_tune = 1;

	if ((PORTBbits.RB1 == 0) || (PORTBbits.RB2 == 0) || ((PORTBbits.RB0 == 0) && tune_btn_release)) {
		button_delay();
		if (but == 1) {
			but = 0;
			return;
		}
	} // Fast return if button pressed

	show_pwr(Power, SWR_fixed);

	if (PORTBbits.RB1 == 0 || PORTBbits.RB2 == 0 || (PORTBbits.RB0 == 0 && tune_btn_release)) {
		button_delay();
		if (but == 1) {
			but = 0;
			return;
		}
	}

	CLEAR_WDT();

	if (Overload == 1) {
		if (type == 4 || type == 5) { // 128*64 OLED
			led_wr_str(2, 16, "        ", 8);
			delay_ms(100);
			led_wr_str(2, 16, "OVERLOAD", 8);
			delay_ms(500);
			CLEAR_WDT();
			led_wr_str(2, 16, "        ", 8);
			delay_ms(300);
			CLEAR_WDT();
			led_wr_str(2, 16, "OVERLOAD", 8);
			delay_ms(500);
			CLEAR_WDT();
			led_wr_str(2, 16, "        ", 8);
			delay_ms(300);
			CLEAR_WDT();
			led_wr_str(2, 16, "OVERLOAD", 8);
			delay_ms(500);
			CLEAR_WDT();
			led_wr_str(2, 16, "        ", 8);
			delay_ms(100);
			led_wr_str(2, 16, "SWR=    ", 8);
		} else if (type != 0) { // 1602  & 128*32
			led_wr_str(1, 0, "        ", 8);
			delay_ms(100);
			led_wr_str(1, 0, "OVERLOAD", 8);
			delay_ms(500);
			CLEAR_WDT();
			led_wr_str(1, 0, "        ", 8);
			delay_ms(300);
			CLEAR_WDT();
			led_wr_str(1, 0, "OVERLOAD", 8);
			delay_ms(500);
			CLEAR_WDT();
			led_wr_str(1, 0, "        ", 8);
			delay_ms(300);
			CLEAR_WDT();
			led_wr_str(1, 0, "OVERLOAD", 8);
			delay_ms(500);
			CLEAR_WDT();
			led_wr_str(1, 0, "        ", 8);
			delay_ms(100);
			led_wr_str(1, 0, "SWR=    ", 8);
		}
		CLEAR_WDT();
		SWR_old = 10000;
		lcd_swr(SWR_fixed);
	}
	return;
}

void lcd_ind() {
	char column;

	CLEAR_WDT();

	if (1) {
		work_int = 0;
		if (ind.B0) work_int += Ind1;
		if (ind.B1) work_int += Ind2;
		if (ind.B2) work_int += Ind3;
		if (ind.B3) work_int += Ind4;
		if (ind.B4) work_int += Ind5;
		if (ind.B5) work_int += Ind6;
		if (ind.B6) work_int += Ind7;
		if (work_int > 9999) { // more then 9999 nH
			work_int += 50; // round
			IntToStr(work_int, work_str);
			work_str_2[0] = work_str[1];
			work_str_2[1] = work_str[2];
			work_str_2[2] = '.';
			work_str_2[3] = work_str[3];
		} else {
			IntToStr(work_int, work_str);
			if (work_str[2] != ' ') work_str_2[0] = work_str[2];
			else work_str_2[0] = '0';
			work_str_2[1] = '.';
			if (work_str[3] != ' ') work_str_2[2] = work_str[3];
			else work_str_2[2] = '0';
			if (work_str[4] != ' ') work_str_2[3] = work_str[4];
			else work_str_2[3] = '0';
		}

		if (type == 4 | type == 5) { // 128*64 OLED
			if (SW == 1) column = 4;
			else column = 6;
			led_wr_str(column, 16, "L=", 2);
			led_wr_str(column, 16 + 6 * 12, "uH", 2);
			led_wr_str(column, 16 + 2 * 12, work_str_2, 4);
		} else if (type == 2 | type == 3) {// 128*32 OLED
			if (SW == 1) column = 0;
			else column = 1;
			led_wr_str(column, 9, "L=", 2);
			led_wr_str(column, 15, "uH", 2);
			led_wr_str(column, 11, work_str_2, 4);
		} else if (type == 1) { //  1602 LCD
			if (SW == 1) column = 0;
			else column = 1;
			led_wr_str(column, 9, "L=", 2);
			led_wr_str(column, 15, "u", 1);
			led_wr_str(column, 11, work_str_2, 4);
		}
	}

	CLEAR_WDT();

	if (1) {
		work_int = 0;
		if (cap.B0) work_int += Cap1;
		if (cap.B1) work_int += Cap2;
		if (cap.B2) work_int += Cap3;
		if (cap.B3) work_int += Cap4;
		if (cap.B4) work_int += Cap5;
		if (cap.B5) work_int += Cap6;
		if (cap.B6) work_int += Cap7;
		IntToStr(work_int, work_str);
		work_str_2[0] = work_str[2];
		work_str_2[1] = work_str[3];
		work_str_2[2] = work_str[4];
		work_str_2[3] = work_str[5];

		if (type == 4 | type == 5) { // 128*64 OLED
			if (SW == 1) column = 6;
			else column = 4;
			led_wr_str(column, 16, "C=", 2);
			led_wr_str(column, 16 + 6 * 12, "pF", 2);
			led_wr_str(column, 16 + 2 * 12, work_str_2, 4);
		} else if (type == 2 | type == 3) {// 128*32 OLED
			if (SW == 1) column = 1;
			else column = 0;
			led_wr_str(column, 9, "C=", 2);
			led_wr_str(column, 15, "pF", 2);
			led_wr_str(column, 11, work_str_2, 4);
		} else if (type == 1) { // 1602 LCD
			if (SW == 1) column = 1;
			else column = 0;
			led_wr_str(column, 9, "C=", 2);
			led_wr_str(column, 15, "p", 1);
			led_wr_str(column, 11, work_str_2, 4);
		}
	}

	CLEAR_WDT();

	return;
}

void Test_init(void) { // Test mode
	if (type == 4 | type == 5) // 128*64 OLED
		led_wr_str(0, 10, "TEST MODE", 9);
	else if (type != 0) // 1602 LCD  or 128*32 OLED
		led_wr_str(0, 3, "TEST MODE", 9);
	CLEAR_WDT();
	Delay_ms(500);
	CLEAR_WDT();
	Delay_ms(500);
	CLEAR_WDT();
	Delay_ms(500);
	CLEAR_WDT();
	Delay_ms(500);
	CLEAR_WDT();
	if (type == 4 | type == 5) // 128*64 OLED
		led_wr_str(0, 10, "         ", 9);
	else if (type != 0) // 1602 LCD  or 128*32 OLED
		led_wr_str(0, 3, "         ", 9);
	atu_reset();
	SW = 1; // C to OUT
	set_sw(SW);
	EEPROM_Write(255, cap.byte);
	EEPROM_Write(254, ind.byte);
	EEPROM_Write(253, SW);

	if (type == 4 || type == 5) // 128*64 OLED
		led_wr_str(0, 16 + 12 * 8, "l", 1);
	else if (type != 0) // 1602 LCD or 128*32 OLED
		led_wr_str(0, 8, "l", 1);

	lcd_prep_short = 1;
	lcd_prep();
	return;
}

void cells_init(void) {
	CLEAR_WDT();

#if defined(READ_OLED_ADDR_FROM_EEPROM)
	oled_addr = EEPROM_Read(EEPROM_OLED_ADDR);								// OLED I2C address
#endif
	type = EEPROM_Read(EEPROM_DISP_TYPE);									// type of display
	if (EEPROM_Read(EEPROM_AUTO_MODE) == 1) {								/* Check if AUTO mode should be enabled */
		Auto = 1;
	}
	Rel_Del = Bcd2Dec(EEPROM_Read(EEPROM_RELAY_DELAY));						// Relay's Delay
	Auto_delta = Bcd2Dec(EEPROM_Read(EEPROM_AUTO_DELTA)) * 10;				// Auto_delta
	min_for_start = Bcd2Dec(EEPROM_Read(EEPROM_PMIN_FOR_START)) * 10;		// P_min_for_start
	max_for_start = Bcd2Dec(EEPROM_Read(EEPROM_PMAX_FOR_START)) * 10;		// P_max_for_start
	// 7  - shift down
	// 8 - shift left
	max_swr = Bcd2Dec(EEPROM_Read(9)) * 10;									/* Max SWR */
	L_q = EEPROM_Read(10);
	L_linear = EEPROM_Read(11);
	C_q = EEPROM_Read(12);
	C_linear = EEPROM_Read(13);
	D_correction = EEPROM_Read(14);
	L_invert = EEPROM_Read(15);

	CLEAR_WDT();

	Ind1 = Bcd2Dec(EEPROM_Read(16)) * 100 + Bcd2Dec(EEPROM_Read(17));		/* Ind1 */
	Ind2 = Bcd2Dec(EEPROM_Read(18)) * 100 + Bcd2Dec(EEPROM_Read(19));		/* Ind2 */
	Ind3 = Bcd2Dec(EEPROM_Read(20)) * 100 + Bcd2Dec(EEPROM_Read(21));		/* Ind3 */
	Ind4 = Bcd2Dec(EEPROM_Read(22)) * 100 + Bcd2Dec(EEPROM_Read(23));		/* Ind4 */
	Ind5 = Bcd2Dec(EEPROM_Read(24)) * 100 + Bcd2Dec(EEPROM_Read(25));		/* Ind5 */
	Ind6 = Bcd2Dec(EEPROM_Read(26)) * 100 + Bcd2Dec(EEPROM_Read(27));		/* Ind6 */
	Ind7 = Bcd2Dec(EEPROM_Read(28)) * 100 + Bcd2Dec(EEPROM_Read(29));		/* Ind7 */

	Cap1 = Bcd2Dec(EEPROM_Read(32)) * 100 + Bcd2Dec(EEPROM_Read(33));		/* Cap1 */
	Cap2 = Bcd2Dec(EEPROM_Read(34)) * 100 + Bcd2Dec(EEPROM_Read(35));		/* Cap2 */
	Cap3 = Bcd2Dec(EEPROM_Read(36)) * 100 + Bcd2Dec(EEPROM_Read(37));		/* Cap3 */
	Cap4 = Bcd2Dec(EEPROM_Read(38)) * 100 + Bcd2Dec(EEPROM_Read(39));		/* Cap4 */
	Cap5 = Bcd2Dec(EEPROM_Read(40)) * 100 + Bcd2Dec(EEPROM_Read(41));		/* Cap5 */
	Cap6 = Bcd2Dec(EEPROM_Read(42)) * 100 + Bcd2Dec(EEPROM_Read(43));		/* Cap6 */
	Cap7 = Bcd2Dec(EEPROM_Read(44)) * 100 + Bcd2Dec(EEPROM_Read(45));		/* Cap7 */

	P_High = EEPROM_Read(0x30);												/* High power mode */
	K_Mult = Bcd2Dec(EEPROM_Read(0x31));									/* Tandem Match ratio */
	Dysp_delay = Bcd2Dec(EEPROM_Read(0x32));								/* Display ON delay */
	Loss_ind = EEPROM_Read(0x33);
	Fid_loss = Bcd2Dec(EEPROM_Read(0x34));
	Relay_off = Bcd2Dec(EEPROM_Read(0x35));

	CLEAR_WDT();

	return;
}

void show_loss(void) {
	IntToStr(Fid_loss, work_str);
	if (Fid_loss >= 10) {
		work_str_2[0] = work_str[4];
	} else {
		work_str_2[0] = '0';
	}

	work_str_2[1] = '.';
	work_str_2[2] = work_str[5];

	if ((type == 4) || (type == 5)) {			/* 128x64 OLED display */
		led_wr_str(4, 6, work_str_2, 3);
	} else if (type != 0) {						/* 16x2 LCD or 128x32 OLED display */
		led_wr_str(1, 0, work_str_2, 3);
	}

	return;
}
