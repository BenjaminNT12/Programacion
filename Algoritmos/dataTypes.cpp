#include<iostream>
#include <iomanip> 
// using namespace std;

int main()  {
    // YOUR CODE GOES HERE
    // Please take input and print output to standard input/output (stdin/stdout)
    // E.g. 'cin' for input & 'cout' for output
    int integrer = 0;
    long longer = 0;
    char caracter = 0;
    float flotante = 0.0;
    double doble = 0.0; 

    std::cin >> integrer;
    std::cin >> longer;
    std::cin >> caracter;
    std::cin >> flotante;
    std::cin >> doble;

    std::cout << integrer << std::endl;
    std::cout << longer << std::endl;
    std::cout << caracter << std::endl;
    std::cout << std::fixed << std::setprecision(3) << flotante << std::endl;
    std::cout << std::fixed << std::setprecision(9) << doble << std::endl;


    return 0;
}