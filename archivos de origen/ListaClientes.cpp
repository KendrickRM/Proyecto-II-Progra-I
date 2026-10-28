#include "ListaClientes.h"

ListaClientes::ListaClientes() : primero(0), cantidad(0) {}

void ListaClientes::insertar(Cliente* c) {
    NodoCliente* nuevo = new NodoCliente(c);
    if (primero == 0) primero = nuevo;
    else {
        NodoCliente* actual = primero;
        while (actual->getSiguiente() != 0) actual = actual->getSiguiente();
        actual->setSiguiente(nuevo);
    }
    cantidad++;
}

Cliente* ListaClientes::buscar(const string& id) {
    NodoCliente* actual = primero;
    while (actual != 0) {
        if (actual->getDato()->getIdentificacion() == id) return actual->getDato();
        actual = actual->getSiguiente();
    }
    return 0;
}

bool ListaClientes::eliminar(const string& id) {
    NodoCliente* actual = primero;
    NodoCliente* anterior = 0;
    while (actual != 0) {
        if (actual->getDato()->getIdentificacion() == id) {
            if (anterior == 0) primero = actual->getSiguiente();
            else anterior->setSiguiente(actual->getSiguiente());
            delete actual->getDato();
            delete actual;
            cantidad--;
            return true;
        }
        anterior = actual;
        actual = actual->getSiguiente();
    }
    return false;
}

Cliente* ListaClientes::obtener(int pos) {
    if (pos < 0 || pos >= cantidad) return 0;
    NodoCliente* actual = primero;
    for (int i = 0; i < pos; i++) actual = actual->getSiguiente();
    return actual->getDato();
}

int ListaClientes::getCantidad() const { return cantidad; }

ListaClientes::~ListaClientes() {
    while (primero != 0) {
        NodoCliente* siguiente = primero->getSiguiente();
        delete primero->getDato();
        delete primero;
        primero = siguiente;
    }
}
