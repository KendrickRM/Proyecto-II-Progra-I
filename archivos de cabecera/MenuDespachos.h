#ifndef MENUDESPACHOS_H
#define MENUDESPACHOS_H

#include "Sistema.h"
using namespace std;

// Persona 3. Submenu de Despachos de un centro.
class MenuDespachos {
public:
	static void ejecutar(Sistema* sistema, CentroDistribucion* centro);
};

#endif
