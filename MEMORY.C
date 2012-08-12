

#include "stdio.h"
#include "dos.h"


#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long


main()
{
ulong seg;
uint offset=0;
uchar far *data;
FILE *outfile;
char *buffer;
ulong loop;

buffer=(char *)malloc(32768);

if(buffer==0)
exit(1);

outfile=fopen("c:\\memory.fil","wb");
printf("\n\n\n");

for(seg=0;seg<=65536;seg++)
{
data=MK_FP(seg,offset);

for(loop=0;loop<=15;loop++)
buffer[loop]=*(data+loop);

printf("\rSegment:%u",seg);
fwrite(buffer,16,1,outfile);

}

fclose(outfile);

}
