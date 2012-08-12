


#include "stdio.h"
#include "stdlib.h"
#include "dos.h"
#include "bios.h"
#include "unsigned.h"




main()
{
uint loop;
FILE *outfile;
void far *buffer;
void *nearbuff;
union REGS registers;
union REGS returnval;
struct SREGS segs;

nearbuff=malloc(5120);
buffer=farmalloc(5120);

registers.h.al=2;
registers.x.cx=10;
registers.x.dx=0;
registers.x.bx=FP_OFF(buffer);
segs.ds=FP_SEG(buffer);
int86x(0x25,&registers,&returnval,&segs);


for(loop=0;loop<=5119;loop++);
*((uchar *)nearbuff+loop)=*((uchar *)buffer+loop);

outfile=fopen("sectors.bin","wb");
fwrite(nearbuff,5120,1,outfile);
fclose(outfile);

}
