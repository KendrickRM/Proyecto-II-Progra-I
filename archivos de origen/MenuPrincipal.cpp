#include "MenuPrincipal.h"
#include "MenuBodegas.h"
#include "MenuPaquetes.h"
#include "MenuClientes.h"
#include "MenuColaboradores.h"
#include "MenuSolicitudes.h"
#include "MenuDespachos.h"
#include "MenuReportes.h"
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
    string codigo = Utilidades::leerCodigoCentro("Codigo del centro: ");
    CentroDistribucion* centro = sistema->buscarCentro(codigo);
    if (centro == 0) cout << "No existe un centro con ese codigo." << endl;
    return centro;
}

void MenuPrincipal::mostrarMenuPrincipal() {
    cout << endl << "===== SISTEMA DE DISTRIBUCION =====" << endl;
    cout << "1. Centros de distribucion" << endl;
    cout << "2. Clientes" << endl;
    cout << "3. Colaboradores" << endl;
    cout << "4. Bodegas" << endl;
    cout << "5. Paquetes" << endl;
    cout << "6. Solicitudes de envio" << endl;
    cout << "7. Despachos" << endl;
    cout << "8. Reportes" << endl;
    cout << "0. Salir" << endl;
}

void MenuPrincipal::registrarCentro() {
    cout << "--- Registrar centro ---" << endl;
    string codigo = Utilidades::leerCodigoCentro("Codigo del centro: ");
    if (sistema->codigoCentroExiste(codigo)) {
        cout << "Error: ya existe un centro con ese codigo. Registro cancelado." << endl;
        return;
    }
    string nombre = Utilidades::leerTexto("Nombre: ");
    string provincia = Utilidades::leerTexto("Provincia: ");
    string direccion = Utilidades::leerTexto("Direccion descriptiva: ");
    string telefono = Utilidades::leerTelefono("Telefono (exactamente 8 digitos): ");
    sistema->registrarCentro(new CentroDistribucion(codigo, nombre, provincia, direccion, telefono));
    cout << "Centro registrado." << endl;
}

void MenuPrincipal::buscarCentro() {
    cout << "--- Buscar centro ---" << endl;
    string codigo = Utilidades::leerCodigoCentro("Codigo del centro: ");
    CentroDistribucion* centro = sistema->buscarCentro(codigo);
    if (centro == 0) {
        cout << "No existe un centro con ese codigo." << endl;
        return;
    }
    centro->mostrar();
}

void MenuPrincipal::eliminarCentro() {
    cout << "--- Eliminar centro ---" << endl;
    string codigo = Utilidades::leerCodigoCentro("Codigo del centro: ");
    CentroDistribucion* centro = sistema->buscarCentro(codigo);
    if (centro == 0) {
        cout << "No existe un centro con ese codigo." << endl;
        return;
    }
    if (!centro->estaVacio()) {
        cout << "No se puede eliminar: el centro tiene clientes, colaboradores, bodegas, "
            << "paquetes, solicitudes o despachos asociados." << endl;
        return;
    }
    cout << "Eliminar el centro " << centro->getNombre() << "? 1. Si  2. No" << endl;
    if (Utilidades::leerOpcion(1, 2) != 1) {
        cout << "Eliminacion cancelada." << endl;
        return;
    }
    sistema->eliminarCentro(codigo);
    cout << "Centro eliminado." << endl;
}

void MenuPrincipal::menuCentros() {
    int op;
    do {
        system("cls");
        cout << endl << "===== CENTROS DE DISTRIBUCION =====" << endl;
        cout << "1. Registrar centro" << endl;
        cout << "2. Buscar centro por codigo" << endl;
        cout << "3. Mostrar centros" << endl;
        cout << "4. Eliminar centro" << endl;
        cout << "0. Volver" << endl;
        op = Utilidades::leerOpcion(0, 4);
        switch (op) {
        case 1: registrarCentro(); break;
        case 2: buscarCentro(); break;
        case 3: sistema->mostrarCentros(); break;
        case 4: eliminarCentro(); break;
        default: break;
        }
        if (op != 0) {
            system("pause");
        }
    } while (op != 0);
}

void MenuPrincipal::menuClientes() {
    CentroDistribucion* centro = seleccionarCentro();
    if (centro != 0) MenuClientes::ejecutar(centro); else system("pause");
}

void MenuPrincipal::menuColaboradores() {
    CentroDistribucion* centro = seleccionarCentro();
    if (centro != 0) MenuColaboradores::ejecutar(centro); else system("pause");
}

void MenuPrincipal::menuBodegas() {
    CentroDistribucion* centro = seleccionarCentro();
    if (centro != 0) MenuBodegas::ejecutar(centro); else system("pause");
}

void MenuPrincipal::menuPaquetes() {
    CentroDistribucion* centro = seleccionarCentro();
    if (centro != 0) MenuPaquetes::ejecutar(sistema, centro); else system("pause");
}

