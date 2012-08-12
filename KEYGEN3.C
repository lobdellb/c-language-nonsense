

#include "stdio.h"
#include "stdlib.h"
#include "math.h"

#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long


#define RANDOM ((uchar)rand())


uchar select(uchar seed,uchar *lookup,uchar lenth);
int block(uchar *inbuff,uchar *outbuff);
int make(FILE *infile,FILE *outfile);
uint *getseeds(FILE *infile);
int file_error();

main(int numargs,char *args[])
{
FILE *infile;
FILE *outfile;

if (args[1]==NULL)
{
puts("You didn't specify a file name.");
exit(2);
}

printf("Creating key from:%s\n\n",args[1]);

outfile=fopen("key.fil","wb");

if (!outfile)
file_error();

infile=fopen(args[1],"rb");

if (!infile)
file_error();

getseeds(infile);

make(infile,outfile);

fcloseall();
}

int file_error()
{
perror("An error occured opening a file");
exit(1);
return 0;
}


uint *getseeds(FILE *infile)
{
int seed;

fread(&seed,2,1,infile);

srand(seed);

fseek(infile,0,SEEK_SET);

}

 
int make(FILE *infile,FILE *outfile)
{
uint loop;
uchar inbuff[256];
uchar outbuff[256];

puts("Making Key File");

for (loop=0;loop<=255;loop++)
{
printf(".");
fread(inbuff,256,1,infile);

block(inbuff,outbuff);

fwrite(outbuff,256,1,outfile);
}

puts("Done!\n");

return 0;
}



int block(uchar *inbuff,uchar *outbuff)
{
int loop;
uchar lookup[256];

for (loop=0;loop<=255;loop++)
lookup[loop]=loop;



for (loop=255;loop>=0;loop--)
*(outbuff+loop)=select(((float)RANDOM+*(inbuff+loop))/512*loop,lookup,loop);


return 0;
}


uchar select(uchar seed,uchar *lookup,uchar lenth)
{
uchar ret_val;

/*printf("%u\n",(uint)seed);*/

ret_val=*(lookup+seed);

*(lookup+seed)=*(lookup+lenth);

return ret_val;
}
