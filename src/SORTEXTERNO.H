#ifndef SORT_EXTERNO_H
#define SORT_EXTERNO_H

#define MAX_ELEMENT 500
#define MAX_NTERM 10000
#define MAX_NDOC 10000

#include "file.h"
#include "registros.h"

#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class SortExterno{

private:
	vector<RegPart> vecPart;
	File archAux2;
	RegAux2 regAux2;
	//File archAux2Ord;
	//RegAux2 regAux2Ord;
	RegBuff buff[MAX_ELEMENT];
	int cantRegs;

	void Descongelar();
	bool VectorVacio();		
	void BuscarMenor(int& pos);	
	string GenerarNomParticion(int nroPart);
	bool TodosCongelados();
	void MergeDeA3(int,int,int,int);
	void MergeDeA2(int,int,int);
	bool SonIguales(RegAux2,RegAux2);
	static bool MyDataSortPredicate(const RegPart&,const RegPart&);
	void EliminarParticiones(int Part);
	void Merge(int);
	int Sort();
public:
	SortExterno();
	void RealizarMergeSort();
	~SortExterno(); //TODO
};

#endif

