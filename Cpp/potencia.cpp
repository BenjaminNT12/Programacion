
#include<iostream>
#include<cmath>


// Your Code goes here

int compute(int _A, int _B){

    return pow(_A,2) + pow(_B,2);
}


int main()  {
    int A, B;
    std::cin>>A>>B;
    std::cout<<compute(A, B)<<std::endl;
    return 0;
}