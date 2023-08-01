
#include<iostream>
#include<math.h>
//using namespace std;


void solve(int *A, int *B){
    int A_val, B_val;
    
    A_val = *A+*B;
    B_val = abs(*A-*B);
    *A = A_val;
    *B = B_val;
    
}




int main()  {
    int A, B;
    int *pA = &A, *pB = &B;
    std::cin>>A>>B;
    solve(pA, pB);
    std::cout<<A<<std::endl;
    std::cout<<B<<std::endl;
    return 0;
}
