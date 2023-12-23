// Try the following example in the editor below.

// Given an integer num denoting percentage of a student, calculate the grade according to the below rules:

// If num >= 90, grade A.
// If num >= 80, grade B.
// If num >= 70, grade C.
// If num >= 60, grade D.
// If num >= 50, grade E.
// Else grade will be F.
// Print a string consisting of single character denoting the grade.

// Sample Input

// 59
// Sample Output

// E


#include<iostream>

int main(void){
    int var = 0; 

    std::cin>>var;

    if(var >= 90)std::cout<<"A"<<std::endl;
    else if(var >= 80)std::cout<<"B"<<std::endl;
    else if(var >= 70)std::cout<<"C"<<std::endl;
    else if(var >= 60)std::cout<<"D"<<std::endl;
    else if(var >= 50)std::cout<<"E"<<std::endl;
    else std::cout<<"F"<<std::endl;
    return 0;
}