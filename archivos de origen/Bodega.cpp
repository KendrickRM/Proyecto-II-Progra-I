#include "Bodega.h"
#include "Paquete.h"
#include <iostream>
#include <sstream>
using namespace std;

// Centra el texto dentro de 'ancho' caracteres (si sobra un espacio, va a la derecha)
static string centrar(const string& s, int ancho) {
    int falta = ancho - (int)s.size();
    if (falta <= 0) {
        return s;
    }
    int izquierda = falta / 2;
    return string(izquierda, ' ') + s + string(falta - izquierda, ' ');
}

Bodega::Bodega(const string& codigo, const string& nombre, int tipo, int filas, int columnas)
    : codigo(codigo), nombre(nombre), tipo(tipo), filas(filas), columnas(columnas), matriz(0) {
    

    if (this->filas < 1) {
        this->filas = 1;
    }
    if (this->columnas < 1) {
        this->columnas = 1;
    }
    if (this->filas > dimensionMaxima()) {
        this->filas = dimensionMaxima();
    }
    if (this->columnas > dimensionMaxima()) {
        this->columnas = dimensionMaxima();
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

int Bodega::dimensionMaxima() {
    return 50;
}

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

    // Ancho de celda: el texto mas largo entre identificador, LIBRE y codigo de paquete
    int ancho = 5;
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            int largo = (int)matriz[i][j].getIdentificador().size();
            if (largo > ancho) {
                ancho = largo;
            }
            if (!matriz[i][j].estaLibre()) {
                largo = (int)matriz[i][j].getPaquete()->getCodigo().size();
                if (largo > ancho) {
                    ancho = largo;
                }
            }
        }
    }

    // Si la bodega es muy ancha, las columnas se reparten en bloques que caben en la consola
    // (si no, cada fila se parte en varias lineas y la tabla se desordena)
    const int ANCHO_CONSOLA = 100;
    int columnasPorBloque = (ANCHO_CONSOLA - 1) / (ancho + 3);
    if (columnasPorBloque < 1) {
        columnasPorBloque = 1;
    }

    for (int inicio = 0; inicio < columnas; inicio += columnasPorBloque) {
        int fin = inicio + columnasPorBloque;
        if (fin > columnas) {
            fin = columnas;
        }

        if (columnas > columnasPorBloque) {
            cout << endl << "Columnas " << inicio << " a " << (fin - 1) << " (de 0 a " << (columnas - 1) << ")" << endl;
        }

        string separador = "+";
        for (int j = inicio; j < fin; j++) {
            separador += string(ancho + 2, '-') + "+";
        }

        // Cada celda tiene dos lineas: su identificador (A-00) y LIBRE o el codigo del paquete (PK101)
        cout << separador << endl;
        for (int i = 0; i < filas; i++) {
            cout << "|";
            for (int j = inicio; j < fin; j++) {
                cout << " " << centrar(matriz[i][j].getIdentificador(), ancho) << " |";
            }
            cout << endl << "|";
            for (int j = inicio; j < fin; j++) {
                string contenido = "LIBRE";
                if (!matriz[i][j].estaLibre()) {
                    contenido = matriz[i][j].getPaquete()->getCodigo();
                }
                cout << " " << centrar(contenido, ancho) << " |";
            }
            cout << endl << separador << endl;
        }
    }
}