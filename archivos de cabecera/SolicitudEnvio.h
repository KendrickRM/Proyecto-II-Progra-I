#ifndef SOLICITUDENVIO_H
#define SOLICITUDENVIO_H

#include <string>
using namespace std;

// STUB de Persona 1. Persona 3 lo reemplaza.
class SolicitudEnvio {
private:
    string codigo;
public:
    SolicitudEnvio(const string& codigo) : codigo(codigo) {}
    string getCodigo() const { return codigo; }
};

#endif