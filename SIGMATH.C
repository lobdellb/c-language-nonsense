/*  This program does some handy handling of significant
figures that is handy for physics  152

Author:  Bryce Lobdell
Email:  blobdell@purdue.edu
Date:  2/11/99

*/



#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#include "ctype.h"
#include "string.h"


#define SPACE 32
#define PERIOD 46
#define J 74
#define P 80
#define E 69
#define M 77
#define C 67
#define D 68
#define A 65
#define S 83
#define I 73
#define R 82
#define Q 81
#define HELP 63

#define FALSE 0
#define TRUE 1
#define NULL 0

int errorflag=FALSE;


char gospel[2000]=
{"	Jesus replied, \"I am the bread of life.  No one\n\
who comes to me will ever be hungry again.  Those who\n\
believe in me will never thirst.  But you haven't\n\
believed in me even though you have seen me.  However,\n\
those the Father has given me will come to me, and I\n\
will never reject them.  For I have come down from\n\
heaven to do the will of God who sent me, not to do\n\
what I want.  And this is the will of God, that I\n\
should not lose even one of all those he has given me,\n\
but that I should raise them to eternal life at the\n\
last day.  For it is my Father's will that all who see\n\
his Son and believe in him should have eternal - that I\n\
should raise them at the last day.\"  (John 6:35-40)\n\n"};

#define uchar unsigned char
#define uint unsigned int
#define ulong unsinged long

struct number
	{
	double val;
	double delta;
	int sig;
	};



char *strupr(char *string)
{
int counter;
char *index;

counter = 0;

do {
	index = string + counter;
	if ((*index >= 97) && (*index <= 122))
		*index -= 32;
	counter++;
	} while (*index != 0);

return string;
}




void shownum(struct number num)
{
printf("Val = %.12le \xF1 %.8le\n\n",num.val,num.delta);

}




/* This function gets data from the keyboard, does some error checking
and counts the number of significant figures involved */
struct number getnum(void)
{
struct number num;
char input[200];
char *work;

printf("Number: ");
scanf("%s",input);

work=isnumok(input);
if (work)
	{

	sscanf(input,"%lf",&(num.val));
	printf("Uncertainty: ");
	scanf("%lf",&(num.delta));


	}
else
	{
	printf("\"%s\"\" is Not a valid Number.  Ignored\n",input);
	errorflag=TRUE;
	}
return num;
}


