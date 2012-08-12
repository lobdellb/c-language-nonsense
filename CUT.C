
/*
Command Line Switches

CUT source [dest] [/S:xxx] [/N:xxx] [/F:xxx]

/S:xxx		Cuts file int blocks of xxx size.
/N:xxx		Cuts file into xxx blocks.
/F			Cut onto disks.

*/

struct flags
{
uchar sized		:1;
uchar blocked	:1;
uchar disked	:1;

};

struct direct
{
uchar drive;
char path[128];
uchar mediatype;
ulong freespace;


};

struct status
{
uchar *filename;
struct direct source;
struct direct destination;
ulong filelenth;
ulong fileloc;
ulong blocksize;
uint num_blocks;
}


#include "stdio.h"
#include "unsigned.h"


int parse_command_line(int numargs,char *args[],struct flags *cmd_line,struct status *info);


main(int numargs,char *args[])
{
struct status info;
struct flags cmd_line;



}





int parse_command_line(int numargs,char *args[],struct flags *cmd_line,struct status *info)
{
uint loop;

*cmd_line.sized=0;
*cmd_line.blocked=0;
*cmd_line.disked=0;

*info.filename=args[1];



for (loop=1;loop<=numargs;loop++)
{



}






}
