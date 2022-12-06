#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

string trama1 = "$DVPDL,160401000,100000,0.000000,-0.000000,-0.000000,0.000,-0.000,-0.000,0*55 $DVEXT,F,X,3330,-1.8,2.4,259.5,-1175,0.000,0.00,-0.000,0.000,0.000000000,0.000000000,0.100,0.091711,0.019853,0.017436,-0.995435,25,25,25,25,F,F,F,F,0.0000,0.0000,0.0000,0.0000,-1.000,-1.000,-1.000,-1.000,*54";

string extractor(string trama1, int num_val, string inicio ="$DVEXT,T,X,0310", char separador = ',');

void string2dec (string str, float *dec){
  *dec = atof(str.c_str());
}

int main(){
    string tFinal;
    float tFinalDec;

    tFinal = extractor(trama1, 6, "$DVEXT");

    cout<<"final "<<tFinal<<endl;
    // string2dec("10",&tFinalDec);
    // cout<<"string a decimal "<<tFinalDec<<endl;
 
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

