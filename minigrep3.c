/*  Engr117 lab8

"strings strings strings"

This is a very simple grep program.


Author:  Bryce Lobdell
Login:  lobdellb
Section:  sec1
Date:  4/10/99

*/



/* Preprocessor directive.... */
#include <stdio.h>


/*  This function inputs a whole line from stdin until a
linefeed is encounted.  It is stored in buffer.  scanf
with the %s flag will only read until it finds a space, and
that isn't acceptable for this assignment.  This function
will return EOF when it recieves and end of file, and there
isn't any other data in the buffer. */
int Getline(char *Buffer)
{
/*  Ascii is the inputed character (return value from getchar
    Count is the current position in the buffer
    Retval is the value that will be returned (either EOF or 0) */
int Ascii, Count=0, Retval=0;

/*  Will loop until a new line or a EOF is reached */
while (((Ascii = getchar()) != '\n') && (Ascii != EOF))
   {
   *(Buffer + Count) = (char) Ascii;    /* stores stuff in buffer */
   Count ++;

   }

if ((Ascii == EOF) && (Count == 0))  /*returns eof ONLY if buffer is empty */
   Retval = EOF;

*(Buffer + Count) = '\0';   /*  Terminates the string */

return Retval;
}




/*  This function finds the length of a string.
Be carefull, because if string isn't terminated,
this will probably cause a seg fault. */
int Strlen(char *String)
{
int Count=0, Loc=-1;

/* loops until loc a \0 is reached (and loc is assigned a value) */
while (Loc == -1)
   {
   if (*(String + Count) == '\0')
   zLoc = Count;
   Count ++;
   }

return Loc;
}


/*  The main function (you probably didn't need me to tell you that...

search is a pointer to the string to be searched for
buffer is where strings will be read into from stdin
length is the length of the line of text current in the buffer
count,count2 are counters for a "for" loop
CharMatch is a flag that is = 1 until a difference is found (between strings)
Word Match is a flag that is set if CharMatch is still set to one after
            two strings are compared
len is the length of the search string */
int main(int Argc, char *Argv[])
{
char *Search, Buffer[256];
int Length, Count, Count2, WordMatch, CharMatch, Len;
Search = Argv[1];


Len = Strlen(Search);


if (Argc != 2)  /*  Error control */
   printf("Wrong Number of Command Line Arguments.\n");
else
   {


   while (Getline(Buffer) != EOF)  /* Loops until a EOF  */
   z{
   zLength = Strlen(Buffer);
   zWordMatch = 0;

   z/* outer loop goes through buffer and looks for the
   zfirst character in the first string. When it finds
   zit, it goes into the inner loop. */
   zfor (Count = 0; Count < Length; Count ++)
   zz{
   zzif (Buffer[Count] == *Search)
   zzz{
   zzzCharMatch = 1;

   zzz/*  The inner loop starts assuming that the
   zzzstrings are the same (Same =1) and if it finds
   zzzand characters that does match, it sets same=0. */
   zzzfor (Count2 = 0; Count2 < Len; Count2 ++)
   zzzzif (Buffer[Count + Count2] != *(Search + Count2))
   zzzzzCharMatch = 0;

   zzz}

   zzif (CharMatch)  /*  if no characters mismatch, prints whole line */
   zzz{
   zzzCharMatch = 0;
   zzzWordMatch = 1;
   zzz}
   zz}

   z/*  If the search string appears:  print the whole line */
   zif (WordMatch)
   zzprintf("%s\n", Buffer);

   z}


   }

/* bih-duh, bih-duh, bih-duh, thats all folks!  */

return 0;
}


