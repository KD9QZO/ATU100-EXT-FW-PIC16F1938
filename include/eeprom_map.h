/*
 * File:   eeprom_map.h
 * Author: gmunsch
 *
 * Created on December 12, 2021, 11:08 AM
 */

#ifndef EEPROM_MAP_H_
#define EEPROM_MAP_H_

#include <xc.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>



#ifdef __cplusplus
extern "C" {
#endif


/**
 * \name EEPROM Address Map
 *
 * @{
 */

#define EEPROM_OLED_ADDR			0x00
#define EEPROM_DISP_TYPE			0x01
#define EEPROM_AUTO_MODE			0x02
#define EEPROM_RELAY_DELAY			0x03
#define EEPROM_AUTO_DELTA			0x04
#define EEPROM_PMIN_FOR_START		0x05
#define EEPROM_PMAX_FOR_START		0x06
#define EEPROM_SHIFT_DOWN			0x07
#define EEPROM_SHIFT_LEFT			0x08
#define EEPROM_MAX_SWR				0x09
#if 0
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#define EEPROM_
#endif

/**
 * @}
 */


#ifdef __cplusplus
}
#endif

#endif	/* !EEPROM_MAP_H_ */
