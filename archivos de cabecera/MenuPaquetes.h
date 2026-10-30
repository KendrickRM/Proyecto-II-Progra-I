#ifndef MENUPAQUETES_H
#define MENUPAQUETES_H

#include "Sistema.h"
using namespace std;

//Submenu de Paquetes de un centro
class MenuPaquetes {
public:
    static void ejecutar(Sistema* sistema, CentroDistribucion* centro);
};

#endif