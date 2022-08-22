#include <iostream>
#include <stdlib.h>
using namespace std;
//
// class persona{
// private:
//     string nombre;
//     int edad;
// public:
//     persona(string, int);
//     virtual void mostrar();
// };
//
// persona::persona(string _nombre, int _edad){
//     nombre = _nombre;
//     edad = _edad;
// };
//
// void persona::mostrar(){
//     cout<<"Nombe: "<<nombre<<endl;
//     cout<<"Edad: "<<edad<<endl;
// };
//
// class alumno : public persona{
//     private:
//         float nota;
//     public:
//         alumno(string, int, float);
//         void mostrar();
// };
//
// alumno::alumno(string _nombre, int _edad, float _nota):persona(_nombre, _edad){
//     nota = _nota;
// };
//
// void alumno::mostrar(){
//     persona::mostrar();
//     cout<<"nota final: "<<nota<<endl;
// };
//
// class profesor : public persona{
// private:
//     string materia;
// public:
//     profesor(string, int, string);
//     void mostrar();
// };
//
// profesor::profesor(string _nombre, int _edad, string _materia):persona(_nombre, _edad){
//     materia = _materia;
// };
//
// void profesor::mostrar(){
//     persona::mostrar();
//     cout<<"materia: "<<materia<<endl;
// };
//
// int main(){
//     persona *Alumno;
//     Alumno = new alumno("BENJAMIN", 32, 9.9);
//
//     Alumno->mostrar();
//
//     // persona *vector[3];
//     //
//     // vector[0] = new alumno("Alejandro", 20, 18.9);
//     // vector[1] = new alumno("Maria", 19, 22.9);
//     // vector[2] = new profesor("Alejandro", 35, "Matematicas");
//     //
//     // vector[0]->mostrar();
//     // cout<<"\n";
//     // vector[1]->mostrar();
//     // cout<<"\n";
//     // vector[2]->mostrar();
//     // cout<<"\n";
//
//     system("pause");
//     return 0;
// }
int main(){
    const int m =10;
    int  &n = m;
    n = 11;
    cout<<m<<n<<endl;
    return 0;
}
