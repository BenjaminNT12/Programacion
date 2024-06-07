#include <iostream>
using namespace std;


// Your code goes here


template <class T>
int index_of_largest(T a[], int sze)
{
    T max = a[0];
    int index_of_max = 0;
    for (int index = 1; index < sze; index++){
        if (a[index] > max)4
        {
            max = a[index];
            index_of_max = index;
        }
    }
    return index_of_max;
}


int main()  {
    int n;
    cout<<"Ingresa el numero de elementos del array: "<<endl;
    cin>>n;
    int arr_int[n];
    for(int i = 0; i < n; i++){
        cin>>arr_int[i];
    }
    int res = index_of_largest<int>(arr_int, n);
    cout<<"El maximo numero del array en int es :"<<res<<endl;
    
    cout<<"Ingresa el numero de elementos del array en doubles: "<< endl;
    cin>>n;
    double arr_double[n];
    for(int i = 0; i < n; i++){
        cin>>arr_double[i];
    }
    res = index_of_largest<double>(arr_double, n);
    cout<<"El maximo numero del array en double es :"<<res<<endl;
    return 0;
}
