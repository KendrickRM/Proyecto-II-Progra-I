#ifndef SISTEMA_H
#define SISTEMA_H

#include <string>
#include "ListaCentros.h"
#include "Paquete.h"
#include "SolicitudEnvio.h"
#include "Despacho.h"
using namespace std;

class Sistema {
private:
    ListaCentros* centros;

public:
    Sistema();
    ~Sistema();

    bool registrarCentro(CentroDistribucion* c);
    CentroDistribucion* buscarCentro(const string& codigo);
    bool eliminarCentro(const string& codigo);
    void mostrarCentros();
    ListaCentros* getCentros();

    bool codigoCentroExiste(const string& codigo);
    bool codigoPaqueteExiste(const string& codigo);
    bool codigoSolicitudExiste(const string& codigo);
    bool codigoDespachoExiste(const string& codigo);

    Paquete* buscarPaquete(const string& codigo);
    SolicitudEnvio* buscarSolicitud(const string& codigo);
    Despacho* buscarDespacho(const string& codigo);

    void cargarDatosQuemados();
};

#endif