


#include "stdio.h"


main(int numargs,char *args[])
{
long money=2147483647;
long *write;
FILE *file;
int returnval;


puts("Jacob Houson's Mech Warrior Cheat");
puts("Copyright 1993 -- All rights reserved");
puts("\0");

file=fopen(args[1],"ab");

if (!file)
{
puts("Couldn't Open File!");
exit(1);
}

write=&money;

returnval=fseek(file,73,0);



returnval=fwrite(write,4,1,file);


puts("You are now loaded with cash.");


}
