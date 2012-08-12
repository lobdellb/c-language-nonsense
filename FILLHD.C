 

#include "stdio.h"
#include "dos.h"
#include "stdlib.h"
#include "string.h"


#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long

#define CHDIR_ERR		0
#define RMDIR_ERR		1
#define NAME_ERR		2
#define DEL_ERR			3
#define SET_ATTR_ERR	4


uchar FA_DELETE=(FA_NORMAL|FA_ARCH);

int extended_error_info(void);
char *file_list(void);
int intro(char *directory,uchar ask);
int verify(char *directory);
int handle_error(int error_code);
int kill_dir(char *directory);
int del_star(void);
int go(char *directory);
int command(char *command[],int num_args);

main(int numargs,char *args[])
{
uchar ask;

ask=command(args,numargs);

verify(args[1]);

intro(args[1],ask);



go(args[1]);

}

int help(void)
{
printf("PRUNE.EXE		Copyright (c)	1995  Bryce Lobdell\n");
printf("Command Line:   PRUNE name [/all] [/s] [/h] [/r] [/u]\n");
printf("\nname:			The name of the directory to delete.\n");
printf("/s,h,r:			Deletes SYSTEM, HIDDEN, or READ-ONLY files.\n");
printf("/all:			Performs the function of /s /h & /r.\n");
printf("/u:			Doesn't ask for confirmation to delete the directory.\n\n");

exit(0);
return 0;
}

int command(char *command[],int num_args)
{
uchar def_ret=0;
uchar loop;
extern uchar FA_DELETE;

if (strstr(command[1],"?")!=NULL)
help();


for (loop=2;loop<=num_args;loop++)
{
command[loop]=strupr(command[loop]);


if (strstr(command[loop],"/ALL")!=NULL)
FA_DELETE=FA_DELETE|FA_RDONLY|FA_SYSTEM|FA_HIDDEN;

if (strstr(command[loop],"/U")!=NULL)
FA_DELETE=FA_DELETE|FA_SYSTEM;

if (strstr(command[loop],"/S")!=NULL)
FA_DELETE=FA_DELETE|FA_SYSTEM;

if (strstr(command[loop],"/H")!=NULL)
FA_DELETE=FA_DELETE|FA_HIDDEN;

if (strstr(command[loop],"/U")!=NULL)
def_ret=1;

}

return def_ret;
}



int go(char *directory)
{
int tmp;

kill_dir(directory);

tmp=chdir("..");
if (tmp!=0)
handle_error(CHDIR_ERR);

tmp=rmdir(directory);
if (tmp!=0)
handle_error(CHDIR_ERR);

return 0;
}

int kill_dir(char *directory) 
{

int counter;
int tmp;
struct find_t dir;



tmp=chdir(directory);
if (tmp!=0)
handle_error(CHDIR_ERR);

printf("Pruning:	%s\n",strupr(directory));

del_star();


tmp=_dos_findfirst("*.*",FA_DIREC,&dir);

while (tmp==0)
{

if ((strstr(dir.name,"..")==NULL)&&(FA_DIREC==(dir.attrib&FA_DIREC))&&(strstr(dir.name,".")==NULL))    
{

kill_dir(dir.name);

tmp=chdir("..");
if (tmp!=0)
handle_error(CHDIR_ERR);

tmp=rmdir(dir.name);
if (tmp!=0)
handle_error(CHDIR_ERR);
}

tmp=_dos_findnext(&dir);
}

}





int del_star(void)
{
extern uchar FA_DELETE;
int tmp;
struct find_t file;

tmp=_dos_findfirst("*.*",FA_DELETE,&file);

while (tmp==0)
{
tmp=dos_setfileattr(file.name,FA_NORMAL);
if (tmp!=0)
handle_error(SET_ATTR_ERR);
tmp=remove(file.name);
if (tmp!=0)
handle_error(DEL_ERR);
tmp=_dos_findnext(&file);
}
if (errno!=2)
return 0;
}





int intro(char *directory,uchar ask)
{
char response[2];
puts("Tree Pruner--Copyright 1995 by Bryce Lobdell\n");

if (ask==0)
{
printf("Confirm deletion of %s.   [y,N]:",strupr(directory));
fgets(response,2,stdin);
if (strstr(strupr(response),"Y")==NULL)
{

printf("Quitting\n");
exit(0);
}

}

return 0;
}



int handle_error(int error_code)
{
switch (error_code)
{
	case CHDIR_ERR:
	{
    perror("Cannot change directory");
    exit(1);
    }
    case RMDIR_ERR:
    {
    perror("Cannot remove directory");
    exit(2);
    }
    case NAME_ERR:
    {
    printf("Invalid Name.");
	exit(3);
    }
    case DEL_ERR:
	{
    perror("Cannot delete file");
    exit(4);
	}
    case SET_ATTR_ERR:
    {
    perror("Cannot overide attribute");
    exit(5);
    }
}

    return 0;
}


int verify(char *directory)
{
struct find_t verify_dir;
int tmp;
tmp=_dos_findfirst(directory,FA_DIREC,&verify_dir);
if (tmp!=0)
handle_error(NAME_ERR);
else
return 0;
}


void copy(FILE *infile,FILE *outfile)
{