
#include "graphics.h"
#include "unsigned.h"

int gdriver,gmode;


void translat(float *x,float *y)
{
*x=(*x-10)*640;
*y=(*y-10)*480;
}




main()
{
float x,y,x2,y2;
gdriver=VGA;
gmode=VGAHI;

initgraph(&gdriver,&gmode,"c:\\programs\\tc\\bgi");

for(x=-10;x<=10;x+=0.1)
{
y=x*x;
x2=x;
y2=y;
translat(&x2,&y2);
putpixel((int)x2,(int)y2,14);

}

for(x=0;x<=100000000;x++)
y=1;


closegraph();
}