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
		break;
		}
	}

return count;
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
	loc=(top+bottom)/2;
	if (array[loc] > number)
		top=loc+1;

	if (array[loc] < number)
		bottom=loc-1;


	if (top > bottom)
		{
		loc=-1;
		break;
		}
	} while (array[loc]!=number);

return loc;
}


/*  This function does a zipper merge of two lists.  It assumes that both
lists of numbers are already sorted, and it assumes that enought memory is
already allocated for the two arrays combined. */
void merge(int size1,double array1[],int size2,double array2[],double dest[])
{
int loc1,loc2,loc;

loc1=loc2=loc=0;

do {

	if (loc1<=size1-1)
		{
		if (array1[loc1]>=array2[loc2])
			{
			dest[loc]=array1[loc1];
			loc++;
			loc1++;
			}
		}
	else
		{
		dest[loc]=array2[loc2];
		loc++;
		loc2++;
		}

	if (loc2<=size2-1)
		{
		if (array2[loc2]>array1[loc1])
			{
			dest[loc]=array2[loc2];
			loc++;
			loc2++;
			}
		}
	else
		{
		dest[loc]=array1[loc1];
		loc++;
		loc1++;
		}

   } while (loc1<size1 || loc2<size2);

}











int main()
{
double array1[MAXSIZE],array2[MAXSIZE],array3[MAXSIZE*2];
int size1,size2,location;
double value;

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


merge(size1,array1,size2,array2,array3);
printf("\nThese are the numbers you entered, merged and sorted:\n");
disp_array(size1+size2,array3);

printf("\nEnter value to locate (CTRL-D to end): ");
while (scanf("%lf",&value)!=EOF)
	{
	location=search(size1+size2,array3,value);
	if (location==-1)
		printf("Could not find %lf in the list.\n",value);
	else
		printf("Value: %lf was found at location: %i\n",
		                    array3[location],location+1);

   printf("Enter value to locate: ");
   } 

printf("\n");

return 0;

}
