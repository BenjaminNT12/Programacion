#include<iostream>
#include<cmath>

int main()  {
    float A = 12.56, B = 5.12;
    float cube_val = 0, sq_val = 0;
    // Print the sum of cube of both A and B, and store it in float variable named "cube_val"
    cube_val = std::pow(A,3)+std::pow(B,3);
    std::cout<<cube_val<<std::endl;
    // Print the square root of cube_val, and store it in float variable named "sq_val"
    sq_val = std::sqrt(cube_val);
    std::cout<<sq_val<<std::endl;
    // Print the sin of sq_val
    std::cout<<std::sin(sq_val)<<std::endl;
    return 0;
}