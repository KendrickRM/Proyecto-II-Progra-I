#include "ClienteEmpresa.h"
#include <iostream>
using namespace std;

ClienteEmpresa::ClienteEmpresa(const string& identificacion, const string& nombre,
    const string& telefono, const string& correo,
    const string& actividadEconomica, double porcentajeDescuento)
    : Cliente(identificacion, nombre, telefono, correo),
    actividadEconomica(actividadEconomica), porcentajeDescuento(porcentajeDescuento) {
    // El descuento autorizado debe estar entre 0% y 100%
    if (this->porcentajeDescuento < 0) {
        this->porcentajeDescuento = 0;
    }
    if (this->porcentajeDescuento > 100) {
        this->porcentajeDescuento = 100;
    }
}

double ClienteEmpresa::obtenerDescuento() const { return porcentajeDescuento; }

void ClienteEmpresa::mostrar() const {
    cout << "Tipo: Empresa" << endl;
    Cliente::mostrar();
    cout << "Actividad economica: " << actividadEconomica << endl;
    cout << "Descuento: " << porcentajeDescuento << "%" << endl;
}