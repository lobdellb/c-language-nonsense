/* Include files */

#include "graphics.h"
#include "unsigned.h"

/* Structures */

struct point3d {
int x;
int y;
int z;
};

struct point2d {
uint x;
uint y;
};

struct vector {
uint p1;
uint p2;
};



/* Constants */

#define PI 3.141592653
#define E 2.718281828
#define REAL_X 1024
#define REAL_Y 768
#define XMIN -32768
#define XMAX 32768
#define YMIN -24576
#define YMAX 24576



/* Global Variables */

struct point3d vp;
struct point3d points[8];
strict vector lines[12];



/* Functions */

void coord_trans(int *x,int *y)
{
*x=((*x/XMAX)+1)*(REAL_X/2);
*y=((*y/YMAX)+1)*(REAL_Y/2);

}


void setup_graph()
{
int gmode;
int gdriver;
int retval;

gdriver=IBM8514;
gmode=IBM8514HI;


initgraph(&gdriver,&gmode,"c:\\programs\\tc\\bgi\\");
}


void map3dpoints(struct point3d *inpoints,struct point2d *outpoints,uint quantity)
{
int temp;
uint loop;

for (loop=0;loop<=quantity;loop++)
	{
	temp=(((inpoints+loop)->x)-vp.x)/(((inpoints+loop)->z)-vp.z);
	(outpoints+loop)->x=temp*((inpoints+loop)->z)+vp.x-(vp.z*temp);
	temp=(((inpoints+loop)->y)-vp.y)/(((inpoints+loop)->z)-vp.z);
	(outpoints+loop)->y=temp*((inpoints+loop)->z)+vp.y-(vp.z*temp);
	}



}


void setup_data()
{
vp.x=0;
vp.y=0;
vp.z=32768;

points[0].x=-16000;
points[0].y=-12000;
points[0].z=10000;
points[1].x=16000;
points[1].y=-12000;
points[1].z=10000;
points[2].x=16000;
points[2].y=12000;
points[2].z=10000;
points[3].x=-16000;
points[3].y=12000;
points[3].z=10000;
points[4].x=-16000;
points[4].y=-12000;
points[4].z=20000;
points[5].x=16000;
points[5].y=-12000;
points[5].z=20000;
points[6].x=16000;
points[6].y=12000;
points[6].z=20000;
points[7].x=-16000;
points[7].y=12000;
points[7].z=20000;


lines[0].p1=0;
lines[0].p2=1;
lines[1].p1=1;
lines[1].p2=2;
lines[2].p1=2;
lines[2].p2=3;
lines[3].p1=3;
lines[3].p2=0;
lines[4].p1=4;
lines[4].p2=5;
lines[5].p1=5;
lines[5].p2=6;
lines[6].p1=6;
lines[6].p2=7;
lines[7].p1=7;
lines[7].p2=4;
lines[8].p1=0;
lines[8].p2=4;
lines[9].p1=1;
lines[9].p2=5;
lines[10].p1=2;
lines[10].p2=6;
lines[11].p1=3;
lines[11].p2=7;


}

void display(uint quanity);
{
uint loop;

for(loop=0;loop<=quantity;loop++)
	{






}



main()
{
setup_graph();
setup_data();




}




