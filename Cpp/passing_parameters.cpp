
#include<iostream>
#include<cmath>
using namespace std;


// Your code goes here

void compute(int &_A, int &_B, int &_C){
    _A = pow(_A,3);
    _B = pow(_B,3);
    _C = pow(_C,3);
}


int main()  {
    int A, B, C;
    cin>>A>>B>>C;
    compute(A, B, C);
    cout<<A<<endl;
    cout<<B<<endl;
    cout<<C<<endl;
    return 0;
}