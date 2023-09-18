#include <iostream>
#include <stdlib.h>

using namespace std;

class persona{
    private: // atributos
        int edad;
        string nombre;
    public: // metodos
        persona(int, string);//constructor
        void leer();
        void correr();
};

//constructor nos sirve para inicializar los atributos
persona::persona(int _edad, string _nombre){
    edad = _edad;
    nombre = _nombre;
};

void persona::leer(){
    cout<<"soy "<<nombre<<" y estoy leyendo "<<endl;
};

void persona::correr(){
    cout<<"soy "<<nombre<<" y estoy corriendo una maraton y tengo "<<edad<<endl;
};

int main(){

    persona p1 = persona(32, "Benjamin");
    persona p2 = persona(31, "Esbeydi");

    p1.correr();
    p2.correr();
    system("pause");
    return 0;
};
