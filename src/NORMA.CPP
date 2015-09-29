#include "norma.h"
extern unsigned long bytesDelHeap; //TODO
Norma::Norma(int cant):aux2Ord(Constantes::NOM_AUX2_ORD,Constantes::LECTURA_BIN),
		       aux2(Constantes::NOM_AUX2,Constantes::LECTURA_BIN),
		       archNorma(Constantes::NORMAS,Constantes::ESCRITURA_BIN), N(cant) {
	archNorma.escribir(&N, sizeof(int));
}

//Se lee el aux2Ord para obtener el ft (llamado wt por eficiencia) de un determinado termino
//y se lo almacena en un vector
void Norma::LlenarVector(){
	int nTermAnt;	
	RegAux2 regAux2;
	RegVecNorma regVec;


	aux2Ord.leer(&regAux2,sizeof(RegAux2));	
	nTermAnt=regAux2.nroTerm;
	while (!aux2Ord.esFin()){
		regVec.wt=0;		
		while ((!aux2Ord.esFin())&&(nTermAnt==regAux2.nroTerm)){		
			regVec.wt++;
			aux2Ord.leer(&regAux2,sizeof(RegAux2));			
		}

		regVec.wt=log10(N/regVec.wt);		
		vec.push_back(regVec);		
		nTermAnt=regAux2.nroTerm;
	}
}

//Se lee el aux2, se acumula la norma de cada documento y se la guarda en archNorma
void Norma:: CalcularNorma(){
	int nDocAnt;	
	RegAux2 regAux2;
	float acumN,acum;

	LlenarVector();

	aux2.leer(&regAux2,sizeof(RegAux2));
	nDocAnt=regAux2.nroDoc;
	while (!aux2.esFin()){
		acumN=0;
		while ((!aux2.esFin())&&(nDocAnt==regAux2.nroDoc)) {
			acum = ((vec[regAux2.nroTerm-1].wt)*regAux2.ftd);
			acum *=acum;
			acumN +=acum;

			aux2.leer(&regAux2,sizeof(RegAux2));
		}

		nDocAnt=regAux2.nroDoc;
		acumN=sqrt(acumN);
		archNorma.escribir(&acumN,sizeof(float));
	}
}
		
Norma::~Norma(){ //TODO
	cout << "BYTES AL DESTR NORMA " << bytesDelHeap << endl; //TODO
}
	
/* EJEMPLO DE USO TODO: SACAR
   int main(){
	claseNorma norm(5);

	norm.CalcularNorma();
}

*/

