#include <iostream>
#include <stdlib.h>

using namespace std;

class persona{
    private:
        string nombre;
        int edad;
    public:
        persona(string, int);
        ~persona();
        void mostrarPersona();
};

class alumno: public persona{
    private:
        string cuenta;
        float calificacion;
    public:
        alumno(string, int, string, float);
        ~alumno();
        void obtenerAlumno();
};

persona::~persona(){};

alumno::~alumno(){};

persona::persona(string _nombre, int _edad){
    nombre = _nombre;
    edad = _edad;
}

alumno::alumno(string _nombre, int _edad, string _cuenta, float _calificacion):persona(_nombre, _edad){
    cuenta = _cuenta;
    calificacion = _calificacion;
}

void persona::mostrarPersona(){
    cout<<"nombre:" <<nombre<<endl;
    cout<<"edad: "<<edad<<endl;
}

void alumno::obtenerAlumno(){
    mostrarPersona();
    cout<<"cuenta :"<<cuenta<<endl;
    cout<<"calificacion :"<<calificacion<<endl;
}

int main(){
    alumno A1("Benjamin", 32,"140240",8);
    alumno A2("Esbeydi", 31,"1kjsuhd",10);

    A1.obtenerAlumno();
    A2.obtenerAlumno();
    A1.~alumno();
    A2.~alumno();
    system("pause");

    return 0;
}
