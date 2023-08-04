
#include <stdio.h>

int main(void)
{
  int i,no=0;
  for( i = 0; i < 100; i++ ){
    if( i & 1 ){
        no ++;
        printf("entro: %d \n", i);
        
    }
  }
  printf("%d \n", no);

}