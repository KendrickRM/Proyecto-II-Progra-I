#include "SolicitudEnvio.h"
#include "Tarifa.h"
#include <sstream>

SolicitudEnvio::SolicitudEnvio(string codigo, Cliente* cliente, Paquete* paquete, Colaborador* colaborador,
    string codigoCentro, string destino, Fecha fechaSolicitud) {
    this->codigo = codigo;
    this->cliente = cliente;
    this->paquete = paquete;
    this->colaborador = colaborador;
    this->codigoCentro = codigoCentro;
    this->destino = destino;
    this->fechaSolicitud = fechaSolicitud;
    this->estado = PENDIENTE;
    this->costoEstimado = 0;
    if (paquete != nullptr) {
        this->costoEstimado = Tarifa::calcularCostoFinal(paquete->getPeso(), paquete->getCategoria(), cliente);
    }
}

string SolicitudEnvio::toStringSolicitud() {
    stringstream ss;
    ss << "=====================\n";
    ss << "DATOS DE LA SOLICITUD\n";
    ss << "=====================\n";
    ss << "Codigo de la solicitud: " << codigo << endl
        << "Cliente: " << cliente->getNombre() << " (" << cliente->getIdentificacion() << ")" << endl
        << "Paquete: " << paquete->getCodigo() << " - " << paquete->getDescripcion() << endl
        << "Colaborador responsable: " << colaborador->getNombreCompleto() << endl
        << "Centro de origen: " << codigoCentro << endl
        << "Destino: " << destino << endl
        << "Fecha de solicitud: " << fechaSolicitud.aTexto() << endl
        << "Costo estimado: CRC " << Tarifa::formatearDecimal(costoEstimado) << endl
        << "Estado: " << getNombreEstado() << endl;
    return ss.str();
}

bool SolicitudEnvio::cambiarEstado(int nuevoEstado) {
    if (estado != PENDIENTE) {
        return false;
    }
    if (nuevoEstado != APROBADA && nuevoEstado != RECHAZADA && nuevoEstado != ANULADA) {
        return false;
    }
    estado = nuevoEstado;
    return true;
}

string SolicitudEnvio::nombreEstado(int estado) {
    switch (estado) {
    case PENDIENTE: return "Pendiente";
    case APROBADA: return "Aprobada";
    case RECHAZADA: return "Rechazada";
    case ANULADA: return "Anulada";
    default: return "Desconocido";
    }
}

SolicitudEnvio::~SolicitudEnvio() {
}
