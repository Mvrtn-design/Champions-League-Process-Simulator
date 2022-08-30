#include "Grupo.h"
#include "Equipo.h"
#include "iostream"
#include "Partido.h"
#include <stdlib.h>

using namespace std;

Grupo::Grupo()
{
}

Grupo::Grupo(char l, int Cantidad) {
	this->letra = l;
	this->cantidad = Cantidad;
	this->contador = 0;
	this->integrante = new Equipo[cantidad];

}
void Grupo::meterEquipo(std::string _nombre, std::string _pais, int posicion) {
	if (contador <= cantidad) {
		Equipo  aux = Equipo(_nombre, _pais, posicion);
		integrante[contador] = aux;
		contador++;
	}
	else {
		cout << "No hay mas espacio disponible";
	}
}
void Grupo::meterEquipo(Equipo* aux) {
	if (contador <= cantidad) {
		integrante[contador] = *aux;
		contador++;
	}
	else {
		cout << "No hay mas espacio disponible";
	}
}
void Grupo::calendario(int jornada) {
	
	if (jornada == 0) {
		Partido p11(&integrante[0], &integrante[2]);
		Partido p12(&integrante[1], &integrante[3]);
	}
	else if (jornada == 1) {
		Partido p21(&integrante[3], &integrante[0]);
		Partido p22(&integrante[2], &integrante[1]);
	}
	else if (jornada == 2) {
		Partido p31(&integrante[3], &integrante[2]);
		Partido p32(&integrante[1], &integrante[0]);
	}
	else if (jornada == 3) {
		Partido p41(&integrante[0], &integrante[1]);
		Partido p42(&integrante[2], &integrante[3]);
	}
	else if (jornada == 4) {
		Partido p21(&integrante[3], &integrante[1]);
		Partido p22(&integrante[2], &integrante[0]);
	}
	else if (jornada == 5) {
		Partido p21(&integrante[1], &integrante[2]);
		Partido p22(&integrante[0], &integrante[3]);
	}
}
int Grupo::getContador()
{
	return contador;
}
void Grupo::setEquipo(Equipo *aux, int posicion)
{
	if (contador <= cantidad) {
		integrante[posicion] = *aux;
	}
	else {
		cout << "No hay mas espacio disponible";
	}
}
char Grupo::getLetra()
{
	return letra;
}
void Grupo::mostrarGrupo() {
	if (contador > 0 && contador <= 4) {
		int i;
		cout << "\nNombre\t\t\tVictorias\tEmpates\tDerrotas\tGoles\tGolesEncajados\tPUNTOS" << endl;


		Equipo aux;

		for (int i = 0; i < 4; i++) {

			for (int j = 0; j < i; j++) {
				if (integrante[i].getPuntos() > integrante[j].getPuntos()) {
					aux = integrante[i];
					integrante[i] = integrante[j];
					integrante[j] = aux;
				}
				else if (integrante[i].getPuntos() == integrante[j].getPuntos() &&
					(integrante[i].getGoles() - integrante[i].getGolesEncajados()) > (integrante[j].getGoles() - integrante[j].getGolesEncajados())) {
					aux = integrante[i];
					integrante[i] = integrante[j];
					integrante[j] = aux;
				}
			}
		}
		for (i = 0; i < contador; i++) {
			cout << integrante[i].getNombre();
			cout << "\t\t" << integrante[i].getVictorias() << "\t" << integrante[i].getEmpates() << "\t" << integrante[i].getDerrotas();
			cout << "\t\t" << integrante[i].getGoles() << "\t" << integrante[i].getGolesEncajados();
			cout << "\t\t" << integrante[i].getPuntos() << endl;
		}
	}
	else {
		cout << "no hay nadie metido en el grupo";
	}
}

Equipo* Grupo::getEquipo(int posicion) {
	if (posicion >= 0 && posicion < cantidad) {
		return (&integrante[posicion]);
	}
}