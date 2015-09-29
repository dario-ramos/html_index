#ifndef NORMA_H
#define NORMA_H

#include "file.h"
#include "registros.h"

#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

class Norma{
	private:
		vector<RegVecNorma> vec;
		File aux2Ord; //TODO: Sería mejor que sean referencias o punteros a los de indexador
		File aux2;
		File archNorma;
		void LlenarVector();
		int N;  //N= cantidad de documentos totales
	public:
		void CalcularNorma();
		Norma(int N);
		~Norma(); //TODO

};

#endif



