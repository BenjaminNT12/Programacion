// ******************************************************************************/
//                    VERSION PRELIMINAR PARA EL SISTEMA PARKUEST               //
// ******************************************************************************/
// Red neuronal Multicapa con entrenamiento en retropopagacion
// Red neuronal con funcionamiento supervisado
// NeuralNetwork_PARKUEST
// se deben especificar el numero de neuronas de la capa entrada
// se deben especificar el numero de neuronas en la capa oculta
// se deben especificar el numero de neuronas en la capa salida
//

#include <stdio.h>
#include <stdlib.h>
#include "PROCESSOR_dsPIC_PARKUEST.h"
#include "UART_dsPIC_PARKUEST.h"
#include "GenericTypeDefs.h"
#include "NeuralNetwork_PARKUEST.h"
#include <p33Exxxx.h>
#include <math.h>

ArtifitialNeuralNetwork NeuralNetwork  __attribute__ ((far)); //__attribute__((space(auto))); __attribute__((space(ymemory))); bytes maximos en variable alineacion

static double SigmoidalFunction(double alpha) {
    return (1 / (1 + exp(-1 * alpha)));
}

static void NumberOfWeightsNeeded(ArtifitialNeuralNetwork *NeuralNETWORK_A, unsigned char *NumberWEIGHT){
    unsigned char i = 0;
    unsigned char N_W = 0;

    for (i = 0; i < (NeuralNETWORK_A->N_Layers - 1); i++) {
        N_W += ((NeuralNETWORK_A->N_NeuronsIn_Layer[i]) * (NeuralNETWORK_A->N_NeuronsIn_Layer[i + 1]));
    }
    *NumberWEIGHT = N_W;
}

static void NumberOfOutputNeeded(ArtifitialNeuralNetwork *NeuralNETWORK_B, unsigned char *NumberOUTPUT){
    unsigned char i = 0;
    unsigned char N_O = 0;

    for (i = 1; i < NeuralNETWORK_B->N_Layers; i++) {
        N_O += NeuralNETWORK_B->N_NeuronsIn_Layer[i];
    }
    *NumberOUTPUT = N_O;
}

static unsigned char RetWeightNumber(ArtifitialNeuralNetwork *NeuralNETWORK_C, unsigned char NumberLayer) {
    unsigned char i = 0;
    unsigned char cont = 0;

    if (NumberLayer != 0) {
        for (i = 0; i < NeuralNETWORK_C->N_Layers && i < NumberLayer; i++) {
            cont += NeuralNETWORK_C->N_NeuronsIn_Layer[i] * NeuralNETWORK_C->N_NeuronsIn_Layer[i + 1];
        }
    } else if (NumberLayer == 0) {
        cont = 0;
    }
    return (cont);
}

static unsigned char RetOutputNumber(ArtifitialNeuralNetwork *NeuralNETWORK_D, unsigned char NumberLayer) {
    unsigned char i = 0;
    unsigned char cont = 0;

    if (NumberLayer != 1) {
        for (i = 1; i < NeuralNETWORK_D->N_Layers && i < NumberLayer; i++) {
            cont += NeuralNETWORK_D->N_NeuronsIn_Layer[i];
        }
    } else if (NumberLayer == 1 && NumberLayer == 0) {
        cont = 0;
    }
    return (cont);
}

static unsigned char RetErrorNumber(ArtifitialNeuralNetwork *NeuralNETWORK_E, unsigned char NumberLayer) {
    unsigned char i = 0;
    unsigned char cont = 0;

    if (NumberLayer != 1) {
        for (i = 1; i < NeuralNETWORK_E->N_Layers && i < NumberLayer; i++) {
            cont += NeuralNETWORK_E->N_NeuronsIn_Layer[i];
        }
    } else if (NumberLayer == 1 && NumberLayer == 0) {
        cont = 0;
    }
    return (cont);
}

static double OutputError_DERIVATIVE(double output, double target) {
    return ((target - output)*(1 - output) * output);
}

void Initialization_Weights(ArtifitialNeuralNetwork *NeuralNETWORK_F){
    unsigned char temp_N_neurons_weights = 0;
    unsigned char i = 0;

    NumberOfWeightsNeeded(NeuralNETWORK_F, &temp_N_neurons_weights);
    for (i = 0; i < temp_N_neurons_weights; i++) {
        NeuralNETWORK_F->NeuronsWeights[i] = (( (double)rand() * 2 ) / ( (double)RAND_MAX + 1 ) ) - 1;
    }
}

