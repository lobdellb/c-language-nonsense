
#include "stdio.h"
#include "time.h"
#include "math.h"

#define uchar unsigned char
#define ulong unsigned long
#define uint unsigned int


main()
{
ulong dividend,divisor;
uchar flag;
time_t starttime,stoptime;
ulong maxnum;
ulong length;

fprintf(stderr,"Input Maximum:  ");
scanf("%lu",&length);

time(&starttime);

for (dividend=1;dividend<=(ulong)length;dividend++)
	{
	flag=0;

	if (dividend%2!=0)
		{
		maxnum=sqrt(dividend);
		for (divisor=3;divisor<=maxnum;divisor+=2)
			if (dividend%divisor==0)
				{
				flag=1;
				divisor=maxnum;
				}
		}
	else
	 if (dividend!=2)
		flag=1;

	if (flag==0)
		printf("%lu\n",dividend);

	}

time(&stoptime);

fprintf(stderr,"Operation Time:  %ld seconds\n",stoptime-starttime);

return 0;
}
