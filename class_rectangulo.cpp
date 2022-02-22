#include <iostream>
#include <stdlib.h>

using namespace std;

class rectangulo{
    private:
        int largo;
        int ancho;
    public:
        rectangulo(int, int);
        void perimetro();
        void area();
};

rectangulo::rectangulo(int _largo, int _ancho){
    largo = _largo;
    ancho = _ancho;
};

void rectangulo::perimetro(){
    cout<<"perimetro rectangulo "<<largo*2+ancho*2<<endl;
};

void rectangulo::area(){
    cout<<"Area rectangulo "<<largo*ancho<<endl;
};

int main(){
    rectangulo r1(2,3);
    rectangulo r2 = rectangulo(5,5);

    r1.area();
    r1.perimetro();
    r2.area();
    r2.perimetro();
    system("pause");
    return 0;
};
