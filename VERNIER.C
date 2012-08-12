/* Program to implement vernier encryption
Author:  Bryce Lobdell
Login:  lobdellb
filename:  vernier.c
date:  11/5/98

*/

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define GOOD 0
#define WRONGARGS 1
#define BADPASSWD 2
#define FALSE 0
#define TRUE 1
#define uint unsigned int
#define uchar unsigned char
#define ulong unsigned long


char caps(char num)
{

if (num >= 65 && num <= 90)
	num+=32;

return num;
}

char alpha(char num)
{

num-=97;

return num;
}


char ascii(char num)
{
num+=97;
return num;
}


void setupkey(char *key)
{
uint keylength,loop;

keylength=strlen(key);

for (loop=0;loop<=keylength-1;loop++)
	{
	*(key+loop)=caps(*(key+loop));

	if (!(*(key+loop) >= 97 && *(key+loop) <= 122))
		{
		fprintf(stderr,"Bad Password\n");
		exit(BADPASSWD);
		}
	*(key+loop)=alpha(*(key+loop));
	}
}



int main(int numargs,void *args[])
{
char *key,nextchar;
uint keylength,keylocation;

key=args[1];
keylocation=0;

if (numargs != 2 || !strcmp(key,"--help"))
	{
	printf("Usage:  vernier KEY < INFILE > OUTFILE\n");
	exit(WRONGARGS);
	}

keylength=strlen(key)-1;
setupkey(key);

nextchar=fgetc(stdin);
while (nextchar != EOF)
	{
	nextchar=caps(nextchar);

	if (nextchar <= 122 && nextchar >=97)
		{
		nextchar=alpha(nextchar);
		nextchar+=*(key+keylocation);
		nextchar=nextchar%26;
		nextchar=ascii(nextchar);
		keylocation++;
		if (keylocation > keylength)
			keylocation=0;
		}
	putc(nextchar,stdout);
	nextchar=fgetc(stdin);
	}

return 0;
}
