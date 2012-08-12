

#include "stdio.h"


main()
{
FILE *bryce;
char buffer[256];
int x;

bryce=fopen("com2","wb");

for(x=0;x<=10;x++)
{
scanf("%s",buffer);
fprintf(bryce,"%s\n",buffer);

} 


}
