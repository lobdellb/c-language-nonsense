/*  This is library of functions that do vector math on stuff

Author:  Bryce Lobdell
Date:  12/14/98

*/

#include "math.h"
#include "vector.h"


/* Returns the magnitude of a vector. */
float mag(struct vector v)
	{
	return sqrt(v.i*v.i+v.j*v.j+v.k*v.k);
	}

struct vector scalaradd(struct vector vin,float scalar)
	{
	struct vector v;
	v.i=vin.i+scalar;
	v.j=vin.j+scalar;
	v.k=vin.k+scalar;
	return v;
	}

/* Adds two vectors together */
struct vector vectoradd(struct vector v1,struct vector v2)
	{
	struct vector v;
	v.i=v1.i+v2.i;
	v.j=v1.j+v2.j;
	v.k=v1.k+v2.k;
	return v;
	}

/* Multiplies the magnitude of a vector by -1 */
struct vector negate(struct vector v)
	{
	v.i=0-v.i;
	v.j=0-v.j;
	v.k=0-v.k;
	return v;
	}


/* Multiplies a vector by a scalar */
struct vector scalarmult(struct vector v,float scalar)
	{
	v.i=v.i*scalar;
	v.j=v.j*scalar;
	v.k=v.k*scalar;
	return v;
	}

/* Devides a vector by a scalar */
struct vector scalardiv(struct vector v,float scalar)
	{
	v.i=v.i/scalar;
	v.j=v.j/scalar;
	v.k=v.k/scalar;
	return v;
	}

/* Returns the cross product of two vectors
the process is icky and requires determinants
and ugly stuff like this */
struct vector crossproduct(struct vector v1,struct vector v2)
	{
	struct vector v;
	v.i=v1.j*v2.k-v1.k*v2.j;
	v.j=v1.k*v2.i-v1.i*v2.k;
	v.k=v1.i*v2.j-v1.j*v2.i;
	return v;
	}


/* Finds the dot product of two vectors */
float dotproduct(struct vector v1,struct vector v2)
	{
	float dp;
	dp=v1.i*v2.i+v1.j*v2.j+v1.k*v2.k;
	return dp;
	}


/* Finds the unit (length=1) vector for a givin vector */
struct vector unit(struct vector v)
	{
	return scalardiv(v,mag(v));
	}


/* Multiplies two vectors together */
struct vector vectormult(struct vector v1,struct vector v2)
	{
	struct vector v;
	v.i=v1.i*v2.i;
	v.j=v1.j*v2.j;
	v.k=v1.k*v2.k;
	return v;
	}

/* Divides two vectors together */
struct vector vectordiv(struct vector v1,struct vector v2)
  	{
	struct vector v;
	v.i=v1.i/v2.i;
	v.j=v1.j/v2.j;
	v.k=v1.k/v2.k;
	return v;
	}

