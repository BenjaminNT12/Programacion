// ou have to input 5 space-separated values: int, long, char, 
// float and double respectively.

// Print each value on a new line in the same order it is received 
// as input. Note that the floating point value should be correct up 
// to 3 decimal places and the double to 9 decimal places.

#include <iostream>
#include <iomanip>

int main(void){
    int entero = 0;
    long largo = 0;
    char caracter = 0;
    float flotante = 0;
    double doble = 0.0;

    std::cin>>entero;
    std::cin>>largo;
    std::cin>>caracter;
    std::cin>>flotante;
    std::cin>>doble;

    std::cout<<entero<<std::endl;
    std::cout<<largo<<std::endl;
    std::cout<<caracter<<std::endl;
    std::cout<<std::fixed << std:: setprecision(3) <<flotante<<std::endl;
    std::cout<< std:: setprecision(6)<<doble<<std::endl;

    return 0; 
}