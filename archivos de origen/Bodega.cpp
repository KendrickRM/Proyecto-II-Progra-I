#include "Bodega.h"
#include <iostream>
#include <sstream>
using namespace std;

static string padIzq(const string& s, int ancho) {
    string r = s;
    while ((int)r.size() < ancho) {
        r = " " + r;
    }
    return r;
}

static string padDer(const string& s, int ancho) {
    string r = s;
    while ((int)r.size() < ancho) {
        r = r + " ";
    }
    return r;
}

Bodega::Bodega(const string& codigo, const string& nombre, int tipo, int filas, int columnas)
    : codigo(codigo), nombre(nombre), tipo(tipo), filas(filas), columnas(columnas), matriz(0) {
    

    if (this->filas < 1) {
        this->filas = 1;
    }
    if (this->columnas < 1) {
        this->columnas = 1;
    }

    bool largo = (this->filas > 10 || this->columnas > 10);

    
    matriz = new Celda * [this->filas];
    for (int i = 0; i < this->filas; i++) {
        matriz[i] = new Celda[this->columnas];
        for (int j = 0; j < this->columnas; j++) {
            matriz[i][j].inicializar(codigo, i, j, largo);
        }
    }
}

Bodega::~Bodega() {
    
    for (int i = 0; i < filas; i++) {
        delete[] matriz[i];
    }
    delete[] matriz;
}

string Bodega::getCodigo() const { return codigo; }
string Bodega::getNombre() const { return nombre; }
int Bodega::getTipo() const { return tipo; }
int Bodega::getFilas() const { return filas; }
int Bodega::getColumnas() const { return columnas; }

bool Bodega::tipoValido(int tipo) {
    return tipo >= 1 && tipo <= 4;
}

string Bodega::nombreTipo(int tipo) {
    switch (tipo) {
    case 1: return "General";
    case 2: return "Fragil";
    case 3: return "Tecnologia";
    case 4: return "Documentos";
    default: return "Desconocido";
    }
}

bool Bodega::esCompatible(int categoria) const {
    return categoria == tipo;
}

bool Bodega::posicionValida(int fila, int columna) const {
    return fila >= 0 && fila < filas && columna >= 0 && columna < columnas;
}

Celda* Bodega::getCelda(int fila, int columna) {
    if (!posicionValida(fila, columna)) {
        return 0;
    }
    return &matriz[fila][columna];
}

bool Bodega::asignarPaquete(int fila, int columna, Paquete* p) {
    Celda* c = getCelda(fila, columna);
    if (c == 0) {
        return false;
    }
    return c->asignar(p);
}

bool Bodega::liberarCelda(int fila, int columna) {
    Celda* c = getCelda(fila, columna);
    if (c == 0 || c->estaLibre()) {
        return false;
    }
    c->liberar();
    return true;
}

Celda* Bodega::primeraCeldaLibre() {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (matriz[i][j].estaLibre()) {
                return &matriz[i][j];
            }
        }
    }
    return 0;
}

int Bodega::totalCeldas() const {
    return filas * columnas;
}

int Bodega::celdasOcupadas() const {
    int n = 0;
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (!matriz[i][j].estaLibre()) {
                n++;
            }
        }
    }
    return n;
}

int Bodega::celdasLibres() const {
    return totalCeldas() - celdasOcupadas();
}

bool Bodega::todasLibres() const {
    return celdasOcupadas() == 0;
}

double Bodega::porcentajeOcupacion() const {
    return (celdasOcupadas() * 100.0) / totalCeldas();
}

double Bodega::porcentajeDisponible() const {
    return 100.0 - porcentajeOcupacion();
}

string Bodega::getOcupacionTexto() const {
    ostringstream os;
    os.setf(ios::fixed);
    os.precision(1);
    os << porcentajeOcupacion() << "%";
    return os.str();
}

void Bodega::mostrar() const {
    cout << "Codigo: " << codigo
        << " | Nombre: " << nombre
        << " | Tipo: " << nombreTipo(tipo)
        << " | Tamano: " << filas << "x" << columnas
        << " | Ocupadas: " << celdasOcupadas() << "/" << totalCeldas()
        << " (" << getOcupacionTexto() << ")" << endl;
}

void Bodega::dibujar() const {
    cout << "Bodega " << codigo << " - " << nombre << " (" << nombreTipo(tipo) << ") "
        << filas << "x" << columnas << endl;

    // Encabezado con numero de columna
    cout << "     ";
    for (int j = 0; j < columnas; j++) {
        cout << padDer(to_string(j), 3) << " ";
    }
    cout << endl;

    for (int i = 0; i < filas; i++) {
        cout << padIzq(to_string(i), 3) << "  ";
        for (int j = 0; j < columnas; j++) {
            if (matriz[i][j].estaLibre()) {
                cout << "[ ] ";
            }
            else {
                cout << "[X] ";
            }
        }
        cout << endl;
    }
    cout << "[ ] libre   [X] ocupada" << endl;
}