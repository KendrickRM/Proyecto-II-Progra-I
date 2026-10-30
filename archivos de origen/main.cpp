#include "Sistema.h"
#include "MenuPrincipal.h"
#include "Utilidades.h"

int main() {
    Sistema sistema;
    sistema.cargarDatosQuemados();

    MenuPrincipal menu(&sistema);
    try {
        menu.ejecutar();
    }
    catch (EntradaCerrada&) {
        // La entrada se cerro: se sale normalmente y los destructores liberan la memoria
    }

    return 0;
}