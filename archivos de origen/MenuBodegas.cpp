#include "MenuBodegas.h"
#include "Utilidades.h"
#include "Bodega.h"
#include "Paquete.h"
#include <iostream>
#include <string>
using namespace std;


static const int MAX_DIMENSION = Bodega::dimensionMaxima();

static int leerEnRango(const string& msg, int min, int max) {
    while (true) {
        int n = Utilidades::leerEntero(msg);
        if (n >= min && n <= max) {
            return n;
        }
        cout << "Error: el valor debe estar entre " << min << " y " << max << "." << endl;
    }
}


static Bodega* pedirBodega(CentroDistribucion* centro) {
    string codigo = Utilidades::leerCodigoBodega("Codigo de la bodega: ");
    Bodega* b = centro->getBodegas()->buscar(codigo);
    if (b == 0) {
        cout << "No existe una bodega con ese codigo en este centro." << endl;
    }
    return b;
}

static void registrarBodega(CentroDistribucion* centro) {
    cout << "--- Registrar bodega ---" << endl;
    string codigo = Utilidades::leerCodigoBodega("Codigo de la bodega (ejemplo: A): ");
    if (centro->getBodegas()->buscar(codigo) != 0) {
        cout << "Error: ya existe una bodega con ese codigo en este centro. Registro cancelado." << endl;
        return;
    }
    string nombre = Utilidades::leerTexto("Nombre: ");
    cout << "Tipos: 1 General, 2 Fragil, 3 Tecnologia, 4 Documentos" << endl;
    int tipo = leerEnRango("Tipo (1-4): ", 1, 4);
    int filas = leerEnRango("Filas (1-" + to_string(MAX_DIMENSION) + "): ", 1, MAX_DIMENSION);
    int columnas = leerEnRango("Columnas (1-" + to_string(MAX_DIMENSION) + "): ", 1, MAX_DIMENSION);

    centro->getBodegas()->insertar(new Bodega(codigo, nombre, tipo, filas, columnas));
    cout << "Bodega registrada correctamente (" << filas * columnas << " celdas)." << endl;
}

static void buscarBodega(CentroDistribucion* centro) {
    cout << "--- Buscar bodega ---" << endl;
    Bodega* b = pedirBodega(centro);
    if (b != 0) {
        b->mostrar();
    }
}

static void mostrarBodegas(CentroDistribucion* centro) {
    cout << "--- Bodegas del centro ---" << endl;
    ListaBodegas* lista = centro->getBodegas();
    if (lista->getCantidad() == 0) {
        cout << "No hay bodegas registradas en este centro." << endl;
        return;
    }
    for (int i = 0; i < lista->getCantidad(); i++) {
        lista->obtener(i)->mostrar();
    }
}

static void consultarMatriz(CentroDistribucion* centro) {
    cout << "--- Consultar matriz ---" << endl;
    Bodega* b = pedirBodega(centro);
    if (b == 0) {
        return;
    }
    b->dibujar();
    cout << "Desea consultar una posicion? 1. Si  2. No" << endl;
    if (leerEnRango("Opcion: ", 1, 2) != 1) {
        return;
    }
    int fila = leerEnRango("Fila (0-" + to_string(b->getFilas() - 1) + "): ", 0, b->getFilas() - 1);
    int col = leerEnRango("Columna (0-" + to_string(b->getColumnas() - 1) + "): ", 0, b->getColumnas() - 1);
    Celda* c = b->getCelda(fila, col);
    cout << "Celda " << c->getIdentificador() << ": ";
    if (c->estaLibre()) {
        cout << "libre" << endl;
    }
    else {
        Paquete* p = c->getPaquete();
        cout << "ocupada por el paquete " << p->getCodigo()
            << " (" << p->getDescripcion() << ")" << endl;
    }
}

static void eliminarBodega(CentroDistribucion* centro) {
    cout << "--- Eliminar bodega ---" << endl;
    Bodega* b = pedirBodega(centro);
    if (b == 0) {
        return;
    }
    if (!b->todasLibres()) {
        cout << "No se puede eliminar: la bodega tiene paquetes almacenados ("
            << b->celdasOcupadas() << " celdas ocupadas)." << endl;
        return;
    }
    cout << "Eliminar la bodega " << b->getCodigo() << "? 1. Si  2. No" << endl;
    if (leerEnRango("Opcion: ", 1, 2) != 1) {
        cout << "Eliminacion cancelada." << endl;
        return;
    }
    string codigo = b->getCodigo();   
    centro->getBodegas()->eliminar(codigo);
    cout << "Bodega eliminada." << endl;
}

void MenuBodegas::ejecutar(CentroDistribucion* centro) {
    if (centro == 0) {
        return;
    }
    int op;
    do {
        system("cls");
        cout << endl << "===== BODEGAS (Centro: " << centro->getNombre() << ") =====" << endl;
        cout << "1. Registrar bodega" << endl;
        cout << "2. Buscar bodega por codigo" << endl;
        cout << "3. Mostrar bodegas" << endl;
        cout << "4. Consultar matriz de una bodega" << endl;
        cout << "5. Eliminar bodega" << endl;
        cout << "0. Volver" << endl;
        op = Utilidades::leerOpcion(0, 5);
        switch (op) {
        case 1: registrarBodega(centro); break;
        case 2: buscarBodega(centro); break;
        case 3: mostrarBodegas(centro); break;
        case 4: consultarMatriz(centro); break;
        case 5: eliminarBodega(centro); break;
        default: break;
        }
        if (op != 0) {
            system("pause");
        }
    } while (op != 0);
}