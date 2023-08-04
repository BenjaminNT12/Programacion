#include <stdio.h>

void f(int **p){…}

void main(void)
 {
  int *pi;
  f(&pi);
 }/* Begin of file */