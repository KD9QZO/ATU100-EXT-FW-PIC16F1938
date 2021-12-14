/*
 * File:   common.h
 * Author: gmunsch
 *
 * Created on December 13, 2021, 8:27 AM
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <xc.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "eeprom_map.h"
#include "preprocessor.h"

#ifdef __cplusplus
extern "C" {
#endif


#define CLEAR_WDT()																									\
		asm("CLRWDT")




#ifdef __cplusplus
}
#endif

#endif	/* !COMMON_H_ */

