#ifndef COLABORADOR_H
#define COLABORADOR_H

#include <string>
#include <iostream>
#include "Fecha.h"

using namespace std;

class Colaborador {
private:
    string identificacion;
    string nombreCompleto;
    string puesto;
    Fecha fechaIngreso;

public:
    Colaborador(const string& identificacion, const string& nombreCompleto,
        const string& puesto, const Fecha& fechaIngreso);
    string getIdentificacion() const;
    string getNombreCompleto() const;
    string getPuesto() const;
    Fecha getFechaIngreso() const;
    void mostrar() const;
};

#endif