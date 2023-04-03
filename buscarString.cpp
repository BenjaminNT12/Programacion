#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

string trama1 = "DVPDL,1398604000,50000,0.000000,-0.000000,-0.000000,-0.003,0.017,0.002,100*79 $DVEXT,T,X,0310,89.5,69.3,290.9,0,-0.073,0.35,-0.158,0.302,-0.000426945,0.001465221,0.050,0.500257,-0.290460,0.644365,0.500170,19,19,48,25,T,T,T,T,-0.0103,-0.0228,0.2731,-0.0607,0.371,0.391,0.371,0.371,*57 DVEXT,T,X,0310,89.9,69.3,290.9,0,-0.067,0.35,-0.144,0.295,-0.000427010,0.001465353,0.050,0.500257,-0.290460,0.644365,0.500170,19,19,48,25,T,T,F,T,-0.0086,-0.0169,0.0000,-0.0608,0.371,0.391,-1.000,0.371,*65";

string extractor(string trama1, int num_val, string inicio ="$DVEXT,T,X,0310", char separador = ',');


int main(){
    string tFinal;

    tFinal = extractor(trama1, 6);

    cout<<"final "<<tFinal<<endl;
    return 0;

};


string extractor(string trama1, int num_val, string inicio, char separador){
  int pos = 0,init = 0, end_pos = 0;
  int i = 0, occurrence = 0, len = 0;
  string tramaFinal;

  num_val += 1;
  pos = trama1.find(inicio);
  if(pos != -1){
    init = pos + inicio.size();
    end_pos = init;
    for(i = 0;i < num_val ;i++){
      end_pos = trama1.find(separador, end_pos + 1);
      if (init != -1){
        occurrence ++;
      }
      if(occurrence == (num_val-1)){
        len = end_pos - init;

        tramaFinal = trama1.substr(init+1, len-1);
        return(tramaFinal);
        break;
      }
    };
  }
  return("error");
}
