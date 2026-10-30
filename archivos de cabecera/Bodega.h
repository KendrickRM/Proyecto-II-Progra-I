#ifndef BODEGA_H
#define BODEGA_H

#include <string>
#include "Celda.h"

using namespace std;

class Bodega {
private:
    string codigo;
    string nombre;
    int tipo;
    int filas;
    int columnas;
    Celda** matriz;
public:
    Bodega(const string& codigo, const string& nombre, int tipo, int filas, int columnas);
    ~Bodega();

    string getCodigo() const;
    string getNombre() const;
    int getTipo() const;
    int getFilas() const;
    int getColumnas() const;

    // Maximo de filas y de columnas (el minimo es 1)
    static int dimensionMaxima();

    static bool tipoValido(int tipo);
    static string nombreTipo(int tipo);

    
    bool esCompatible(int categoria) const;

    
    bool posicionValida(int fila, int columna) const;
    Celda* getCelda(int fila, int columna);          
    bool asignarPaquete(int fila, int columna, Paquete* p);
    bool liberarCelda(int fila, int columna);
    Celda* primeraCeldaLibre();                      
    

    int totalCeldas() const;
    int celdasOcupadas() const;
    int celdasLibres() const;
    bool todasLibres() const;
    double porcentajeOcupacion() const;
    double porcentajeDisponible() const;
    string getOcupacionTexto() const;               

    void mostrar() const;                            
    void dibujar() const;                            
};

#endif
