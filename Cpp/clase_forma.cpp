#include <iostream>


class tiempo{
    private:
        int horas;
        int minutos;
        int segundos;
    public:
        tiempo(int, int, int);
        tiempo(long);
        void showHora();
        // ~tiempo();
};


tiempo::tiempo(int horas_, int minutos_, int segundos_){
    horas = horas_;
    minutos = minutos_;
    segundos = segundos_;
}

tiempo::tiempo(long tiempo){
    horas = int(tiempo/3600);
    minutos = int((tiempo - 3600*horas)/60);
    segundos = int((tiempo - 3600*horas - minutos*60));
}

void tiempo::showHora(){
    std::cout<<"Horas: "<<horas<<" Minutos: "<<minutos<<" Segundos: "<<segundos<<std::endl;
}

int main(){
    tiempo T1(3,15,34); 
    tiempo T2(34953); 

    T1.showHora();
    T2.showHora();

    return 0;
}