#ifndef COLABORADOR_H
#define COLABORADOR_H

#include <string>
#include <iostream>
#include "Fecha.h"

using namespace std;

// STUB de Persona 1. Persona 2 lo reemplaza (agrega fechaIngreso con Fecha).
class Colaborador {
private:
    string identificacion;
    string nombreCompleto;
    string puesto;
    Fecha fechaIngreso;

public:
    Colaborador(const string& id, const string& nombre, const string& puesto)
        : identificacion(id), nombreCompleto(nombre), puesto(puesto) {
    }
    string getIdentificacion() const { return identificacion; }
    string getNombreCompleto() const { return nombreCompleto; }
    string getPuesto()         const { return puesto;         }
    Fecha getFechaIngreso()    const { return fechaIngreso;   }




    void mostrar() const {
        cout << identificacion << " - " << nombreCompleto << " (" << puesto << ")" << endl;
    }
};

#endif