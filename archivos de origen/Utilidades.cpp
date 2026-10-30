#include "Utilidades.h"
#include <iostream>
using namespace std;

static string leerLinea(const string& msg) {
    string linea;
    cout << msg;
    if (!getline(cin, linea)) {
        cout << endl << "Entrada cerrada. Fin del programa." << endl;
        throw EntradaCerrada();
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

string Utilidades::leerIdCuatroDigitos(const string& msg) {
    while (true) {
        string t = leerLinea(msg);
        if (soloDigitos(t, 4)) {
            return t;
        }
        cout << "Error: la identificacion debe tener exactamente 4 digitos." << endl;
    }
}

string Utilidades::leerCodigoTresDigitos(const string& msg) {
    while (true) {
        string t = leerLinea(msg);
        if (soloDigitos(t, 3)) {
            return t;
        }
        cout << "Error: el codigo debe tener exactamente 3 digitos." << endl;
    }
}

string Utilidades::leerNombre(const string& msg) {
    while (true) {
        string t = leerLinea(msg);
        if (nombreValido(t)) {
            return t;
        }
        cout << "Error: el nombre solo puede contener letras y espacios, sin numeros ni simbolos." << endl;
    }
}

string Utilidades::leerCorreo(const string& msg) {
    while (true) {
        string t = leerLinea(msg);
        if (correoValido(t)) {
            return t;
        }
        cout << "Error: el correo debe contener una @ con texto antes y despues, y sin espacios." << endl;
    }
}

string Utilidades::leerTelefono(const string& msg) {
    while (true) {
        string t = leerLinea(msg);
        if (telefonoValido(t)) {
            return t;
        }
        cout << "Error: digite un numero de telefono valido (solo numeros, exactamente 8 digitos)." << endl;
    }
}

bool Utilidades::telefonoValido(const string& texto) {
    return soloDigitos(texto, 8);
}

bool Utilidades::soloDigitos(const string& texto, int longitud) {
    if ((int)texto.length() != longitud) {
        return false;
    }
    for (int i = 0; i < longitud; i++) {
        if (texto[i] < '0' || texto[i] > '9') {
            return false;
        }
    }
    return true;
}

bool Utilidades::nombreValido(const string& texto) {
    bool hayLetra = false;
    for (int i = 0; i < (int)texto.length(); i++) {
        char ch = texto[i];
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
            hayLetra = true;
        }
        else if (ch != ' ') {
            return false;
        }
    }
    return hayLetra;
}

bool Utilidades::correoValido(const string& texto) {
    int arrobas = 0;
    int posicion = -1;
    for (int i = 0; i < (int)texto.length(); i++) {
        if (texto[i] == ' ') {
            return false;
        }
        if (texto[i] == '@') {
            arrobas++;
            posicion = i;
        }
    }
    return arrobas == 1 && posicion > 0 && posicion < (int)texto.length() - 1;
}

bool Utilidades::codigoPaqueteValido(const string& texto) {
    if (texto.length() != 5 || texto[0] != 'P' || texto[1] != 'K') {
        return false;
    }
    return soloDigitos(texto.substr(2), 3);
}