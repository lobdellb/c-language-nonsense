

#include "stdio.h"
#include "stdlib.h"

#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long


main()
{
char *filename;
ulong filelen;
uint loop1;
ulong loop2;
uchar *buffer;
FILE *infile,*outfiles;

filelen=filesize("doom1.zip");

infile=fopen("doom1.zip","rb");

for (loop1=1;loop1<=11;loop1++)
{
sprintf(filename,"doom%u.cut",loop1);
outfiles=fopen(filename,"wb");
 
for (loop2=1;loop2<=480000;loop2++)
fputc(fgetc(infile),outfiles);

fclose(outfiles);
}

outfiles=fopen("doom12.cut","wb");


for (loop2=1;loop2<=(filelen-5280000);loop2++)
{
fputc(fgetc(infile),outfiles);
}

fclose(infile);
fclose(outfiles);



}
