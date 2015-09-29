#include "indexador.h"
#include "directorio.h"

#include <iostream>
using namespace std;

//TODO: Unificar file y file2, y Constantes y Constants
//TODO: Optimizar (comprobando haciendo profiling) con el uso de inline, por ej.
//TODO: Aprovechar que el trie puede generar particiones ordenadas para evitar el 
//	costo innecesario del replacement selection
//TODO: Escribir la cantidad de documentos al principio del archivo de normas (un unsigned int)

unsigned long bytesDelHeap = 0; //TODO

int main(int argc, char *argv[]){
	Indexador indexador;
	Directorio d;
	d.Validar_Parametros(argc,argv);
	// Esta llamada cubre la fase 1 de la indexación : Genera el 
	// archivo auxiliar 1.
	d.Recorrer(argv[1],indexador);
	cout << "FIN DE LA FASE 1: BYTES DEL HEAP OCUPADOS: " << bytesDelHeap << endl; //TODO
	getchar(); //TODO
	// A continuación, la fase 2 : Generación del archivo de léxico
	// intermedio y archivo auxiliar 2.
	indexador.indexarFase2();
	cout << "BYTES DEL HEAP OCUPADOS" << bytesDelHeap << endl; //TODO
	getchar(); //TODO
	// Cálculo y almacenamiento de las normas de los documentos, 
	// generación del archivo de punteros y compresión del léxico
	// con Front Coding Parcial
	indexador.indexarFase3();
	cout << "BYTES DEL HEAP OCUPADOS" << bytesDelHeap << endl; //TODO
	getchar(); //TODO
	return 0;
}
