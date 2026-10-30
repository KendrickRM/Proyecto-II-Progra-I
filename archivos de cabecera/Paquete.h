#ifndef PAQUETE_H
#define PAQUETE_H

#include <string>
#include "Cliente.h"
#include "Colaborador.h"
#include "Fecha.h"
#include "Celda.h"
#include "Bodega.h"
#include "ListaBitacora.h"


using namespace std;

class Paquete {
public:
    enum Estado {
        RECIBIDO = 1, ALMACENADO = 2, EN_TRANSITO = 3, ENTREGADO = 4, INCIDENCIA = 5
    };

private:
    string codigo;
    string descripcion;
    double peso;
    int categoria;               
    Cliente* propietario;        
    string codigoCentro;        
    int estado;
    int estadoPrevioIncidencia;  
    Bodega* bodega;              
    Celda* celda;                
    ListaBitacora* bitacora;

    Paquete(const Paquete&);
    Paquete& operator=(const Paquete&);

    void aplicarCambio(int nuevo, Colaborador* responsable, const Fecha& fecha);

public:
    Paquete(const string& codigo, const string& descripcion, double peso,
        int categoria, Cliente* propietario, const string& codigoCentro);
    ~Paquete();

    string getCodigo() const;
    string getDescripcion() const;
    double getPeso() const;
    int getCategoria() const;
    string getNombreCategoria() const;
    Cliente* getPropietario() const;
    string getCodigoCentro() const;
    int getEstado() const;
    string getNombreEstado() const;
    Bodega* getBodega() const;
    Celda* getCelda() const;
    ListaBitacora* getBitacora() const;


    static double pesoMaximo();

    static bool categoriaValida(int categoria);
    static string nombreEstado(int estado);

    bool puedeCambiarA(int nuevo) const;

    bool necesitaAlmacenarse() const;

    //Estado previo a la ultima incidencia
    int getEstadoPrevioIncidencia() const;


    bool almacenar(Bodega* bodega, Celda* celda, Colaborador* responsable, const Fecha& fecha);
    bool reubicar(Bodega* nuevaBodega, Celda* nuevaCelda);   
    bool pasarATransito(Colaborador* responsable, const Fecha& fecha);   
    bool marcarEntregado(Colaborador* responsable, const Fecha& fecha);
    bool registrarIncidencia(Colaborador* responsable, const Fecha& fecha);
    bool resolverIncidencia(Colaborador* responsable, const Fecha& fecha);

    bool tieneColaboradorEnBitacora(const string& identificacion) const;

    void mostrar() const;
    void mostrarBitacora() const;

};

#endif