
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
ulong primes[6543];
uint current=0;

primes[0]=1;
primes[1]=2;

fprintf(stderr,"Input Maximum:  ");
scanf("%lu",&length);

time(&starttime);

for (dividend=1;dividend<=(ulong)length;dividend++)
	{
	flag=0;

		maxnum=sqrt(dividend);
		for (divisor=1;divisor<=6543;divisor++)
			if (primes[divisor]<=maxnum)
				if (dividend%primes[divisor]==0)
					{
					flag=1;
					divisor=maxnum;
					}
				else
					{}
			else
				divisor=6543;


	if (flag==0)
		{
		printf("%lu\n",dividend);
		if (current<=6543)
			{
			primes[current]=dividend;
			current++;
			}
		}

	}

time(&stoptime);

fprintf(stderr,"Operation Time:  %ld seconds\n",stoptime-starttime);

return 0;
}
