/*  This program performs gauss elimination to solve
	 a system of linear equasions.

Author:  Bryce Lobdell
Section:  1
Filename:  gauss.c
Date:  3/26/99
Magic Number:  99906




I took a slighly differnt approach to this program than the instructions
suggested.  I though it would be fun, more usefull, and not a whole lot
more difficult to make a solution that didn't have to hard code the matrix
size.  The gauss_matrix() function can take any size of matrix, defined at
run time, not compile time...

*/









/* formula for finding a value in a matrix of know size
and a pointer the the matrix.

data[row][col]=*(pointer+row*(numberofrows)+col);

Example:
int bryce[6][8];
int *trent;
trent=&bryce[0][0];

bryce[3][4]=*(trent+8*3+4);

this type of thing lends itself very well to a de*fined
macro, but an uga told me that the grading script would
replace and de*fines with the size of the matrix the
program will operate on, so my only de*fine should be the
one that defines the size of the matrix.


I was later told that I could use defines here, but I
have already written all the code...
*/






/* Preprocessor directives, of course.  The matrix size that this
program will input and operate on is defined by MATRIXSIZE */
#include <stdio.h>
#define MATRIXSIZE 4

/*  Function prototypes */
int math_op(int rows,int cols,int loc,int direction,double *matrix);
void solve(int rows,int cols,double *matrix);
void disp_matrix(int rows,int cols,double *matrix);
void get_matrix(int rows,int cols,double *matrix);
void addrow_matrix(int rows,int cols,int row1,int row2,
						  double *matrix1,double *matrix2);
void mulrow_matrix(int rows,int cols,int row,double c,double *matrix);
int gauss_matrix(int rows,int cols,double *matrix);



/*  In this program the general form for a matrix function is:
	 func_matrix(rows,cols,op1,op2,...,matrix);
	 I tried to stick to this, but it didn't always work.
*/


/*  This function will display a matrix of size rows x cols
it takes a pointer to the first element to the &matrix[0][0].
It separates each element by a tab, so if any one number gets
too long, the output will be ugly, but with number that long,
a classier output function won't make it look that much
prettier */
void disp_matrix(int rows,int cols,double *matrix)
{
int count_row,count_col;

for (count_row=0;count_row<=rows-1;count_row++)
	{
	printf("\n\t");
	for (count_col=0;count_col<=cols-2;count_col++)
		printf("%.2lf\t",*(matrix+cols*count_row+count_col));

	printf("%.5lf\t",*(matrix+cols*count_row+count_col));
	}

printf("\n");
}


/*  This function inputs a matrix of size rows x cols.
It takes a pointer to the first element of the 2d
matrix.  It is made to call the last col in a row the
"constant".  It makes the input look pretty too.  FYI,
if the input is piped in from a file, there will be no
carraige returns, so all the input prompts will be on
one line.  But I did it this way, because it makes the
input prettier. */
void get_matrix(int rows,int cols,double *matrix)
{
int count_row,count_col;

printf("\n");
for (count_row=0;count_row<=rows-1;count_row++)
	{

	for (count_col=0;count_col<=cols-2;count_col++)
		{
		printf("Please enter the #%i coeffi"
		 "cient for the #%i equation > ",count_col+1,count_row+1);
		scanf("%lf",(matrix+cols*count_row+count_col));
		}

	printf("Please enter the right hand side"
			 " constant for the #%i equation > ",count_row+1);
	scanf("%lf",(matrix+cols*count_row+cols-1));

	}

printf("\n");
}



/*  This function adds row1 of matrix1 to row2 of matrix2 and
stores the result in row1 of matrix1.  No rocket science here. */
void addrow_matrix(int rows,int cols,int row1,int row2,
						  double *matrix1,double *matrix2)
{
int count_col;


for (count_col=0;count_col<=cols-1;count_col++)
	{
	*(matrix1+cols*row1+count_col)+=
	*(matrix2+cols*row2+count_col);
	}

if (rows==rows)
	rows=rows;

}



/*  This function multiplies row of matrix by constant c.  No
rocket science here either. */
void mulrow_matrix(int rows,int cols,int row,double c,double *matrix)
{
int count_col;

for (count_col=0;count_col<=cols-1;count_col++)
	{
	*(matrix+cols*row+count_col)*=c;
	}

/*  These lines prevent a compiler error.  I wanted to preserve
my standard form for a matrix function, so I did this instead
of changing the function parameters */
if (rows==rows)
	rows=rows;

}

