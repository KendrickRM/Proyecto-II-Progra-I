#include "MenuSolicitudes.h"
#include "Utilidades.h"
#include "Relaciones.h"
#include "Tarifa.h"
#include <iostream>
#include <string>
using namespace std;

static SolicitudEnvio* pedirSolicitud(Sistema* sistema, CentroDistribucion* centro) {
	string codigo = Utilidades::leerTexto("Codigo de la solicitud: ");
	SolicitudEnvio* s = centro->getSolicitudes()->buscar(codigo);
	if (s == 0) {
		if (sistema->codigoSolicitudExiste(codigo)) {
			cout << "Esa solicitud existe, pero pertenece a otro centro." << endl;
		}
		else {
			cout << "No existe una solicitud con ese codigo." << endl;
		}
	}
	return s;
}

static void crearSolicitud(Sistema* sistema, CentroDistribucion* centro) {
	cout << "--- Crear solicitud de envio ---" << endl;
	string codigo = Utilidades::leerCodigoTresDigitos("Codigo de la solicitud (3 digitos): ");
	if (sistema->codigoSolicitudExiste(codigo)) {
		cout << "Error: ya existe una solicitud con ese codigo en el sistema. Operacion cancelada." << endl;
		return;
	}

	string codigoPaquete = Utilidades::leerTexto("Codigo del paquete (ej: PK101): ");
	Paquete* paquete = centro->getPaquetes()->buscar(codigoPaquete);
	if (paquete == 0) {
		cout << "Error: no existe ese paquete en este centro. Operacion cancelada." << endl;
		return;
	}
	if (paquete->getEstado() != Paquete::ALMACENADO) {
		cout << "Error: solo se puede solicitar el envio de un paquete Almacenado. Estado actual: "
			<< paquete->getNombreEstado() << "." << endl;
		return;
	}
	if (Relaciones::solicitudPendienteDe(centro, paquete) != 0) {
		cout << "Error: el paquete ya tiene una solicitud Pendiente." << endl;
		return;
	}
	if (Relaciones::solicitudAprobadaDe(centro, paquete) != 0 || Relaciones::despachoDePaquete(centro, paquete) != 0) {
		cout << "Error: el paquete ya tiene una solicitud aprobada o un despacho." << endl;
		return;
	}

	string idCliente = Utilidades::leerIdCuatroDigitos("Identificacion del cliente (4 digitos): ");
	Cliente* cliente = centro->getClientes()->buscar(idCliente);
	if (cliente == 0) {
		cout << "Error: no existe ese cliente en este centro. Operacion cancelada." << endl;
		return;
	}
	if (cliente != paquete->getPropietario()) {
		cout << "Error: el cliente no es el propietario del paquete. Operacion cancelada." << endl;
		return;
	}

	string idColaborador = Utilidades::leerIdCuatroDigitos("Identificacion del colaborador responsable (4 digitos): ");
	Colaborador* colaborador = centro->getColaboradores()->buscar(idColaborador);
	if (colaborador == 0) {
		cout << "Error: no existe ese colaborador en este centro. Operacion cancelada." << endl;
		return;
	}

	string destino = Utilidades::leerTexto("Destino de entrega (direccion): ");
	Fecha fecha = Fecha::leerFecha("Fecha de la solicitud:");

	SolicitudEnvio* s = new SolicitudEnvio(codigo, cliente, paquete, colaborador, centro->getCodigo(), destino, fecha);
	centro->getSolicitudes()->insertar(s);
	cout << "Solicitud creada en estado Pendiente. Costo estimado: CRC "
		<< Tarifa::formatearDecimal(s->getCostoEstimado()) << "." << endl;
}

static void buscarSolicitud(Sistema* sistema) {
	cout << "--- Buscar solicitud ---" << endl;
	string codigo = Utilidades::leerTexto("Codigo de la solicitud: ");
	SolicitudEnvio* s = sistema->buscarSolicitud(codigo);
	if (s == 0) {
		cout << "No existe una solicitud con ese codigo." << endl;
		return;
	}
	cout << s->toStringSolicitud();
}

