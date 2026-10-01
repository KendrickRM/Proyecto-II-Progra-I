#ifndef LISTADESPACHOS_H
#define LISTADESPACHOS_H

#include <string>
#include "Despacho.h"
using namespace std;

class NodoDespacho {
private:
    Despacho* dato;
    NodoDespacho* siguiente;
public:
    NodoDespacho(Despacho* d) : dato(d), siguiente(0) {}
    Despacho* getDato() { return dato; }
    NodoDespacho* getSiguiente() { return siguiente; }
    void setSiguiente(NodoDespacho* n) { siguiente = n; }
};

class ListaDespachos {
private:
    NodoDespacho* primero;
    int cantidad;
public:
    ListaDespachos() : primero(0), cantidad(0) {}

    void insertar(Despacho* d) {
        NodoDespacho* nuevo = new NodoDespacho(d);
        if (primero == 0) {
            primero = nuevo;
        }
        else {
            NodoDespacho* act = primero;
            while (act->getSiguiente() != 0) {
                act = act->getSiguiente();
            }
            act->setSiguiente(nuevo);
        }
        cantidad++;
    }

    Despacho* buscar(const string& codigo) {
        NodoDespacho* act = primero;
        while (act != 0) {
            if (act->getDato()->getCodigo() == codigo) {
                return act->getDato();
            }
            act = act->getSiguiente();
        }
        return 0;
    }

    Despacho* obtener(int pos) {
        if (pos < 0 || pos >= cantidad) {
            return 0;
        }
        NodoDespacho* act = primero;
        for (int i = 0; i < pos; i++) {
            act = act->getSiguiente();
        }
        return act->getDato();
    }

    int getCantidad() const { return cantidad; }

    ~ListaDespachos() {
        while (primero != 0) {
            NodoDespacho* sig = primero->getSiguiente();
            delete primero->getDato();
            delete primero;
            primero = sig;
        }
    }
};

#endif