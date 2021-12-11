/*
 * File:   extratypes.h
 * Author: gmunsch
 *
 * Created on December 10, 2021, 2:34 PM
 */

#ifndef EXTRATYPES_H_
#define	EXTRATYPES_H_

#include <xc.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef	__cplusplus
extern "C" {
#endif



typedef union {
	struct {
		unsigned B0:1;
		unsigned B1:1;
		unsigned B2:1;
		unsigned B3:1;
		unsigned B4:1;
		unsigned B5:1;
		unsigned B6:1;
		unsigned B7:1;
	};
	uint8_t byte;
} bit_byte_t;



#ifdef	__cplusplus
}
#endif

#endif	/* EXTRATYPES_H */

