/***********************************************************************

   All important Code of attendance = 5635A

   Solution to ENGR117 lab assignment #7, given 4-02-98, on
   Gaussian Elimination for solving simultaneous linear equations.

   Programmed by :   Allen Kocher
   Begin Date    :   3-24-99
   End Date      :   4-06-99

***********************************************************************/

/***********************************************************************

   PREPROCESSOR ITEMS

***********************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define NUM_EQNS 3

/***********************************************************************

   FUNCTION PROTOTYPES

***********************************************************************/

/***********************************************************************

   GLOBAL VARIABLES

***********************************************************************/

/***********************************************************************

   BEGIN MAIN

***********************************************************************/

int main (void)
{
   int r,c,p,n=NUM_EQNS;
   double x[NUM_EQNS][NUM_EQNS+1],pivot;

/*   system("clear");

***********************************************************************

   INPUT BLOCK

***********************************************************************/

   printf("You have storage for %d equations in %d unknowns.\n",n,n);
   printf("\n\n");
   for(r=0; r <= n-1; ++r)
   {
      for(c=0; c <= n-1; ++c)
      {
	 printf("Please enter the #%d coefficient of ",c+1);
	 printf("the #%d equation > ",r+1);
	 scanf ("%lf",&x[r][c]);
      }
      printf("Please enter the right hand side constant for ");
      printf("the #%d equation > ",r+1);
      scanf ("%lf",&x[r][n]);
   }
   printf("\n\n\n");

/***********************************************************************

   DIAGONAL NORMALIZING AND UPPER AND LOWER DIAGONAL "CLEARING"

***********************************************************************/
// p is the broader sence of column.  (Used for the diagonal)
   for (p=0; p <= n-1; ++p) 
   {
// Finds if any of the diaginal coeffecients are zero.
      printf("\n%7.5f", x[p][p]);
      if(x[p][p] != 0)
      {
// Assigns nonzero diaginal point to pivot.
	 printf("hi1\n");
	 pivot= x[p][p];
// Divids all coeffecients and constant in order to make pivot 1.
			for(c=0; c <= n; ++c)
			{
	    printf("BRYCE:  x[%i][%i]=%7.4lf     c=%i\n",p,p, x[p][p],c);
		 x[p][c] /= pivot;
/*	    goto bug;
		 bugs:*/
	 }
// Sets column under the diagonal zero.
	 printf("\n");
	 if (p+1 <= n)
	 {
	    printf("hi3\n");
	    for(r= p+1; r <= n-1; ++r)
	    {
	       printf("hi4\n");
	       for(c=0; c <= n; ++c)
	       {
	       	  printf("hi5\n");
	       	  x[r][c] -= x[r][p] * x[p][c]; 
	       }	  
	    }
	 }
      }
      else
      {
	 printf("The equations given result in a non-invertible ");
	 printf("matrix.\n\n");
	 break;
      }
   }

/***********************************************************************

   OUTPUT BLOCK

***********************************************************************/

	bug:

	for(r=0; r <= n-1; ++r)
	{
		for(c=0; c <= n; ++c)
			printf("%10.4f", x[r][c]);
		printf("\n");
	}
//   printf("\n\n\n");
 /*	if (p <= 2) goto bugs;
	return 0; */
return 0;
}

/*
You have storage for 3 equations in 3 unknowns.


Please enter the #1 coefficient of the #1 equation > Please enter the #2 coefficient of the #1 equation > Please enter the #3 coefficient of the #1 equation > Please enter the right hand side constant for the #1 equation > Please enter the #1 coefficient of the #2 equation > Please enter the #2 coefficient of the #2 equation > Please enter the #3 coefficient of the #2 equation > Please enter the right hand side constant for the #2 equation > Please enter the #1 coefficient of the #3 equation > Please enter the #2 coefficient of the #3 equation > Please enter the #3 coefficient of the #3 equation > Please enter the right hand side constant for the #3 equation > 



2.00000hi1
 2.0000
    1.0000   12.0000    0.0000    6.0000
    2.0000    1.0000    0.0000    1.0000
    0.0000    2.0000    1.0000    1.0000

hi3
hi4
hi5
hi5
hi5
hi5
hi4
hi5
hi5
hi5
hi5

1.00000hi1
 1.0000
    1.0000   12.0000    0.0000    6.0000
    0.0000    1.0000    0.0000    1.0000
    0.0000    2.0000    1.0000    1.0000

hi3
hi4
hi5
hi5
hi5
hi5

1.00000hi1
 1.0000
    1.0000   12.0000    0.0000    6.0000
    0.0000    1.0000    0.0000    1.0000
    0.0000    0.0000    1.0000    1.0000

hi3
    1.0000   12.0000    0.0000    6.0000
    0.0000    1.0000    0.0000    1.0000
    0.0000    0.0000    1.0000    1.0000
enad240-025.cc.purdue.edu% */
