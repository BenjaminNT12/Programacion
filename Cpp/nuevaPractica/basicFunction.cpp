// Try the following example in the editor below.

// Create a function named “compute” which takes two integer arguments A and B and returns an integer denoting A2 + B2. 

#include <iostream>
#include <cmath>

int compute(int A, int B){
    return std::pow(A,2)+std::pow(B,2);
}

int main(void){
    int A = 0, B = 0; 

    std::cin>>A>>B;    
    std::cout<<compute(A, B)<<std::endl;
    return 0;
}

























/*
int main()  {
    int A, B;
    cin>>A>>B;
    cout<<compute(A, B)<<endl;
    return 0;
}
*/




