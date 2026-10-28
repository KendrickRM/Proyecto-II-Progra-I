#include "MenuPrincipal.h"
#include "MenuBodegas.h"
#include "MenuPaquetes.h"
#include "Utilidades.h"
#include <iostream>

using namespace std;

MenuPrincipal::MenuPrincipal(Sistema* sistema) : sistema(sistema) {}

CentroDistribucion* MenuPrincipal::seleccionarCentro() {
    if (sistema == 0 || sistema->getCentros()->getCantidad() == 0) {
        cout << "No hay centros registrados." << endl;
        return 0;
    }
    sistema->mostrarCentros();
    string codigo = Utilidades::leerTexto("Codigo del centro: ");
    CentroDistribucion* centro = sistema->buscarCentro(codigo);
    if (centro == 0) cout << "No existe un centro con ese codigo." << endl;
    return centro;
}

void MenuPrincipal::mostrarMenuPrincipal() {
    cout << endl << "===== SISTEMA DE DISTRIBUCION =====" << endl;
    cout << "1. Mostrar centros" << endl << "2. Gestionar bodegas" << endl << "3. Gestionar paquetes" << endl << "0. Salir" << endl;
}

void MenuPrincipal::menuCentros() { sistema->mostrarCentros(); }

void MenuPrincipal::menuBodegas() {
    CentroDistribucion* centro = seleccionarCentro();
    if (centro != 0) MenuBodegas::ejecutar(centro);
}

void MenuPrincipal::menuPaquetes() {
    CentroDistribucion* centro = seleccionarCentro();
    if (centro != 0) MenuPaquetes::ejecutar(sistema, centro);
}

void MenuPrincipal::ejecutar() {
    if (sistema == 0) return;
    int opcion;
    do {
        mostrarMenuPrincipal();
        opcion = Utilidades::leerOpcion(0, 3);
        switch (opcion) {
        case 1: menuCentros(); break;
        case 2: menuBodegas(); break;
        case 3: menuPaquetes(); break;
        default: break;
        }
    } while (opcion != 0);
}


