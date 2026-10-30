#ifndef SOLICITUDENVIO_H
#define SOLICITUDENVIO_H

#include <string>
#include "Cliente.h"
#include "Paquete.h"
#include "Colaborador.h"
#include "Fecha.h"
using namespace std;

class SolicitudEnvio {
public:
    enum Estado {
        PENDIENTE = 1, APROBADA = 2, RECHAZADA = 3, ANULADA = 4
    };

private:
    string codigo;
    Cliente* cliente;
    Paquete* paquete;
    Colaborador* colaborador;
    string codigoCentro;
    string destino;
    Fecha fechaSolicitud;
    double costoEstimado;
    int estado;

public:
    // Nace Pendiente. El costo estimado se calcula con Tarifa (peso, categoria y descuento del cliente).
    SolicitudEnvio(string codigo, Cliente* cliente, Paquete* paquete, Colaborador* colaborador,
        string codigoCentro, string destino, Fecha fechaSolicitud);
    string toStringSolicitud();

    string getCodigo() const { return codigo; }
    Cliente* getCliente() const { return cliente; }
    Paquete* getPaquete() const { return paquete; }
    Colaborador* getColaborador() const { return colaborador; }
    string getCodigoCentro() const { return codigoCentro; }
    string getDestino() const { return destino; }
    Fecha getFechaSolicitud() const { return fechaSolicitud; }
    double getCostoEstimado() const { return costoEstimado; }
    int getEstado() const { return estado; }
    string getNombreEstado() const { return nombreEstado(estado); }

    bool estaPendiente() const { return estado == PENDIENTE; }

    // Solo permite Pendiente -> Aprobada, Rechazada o Anulada. Los estados finales no cambian.
    bool cambiarEstado(int nuevoEstado);

    static string nombreEstado(int estado);

    ~SolicitudEnvio();
};

#endif
