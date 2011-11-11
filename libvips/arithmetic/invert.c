/* photographic negative ... just an example, really
 *
 * Copyright: 1990, N. Dessipris.
 *
 * Author: Nicos Dessipris
 * Written on: 12/02/1990
 * Modified on :
 * 7/7/93 JC
 *      - memory leaks fixed
 *      - adapted for partial v2
 *      - ANSIfied
 * 22/2/95 JC
 *	- tidied up again
 * 2/9/09
 * 	- gtk-doc comment
 * 23/8/11
 * 	- rewrite as a class 
 */

/*

    Copyright (C) 1991-2005 The National Gallery

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

 */

/*

    These files are distributed with VIPS - http://www.vips.ecs.soton.ac.uk

 */

/*
#define DEBUG
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /*HAVE_CONFIG_H*/
#include <vips/intl.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <vips/vips.h>

#include "unary.h"

/**
 * VipsInvert:
 * @in: input #VipsImage
 * @out: output #VipsImage
 *
 * For unsigned formats, this operation calculates (max - @in), eg. (255 -
 * @in) for uchar. For signed and float formats, this operation calculates (-1
 * * @in). 
 *
 * See also: im_lintra().
 *
 * Returns: 0 on success, -1 on error
 */

typedef VipsUnary VipsInvert;
typedef VipsUnaryClass VipsInvertClass;

G_DEFINE_TYPE( VipsInvert, vips_invert, VIPS_TYPE_UNARY );

#define LOOP( TYPE, L ) { \
	TYPE *p = (TYPE *) in[0]; \
	TYPE *q = (TYPE *) out; \
	\
	for( x = 0; x < sz; x++ ) \
		q[x] = (L) - p[x]; \
}

#define LOOPN( TYPE ) { \
	TYPE *p = (TYPE *) in[0]; \
	TYPE *q = (TYPE *) out; \
	\
	for( x = 0; x < sz; x++ ) \
		q[x] = -1 * p[x]; \
}

static void
vips_invert_buffer( VipsArithmetic *arithmetic, PEL *out, PEL **in, int width )
{
	VipsImage *im = arithmetic->ready[0];

	/* Complex just doubles the size.
	 */
	const int sz = width * vips_image_get_bands( im ) * 
		(vips_band_format_iscomplex( vips_image_get_format( im ) ) ? 
		 	2 : 1);

	int x;

	switch( vips_image_get_format( im ) ) {
	case VIPS_FORMAT_UCHAR: 	
		LOOP( unsigned char, UCHAR_MAX ); break; 
	case VIPS_FORMAT_CHAR: 	
		LOOPN( signed char ); break; 
	case VIPS_FORMAT_USHORT: 
		LOOP( unsigned short, USHRT_MAX ); break; 
	case VIPS_FORMAT_SHORT: 	
		LOOPN( signed short ); break; 
	case VIPS_FORMAT_UINT: 	
		LOOP( unsigned int, UINT_MAX ); break; 
	case VIPS_FORMAT_INT: 	
		LOOPN( signed int ); break; 

	case VIPS_FORMAT_FLOAT: 		
	case VIPS_FORMAT_COMPLEX: 
		LOOPN( float ); break; 

	case VIPS_FORMAT_DOUBLE:	
	case VIPS_FORMAT_DPCOMPLEX: 
		LOOPN( double ); break;

	default:
		g_assert( 0 );
	}
}

/* Save a bit of typing.
 */
#define UC VIPS_FORMAT_UCHAR
#define C VIPS_FORMAT_CHAR
#define US VIPS_FORMAT_USHORT
#define S VIPS_FORMAT_SHORT
#define UI VIPS_FORMAT_UINT
#define I VIPS_FORMAT_INT
#define F VIPS_FORMAT_FLOAT
#define X VIPS_FORMAT_COMPLEX
#define D VIPS_FORMAT_DOUBLE
#define DX VIPS_FORMAT_DPCOMPLEX

/* Format doesn't change with invert.
 */
static const VipsBandFormat vips_bandfmt_invert[10] = {
/* UC  C   US  S   UI  I   F   X   D   DX */
   UC, C,  US, S,  UI, I,  F,  X,  D,  DX 
};

static void
vips_invert_class_init( VipsInvertClass *class )
{
	VipsObjectClass *object_class = (VipsObjectClass *) class;
	VipsArithmeticClass *aclass = VIPS_ARITHMETIC_CLASS( class );

	object_class->nickname = "invert";
	object_class->description = _( "invert an image" );

	vips_arithmetic_set_format_table( aclass, vips_bandfmt_invert );

	aclass->process_line = vips_invert_buffer;
}

static void
vips_invert_init( VipsInvert *invert )
{
}

int
vips_invert( VipsImage *in, VipsImage **out, ... )
{
	va_list ap;
	int result;

	va_start( ap, out );
	result = vips_call_split( "invert", ap, in, out );
	va_end( ap );

	return( result );
}
