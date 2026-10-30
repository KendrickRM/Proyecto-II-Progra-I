#ifndef MENUPRINCIPAL_H
#define MENUPRINCIPAL_H

#include "Sistema.h"
using namespace std;

class MenuPrincipal {
private:
    Sistema* sistema;

    //Metodos Propios (Menus)
    void mostrarMenuPrincipal();
    void menuCentros();
    void menuClientes();
    void menuColaboradores();
    void menuBodegas();
    void menuPaquetes();
    void menuSolicitudes();
    void menuDespachos();
    void menuReportes();

    CentroDistribucion* seleccionarCentro();

    //Metodos Propios (Centros)
    void registrarCentro();
    void buscarCentro();
    void eliminarCentro();

public:
    MenuPrincipal(Sistema* sistema);
    void ejecutar();
};

#endif
