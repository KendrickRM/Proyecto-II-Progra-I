#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H

#include "Sistema.h"
using namespace std;

class MenuPrincipal {
private:
    Sistema* sistema;

    void mostrarMenuPrincipal();
    void menuCentros();
    void menuClientes();        // Persona 3
    void menuColaboradores();   // Persona 3
    void menuBodegas();         // Persona 2
    void menuPaquetes();        // Persona 2
    void menuSolicitudes();     // Persona 3
    void menuDespachos();       // Persona 3
    void menuReportes();        // Persona 3

    CentroDistribucion* seleccionarCentro();

    void registrarCentro();
    void buscarCentro();
    void eliminarCentro();

public:
    MenuPrincipal(Sistema* sistema);
    void ejecutar();
};

#endif
