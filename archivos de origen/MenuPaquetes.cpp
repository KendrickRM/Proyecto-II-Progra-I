#include "MenuPaquetes.h"
#include "Utilidades.h"
#include "Paquete.h"
#include "Relaciones.h"
#include "Tarifa.h"
#include "Bodega.h"
#include "Cliente.h"
#include "Colaborador.h"
#include "Fecha.h"
#include <iostream>
#include <string>
using namespace std;



static int leerEnRango(const string& msg, int min, int max) {
    while (true) {
        int n = Utilidades::leerEntero(msg);
        if (n >= min && n <= max) {
            return n;
        }
        cout << "Error: el valor debe estar entre " << min << " y " << max << "." << endl;
    }
}


static Paquete* pedirPaquete(Sistema* sistema, CentroDistribucion* centro) {
    string codigo = Utilidades::leerCodigoPaquete("Codigo del paquete: ");
    Paquete* p = centro->getPaquetes()->buscar(codigo);
    if (p == 0) {
        if (sistema->codigoPaqueteExiste(codigo)) {
            cout << "Ese paquete existe, pero pertenece a otro centro." << endl;
        }
        else {
            cout << "No existe un paquete con ese codigo." << endl;
        }
    }
    return p;
}


static Colaborador* pedirColaborador(CentroDistribucion* centro) {
    string id = Utilidades::leerTexto("Identificacion del colaborador responsable: ");
    Colaborador* c = centro->getColaboradores()->buscar(id);
    if (c == 0) {
        cout << "No existe un colaborador con esa identificacion en este centro." << endl;
    }
    return c;
}


static Bodega* mejorBodega(CentroDistribucion* centro, int categoria) {
    Bodega* mejor = 0;
    ListaBodegas* lista = centro->getBodegas();
    for (int i = 0; i < lista->getCantidad(); i++) {
        Bodega* b = lista->obtener(i);
        if (b->esCompatible(categoria) && b->celdasLibres() > 0) {
            if (mejor == 0 || b->porcentajeDisponible() > mejor->porcentajeDisponible()) {
                mejor = b;
            }
        }
    }
    return mejor;
}

static void mostrarCompatibles(CentroDistribucion* centro, int categoria) {
    ListaBodegas* lista = centro->getBodegas();
    for (int i = 0; i < lista->getCantidad(); i++) {
        Bodega* b = lista->obtener(i);
        if (b->esCompatible(categoria) && b->celdasLibres() > 0) {
            cout << "  " << b->getCodigo() << " - " << b->getNombre()
                << " | celdas libres: " << b->celdasLibres() << "/" << b->totalCeldas()
                << " | ocupacion: " << b->getOcupacionTexto() << endl;
        }
    }
}


static void elegirCeldaManual(CentroDistribucion* centro, int categoria, Bodega*& bodega, Celda*& celda) {
    while (true) {
        string codigo = Utilidades::leerCodigoBodega("Codigo de la bodega elegida: ");
        Bodega* b = centro->getBodegas()->buscar(codigo);
        if (b == 0 || !b->esCompatible(categoria) || b->celdasLibres() == 0) {
            cout << "Error: elija una de las bodegas compatibles con espacio libre de la lista." << endl;
            continue;
        }
        b->dibujar();
        while (true) {
            int fila = leerEnRango("Fila (0-" + to_string(b->getFilas() - 1) + "): ", 0, b->getFilas() - 1);
            int col = leerEnRango("Columna (0-" + to_string(b->getColumnas() - 1) + "): ", 0, b->getColumnas() - 1);
            Celda* c = b->getCelda(fila, col);
            if (c->estaLibre()) {
                bodega = b;
                celda = c;
                return;
            }
            cout << "Error: esa celda esta ocupada. Elija una celda libre." << endl;
        }
    }
}

///////////////////////////////Opciones del menu////////////////////////////////

