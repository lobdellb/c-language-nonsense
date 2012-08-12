
#include "stdio.h"
#include "bios.h"
#include "unsigned.h"

main()
{
uchar buffer[512];

int cmd,drive,head,track,sector,nsects,returnx;

cmd=3;
drive=0x80;
head=0;
track=0;
sector=1;
nsects=1;

returnx=biosdisk(cmd,drive,head,track,sector,nsects,buffer);

printf("Returned:%i\n",returnx);






}