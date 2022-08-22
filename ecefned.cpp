#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


using namespace std;

float* ecef2ned(float _x, float _y, float _z, float lat, float lon, float h0){
    float R[3][3] = {{3},{3}};
    int i,k;
    float temp = 0;

    static float ned[3] = {0};
    float ecef[3] = {0};

    ecef[0] = _x;
    ecef[1] = _y;
    ecef[2] = _z;
    R[0][0] = -sin(lat)*cos(lon);
    R[0][1] = -sin(lat)*sin(lon);
    R[0][2] = cos(lat);

    R[1][0] = -sin(lon);
    R[1][1] = cos(lon);
    R[1][2] = 0;

    R[2][0] = -cos(lat)*cos(lon);
    R[2][1] = -cos(lat)*sin(lon);
    R[2][2] = -sin(lat);

    for(i = 0; i < 3; i++){
        temp = 0;
        for(k = 0; k < 3; k++){
             temp += R[i][k]*ecef[k];
             ned[i] = temp;
        }
    }
    return ned;
}

int main(void){
    double lat0 = 44.532;
    double lon0 = -72.782;
    double h0   = 1.699;
    double x    = 1345.660;
    double y    = -4350.891;
    double z    = 4452.314;

    float *NED;

    NED = ecef2ned(x, y, z, lat0, lon0, h0);

    cout<<NED[0]<<","<<NED[1]<<","<<NED[2]<<endl;
    return 0;
}