/*  returns the number of significant figures in an inputed number */
int count_sigfigs(char *data)
{
int retval,decimal,len;

if (isnumok(data))
	{
	decimal=find_decimal(data);





}


int isnumok(char *data)
{

int charcheck(data);




}


/*  This function returns a pointer to the givin string wherever the first
none-space character is.  It also inserts a \0 character wherever the next
space character is.  In short, it removes trailing and preceeding spaces.
It will return the NULL pointer if there is a space between any of the
characters in the middle.  The purpose of this function is to prepare the
string for being parsed by the "findfigs" function and by sscanf() */
char *spacecheck(char *data)
{





}




/*  This function finds the location of the decimal point in a number
in string form */
int find_decimal(char *data)
{
int count,len,retval;

len=strlen(data)-1;

for (count=0;count<=len;count++)
	if (*(data+count)==PERIOD)
		{
		retval=count;
		count=len;
		}

return reval;
}




/*  This function tests to see whether a string contains acceptable
characters for numeric input.  1 (true) =ok 0 (false)=notok */
int charcheck(char *data)
{
int count,len,retval;

retval=0;
len=strlen(data)-1;

/* remember to test this function for completion of the string */
for (count=0;count<=data;count++)
	if( (*(data+count)<=57 ||
		  *(data+count)>=48 ||
		  *(data+count)==101 ||
		  *(data+count)==69 ||
		  *(data+count)==43 ||
		  *(data+count)==45 ||
		  *(data+count)==46 )
				retval=1;

return retval;
}



void clear_vars(struct number *first,int n)
{
int count;

for (count=0;count<=n-2;count++)
	{
	(*(first+count)).val=0;
	(*(first+count)).delta=0;
	(*(first+count)).sig=0;
	}

}




void help(void)
{

printf("Command Help:\nE  Enter Data to Variable\nM  Multiply\nD  Divide\n");
printf("A  Add\nS  Subtract\nP  Print Variable Data\nI  Inverse\n");
printf("R  Root\nC  Clear Screen\nQ  Quit\n\n");

}


struct number mult(struct number num1,struct number num2)
{
struct number num;

num.val = num1.val * num2.val;
num.delta = num.val * ((num1.delta/num1.val) + (num2.delta/num2.val));

return num;
}





struct number div(struct number num1,struct number num2)
{
struct number num;

num.val = num1.val / num2.val;
num.delta = num.val * ((num1.delta/num1.val) + (num2.delta/num2.val));

return num;
}


struct number add(struct number num1,struct number num2)
{
struct number num;

num.val = num1.val + num2.val;
num.delta = num1.delta + num2.delta;

return num;
}


struct number sub(struct number num1,struct number num2)
{
struct number num;

num.val = num1.val - num2.val;
num.delta = num1.delta + num2.delta;

return num;
}



struct number inv(struct number num)
{

num.delta = (1 / num.val) * (num.delta / num.val);
num.val = 1 / num.val;

return num;
}


struct number root(struct number num)
{

num.delta = num.delta / (2 * sqrt(num.val));
num.val = sqrt(num.val);

return num;
}



int selectvar(void)
{
int varnum;
char varstr[20];
printf("Select a Variable (A to Z): ");
scanf("%s",varstr);
strupr(varstr);
varnum = (int)varstr[0];
varnum -= 65;

if ((varnum < 0) || (varnum > 25))
	varnum = -1;

return varnum;
}



main(void)
{
char command[20];
int quit,var1,var2,ans;
struct number variables[26];


clear_vars(variables,25);
quit = 1;

printf("PHYS 152 Uncertainty Math\n");
printf("Enter ? for help\n\n");

do {
	scanf("%s",command);
	strupr(command);

	switch((int)(command[0]))
		{
		case (P):
			{
			var1 = selectvar();
			if (var1 == -1)
				{
				printf("Not a valid Variable\n");
				break;
				}
			shownum(variables[var1]);
			break;
			}
		case (E):
			{
			var1 = selectvar();
			if (var1 == -1)
				{
				printf("Invalid Variable\n");
				break;
				}
			variables[var1] = getnum();
			break;
			}
		case (M):
			{
			printf("Select 1st operand, 2nd operand and Answer Variables\n");
			var1 = selectvar();
			var2 = selectvar();
			ans = selectvar();
			if ((var1 == -1) || (var2 == -1) || (ans == -1))
				{
				printf("Invalid Variable\n");
				break;
				}
			variables[ans] = mult(variables[var1],variables[var2]);
			shownum(variables[ans]);
			break;
			}
		case (D):
			{
			printf("Select 1st operand, 2nd operand and Answer Variables\n");
			var1 = selectvar();
			var2 = selectvar();
			ans = selectvar();
			if ((var1 == -1) || (var2 == -1) || (ans == -1))
				{
				printf("Invalid Variable\n");
				break;
				}
			variables[ans] = div(variables[var1],variables[var2]);
			shownum(variables[ans]);
			break;
			}
		case (A):
			{
			printf("Select 1st operand, 2nd operand and Answer Variables\n");
			var1 = selectvar();
			var2 = selectvar();
			ans = selectvar();
			if ((var1 == -1) || (var2 == -1) || (ans == -1))
				{
				printf("Invalid Variable\n");
				break;
				}
			variables[ans] = add(variables[var1],variables[var2]);
			shownum(variables[ans]);
			break;
			}
		case (S):
			{
			printf("Select 1st operand, 2nd operand and Answer Variables\n");
			var1 = selectvar();
			var2 = selectvar();
			ans = selectvar();
			if ((var1 == -1) || (var2 == -1) || (ans == -1))
				{
				printf("Invalid Variable\n");
				break;
				}
			variables[ans] = sub(variables[var1],variables[var2]);
			shownum(variables[ans]);
			break;
			}
		case (I):
			{
			printf("Select operand and Answer Variables\n");
			var1 = selectvar();
			ans = selectvar();
			if ((var1 == -1) || (ans == -1))
				{
				printf("Invalid Variable\n");
				break;
				}
			variables[ans] = inv(variables[var1]);
			shownum(variables[ans]);
			break;
			}
		case (C):
			{
			printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
			break;
			}
		case (R):
			{
			printf("Select operand and Answer Variables\n");
			var1 = selectvar();
			ans = selectvar();
			if ((var1 == -1) || (ans == -1))
				{
				printf("Invalid Variable\n");
				break;
				}
			variables[ans] = root(variables[var1]);
			shownum(variables[ans]);
			break;
			}
		case (Q):
			{
			quit = 0;
			break;
			}
		case (J):
			{
			printf("%s\n",gospel);
			break;
			}
		case (HELP):
			{
			help();
			break;
			}
		default:
			printf("Invalid Command\n");
		}

	} while (quit);


return 0;
}
