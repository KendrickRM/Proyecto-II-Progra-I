#ifndef MENUCLIENTES_H
#define MENUCLIENTES_H

#include "CentroDistribucion.h"
using namespace std;

// Persona 3. Submenu de Clientes de un centro.
// MenuPrincipal::menuClientes() solo debe elegir el centro y llamar a ejecutar().
class MenuClientes {
public:
	static void ejecutar(CentroDistribucion* centro);
};

#endif
