

#include "stdio.h"
#include "stdlib.h"


main(int num_args,char *args[])
{
FILE *in,*out;
unsigned long in_lenth,vir_location,loop,vir_lenth;
in=fopen(args[1],"rb");
out=fopen(args[2],"wb");
in_lenth=filesize(args[1]);
vir_location=atol(args[3]);
fseek(in,vir_location,0);
vir_lenth=in_lenth-vir_location;

for(loop=0;loop<=vir_lenth;loop++)
putc(getc(in),out);

fcloseall();
}
