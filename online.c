


#include "stdio.h"
#include "stdlib.h"


int main()
{
int count;

for (count=1;count<=255;count++)
    printf("ping 128.210.202.%d -c 1 > %d &\n",count,count);

return 0;
}  