void MenuPrincipal::menuSolicitudes() {
    CentroDistribucion* centro = seleccionarCentro();
    if (centro != 0) MenuSolicitudes::ejecutar(sistema, centro); else system("pause");
}

void MenuPrincipal::menuDespachos() {
    CentroDistribucion* centro = seleccionarCentro();
    if (centro != 0) MenuDespachos::ejecutar(sistema, centro); else system("pause");
}

void MenuPrincipal::menuReportes() {
    MenuReportes::ejecutar(sistema);
}

void MenuPrincipal::ejecutar() {
    if (sistema == 0) return;
    int opcion;

    //Pantalla de bienvenida
    system("cls");
    cout << R"(   ___                                                _   /_/           _____
  / _ \_ __ ___   __ _ _ __ __ _ _ __ ___   __ _  ___(_) ___  _ __      \_   \
 / /_)/ '__/ _ \ / _` | '__/ _` | '_ ` _ \ / _` |/ __| |/ _ \| '_ \      / /\/
/ ___/| | | (_) | (_| | | | (_| | | | | | | (_| | (__| | (_) | | | |  /\/ /_
\/    |_|  \___/ \__, |_|  \__,_|_| |_| |_|\__,_|\___|_|\___/|_| |_|  \____/
                 |___/
 _____  _                 ___                _
/__   \(_)  ___   ___    / _ \  __ _    ___ | | __ ___
  / /\/| | / __| / _ \  / /_)/ / _` |  / __|| |/ // __|
 / /   | || (__ | (_) |/ ___/ | (_| | | (__ |   < \__ \
 \/    |_| \___| \___/ \/      \__,_|  \___||_|\_\|___/
  _____       _                             _
  \_   \_ __ | |_ ___  __ _ _ __ __ _ _ __ | |_ ___  ___   _
   / /\/ '_ \| __/ _ \/ _` | '__/ _` | '_ \| __/ _ \/ __| (_)
/\/ /_ | | | | ||  __/ (_| | | | (_| | | | | ||  __/\__ \  _
\____/ |_| |_|\__\___|\__, |_|  \__,_|_| |_|\__\___||___/ (_)
                      |___/                                                                      )";
    cout << R"(                        _  __            _     _   ___ _                      _     ___         _           __  __          _   __
| |/ /___ _ _  __| |_ _(_) | _ |_)____ __  __ _ _ _ __| |__ | _ \___  __| |_  __ _  |  \/  |__ _ _ _| |_/_/_ _  ___ ___
| ' </ -_) ' \/ _` | '_| | | _ \ (_-< '  \/ _` | '_/ _| / / |   / _ \/ _| ' \/ _` | | |\/| / _` | '_|  _| | ' \/ -_)_ /
|_|\_\___|_||_\__,_|_| |_| |___/_/__/_|_|_\__,_|_| \__|_\_\ |_|_\___/\__|_||_\__,_| |_|  |_\__,_|_|  \__|_|_||_\___/__|

  _ | |___ ___ ___   _ | |_  _| (_)_/_/ _ _    / __|/_/ _ _ __| |___| |__  __ _  | \| |__ ___ ____ _ _ _ _ _ ___
 | || / _ (_-</ -_) | || | || | | / _` | ' \  | (__/ _ \ '_/ _` / _ \ '_ \/ _` | | .` / _` \ V / _` | '_| '_/ _ \
  \__/\___/__/\___|  \__/ \_,_|_|_\__,_|_||_|  \___\___/_| \__,_\___/_.__/\__,_| |_|\_\__,_|\_/\__,_|_|  |_|\___/
 __   __         _ _             __  __             _               ___                 __    _
 \ \ / /_ _ _ _ (_) |_ _____ _  |  \/  |___ _ _  __| |___ _____ _  | _ ) ___ _ _ _ __ _/_/ __| |___ ___
  \ V / _` | ' \| |  _|_ / _` | | |\/| / -_) ' \/ _` / _ \_ / _` | | _ \/ -_) '_| '  \ || / _` / -_)_ /
   |_|\__,_|_||_|_|\__/__\__,_| |_|  |_\___|_||_\__,_\___/__\__,_| |___/\___|_| |_|_|_\_,_\__,_\___/__|
)" << endl;

    system("pause");
    system("cls");

    do {
        system("cls");
        mostrarMenuPrincipal();
        opcion = Utilidades::leerOpcion(0, 8);
        switch (opcion) {
        case 1: menuCentros(); break;
        case 2: menuClientes(); break;
        case 3: menuColaboradores(); break;
        case 4: menuBodegas(); break;
        case 5: menuPaquetes(); break;
        case 6: menuSolicitudes(); break;
        case 7: menuDespachos(); break;
        case 8: menuReportes(); break;
        default: break;
        }
    } while (opcion != 0);
}
