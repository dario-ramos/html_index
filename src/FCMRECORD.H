#ifndef FCM_RECORD_H_
#define FCM_RECORD_H_

//
// C++ Interface: FCMRecord
//
// Description:  En este objeto se va a guardar la combinacion de registros para componer y descomponer el Front Coding
//		      CantLetras palabra anteriro, Cant Letras Nuevas, Puntero 	
//
// Author: Seba <sebasg@gmail.com>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
//Una Best Practice seria implementar setters y getters
#include <string>
#include <iostream>
using namespace std;

class FCM_Record
{
	public:
		FCM_Record();
		
		FCM_Record(unsigned int cantLetrasAnteriores, unsigned int cantLetrasNuevas,std:: string letrasNuevas, long int puntero);
		
		//Propiedades
		//Cant Letras Anteriores
		unsigned int getCantLetrasAnteriores();
		void setCantLetrasAnteriores(unsigned int valor);

		//Cant Letras Nuevas
		unsigned int getCantLetrasNuevas();
		void setCantLetrasNuevas(unsigned int valor);

		//Puntero
		long int getPuntero();
		void setPuntero(long int valor);

		//Letras Nuevas
		string getLetrasNuevas();
		void setLetrasNuevas(string valor);

		//Palabra Completa
		string getPalabraCompleta();
		void setPalabraCompleta(string valor);
		


		unsigned int getSizeLetrasNuevas();
		unsigned int getSizePointer();
		
		char* getParsedLetrasNuevas(char* toReturn);
		char* getParsedPointer(char* record);

		void parseOutPointer(char* record);
		~FCM_Record(); //TODO	

	private:
		unsigned int _cantLetrasAnteriores;
		unsigned int _cantLetrasNuevas;
		long int _puntero;
		string _letrasNuevas;
		string _palabraCompleta;
};

#endif


