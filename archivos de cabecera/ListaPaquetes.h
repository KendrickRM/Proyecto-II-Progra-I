#ifndef LISTAPAQUETES_H
#define LISTAPAQUETES_H

#include <string>
#include "Paquete.h"
using namespace std;

class NodoPaquete {
private:
    Paquete* dato;
    NodoPaquete* siguiente;
public:
    NodoPaquete(Paquete* d) : dato(d), siguiente(0) {}
    Paquete* getDato() { return dato; }
    NodoPaquete* getSiguiente() { return siguiente; }
    void setSiguiente(NodoPaquete* n) { siguiente = n; }
};

class ListaPaquetes {
private:
    NodoPaquete* primero;
    int cantidad;
public:
    ListaPaquetes() : primero(0), cantidad(0) {}

    void insertar(Paquete* p) {
        NodoPaquete* nuevo = new NodoPaquete(p);
        if (primero == 0) {
            primero = nuevo;
        }
        else {
            NodoPaquete* act = primero;
            while (act->getSiguiente() != 0) {
                act = act->getSiguiente();
            }
            act->setSiguiente(nuevo);
        }
        cantidad++;
    }

    Paquete* buscar(const string& codigo) {
        NodoPaquete* act = primero;
        while (act != 0) {
            if (act->getDato()->getCodigo() == codigo) {
                return act->getDato();
            }
            act = act->getSiguiente();
        }
        return 0;
    }

    bool eliminar(const string& codigo) {
        NodoPaquete* act = primero;
        NodoPaquete* ant = 0;
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

    Paquete* obtener(int pos) {
        if (pos < 0 || pos >= cantidad) {
            return 0;
        }
        NodoPaquete* act = primero;
        for (int i = 0; i < pos; i++) {
            act = act->getSiguiente();
        }
        return act->getDato();
    }

    int getCantidad() const { return cantidad; }

    ~ListaPaquetes() {
        while (primero != 0) {
            NodoPaquete* sig = primero->getSiguiente();
            delete primero->getDato();
            delete primero;
            primero = sig;
        }
    }
};

#endif