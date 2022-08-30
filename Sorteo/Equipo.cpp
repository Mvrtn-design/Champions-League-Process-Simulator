#include "iostream"
#include "Equipo.h"
#include "string"
#include "stdlib.h"

using namespace std;

Equipo::Equipo(std::string _nombre, std::string _pais, int _posicion) {
	posicionLiga = _posicion;
	goles = 0;
	golesEncajados = 0;
	victorias = 0;
	empates = 0;
	derrotas = 0;
	puntos = 0;
	nombre = _nombre;
	pais = _pais;
	encuadrado = false;
}
Equipo::Equipo() {
	nombre = "Sin nombre";
}


void Equipo::setPosicionLiga(int nueva)
{
}
void Equipo::addGoles(int _goles)
{
	this->goles =goles + _goles;
}
void Equipo::addGolesEncajados(int _goles)
{
	golesEncajados += _goles;
}
void Equipo::addPuntos(int _puntos)
{
	this->puntos = puntos + _puntos;
}
void Equipo::addVictoria()
{
	this->victorias++;
}
void Equipo::addEmpate()
{
	empates++;
}
void Equipo::addDerrota()
{
	derrotas++;
}
void Equipo::setNombre(std::string _nuevo)
{
	nombre = _nuevo;
}
void Equipo::setPais(std::string _nuevo)
{
	pais = _nuevo;
}
std::string Equipo::getNombre() {
	return nombre;
}
std::string Equipo::getPais()
{
	return pais;
}
int Equipo::getPosicion()
{
	return posicionLiga;
}
Equipo Equipo::getEquipo()
{
	return *this;
}
int Equipo::getGoles() {
	return goles;
}
int Equipo::getGolesEncajados()
{
	return golesEncajados;
}
bool Equipo::getEncuadrado()
{
	return encuadrado;
}
void Equipo::setEncuadrado(bool opcion)
{
	encuadrado = opcion;
}
int Equipo::getPuntos() {
	return puntos;
}
int Equipo::getVictorias() {
	return victorias;
}

int Equipo::getEmpates()
{
	return empates;;
}

int Equipo::getDerrotas()
{
	return derrotas;
}

Equipo::~Equipo() {

}