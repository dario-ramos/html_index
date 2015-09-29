#ifndef TRIE_H
#define TRIE_H

#include <deque>
#include <vector>
#include <string>
#include <sstream> //TODO
#include <iostream> //TODO
using namespace std;

#include "lexico.h"
#include "file.h"
#include "registros.h"

class Lexico;

class NodoTrie{
friend class Trie;
	char caracter;
	deque<NodoTrie*> pHijos; //Punteros a los hijos
	unsigned int ftd;
	long int offset;
public:
	NodoTrie(char c);
	~NodoTrie();
	char getCaracter();
};

class Trie{
	deque<NodoTrie*> pHijosDeLaRaiz;
public:
	Trie();
	~Trie();
	bool vacio();
	// Devuelve false sii nuevoTerm ya fue insertado
	bool insertarTermino(const string& nuevoTerm, long int offset);
	void mostrar();
	// Compacta el trie, generando el archivo de léxico TODO
	void podarYGenerarLexico(Lexico& lexico);
	// Pone todas las ftds en cero
	void ponerFtdsEnCero();
	bool pertenece(const string& s);
	void volcarAAux1(unsigned int numDoc, File& aux1);
	// PRE: Debe haberse llamado previamente a podarYGenerarLexico
	unsigned int getNumTerm(const string& s);
	// PRE: Debe haberse llamado previamente a podarYGenerarLexico
	long int getOffsetAlLexico(const string& s);
	
private:
	static int busqBinEnHijos(deque<NodoTrie*> d, char c, unsigned int posIni, unsigned int posFin);
	// Devuelve NULL si no agregó
	NodoTrie* insertarNodo(deque<NodoTrie*>& hijos, char c, int& pos, long int offset);
	// Cuelga lo que queda del término como una secuencia lineal de nodos
	void colgar(NodoTrie* padre, string nuevoTerm, unsigned int posIni, long int offset);
	void mostrarRec(NodoTrie*& actual);
	bool insertarTerminoRec(deque<NodoTrie*>& hijosActual, const string& term, int& posTerm,
				long int offset);
	void podarRec(NodoTrie*& actual, vector<NodoTrie*>& pila, Lexico& lexico, unsigned int& numTerm, long int& offset);
	void ponerFtdsEnCeroRec(NodoTrie*& actual);
	bool perteneceRec(const deque<NodoTrie*>& hijosActual, const string& s, unsigned int& nivel);
	//void generarLexicoRec(NodoTrie*& actual, const deque<NodoTrie*>& hijosActual,Lexico &lex, unsigned int& numTerm);
	void volcarAAux1Rec(unsigned int numDoc, NodoTrie*& actual, File& aux1, unsigned int& ftd, long int& offset);
	void borrarRec(NodoTrie*& actual);
	long int getOffsetAlLexicoRec(const deque<NodoTrie*>& hijosActual, const string& s, unsigned int& nivel,
				      long int& offset);
};

#endif

