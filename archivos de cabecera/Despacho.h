#ifndef DESPACHO_H
#define DESPACHO_H

#include <string>
#include "SolicitudEnvio.h"
#include "Paquete.h"
#include "Cliente.h"
#include "Colaborador.h"
#include "Fecha.h"
using namespace std;

class Despacho {
public:
    enum Estado {
        EN_PROCESO = 1, FINALIZADO = 2
    };

private:
    string codigo;
    SolicitudEnvio* solicitud;
    Paquete* paquete;
    Cliente* cliente;
    Colaborador* colaborador;
    string centroOrigen;
    string destino;
    Fecha fechaDespacho;    // incluye hora y minuto
    int estado;

public:
    //Nace En proceso
    Despacho(string codigo, SolicitudEnvio* solicitud, Paquete* paquete, Cliente* cliente,
        Colaborador* colaborador, string centroOrigen, string destino, Fecha fechaDespacho);
    string toStringDespacho();

    string getCodigo() const { return codigo; }
    SolicitudEnvio* getSolicitud() const { return solicitud; }
    Paquete* getPaquete() const { return paquete; }
    Cliente* getCliente() const { return cliente; }
    Colaborador* getColaborador() const { return colaborador; }
    string getCentroOrigen() const { return centroOrigen; }
    string getDestino() const { return destino; }
    Fecha getFechaDespacho() const { return fechaDespacho; }
    int getHora() const { return fechaDespacho.getHora(); }
    int getMinuto() const { return fechaDespacho.getMinuto(); }
    int getEstado() const { return estado; }
    string getNombreEstado() const { return nombreEstado(estado); }

    //Solo En proceso -> Finalizado
    bool finalizar();

    static string nombreEstado(int estado);

    ~Despacho();
};

#endif
