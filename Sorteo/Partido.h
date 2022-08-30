#pragma once
#include "Equipo.h"
#include "Grupo.h"

class Partido
{
public:
	Partido()=default;
	Partido(Equipo *l, Equipo *v);
	void actualizarDatos(Equipo *Local, Equipo * Visitante);	
	int getGolesLocal();
	int getGolesVisitante();
	Equipo getLocal();
	Equipo getVisitante();
	Equipo *partidoEliminatoria(Equipo* l, Equipo* v);

	
private:
	int golesLocal;
	int golesVisitante;
	Equipo *Local;
	Equipo *Visitante;
};

