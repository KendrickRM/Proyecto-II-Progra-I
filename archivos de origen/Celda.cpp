#include "Celda.h"
using namespace std;

static string dosDigitos(int n) {
    if (n < 10) {
        return "0" + to_string(n);
    }
    return to_string(n);
}

Celda::Celda()
    : codigoBodega(""), fila(0), columna(0), formatoLargo(false), paquete(0) {
}

Celda::Celda(const string& codigoBodega, int fila, int columna, bool formatoLargo)
    : codigoBodega(codigoBodega), fila(fila), columna(columna),
    formatoLargo(formatoLargo), paquete(0) {
}

void Celda::inicializar(const string& codigoBodega, int fila, int columna, bool formatoLargo) {
    this->codigoBodega = codigoBodega;
    this->fila = fila;
    this->columna = columna;
    this->formatoLargo = formatoLargo;
    this->paquete = 0;
}

bool Celda::estaLibre() const { return paquete == 0; }
Paquete* Celda::getPaquete() const { return paquete; }
int Celda::getFila() const { return fila; }
int Celda::getColumna() const { return columna; }


string Celda::getIdentificador() const {
    if (!formatoLargo) {
        return codigoBodega + "-" + to_string(fila) + to_string(columna);
    }
    return codigoBodega + "-F" + dosDigitos(fila) + "-C" + dosDigitos(columna);
}

bool Celda::asignar(Paquete* p) {
    if (p == 0 || paquete != 0) {
        return false;
    }
    paquete = p;
    return true;
}

void Celda::liberar() {
    paquete = 0;
}