static void registrarPaquete(Sistema* sistema, CentroDistribucion* centro) {
    cout << "--- Registrar paquete ---" << endl;
    string codigo = Utilidades::leerCodigoPaquete("Codigo del paquete: ");
    if (sistema->codigoPaqueteExiste(codigo)) {
        cout << "Error: ya existe un paquete con ese codigo en el sistema. Registro cancelado." << endl;
        return;
    }
    string descripcion = Utilidades::leerTexto("Descripcion: ");

    double peso;
    while (true) {
        peso = Utilidades::leerDecimal("Peso en kg (mayor que 0 y maximo " + to_string((int)Paquete::pesoMaximo()) + "): ");
        if (peso > 0 && peso <= Paquete::pesoMaximo()) {
            break;
        }
        cout << "Error: el peso debe ser mayor que 0 y como maximo " << Paquete::pesoMaximo() << " kg." << endl;
    }

    cout << "Categorias: 1 General, 2 Fragil, 3 Tecnologia, 4 Documentos" << endl;
    int categoria = leerEnRango("Categoria (1-4): ", 1, 4);

    string idCliente = Utilidades::leerTexto("Identificacion del cliente propietario: ");
    Cliente* cliente = centro->getClientes()->buscar(idCliente);
    if (cliente == 0) {
        cout << "Error: no existe un cliente con esa identificacion en este centro. Registro cancelado." << endl;
        return;
    }

    centro->getPaquetes()->insertar(new Paquete(codigo, descripcion, peso, categoria, cliente, centro->getCodigo()));
    cout << "Paquete registrado. Estado inicial: Recibido." << endl;
}

static void buscarPaquete(Sistema* sistema) {
    cout << "--- Buscar paquete ---" << endl;
    string codigo = Utilidades::leerCodigoPaquete("Codigo del paquete: ");
    Paquete* p = sistema->buscarPaquete(codigo);  
    if (p == 0) {
        cout << "No existe un paquete con ese codigo." << endl;
        return;
    }
    p->mostrar();
}

static void mostrarPaquetes(CentroDistribucion* centro) {
    cout << "--- Paquetes del centro ---" << endl;
    ListaPaquetes* lista = centro->getPaquetes();
    if (lista->getCantidad() == 0) {
        cout << "No hay paquetes registrados en este centro." << endl;
        return;
    }
    int n = lista->getCantidad();
    string encabezados[7] = { "Codigo", "Descripcion", "Peso", "Categoria", "Cliente", "Estado", "Ubicacion" };
    string* celdas = new string[n * 7];
    for (int i = 0; i < n; i++) {
        Paquete* p = lista->obtener(i);
        string descripcion = p->getDescripcion();
        if (descripcion.size() > 24) {
            descripcion = descripcion.substr(0, 21) + "...";
        }
        celdas[i * 7] = p->getCodigo();
        celdas[i * 7 + 1] = descripcion;
        celdas[i * 7 + 2] = Tarifa::formatearDecimal(p->getPeso()) + " kg";
        celdas[i * 7 + 3] = p->getNombreCategoria();
        celdas[i * 7 + 4] = p->getPropietario()->getIdentificacion();
        celdas[i * 7 + 5] = p->getNombreEstado();
        if (p->getBodega() != 0 && p->getCelda() != 0) {
            celdas[i * 7 + 6] = p->getCelda()->getIdentificador();
        }
        else {
            celdas[i * 7 + 6] = "Sin ubicacion";
        }
    }
    Utilidades::imprimirTabla(7, n, encabezados, celdas);
    delete[] celdas;
}

static void eliminarPaquete(Sistema* sistema, CentroDistribucion* centro) {
    cout << "--- Eliminar paquete ---" << endl;
    Paquete* p = pedirPaquete(sistema, centro);
    if (p == 0) {
        return;
    }
    
    if (p->getEstado() != Paquete::RECIBIDO || p->getCelda() != 0) {
        cout << "No se puede eliminar: el paquete solo se elimina si esta en estado Recibido y sin celda. "
            << "Estado actual: " << p->getNombreEstado() << "." << endl;
        return;
    }
    if (Relaciones::paqueteTieneSolicitudes(centro, p) || Relaciones::despachoDePaquete(centro, p) != 0) {
        cout << "No se puede eliminar: el paquete tiene solicitudes o despachos asociados." << endl;
        return;
    }
    cout << "Eliminar el paquete " << p->getCodigo() << "? 1. Si  2. No" << endl;
    if (leerEnRango("Opcion: ", 1, 2) != 1) {
        cout << "Eliminacion cancelada." << endl;
        return;
    }
    string codigo = p->getCodigo();   
    centro->getPaquetes()->eliminar(codigo);
    cout << "Paquete eliminado." << endl;
}

