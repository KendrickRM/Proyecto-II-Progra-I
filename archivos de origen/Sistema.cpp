#include "Sistema.h"
#include "ClientePersonaFisica.h"
#include "ClienteEmpresa.h"
#include <iostream>
using namespace std;

Sistema::Sistema() {
    centros = new ListaCentros();
}

Sistema::~Sistema() {
    delete centros;
}

bool Sistema::registrarCentro(CentroDistribucion* c) {
    if (c == 0) {
        return false;
    }
    if (codigoCentroExiste(c->getCodigo())) {
        return false;
    }
    centros->insertar(c);
    return true;
}

CentroDistribucion* Sistema::buscarCentro(const string& codigo) {
    return centros->buscar(codigo);
}

bool Sistema::eliminarCentro(const string& codigo) {
    CentroDistribucion* c = centros->buscar(codigo);
    if (c == 0) {
        return false;
    }
    if (!c->estaVacio()) {
        return false;
    }
    return centros->eliminar(codigo);
}

void Sistema::mostrarCentros() {
    if (centros->getCantidad() == 0) {
        cout << "No hay centros registrados." << endl;
        return;
    }
    for (int i = 0; i < centros->getCantidad(); i++) {
        cout << "---------------------------" << endl;
        centros->obtener(i)->mostrar();
    }
    cout << "---------------------------" << endl;
}

ListaCentros* Sistema::getCentros() { return centros; }

bool Sistema::codigoCentroExiste(const string& codigo) {
    return centros->buscar(codigo) != 0;
}

bool Sistema::codigoPaqueteExiste(const string& codigo) {
    return buscarPaquete(codigo) != 0;
}

bool Sistema::codigoSolicitudExiste(const string& codigo) {
    return buscarSolicitud(codigo) != 0;
}

bool Sistema::codigoDespachoExiste(const string& codigo) {
    return buscarDespacho(codigo) != 0;
}

Paquete* Sistema::buscarPaquete(const string& codigo) {
    for (int i = 0; i < centros->getCantidad(); i++) {
        Paquete* p = centros->obtener(i)->getPaquetes()->buscar(codigo);
        if (p != 0) {
            return p;
        }
    }
    return 0;
}

SolicitudEnvio* Sistema::buscarSolicitud(const string& codigo) {
    for (int i = 0; i < centros->getCantidad(); i++) {
        SolicitudEnvio* s = centros->obtener(i)->getSolicitudes()->buscar(codigo);
        if (s != 0) {
            return s;
        }
    }
    return 0;
}

Despacho* Sistema::buscarDespacho(const string& codigo) {
    for (int i = 0; i < centros->getCantidad(); i++) {
        Despacho* d = centros->obtener(i)->getDespachos()->buscar(codigo);
        if (d != 0) {
            return d;
        }
    }
    return 0;
}

// ---------- Ayudas para los datos quemados (siguen las mismas reglas que los menus) ----------

static Colaborador* quemarColaborador(CentroDistribucion* c, const string& id, const string& nombre,
    const string& puesto, const Fecha& ingreso) {
    Colaborador* col = new Colaborador(id, nombre, puesto, ingreso);
    c->getColaboradores()->insertar(col);
    return col;
}

static Bodega* quemarBodega(CentroDistribucion* c, const string& codigo, const string& nombre,
    int tipo, int filas, int columnas) {
    Bodega* b = new Bodega(codigo, nombre, tipo, filas, columnas);
    c->getBodegas()->insertar(b);
    return b;
}

static Paquete* quemarPaquete(CentroDistribucion* c, const string& codigo, const string& descripcion,
    double peso, int categoria, const string& idCliente) {
    Paquete* p = new Paquete(codigo, descripcion, peso, categoria,
        c->getClientes()->buscar(idCliente), c->getCodigo());
    c->getPaquetes()->insertar(p);
    return p;
}

static void quemarAlmacenado(Paquete* p, Bodega* b, int fila, int columna, Colaborador* col, const Fecha& fecha) {
    p->almacenar(b, b->getCelda(fila, columna), col, fecha);
}

static SolicitudEnvio* quemarSolicitud(CentroDistribucion* c, const string& codigo, Paquete* p,
    Colaborador* col, const string& destino, const Fecha& fecha) {
    SolicitudEnvio* s = new SolicitudEnvio(codigo, p->getPropietario(), p, col, c->getCodigo(), destino, fecha);
    c->getSolicitudes()->insertar(s);
    return s;
}

static Despacho* quemarAprobacion(CentroDistribucion* c, SolicitudEnvio* s, const string& codigoDespacho,
    const Fecha& fecha) {
    s->getPaquete()->pasarATransito(s->getColaborador(), fecha);
    s->cambiarEstado(SolicitudEnvio::APROBADA);
    Despacho* d = new Despacho(codigoDespacho, s, s->getPaquete(), s->getCliente(), s->getColaborador(),
        c->getCodigo(), s->getDestino(), fecha);
    c->getDespachos()->insertar(d);
    return d;
}

