#include <stdio.h>

void increment(int a);
int table[ ]={0, 1, 7, 5, 0};

void main  ( void )
{
  int i = 4;
  int *index;

   while( i--)
    {
      if(table[i]) table[i]++;
   } 
   printf("%d,%d,%d,%d,%d \n", table[0],table[1],table[2],table[3],table[4]);
}