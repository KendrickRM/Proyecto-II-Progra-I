#ifndef BODEGA_H
#define BODEGA_H

#include <string>
using namespace std;

// STUB de Persona 1. Persona 2 lo reemplaza (matriz dinamica, etc.).
class Bodega {
private:
    string codigo;
public:
    Bodega(const string& codigo) : codigo(codigo) {}
    string getCodigo() const { return codigo; }
};

#endif