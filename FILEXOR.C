


#include "stdio.h"


#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long

main(int numargs,char *args[])
{
uint xornum;
uint loop;
uint bytes;
uint *ptr;

FILE *infile,*outfile;
ptr=&bytes;
printf("arg[1] =infile, arg[2]=outfile , arg[3]=xor number\n");
infile=fopen(args[1],"rb");
outfile=fopen(args[2],"wb");
xornum=atoi(args[3]);

while (!feof(infile))
{
fread(ptr,2,1,infile);
bytes=bytes^xornum;
fwrite(ptr,2,1,outfile);



}


fcloseall();




}
