#ifndef LISTABITACORA_H
#define LISTABITACORA_H

#include <string>
#include "RegistroBitacora.h"
#include "Colaborador.h"
using namespace std;

class NodoBitacora {
private:
    RegistroBitacora* dato;
    NodoBitacora* siguiente;
public:
    NodoBitacora(RegistroBitacora* d) : dato(d), siguiente(0) {}
    RegistroBitacora* getDato() const { return dato; }
    NodoBitacora* getSiguiente() const { return siguiente; }
    void setSiguiente(NodoBitacora* n) { siguiente = n; }
};


class ListaBitacora {
private:
    NodoBitacora* primero;
    int cantidad;
public:
    ListaBitacora() : primero(0), cantidad(0) {}

    void insertar(RegistroBitacora* r) {
        NodoBitacora* nuevo = new NodoBitacora(r);
        if (primero == 0) {
            primero = nuevo;
        }
        else {
            NodoBitacora* act = primero;
            while (act->getSiguiente() != 0) {
                act = act->getSiguiente();
            }
            act->setSiguiente(nuevo);
        }
        cantidad++;
    }

    RegistroBitacora* obtener(int pos) const {
        if (pos < 0 || pos >= cantidad) {
            return 0;
        }
        NodoBitacora* act = primero;
        for (int i = 0; i < pos; i++) {
            act = act->getSiguiente();
        }
        return act->getDato();
    }

    //Para eliminar colaboradores
    bool participoColaborador(const string& identificacion) const {
        NodoBitacora* act = primero;
        while (act != 0) {
            Colaborador* c = act->getDato()->getResponsable();
            if (c != 0 && c->getIdentificacion() == identificacion) {
                return true;
            }
            act = act->getSiguiente();
        }
        return false;
    }

    int getCantidad() const { return cantidad; }

    ~ListaBitacora() {
        while (primero != 0) {
            NodoBitacora* sig = primero->getSiguiente();
            delete primero->getDato();
            delete primero;
            primero = sig;
        }
    }
};

#endif