#include "lexico.h"
extern unsigned long bytesDelHeap; //TODO

Lexico::Lexico() : archLexico(Constantes::NOM_LEXICO, Constantes::ESCRITURA_BIN) { }

Lexico::~Lexico(){ cout << "BYTES AL DESTR LEX " << bytesDelHeap << endl; /*TODO*/ }

void Lexico::agregarTerm(const vector<NodoTrie*>& v, unsigned int numTerm){
	archLexico.escribir(&numTerm, sizeof(unsigned int));
	unsigned int longTerm = v.size();
	archLexico.escribir(&longTerm, sizeof(unsigned int));
	string s="";
	for(unsigned int i = 0; i<v.size(); i++)
		s.push_back(v[i]->getCaracter());
	char* cTerm = const_cast<char*>(s.c_str());
	archLexico.escribir(cTerm, s.size());
}

/*Trie Lexico::levantarAMemoria(){
     //TODO: Implementar
     // Recorrer el lexico e insertar en un nuevo Trie los términos
     return Trie();
}*/

