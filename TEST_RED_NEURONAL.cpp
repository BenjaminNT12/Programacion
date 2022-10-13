#include <iostream>
// #include <conio>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUMBER_LAYER 3
#define NEURON_INPUT_LAYER 5
#define NEURON_HIDE_LAYER 10
#define NEURON_OUTPUT_LAYER 2

typedef struct {
    double *NeuronsWeights;
    double *NeuronsInputVal;
    double *NeuronsOutputVal;
    double *DesiredError;
    double *LearningFactor;
    double *Momentum;
    unsigned char N_Layers;
    unsigned char N_Hide_Layers;
    unsigned char N_NeuronsInputs;
    unsigned char *N_NeuronsInHide_Layer;
    unsigned char N_NeuronsOutputs;
}ArtifitialNeuralNetwork;

static ArtifitialNeuralNetwork NeuralNetwork;

static double *SigmoidalFunction(double *alpha){
    return(1/(1+exp(-1*alpha)));
}

static void InitializationWeights(ArtifitialNeuralNetwork *A_NeuralNETWORK){
    unsigned char temp_N_neurons_weights = 0;
    unsigned char i = 0;
    double temp_weight = 0;

    for (i = 0; i < (A_NeuralNETWORK->N_Layers - 2); i++) temp_N_neurons_weights += (i == 0) ? A_NeuralNETWORK->N_NeuronsInputs * A_NeuralNETWORK->N_NeuronsInHide_Layer[i] : A_NeuralNETWORK->N_NeuronsInHide_Layer[i - 1] * A_NeuralNETWORK->N_NeuronsInHide_Layer[i];
    temp_N_neurons_weights += A_NeuralNETWORK->N_NeuronsOutputs * A_NeuralNETWORK->N_NeuronsInHide_Layer[A_NeuralNETWORK->N_Layers - 3];
    for (i = 0; i < temp_N_neurons_weights; i++) {
        temp_weight = ((double) rand() / (double) RAND_MAX);
        *A_NeuralNETWORK->NeuronsWeights++ = temp_weight;
    }
}

static void InitializationNeuralNetwork(unsigned char number_layers,unsigned char neurons_inputs,unsigned char *neurons_InHidden,unsigned char neurons_output,ArtifitialNeuralNetwork *NeuralNETWORK){
    unsigned char i=0;

    NeuralNETWORK->N_Layers = number_layers;
    NeuralNETWORK->N_NeuronsInputs = neurons_inputs;
    NeuralNETWORK->N_Hide_Layers = (number_layers - 2);
    for (i = 0; i < NeuralNETWORK->N_Hide_Layers; i++)NeuralNETWORK->N_NeuronsInHide_Layer[i] = (i != (NeuralNETWORK->N_Hide_Layers - 1)) ? *neurons_InHidden++ : *neurons_InHidden;
    NeuralNETWORK->N_NeuronsOutputs = neurons_output;
    InitializationWeights(NeuralNETWORK);
}

static unsigned char RetWeightNumber(ArtifitialNeuralNetwork *NeuralNETWORK,unsigned char NumberLayer){
    unsigned char i = 0;
    unsigned char cont = 0;

    if (NumberLayer == 1) {
        cont = NeuralNETWORK->N_NeuronsInputs * NeuralNETWORK->N_NeuronsInHide_Layer[0];
    }else if (NumberLayer > 1) {
        cont = (NeuralNETWORK->N_NeuronsInputs * NeuralNETWORK->N_NeuronsInHide_Layer[0]);
        for (i = 1; i < NeuralNETWORK->N_Hide_Layers && i<NumberLayer; i++) {
            cont += NeuralNETWORK->N_NeuronsInHide_Layer[i] * NeuralNETWORK->N_NeuronsInHide_Layer[i - 1];
        }
    }else if(NumberLayer == 0){
        cont = 0;
    }
    return(cont);
}

void BackpropagationTraining(ArtifitialNeuralNetwork *NeuralNETWORK){
    unsigned char i = 0, j = 0, k = 0, l = 0, m = 0, n = 0, o = 0;
    unsigned char NumberOfOutput = 0,NumberNeuronsInHideLayer = 0;
    double accumulator = 0,*neurons_calculate_outputs = 0;

    for(i=0;i<NeuralNETWORK->N_Hide_Layers;i++)NumberOfOutput += NeuralNETWORK->N_NeuronsInHide_Layer[i];
    NumberNeuronsInHideLayer = NumberOfOutput;
    NumberOfOutput += NeuralNETWORK->N_NeuronsOutputs;
    neurons_calculate_outputs = (double*)malloc(NumberOfOutput*sizeof(double));

    for (j = 0; j < NeuralNETWORK->N_Hide_Layers; j++) {
        for (i = 0; i < NeuralNETWORK->N_NeuronsInHide_Layer[j]; i++) {
            if (j == 0) {
                l = i;
                for (k = 0; k < NeuralNETWORK->N_NeuronsInputs; k++, l = l + NeuralNETWORK->N_NeuronsInHide_Layer[j]) {
                    accumulator += (NeuralNETWORK->NeuronsInputVal[k] * NeuralNETWORK->NeuronsWeights[l]);
                }
                neurons_calculate_outputs[i] = SigmoidalFunction(&accumulator);
            } else {
                l = (j > 1) ? (RetWeightNumber(NeuralNETWORK,j) + i): (RetWeightNumber(NeuralNETWORK,j) + i);
                n = (j > 1) ? (n+NeuralNETWORK->N_NeuronsInHide_Layer[j-1]) : NeuralNETWORK->N_NeuronsInHide_Layer[j-1] ;
                m = (j > 1) ? (m+i) : (NeuralNETWORK->N_NeuronsInHide_Layer[j-1]+i) ;
                for (k = 0; k < NeuralNETWORK->N_NeuronsInHide_Layer[j - 1]; k++, l = l + NeuralNETWORK->N_NeuronsInHide_Layer[j]) {
                    accumulator += (neurons_calculate_outputs[n] * NeuralNETWORK->NeuronsWeights[l]);
                }
                neurons_calculate_outputs[m] = SigmoidalFunction(&accumulator);
            }
        }
    }

    o = (NumberNeuronsInHideLayer - NeuralNETWORK->N_NeuronsInHide_Layer[(NeuralNETWORK->N_Hide_Layers-1)]);
    for (j = 0; j < NeuralNETWORK->N_NeuronsOutputs; j++) {
        l = (RetWeightNumber(NeuralNETWORK,NeuralNETWORK->N_Hide_Layers)+j);
        for (i = 0; i < NeuralNETWORK->N_NeuronsInHide_Layer[(NeuralNETWORK->N_Hide_Layers-1)]; i++,l = l+NeuralNETWORK->N_NeuronsInHide_Layer[(NeuralNETWORK->N_Hide_Layers-1)]) {
            accumulator = neurons_calculate_outputs[o+i] * NeuralNETWORK->NeuronsWeights[l];
        }
         NeuralNETWORK->NeuronsOutputVal[j] = SigmoidalFunction(&accumulator);
    }

}

void main(void){
	unsigned char LAYERS = 3;
	unsigned char NEURON_INPUT = 2;
	unsigned char neurons_InHidden = 2;
	unsigned char Neuron_OUTPUT = 1;

  InitializationNeuralNetwork(&LAYERS,&NEURON_INPUT,&neurons_InHidden,&Neuron_OUTPUT,&NeuralNetwork);
	printf("Resultado %2.5f \n",NeuralNetwork.NeuronsOutputVal);
  getch();
}
