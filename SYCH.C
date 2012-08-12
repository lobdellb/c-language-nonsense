
#include "c:\users\bryce\c\sych.h"


void fileopenerror(FILE *retval)
{
if (retval==NULL)
	{
	perror("Error Opening File");
	exit(FILEOPEN);
	}

}


void checksearch(void)
{

if (_doserrno==ENOENT)
	{
	puts("Bad Path or File Name");
	exit(BADDIRPATH);
	}

}





void memoryerror(int retval)
{
if (retval==NULL)
	{
	perror("Error Allocating Memory");
	exit(MEMORY);
	}

}

char *unparse_name(char *path,char *name)
{
char *temp;

temp=malloc(strlen(path)+strlen(name)+3);
memoryerror((int)temp);

strcpy(temp,path);
strcat(temp,".\\");
strcat(temp,name);

return temp;
}


struct found_file *makelist(char *name)
{
struct ffblk find;
int retval;
struct found_file *start,*current;


name=unparse_name(name,"*.*");

start=malloc(sizeof(struct found_file));
current=start;

retval=findfirst(name,&find,FA_RDONLY|FA_HIDDEN|FA_SYSTEM|FA_ARCH);

while (retval==NULL)
	{

	strncpy((*current).name,find.ff_name,13);
	(*current).date=find.ff_fdate;
	(*current).time=find.ff_ftime;
	(*current).attrib=find.ff_attrib;
	(*current).size=find.ff_fsize;

	retval=findnext(&find);
	if (retval==NULL)
		{
		(*current).next=malloc(sizeof(struct found_file));
		current=(*current).next;
		memoryerror((int)current);
		}
	else
		(*current).next=NULL;

	}

checksearch();

free(name);

return start;

}


FILE *openmsg(char *dir)
{
char *name;
FILE *fp;

name=unparse_name(dir,"duplicate.lst");

fp=fopen(name,"w");
fileopenerror(fp);

return fp;

}



void file_work(char *source,char *dest,struct found_file *file)
{
FILE *infile,*outfile;

source=unparse_name(source,(*file).name);
dest=unparse_name(dest,(*file).name);

fileopenerror(infile=fopen(source,"rb"));
fileopenerror(outfile=fopen(dest,"wb"));

copy(infile,outfile,(ulong)((*file).size));

fflush(outfile);

change_chrono(infile,outfile);

fclose(infile);
fclose(outfile);
free(source);
free(dest);

}


void copy(FILE *source,FILE *destination,ulong size)
{
uchar buffer[BUFFERSIZE];
ulong loop=0;


while (size>=loop+BUFFERSIZE)
	{
	fread(buffer,BUFFERSIZE,1,source);
	fwrite(buffer,BUFFERSIZE,1,destination);
	loop+=BUFFERSIZE;
	}

fread(buffer,size%BUFFERSIZE,1,source);
fwrite(buffer,size%BUFFERSIZE,1,destination);


}




struct dual_ptr *compare(struct found_file *firstdir,struct found_file *seconddir,FILE *msg)
{
struct found_file *firstcurrent,*secondcurrent,*temp;
int *firstlast,*secondlast;
struct dual_ptr newptrs;
uint flag=NULL;


firstlast=&(int)firstdir;
firstcurrent=firstdir;

while (firstcurrent!=NULL)
	{

	flag=NULL;
	secondlast=&(int)seconddir;
	secondcurrent=seconddir;


	while ((flag==NULL)&&(secondcurrent!=NULL))
		{

		if(strncmp((*firstcurrent).name,(*secondcurrent).name,12)==0)
			{
			if ( !(((*firstcurrent).size==(*secondcurrent).size) ||
			(((*firstcurrent).date==(*secondcurrent).date) &&
			((*firstcurrent).time==(*secondcurrent).time))) )
				{
				fprintf(msg,"Files not identical:  %s......",(*secondcurrent).name);
				fprintf(stdout,"Files not identical:  %s......",(*secondcurrent).name);
				}
			*secondlast=(int)((*secondcurrent).next);
			temp=secondcurrent;
			secondcurrent=(*secondcurrent).next;
			free(temp);

			*firstlast=(int)((*firstcurrent).next);
			temp=firstcurrent;
			firstcurrent=(*firstcurrent).next;
			free(temp);

			flag=1;
			}
		else
			{
			secondlast=&((int)(*secondcurrent).next);
			secondcurrent=(*secondcurrent).next;
			}

		}
	if (flag==NULL)
		{
		firstlast=&((int)(*firstcurrent).next);
		firstcurrent=(*firstcurrent).next;
		}
	}

newptrs.firstdir=firstdir;
newptrs.seconddir=seconddir;

return &newptrs;

}



void printlist(struct found_file *firstdir,struct found_file *seconddir)
{



puts("\n\n\nPrinting First Directory");

	while (firstdir!=NULL)
	{
	printf("%s\n",(*firstdir).name);
	firstdir=(*firstdir).next;

	}

puts("\n\n\nPrinting Second Directory");

	while (seconddir!=NULL)
	{
	printf("%s\n",(*seconddir).name);
	seconddir=(*seconddir).next;


	}



}

void select_files(char *sourcedir,char *destdir,struct found_file *list)
{



while (list!=NULL)
	{

	file_work(sourcedir,destdir,list);

	list=(*list).next;
	}

}




void change_chrono(FILE *source,FILE *destination)
{
union REGS inregs,outregs;

inregs.h.ah=0x57;
inregs.h.al=0;
inregs.x.bx=fileno(source);

int86(0x21,&inregs,&outregs);

inregs.h.al=1;
inregs.x.cx=outregs.x.cx;
inregs.x.dx=outregs.x.dx;
inregs.x.bx=fileno(destination);

int86(0x21,&inregs,&outregs);

}


void help()
{
puts("SYNCH.EXE-Synchronizes Files in Two Directorys");
puts("Copyright 1997 by Bryce Lobdell\n");
puts("Command Line:  SYNCH dir1 dir2");
puts("dir1/dir2=directorys to synchronize\n");
puts("A file called DUPLICATE.LST is left in dir1,");
puts("and it contains files with different dates and");
puts("times from the two directories.");
exit(HELP);

}


main(int numargs,char *args[])
{
struct found_file *firstdir,*seconddir;
FILE *infile,*outfile,*message;
struct dual_ptr *newptrs;

if ((strncmp("/?",args[1],2)==0)||(numargs==1))
	help();

message=openmsg(args[1]);

puts("Make File Lists");
firstdir=makelist(args[1]);
seconddir=makelist(args[2]);

puts("Finding Duplicates");
newptrs=compare(firstdir,seconddir,message);

firstdir=(*newptrs).firstdir;
seconddir=(*newptrs).seconddir;

puts ("\nCopying Files");
select_files(args[1],args[2],firstdir);
select_files(args[2],args[1],seconddir);

fclose(message);

 puts("Done");
return NOERROR;

}







