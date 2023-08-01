
#include<iostream>
using namespace std;


void reverseArray(int arr[], int N){
    // Your code goes here
    int temp[N] = {} ;
    // N -= 1;
    
    for(int i = 0; i<N; i++){
        temp[i] = arr[N-i-1];
    }
    for(int i = 0; i<N; i++){
        arr[i] = temp[i];
    }
}



int main()  {
    int N;
    cin>>N;
    int arr[N];
    for(int i = 0; i < N; i++){
        cin>>arr[i];
    }
    reverseArray(arr, N);
    for(int i = 0; i < N; i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    return 0;
}