static void mostrarSolicitudes(CentroDistribucion* centro) {
	cout << "--- Solicitudes del centro ---" << endl;
	ListaSolicitudes* lista = centro->getSolicitudes();
	if (lista->getCantidad() == 0) {
		cout << "No hay solicitudes registradas en este centro." << endl;
		return;
	}
	for (int i = 0; i < lista->getCantidad(); i++) {
		cout << "---------------------------" << endl;
		cout << lista->obtener(i)->toStringSolicitud();
	}
	cout << "---------------------------" << endl;
}

static void aprobarSolicitud(Sistema* sistema, CentroDistribucion* centro) {
	cout << "--- Aprobar solicitud ---" << endl;
	SolicitudEnvio* s = pedirSolicitud(sistema, centro);
	if (s == 0) {
		return;
	}
	if (!s->estaPendiente()) {
		cout << "No se puede aprobar: la solicitud esta " << s->getNombreEstado() << "." << endl;
		return;
	}
	Paquete* paquete = s->getPaquete();
	if (paquete->getEstado() != Paquete::ALMACENADO) {
		cout << "No se puede aprobar: el paquete debe estar Almacenado. Estado actual: "
			<< paquete->getNombreEstado() << "." << endl;
		return;
	}
	if (Relaciones::despachoDePaquete(centro, paquete) != 0) {
		cout << "No se puede aprobar: el paquete ya tiene un despacho asociado." << endl;
		return;
	}

	string codigoDespacho = Utilidades::leerCodigoTresDigitos("Codigo del nuevo despacho (3 digitos): ");
	if (sistema->codigoDespachoExiste(codigoDespacho)) {
		cout << "Error: ya existe un despacho con ese codigo en el sistema. Operacion cancelada." << endl;
		return;
	}
	Fecha fecha = Fecha::leerFechaHora("Fecha y hora del despacho:");

	// El paquete pasa a En transito y libera su celda; el responsable es el de la solicitud
	if (!paquete->pasarATransito(s->getColaborador(), fecha)) {
		cout << "No se pudo pasar el paquete a En transito. No se realizo ningun cambio." << endl;
		return;
	}
	s->cambiarEstado(SolicitudEnvio::APROBADA);
	centro->getDespachos()->insertar(new Despacho(codigoDespacho, s, paquete, s->getCliente(),
		s->getColaborador(), s->getCodigoCentro(), s->getDestino(), fecha));
	cout << "Solicitud aprobada. Despacho " << codigoDespacho << " creado En proceso; "
		<< "el paquete esta En transito y su celda quedo libre." << endl;
}

static void cambiarAFinal(Sistema* sistema, CentroDistribucion* centro, int nuevoEstado, const string& accion) {
	cout << "--- " << accion << " solicitud ---" << endl;
	SolicitudEnvio* s = pedirSolicitud(sistema, centro);
	if (s == 0) {
		return;
	}
	if (!s->estaPendiente()) {
		cout << "No se puede cambiar: la solicitud esta " << s->getNombreEstado()
			<< " (estado final)." << endl;
		return;
	}
	s->cambiarEstado(nuevoEstado);
	cout << "Solicitud " << s->getCodigo() << " ahora esta " << s->getNombreEstado() << "." << endl;
}

void MenuSolicitudes::ejecutar(Sistema* sistema, CentroDistribucion* centro) {
	if (sistema == 0 || centro == 0) {
		return;
	}
	int op;
	do {
		system("cls");
		cout << endl << "===== SOLICITUDES (Centro: " << centro->getNombre() << ") =====" << endl;
		cout << "1. Crear solicitud" << endl;
		cout << "2. Buscar solicitud por codigo" << endl;
		cout << "3. Mostrar solicitudes del centro" << endl;
		cout << "4. Aprobar solicitud (crea el despacho)" << endl;
		cout << "5. Rechazar solicitud" << endl;
		cout << "6. Anular solicitud" << endl;
		cout << "0. Volver" << endl;
		op = Utilidades::leerOpcion(0, 6);
		switch (op) {
		case 1: crearSolicitud(sistema, centro); break;
		case 2: buscarSolicitud(sistema); break;
		case 3: mostrarSolicitudes(centro); break;
		case 4: aprobarSolicitud(sistema, centro); break;
		case 5: cambiarAFinal(sistema, centro, SolicitudEnvio::RECHAZADA, "Rechazar"); break;
		case 6: cambiarAFinal(sistema, centro, SolicitudEnvio::ANULADA, "Anular"); break;
		default: break;
		}
		if (op != 0) {
			system("pause");
		}
	} while (op != 0);
}
