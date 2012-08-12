

#include "stdio.h"
#include "unsigned.h"
#include "dos.h"
#include "alloc.h"


main()
{
int track;
int sector;
int head;
int retval;
uchar buffer[512];
FILE *outfile;

outfile=fopen("c:\defects.dat","w");



for (track=0;track<=30;track++)
	{
	for (sector=1;sector<=17;sector++)
		{
		for (head=0;head<=7;head++)
			{

			retval=biosdisk(2,0x80,head,track,sector,1,buffer);
			 puts(".");
			if (retval!=0)
				{
                                printf("Head:   %i     Track:   %i     Sector:   %i     Error:   %i\n",head,track,sector,retval);
				fprintf(outfile,"Head:   %i     Track:   %i     Sector:   %i     Error:   %i\n",head,track,sector,retval);
				}
			}

		}
	

	}


fclose(outfile);



}