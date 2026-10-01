#ifndef LISTABODEGAS_H
#define LISTABODEGAS_H

#include <string>
#include "Bodega.h"
using namespace std;

class NodoBodega {
private:
    Bodega* dato;
    NodoBodega* siguiente;
public:
    NodoBodega(Bodega* d) : dato(d), siguiente(0) {}
    Bodega* getDato() { return dato; }
    NodoBodega* getSiguiente() { return siguiente; }
    void setSiguiente(NodoBodega* n) { siguiente = n; }
};

class ListaBodegas {
private:
    NodoBodega* primero;
    int cantidad;
public:
    ListaBodegas() : primero(0), cantidad(0) {}

    void insertar(Bodega* b) {
        NodoBodega* nuevo = new NodoBodega(b);
        if (primero == 0) {
            primero = nuevo;
        }
        else {
            NodoBodega* act = primero;
            while (act->getSiguiente() != 0) {
                act = act->getSiguiente();
            }
            act->setSiguiente(nuevo);
        }
        cantidad++;
    }

    Bodega* buscar(const string& codigo) {
        NodoBodega* act = primero;
        while (act != 0) {
            if (act->getDato()->getCodigo() == codigo) {
                return act->getDato();
            }
            act = act->getSiguiente();
        }
        return 0;
    }

    bool eliminar(const string& codigo) {
        NodoBodega* act = primero;
        NodoBodega* ant = 0;
        while (act != 0) {
            if (act->getDato()->getCodigo() == codigo) {
                if (ant == 0) {
                    primero = act->getSiguiente();
                }
                else {
                    ant->setSiguiente(act->getSiguiente());
                }
                delete act->getDato();
                delete act;
                cantidad--;
                return true;
            }
            ant = act;
            act = act->getSiguiente();
        }
        return false;
    }

    Bodega* obtener(int pos) {
        if (pos < 0 || pos >= cantidad) {
            return 0;
        }
        NodoBodega* act = primero;
        for (int i = 0; i < pos; i++) {
            act = act->getSiguiente();
        }
        return act->getDato();
    }

    int getCantidad() const { return cantidad; }

    ~ListaBodegas() {
        while (primero != 0) {
            NodoBodega* sig = primero->getSiguiente();
            delete primero->getDato();
            delete primero;
            primero = sig;
        }
    }
};

#endif