/*
Performs gauss elimination on a matrix that is n by n+1
the extra column on the right side is the constants.  When
this function is done the left 3 columns will be the 3 by 3
identitiy matrix, and the right side will be the solution to
the linear system.  This function calls several other functions
like math_op() and solve() which in turn call add_row and mul_row.
There is some tricky stuff going on here, so I will try to
explain:
count_loc is which variable (row is currently being multiplied
and subtracted from all the other rows.
direction is a number the represents whether gauss is eliminated
in the downward direction of the upward direction.
retval is the error code for whether elimination is possible on
this matrix

The entire objective of that confusing looking while loop is
to make the function walk through the rows in the right order:

for a 3 by 4 (zero indexed)
row #:      0 1  2  1
direction:  1 1 -1 -1

for a 4 by 5
row #:      0 1 2  3  2  1
direction:  1 1 1 -1 -1 -1

What this means is that it will take the first row: matrix[0][] and
walk forware (direction=1) through the matrix eliminating the first
coefficient from every other row. Next it will go to the second row
and eliminate the second constant from all the equations in rows below
it.  It will do that until it gets to the bottom row, it which case it
walks up, removing the coresponding constant from all the rows above it.
(direction=-1)

This method seems a little more complicated that it should be, but this
is the way I understood.
*/
int gauss_matrix(int rows,int cols,double *matrix)
{
int count_loc,direction;
int retval;

direction=1;
count_loc=0;

while (1)
	{

	if (direction==-1 && count_loc==0)
		break;

	retval=math_op(rows,cols,count_loc,direction,matrix);

	count_loc+=direction;

	if (count_loc >= rows-1)
		direction=-1;

	}

solve(rows,cols,matrix);

return retval;
}


/*  This function takes a matrix with numbers only in the
diagonal from the upper left to the lower right, and makes
all the numbers equal to one, ie the identity matrix. */
void solve(int rows,int cols,double *matrix)
{
int count;
double multiplier;

for (count=0;count<=rows-1;count++)
	{

	multiplier=1.0/ *(matrix+cols*count+count);
	mulrow_matrix(rows,cols,count,multiplier,matrix);

	}

}


/*  This function is called by gauss_matrix().  It first finds the
value of "multiplier".  Multiplier is what matrix[loc][loc] will have to be
multiplied by so that it will be equal to matrix[count][loc].
Then it subtracts matrix[loc][loc] from matrix[count][loc] so
matrix[count][loc] is equal to zero (and eliminated).  It does this
for all the rows above loc (if direction =-1) or below loc (if
direction=1).  Direction Defines which way it goes. */
int math_op(int rows,int cols,int loc,int direction,double *matrix)
{
double multiplier;
int count,retval=0;


for (count=loc+direction;(count<=rows-1  && direction==1) ||
					(count>=0 && direction==-1);count+=direction)
	{
	if (*(matrix+cols*count+loc)!=0)
		{
		if (*(matrix+cols*loc+loc)==0)
		  {
		  retval=-1;
		  *(matrix+cols*loc+loc)+=1.0;
		  }

		multiplier= *(matrix+cols*count+loc)/
						*(matrix+cols*loc+loc);
		mulrow_matrix(rows,cols,loc,-1.0*multiplier,matrix);
		addrow_matrix(rows,cols,count,loc,matrix,matrix);

		}

	}

return retval;
}

/*  Ah ha, we are finally to the main function */
int main()
{
double matrix[MATRIXSIZE][MATRIXSIZE+1];
int retval;

get_matrix(MATRIXSIZE,MATRIXSIZE+1,&matrix[0][0]);

printf("The matrix you entered is:");
disp_matrix(MATRIXSIZE,MATRIXSIZE+1,&matrix[0][0]);

retval=gauss_matrix(MATRIXSIZE,MATRIXSIZE+1,&matrix[0][0]);

if (retval==0)
	{
	printf("\nThe solution to this system is:");
	disp_matrix(MATRIXSIZE,MATRIXSIZE+1,&matrix[0][0]);
	}
else
	printf("\nThe matrix you entered cannot be solved.\n");




return 0;
}
