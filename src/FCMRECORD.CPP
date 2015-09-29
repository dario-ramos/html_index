#include "fcmrecord.h"
//
// C++ Implementation: FCMRecord
//
// Description: 
//
//
// Author: Seba <sebasg@gmail.com>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include <sstream>
#include <iostream>
extern unsigned long bytesDelHeap; //TODO

FCM_Record::FCM_Record()
{
	this->_cantLetrasAnteriores=0; //Le puso NULL pero tira warning
	this->_cantLetrasNuevas=0;//Le puso NULL pero tira warning
	this->_letrasNuevas="";
	this->_puntero=0;//Le puso NULL pero tira warning
	this->_palabraCompleta="";
}

FCM_Record::~FCM_Record() { cout << "BYTES AL DESTR FCM_REC " << bytesDelHeap << endl; } //TODO

FCM_Record::FCM_Record(unsigned int cantLetrasAnteriores, unsigned int cantLetrasNuevas,std:: string letrasNuevas, long int puntero)
{
	this->_cantLetrasAnteriores=cantLetrasAnteriores;
	this->_cantLetrasNuevas=cantLetrasNuevas;
	this->_letrasNuevas=letrasNuevas;
	this->_puntero=puntero;
}

//Propiedades
//Cant Letras Anteriores
unsigned int FCM_Record::getCantLetrasAnteriores()
{
	return this-> _cantLetrasAnteriores;
}

void FCM_Record::setCantLetrasAnteriores(unsigned int valor)
{
	this->_cantLetrasAnteriores=valor;
}


//Cant Letras Nuevas
unsigned int FCM_Record::getCantLetrasNuevas()
{
	return this->_cantLetrasNuevas;
}

void FCM_Record::setCantLetrasNuevas(unsigned int valor)
{
	this->_cantLetrasNuevas=valor;
}

//Puntero
long int FCM_Record::getPuntero()
{
	return this->_puntero;
}

void FCM_Record::setPuntero(long int valor)
{
	this->_puntero=valor;
}


//Letras Nuevas
string FCM_Record::getLetrasNuevas()
{
	return this-> _letrasNuevas;
}

void FCM_Record::setLetrasNuevas(string valor)
{
	this->_letrasNuevas=valor;
}

unsigned int FCM_Record::getSizeLetrasNuevas()
{
	return _letrasNuevas.length();
}

unsigned int FCM_Record::getSizePointer()
{
	unsigned int size=0;
	size+= sizeof(int)+sizeof(int); //Marcadores de Front Coding
	size+=sizeof(long int); //puntero
	return size;
}

char* FCM_Record::getParsedPointer(char* record)
{
	char* current=record;
	
	((int*)current)[0] =_cantLetrasAnteriores;	
	current += sizeof(int);
	
	((int*)current)[0] =_cantLetrasNuevas;	
	current += sizeof(int);

	((long int*)current)[0] =_puntero;	
	current += sizeof(long int);


	return record;
}

char* FCM_Record::getParsedLetrasNuevas(char* toReturn)
{
	std::ostringstream os;
	os<<_letrasNuevas;
	return (char*)memcpy((void*)toReturn,(void*)((char*)(os.str().c_str())),_cantLetrasNuevas);


}


void FCM_Record::parseOutPointer(char* record)
{
char* tempRecord=record;

_cantLetrasAnteriores= ((int*)tempRecord)[0];
tempRecord += sizeof(int);

_cantLetrasNuevas= ((int*)tempRecord)[0];
tempRecord += sizeof(int);

_puntero=((long int*)tempRecord)[0];

}

//Palabra Completa
string FCM_Record::getPalabraCompleta()
{
	return this-> _palabraCompleta;
}

void FCM_Record::setPalabraCompleta(string valor)
{
	_palabraCompleta=valor;
}

