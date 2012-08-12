

#include "stdio.h"



main()
{
int bryce;
for (bryce=0;bryce<=63;bryce++)
printf("Decimal:%3i, Binary:%8b   Decimal:%3i, Binary:%8b\n",bryce,bryce,bryce+64,bryce+64);
for (bryce=128;bryce<=191;bryce++)
printf("Decimal:%3i, Binary:%8b   Decimal:%3i, Binary:%8b\n",bryce,bryce,bryce+64,bryce+64);

}
