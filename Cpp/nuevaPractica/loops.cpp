// Try the following example in the editor below.

// You are given an integer N, print all the odd values, for all i, where 0 <= i < N. Print each values on a seperate line.

#include <iostream>

int main(void){
    int N = 0;

    std::cin>>N;

    for(int i = 0; i <= N; i++){
        if(i % 2 != 0){
            std::cout<<i<<std::endl;
        }else{
            continue;
        }
    } 

    return 0;
}