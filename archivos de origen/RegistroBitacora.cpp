#include "RegistroBitacora.h"
#include "Colaborador.h"
#include "Paquete.h"
#include <iostream>
using namespace std;

RegistroBitacora::RegistroBitacora(int estadoAnterior, int estadoNuevo,
    const Fecha& fecha, Colaborador* responsable)
    : estadoAnterior(estadoAnterior), estadoNuevo(estadoNuevo),
    fecha(fecha), responsable(responsable) {
}

int RegistroBitacora::getEstadoAnterior() const { return estadoAnterior; }
int RegistroBitacora::getEstadoNuevo() const { return estadoNuevo; }
Fecha RegistroBitacora::getFecha() const { return fecha; }
Colaborador* RegistroBitacora::getResponsable() const { return responsable; }

void RegistroBitacora::mostrar() const {
    cout << Paquete::nombreEstado(estadoAnterior) << " -> "
        << Paquete::nombreEstado(estadoNuevo)
        << " | Fecha: " << fecha.aTexto()
        << " | Responsable: ";
    if (responsable != 0) {
        cout << responsable->getNombreCompleto()
            << " (" << responsable->getIdentificacion() << ")";
    }
    else {
        cout << "-";
    }
    cout << endl;
}