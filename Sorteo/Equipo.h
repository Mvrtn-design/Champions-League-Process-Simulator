#pragma once
#include "string"
class Equipo
{
private:
	std::string nombre;
	std::string pais;
	bool encuadrado;
	int posicionLiga;
	int victorias;
	int empates;
	int derrotas;
	int puntos;
	int goles;
	int golesEncajados;
	int categoria;
	
public:
	Equipo(std::string, std::string, int posicion, int categoria);
	Equipo();
	~Equipo();
	int getVictorias();
	int getEmpates();
	int getDerrotas();
	int getPuntos();
	int getGoles();
	int getCategoria();
	int getGolesEncajados();
	bool getEncuadrado();
	void setEncuadrado(bool opcion);
	std::string getNombre();
	std::string getPais();
	int getPosicion();
	Equipo getEquipo();
	void setPosicionLiga(int nueva);
	void addGoles(int goles);
	void addGolesEncajados(int goles);
	void addPuntos(int puntos);
	void addVictoria();
	void addEmpate();
	void addDerrota();
	void setNombre(std::string _nuevo);
	void setPais(std::string _nuevo);
};