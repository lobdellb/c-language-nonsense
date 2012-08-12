/*  A simple benchmarking program that will run on any platform.

Author:  Bryce Lobdell
Date:  3/18/99
Filename:  bench.c

*/



#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long

#define LONGTEST (CLK_TCK*10)
#define MEDTEST (CLK_TCK*2)
#define SHORTTEST (CLK_TCK/2)


long intmath_short(clock_t length)
{
clock_t timer;
int test1=123,test2=456,test3=789;
long test4=987,test5=654,test6=321;
long count=0;

timer=clock();

timer+=length;

while (clock()<=timer)
	{
	count++;
	test1=test2+test3;
	test2=test3-test1;
	test3=test1*test2;
	test1=test3/test2;

	test4=test5+test6;
	test5=test6-test4;
	test6=test4*test5;
	test4=test6/test5;
	}

return count;
}




long intmath_long(clock_t length)
{
clock_t timer;
int test1=123,test2=456,test3=789;
long test4=987,test5=654,test6=321;
long count=0;

timer=clock();

timer+=length;

while (clock()<=timer)
	{
	count++;
	test1=test2+test3;
	test2=test3-test1;
	test3=test1*test2;
	test1=test3/test2;

	test4=test5+test6;
	test5=test6-test4;
	test6=test4*test5;
	test4=test6/test5;

	test1=test2+test3;
	test2=test3-test1;
	test3=test1*test2;
	test1=test3/test2;

	test4=test5+test6;
	test5=test6-test4;
	test6=test4*test5;
	test4=test6/test5;

	}

return count;
}









int main()
{
long s_test,l_test;
int seconds;
double s_freq,l_freq,s_period,l_period;

/*printf("Hey Look, I can print a floating point number!!!, %f\n",3.1415926535); */


s_test=intmath_short(LONGTEST);
l_test=intmath_long(LONGTEST);

seconds=(int)LONGTEST/CLK_TCK;

s_freq=(double)s_test/(double)seconds;
l_freq=(double)l_test/(double)seconds;
s_period=1/s_freq;
l_period=1/l_freq;

printf("Single Set Opps in %i Seconds:  %lu\n",seconds,s_test);
printf("Double Set Opps in %i Seconds:  %lu\n",seconds,l_test);

printf("\nSingle Set Opps per Second:  %.1lf\n",s_freq);
printf("Double Set Opps per Second:  %.1lf\n",l_freq);

printf("\nTime to do one loop (one math set):  %.9lf\n",s_period);
printf("Time to do one loop (two math sets):  %.9lf\n",l_period);

printf("\nAmmount of time it takes to do one set of math operations:  %.12lf\n",
																			l_period-s_period);
printf("Number of operations possible per seconds:  %.12lf\n",
																			1/(l_period-s_period));


return 0;
}





