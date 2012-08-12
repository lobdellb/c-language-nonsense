/* This is my test function for the graphics libraries
In this case, a 3d rotating cube
Author:  Bryce Lobdell
Date: 12/14/98

*/


struct point
	{
	float x,y;
   };


struct line
	{
	float x1,y1,z1,x2,y2,z2;
	};

/* Works like this cube[x][ 0   1   2   3   4   5]
									 x1  y1  z1  x2  y2  z2
*/
float cube[12][6]={	{-1,-1,-1,1,-1,-1},
							{1,-1,-1,1,1,-1},
							{1,1,-1,-1,1,-1},
							{-1,1,-1,-1,-1,-1},
							{-1,-1,-1,-1,-1,1},
							{-1,-1,1,-1,1,1},
							{-1,1,1,-1,1,-1},
							{1,-1,-1,1,-1,1},
							{1,-1,1,-1,-1,1},
							{1,-1,1,1,1,1},
							{1,1,1,-1,1,1},
							{1,1,-1,1,1,1}
						 };


#include "stdio.h"
#include "vector.h"
#include "cartmath.h"
#include "graphics.h"
#include "conio.h"

void printv(struct vector v)
	{
	printf("i=%f		j=%f		k=%f\n",v.i,v.j,v.k);
	}


#define SCRUP 0
#define SCRDOWN 480
#define SCRRIGHT 640
#define SCRLEFT 0

#define VIEWUP 2
#define VIEWDOWN -2
#define VIEWRIGHT 2
#define VIEWLEFT 2

#define XSCALE ((SCRRIGHT-SCRLEFT)/(VIEWRIGHT-VIEWLEFT))
#define YSCALE ((SCRUP-SCRDOWN)/(VIEWUP-VIEWDOWN))
#define XCENTER ((SCRRIGHT+SCRLEFT)/2)
#define YCENTER ((SCRUP+SCRDOWN)/2)
#define XCENTER_V ((VIEWRIGHT+VIEWLEFT)/2)
#define YCENTER_V ((VIEWUP+VIEWDOWN)/2)

struct point viewport(struct point l)
	{
	l.x=((l.x-XCENTER_V)/XSCALE)+XCENTER;
	l.y=((l.y-YCENTER_V)/YSCALE)+YCENTER;
	return l;
	}

#define SINX
#define COSX

struct vector rotatexy
	{





	}






main()
{
int gdriver=VGA,gmode=VGAHI;

initgraph(&gdriver,&gmode,"c:\\winprogs\\bc45\\bgi");


do {






} while (!kbhit());

closegraph();

return 0;
}


