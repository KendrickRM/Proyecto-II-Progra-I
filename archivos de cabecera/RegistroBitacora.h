#ifndef REGISTROBITACORA_H
#define REGISTROBITACORA_H

#include "Fecha.h"
using namespace std;

class Colaborador;  


class RegistroBitacora {
private:
    int estadoAnterior;
    int estadoNuevo;
    Fecha fecha;
    Colaborador* responsable;   
public:
    RegistroBitacora(int estadoAnterior, int estadoNuevo,
        const Fecha& fecha, Colaborador* responsable);

    int getEstadoAnterior() const;
    int getEstadoNuevo() const;
    Fecha getFecha() const;
    Colaborador* getResponsable() const;

    void mostrar() const;
};

#endif