void Initialization_NeuralNetwork_PARKUEST(unsigned char number_layers, unsigned char *STRUCTURE_OF_NEURONS, ArtifitialNeuralNetwork *NeuralNETWORK_G){
    unsigned char i = 0;

    for (i = 0; i < number_layers; i++) {
        NeuralNETWORK_G->N_NeuronsIn_Layer[i] = (i != number_layers - 1) ? *STRUCTURE_OF_NEURONS++ : *STRUCTURE_OF_NEURONS;
    }

    NeuralNETWORK_G->N_Layers = number_layers;
    Initialization_Weights(NeuralNETWORK_G);
}

BOOL BackpropagationTraining_PARKUEST(ArtifitialNeuralNetwork *NeuralNETWORK_H, double *error, double *target, double LearningRate, double DesiredError) {
    unsigned char E2 = 0, E = 0, i = 0, j = 0, k = 0, l = 0, m = 0, n = 0, o = 0, q = 0, O_P = 0, Err1 = 0, Err2 = 0, N_EnO = 0;
    double A = 0, TargetTEMP = 0, SumTemp = 0;
    double *Errors;
    double *OutputTemp;
    double *ErrorsOUTPUTS;

    if (LearningRate > 0 && LearningRate <= 1);
    else return (0);
    NumberOfOutputNeeded(NeuralNETWORK_H, &N_EnO);

    ErrorsOUTPUTS = (double*) calloc(NeuralNETWORK_H->N_NeuronsIn_Layer[NeuralNETWORK_H->N_Layers - 1], sizeof (double));
    Errors = (double*) calloc(N_EnO, sizeof (double));
    OutputTemp = (double*) calloc(N_EnO, sizeof (double));

    O_P = RetOutputNumber(NeuralNETWORK_H, NeuralNETWORK_H->N_Layers - 1);
    o = 0;
    for (i = 0; i < (NeuralNETWORK_H->N_Layers - 1); i++) {
        for (j = 0; j < NeuralNETWORK_H->N_NeuronsIn_Layer[i + 1]; j++) {
            l = (RetWeightNumber(NeuralNETWORK_H, i) + j);
            n = 0;
            for (m = 1; m < i; m++) {
                n += NeuralNETWORK_H->N_NeuronsIn_Layer[m];
            }
            for (k = 0; k < NeuralNETWORK_H->N_NeuronsIn_Layer[i]; k++, l = l + NeuralNETWORK_H->N_NeuronsIn_Layer[i + 1]) {
                if (i == 0) {
                    A += (NeuralNETWORK_H->NeuronsInputVal[k] * NeuralNETWORK_H->NeuronsWeights[l]);
                } else {
                    A += (OutputTemp[n] * NeuralNETWORK_H->NeuronsWeights[l]);
                    n++;
                }
            }
            OutputTemp[o] = SigmoidalFunction(A);
            o++;
            A = 0;
        }
    }

    for (i = (NeuralNETWORK_H->N_Layers - 1); i != 0; i--) {
        if (i == (NeuralNETWORK_H->N_Layers - 1)) {
            n = RetOutputNumber(NeuralNETWORK_H, i);
            E = RetErrorNumber(NeuralNETWORK_H, i);
            for (l = 0; l < NeuralNETWORK_H->N_NeuronsIn_Layer[i]; l++) {
                TargetTEMP = *target++;
                Errors[l + E] = OutputError_DERIVATIVE(OutputTemp[n + l], TargetTEMP);
                ErrorsOUTPUTS[l] = (TargetTEMP - OutputTemp[n + l]);
                NeuralNETWORK_H->NeuronsOutputVal[l] = OutputTemp[l + O_P];
            }
        } else {
            n = RetWeightNumber(NeuralNETWORK_H, i);
            m = RetOutputNumber(NeuralNETWORK_H, i);
            E = RetErrorNumber(NeuralNETWORK_H, i + 1);
            E2 = RetErrorNumber(NeuralNETWORK_H, i);
            q = n;
            for (l = 0; l < NeuralNETWORK_H->N_NeuronsIn_Layer[i]; l++) {
                SumTemp = 0;
                for (k = 0; k < NeuralNETWORK_H->N_NeuronsIn_Layer[i + 1]; k++) {
                    SumTemp += (Errors[E + k] * NeuralNETWORK_H->NeuronsWeights[q]);
                    q++;
                }
                Errors[E2 + l] = ((OutputTemp[m + l])*(1 - OutputTemp[m + l]) * SumTemp);
            }
        }
    }

    for (i = (NeuralNETWORK_H->N_Layers - 1); i > 0; i--) {
        n = RetWeightNumber(NeuralNETWORK_H, i - 1);
        m = RetOutputNumber(NeuralNETWORK_H, i - 1);
        for (k = 0; k < NeuralNETWORK_H->N_NeuronsIn_Layer[i - 1]; k++) {
            E = RetErrorNumber(NeuralNETWORK_H, i);
            for (j = 0; j < NeuralNETWORK_H->N_NeuronsIn_Layer[i]; j++) {
                if (i == 1) {
                    NeuralNETWORK_H->NeuronsWeights[n] = (NeuralNETWORK_H->NeuronsWeights[n] + (NeuralNETWORK_H->NeuronsInputVal[k] * Errors[E + k] * LearningRate));
                } else {
                    NeuralNETWORK_H->NeuronsWeights[n] = (NeuralNETWORK_H->NeuronsWeights[n] + (OutputTemp[m] * Errors[E] * LearningRate));
                }
                n++;
                E++;
            }
            m++;
        }
        n = 0;
    }

    Err1 = 0;
    Err2 = 0;
    for (i = 0; i < NeuralNETWORK_H->N_NeuronsIn_Layer[NeuralNETWORK_H->N_Layers - 1]; i++) {
        *error++ = ErrorsOUTPUTS[i];
        if (ErrorsOUTPUTS[i] < 0) {
            if ((ErrorsOUTPUTS[i]*-1) < DesiredError) {
                Err1 += i + 1;
            }
        }
        if (ErrorsOUTPUTS[i] > 0) {
            if (ErrorsOUTPUTS[i] < DesiredError) {
                Err1 += i + 1;
            }
        }
        Err2 += i + 1;
    }
    free(OutputTemp);
    free(Errors);
    free(ErrorsOUTPUTS);
    if (Err1 == Err2)return (1);
    else return (0);
}

