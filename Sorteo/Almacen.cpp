#include "Almacen.h"
#include "iostream"
#include "cassert"
#include "Equipo.h"
#include "Grupo.h"
#include <stdlib.h>
#include <thread>         // std::this_thread::sleep_for

using namespace std;

Almacen::Almacen() {
	this->cantidad = 0;
	this->Bombo = new Grupo[6];
	this->Grupos = new Grupo[8];
	this->Clubes = new Equipo[32];

	//Los 4 bombos , un bombo donde pondremos a los que pasan de ronda y otro con los mismos pero ya emparejadosn
	Bombo[0] = Grupo('1', 8);
	Bombo[1] = Grupo('2', 8);
	Bombo[2] = Grupo('3', 8);
	Bombo[3] = Grupo('4', 8);
	Bombo[4] = Grupo('C', 16);
	Bombo[5] = Grupo('F', 16);

	//Los 8 grupos de la fase de grupos
	for (int i = 0; i < 8; i++)
	{
		char letra = (65 + i);
		Grupos[i] = Grupo(letra, 4);
	}
}
void Almacen::meterEquipo(std::string _nombre, std::string _pais, int posicion) {
	Clubes[cantidad] = Equipo(_nombre, _pais, posicion);
	cantidad++;
	cout << "Equipo metido: " << Clubes[cantidad - 1].getNombre() << endl;
}

void Almacen::mostrarAlmacen() {
	assert(cantidad > 0);
	cout << "Hay " << cantidad << ", que son:" << endl;

	for (int i = 0; i < cantidad; i++)
	{
		cout << Clubes[i].getPais() << endl;
	}
}

void Almacen::asignacionBombos()
{
	/*
	- Hay que separar los equipos en 4 bombos con sus respectivas caracteristicas (Cada equipo de un bombo irá a un grupo diferente)
	- En el 1º bombo los campeones de sus respectivas ligas (Las 7 ligas principales) y el ganador de la Europa League ,(si es repetido se pasa a la siguiente liga)
	- En el 2º bombo 2 de España , 2 de Inglaterra , 2 de Alemania y 1 de Francia e Italia
	- En el 3º bombo 2 de Italia, 1 de Alemania,España,Inglaterra,Francia,Portugal,Ucrania
*/

	int i, j, found;
	std::string paises[] = { "Spain ","England ","Italy ","Germany ","France ","Portugal ","Turkey ","Ukraine " };
	int contador[] = { 4,4,4,3,3,2,2,2,7 };  //numero de equipos de cada pais



	Bombo[0].meterEquipo(&Clubes[0]);
	for (i = 1; i < cantidad; i++)
	{
		found = 0;
		for (j = 0; j < 8; j++) {
			if (Clubes[i].getPais() == (paises[j]) && found == 0) {
				cout << Clubes[i].getNombre();
				found = 1;
				if (Clubes[i].getPosicion() == 1 && j < 7) {
					Bombo[0].meterEquipo(&Clubes[i]);
					cout << " al bombo 1" << endl;
				}
				else if ((Clubes[i].getPosicion() == 2 && j < 6 || (j < 4 && Clubes[i].getPosicion() == 3)) && Bombo[1].getContador() < 8) {
					Bombo[1].meterEquipo(&Clubes[i]);
					cout << " al bombo 2" << endl;
				}
				else {
					Bombo[2].meterEquipo(&Clubes[i]);
					cout << " al bombo 3" << endl;
				}
			}
		}
		if (!found) {
			Bombo[3].meterEquipo(&Clubes[i]);
			cout << Clubes[i].getNombre() << " al bombo 4" << endl;
		}
	}
}

void Almacen::meterManualmente()
{
	std::string nombre;
	std::string pais;
	int posicion;
	cout << "\nIntroduzca nombre del club: "; cin >> nombre;
	cout << "\nIntroduzca su pais (en ingles): ";	cin >> pais;
	cout << "\nIntroduzca la posicion ocupada en su respectiva liga: ";	cin >> posicion;
	meterEquipo(nombre, pais, posicion);
}

void Almacen::mostrarBombos()
{
	int i, j;
	srand(time(NULL));

	for (i = 0; i < 4; i++)
	{
		std::this_thread::sleep_for(std::chrono::seconds(2));
		cout << "\n\nBOMBO " << i + 1 << endl;
		for (j = 0; j < Bombo[i].getContador(); j++)
		{
			cout << Bombo[i].getEquipo(j)->getNombre() << "\t(" << Bombo[i].getEquipo(j)->getPais() << ")" << endl;
		}
	}
}

