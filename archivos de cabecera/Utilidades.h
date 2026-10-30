#ifndef UTILIDADES_H
#define UTILIDADES_H
//Utilidades o validaciones
#include <string>
using namespace std;

// Se lanza cuando la entrada estandar se cierra (fin de archivo). main la captura para terminar el programa.
class EntradaCerrada {};

class Utilidades {
public:
    static int leerEntero(const string& msg);
    static double leerDecimal(const string& msg);
    static string leerTexto(const string& msg);
    static int leerOpcion(int min, int max);
    static void limpiarBuffer();

    // Dibuja una tabla con bordes. 'celdas' es una matriz en una sola lista, fila por fila
    // (filas * columnas textos). No usa STL: el que llama reserva y libera los arreglos.
    static void imprimirTabla(int columnas, int filas, const string* encabezados,
        const string* celdas, bool centrarCeldas = false);

    // Lecturas validadas: repiten hasta que el dato sea correcto
    static string leerIdCuatroDigitos(const string& msg);       // identificacion de 4 digitos
    static string leerCodigoTresDigitos(const string& msg);     // codigo de solicitud o despacho
    static string leerNombre(const string& msg);                // solo letras y espacios
    static string leerCodigoCentro(const string& msg);          // plantilla CD-XX: se digitan solo los 2 numeros
    static string leerCodigoPaquete(const string& msg);         // plantilla PKXXX: se digitan solo los 3 numeros
    static string leerCodigoBodega(const string& msg);          // acepta B o b: se guarda siempre en mayuscula
    static string aMayusculas(const string& texto);
    static string leerCorreo(const string& msg);          // debe contener @
    static string leerTelefono(const string& msg);              // solo numeros, exactamente 8 digitos

    // Validadores de formato (no leen del teclado)
    static bool soloDigitos(const string& texto, int longitud);   // exactamente 'longitud' digitos
    static bool nombreValido(const string& texto);                // solo letras y espacios, sin acentos
    static bool telefonoValido(const string& texto);              // solo digitos, exactamente 8
    static bool correoValido(const string& texto);             // una sola @, con texto antes y despues
    static bool codigoPaqueteValido(const string& texto);         // PK + 3 digitos (ej: PK101)
};

#endif