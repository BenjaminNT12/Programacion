#include <stdio.h>

#define SUM(A, B) A + B

// (0xD4,4,3)
unsigned getbits(unsigned x, int p, int n)
 {
 	return (x >> (p+1-n)) & ~(~0 << n);
 }
// 11010100
//
// 00110101  & 00000111
// 00000101
int main(void)
{
    int x;
    x = 5;

    if(x>10){
        if(x>20) x--;
    }else x++;
    printf("%d \n", x);
}