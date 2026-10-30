#ifndef MENUSOLICITUDES_H
#define MENUSOLICITUDES_H

#include "Sistema.h"
using namespace std;

// Persona 3. Submenu de Solicitudes de envio de un centro (incluye aprobar, que crea el despacho).
class MenuSolicitudes {
public:
	static void ejecutar(Sistema* sistema, CentroDistribucion* centro);
};

#endif
