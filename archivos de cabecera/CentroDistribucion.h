#ifndef CENTRODISTRIBUCION_H
#define CENTRODISTRIBUCION_H

#include <string>
#include "ListaClientes.h"
#include "ListaColaboradores.h"
#include "ListaPaquetes.h"
#include "ListaSolicitudes.h"
#include "ListaBodegas.h"
#include "ListaDespachos.h"
using namespace std;

class CentroDistribucion {
private:
    string codigo;
    string nombre;
    string provincia;
    string direccion;
    string telefono;
    ListaClientes* clientes;
    ListaColaboradores* colaboradores;
    ListaPaquetes* paquetes;
    ListaSolicitudes* solicitudes;
    ListaBodegas* bodegas;
    ListaDespachos* despachos;

public:
    CentroDistribucion(const string& codigo, const string& nombre,
        const string& provincia, const string& direccion,
        const string& telefono);
    ~CentroDistribucion();

    bool estaVacio() const;
    void mostrar() const;
    string getCodigo() const;
    string getNombre() const;

    ListaClientes* getClientes();
    ListaColaboradores* getColaboradores();
    ListaPaquetes* getPaquetes();
    ListaSolicitudes* getSolicitudes();
    ListaBodegas* getBodegas();
    ListaDespachos* getDespachos();
};

#endif