


#include "stdio.h"



main()
{
FILE *fp;
unsigned int loop;

fp=fopen("blank.fil","wb");

for (loop=0;loop<=50000;loop++)
	fputc(0,fp);

fclose(fp);


}