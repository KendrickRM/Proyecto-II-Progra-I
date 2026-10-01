#ifndef LISTACENTROS_H
#define LISTACENTROS_H

#include <string>
#include "CentroDistribucion.h"
using namespace std;

class NodoCentro {
private:
    CentroDistribucion* dato;
    NodoCentro* siguiente;
public:
    NodoCentro(CentroDistribucion* d) : dato(d), siguiente(0) {}
    CentroDistribucion* getDato() { return dato; }
    NodoCentro* getSiguiente() { return siguiente; }
    void setSiguiente(NodoCentro* n) { siguiente = n; }
};

class ListaCentros {
private:
    NodoCentro* primero;
    int cantidad;
public:
    ListaCentros();
    void insertar(CentroDistribucion* c);
    CentroDistribucion* buscar(const string& codigo);
    bool eliminar(const string& codigo);
    CentroDistribucion* obtener(int pos);
    int getCantidad() const;
    ~ListaCentros();
};

#endif