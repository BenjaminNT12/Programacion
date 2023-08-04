

#include <iostream>

int main(void){
    char x,a,b,c;

    a = 0x64;
    b = 0xC8;
    c = 0x32;

    x = (a + b) + c;

    std::cout << "El resultado es: " << std::hex << (int)x << std::endl;

    return 0;
}
