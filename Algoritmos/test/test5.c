#include <stdio.h>

#define SUM(A, B) A + B

// (0xD4,4,3)
unsigned getbits(unsigned x, int p, int n)
 {
    printf("%b \n", (x >> (p+1-n)));
 	return (x >> (p+1-n)) & ~(~0 << n);
 }
// 11010100
//
// 00110101  & 00000111
// 00000101
int main(void)
{
    int a;
// El resultado es 45 debido a que el macro no considera jerarquia de operaciones
    a = getbits(0xD4,4,3);
    printf( "El resultado es: %b \n", a) ;
}