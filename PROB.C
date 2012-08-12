


#include "math.h"
#include "stdio.h"

double factorial(double x);


main()
{
double x,y;
x=factorial(256);
y=pow(x,256);
printf("The value is:%e\n",y);

}

double factorial(double x)
{
if (x==1)
return 1;
else
{
x*=factorial(x-1);
return x;
}
}
