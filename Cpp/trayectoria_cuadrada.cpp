#include <iostream>
#include <math.h>

using namespace std;

float trayectoria_cuadrada(float Tm ,float t_inicial, float t_final, float Ci, float pf, float xd[], float xdp[], float xdpp[]);

int main(int argc, char **argv){
    float T = 0.01;
    float xd[6000] = {0};
    float xdp[6000] = {0};
    float xdpp[6000] = {0};

    trayectoria_cuadrada( T, 0, 60, 0, 10, xd, xdp, xdpp);
    cout<< "xd= " <<xd[1]<< " xdp= " << xdp[1] << " xdpp= " << xdpp[1] << endl;

    return 0;
}

float trayectoria_cuadrada(float Tm ,float t_inicial, float t_final, float Ci, float pf, float xd[], float xdp[], float xdpp[]){
    unsigned int i = 0;
    float tf = 0;
    unsigned int pasos = 0;
    float t = t_inicial;

    pasos = (unsigned int)((t_final - t_inicial)/Tm);
    cout<<pasos<<endl;
    tf = t_final;   
    xd[0] = Ci;       

    for(i = 0; i < pasos ; i++){
        t += Tm; 
        cout<<t<<endl;

        xd[i+1] = Ci + pf*( 10*pow(t/tf, 3) - 15*pow(t/tf, 4) + 6*pow(t/tf, 5));
        xdp[i+1] = 0 + pf*( 30*(pow(t, 2)/pow(tf,3)) - 60*(pow(t, 3)/pow(tf,4)) + 30*(pow(t, 4)/pow(tf,5)) );
        xdpp[i+1] = (xdp[i+1] - xdp[i])/Tm;

        cout<< "xd= " <<xd[i+1]<< " xdp= " << xdp[i+1] << " xdpp= " << xdpp[i+1] << endl;
    }
    return 0.0;
}


