#include <stdio.h>
#include <ctype.h>

main()

{
char one = 'A';
char two = '!';
char three = 'b';
char four = 'F';
char five = '8';
char six = ' ';
char seven = '+';

  if (isalpha(three))
    printf("\n\n  The result of isalpha(three) is %d.\n", three);

  if (!isdigit(five))
    printf("\n  The result of !isdigit(five) is %d.\n", five);
  
 


}
