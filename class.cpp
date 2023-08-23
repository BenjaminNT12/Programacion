#include <iostream>
#include <cmath>

// Clase Triángulo
class Triangulo {
private:
    double base;
    double altura;

public:
    Triangulo(double b, double h) : base(b), altura(h) {}

    double calcularArea() {
        return 0.5 * base * altura;
    }
};

// Clase Cuadrado
class Cuadrado {
private:
    double lado;

public:
    Cuadrado(double l) : lado(l) {}

    double calcularArea() {
        return lado * lado;
    }
};

// Clase Círculo
class Circulo {
private:
    double radio;

public:
    Circulo(double r) : radio(r) {}

    double calcularArea() {
        return M_PI * radio * radio;
    }
};

int main() {
    Triangulo triangulo(5.0, 4.0);
    Cuadrado cuadrado(3.0);
    Circulo circulo(2.5);

    std::cout << "Área del triángulo: " << triangulo.calcularArea() << std::endl;
    std::cout << "Área del cuadrado: " << cuadrado.calcularArea() << std::endl;
    std::cout << "Área del círculo: " << circulo.calcularArea() << std::endl;

    return 0;
}
