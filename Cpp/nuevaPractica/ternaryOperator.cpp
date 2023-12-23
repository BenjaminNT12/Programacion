// Try the following example in the editor below.

// Given two integer x and y, using Conditional or Ternary expression, print “Robin” if the value of x is less than or equal to y else print “Rahul” (without quotes).

// Sample Input:

// x = 10
// y = 9
// Sample Output:

// Rahul

#include<iostream>

int main(void){
    int x = 0, y = 0;

    std::cin>>x;
    std::cin>>y;

    x <= y ? std::cout<<"Robin":std::cout<<"Rahul"<<std::endl;
    return 0;
}