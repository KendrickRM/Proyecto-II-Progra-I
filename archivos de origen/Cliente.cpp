#include "Cliente.h"
#include <iostream>
using namespace std;

Cliente::Cliente(const string& identificacion, const string& nombre,
    const string& telefono, const string& correo)
    : identificacion(identificacion), nombre(nombre), telefono(telefono), correo(correo) {
}

string Cliente::getIdentificacion() const { return identificacion; }
string Cliente::getNombre() const { return nombre; }
string Cliente::getTelefono() const { return telefono; }
string Cliente::getCorreo() const { return correo; }

double Cliente::obtenerDescuento() const { return 0; }

void Cliente::mostrar() const {
    cout << "Identificacion: " << identificacion << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Telefono: " << telefono << endl;
    cout << "Correo: " << correo << endl;
}

Cliente::~Cliente() {}