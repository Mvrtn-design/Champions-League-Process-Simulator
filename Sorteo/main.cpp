#include "iostream"
#include "stdlib.h"
#include "Equipo.h"
#include "Almacen.h"
#include "fstream"

using namespace std;


/*UEFA CHAMPIONS LEAGUE
Queremos realizar el sorteo de la UEFA CHAMPIONS LEAGUE , para ello queremos incluir a 32 equipos de diferentes ligas europeas, pero con condiciones:
- No se enfrentaran entre equipos del mismo país
- De España:        4 equipos
- De Inglaterra:    4 equipos
- De Italia:        4 equipos
- De Alemania:      3 equipos
- De Francia:       3 equipos
- De Portugal:      2 equipos
- De Turquía:       2 equipos
- De Rusia:         2 equipos
- 9 del resto de Europa (Escocia,Grecia,Rumania,Paises Bajos,Hungría,Eslovaquia ...) (1 de cada país)

- El campeón de la pasada EUROPA LEAGUE (una competicion aparte pero que te asegura participar en este torneo) con su pais correspondiente (Este equipo podrá ser el mismo de los añadidos anteriormente, por lo que habrá que ver si ocupa o no una plaza de más ) de no ocupar plaza , la restante viene de Resto de Europa

- Hay que separar los equipos en 4 bombos con sus respectivas caracteristicas (Cada equipo de un bombo irá a un grupo diferente)
- En el 1º bombo los campeones de sus respectivas ligas (Las 7 ligas principales) y el ganador de la Europa League ,(si es repetido se pasa a la siguiente liga)
- En el 2º bombo 2 de España , 2 de Inglaterra , 2 de Alemania y 1 de Francia e Italia
- En el 3º bombo 2 de Italia, 1 de Alemania,España,Inglaterra,Francia,Portugal,Rusia
- En el cuarto bombo
*/

int main() {

	fstream archivo("./TextoEquipos.txt");

	Almacen sistema = Almacen();
	string word, nombre, pais, posicion,categoria;


	int i = 0;
	while (archivo >> word) {
		if (word != ",") {
			if (i % 4 == 0) {
				nombre += word;
				nombre += " ";
			}
			else if (i % 4 == 1) {
				pais += word;
				pais += " ";
			}
			else if (i % 4 == 2) {
				posicion = word;
			}
			else if (i % 4 == 3) {
				categoria = word;
				sistema.meterEquipo(nombre, pais,stoi(posicion),stoi(categoria));
				
				nombre.erase();
				pais.erase();
				posicion.erase();
				categoria.erase();
			}
		}
		else {
			i++;
			word.erase();
		}
	}
	archivo.close();
	cin.ignore();
	sistema.asignacionBombos();
	cin.ignore();
	sistema.mostrarBombos();
	cin.ignore();	
	sistema.realizarSorteo();	
	cin.ignore();
	sistema.realizarFaseGrupos();
	cin.ignore();
	sistema.realizarSorteoFaseFinal();
}