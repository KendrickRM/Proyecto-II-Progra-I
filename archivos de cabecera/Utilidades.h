#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <string>
using namespace std;

class Utilidades {
public:
    static int leerEntero(const string& msg);
    static double leerDecimal(const string& msg);
    static string leerTexto(const string& msg);
    static int leerOpcion(int min, int max);
    static void limpiarBuffer();
};

#endif