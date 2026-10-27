#ifndef LISTACOLABORADORES_H
#define LISTACOLABORADORES_H

#include <string>
#include "Colaborador.h"
using namespace std;

class NodoColaborador {
private:
    Colaborador* dato;
    NodoColaborador* siguiente;
public:
    NodoColaborador(Colaborador* d) : dato(d), siguiente(0) {}
    Colaborador* getDato() { return dato; }
    NodoColaborador* getSiguiente() { return siguiente; }
    void setSiguiente(NodoColaborador* n) { siguiente = n; }
};

class ListaColaboradores {
private:
    NodoColaborador* primero;
    int cantidad;
public:
    ListaColaboradores() : primero(0), cantidad(0) {}

    void insertar(Colaborador* c) {
        NodoColaborador* nuevo = new NodoColaborador(c);
        if (primero == 0) {
            primero = nuevo;
        }
        else {
            NodoColaborador* act = primero;
            while (act->getSiguiente() != 0) {
                act = act->getSiguiente();
            }
            act->setSiguiente(nuevo);
        }
        cantidad++;
    }

    Colaborador* buscar(const string& id) {
        NodoColaborador* act = primero;
        while (act != 0) {
            if (act->getDato()->getIdentificacion() == id) {
                return act->getDato();
            }
            act = act->getSiguiente();
        }
        return 0;
    }

    bool eliminar(const string& id) {
        NodoColaborador* act = primero;
        NodoColaborador* ant = 0;
        while (act != 0) {
            if (act->getDato()->getIdentificacion() == id) {
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

    Colaborador* obtener(int pos) {
        if (pos < 0 || pos >= cantidad) {
            return 0;
        }
        NodoColaborador* act = primero;
        for (int i = 0; i < pos; i++) {
            act = act->getSiguiente();
        }
        return act->getDato();
    }

    int getCantidad() const { return cantidad; }

    ~ListaColaboradores() {
        while (primero != 0) {
            NodoColaborador* sig = primero->getSiguiente();
            delete primero->getDato();
            delete primero;
            primero = sig;
        }
    }
};

#endif