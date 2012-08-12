
#include "stdio.h"
#define ulong unsigned long
#define byte unsigned char

struct size
{
ulong occur;
byte num;
};

struct sort
{
ulong occurance;
byte place;
byte used;
};

main(int args,char *argsx[])
{
float ratio;
ulong num;
char *filename;
ulong totalbits,totalbytes,origin;
ulong bryce[256];
struct sort trent[256];
ulong loop,loop2;
struct size big,little;
FILE *infile;
filename=argsx[1];
for (loop=0;loop<=255;loop++)
bryce[loop]=0;
infile=fopen(filename,"rb");
if (infile==0)
exit(1);
loop=0;
do
{
bryce[getc(infile)]++;
} while (feof(infile)==0);

for (loop=0;loop<=255;loop++)
{
trent[loop].used=0;
trent[loop].occurance=bryce[loop];
} 

for (loop2=0;loop2<=127;loop2++)
{
big.occur=0;
big.num=0;
little.occur=4294967295;
little.num=0;
	for(loop=0;loop<=255;loop++)
	{
    if ((trent[loop].occurance<little.occur)&&trent[loop].used==0)
	{
	little.occur=trent[loop].occurance;
	little.num=loop;
	}
	if ((trent[loop].occurance>=big.occur)&&trent[loop].used==0)
	{
	big.occur=trent[loop].occurance;
	big.num=loop;
	}
	}
trent[little.num].place=loop2+1;
trent[little.num].used=1;
trent[big.num].place=255-loop2;
trent[big.num].used=1;
}
totalbits=0;
for (loop=0;loop<=255;loop++)
{
num=256-trent[loop].place;
/*totalbits+=(256-trent[loop].place)*trent[loop].occurance;*/
if (num<=1)
totalbits+=4*trent[loop].occurance;
else if (num<=2)
totalbits+=4*trent[loop].occurance;
else if (num<=4)
totalbits+=5*trent[loop].occurance;
else if (num<=8)
totalbits+=6*trent[loop].occurance;
else if (num<=16)
totalbits+=7*trent[loop].occurance;
else if (num<=32)
totalbits+=8*trent[loop].occurance;
else if (num<=64)
totalbits+=9*trent[loop].occurance;
else
totalbits+=10*trent[loop].occurance;
}
origin=filelength(fileno(infile));
totalbytes=totalbits/8;
printf("Original:%.0f, ",(float)origin);
printf("Compressed:%.0f, ",(float)totalbytes);
ratio=(float)totalbytes/(float)origin*100;
printf("Ratio:%.2f%%\n",ratio);
}
