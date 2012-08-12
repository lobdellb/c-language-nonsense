/*  Include file for vector math library

Author:  Bryce Lobdell
Date:  12/14/98

*/


struct vector
	{
	float i,j,k;
	};

#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long

#define vectorsub(v1,v2) vectoradd(v1,negate(v2))

float mag(struct vector v);
struct vector scalaradd(struct vector vin,float scalar);
struct vector vectoradd(struct vector v1,struct vector v2);
struct vector negate(struct vector v);
struct vector scalarmult(struct vector v,float scalar);
struct vector scalardiv(struct vector v,float scalar);
struct vector crossproduct(struct vector v1,struct vector v2);
float dotproduct(struct vector v1,struct vector v2);
struct vector unit(struct vector v);
struct vector vectordiv(struct vector v1,struct vector v2);
struct vector vectormult(struct vector v1,struct vector v2);
