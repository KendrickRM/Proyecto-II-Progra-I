#ifndef RELACIONES_H
#define RELACIONES_H

#include "CentroDistribucion.h"
using namespace std;

// Persona 3. Consultas sobre las relaciones entre paquetes, solicitudes y despachos de un centro.
// Las usan los menus para validar creaciones, aprobaciones y eliminaciones.
class Relaciones {
public:
	static SolicitudEnvio* solicitudPendienteDe(CentroDistribucion* centro, Paquete* paquete);
	static SolicitudEnvio* solicitudAprobadaDe(CentroDistribucion* centro, Paquete* paquete);
	static bool paqueteTieneSolicitudes(CentroDistribucion* centro, Paquete* paquete);
	static Despacho* despachoDePaquete(CentroDistribucion* centro, Paquete* paquete);

	static bool clienteTieneDependencias(CentroDistribucion* centro, Cliente* cliente);
	static bool colaboradorTieneDependencias(CentroDistribucion* centro, Colaborador* colaborador);
};

#endif
