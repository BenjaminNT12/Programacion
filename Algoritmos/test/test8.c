#include <stdio.h>

int mystery(unsigned);

int main(void)
{
    unsigned x;
    
    printf("Enter an integer: ");
    scanf("%u", &x);
    printf("The result is %d, %b\n", mystery(x), x);
    return 0;
}

int mystery(unsigned bits)
{
    unsigned i, mask = 1 << 15, total = 0;
    
    // printf("Mask %b\n", mask);
    for (i = 1; i <= 16; i++, bits <<= 1)

        if((bits & mask) == mask){
            ++total;
            printf("Entro Bits %b & %b = %b \n", bits, mask, (bits & mask));

            printf("total = %d \n", total);
        }else{
            printf("Bits %b & %b = %b \n", bits, mask, (bits & mask));
        }
    return total % 2 == 0 ? 1 : 0;
}