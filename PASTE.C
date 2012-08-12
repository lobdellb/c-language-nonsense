


#include "stdio.h"
#include "unsigned.h"


main()
{
ulong filelen;
uint loop1;
ulong loop2;
FILE *infiles,*outfile;
char *filename;

filelen=filesize("doom12.cut");

outfile=fopen("doom1.zip","wb");


for (loop1=1;loop1<=11;loop1++)
{
sprintf(filename,"doom%u.cut",loop1);
 
infiles=fopen(filename,"rb");

for (loop2=1;loop2<=480000;loop2++)
{
fputc(fgetc(infiles),outfile);
}

fclose(infiles);
}

infiles=fopen("doom12.cut","rb");

for (loop2=1;loop2<=filelen;loop2++)
{
fputc(fgetc(infiles),outfile);
}
fclose(infiles);
fclose(outfile);




}
