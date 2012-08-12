


#include "stdio.h"
#include "unsigned.h"


main()
{
FILE *fp;
uint loop;
uint loop2;
uint storeval;
uchar portmap[16384];


fp=fopen("portmap.fil","wb");

for (loop2=0;loop2<=3;loop2++)
	{

	storeval=16384*loop2;

	for (loop=0+storeval;loop<=16383+storeval;loop++)
		{
		portmap[loop-storeval]=inportb(loop);
		if (loop%16==0)
			printf("Portnumber:  %X\r",loop);
		}

	fwrite(portmap,16384,1,fp);

	}

fclose(fp);



return 0;


}