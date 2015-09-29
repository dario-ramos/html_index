#ifndef FILE_H
#define FILE_H

#include "constantes.h"
//TODO: SACAR
#include "registros.h"

#include <string>
#include <fstream>
//TODO: SACAR
#include <iostream>
using namespace std;

// Representa un archivo con registros estructurados de longitud fija
class File{
public: //TODO
	fstream archivo;
	string nomArch;
	int modo;
	long int offsetAlFinal; //Para ahorrarse un seek
public:
	File(string s, const int m);
	~File();
	bool escribir(const void* reg, int tamEnBytes);
	void cambiarModo(const int m);
	bool leer(void* reg, int tamEnBytes);
	bool leerProxCaracter(char& c);
	long int getFinal();
	bool esFin();
	void setPosicionLect(long int pos);
	// Borra físicamente el archivo (libera espacio en disco)
	void eliminar();
	// TODO: SACAR TODOS LOS MÉTODOS QUE SIGUEN
	void mostrarAux1();
	void mostrarStream();
	void mostrarAux2();
	//Esto es para el secuencial
	bool lectura_secuencial(void *reg);
	bool estado_archivo();
};

#endif
