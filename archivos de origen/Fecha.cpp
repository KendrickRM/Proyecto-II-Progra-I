#include "Fecha.h"
#include "Utilidades.h"
#include <iostream>
using namespace std;

static string dosDigitos(int n) {
    if (n < 10) {
        return "0" + to_string(n);
    }
    return to_string(n);
}

Fecha::Fecha() : dia(1), mes(1), anio(2026), hora(0), minuto(0) {}

Fecha::Fecha(int dia, int mes, int anio, int hora, int minuto) {
    if (esValida(dia, mes, anio) && esHoraValida(hora, minuto)) {
        this->dia = dia;
        this->mes = mes;
        this->anio = anio;
        this->hora = hora;
        this->minuto = minuto;
    }
    else {
        
        this->dia = 1;
        this->mes = 1;
        this->anio = 2026;
        this->hora = 0;
        this->minuto = 0;
    }
}

bool Fecha::esBisiesto(int anio) {
    return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
}

int Fecha::diasDelMes(int mes, int anio) {
    switch (mes) {
    case 1: case 3: case 5: case 7: case 8: case 10: case 12:
        return 31;
    case 4: case 6: case 9: case 11:
        return 30;
    case 2:
        return esBisiesto(anio) ? 29 : 28;
    default:
        return 0;
    }
}

bool Fecha::esValida(int dia, int mes, int anio) {
    if (anio < 1900 || anio > 2100) {
        return false;
    }
    if (mes < 1 || mes > 12) {
        return false;
    }
    if (dia < 1 || dia > diasDelMes(mes, anio)) {
        return false;
    }
    return true;
}

bool Fecha::esHoraValida(int hora, int minuto) {
    return hora >= 0 && hora <= 23 && minuto >= 0 && minuto <= 59;
}

Fecha Fecha::leerFecha(const string& msg) {
    cout << msg << endl;
    while (true) {
        int d = Utilidades::leerEntero("  Dia: ");
        int m = Utilidades::leerEntero("  Mes: ");
        int a = Utilidades::leerEntero("  Anio: ");
        if (esValida(d, m, a)) {
            return Fecha(d, m, a);
        }
        cout << "Error: fecha invalida. Intente de nuevo." << endl;
    }
}

Fecha Fecha::leerFechaHora(const string& msg) {
    Fecha f = leerFecha(msg);
    while (true) {
        int h = Utilidades::leerEntero("  Hora (0-23): ");
        int min = Utilidades::leerEntero("  Minuto (0-59): ");
        if (esHoraValida(h, min)) {
            return Fecha(f.dia, f.mes, f.anio, h, min);
        }
        cout << "Error: hora invalida. Intente de nuevo." << endl;
    }
}

int Fecha::getDia() const { return dia; }
int Fecha::getMes() const { return mes; }
int Fecha::getAnio() const { return anio; }
int Fecha::getHora() const { return hora; }
int Fecha::getMinuto() const { return minuto; }

int Fecha::comparar(const Fecha& otra) const {
    if (anio != otra.anio) return anio < otra.anio ? -1 : 1;
    if (mes != otra.mes) return mes < otra.mes ? -1 : 1;
    if (dia != otra.dia) return dia < otra.dia ? -1 : 1;
    if (hora != otra.hora) return hora < otra.hora ? -1 : 1;
    if (minuto != otra.minuto) return minuto < otra.minuto ? -1 : 1;
    return 0;
}

string Fecha::aTexto() const {
    return dosDigitos(dia) + "/" + dosDigitos(mes) + "/" + to_string(anio);
}

string Fecha::aTextoConHora() const {
    return aTexto() + " " + dosDigitos(hora) + ":" + dosDigitos(minuto);
}

void Fecha::mostrar() const {
    cout << aTexto();
}