static void almacenarPaquete(Sistema* sistema, CentroDistribucion* centro) {
    cout << "--- Almacenar paquete ---" << endl;
    Paquete* p = pedirPaquete(sistema, centro);
    if (p == 0) {
        return;
    }
    if (!p->necesitaAlmacenarse()) {
        cout << "No se puede almacenar: solo se almacena un paquete en estado Recibido "
            << "(o en Incidencia ocurrida estando Recibido). Estado actual: "
            << p->getNombreEstado() << "." << endl;
        return;
    }

    Bodega* mejor = mejorBodega(centro, p->getCategoria());
    if (mejor == 0) {
        cout << "No hay espacio disponible en bodegas compatibles (" << p->getNombreCategoria()
            << "). No se realizo ningun cambio." << endl;
        return;
    }

    cout << "Bodegas compatibles con espacio libre:" << endl;
    mostrarCompatibles(centro, p->getCategoria());

    Celda* sugerida = mejor->primeraCeldaLibre();
    cout << "Recomendacion: bodega " << mejor->getCodigo() << " (mayor espacio disponible, ocupacion "
        << mejor->getOcupacionTexto() << "), celda " << sugerida->getIdentificador() << "." << endl;
    cout << "1. Aceptar la recomendacion  2. Elegir otra celda" << endl;

    Bodega* bodega = 0;
    Celda* celda = 0;
    if (leerEnRango("Opcion: ", 1, 2) == 1) {
        bodega = mejor;
        celda = sugerida;
    }
    else {
        elegirCeldaManual(centro, p->getCategoria(), bodega, celda);
    }

    Colaborador* responsable = pedirColaborador(centro);
    if (responsable == 0) {
        cout << "Operacion cancelada. No se realizo ningun cambio." << endl;
        return;
    }
    Fecha fecha = Fecha::leerFecha("Fecha del cambio:");

    if (p->almacenar(bodega, celda, responsable, fecha)) {
        cout << "Paquete almacenado en la bodega " << bodega->getCodigo()
            << ", celda " << celda->getIdentificador() << "." << endl;
    }
    else {
        cout << "No se pudo almacenar el paquete. No se realizo ningun cambio." << endl;
    }
}

static void reubicarPaquete(Sistema* sistema, CentroDistribucion* centro) {
    cout << "--- Reubicar paquete ---" << endl;
    Paquete* p = pedirPaquete(sistema, centro);
    if (p == 0) {
        return;
    }
    if (p->getEstado() != Paquete::ALMACENADO) {
        cout << "No se puede reubicar: solo se reubican paquetes Almacenados. Estado actual: "
            << p->getNombreEstado() << "." << endl;
        return;
    }
    string anterior = p->getCelda()->getIdentificador();
    cout << "Ubicacion actual: bodega " << p->getBodega()->getCodigo() << ", celda " << anterior << "." << endl;

    if (mejorBodega(centro, p->getCategoria()) == 0) {
        cout << "No hay celdas libres en bodegas compatibles. No se realizo ningun cambio." << endl;
        return;
    }
    cout << "Bodegas compatibles con espacio libre:" << endl;
    mostrarCompatibles(centro, p->getCategoria());

    Bodega* bodega = 0;
    Celda* celda = 0;
    elegirCeldaManual(centro, p->getCategoria(), bodega, celda);

    
    if (p->reubicar(bodega, celda)) {
        cout << "Paquete reubicado de la celda " << anterior << " a la celda "
            << celda->getIdentificador() << " (bodega " << bodega->getCodigo() << ")." << endl;
    }
    else {
        cout << "No se pudo reubicar. No se realizo ningun cambio." << endl;
    }
}

