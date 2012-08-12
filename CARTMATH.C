/*  This file contains functions that translate 3d coordinates to a
2d plane.  These functins work only on points.

Author:  Bryce Lobdell
Date:  12/14/98

*/


#include "math.h"
#include "vector.h"
#include "cartmath.h"

struct vector location;
struct vector up;
struct vector lookat;


void set_location(struct vector v)
	{
	extern struct vector location;
	location.i=v.i;
	location.j=v.j;
	location.k=v.k;
	}

void set_up(struct vector v)
	{
	extern struct vector up;
	up.i=v.i;
	up.j=v.j;
	up.k=v.k;
	}

void set_lookat(struct vector v)
	{
	extern struct vector lookat;
	lookat.i=v.i;
	lookat.j=v.j;
	lookat.k=v.k;
	}


struct vector get_location()
	{
	extern struct vector location;
	return location;
	}

struct vector get_up()
	{
	extern struct vector up;
	return up;
	}

struct vector get_lookat()
	{
	extern struct vector lookat;
	return lookat;
	}


