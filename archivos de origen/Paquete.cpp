#include "Paquete.h"
#include "Utilidades.h"
#include <iostream>
using namespace std;

Paquete::Paquete(const string& codigo, const string& descripcion, double peso,
    int categoria, Cliente* propietario, const string& codigoCentro)
    : codigo(codigo), descripcion(descripcion), peso(peso), categoria(categoria),
    propietario(propietario), codigoCentro(codigoCentro),
    estado(RECIBIDO), estadoPrevioIncidencia(RECIBIDO), bodega(0), celda(0) {

    if (this->peso > pesoMaximo()) {
        this->peso = pesoMaximo();
    }
    if (this->peso <= 0) {
        this->peso = 0.01;
    }
    bitacora = new ListaBitacora();
}

double Paquete::pesoMaximo() {
    return 5000;
}

Paquete::~Paquete() {
   
    delete bitacora;
}

string Paquete::getCodigo() const { return codigo; }
string Paquete::getDescripcion() const { return descripcion; }
double Paquete::getPeso() const { return peso; }
int Paquete::getCategoria() const { return categoria; }
string Paquete::getNombreCategoria() const { return Bodega::nombreTipo(categoria); }
Cliente* Paquete::getPropietario() const { return propietario; }
string Paquete::getCodigoCentro() const { return codigoCentro; }
int Paquete::getEstado() const { return estado; }
string Paquete::getNombreEstado() const { return nombreEstado(estado); }
Bodega* Paquete::getBodega() const { return bodega; }
Celda* Paquete::getCelda() const { return celda; }
ListaBitacora* Paquete::getBitacora() const { return bitacora; }

bool Paquete::categoriaValida(int categoria) {
    return Bodega::tipoValido(categoria);
}

string Paquete::nombreEstado(int estado) {
    switch (estado) {
    case RECIBIDO: return "Recibido";
    case ALMACENADO: return "Almacenado";
    case EN_TRANSITO: return "En transito";
    case ENTREGADO: return "Entregado";
    case INCIDENCIA: return "Incidencia";
    default: return "Desconocido";
    }
}

bool Paquete::puedeCambiarA(int nuevo) const {
    switch (estado) {
    case RECIBIDO:
        return nuevo == ALMACENADO || nuevo == INCIDENCIA;
    case ALMACENADO:
        return nuevo == EN_TRANSITO || nuevo == INCIDENCIA;
    case EN_TRANSITO:
        return nuevo == ENTREGADO || nuevo == INCIDENCIA;
    case INCIDENCIA:
        
        if (estadoPrevioIncidencia == EN_TRANSITO) {
            return nuevo == EN_TRANSITO;
        }
        return nuevo == ALMACENADO;
    default:
        return false;   
    }
}

void Paquete::aplicarCambio(int nuevo, Colaborador* responsable, const Fecha& fecha) {
    if (nuevo == INCIDENCIA) {
        estadoPrevioIncidencia = estado;
    }
    bitacora->insertar(new RegistroBitacora(estado, nuevo, fecha, responsable));
    estado = nuevo;
}

bool Paquete::almacenar(Bodega* b, Celda* c, Colaborador* responsable, const Fecha& fecha) {
    if (b == 0 || c == 0 || responsable == 0) {
        return false;
    }
    if (!puedeCambiarA(ALMACENADO)) {
        return false;
    }
    
    if (estado == INCIDENCIA && estadoPrevioIncidencia != RECIBIDO) {
        return false;
    }
    if (!b->esCompatible(categoria)) {
        return false;
    }
    if (b->getCelda(c->getFila(), c->getColumna()) != c) {
        return false;   
    }
    if (!c->asignar(this)) {
        return false;   
    }
    bodega = b;
    celda = c;
    aplicarCambio(ALMACENADO, responsable, fecha);
    return true;
}

bool Paquete::reubicar(Bodega* nuevaBodega, Celda* nuevaCelda) {
    if (estado != ALMACENADO || celda == 0 || bodega == 0) {
        return false;
    }
    if (nuevaBodega == 0 || nuevaCelda == 0 || nuevaCelda == celda) {
        return false;
    }
    if (!nuevaBodega->esCompatible(categoria)) {
        return false;
    }
    if (nuevaBodega->getCelda(nuevaCelda->getFila(), nuevaCelda->getColumna()) != nuevaCelda) {
        return false;
    }
    if (!nuevaCelda->asignar(this)) {
        return false;
    }
    celda->liberar();
    bodega = nuevaBodega;
    celda = nuevaCelda;
    return true;
}

