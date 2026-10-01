#ifndef DESPACHO_H
#define DESPACHO_H

#include <string>
using namespace std;

// STUB de Persona 1. Persona 3 lo reemplaza.
class Despacho {
private:
    string codigo;
public:
    Despacho(const string& codigo) : codigo(codigo) {}
    string getCodigo() const { return codigo; }
};

#endif