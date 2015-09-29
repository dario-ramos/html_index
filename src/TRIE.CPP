#include "trie.h"

extern unsigned long bytesDelHeap; //TODO

NodoTrie::NodoTrie(char c) : caracter(c), pHijos(), ftd(0), offset(0) {
}
NodoTrie::~NodoTrie() { pHijos.clear(); }
Trie::Trie() : pHijosDeLaRaiz() {
}
Trie::~Trie(){
	for(unsigned int i=0; i<pHijosDeLaRaiz.size(); i++)
		borrarRec(pHijosDeLaRaiz[i]);
	pHijosDeLaRaiz.clear();
	cout << "BYTES LUEGO DE DESTR TRIE: " << bytesDelHeap << endl; //TODO
}	
bool Trie::vacio(){
	return pHijosDeLaRaiz.empty();
}
int Trie::busqBinEnHijos(deque<NodoTrie*> d, char c, unsigned int posIni, unsigned int posFin){
	unsigned int m = (posIni+posFin) / 2;
	if (m == posIni || m == posFin) return m;
	if (d[m]->caracter == c) return m;
	if (d[m]->caracter < c) return busqBinEnHijos(d, c, m, posFin);
	else return busqBinEnHijos(d, c, posIni, m);
	
}
NodoTrie* Trie::insertarNodo(deque<NodoTrie*>& hijos, char c, int& pos, long int offset){
	int i = 0;
	bool hayNull = false;
	if (hijos.empty() || (hijos.size() == 1 && hijos[0] == NULL)){
		if (hijos.empty()) pos = 0;
		else pos = 1;
		NodoTrie* pNuevoNodo = new NodoTrie(c); bytesDelHeap += sizeof(*pNuevoNodo); //TODO
		pNuevoNodo->offset = offset;
		hijos.push_back(pNuevoNodo);
		return pNuevoNodo;
	}
	else{
		if (hijos[0] == NULL){
			hayNull = true;
			i = busqBinEnHijos(hijos, c, 1, hijos.size());
		}
		else i = busqBinEnHijos(hijos, c, 0, hijos.size());
	}
	if (hijos[i]->caracter == c) { pos = i; return NULL;}
	NodoTrie* pNuevoNodo = new NodoTrie(c); bytesDelHeap += sizeof(*pNuevoNodo); //TODO
	pNuevoNodo->offset = offset;
	if(i == 0 && !hayNull)
		if (c < hijos[0]->caracter){
			hijos.push_front(pNuevoNodo);
			pos = 0;
			return pNuevoNodo;
		}else{
			hijos.insert(++hijos.begin(), pNuevoNodo);
			pos = 1;
			return pNuevoNodo;
		}
	else if (i == 1 && hayNull)
		if (c < hijos[1]->caracter){
			hijos.insert(++hijos.begin(), pNuevoNodo);
			pos = 1;
			return pNuevoNodo;
		}else{
			hijos.insert(++(++hijos.begin()), pNuevoNodo);
			pos = 2;
			return pNuevoNodo;
		}
	else if (i == hijos.size()-1){
		hijos.push_back(pNuevoNodo);
		pos = hijos.size()-1;
		return pNuevoNodo;
	}
	else{
		deque<NodoTrie*>::iterator it;
		if(i < (hijos.size()/2)){
			if (hijos[0] == NULL) it = ++hijos.begin(); //PARCHE
			else it = hijos.begin(); //PARCHE
			for(; c > (*it)->caracter; it++);
			hijos.insert(it, pNuevoNodo);
		}else{
			for(it = --hijos.end(); c < (*it)->caracter; it--);
			hijos.insert(++it, pNuevoNodo);
		}
		pos = i+1;
		return pNuevoNodo;
	}
}
void Trie::colgar(NodoTrie* padre, string nuevoTerm, unsigned int posIni, long int offset){
	NodoTrie* p = padre; NodoTrie* pNuevoNodo; 
	for(unsigned int i = posIni; i<nuevoTerm.size(); i++){
		pNuevoNodo = new NodoTrie(nuevoTerm[i]); bytesDelHeap += sizeof(*pNuevoNodo); //TODO
		p->pHijos.push_back(pNuevoNodo);
		p = pNuevoNodo;
	}
	// Al último hay que incrementarle la ftd y asignarle offset
	++(pNuevoNodo->ftd);
	pNuevoNodo->offset = offset;
	// Marca de fin de término: Para los casos en que un término completo es
	// prefijo de otro (ej: casa y casado). NULL siempre va al principio 
	(pNuevoNodo->pHijos).push_front(NULL);
}
bool Trie::insertarTerminoRec(deque<NodoTrie*>& hijosActual, const string& term, int& posTerm,
			      long int offset){
	
	int pos = 0;
	NodoTrie* pNuevoNodo = insertarNodo(hijosActual, term[posTerm], pos, offset);
	posTerm++;
	if (posTerm == term.size() ) {
		if (pNuevoNodo != NULL){
			pNuevoNodo->pHijos.push_front(NULL);
			++(pNuevoNodo->ftd);
			hijosActual[pos]->offset = offset;
			return true;
		}
		else if (hijosActual.size() == 1 && hijosActual[0] == NULL || 
		    	hijosActual[pos]->pHijos[0] == NULL){ 
			++(hijosActual[pos]->ftd);
			return false;
		     }else{
			hijosActual[pos]->pHijos.push_front(NULL);
			++(hijosActual[pos]->ftd);
			hijosActual[pos]->offset = offset;
			return true;
		     }
	}
	else 	if (pNuevoNodo == NULL) return insertarTerminoRec(hijosActual[pos]->pHijos, term, posTerm, offset);
		else{
			colgar(hijosActual[pos], term, posTerm, offset);
			return true;
		}
}
bool Trie::insertarTermino(const string& nuevoTerm, long int offset){
	int posTerm = 0;	
	return insertarTerminoRec(pHijosDeLaRaiz, nuevoTerm, posTerm, offset);
}
void Trie::mostrarRec(NodoTrie*& actual){ //TODO:Sacar
	if(actual != NULL){
		cout << actual->caracter << " con ftd " << actual->ftd << " y offset " << actual->offset << endl;
		for(unsigned int i = 0; i<(actual->pHijos).size(); i++)
			mostrarRec(actual->pHijos[i]);
	}else{
		cout << "NULL" << endl;
	}
}
void Trie::mostrar(){ //TODO:Sacar
	for(unsigned int i = 0; i<pHijosDeLaRaiz.size(); i++)
		mostrarRec(pHijosDeLaRaiz[i]);
}
void Trie::podarRec(NodoTrie*& actual, vector<NodoTrie*>& pila, Lexico& lexico, unsigned int& numTerm, 
		    long int& offset){
	if(actual != NULL){
		pila.push_back(actual);
		for(unsigned int i = 0; i<(actual->pHijos).size(); i++)
			podarRec(actual->pHijos[i], pila, lexico, numTerm, offset);
		// Si el actual no tiene hijos ni hermanos, hay que borrarlo
		// y "subir" los datos a su padre.
		if (actual->pHijos.size() ==1 && actual->pHijos[0] == NULL)
		   if(pila.size() >= 2)
		      if (pila[pila.size()-2]->pHijos.size() == 1){
		    	// Subo ftd y offset
			pila[pila.size()-2]->ftd = actual->ftd;
			pila[pila.size()-2]->offset = actual->offset;
			// Borro
			pila[pila.size()-2]->pHijos.clear();
			pila[pila.size()-2]->pHijos.push_front(NULL);
			delete actual; bytesDelHeap -= sizeof(*actual); //TODO
			actual = NULL; //CAMBIO
		      }
		pila.pop_back();
	}else{
		// Una vez que llego a una hoja, debo volcar el término con su numTerm
		// al léxico.  Además, el offset debe pasar a ser al léxico.
		pila[pila.size()-1]->offset = offset;
		lexico.agregarTerm(pila, numTerm);
		offset += (2*sizeof(unsigned int)+pila.size());
		numTerm++;
	}
}
void Trie::podarYGenerarLexico(Lexico& lexico){
	vector<NodoTrie*> pila;
	pila.clear();
	unsigned int numTerm = 1; long int offset = 0;
	for(unsigned int i = 0; i<pHijosDeLaRaiz.size(); i++){
		podarRec(pHijosDeLaRaiz[i], pila, lexico, numTerm, offset);
	}
}
char NodoTrie::getCaracter(){
	return caracter;
}
void Trie::ponerFtdsEnCero(){
	for(unsigned int i = 0; i<pHijosDeLaRaiz.size(); i++)
		ponerFtdsEnCeroRec(pHijosDeLaRaiz[i]);
}
void Trie::ponerFtdsEnCeroRec(NodoTrie*& actual){
	if(actual != NULL){
		actual->ftd = 0;
		for(unsigned int i = 0; i<(actual->pHijos).size(); i++)
			ponerFtdsEnCeroRec(actual->pHijos[i]);
	}
}
bool Trie::pertenece(const string& s){
	unsigned int nivel = 0;
	return perteneceRec(pHijosDeLaRaiz, s, nivel);
}
bool Trie::perteneceRec(const deque<NodoTrie*>& hijosActual, const string& s, unsigned int& nivel){
	// Si no hay hijos o sólo hay un NULL, pueden ocurrir dos cosas: O se llegó al final del
	// string (caso en que nivel == s.size()-1), o bien no se encontró s.
	if (hijosActual.empty() || (hijosActual.size() == 1 && hijosActual[0] == NULL)){ 
		if (nivel == s.size()) return true;
		else return false;
	}
	// En otros casos debo buscar
	unsigned int i;
	if (hijosActual[0] != NULL) i = busqBinEnHijos(hijosActual, s[nivel], 0, hijosActual.size());
	else i = busqBinEnHijos(hijosActual, s[nivel], 1, hijosActual.size());
	// Si está, avanzo al siguiente nivel. Si no, devuelvo false.
	if (hijosActual[i]->caracter == s[nivel]){
		++nivel;
		if (nivel == s.size()){
			if (hijosActual[i]->pHijos[0] == NULL) return true;
			else return false;
		}else return perteneceRec(hijosActual[i]->pHijos, s, nivel);
		
	}
	else return false;
}
void Trie::volcarAAux1(unsigned int numDoc, File& aux1){
	unsigned int ftd = 0;
	long int offset = 0;
	string pila; pila.clear();
	for(unsigned int i = 0; i<pHijosDeLaRaiz.size(); i++)
		volcarAAux1Rec(numDoc, pHijosDeLaRaiz[i], aux1, ftd, offset);
}
void Trie::volcarAAux1Rec(unsigned int numDoc, NodoTrie*& actual, File& aux1,
			  unsigned int& ftd, long int& offset){
	if(actual != NULL){
		ftd = actual->ftd;
		offset = actual->offset;
		for(unsigned int i = 0; i<(actual->pHijos).size(); i++)
			volcarAAux1Rec(numDoc, actual->pHijos[i], aux1, ftd, offset);
	}else{
		// Una vez que llego a una hoja, debo volcar: numDoc ftd offset
		// sólo si ftd es mayor a cero
		if (ftd != 0){
			RegAux1 reg;
			reg.nroDoc = numDoc;
			reg.ftd = ftd;
			reg.offset = offset;
			aux1.escribir(&reg, sizeof(reg));
		}
	}
}
void Trie::borrarRec(NodoTrie*& actual){
	if(actual != NULL){
		for(unsigned int i = 0; i<(actual->pHijos).size(); i++)
			borrarRec(actual->pHijos[i]);
		delete actual; bytesDelHeap -= sizeof(*actual); //TODO
		actual = NULL; //TODO
	}
}
long int Trie::getOffsetAlLexico(const string& s){
	unsigned int nivel = 0;
	long int offset = 0;
	return getOffsetAlLexicoRec(pHijosDeLaRaiz, s, nivel, offset);
}
long int Trie::getOffsetAlLexicoRec(const deque<NodoTrie*>& hijosActual, const string& s, unsigned int& nivel,
				    long int& offset){
	// Al llegar a una hoja, devuelvo el offset
	if (hijosActual.empty() || (hijosActual.size() == 1 && hijosActual[0] == NULL))
		return offset;
	// En otros casos debo buscar
	unsigned int i;
	if (hijosActual[0] != NULL) i = busqBinEnHijos(hijosActual, s[nivel], 0, hijosActual.size());
	else i = busqBinEnHijos(hijosActual, s[nivel], 1, hijosActual.size());
	// Si está, avanzo al siguiente nivel. Si no, sé que no está.
	if (hijosActual[i]->caracter == s[nivel]){
		offset = hijosActual[i]->offset;
		++nivel;
		if (nivel == s.size()) return offset;
		else return getOffsetAlLexicoRec(hijosActual[i]->pHijos, s, nivel, offset);
	}
	else return -1;
}