bool Paquete::pasarATransito(Colaborador* responsable, const Fecha& fecha) {
    if (responsable == 0 || estado != ALMACENADO) {
        return false;
    }
    if (celda != 0) {
        celda->liberar();
    }
    celda = 0;
    bodega = 0;
    aplicarCambio(EN_TRANSITO, responsable, fecha);
    return true;
}

bool Paquete::marcarEntregado(Colaborador* responsable, const Fecha& fecha) {
    if (responsable == 0 || estado != EN_TRANSITO) {
        return false;
    }
    aplicarCambio(ENTREGADO, responsable, fecha);
    return true;
}

bool Paquete::registrarIncidencia(Colaborador* responsable, const Fecha& fecha) {
    if (responsable == 0 || !puedeCambiarA(INCIDENCIA)) {
        return false;
    }
    
    aplicarCambio(INCIDENCIA, responsable, fecha);
    return true;
}

bool Paquete::resolverIncidencia(Colaborador* responsable, const Fecha& fecha) {
    if (responsable == 0 || estado != INCIDENCIA) {
        return false;
    }
    
    if (estadoPrevioIncidencia == RECIBIDO) {
        return false;
    }
    int destino = estadoPrevioIncidencia;   
    if (!puedeCambiarA(destino)) {
        return false;
    }

    aplicarCambio(destino, responsable, fecha);
    return true;
}

bool Paquete::necesitaAlmacenarse() const {
    return estado == RECIBIDO || (estado == INCIDENCIA && estadoPrevioIncidencia == RECIBIDO);
}

int Paquete::getEstadoPrevioIncidencia() const {
    return estadoPrevioIncidencia;
}

bool Paquete::tieneColaboradorEnBitacora(const string& identificacion) const {
    return bitacora->participoColaborador(identificacion);
}

void Paquete::mostrar() const {
    cout << "Codigo: " << codigo << endl;
    cout << "Descripcion: " << descripcion << endl;
    cout << "Peso: " << peso << " kg" << endl;
    cout << "Categoria: " << getNombreCategoria() << endl;
    if (propietario != 0) {
        cout << "Cliente: " << propietario->getNombre()
            << " (" << propietario->getIdentificacion() << ")" << endl;
    }
    cout << "Centro: " << codigoCentro << endl;
    cout << "Estado: " << getNombreEstado() << endl;
    if (bodega != 0 && celda != 0) {
        cout << "Ubicacion: bodega " << bodega->getCodigo()
            << ", celda " << celda->getIdentificador() << endl;
    }
    else {
        cout << "Ubicacion: sin bodega ni celda" << endl;
    }
}

void Paquete::mostrarBitacora() const {
    if (bitacora->getCantidad() == 0) {
        cout << "El paquete aun no tiene cambios de estado." << endl;
        return;
    }
    //Del mas antiguo al mas reciente
    int n = bitacora->getCantidad();
    string encabezados[5] = { "#", "Estado anterior", "Nuevo estado", "Fecha", "Responsable" };
    string* celdas = new string[n * 5];
    for (int i = 0; i < n; i++) {
        RegistroBitacora* r = bitacora->obtener(i);
        celdas[i * 5] = to_string(i + 1);
        celdas[i * 5 + 1] = nombreEstado(r->getEstadoAnterior());
        celdas[i * 5 + 2] = nombreEstado(r->getEstadoNuevo());
        celdas[i * 5 + 3] = r->getFecha().aTexto();
        if (r->getResponsable() != 0) {
            celdas[i * 5 + 4] = r->getResponsable()->getNombreCompleto()
                + " (" + r->getResponsable()->getIdentificacion() + ")";
        }
        else {
            celdas[i * 5 + 4] = "-";
        }
    }
    Utilidades::imprimirTabla(5, n, encabezados, celdas);
    delete[] celdas;
}