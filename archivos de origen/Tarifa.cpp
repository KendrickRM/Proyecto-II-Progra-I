#include "Tarifa.h"
#include <sstream>
using namespace std;

const double Tarifa::TARIFA_GENERAL = 1500;
const double Tarifa::TARIFA_FRAGIL = 2000;
const double Tarifa::TARIFA_TECNOLOGIA = 2500;
const double Tarifa::TARIFA_DOCUMENTOS = 1000;

double Tarifa::obtenerTarifa(int categoria) {
	switch (categoria) {
	case 1: return TARIFA_GENERAL;
	case 2: return TARIFA_FRAGIL;
	case 3: return TARIFA_TECNOLOGIA;
	case 4: return TARIFA_DOCUMENTOS;
	default: return 0;
	}
}

double Tarifa::calcularCostoBase(double peso, int categoria) {
	return peso * obtenerTarifa(categoria);
}

double Tarifa::calcularCostoFinal(double peso, int categoria, const Cliente* cliente) {
	double base = calcularCostoBase(peso, categoria);
	double descuento = 0;
	if (cliente != 0) {
		descuento = cliente->obtenerDescuento();
	}
	return base - (base * descuento / 100);
}

string Tarifa::formatearDecimal(double valor) {

	ostringstream os;
	os.setf(ios::fixed);
	os.precision(2);
	os << valor;
	return os.str();
}
