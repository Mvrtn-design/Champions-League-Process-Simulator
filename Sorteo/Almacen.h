#pragma once
#include "Equipo.h"
#include "Grupo.h"

//AQUI SE METERA LA CANTIDAD TOTAL DE EQUIPOS, DE BOMBOS Y DE CLUBES DE UNA MISMA TEMPORADA

class Almacen
{
public:
	Almacen();
	Equipo getEquipo(int Equipo);
	void meterEquipo(std::string _nombre, std::string _pais, int posicion);
	void mostrarAlmacen();
	void asignacionBombos();
	void meterManualmente();
	void mostrarBombos();
	void realizarSorteo();
	void realizarSorteoFaseFinal();
	void realizarFaseGrupos();
	void realizarFaseFinal(int num);

	~Almacen();
private:
	Equipo *Clubes;
	Grupo *Grupos;
	Grupo *Bombo;
	int cantidad;
};