#include <iostream>

class tiempo{
    private:
        int hora, minutos, segundos;
    public:
        tiempo(int, int, int);
        tiempo(long);
        void showHora();
};

tiempo::tiempo(int _horas, int _minutos, int _segundos){
    hora = _horas;
    minutos = _minutos;
    segundos = _segundos;
}

tiempo::tiempo(long _tiempo){
    hora = int(_tiempo/3600);
    minutos = int(_tiempo - hora*3600)/60;
    segundos = int(_tiempo - hora*3600 - minutos*60);
}

void tiempo::showHora(){
    std::cout<<"Hora :"<< hora << "Minutos: "<< minutos << "Segundos: "<< segundos<<std::endl;
}

int main(){
    tiempo T1(3, 34, 15);
    tiempo T2(31256);

    T1.showHora();
    T2.showHora();

    return 0;
}


