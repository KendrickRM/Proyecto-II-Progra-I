#include "Colaborador.h"
#include <iostream>
using namespace std;

Colaborador::Colaborador(const string& identificacion, const string& nombreCompleto,
    const string& puesto, const Fecha& fechaIngreso)
    : identificacion(identificacion), nombreCompleto(nombreCompleto),
    puesto(puesto), fechaIngreso(fechaIngreso) {
}

string Colaborador::getIdentificacion() const { return identificacion; }
string Colaborador::getNombreCompleto() const { return nombreCompleto; }
string Colaborador::getPuesto() const { return puesto; }
Fecha Colaborador::getFechaIngreso() const { return fechaIngreso; }

void Colaborador::mostrar() const {
    cout << "Identificacion: " << identificacion << endl;
    cout << "Nombre: " << nombreCompleto << endl;
    cout << "Puesto: " << puesto << endl;
    cout << "Fecha de ingreso: " << fechaIngreso.aTexto() << endl;
}