#include "Relaciones.h"

SolicitudEnvio* Relaciones::solicitudPendienteDe(CentroDistribucion* centro, Paquete* paquete) {
	ListaSolicitudes* lista = centro->getSolicitudes();
	for (int i = 0; i < lista->getCantidad(); i++) {
		SolicitudEnvio* s = lista->obtener(i);
		if (s->getPaquete() == paquete && s->estaPendiente()) {
			return s;
		}
	}
	return 0;
}

SolicitudEnvio* Relaciones::solicitudAprobadaDe(CentroDistribucion* centro, Paquete* paquete) {
	ListaSolicitudes* lista = centro->getSolicitudes();
	for (int i = 0; i < lista->getCantidad(); i++) {
		SolicitudEnvio* s = lista->obtener(i);
		if (s->getPaquete() == paquete && s->getEstado() == SolicitudEnvio::APROBADA) {
			return s;
		}
	}
	return 0;
}

bool Relaciones::paqueteTieneSolicitudes(CentroDistribucion* centro, Paquete* paquete) {
	ListaSolicitudes* lista = centro->getSolicitudes();
	for (int i = 0; i < lista->getCantidad(); i++) {
		if (lista->obtener(i)->getPaquete() == paquete) {
			return true;
		}
	}
	return false;
}

Despacho* Relaciones::despachoDePaquete(CentroDistribucion* centro, Paquete* paquete) {
	ListaDespachos* lista = centro->getDespachos();
	for (int i = 0; i < lista->getCantidad(); i++) {
		Despacho* d = lista->obtener(i);
		if (d->getPaquete() == paquete) {
			return d;
		}
	}
	return 0;
}

bool Relaciones::clienteTieneDependencias(CentroDistribucion* centro, Cliente* cliente) {
	ListaPaquetes* paquetes = centro->getPaquetes();
	for (int i = 0; i < paquetes->getCantidad(); i++) {
		if (paquetes->obtener(i)->getPropietario() == cliente) {
			return true;
		}
	}
	ListaSolicitudes* solicitudes = centro->getSolicitudes();
	for (int i = 0; i < solicitudes->getCantidad(); i++) {
		if (solicitudes->obtener(i)->getCliente() == cliente) {
			return true;
		}
	}
	ListaDespachos* despachos = centro->getDespachos();
	for (int i = 0; i < despachos->getCantidad(); i++) {
		if (despachos->obtener(i)->getCliente() == cliente) {
			return true;
		}
	}
	return false;
}

bool Relaciones::colaboradorTieneDependencias(CentroDistribucion* centro, Colaborador* colaborador) {
	ListaSolicitudes* solicitudes = centro->getSolicitudes();
	for (int i = 0; i < solicitudes->getCantidad(); i++) {
		if (solicitudes->obtener(i)->getColaborador() == colaborador) {
			return true;
		}
	}
	ListaDespachos* despachos = centro->getDespachos();
	for (int i = 0; i < despachos->getCantidad(); i++) {
		if (despachos->obtener(i)->getColaborador() == colaborador) {
			return true;
		}
	}
	ListaPaquetes* paquetes = centro->getPaquetes();
	for (int i = 0; i < paquetes->getCantidad(); i++) {
		if (paquetes->obtener(i)->tieneColaboradorEnBitacora(colaborador->getIdentificacion())) {
			return true;
		}
	}
	return false;
}
