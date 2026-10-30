#ifndef UTILIDADES_H
#define UTILIDADES_H
//Utilidades o validaciones
#include <string>
using namespace std;

//Se lanza al cerrarse la entrada 
class EntradaCerrada {};

class Utilidades {
public:
    static int leerEntero(const string& msg);
    static double leerDecimal(const string& msg);
    static string leerTexto(const string& msg);
    static int leerOpcion(int min, int max);
    static void limpiarBuffer();

    //Dibuja una tabla con bordes
    static void imprimirTabla(int columnas, int filas, const string* encabezados,
        const string* celdas, bool centrarCeldas = false);

    //Lecturas validadas
    static string leerIdCuatroDigitos(const string& msg);       
    static string leerCodigoTresDigitos(const string& msg);  
    static string leerNombre(const string& msg);               
    static string leerCodigoCentro(const string& msg);      
    static string leerCodigoPaquete(const string& msg);        
    static string leerCodigoBodega(const string& msg);         
    static string aMayusculas(const string& texto);
    static string leerCorreo(const string& msg);         
    static string leerTelefono(const string& msg);              

    //Validadores de formato
    static bool soloDigitos(const string& texto, int longitud);  
    static bool nombreValido(const string& texto);                
    static bool telefonoValido(const string& texto);              
    static bool correoValido(const string& texto);           
    static bool codigoPaqueteValido(const string& texto);       
};

#endif