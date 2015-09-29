#ifndef INDEXADOR_H
#define INDEXADOR_H

#include "myparser.h"
#include "trie.h"
#include "file.h"
#include "constantes.h"
#include "sortexterno.h"
#include "norma.h"
#include "frontcodingmanager.h"

#include <string>
#include <sstream>
using namespace std;

class Indexador{
private :
	Parser_G7 p;
	unsigned int idDocActual;
	Trie* t; // Se destruye al terminar la fase 2
	File terminosParseados;
	File aux1;
	File aux2;
	Lexico lex;
	Trie* stopWords; //Se crea en el heap para destruirlo al terminar la fase 1
	FrontCodingManager* fcm;

	bool filtrarTermino(string &termino);
	void agregarRegistrosAux1();
	void GrabarArchivosdeIndexacion();
public:
	Indexador();
	~Indexador();
	
	void indexarFase1(string nomArch);
	void indexarFase2();
	void indexarFase3();
};

#endif

