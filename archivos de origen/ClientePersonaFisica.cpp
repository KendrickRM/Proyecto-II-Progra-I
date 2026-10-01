#include "ClientePersonaFisica.h"
#include <iostream>
using namespace std;

ClientePersonaFisica::ClientePersonaFisica(const string& identificacion, const string& nombre,
    const string& telefono, const string& correo)
    : Cliente(identificacion, nombre, telefono, correo) {
}

double ClientePersonaFisica::obtenerDescuento() const { return 0; }

void ClientePersonaFisica::mostrar() const {
    cout << "Tipo: Persona fisica" << endl;
    Cliente::mostrar();
}