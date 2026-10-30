#include "Despacho.h"
#include <sstream>

Despacho::Despacho(string codigo, SolicitudEnvio* solicitud, Paquete* paquete, Cliente* cliente,
    Colaborador* colaborador, string centroOrigen, string destino, Fecha fechaDespacho) {
    this->codigo = codigo;
    this->solicitud = solicitud;
    this->paquete = paquete;
    this->cliente = cliente;
    this->colaborador = colaborador;
    this->centroOrigen = centroOrigen;
    this->destino = destino;
    this->fechaDespacho = fechaDespacho;
    this->estado = EN_PROCESO;
}

string Despacho::toStringDespacho() {
    stringstream ss;
    ss << "=====================\n";
    ss << "DATOS DEL DESPACHO\n";
    ss << "=====================\n";
    ss << "Codigo del despacho: " << codigo << endl
        << "Solicitud: " << solicitud->getCodigo() << endl
        << "Paquete: " << paquete->getCodigo() << " - " << paquete->getDescripcion() << endl
        << "Cliente: " << cliente->getNombre() << " (" << cliente->getIdentificacion() << ")" << endl
        << "Colaborador responsable: " << colaborador->getNombreCompleto() << endl
        << "Centro de origen: " << centroOrigen << endl
        << "Destino: " << destino << endl
        << "Fecha y hora: " << fechaDespacho.aTextoConHora() << endl
        << "Estado: " << getNombreEstado() << endl;
    return ss.str();
}

bool Despacho::finalizar() {
    if (estado != EN_PROCESO) {
        return false;
    }
    estado = FINALIZADO;
    return true;
}

string Despacho::nombreEstado(int estado) {
    if (estado == EN_PROCESO) {
        return "En proceso";
    }
    if (estado == FINALIZADO) {
        return "Finalizado";
    }
    return "Desconocido";
}

Despacho::~Despacho() {
}
