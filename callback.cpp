#include <iostream>

using namespace std;

int suma(int a ,int b){
    return a+b;
}

int resta(int a, int b){
    return a-b;
}

void operacion(int(* funcion)(int,int), int _a, int _b){
    int resultado = 0;
    resultado = funcion(_a, _b);
    cout<<resultado<<endl;
}

int main(){

    operacion(suma,10, 20);
    operacion(resta,10, 5);
    system("pause");
    return 0;
}
