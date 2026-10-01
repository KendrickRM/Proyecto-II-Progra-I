#include "Sistema.h"
#include "MenuPrincipal.h"

int main() {
    Sistema sistema;
    sistema.cargarDatosQuemados();

    MenuPrincipal menu(&sistema);
    menu.ejecutar();

    return 0;
}