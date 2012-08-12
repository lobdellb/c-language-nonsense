/*  ENGR 117    Project #3
Sorting and Searching and Pointers OH MY!

Author:  Bryce Lobdell
Date:  4/2/99
Filename: sortsrch.c
Section:  1

*/


#include <stdio.h>

#define MAXSIZE 100

void disp_array(int size,double array[])
{
int count;


for (count=0;count<=size-1;count++)
	printf("   %lf\n",array[count]);

}


/*  This function inputs an array of double floating
point numbers from the terminal terminated by a CTRL-D.
It returns the number of numbers inputed. */
int get_array(double array[])
{
int count=0;

while (scanf("%lf",&array[count])!=EOF)
	{
	count++;
	if (count>=100)
		{
		printf("Matrix is FULL, Ending Input");
		count--;
		break;
		}
	}

return (count+1);
}



void exchange(double *a,double *b)
{
double temp;

temp=*a;
*a=*b;
*b=temp;

}




void sort_array(int size,double array[])
{
int hit,count;


do {
	hit=0;

	for (count=0;count<=size-2;count++)
		if (array[count]<array[count+1])
			{
			hit++;
			exchange(&array[count],&array[count+1]);
			}

	} while (hit);

}


/*  Performs a binary search on the numbers in array.
Will return the location (zero indexed) of number if
number is found.  If number isn't found, it returns -1 */
int search(int size,double array[],double number)
{
int top=0,bottom=size-1,loc;


do {

	loc=top+bottom/2;

	if (array[loc] > number)
		top=loc-1;

	if (array[loc] < number)
		bottom=loc+1;


	if (top < bottom)
		{
		loc=-1;
		break;
		}

	} while (array[loc]!=number);

return loc;
}



void merge(int size1,double array1[],int size2,double array2[],double dest[])
{
int count,loc=0;


for (count=0;count<=size1;count++)
	{
	dest[loc]=array1[count];
	loc++;
	}

for (count=0;count<=size2;count++)
	{
	dest[loc]=array2[count];
	loc++;
	}

}











int main()
{
double array1[200],array2[100];
int size1,size2;

printf("Enter the 1st array terminated by a CTRL-D:\n");
size1=get_array(array1);

printf("\nYou entered these numbers:\n");
disp_array(size1,array1);
sort_array(size1,array1);
printf("\nIn descending order, these are the number you entered:\n");
disp_array(size1,array1);

printf("\n\nEnter the 2nd array terminated by a CTRL-D:\n");
size2=get_array(array2);
printf("\nYou entered these numbers:\n");
disp_array(size2,array2);
sort_array(size2,array2);
printf("\nIn descending order, these are the number you entered:\n");
disp_array(size2,array2);




return 0;
}
