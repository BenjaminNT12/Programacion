#include <stdio.h>

#define SUM(A, B) A + B

int main(void)
{
    int a;
// El resultado es 45 debido a que el macro no considera jerarquia de operaciones
    a = 2 * SUM(5 * 3, 6 + 3) * 3;
    printf( "El resultado es: %d \n", a) ;
}