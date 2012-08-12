
#include "stdio.h"


main(int args,char *argsx[])
{
FILE *file,*outfile;
unsigned int count[256];
int loop;
printf("%s\n",argsx[1]);
file=fopen(argsx[1],"rb");
outfile=fopen("histgram.fil","w");

for(loop=0;loop<=256;loop++)
        count[loop]=0;


do
{
count[getc(file)]++;
} while (feof(file)==0);
for (loop=0;loop<=255;loop++)
printf("%u\n",*(count+loop));


fcloseall();

}
