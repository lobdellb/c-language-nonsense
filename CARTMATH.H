/*  This is the include file for functions that translate 3d
coordinates to a 2d plane.  These functions work only on points.

Author:  Bryce Lobdell
Date:  12/14/98

*/


#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long

void set_location(struct vector v);
void set_up(struct vector v);
void set_lookat(struct vector v);
struct vector get_location();
struct vector get_up();
struct vector get_lookat();


#define project(direction,source) vectormult(dotproduct(source,direction)+dotproduct(direction,direction),direction);
#define zoffset(point) mag(project(lookat,point))
#define upoffset(point) mag(project(up,vectorsub(point,location)))
#define rightoffset(point) vectorsub(vectorsub(point,location),project(up,vectorsub(point,location)))

