#include "MenuReportes.h"
#include "Utilidades.h"
#include "Relaciones.h"
#include "Tarifa.h"
#include <iostream>
#include <string>
using namespace std;

static CentroDistribucion* elegirCentro(Sistema* sistema) {
	ListaCentros* centros = sistema->getCentros();
	if (centros->getCantidad() == 0) {
		cout << "No hay centros registrados." << endl;
		return 0;
	}
	cout << "Centros disponibles:" << endl;
	for (int i = 0; i < centros->getCantidad(); i++) {
		cout << "  " << centros->obtener(i)->getCodigo() << " - " << centros->obtener(i)->getNombre() << endl;
	}
	string codigo = Utilidades::leerCodigoCentro("Codigo del centro: ");
	CentroDistribucion* centro = sistema->buscarCentro(codigo);
	if (centro == 0) {
		cout << "No existe un centro con ese codigo." << endl;
	}
	return centro;
}

//Reporte 1: Historial de un cliente
static void reporteHistorialCliente(Sistema* sistema) {
	cout << "--- Historial de un cliente ---" << endl;
	CentroDistribucion* centro = elegirCentro(sistema);
	if (centro == 0) {
		return;
	}
	string id = Utilidades::leerTexto("Identificacion del cliente: ");
	Cliente* cliente = centro->getClientes()->buscar(id);
	if (cliente == 0) {
		cout << "No existe un cliente con esa identificacion en este centro." << endl;
		return;
	}
	cout << "Cliente: " << cliente->getNombre() << " (" << cliente->getIdentificacion() << ")" << endl;

	cout << endl << "Solicitudes:" << endl;
	int totalSolicitudes = 0;
	ListaSolicitudes* solicitudes = centro->getSolicitudes();
	for (int i = 0; i < solicitudes->getCantidad(); i++) {
		SolicitudEnvio* s = solicitudes->obtener(i);
		if (s->getCliente() == cliente) {
			cout << "  Codigo: " << s->getCodigo() << " | Paquete: " << s->getPaquete()->getCodigo()
				<< " | Fecha: " << s->getFechaSolicitud().aTexto()
				<< " | Estado: " << s->getNombreEstado() << endl;
			totalSolicitudes++;
		}
	}
	if (totalSolicitudes == 0) {
		cout << "  El cliente no tiene solicitudes." << endl;
	}

	cout << endl << "Despachos:" << endl;
	int totalDespachos = 0;
	ListaDespachos* despachos = centro->getDespachos();
	for (int i = 0; i < despachos->getCantidad(); i++) {
		Despacho* d = despachos->obtener(i);
		if (d->getCliente() == cliente) {
			cout << "  Codigo: " << d->getCodigo() << " | Paquete: " << d->getPaquete()->getCodigo()
				<< " | Fecha: " << d->getFechaDespacho().aTextoConHora()
				<< " | Estado: " << d->getNombreEstado() << endl;
			totalDespachos++;
		}
	}
	if (totalDespachos == 0) {
		cout << "  El cliente no tiene despachos." << endl;
	}
}

//Reporte 2: Clientes por cantidad de envios
static void reporteClientesPorEnvios(Sistema* sistema) {
	cout << "--- Clientes por cantidad de envios ---" << endl;
	CentroDistribucion* centro = elegirCentro(sistema);
	if (centro == 0) {
		return;
	}
	ListaClientes* clientes = centro->getClientes();
	int n = clientes->getCantidad();
	if (n == 0) {
		cout << "No hay clientes registrados en este centro." << endl;
		return;
	}

	Cliente** orden = new Cliente*[n];
	int* cuenta = new int[n];
	ListaDespachos* despachos = centro->getDespachos();
	for (int i = 0; i < n; i++) {
		orden[i] = clientes->obtener(i);
		cuenta[i] = 0;
		for (int j = 0; j < despachos->getCantidad(); j++) {
			Despacho* d = despachos->obtener(j);
			if (d->getCliente() == orden[i] && d->getEstado() == Despacho::FINALIZADO) {
				cuenta[i]++;
			}
		}
	}

	
	for (int i = 1; i < n; i++) {
		Cliente* clienteActual = orden[i];
		int cuentaActual = cuenta[i];
		int j = i - 1;
		while (j >= 0 && cuenta[j] < cuentaActual) {
			orden[j + 1] = orden[j];
			cuenta[j + 1] = cuenta[j];
			j--;
		}
		orden[j + 1] = clienteActual;
		cuenta[j + 1] = cuentaActual;
	}

	for (int i = 0; i < n; i++) {
		cout << (i + 1) << ". " << orden[i]->getNombre() << " (" << orden[i]->getIdentificacion()
			<< ") - envios finalizados: " << cuenta[i] << endl;
	}
	delete[] orden;
	delete[] cuenta;
}

//Reporte 3: Bitacora de un paquete
static void reporteBitacoraPaquete(Sistema* sistema) {
	cout << "--- Bitacora de un paquete ---" << endl;
	string codigo = Utilidades::leerCodigoPaquete("Codigo del paquete: ");
	Paquete* p = sistema->buscarPaquete(codigo);
	if (p == 0) {
		cout << "No existe un paquete con ese codigo." << endl;
		return;
	}
	cout << "Paquete " << p->getCodigo() << " - " << p->getDescripcion()
		<< " (estado actual: " << p->getNombreEstado() << ")" << endl;
	p->mostrarBitacora();
}

