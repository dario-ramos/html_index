#ifndef LEXICO_H
#define LEXICO_H

#include "file.h"
#include "trie.h"
#include "constantes.h"

#include <sstream>
using namespace std;

class NodoTrie;
class Trie;

class Lexico{
public: //TODO: "Reprivatizar"
	File archLexico;
public:
	Lexico();
	~Lexico();
	void agregarTerm(const vector<NodoTrie*>& v, unsigned int numTerm);
};

#endif

