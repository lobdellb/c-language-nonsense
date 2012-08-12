

#include "stdio.h"
#include "time.h"
#include "bios.h"

#define current_time clock()/100


main()
{
int loop,loop2,response;
int start_time;
printf("\nGo to Windows? [Y,n]?\n\n");
for (loop=3;loop>0;loop--)
{
start_time=current_time;
for (loop2=0;loop2<=33;loop2++)
printf("\b");
printf("Will go to Windows in %i seconds. ",loop);
do
{
if (bioskey(1))
response=bioskey(0);
if ((response==5465)||(response==5497)||(response==12654)||(response==12622))
{
break;
loop=5;
}
} while (current_time<=(start_time+1));
}
if ((response==5465)||(response==5497))
{
printf("\nEntering Windows!\n");
exit(0);
}
if ((response==12654)||(response==12622))
{
printf("\nStaying in DOS!\n");
exit(1);
}
printf("\nEntering Windows!\n");
exit(0);
}
