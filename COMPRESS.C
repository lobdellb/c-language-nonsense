
/* Includes */
#include "stdio.h"
#include "stdlib.h"
#include "huffman.h"

/* Macros */
#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long

#define BLOCKSIZE 512



main(int numargs,char *args[])
{
FILE *infile,*outfile;
int ret_val;

infile=fopen(args[1],"rb");
outfile=fopen(args[2],"wb");

huffman(infile,outfile);
}
