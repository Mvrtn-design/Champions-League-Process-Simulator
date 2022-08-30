#pragma once
#include "Equipo.h"
#include "Partido.h"

class Grupo
{
public:
	Grupo();
	Grupo(char l, int Cantidad);
	void meterEquipo(std::string _nombre, std::string _pais, int posicion);
	void meterEquipo(Equipo* aux);
	void mostrarGrupo();
	void calendario(int jornada);
	int getContador();
	void setEquipo(Equipo* aux,int posicion);
	char getLetra();
	Equipo* getEquipo(int posicion);

private:
	int contador;
	int cantidad;
	char letra;
	Equipo* integrante;
};