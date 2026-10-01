#include "Sistema.h"
#include "ClientePersonaFisica.h"
#include "ClienteEmpresa.h"
#include <iostream>
using namespace std;

Sistema::Sistema() {
    centros = new ListaCentros();
}

Sistema::~Sistema() {
    delete centros;
}

bool Sistema::registrarCentro(CentroDistribucion* c) {
    if (c == 0) {
        return false;
    }
    if (codigoCentroExiste(c->getCodigo())) {
        return false;
    }
    centros->insertar(c);
    return true;
}

CentroDistribucion* Sistema::buscarCentro(const string& codigo) {
    return centros->buscar(codigo);
}

bool Sistema::eliminarCentro(const string& codigo) {
    CentroDistribucion* c = centros->buscar(codigo);
    if (c == 0) {
        return false;
    }
    if (!c->estaVacio()) {
        return false;
    }
    return centros->eliminar(codigo);
}

void Sistema::mostrarCentros() {
    if (centros->getCantidad() == 0) {
        cout << "No hay centros registrados." << endl;
        return;
    }
    for (int i = 0; i < centros->getCantidad(); i++) {
        cout << "---------------------------" << endl;
        centros->obtener(i)->mostrar();
    }
    cout << "---------------------------" << endl;
}

ListaCentros* Sistema::getCentros() { return centros; }

bool Sistema::codigoCentroExiste(const string& codigo) {
    return centros->buscar(codigo) != 0;
}

bool Sistema::codigoPaqueteExiste(const string& codigo) {
    return buscarPaquete(codigo) != 0;
}

bool Sistema::codigoSolicitudExiste(const string& codigo) {
    return buscarSolicitud(codigo) != 0;
}

bool Sistema::codigoDespachoExiste(const string& codigo) {
    return buscarDespacho(codigo) != 0;
}

Paquete* Sistema::buscarPaquete(const string& codigo) {
    for (int i = 0; i < centros->getCantidad(); i++) {
        Paquete* p = centros->obtener(i)->getPaquetes()->buscar(codigo);
        if (p != 0) {
            return p;
        }
    }
    return 0;
}

SolicitudEnvio* Sistema::buscarSolicitud(const string& codigo) {
    for (int i = 0; i < centros->getCantidad(); i++) {
        SolicitudEnvio* s = centros->obtener(i)->getSolicitudes()->buscar(codigo);
        if (s != 0) {
            return s;
        }
    }
    return 0;
}

Despacho* Sistema::buscarDespacho(const string& codigo) {
    for (int i = 0; i < centros->getCantidad(); i++) {
        Despacho* d = centros->obtener(i)->getDespachos()->buscar(codigo);
        if (d != 0) {
            return d;
        }
    }
    return 0;
}

void Sistema::cargarDatosQuemados() {
    CentroDistribucion* c1 = new CentroDistribucion("CD-001", "Centro San Jose", "San Jose",
        "Avenida Central, 200m norte del parque", "2222-1111");
    CentroDistribucion* c2 = new CentroDistribucion("CD-002", "Centro Alajuela", "Alajuela",
        "Radial Francisco J. Orlich", "2433-2222");
    CentroDistribucion* c3 = new CentroDistribucion("CD-003", "Centro Cartago", "Cartago",
        "Frente a las Ruinas, calle principal", "2551-3333");

    c1->getClientes()->insertar(new ClientePersonaFisica("1-1111-1111", "Maria Rojas", "8888-0001", "maria@correo.com"));
    c1->getClientes()->insertar(new ClienteEmpresa("3-101-111111", "Importadora Tica S.A.", "2222-0002", "info@importadora.com", "Importacion", 10));

    c2->getClientes()->insertar(new ClientePersonaFisica("2-2222-2222", "Carlos Vargas", "8888-0003", "carlos@correo.com"));
    c2->getClientes()->insertar(new ClienteEmpresa("3-101-222222", "Tecnologia Total S.A.", "2433-0004", "ventas@tecnototal.com", "Venta de tecnologia", 15));

    c3->getClientes()->insertar(new ClientePersonaFisica("3-3333-3333", "Ana Jimenez", "8888-0005", "ana@correo.com"));
    c3->getClientes()->insertar(new ClienteEmpresa("3-101-333333", "Distribuidora Cartago S.A.", "2551-0006", "contacto@distcartago.com", "Distribucion de alimentos", 5));

    registrarCentro(c1);
    registrarCentro(c2);
    registrarCentro(c3);
}