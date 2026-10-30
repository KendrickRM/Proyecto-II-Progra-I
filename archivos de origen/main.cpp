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
        //Entrada cerrada: se sale normalmente
    }

    return 0;
}