#include "Partido.h"
#include "Equipo.h"
#include "Grupo.h"
#include "cstdlib"
#include "time.h"
#include "iostream"
#include <thread>         // std::this_thread::sleep_for

using namespace std;

Partido::Partido(Equipo* l, Equipo* v) {
	srand(time(NULL));
	std::this_thread::sleep_for(std::chrono::seconds(1));

	golesLocal = rand() % 4;
	golesVisitante = rand() % 4;

	cout << l->getNombre() << " " << golesLocal << "-" << golesVisitante << " " << v->getNombre() << endl;

	actualizarDatos(l, v);
}
void Partido::actualizarDatos(Equipo* Local, Equipo* Visitante) {
	Local->addGoles(golesLocal);
	Local->addGolesEncajados(getGolesVisitante());


	Visitante->addGolesEncajados(golesLocal);
	Visitante->addGoles(golesVisitante);


	if (golesLocal > golesVisitante) {
		Local->addPuntos(3);
		Local->addVictoria();
		Visitante->addDerrota();
	}
	else if (golesLocal < golesVisitante) {
		Visitante->addPuntos(3);
		Visitante->addVictoria();
		Local->addDerrota();
	}
	else {
		Local->addPuntos(1);
		Visitante->addPuntos(1);
		Local->addEmpate();
		Visitante->addEmpate();
	}
}

int Partido::getGolesLocal()
{
	return golesLocal;
}

int Partido::getGolesVisitante()
{
	return golesVisitante;
}

Equipo Partido::getLocal()
{
	return *Local;
}

Equipo Partido::getVisitante()
{
	return *Visitante;
}

Equipo* Partido::partidoEliminatoria(Equipo* l, Equipo* v) {

	srand(time(NULL));
	std::this_thread::sleep_for(std::chrono::seconds(1));

	golesLocal = rand() % 4;
	golesVisitante = rand() % 4;
	int gl = golesLocal, gv = golesVisitante;
	Equipo* ganador = l;//asignacion solo para que esté inicializado
	Equipo* perdedor = l;


	cout << "\n" << l->getNombre() << " " << golesLocal << "-" << golesVisitante << " " << v->getNombre() << endl;


	if (gl > gv) {

		ganador = l;
		perdedor = v;
	}
	else if (gl < gv) {

		ganador = v;
		perdedor = l;
	}
	else {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		int pl = rand() % 2;
		std::this_thread::sleep_for(std::chrono::seconds(1));
		int pv = rand() % 2;

		gv += pv;
		gl += pl;

		cout << "PRÓRROGA: " << pl << "-" << pv << endl;
		if (gl > gv) {

			ganador = l;
			perdedor = v;

		}
		else if (gl < gv) {
			ganador = v;
			perdedor = l;
		}
		else {
			std::this_thread::sleep_for(std::chrono::seconds(2));
			int pel = rand() % 5;
			std::this_thread::sleep_for(std::chrono::seconds(2));
			int pev = rand() % 5;

			cout << "PENALTIS: " << pel << " - " << pev << endl;
			if (pel > pev) {
				ganador = l;
				perdedor = v;
			}
			else if (pel < pev) {
				ganador = v;
				perdedor = l;
			}
		}
	}
	l->addGoles(gl);
	l->addGolesEncajados(gv);
	v->addGoles(gv);
	v->addGolesEncajados(gl);
	ganador->addVictoria();
	perdedor->addDerrota();

	cout << "GANADOR: " << ganador->getNombre() << endl;
	return ganador;
}
