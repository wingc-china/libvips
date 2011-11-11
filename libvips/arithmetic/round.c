/* round.c --- various rounding operations
 *
 * 20/6/02 JC
 *	- adapted from im_abs()
 * 29/8/09
 * 	- gtkdoc
 * 	- tiny cleanups
 * 19/9/09
 * 	- im_ceil.c adapted to make round.c
 * 10/11/11
 * 	- redone as a class
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
 * VipsRound:
 * @in: input #VipsImage
 * @out: output #VipsImage
 * @round: #VipsOperationRound rounding operation to perform
 *
 * Round to an integral value.
 *
 * Copy for integer types, round float and 
 * complex types. Output type == input type.
 *
 * See also: #VipsCast.
 */

typedef struct _VipsRound {
	VipsUnary parent_instance;

	VipsOperationRound round;

} VipsRound;

typedef VipsUnaryClass VipsRoundClass;

G_DEFINE_TYPE( VipsRound, vips_round, VIPS_TYPE_UNARY );

static int
vips_round_build( VipsObject *object )
{
	VipsArithmetic *arithmetic = VIPS_ARITHMETIC( object );
	VipsUnary *unary = (VipsUnary *) object;

	/* Is this one of the int types? Degenerate to im_copy() if it
	 * is.
	 */
	if( unary->in &&
		vips_bandfmt_isint( unary->in->BandFmt ) ) {
		/* This isn't set by arith until build(), so we have to set
		 * again here.
		 *
		 * Should arith set out in _init()?
		 */
		g_object_set( arithmetic, "out", vips_image_new(), NULL ); 

		return( vips_image_write( unary->in, arithmetic->out ) );
	}

	if( VIPS_OBJECT_CLASS( vips_round_parent_class )->build( object ) )
		return( -1 );

	return( 0 );
}

#define LOOP( TYPE, OP ) { \
	TYPE *p = (TYPE *) in[0]; \
	TYPE *q = (TYPE *) out; \
	\
	for( x = 0; x < sz; x++ ) \
		q[x] = OP( p[x] ); \
}

#define SWITCH( OP ) { \
	switch( vips_image_get_format( im ) ) { \
        case VIPS_FORMAT_COMPLEX: \
	case VIPS_FORMAT_FLOAT: LOOP( float, OP ); break; \
	\
        case VIPS_FORMAT_DPCOMPLEX: \
	case VIPS_FORMAT_DOUBLE:LOOP( double, OP ); break;\
 	\
	default: \
		g_assert( 0 ); \
	} \
}

static void
vips_round_buffer( VipsArithmetic *arithmetic, PEL *out, PEL **in, int width )
{
	VipsRound *round = (VipsRound *) arithmetic;
	VipsImage *im = arithmetic->ready[0];

	/* Complex just doubles the size.
	 */
	const int sz = width * im->Bands * 
		(vips_bandfmt_iscomplex( im->BandFmt ) ? 2 : 1);

	int x;

	switch( round->round ) {
	case VIPS_OPERATION_ROUND_NEAREST:	SWITCH( VIPS_RINT ); break;
	case VIPS_OPERATION_ROUND_CEIL: 	SWITCH( ceil ); break;
	case VIPS_OPERATION_ROUND_FLOOR: 	SWITCH( floor ); break;

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

static const VipsBandFormat vips_bandfmt_round[10] = {
/* UC  C   US  S   UI  I   F   X   D   DX */
   UC, C,  US, S,  UI, I,  F,  X,  D,  DX 
};

static void
vips_round_class_init( VipsRoundClass *class )
{
	GObjectClass *gobject_class = G_OBJECT_CLASS( class );
	VipsObjectClass *object_class = (VipsObjectClass *) class;
	VipsArithmeticClass *aclass = VIPS_ARITHMETIC_CLASS( class );

	gobject_class->set_property = vips_object_set_property;
	gobject_class->get_property = vips_object_get_property;

	object_class->nickname = "round";
	object_class->description = _( "perform a round function on an image" );
	object_class->build = vips_round_build;

	vips_arithmetic_set_format_table( aclass, vips_bandfmt_round );

	aclass->process_line = vips_round_buffer;

	VIPS_ARG_ENUM( class, "round", 200, 
		_( "Round operation" ), 
		_( "rounding operation to perform" ),
		VIPS_ARGUMENT_REQUIRED_INPUT,
		G_STRUCT_OFFSET( VipsRound, round ),
		VIPS_TYPE_OPERATION_ROUND, VIPS_OPERATION_ROUND_NEAREST ); 
}

static void
vips_round_init( VipsRound *round )
{
}

int
vips_round( VipsImage *in, VipsImage **out, VipsOperationRound round, ... )
{
	va_list ap;
	int result;

	va_start( ap, round );
	result = vips_call_split( "round", ap, in, out, round );
	va_end( ap );

	return( result );
}
