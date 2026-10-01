#ifndef CLIENTEPERSONAFISICA_H
#define CLIENTEPERSONAFISICA_H

#include "Cliente.h"
using namespace std;

class ClientePersonaFisica : public Cliente {
public:
    ClientePersonaFisica(const string& identificacion, const string& nombre,
        const string& telefono, const string& correo);
    double obtenerDescuento() const;
    void mostrar() const;
};

#endif