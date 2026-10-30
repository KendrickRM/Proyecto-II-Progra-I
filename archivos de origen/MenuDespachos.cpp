#include "MenuDespachos.h"
#include "Utilidades.h"
#include <iostream>
#include <string>
using namespace std;

static void buscarDespacho(Sistema* sistema) {
	cout << "--- Buscar despacho ---" << endl;
	string codigo = Utilidades::leerTexto("Codigo del despacho: ");
	Despacho* d = sistema->buscarDespacho(codigo);
	if (d == 0) {
		cout << "No existe un despacho con ese codigo." << endl;
		return;
	}
	cout << d->toStringDespacho();
}

static void mostrarDespachos(CentroDistribucion* centro) {
	cout << "--- Despachos del centro ---" << endl;
	ListaDespachos* lista = centro->getDespachos();
	if (lista->getCantidad() == 0) {
		cout << "No hay despachos registrados en este centro." << endl;
		return;
	}
	for (int i = 0; i < lista->getCantidad(); i++) {
		cout << "---------------------------" << endl;
		cout << lista->obtener(i)->toStringDespacho();
	}
	cout << "---------------------------" << endl;
}

static void finalizarEntrega(Sistema* sistema, CentroDistribucion* centro) {
	cout << "--- Finalizar entrega ---" << endl;
	string codigo = Utilidades::leerTexto("Codigo del despacho: ");
	Despacho* d = centro->getDespachos()->buscar(codigo);
	if (d == 0) {
		if (sistema->codigoDespachoExiste(codigo)) {
			cout << "Ese despacho existe, pero pertenece a otro centro." << endl;
		}
		else {
			cout << "No existe un despacho con ese codigo." << endl;
		}
		return;
	}
	if (d->getEstado() != Despacho::EN_PROCESO) {
		cout << "No se puede finalizar: el despacho esta " << d->getNombreEstado() << "." << endl;
		return;
	}
	Paquete* paquete = d->getPaquete();
	if (paquete->getEstado() != Paquete::EN_TRANSITO) {
		cout << "No se puede finalizar: el paquete debe estar En transito. Estado actual: "
			<< paquete->getNombreEstado() << "." << endl;
		return;
	}
	Fecha fecha = Fecha::leerFecha("Fecha de la entrega:");
	// El responsable del cambio es el colaborador asociado al despacho
	if (!paquete->marcarEntregado(d->getColaborador(), fecha)) {
		cout << "No se pudo marcar el paquete como Entregado. No se realizo ningun cambio." << endl;
		return;
	}
	d->finalizar();
	cout << "Entrega finalizada. Despacho Finalizado y paquete Entregado." << endl;
}

void MenuDespachos::ejecutar(Sistema* sistema, CentroDistribucion* centro) {
	if (sistema == 0 || centro == 0) {
		return;
	}
	int op;
	do {
		system("cls");
		cout << endl << "===== DESPACHOS (Centro: " << centro->getNombre() << ") =====" << endl;
		cout << "1. Buscar despacho por codigo" << endl;
		cout << "2. Mostrar despachos del centro" << endl;
		cout << "3. Finalizar entrega" << endl;
		cout << "0. Volver" << endl;
		op = Utilidades::leerOpcion(0, 3);
		switch (op) {
		case 1: buscarDespacho(sistema); break;
		case 2: mostrarDespachos(centro); break;
		case 3: finalizarEntrega(sistema, centro); break;
		default: break;
		}
		if (op != 0) {
			system("pause");
		}
	} while (op != 0);
}
