
#include "stdio.h"

#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long


typedef struct
{
uchar index;
uchar byte;
} sort;

#define swap(x,y) {long z;z=x;x=y;y=z;}

int read_file(FILE *infile,sort *data);
int make(FILE *infile,FILE *outfile,sort *data);
int sortx(sort *data);
int file_error(void);
int write_file(FILE *outfile,sort *data);

main(int numargs,char *args[])
{
sort data[256];
FILE *infile;
FILE *outfile;

infile=fopen(args[1],"rb");
if (!infile)
file_error();

outfile=fopen("dekey.fil","wb");
if (!outfile)
file_error();


make(infile,outfile,data);

}

int file_error(void)
{
perror("A error occured opening files");
exit(1);

return 0;
}
 
int sortx(sort *data)
{
uchar flag=1;
int loop;

while (flag)
	{
	flag=0;
	
	for (loop=0;loop<=254;loop++)
		{
		if ((data+loop)->byte>(data+loop+1)->byte)
			{
            swap((data+loop+1)->byte,(data+loop)->byte);
            swap((data+loop+1)->index,(data+loop)->index);
			flag=1;
			} 
		
        }
	
	}


}

int make(FILE *infile,FILE *outfile,sort *data)
{
int loop;

for (loop=0;loop<=255;loop++)
{
read_file(infile,data);


sortx(data);

write_file(outfile,data);

}



}


int read_file(FILE *infile,sort *data)
{
int loop;

for (loop=0;loop<=255;loop++)
{
(data+loop)->index=loop;
(data+loop)->byte=fgetc(infile);
}

return 0;

}


int write_file(FILE *outfile,sort *data)
{
int loop;

for (loop=0;loop<=255;loop++)
putc((data+loop)->index,outfile);

return 0;

}
