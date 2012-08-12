/*  Includes prototypes and structures for huffman.c and
associated source files.

Author:  Bryce Lobdell
Date:  4/9/99

*/

#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long


struct code
	{
	uchar ascii;
	ulong freq;
	ulong bitcode;

	};


struct node
	{
	struct node *backward;
	struct node *left;
	struct node *right;
	ulong freq;
	uchar ascii;
	};



