#include "Utilidades.h"
#include <iostream>
#include <cstdlib>
using namespace std;

static string leerLinea(const string& msg) {
    string linea;
    cout << msg;
    if (!getline(cin, linea)) {
        cout << endl << "Entrada cerrada. Fin del programa." << endl;
        exit(0);
    }
    return linea;
}

int Utilidades::leerEntero(const string& msg) {
    while (true) {
        string t = leerLinea(msg);
        int i = 0;
        bool negativo = false;
        if (t[0] == '-') {
            negativo = true;
            i = 1;
        }
        bool ok = true;
        int digitos = 0;
        long valor = 0;
        while (t[i] != '\0') {
            if (t[i] < '0' || t[i] > '9') {
                ok = false;
                break;
            }
            valor = valor * 10 + (t[i] - '0');
            digitos++;
            if (digitos > 9) {
                ok = false;
                break;
            }
            i++;
        }
        if (digitos == 0) {
            ok = false;
        }
        if (!ok) {
            cout << "Error: digite un numero entero valido." << endl;
            continue;
        }
        if (negativo) {
            valor = -valor;
        }
        return (int)valor;
    }
}

double Utilidades::leerDecimal(const string& msg) {
    while (true) {
        string t = leerLinea(msg);
        int i = 0;
        bool negativo = false;
        if (t[0] == '-') {
            negativo = true;
            i = 1;
        }
        bool ok = true;
        bool punto = false;
        int digitos = 0;
        double entero = 0;
        double fraccion = 0;
        double divisor = 1;
        while (t[i] != '\0') {
            char c = t[i];
            if (c == '.' || c == ',') {
                if (punto) {
                    ok = false;
                    break;
                }
                punto = true;
            }
            else if (c >= '0' && c <= '9') {
                digitos++;
                if (digitos > 12) {
                    ok = false;
                    break;
                }
                if (!punto) {
                    entero = entero * 10 + (c - '0');
                }
                else {
                    divisor = divisor * 10;
                    fraccion = fraccion * 10 + (c - '0');
                }
            }
            else {
                ok = false;
                break;
            }
            i++;
        }
        if (digitos == 0) {
            ok = false;
        }
        if (!ok) {
            cout << "Error: digite un numero decimal valido." << endl;
            continue;
        }
        double valor = entero + fraccion / divisor;
        if (negativo) {
            valor = -valor;
        }
        return valor;
    }
}

string Utilidades::leerTexto(const string& msg) {
    while (true) {
        string t = leerLinea(msg);
        bool hayTexto = false;
        int i = 0;
        while (t[i] != '\0') {
            if (t[i] != ' ' && t[i] != '\t') {
                hayTexto = true;
            }
            i++;
        }
        if (!hayTexto) {
            cout << "Error: el texto no puede estar vacio." << endl;
            continue;
        }
        return t;
    }
}

int Utilidades::leerOpcion(int min, int max) {
    while (true) {
        int op = leerEntero("Seleccione una opcion: ");
        if (op >= min && op <= max) {
            return op;
        }
        cout << "Error: la opcion debe estar entre " << min << " y " << max << "." << endl;
    }
}

void Utilidades::limpiarBuffer() {
    cin.clear();
    cin.ignore(10000, '\n');
}