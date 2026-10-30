#ifndef CELDA_H
#define CELDA_H

#include <string>
using namespace std;

class Paquete;  

//Posicion de la matriz de una bodega
class Celda {
private:
    string codigoBodega;
    int fila;
    int columna;
    bool formatoLargo;   
    Paquete* paquete;    

public:
    Celda();
    Celda(const string& codigoBodega, int fila, int columna, bool formatoLargo);

    void inicializar(const string& codigoBodega, int fila, int columna, bool formatoLargo);

    bool estaLibre() const;
    Paquete* getPaquete() const;
    int getFila() const;
    int getColumna() const;
    string getIdentificador() const;

    bool asignar(Paquete* p);   
    void liberar();
};

#endif