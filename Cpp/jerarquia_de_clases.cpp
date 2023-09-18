#include <iostream>
#include <stdlib.h>


// persona
    // empleado
    // estudiante
            // universitario

using namespace std;

class Persona{
    private:
        string nombre;
        int edad;
    public:
        Persona(string, int);
        ~Persona();
        void mostrarPersona();
};

Persona::Persona(string _nombre, int _edad){
    nombre = _nombre;
    edad = _edad;
}

Persona::mostrarPersona(){
    cout<<"Nombre: "<<nombre<<endl;
    cout<<"Edad: "<<edad<<endl;
}

class Empleado : public Persona{
    public:
        float sueldo;
    private:
        Empleado(string, int, float);
        void mostrarEmpleado();
};

Empleado::Empleado(string _nombre, int _edad, float _sueldo):Persona(_nombre, _edad){
    mostrarPersona();
    sueldo = _sueldo;
}

void Empleado::mostrarEmpleado(){
     mostrarPersona();
     cout<<"sueldo"<<endl;
}
