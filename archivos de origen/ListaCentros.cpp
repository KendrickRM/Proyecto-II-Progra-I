#include "ListaCentros.h"
using namespace std;

ListaCentros::ListaCentros() : primero(0), cantidad(0) {}

void ListaCentros::insertar(CentroDistribucion* c) {
    NodoCentro* nuevo = new NodoCentro(c);
    if (primero == 0) {
        primero = nuevo;
    }
    else {
        NodoCentro* act = primero;
        while (act->getSiguiente() != 0) {
            act = act->getSiguiente();
        }
        act->setSiguiente(nuevo);
    }
    cantidad++;
}

CentroDistribucion* ListaCentros::buscar(const string& codigo) {
    NodoCentro* act = primero;
    while (act != 0) {
        if (act->getDato()->getCodigo() == codigo) {
            return act->getDato();
        }
        act = act->getSiguiente();
    }
    return 0;
}

bool ListaCentros::eliminar(const string& codigo) {
    NodoCentro* act = primero;
    NodoCentro* ant = 0;
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

CentroDistribucion* ListaCentros::obtener(int pos) {
    if (pos < 0 || pos >= cantidad) {
        return 0;
    }
    NodoCentro* act = primero;
    for (int i = 0; i < pos; i++) {
        act = act->getSiguiente();
    }
    return act->getDato();
}

int ListaCentros::getCantidad() const { return cantidad; }

ListaCentros::~ListaCentros() {
    while (primero != 0) {
        NodoCentro* sig = primero->getSiguiente();
        delete primero->getDato();
        delete primero;
        primero = sig;
    }
}