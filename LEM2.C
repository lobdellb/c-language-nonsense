
#include "stdlib.h"
#include "graphics.h"
#include "math.h"
#include "stdio.h"
#include "time.h"
#include "unsigned.h"

int gmode=IBM8514HI,gdriver=IBM8514;

float realtime(uchar event);
int screen(void);

main()
{
screen();




return 0;
}


float realtime(uchar event)
{
float retval;
static float events[256];
retval=events[event];
events[event]=clock()-retval;
return retval;
}

int screen(void)
{
initgraph(&gdriver,&gmode,"C:\\TC\\BGI");



return 0;
}