#ifndef TARIFA_H
#define TARIFA_H

#include <string>
#include "Cliente.h"
using namespace std;

// Persona 3. Tarifas por kilogramo compartidas (static) y calculo de costos.
// Los codigos de categoria coinciden con los de Bodega/Paquete:
// 1 General, 2 Fragil, 3 Tecnologia, 4 Documentos.
class Tarifa {
private:
	static const double TARIFA_GENERAL;
	static const double TARIFA_FRAGIL;
	static const double TARIFA_TECNOLOGIA;
	static const double TARIFA_DOCUMENTOS;

	Tarifa();
	Tarifa(const Tarifa&);
	Tarifa& operator=(const Tarifa&);

public:
	static double obtenerTarifa(int categoria);
	static double calcularCostoBase(double peso, int categoria);
	static double calcularCostoFinal(double peso, int categoria, const Cliente* cliente);

	// Texto con 2 decimales, sin usar iomanip (ej: 1500 -> "1500.00")
	static string formatearDecimal(double valor);
};

#endif
