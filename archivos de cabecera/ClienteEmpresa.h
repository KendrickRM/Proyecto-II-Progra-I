#ifndef CLIENTEEMPRESA_H
#define CLIENTEEMPRESA_H

#include "Cliente.h"
using namespace std;

class ClienteEmpresa : public Cliente {
private:
    string actividadEconomica;
    double porcentajeDescuento;

public:
    ClienteEmpresa(const string& identificacion, const string& nombre,
        const string& telefono, const string& correo,
        const string& actividadEconomica, double porcentajeDescuento);
    double obtenerDescuento() const;
    void mostrar() const;
};

#endif