static void quemarOperaciones(CentroDistribucion* c1, CentroDistribucion* c2, CentroDistribucion* c3) {
    // ----- Centro 1: todos los estados de solicitud y de despacho -----
    Colaborador* luis = quemarColaborador(c1, "1101", "Luis Mora Solano", "Operador", Fecha(15, 3, 2022));
    quemarColaborador(c1, "1102", "Sofia Rojas Vega", "Supervisora", Fecha(10, 8, 2021));
    Bodega* a1 = quemarBodega(c1, "A", "Bodega General", 1, 3, 4);
    Bodega* b1 = quemarBodega(c1, "B", "Bodega Fragil", 2, 2, 3);

    quemarPaquete(c1, "PK101", "Cajas de ropa", 2.5, 1, "1001");                     // Recibido
    Paquete* p102 = quemarPaquete(c1, "PK102", "Repuestos de maquinaria", 10, 1, "1002");
    quemarAlmacenado(p102, a1, 0, 0, luis, Fecha(2, 10, 2026));
    quemarSolicitud(c1, "001", p102, luis, "Cartago, Barrio El Molino", Fecha(3, 10, 2026));   // Pendiente

    Paquete* p103 = quemarPaquete(c1, "PK103", "Juego de copas de cristal", 4, 2, "1001");
    quemarAlmacenado(p103, b1, 0, 1, luis, Fecha(2, 10, 2026));
    SolicitudEnvio* s2 = quemarSolicitud(c1, "002", p103, luis, "Heredia, Barva centro", Fecha(3, 10, 2026));
    s2->cambiarEstado(SolicitudEnvio::RECHAZADA);

    Paquete* p104 = quemarPaquete(c1, "PK104", "Muebles desarmados", 6, 1, "1001");
    quemarAlmacenado(p104, a1, 0, 1, luis, Fecha(2, 10, 2026));
    SolicitudEnvio* s3 = quemarSolicitud(c1, "003", p104, luis, "Limon, Avenida 2", Fecha(4, 10, 2026));
    quemarAprobacion(c1, s3, "001", Fecha(8, 10, 2026, 9, 30));                          // En proceso

    Paquete* p105 = quemarPaquete(c1, "PK105", "Material de oficina", 1.2, 1, "1002");
    quemarAlmacenado(p105, a1, 1, 0, luis, Fecha(2, 10, 2026));
    SolicitudEnvio* s4 = quemarSolicitud(c1, "004", p105, luis, "Puntarenas, Paseo de los Turistas", Fecha(4, 10, 2026));
    Despacho* d2 = quemarAprobacion(c1, s4, "002", Fecha(9, 10, 2026, 14, 15));
    p105->marcarEntregado(luis, Fecha(12, 10, 2026));
    d2->finalizar();                                                                       // Finalizado

    // Incidencia estando Almacenado: conserva su celda
    Paquete* p106 = quemarPaquete(c1, "PK106", "Vajilla de porcelana", 3.5, 2, "1001");
    quemarAlmacenado(p106, b1, 0, 0, luis, Fecha(5, 10, 2026));
    p106->registrarIncidencia(luis, Fecha(7, 10, 2026));

    // Incidencia estando Recibido: queda sin ubicacion
    Paquete* p107 = quemarPaquete(c1, "PK107", "Llantas", 12, 1, "1002");
    p107->registrarIncidencia(luis, Fecha(8, 10, 2026));

    // ----- Centro 2 -----
    Colaborador* andrea = quemarColaborador(c2, "2101", "Andrea Solis Mena", "Operadora", Fecha(5, 1, 2023));
    Bodega* a2 = quemarBodega(c2, "A", "Bodega Tecnologia", 3, 2, 3);

    Paquete* p201 = quemarPaquete(c2, "PK201", "Laptop", 2, 3, "2001");
    quemarAlmacenado(p201, a2, 0, 0, andrea, Fecha(5, 10, 2026));
    SolicitudEnvio* s5 = quemarSolicitud(c2, "005", p201, andrea, "San Carlos, Ciudad Quesada", Fecha(6, 10, 2026));
    s5->cambiarEstado(SolicitudEnvio::ANULADA);

    Paquete* p202 = quemarPaquete(c2, "PK202", "Monitores", 1.5, 3, "2002");
    quemarAlmacenado(p202, a2, 0, 1, andrea, Fecha(5, 10, 2026));
    quemarSolicitud(c2, "006", p202, andrea, "Grecia, frente al parque", Fecha(7, 10, 2026));  // Pendiente, con descuento

    quemarPaquete(c2, "PK203", "Contratos firmados", 0.5, 4, "2001");                // Recibido

    // Incidencia en transito: el despacho sigue En proceso y el paquete queda sin celda
    Colaborador* marco = quemarColaborador(c2, "2102", "Marco Quesada Mora", "Despachador", Fecha(1, 3, 2024));
    Paquete* p204 = quemarPaquete(c2, "PK204", "Tablet y accesorios", 3.2, 3, "2002");
    quemarAlmacenado(p204, a2, 1, 0, marco, Fecha(8, 10, 2026));
    SolicitudEnvio* s7 = quemarSolicitud(c2, "007", p204, marco, "Naranjo, centro comercial", Fecha(9, 10, 2026));
    quemarAprobacion(c2, s7, "003", Fecha(10, 10, 2026, 8, 0));
    p204->registrarIncidencia(marco, Fecha(11, 10, 2026));

    // ----- Centro 3 -----
    quemarColaborador(c3, "3101", "Pedro Mena Soto", "Operador", Fecha(20, 6, 2022));
    Colaborador* pedro = c3->getColaboradores()->buscar("3101");
    Bodega* a3 = quemarBodega(c3, "A", "Bodega Documentos", 4, 2, 2);
    Paquete* p301 = quemarPaquete(c3, "PK301", "Escrituras", 0.8, 4, "3001");
    quemarAlmacenado(p301, a3, 0, 0, pedro, Fecha(6, 10, 2026));

    Colaborador* lucia = quemarColaborador(c3, "3102", "Lucia Araya Campos", "Supervisora", Fecha(3, 2, 2024));

    Paquete* p302 = quemarPaquete(c3, "PK302", "Planos del proyecto", 0.4, 4, "3002");
    quemarAlmacenado(p302, a3, 0, 1, pedro, Fecha(7, 10, 2026));
    quemarSolicitud(c3, "008", p302, pedro, "Paraiso, Calle Real", Fecha(8, 10, 2026));   // Pendiente

    Paquete* p303 = quemarPaquete(c3, "PK303", "Titulos academicos", 0.6, 4, "3001");
    quemarAlmacenado(p303, a3, 1, 0, lucia, Fecha(7, 10, 2026));
    SolicitudEnvio* s9 = quemarSolicitud(c3, "009", p303, lucia, "Turrialba, Avenida Central", Fecha(8, 10, 2026));
    Despacho* d4 = quemarAprobacion(c3, s9, "004", Fecha(9, 10, 2026, 10, 45));
    p303->marcarEntregado(lucia, Fecha(10, 10, 2026));
    d4->finalizar();                                                                       // Finalizado

    // Bodega amplia: sus indices de dos digitos usan el formato largo (B-F02-C11)
    Bodega* b3 = quemarBodega(c3, "B", "Bodega General Amplia", 1, 3, 12);
    Paquete* p304 = quemarPaquete(c3, "PK304", "Sacos de granos", 7.5, 1, "3002");
    quemarAlmacenado(p304, b3, 2, 11, pedro, Fecha(9, 10, 2026));
}

