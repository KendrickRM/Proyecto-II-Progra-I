#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>
using namespace std;

class Cliente {
protected:
    string identificacion;
    string nombre;
    string telefono;
    string correo;

public:
    Cliente(const string& identificacion, const string& nombre,
        const string& telefono, const string& correo);
    string getIdentificacion() const;
    string getNombre() const;
    string getTelefono() const;
    string getCorreo() const;
    virtual double obtenerDescuento() const;
    virtual void mostrar() const;
    virtual ~Cliente();
};

#endif