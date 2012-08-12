
/****************************************************
*
*     Programmer: Nathaniel Canady
*
*     Student ID: 510-92-5422
*
*     Lab Division and Section: 0101
*
*     Lab #: 5
*
*     Program Description:
*
****************************************************/

#include <stdio.h>

main()
{
  int lowerbound;
  int upperbound;
  int i;
  
  
  printf("\nPlease enter the lower bound for your multiplication table:\n");
  scanf("%d",&lowerbound);

  printf("\nPlease enter the upper bound for your multiplication table:\n");
  scanf("%d",&upperbound);

  for (i = lowerbound; i <= upperbound; i++)
    printf("%2d\n",i);

  if (lowerbound >= upperbound)
    printf("\nSorry, the lower bound must be less than the upper bound.\n\n"); 



}
