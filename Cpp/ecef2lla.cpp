#include <iostream>
#include <math.h>

#define iteraciones (int)1000

using namespace std;

float* ecef2lla(float _x, float _y, float _z);

int main(void){
    double x   = 1345.660;
    double y   = -4350.891;
    double z   = 4452.314;

    float* _lla;

    _lla = ecef2lla(x, y, z);

    cout<<_lla[0]<<","<<_lla[1]<<","<<_lla[2]<<endl;
    return 0;
}

float* ecef2lla(float _x, float _y, float _z){
    unsigned int i          = 0;
    float Ni[iteraciones]   = {0.0};
    float phi0[iteraciones] = {0.0};
    float h[iteraciones]    = {0.0};
    float a                 = 6378137;
    float b                 = 0.0;
    float f                 = 0.0;
    float e                 = 0.0;
    float p                 = 0.0;
    float lambda            = 0.0;
    float theta             = 0.0;
    static float lla[3]     = {0.0};

    h[0] = 0.0;
    f = 1/((float)298.257223563);
    b = a*(1-f);
    p = sqrt(pow(_x,2) + pow(_y,2));
    e = sqrt((pow(a,2)-pow(b,2))/pow(a,2));
    phi0[0] = atan(_z/(p*(1-pow(e,2))));

    for(i = 0; i<999; i++){
        Ni[i] = (a/sqrt(1 - pow(e, 2)* pow( sin(phi0[i]), 2)));
        h[i + 1] = (p/(cos(phi0[i]))-Ni[i]);
        phi0[i + 1] = atan(_z/p*(1-(pow(e,2)*(Ni[i]/(Ni[i]+h[i+1])))));
    }
    lambda = atan(_y/_x);
    theta = atan((_z*a)/(p*b));

    lla[0] = phi0[i];
    lla[1] = lambda;
    lla[2] = theta;

    return lla;
}