void Sistema::cargarDatosQuemados() {
    CentroDistribucion* c1 = new CentroDistribucion("CD-01", "Centro San Jose", "San Jose",
        "Avenida Central, 200m norte del parque", "22221111");
    CentroDistribucion* c2 = new CentroDistribucion("CD-02", "Centro Alajuela", "Alajuela",
        "Radial Francisco J. Orlich", "24332222");
    CentroDistribucion* c3 = new CentroDistribucion("CD-03", "Centro Cartago", "Cartago",
        "Frente a las Ruinas, calle principal", "25513333");

    c1->getClientes()->insertar(new ClientePersonaFisica("1001", "Maria Rojas", "88880001", "maria@correo.com"));
    c1->getClientes()->insertar(new ClienteEmpresa("1002", "Importadora Tica", "22220002", "info@importadora.com", "Importacion", 10));
    c1->getClientes()->insertar(new ClientePersonaFisica("1003", "Jorge Salas", "88880007", "jorge@correo.com"));   // sin movimientos: se puede eliminar

    c2->getClientes()->insertar(new ClientePersonaFisica("2001", "Carlos Vargas", "88880003", "carlos@correo.com"));
    c2->getClientes()->insertar(new ClienteEmpresa("2002", "Tecnologia Total", "24330004", "ventas@tecnototal.com", "Venta de tecnologia", 15));

    c3->getClientes()->insertar(new ClientePersonaFisica("3001", "Ana Jimenez", "88880005", "ana@correo.com"));
    c3->getClientes()->insertar(new ClienteEmpresa("3002", "Distribuidora Cartago", "25510006", "contacto@distcartago.com", "Distribucion de alimentos", 5));
    c3->getClientes()->insertar(new ClientePersonaFisica("3003", "Sara Brenes", "88880008", "sara@correo.com"));   // sin movimientos: se puede eliminar

    // Centro sin nada asociado: sirve para probar la eliminacion de centros
    CentroDistribucion* c4 = new CentroDistribucion("CD-04", "Centro Heredia", "Heredia",
        "Del parque central, 100m este", "22884444");

    quemarOperaciones(c1, c2, c3);

    registrarCentro(c1);
    registrarCentro(c2);
    registrarCentro(c3);
    registrarCentro(c4);
}