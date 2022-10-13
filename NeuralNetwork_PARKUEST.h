/* 
 * File:   NeuralNectwork_PARKUEST.h
 * Author: Wavelet
 *
 * Created on 5 de noviembre de 2014, 04:29 PM
 */

#ifndef NEURALNECTWORK_PARKUEST_H
#define	NEURALNECTWORK_PARKUEST_H

#ifdef	__cplusplus
extern "C" {
#endif



#define NUMBER_LAYER 		5
#define NEURON_INPUT_LAYER 	20
#define NEURON_OUTPUT_LAYER 	4
#define NUMBER_WEIGHT		1110 // Se debe especificar el numero de pesos a Guardar

typedef struct {
    double NeuronsInputVal[NEURON_INPUT_LAYER];
    double NeuronsOutputVal[NEURON_OUTPUT_LAYER+1]; // numero de salidas = numero de neuronas menos entradas
    double NeuronsWeights[NUMBER_WEIGHT];
    unsigned char N_Layers;
    unsigned char N_NeuronsIn_Layer[NUMBER_LAYER];
}ArtifitialNeuralNetwork;

    void Initialization_Weights(ArtifitialNeuralNetwork *NeuralNETWORK_F);
    void Initialization_NeuralNetwork_PARKUEST(unsigned char number_layers, unsigned char *STRUCTURE_OF_NEURONS, ArtifitialNeuralNetwork *NeuralNETWORK_G);
    BOOL BackpropagationTraining_PARKUEST(ArtifitialNeuralNetwork *NeuralNETWORK_H, double *error, double *target, double LearningRate, double DesiredError);
    BOOL RunNetwork_PARKUEST(ArtifitialNeuralNetwork *NeuralNETWORK_I);

#ifdef	__cplusplus
}
#endif

#endif	/* NEURALNECTWORK_PARKUEST_H */

