
#include "stdio.h"
#include "stdlib.h"
#include "dos.h"
#include "dir.h"
#include "string.h"
#include "errno.h"

#define NOERROR 0
#define BADDIRPATH 1
#define MEMORY 2
#define FILEOPEN 3
#define NAMELEN 4
#define HELP 5

#define BUFFERSIZE 16384

#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long


struct found_file {
	char name[13];
	int date;
	int time;
	char attrib;
	long size;
	struct found_file *next;
	};


struct dual_ptr {
	struct found_file *firstdir;
	struct found_file *seconddir;
	};



void fileopenerror(FILE *retval);
void checksearch(void);
void memoryerror(int retval);
char *unparse_name(char *path,char *name);
struct found_file *makelist(char *name);
FILE *openmsg();
void file_work(char *source,char *dest,struct found_file *file);
void copy(FILE *source,FILE *destination,ulong size);
struct dual_ptr *compare(struct found_file *firstdir,struct found_file *seconddir,FILE *msg);
void printlist(struct found_file *firstdir,struct found_file *seconddir);
void select_files(char *sourcedir,char *destdir,struct found_file *list);
void change_chrono(FILE *source,FILE *destination);
