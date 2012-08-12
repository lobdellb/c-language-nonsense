
#include "math.h"
#include "stdio.h"
#include "stdlib.h"

main()
{
double pi,pix;
int odd_even=1;
float curnum=3;
pi=1;
printf("Calculating Pi\n");
do
{
pix=pi;
if (odd_even==1)
{
pi-=1/curnum;
odd_even=0;
}
else
{
pi+=1/curnum;
odd_even=1;
}
curnum+=2;
} while (pi!=pix);
printf("Done!\n");
pi=pi*4; 
printf("Pi=%.19f\n",pi);
}
