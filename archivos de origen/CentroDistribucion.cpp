#include "CentroDistribucion.h"
#include <iostream>
using namespace std;

CentroDistribucion::CentroDistribucion(const string& codigo, const string& nombre,
    const string& provincia, const string& direccion,
    const string& telefono)
    : codigo(codigo), nombre(nombre), provincia(provincia),
    direccion(direccion), telefono(telefono) {
    clientes = new ListaClientes();
    colaboradores = new ListaColaboradores();
    paquetes = new ListaPaquetes();
    solicitudes = new ListaSolicitudes();
    bodegas = new ListaBodegas();
    despachos = new ListaDespachos();
}

CentroDistribucion::~CentroDistribucion() {
    delete clientes;
    delete colaboradores;
    delete paquetes;
    delete solicitudes;
    delete bodegas;
    delete despachos;
}

bool CentroDistribucion::estaVacio() const {
    return clientes->getCantidad() == 0 &&
        colaboradores->getCantidad() == 0 &&
        paquetes->getCantidad() == 0 &&
        solicitudes->getCantidad() == 0 &&
        bodegas->getCantidad() == 0 &&
        despachos->getCantidad() == 0;
}

void CentroDistribucion::mostrar() const {
    cout << "Codigo: " << codigo << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Provincia: " << provincia << endl;
    cout << "Direccion: " << direccion << endl;
    cout << "Telefono: " << telefono << endl;
    cout << "Clientes: " << clientes->getCantidad()
        << " | Colaboradores: " << colaboradores->getCantidad()
        << " | Bodegas: " << bodegas->getCantidad()
        << " | Paquetes: " << paquetes->getCantidad()
        << " | Solicitudes: " << solicitudes->getCantidad()
        << " | Despachos: " << despachos->getCantidad() << endl;
}

string CentroDistribucion::getCodigo() const { return codigo; }
string CentroDistribucion::getNombre() const { return nombre; }

ListaClientes* CentroDistribucion::getClientes() { return clientes; }
ListaColaboradores* CentroDistribucion::getColaboradores() { return colaboradores; }
ListaPaquetes* CentroDistribucion::getPaquetes() { return paquetes; }
ListaSolicitudes* CentroDistribucion::getSolicitudes() { return solicitudes; }
ListaBodegas* CentroDistribucion::getBodegas() { return bodegas; }
ListaDespachos* CentroDistribucion::getDespachos() { return despachos; }