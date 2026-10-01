#ifndef LISTASOLICITUDES_H
#define LISTASOLICITUDES_H

#include <string>
#include "SolicitudEnvio.h"
using namespace std;

class NodoSolicitud {
private:
    SolicitudEnvio* dato;
    NodoSolicitud* siguiente;
public:
    NodoSolicitud(SolicitudEnvio* d) : dato(d), siguiente(0) {}
    SolicitudEnvio* getDato() { return dato; }
    NodoSolicitud* getSiguiente() { return siguiente; }
    void setSiguiente(NodoSolicitud* n) { siguiente = n; }
};

class ListaSolicitudes {
private:
    NodoSolicitud* primero;
    int cantidad;
public:
    ListaSolicitudes() : primero(0), cantidad(0) {}

    void insertar(SolicitudEnvio* s) {
        NodoSolicitud* nuevo = new NodoSolicitud(s);
        if (primero == 0) {
            primero = nuevo;
        }
        else {
            NodoSolicitud* act = primero;
            while (act->getSiguiente() != 0) {
                act = act->getSiguiente();
            }
            act->setSiguiente(nuevo);
        }
        cantidad++;
    }

    SolicitudEnvio* buscar(const string& codigo) {
        NodoSolicitud* act = primero;
        while (act != 0) {
            if (act->getDato()->getCodigo() == codigo) {
                return act->getDato();
            }
            act = act->getSiguiente();
        }
        return 0;
    }

    SolicitudEnvio* obtener(int pos) {
        if (pos < 0 || pos >= cantidad) {
            return 0;
        }
        NodoSolicitud* act = primero;
        for (int i = 0; i < pos; i++) {
            act = act->getSiguiente();
        }
        return act->getDato();
    }

    int getCantidad() const { return cantidad; }

    ~ListaSolicitudes() {
        while (primero != 0) {
            NodoSolicitud* sig = primero->getSiguiente();
            delete primero->getDato();
            delete primero;
            primero = sig;
        }
    }
};

#endif