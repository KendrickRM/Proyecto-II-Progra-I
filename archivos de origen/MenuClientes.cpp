#include "MenuClientes.h"
#include "Utilidades.h"
#include "Relaciones.h"
#include "ClientePersonaFisica.h"
#include "ClienteEmpresa.h"
#include <iostream>
#include <string>
using namespace std;

static void registrarCliente(CentroDistribucion* centro) {
	cout << "--- Registrar cliente ---" << endl;
	cout << "Tipo de cliente: 1. Persona fisica  2. Empresa" << endl;
	int tipo = Utilidades::leerOpcion(1, 2);

	string id = Utilidades::leerIdCuatroDigitos("Identificacion (4 digitos): ");
	if (centro->getClientes()->buscar(id) != 0) {
		cout << "Error: ya existe un cliente con esa identificacion en este centro. Registro cancelado." << endl;
		return;
	}
	string nombre = Utilidades::leerNombre("Nombre completo (solo letras y espacios): ");
	string telefono = Utilidades::leerTelefono("Telefono (exactamente 8 digitos): ");
	string correo = Utilidades::leerCorreo("Correo electronico (debe contener @): ");

	if (tipo == 1) {
		centro->getClientes()->insertar(new ClientePersonaFisica(id, nombre, telefono, correo));
	}
	else {
		string actividad = Utilidades::leerTexto("Actividad economica: ");
		double descuento;
		while (true) {
			descuento = Utilidades::leerDecimal("Porcentaje de descuento (0 a 100): ");
			if (descuento >= 0 && descuento <= 100) {
				break;
			}
			cout << "Error: el descuento debe estar entre 0 y 100." << endl;
		}
		centro->getClientes()->insertar(new ClienteEmpresa(id, nombre, telefono, correo, actividad, descuento));
	}
	cout << "Cliente registrado." << endl;
}

static void buscarCliente(CentroDistribucion* centro) {
	cout << "--- Buscar cliente ---" << endl;
	string id = Utilidades::leerTexto("Identificacion: ");
	Cliente* c = centro->getClientes()->buscar(id);
	if (c == 0) {
		cout << "No existe un cliente con esa identificacion en este centro." << endl;
		return;
	}
	c->mostrar();
}

static void mostrarClientes(CentroDistribucion* centro) {
	cout << "--- Clientes del centro ---" << endl;
	ListaClientes* lista = centro->getClientes();
	if (lista->getCantidad() == 0) {
		cout << "No hay clientes registrados en este centro." << endl;
		return;
	}
	for (int i = 0; i < lista->getCantidad(); i++) {
		cout << "---------------------------" << endl;
		lista->obtener(i)->mostrar();
	}
	cout << "---------------------------" << endl;
}

static void eliminarCliente(CentroDistribucion* centro) {
	cout << "--- Eliminar cliente ---" << endl;
	string id = Utilidades::leerTexto("Identificacion: ");
	Cliente* c = centro->getClientes()->buscar(id);
	if (c == 0) {
		cout << "No existe un cliente con esa identificacion en este centro." << endl;
		return;
	}
	if (Relaciones::clienteTieneDependencias(centro, c)) {
		cout << "No se puede eliminar: el cliente tiene paquetes, solicitudes o despachos asociados." << endl;
		return;
	}
	cout << "Eliminar al cliente " << c->getNombre() << "? 1. Si  2. No" << endl;
	if (Utilidades::leerOpcion(1, 2) != 1) {
		cout << "Eliminacion cancelada." << endl;
		return;
	}
	centro->getClientes()->eliminar(id);
	cout << "Cliente eliminado." << endl;
}

void MenuClientes::ejecutar(CentroDistribucion* centro) {
	if (centro == 0) {
		return;
	}
	int op;
	do {
		system("cls");
		cout << endl << "===== CLIENTES (Centro: " << centro->getNombre() << ") =====" << endl;
		cout << "1. Registrar cliente" << endl;
		cout << "2. Buscar cliente por identificacion" << endl;
		cout << "3. Mostrar clientes del centro" << endl;
		cout << "4. Eliminar cliente" << endl;
		cout << "0. Volver" << endl;
		op = Utilidades::leerOpcion(0, 4);
		switch (op) {
		case 1: registrarCliente(centro); break;
		case 2: buscarCliente(centro); break;
		case 3: mostrarClientes(centro); break;
		case 4: eliminarCliente(centro); break;
		default: break;
		}
		if (op != 0) {
			system("pause");
		}
	} while (op != 0);
}