//Reporte 4: Consulta de despacho de un paquete
static void reporteDespachoDePaquete(Sistema* sistema) {
	cout << "--- Consulta de despacho de un paquete ---" << endl;
	string codigo = Utilidades::leerCodigoPaquete("Codigo del paquete: ");
	Paquete* p = sistema->buscarPaquete(codigo);
	if (p == 0) {
		cout << "No existe un paquete con ese codigo." << endl;
		return;
	}
	CentroDistribucion* centro = sistema->buscarCentro(p->getCodigoCentro());
	SolicitudEnvio* s = 0;
	Despacho* d = 0;
	if (centro != 0) {
		s = Relaciones::solicitudAprobadaDe(centro, p);
		d = Relaciones::despachoDePaquete(centro, p);
	}
	if (s == 0 && d == 0) {
		cout << "El paquete " << p->getCodigo() << " no posee despacho." << endl;
		return;
	}
	if (s != 0) {
		cout << "Solicitud aprobada: " << s->getCodigo() << " | Fecha: " << s->getFechaSolicitud().aTexto()
			<< " | Estado: " << s->getNombreEstado() << endl;
	}
	if (d != 0) {
		cout << "Despacho: " << d->getCodigo() << " | Fecha: " << d->getFechaDespacho().aTextoConHora()
			<< " | Estado: " << d->getNombreEstado() << endl;
	}
}

//Reporte 5: Ocupacion de bodegas
static void reporteOcupacionBodegas(Sistema* sistema) {
	cout << "--- Ocupacion de bodegas ---" << endl;
	ListaCentros* centros = sistema->getCentros();
	if (centros->getCantidad() == 0) {
		cout << "No hay centros registrados." << endl;
		return;
	}
	for (int i = 0; i < centros->getCantidad(); i++) {
		CentroDistribucion* centro = centros->obtener(i);
		cout << endl << "Centro " << centro->getCodigo() << " - " << centro->getNombre() << endl;
		ListaBodegas* bodegas = centro->getBodegas();
		if (bodegas->getCantidad() == 0) {
			cout << "  Sin bodegas registradas." << endl;
			continue;
		}
		int totalCentro = 0;
		int ocupadasCentro = 0;
		for (int j = 0; j < bodegas->getCantidad(); j++) {
			Bodega* b = bodegas->obtener(j);
			cout << "  Bodega " << b->getCodigo() << " (" << b->getNombre() << ") | Total: " << b->totalCeldas()
				<< " | Ocupadas: " << b->celdasOcupadas() << " | Disponibles: " << b->celdasLibres()
				<< " | Ocupacion: " << Tarifa::formatearDecimal(b->porcentajeOcupacion()) << "%" << endl;
			totalCentro += b->totalCeldas();
			ocupadasCentro += b->celdasOcupadas();
		}
		double porcentaje = 0;
		if (totalCentro > 0) {
			porcentaje = (double)ocupadasCentro / totalCentro * 100;
		}
		cout << "  TOTAL DEL CENTRO | Total: " << totalCentro << " | Ocupadas: " << ocupadasCentro
			<< " | Disponibles: " << (totalCentro - ocupadasCentro)
			<< " | Ocupacion: " << Tarifa::formatearDecimal(porcentaje) << "%" << endl;
	}
}

//Reporte 6: Despachos por colaborador
static void reporteDespachosPorColaborador(Sistema* sistema) {
	cout << "--- Despachos por colaborador ---" << endl;
	CentroDistribucion* centro = elegirCentro(sistema);
	if (centro == 0) {
		return;
	}
	string id = Utilidades::leerTexto("Identificacion del colaborador: ");
	Colaborador* colaborador = centro->getColaboradores()->buscar(id);
	if (colaborador == 0) {
		cout << "No existe un colaborador con esa identificacion en este centro." << endl;
		return;
	}
	cout << "Colaborador: " << colaborador->getNombreCompleto() << " (" << colaborador->getIdentificacion() << ")" << endl;
	int total = 0;
	ListaDespachos* despachos = centro->getDespachos();
	for (int i = 0; i < despachos->getCantidad(); i++) {
		Despacho* d = despachos->obtener(i);
		if (d->getColaborador() == colaborador) {
			cout << "  Codigo: " << d->getCodigo() << " | Paquete: " << d->getPaquete()->getCodigo()
				<< " | Fecha: " << d->getFechaDespacho().aTextoConHora()
				<< " | Estado: " << d->getNombreEstado() << endl;
			total++;
		}
	}
	if (total == 0) {
		cout << "  El colaborador no ha gestionado despachos." << endl;
	}
}

void MenuReportes::ejecutar(Sistema* sistema) {
	if (sistema == 0) {
		return;
	}
	int op;
	do {
		system("cls");
		cout << endl << "===== REPORTES =====" << endl;
		cout << "1. Historial de un cliente" << endl;
		cout << "2. Clientes por cantidad de envios" << endl;
		cout << "3. Bitacora de un paquete" << endl;
		cout << "4. Consulta de despacho de un paquete" << endl;
		cout << "5. Ocupacion de bodegas" << endl;
		cout << "6. Despachos por colaborador" << endl;
		cout << "0. Volver" << endl;
		op = Utilidades::leerOpcion(0, 6);
		switch (op) {
		case 1: reporteHistorialCliente(sistema); break;
		case 2: reporteClientesPorEnvios(sistema); break;
		case 3: reporteBitacoraPaquete(sistema); break;
		case 4: reporteDespachoDePaquete(sistema); break;
		case 5: reporteOcupacionBodegas(sistema); break;
		case 6: reporteDespachosPorColaborador(sistema); break;
		default: break;
		}
		if (op != 0) {
			system("pause");
		}
	} while (op != 0);
}
