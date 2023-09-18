#include <iostream>
#include <stdlib.h>

using namespace std;

class tiempo{
    //atributos
    private:
        int horas, minutos, segundos;
    // metodo
    public:
        tiempo(int, int, int); // constructor
        tiempo(long);
        void hora(); // metodos
};

tiempo::tiempo(int _horas, int _minutos, int _segundos){
    horas = _horas;
    minutos = _minutos;
    segundos = _segundos;
};

tiempo::tiempo(long _tiempo){
    horas = int(_tiempo/3600);
    minutos = int((_tiempo - horas*3600)/60);
    segundos = _tiempo - (horas*3600 + minutos*60);
};

void tiempo::hora(){
    cout<<"La Hora es: "<<horas<<":"<<minutos<<":"<<segundos<<endl;
};

int main(){
    tiempo t1(2,5,2);
    tiempo t2(7503);

    t1.hora();
    t2.hora();
    system("pause");
    return 0;
}
