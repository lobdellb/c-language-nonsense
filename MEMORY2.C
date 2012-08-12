

#include "stdio.h"
#include "dos.h"


#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long


main()
{
uint seg,segx;
FILE *outfile;
uint loop;
uchar buffer[16384];

outfile=fopen("memory.fil","wb");
printf("\n");

for(segx=0;segx<=63;segx++)
{

seg=segx*1024;

for(loop=0;loop<=16383;loop++)
	buffer[loop]=peekb(seg,loop);

fwrite(buffer,16384,1,outfile);

printf("Segment: %X\r",seg);


}

fclose(outfile);

return 0;

}