void Almacen::realizarSorteo()
{
	srand(time(NULL));
	bool correcto = true;
	int orden[] = { 0,1,2,3,4,5,6,7 };
	int i, j, k, l;
	for (i = 0; i < 4; i++)
	{
		if (Bombo[i].getContador() != 8) {
			correcto = false;
		}
	}
	if (correcto) {
		for (i = 0; i < 4; i++)  //Cada bombo
		{
			int selec[] = { 0,0,0,0,0,0,0,0 };

			int aux, au;
			std::this_thread::sleep_for(std::chrono::seconds(1));
			cout << "\n\n\t---Bombo " << i + 1 << endl;

			for (j = 0; j < 8; j++)  //Cada equipo
			{
				std::this_thread::sleep_for(std::chrono::seconds(1));
				cout << "\nTurno de: " << Bombo[i].getEquipo(j)->getNombre();

				Bombo[i].getEquipo(j)->setEncuadrado(false);

				for (k = 0; k < 8; k++)//Para establecer un orden de preferencia de grupos aletorio 
				{
					aux = rand() % 7;
					au = orden[k];
					orden[k] = orden[aux];
					orden[aux] = au;

					if (k % 4 == 0) {
						cout << ".";
						std::this_thread::sleep_for(std::chrono::seconds(1));
					}
				}
				for (k = 0; k < 8 && (Bombo[i].getEquipo(j)->getEncuadrado() == false); k++) //Cada grupo
				{
					for (l = 0; l < 4; l++)    //Los cuatro espacios del grupo
					{
						if (Bombo[i].getEquipo(j)->getPais() == Grupos[orden[k]].getEquipo(l)->getPais())
						{
							if (selec[orden[k]] == 0) {
								selec[orden[k]] = 2;
							}
							//Ese equipo no puede ir a ese grupo.
						}
					}
					if (selec[orden[k]] == 0 && Bombo[i].getEquipo(j)->getEncuadrado() == false)    //'i' en lugar de 'l' porque cada uno de un bombo ocupa ese lugar en su grupo 
					{
						Grupos[orden[k]].meterEquipo(Bombo[i].getEquipo(j));
						Bombo[i].getEquipo(j)->setEncuadrado(true);
						selec[orden[k]] = 1;
						cout << "\t grupo " << char(orden[k] + 65);
					}
				}
				for (l = 0; l < 8; l++) {
					if (selec[l] == 2) {
						selec[l] = 0;
					}
				}
			}
		}
		cin.ignore();
		for (int i = 0; i < 8; i++) {
			Grupos[i].mostrarGrupo();
		}
	}
	else {
		cout << "no está todo correcto";
	}
}

void Almacen::realizarSorteoFaseFinal() {

	int i, j, k = 0, aux, au, posicion;
	int orden[] = { 0,1,2,3,4,5,6,7 };
	int asig[] = { 0,0,0,0,0,0,0,0 };

	cout << "\nEquipos clasificados" << endl;
	for (i = 0; i < 8; i++)
	{
		Bombo[4].meterEquipo(Grupos[i].getEquipo(0));
		Bombo[4].meterEquipo(Grupos[i].getEquipo(1));
		cout << "- " << Grupos[i].getEquipo(0)->getNombre() << endl;
		cout << "- " << Grupos[i].getEquipo(1)->getNombre() << endl;
	}

	for (i = 0; i < 8; i++) {
		if (i % 4 == 0) {
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		aux = rand() % 7;
		au = orden[i];
		orden[i] = orden[aux];
		orden[aux] = au;
	}
	for (i = 0; i < 8; i++) {
		Bombo[5].setEquipo(Grupos[i].getEquipo(0), orden[i] * 2);
	}
	for (i = 0; i < 8; i++) {
		if (i % 4 == 0) {
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		aux = rand() % 7;
		au = orden[i];
		orden[i] = orden[aux];
		orden[aux] = au;
	}
	for (i = 0; i < 8; i++) {
		bool asignado = false;
		for (j = 0; j < 8 && (!asignado); j++) {
			//Comprobar que son de diferente pais y que no es el equipo que tuviste en tu grupo

			if (asig[orden[j]] == 0 && Bombo[4].getEquipo(i * 2 + 1)->getPais() != Bombo[5].getEquipo(orden[j] * 2)->getPais()) {

				Bombo[5].setEquipo(Bombo[4].getEquipo(i * 2 + 1), orden[j] * 2 + 1);
				asignado = true;
				asig[orden[j]] = 1;
			}
		}
	}
	cout << endl;

	realizarFaseFinal(16);
}

void Almacen::realizarFaseGrupos()
{
	int i, j;
	for (i = 0; i < 6; i++) {
		cout << "JORNADA " << i + 1 << endl;
		for (j = 0; j < 8; j++)
		{
			Grupos[j].calendario(i);
		}
		//cin.ignore();
		for (j = 0; j < 8; j++)
		{
			Grupos[j].mostrarGrupo();
		}
		//cin.ignore();
	}
}

void Almacen::realizarFaseFinal(int num)
{


	int i;
	Equipo* clasi;
	Partido eliminatorio;
	cout << "\n----------------------------------" << endl;
	cout << "Emparejamientos" << endl;
	cout << "----------------------------------\n" << endl;;

	switch (num) {
	case 2:
		cout << "FINAL\n";
		break;
	case 4:
		cout << "SEMIFINAL\n";
		break;
	case 8:
		cout << "CUARTOS DE FINAL\n";
		break;
	case 16:
		cout << "OCTAVOS DE FINAL\n";
		break;
	default:
		cout << "ELIMINATORIAS\n";
		break;
	}
	for (i = 0; i < num; i = i + 2) {
		cout << Bombo[5].getEquipo(i)->getNombre() << "\t-\t" << Bombo[5].getEquipo(i + 1)->getNombre() << endl;
	}

	for (i = 0; i < num; i = i + 2) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		Bombo[5].setEquipo(eliminatorio.partidoEliminatoria(Bombo[5].getEquipo(i), Bombo[5].getEquipo(i + 1)), i / 2);
	}
	if (num > 2) {
		cin.ignore();
		cout << endl;
		realizarFaseFinal(num / 2);
	}
	else {
		cout << "EL CAMPEON ES: " << Bombo[5].getEquipo(0)->getNombre() << endl;
	}
}

Almacen::~Almacen()
{
}

Equipo Almacen::getEquipo(int posicion)
{
	return Clubes[posicion];
}