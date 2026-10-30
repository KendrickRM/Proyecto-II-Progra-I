#include "MenuColaboradores.h"
#include "Utilidades.h"
#include "Relaciones.h"
#include "Colaborador.h"
#include "Fecha.h"
#include <iostream>
#include <string>
using namespace std;

static void registrarColaborador(CentroDistribucion* centro) {
	cout << "--- Registrar colaborador ---" << endl;
	string id = Utilidades::leerIdCuatroDigitos("Identificacion (4 digitos): ");
	if (centro->getColaboradores()->buscar(id) != 0) {
		cout << "Error: ya existe un colaborador con esa identificacion en este centro. Registro cancelado." << endl;
		return;
	}
	string nombre = Utilidades::leerNombre("Nombre completo (solo letras y espacios): ");
	string puesto = Utilidades::leerTexto("Puesto: ");
	Fecha ingreso = Fecha::leerFecha("Fecha de ingreso:");
	centro->getColaboradores()->insertar(new Colaborador(id, nombre, puesto, ingreso));
	cout << "Colaborador registrado." << endl;
}

static void buscarColaborador(CentroDistribucion* centro) {
	cout << "--- Buscar colaborador ---" << endl;
	string id = Utilidades::leerTexto("Identificacion: ");
	Colaborador* c = centro->getColaboradores()->buscar(id);
	if (c == 0) {
		cout << "No existe un colaborador con esa identificacion en este centro." << endl;
		return;
	}
	c->mostrar();
}

static void mostrarColaboradores(CentroDistribucion* centro) {
	cout << "--- Colaboradores del centro ---" << endl;
	ListaColaboradores* lista = centro->getColaboradores();
	if (lista->getCantidad() == 0) {
		cout << "No hay colaboradores registrados en este centro." << endl;
		return;
	}
	for (int i = 0; i < lista->getCantidad(); i++) {
		cout << "---------------------------" << endl;
		lista->obtener(i)->mostrar();
	}
	cout << "---------------------------" << endl;
}

static void eliminarColaborador(CentroDistribucion* centro) {
	cout << "--- Eliminar colaborador ---" << endl;
	string id = Utilidades::leerTexto("Identificacion: ");
	Colaborador* c = centro->getColaboradores()->buscar(id);
	if (c == 0) {
		cout << "No existe un colaborador con esa identificacion en este centro." << endl;
		return;
	}
	if (Relaciones::colaboradorTieneDependencias(centro, c)) {
		cout << "No se puede eliminar: el colaborador figura como responsable en solicitudes, "
			<< "despachos o bitacoras." << endl;
		return;
	}
	cout << "Eliminar al colaborador " << c->getNombreCompleto() << "? 1. Si  2. No" << endl;
	if (Utilidades::leerOpcion(1, 2) != 1) {
		cout << "Eliminacion cancelada." << endl;
		return;
	}
	centro->getColaboradores()->eliminar(id);
	cout << "Colaborador eliminado." << endl;
}

void MenuColaboradores::ejecutar(CentroDistribucion* centro) {
	if (centro == 0) {
		return;
	}
	int op;
	do {
		system("cls");
		cout << endl << "===== COLABORADORES (Centro: " << centro->getNombre() << ") =====" << endl;
		cout << "1. Registrar colaborador" << endl;
		cout << "2. Buscar colaborador por identificacion" << endl;
		cout << "3. Mostrar colaboradores del centro" << endl;
		cout << "4. Eliminar colaborador" << endl;
		cout << "0. Volver" << endl;
		op = Utilidades::leerOpcion(0, 4);
		switch (op) {
		case 1: registrarColaborador(centro); break;
		case 2: buscarColaborador(centro); break;
		case 3: mostrarColaboradores(centro); break;
		case 4: eliminarColaborador(centro); break;
		default: break;
		}
		if (op != 0) {
			system("pause");
		}
	} while (op != 0);
}
