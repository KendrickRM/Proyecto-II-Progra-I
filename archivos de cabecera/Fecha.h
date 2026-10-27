#ifndef FECHA_H
#define FECHA_H

#include <string>
using namespace std;

// Persona 2. Fecha con dia, mes, anio, hora y minuto (sin ctime).
class Fecha {
private:
    int dia;
    int mes;
    int anio;
    int hora;
    int minuto;

public:
    Fecha();
    Fecha(int dia, int mes, int anio, int hora = 0, int minuto = 0);

    // Validaciones (estaticas, se pueden usar sin crear un objeto)
    static bool esBisiesto(int anio);
    static int diasDelMes(int mes, int anio);
    static bool esValida(int dia, int mes, int anio);
    static bool esHoraValida(int hora, int minuto);

    // Lectura desde teclado: repite hasta que la fecha sea valida
    static Fecha leerFecha(const string& msg);
    static Fecha leerFechaHora(const string& msg);

    int getDia() const;
    int getMes() const;
    int getAnio() const;
    int getHora() const;
    int getMinuto() const;

   
    int comparar(const Fecha& otra) const;

    string aTexto() const;          
    string aTextoConHora() const;   
    void mostrar() const;
};

#endif