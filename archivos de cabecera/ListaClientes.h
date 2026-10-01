#ifndef LISTACLIENTES_H
#define LISTACLIENTES_H

#include <string>
#include "Cliente.h"
using namespace std;

class NodoCliente {
private:
    Cliente* dato;
    NodoCliente* siguiente;
public:
    NodoCliente(Cliente* d) : dato(d), siguiente(0) {}
    Cliente* getDato() { return dato; }
    NodoCliente* getSiguiente() { return siguiente; }
    void setSiguiente(NodoCliente* n) { siguiente = n; }
};

class ListaClientes {
private:
    NodoCliente* primero;
    int cantidad;
public:
    ListaClientes();
    void insertar(Cliente* c);
    Cliente* buscar(const string& id);
    bool eliminar(const string& id);
    Cliente* obtener(int pos);
    int getCantidad() const;
    ~ListaClientes();
};

#endif