static void registrarIncidencia(Sistema* sistema, CentroDistribucion* centro) {
    cout << "--- Registrar incidencia ---" << endl;
    Paquete* p = pedirPaquete(sistema, centro);
    if (p == 0) {
        return;
    }
    if (!p->puedeCambiarA(Paquete::INCIDENCIA)) {
        if (p->getEstado() == Paquete::INCIDENCIA) {
            cout << "El paquete ya esta en Incidencia." << endl;
        }
        else {
            cout << "No se puede registrar una incidencia: el paquete esta en estado "
                << p->getNombreEstado() << "." << endl;
        }
        return;
    }
    Colaborador* responsable = pedirColaborador(centro);
    if (responsable == 0) {
        cout << "Operacion cancelada. No se realizo ningun cambio." << endl;
        return;
    }
    Fecha fecha = Fecha::leerFecha("Fecha de la incidencia:");
    if (p->registrarIncidencia(responsable, fecha)) {
        cout << "Incidencia registrada. Estado actual: " << p->getNombreEstado() << "." << endl;
    }
    else {
        cout << "No se pudo registrar la incidencia." << endl;
    }
}

static void resolverIncidencia(Sistema* sistema, CentroDistribucion* centro) {
    cout << "--- Resolver incidencia ---" << endl;
    Paquete* p = pedirPaquete(sistema, centro);
    if (p == 0) {
        return;
    }
    if (p->getEstado() != Paquete::INCIDENCIA) {
        cout << "El paquete no esta en Incidencia. Estado actual: " << p->getNombreEstado() << "." << endl;
        return;
    }
    if (p->necesitaAlmacenarse()) {
        cout << "La incidencia ocurrio estando Recibido: use la opcion Almacenar paquete." << endl;
        return;
    }
    //El despacho debe estar En proceso
    if (p->getEstadoPrevioIncidencia() == Paquete::EN_TRANSITO) {
        Despacho* d = Relaciones::despachoDePaquete(centro, p);
        if (d == 0 || d->getEstado() != Despacho::EN_PROCESO) {
            cout << "No se puede resolver: el despacho del paquete debe estar En proceso." << endl;
            return;
        }
    }
    Colaborador* responsable = pedirColaborador(centro);
    if (responsable == 0) {
        cout << "Operacion cancelada. No se realizo ningun cambio." << endl;
        return;
    }
    Fecha fecha = Fecha::leerFecha("Fecha de la resolucion:");
    if (p->resolverIncidencia(responsable, fecha)) {
        cout << "Incidencia resuelta. Estado actual: " << p->getNombreEstado() << "." << endl;
    }
    else {
        cout << "No se pudo resolver la incidencia." << endl;
    }
}

static void verBitacora(Sistema* sistema, CentroDistribucion* centro) {
    cout << "--- Bitacora de un paquete ---" << endl;
    Paquete* p = pedirPaquete(sistema, centro);
    if (p != 0) {
        p->mostrarBitacora();
    }
}

void MenuPaquetes::ejecutar(Sistema* sistema, CentroDistribucion* centro) {
    if (sistema == 0 || centro == 0) {
        return;
    }
    int op;
    do {
        system("cls");
        cout << endl << "===== PAQUETES (Centro: " << centro->getNombre() << ") =====" << endl;
        cout << "1. Registrar paquete" << endl;
        cout << "2. Buscar paquete por codigo" << endl;
        cout << "3. Mostrar paquetes del centro" << endl;
        cout << "4. Eliminar paquete" << endl;
        cout << "5. Almacenar paquete" << endl;
        cout << "6. Reubicar paquete" << endl;
        cout << "7. Registrar incidencia" << endl;
        cout << "8. Resolver incidencia" << endl;
        cout << "9. Ver bitacora de un paquete" << endl;
        cout << "0. Volver" << endl;
        op = Utilidades::leerOpcion(0, 9);
        switch (op) {
        case 1: registrarPaquete(sistema, centro); break;
        case 2: buscarPaquete(sistema); break;
        case 3: mostrarPaquetes(centro); break;
        case 4: eliminarPaquete(sistema, centro); break;
        case 5: almacenarPaquete(sistema, centro); break;
        case 6: reubicarPaquete(sistema, centro); break;
        case 7: registrarIncidencia(sistema, centro); break;
        case 8: resolverIncidencia(sistema, centro); break;
        case 9: verBitacora(sistema, centro); break;
        default: break;
        }
        if (op != 0) {
            system("pause");
        }
    } while (op != 0);
}

