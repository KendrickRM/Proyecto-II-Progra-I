#include "Utilidades.h"
#include <iostream>
using namespace std;

//Largo maximo de los textos
static const int MAX_TEXTO = 100;

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
        double valor = 0;
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
            cout << "Error: no se permiten numeros negativos (el minimo es 0)." << endl;
            continue;
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
        if (negativo) {
            cout << "Error: no se permiten numeros negativos (el minimo es 0)." << endl;
            continue;
        }
        return entero + fraccion / divisor;
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
        if ((int)t.length() > MAX_TEXTO) {
            cout << "Error: el texto no puede tener mas de " << MAX_TEXTO << " caracteres." << endl;
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
        if ((int)t.length() > MAX_TEXTO) {
            cout << "Error: el nombre no puede tener mas de " << MAX_TEXTO << " caracteres." << endl;
            continue;
        }
        if (nombreValido(t)) {
            return t;
        }
        cout << "Error: el nombre solo puede contener letras y espacios, sin numeros ni simbolos." << endl;
    }
}

string Utilidades::leerCorreo(const string& msg) {
    while (true) {
        string t = leerLinea(msg);
        if ((int)t.length() > MAX_TEXTO) {
            cout << "Error: el correo no puede tener mas de " << MAX_TEXTO << " caracteres." << endl;
            continue;
        }
        if (correoValido(t)) {
            return t;
        }
        cout << "Error: el correo debe contener una @ con texto antes y despues, y sin espacios." << endl;
    }
}


static string ajustar(const string& texto, int ancho, bool centrado) {
    int falta = ancho - (int)texto.size();
    if (falta <= 0) {
        return texto;
    }
    if (!centrado) {
        return texto + string(falta, ' ');
    }
    int izquierda = falta / 2;
    return string(izquierda, ' ') + texto + string(falta - izquierda, ' ');
}

void Utilidades::imprimirTabla(int columnas, int filas, const string* encabezados,
    const string* celdas, bool centrarCeldas) {
    int* ancho = new int[columnas];
    for (int c = 0; c < columnas; c++) {
        ancho[c] = (int)encabezados[c].size();
        for (int f = 0; f < filas; f++) {
            int largo = (int)celdas[f * columnas + c].size();
            if (largo > ancho[c]) {
                ancho[c] = largo;
            }
        }
    }

    string separador = "+";
    for (int c = 0; c < columnas; c++) {
        separador += string(ancho[c] + 2, '-') + "+";
    }

    cout << separador << endl << "|";
    for (int c = 0; c < columnas; c++) {
        cout << " " << ajustar(encabezados[c], ancho[c], true) << " |";
    }
    cout << endl << separador << endl;
    for (int f = 0; f < filas; f++) {
        cout << "|";
        for (int c = 0; c < columnas; c++) {
            cout << " " << ajustar(celdas[f * columnas + c], ancho[c], centrarCeldas) << " |";
        }
        cout << endl;
    }
    cout << separador << endl;
    delete[] ancho;
}

//El sistema agrega el prefijo 
string Utilidades::leerCodigoCentro(const string& msg) {
    while (true) {
        string t = leerLinea(msg + "CD-");
        if (soloDigitos(t, 2)) {
            return "CD-" + t;
        }
        cout << "Error: digite exactamente 2 numeros (CD-XX)." << endl;
    }
}

string Utilidades::leerCodigoPaquete(const string& msg) {
    while (true) {
        string t = leerLinea(msg + "PK");
        if (soloDigitos(t, 3)) {
            return "PK" + t;
        }
        cout << "Error: digite exactamente 3 numeros (PKXXX)." << endl;
    }
}

string Utilidades::aMayusculas(const string& texto) {
    string r = texto;
    for (int i = 0; i < (int)r.length(); i++) {
        if (r[i] >= 'a' && r[i] <= 'z') {
            r[i] = r[i] - 'a' + 'A';
        }
    }
    return r;
}

//No distingue mayusculas
string Utilidades::leerCodigoBodega(const string& msg) {
    while (true) {
        string t = aMayusculas(leerTexto(msg));
        bool valido = (int)t.length() <= 5;
        for (int i = 0; i < (int)t.length(); i++) {
            bool letra = t[i] >= 'A' && t[i] <= 'Z';
            bool digito = t[i] >= '0' && t[i] <= '9';
            if (!letra && !digito) {
                valido = false;
            }
        }
        if (valido) {
            return t;
        }
        cout << "Error: el codigo de bodega debe tener de 1 a 5 letras o numeros, sin espacios ni simbolos." << endl;
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