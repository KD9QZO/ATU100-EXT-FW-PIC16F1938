/* Microchip Technology Inc. and its subsidiaries.  You may use this software
 * and any derivatives exclusively with Microchip products.
 *
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
 * TERMS.
 */

/*
 * File:
 * Author:
 * Comments:
 * Revision history:
 */

#ifndef PREPROCESSOR_H_
#define PREPROCESSOR_H_

#include <xc.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>


// TODO Insert appropriate #include <>

// TODO Insert C++ class definitions if appropriate

// TODO Insert declarations

// Comment a function and leverage automatic documentation with slash star star
/**
	<p><b>Function prototype:</b></p>

	<p><b>Summary:</b></p>

	<p><b>Description:</b></p>

	<p><b>Precondition:</b></p>

	<p><b>Parameters:</b></p>

	<p><b>Returns:</b></p>

	<p><b>Example:</b></p>
	<code>

	</code>

	<p><b>Remarks:</b></p>
 */
// TODO Insert declarations or function prototypes (right here) to leverage
// live documentation

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */


#if !defined(UNUSED)
#define UNUSED(v)																									\
		((void)(v))
#endif


#define STR(s)							#s
#define XSTR(s)							STR(s)


#define TPASTE2(a, b)					a##b
#define TPASTE3(a, b, c)				a##b##c
#define TPASTE4(a, b, c, d)				a##b##c##d
#define TPASTE5(a, b, c, d, e)			a##b##c##d##e
#define TPASTE6(a, b, c, d, e, f)		a##b##c##d##e##f
#define TPASTE7(a, b, c, d, e, f, g)	a##b##c##d##e##f##g

#define ATPASTE2(a, b)					TPASTE2(a, b)
#define ATPASTE3(a, b, c)				TPASTE3(a, b, c)
#define ATPASTE4(a, b, c, d)			TPASTE4(a, b, c, d)
#define ATPASTE5(a, b, c, d, e)			TPASTE5(a, b, c, d, e)
#define ATPASTE6(a, b, c, d, e, f)		TPASTE6(a, b, c, d, e, f)
#define ATPASTE7(a, b, c, d, e, f, g)	TPASTE7(a, b, c, d, e, f, g)


#ifdef __cplusplus
}
#endif	/* __cplusplus */


#endif	/* !PREPROCESSOR_H_ */
