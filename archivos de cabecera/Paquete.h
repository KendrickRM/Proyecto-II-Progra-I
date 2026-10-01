#ifndef PAQUETE_H
#define PAQUETE_H

#include <string>
using namespace std;

// STUB de Persona 1. Persona 2 lo reemplaza.
class Paquete {
private:
    string codigo;
public:
    Paquete(const string& codigo) : codigo(codigo) {}
    string getCodigo() const { return codigo; }
};

#endif