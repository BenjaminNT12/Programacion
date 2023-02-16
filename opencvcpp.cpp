#include<opencv2\opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
int main() {
    Mat imagen = imread("C:\\OpenCV\\lena_std.tif", CV_LOAD_IMAGE_GRAYSCALE); //Guarda la imagen en la matriz en grises
    imshow("Original", imagen);
    cout << "La imagen tiene " << imagen.rows << " pixeles de alto y " << imagen.cols << " pixeles de ancho" << endl;
    uchar pixel = imagen.at<uchar>(511, 511);//Con la func "at" se pide qué hay en ese pixel, y se pide el formato
    cout << "En la coord. 511 x 511 el nivel de gris es " <<(int)pixel<<endl;
    waitKey(0);
    return 1;
}