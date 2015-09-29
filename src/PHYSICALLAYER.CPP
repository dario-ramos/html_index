#include "physicallayer.h"
extern unsigned long bytesDelHeap; //TODO
/*
*  C Implementation: PhysicalLayer
*
* Description: Implementacion de la capa fisica
*
*
* Author: Seba <sebasg@gmail.com>, (C) 2006
*
* Copyright: See COPYING file that comes with this distribution
*
*/
//Si bien esta bien tener variables staticas no me afectaria no tenerlas por el singleton (siempre la misma instancia)

PhysicalLayer* PhysicalLayer::FCM_instance=NULL;
Constants* PhysicalLayer::constantes=NULL;






PhysicalLayer::PhysicalLayer(unsigned short int instanceType)
{
	this->constantes = Constants::GetInstance();
	this->_instanceType=instanceType;
	switch(instanceType)
	{
		case 1 : //FCM			
			_posLexico=0;
			_posPointers=0;
			this->_lexicoFile=new File2(constantes->FCM_LexicoFileName); bytesDelHeap += sizeof(*(this->_lexicoFile)); //TODO
			this->_pointersFile=new File2(constantes->FCM_PunterosFileName); bytesDelHeap += sizeof(*(this->_pointersFile)); //TODO
			break;
	}
}

PhysicalLayer::~PhysicalLayer()
{
	switch(_instanceType)
	{
		case 1:			
			delete _lexicoFile; bytesDelHeap -= sizeof(*_lexicoFile); //TODO
			delete _pointersFile; bytesDelHeap -= sizeof(*_pointersFile); //TODO
			break;
	}
	cout << "BYTES AL DESTR PHYSLAY " << bytesDelHeap << endl; //TODO
}

PhysicalLayer* PhysicalLayer::GetInstance(unsigned short int  instanceType)
{
	switch(instanceType)
	{
		case 1 : //FMC	
			if(FCM_instance == NULL)
			{
				PhysicalLayer::FCM_instance = new PhysicalLayer(instanceType); bytesDelHeap += sizeof(*PhysicalLayer::FCM_instance); //TODO
			}
			return PhysicalLayer::FCM_instance;
	}
}

void PhysicalLayer::Destroy(unsigned short int instanceType)
{
	switch(instanceType)
	{
		case 1: //FCM	
			delete PhysicalLayer::FCM_instance; bytesDelHeap -= sizeof(*PhysicalLayer::FCM_instance); //TODO
			break;
	}
}

bool PhysicalLayer::FCM_Create()
{
// Crea loas archivos necesarios para FCM
//El de lexico y el de punteros
	//File* f_lexico=new File(constantes->FCM_LexicoFileName);
	//delete(f_lexico);
	//File* f_punteros=new File(constantes->FCM_PunterosFileName);
	//delete(f_punteros);
	//return true;
}


bool PhysicalLayer::FCM_GuardarPalabra(FCM_Record* fcm_record)
{

	char* current;
	char* pPointer;
	unsigned int recordSize;

	//Primero Guardamos las letras nuevas
	recordSize=fcm_record->getSizeLetrasNuevas();
	current=new char[recordSize]; bytesDelHeap += sizeof(*current);
	current=fcm_record->getParsedLetrasNuevas(current);

	//escribo
	_lexicoFile->setPosicion(_posLexico); //Me posiciono al final
	_lexicoFile->escribir((void*)current,recordSize);
	//_lexicoFile->escribir((void*)"caballo",8);

	_posLexico+=recordSize;
	
	//Guardo el puntero de frontCoding
	recordSize=fcm_record->getSizePointer();
	

	pPointer=new char[recordSize]; bytesDelHeap += sizeof(*pPointer);
	pPointer=fcm_record->getParsedPointer(pPointer);	

	//escribo
	_pointersFile->setPosicion(_posPointers);
	_pointersFile->escribir((void*)pPointer,recordSize);
	_posPointers+=recordSize;
	delete current; bytesDelHeap -= sizeof(*current); //LEAK
	delete pPointer; bytesDelHeap -= sizeof(*current); //LEAK
}

FCM_Record* PhysicalLayer::FCM_LeerPalabra(long int wordPos,FCM_Record* toReturn)
{

	char* current;
	unsigned int recordSize=0;
	
	//Obtengo el size del puntero
	recordSize=toReturn->getSizePointer();
	current=new char[recordSize]; bytesDelHeap += sizeof(*current); //TODO
	_posPointers =recordSize*wordPos;
	//Me posiciono
	_pointersFile->setPosicion(_posPointers);
	//Leo
	_pointersFile->leer((void*)current,recordSize);
	toReturn->parseOutPointer(current);

	//Posiciono en el lexico si es la primer lectrura
	if(_posPointers==0)
	{
		_posLexico=0;
	}
	delete current; bytesDelHeap -= sizeof(*current); //TODO

	current=new char[toReturn->getCantLetrasNuevas()]; bytesDelHeap += sizeof(*current);
	_lexicoFile->leer(current,toReturn->getCantLetrasNuevas() );
	toReturn->setLetrasNuevas(current);
	

	delete current; bytesDelHeap += sizeof(*current); //TODO
	return toReturn;	
		
}



