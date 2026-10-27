#ifndef MENUPAQUETES_H
#define MENUPAQUETES_H

#include "Sistema.h"
using namespace std;

// Persona 2. Submenu de Paquetes de un centro.
// MenuPrincipal::menuPaquetes() solo debe elegir el centro y llamar a ejecutar().
class MenuPaquetes {
public:
    static void ejecutar(Sistema* sistema, CentroDistribucion* centro);
};

#endif