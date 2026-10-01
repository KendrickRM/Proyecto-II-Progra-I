#include "ClienteEmpresa.h"
#include <iostream>
using namespace std;

ClienteEmpresa::ClienteEmpresa(const string& identificacion, const string& nombre,
    const string& telefono, const string& correo,
    const string& actividadEconomica, double porcentajeDescuento)
    : Cliente(identificacion, nombre, telefono, correo),
    actividadEconomica(actividadEconomica), porcentajeDescuento(porcentajeDescuento) {
}

double ClienteEmpresa::obtenerDescuento() const { return porcentajeDescuento; }

void ClienteEmpresa::mostrar() const {
    cout << "Tipo: Empresa" << endl;
    Cliente::mostrar();
    cout << "Actividad economica: " << actividadEconomica << endl;
    cout << "Descuento: " << porcentajeDescuento << "%" << endl;
}