BOOL RunNetwork_PARKUEST(ArtifitialNeuralNetwork *NeuralNETWORK_I){
    unsigned char i = 0, j = 0, l = 0, n = 0, m = 0, k = 0, o = 0, O_P = 0, N_EnO = 0;
    double *OutputTemp, A = 0;

    NumberOfOutputNeeded(NeuralNETWORK_I, &N_EnO);
    O_P = RetOutputNumber(NeuralNETWORK_I, NeuralNETWORK_I->N_Layers - 1);
    OutputTemp = (double*) calloc(N_EnO, sizeof (double));

    for (i = 0; i < (NeuralNETWORK_I->N_Layers - 1); i++) {
        for (j = 0; j < NeuralNETWORK_I->N_NeuronsIn_Layer[i + 1]; j++) {
            l = (RetWeightNumber(NeuralNETWORK_I, i) + j);
            n = 0;
            for (m = 1; m < i; m++) {
                n += NeuralNETWORK_I->N_NeuronsIn_Layer[m];
            }
            for (k = 0; k < NeuralNETWORK_I->N_NeuronsIn_Layer[i]; k++, l = l + NeuralNETWORK_I->N_NeuronsIn_Layer[i + 1]) {
                if (i == 0) {
                    A += (NeuralNETWORK_I->NeuronsInputVal[k] * (NeuralNETWORK_I->NeuronsWeights[l]));
                } else {
                    A += (OutputTemp[n] * NeuralNETWORK_I->NeuronsWeights[l]);
                    n++;
                }
            }
            OutputTemp[o] = SigmoidalFunction(A);
            o++;
            A = 0;
        }
    }

    for (i = 0; i < NeuralNETWORK_I->N_NeuronsIn_Layer[NeuralNETWORK_I->N_Layers - 1]; i++) {
        NeuralNETWORK_I->NeuronsOutputVal[i] = OutputTemp[i + O_P];
    }
    free(OutputTemp);
    return (1);
}


