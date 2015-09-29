#include "frontcodingmanager.h"

extern unsigned long bytesDelHeap; //TODO

//
// C++ Implementation: FrontCodingManager
//
// Description: 
//
//
// Author: Sebastian Gnagnarella <sebasg@gmail.com>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//

FrontCodingManager* FrontCodingManager::instance=NULL;


FrontCodingManager::FrontCodingManager()
{
	this->constantes = Constants::GetInstance();
	this->phy=PhysicalLayer::GetInstance(1);
	this->palabrasProcesadas=0;
	this->palabraAnterior="";

}

FrontCodingManager::~FrontCodingManager()
{
	Constants::destroy(); // LEAK
	bytesDelHeap -= sizeof(*constantes); //TODO
	PhysicalLayer::Destroy(1);
}


FrontCodingManager* FrontCodingManager::getInstance()
{
	if(instance == NULL)
	{
		instance = new FrontCodingManager(); bytesDelHeap += sizeof(*instance); //TODO
	}
	return instance;
}

void FrontCodingManager::destroy() //LEAK (CORREGIDA)
{
	delete instance; bytesDelHeap -= sizeof(*instance); //TODO
}

void FrontCodingManager::procesarPalabra(string palabra,long int puntero)
{

	FCM_Record* tempFcm_Record=new FCM_Record(); bytesDelHeap += sizeof(*tempFcm_Record); //TODO
	
	//Es momento de resetear el frontCoding
	if (palabrasProcesadas==constantes->FCM_PalabrasPrevioReseteo)
	{
		palabraAnterior="";
	}

	//Poner una funcion que pase palabra a minusculas
	if (palabraAnterior=="")
	{
		tempFcm_Record->setLetrasNuevas(palabra);
		tempFcm_Record->setCantLetrasAnteriores(0);
		tempFcm_Record->setCantLetrasNuevas(palabra.length());
	}
	else
	{
		compararPalabras(palabraAnterior,palabra,tempFcm_Record);
	}
	palabraAnterior=palabra;
	tempFcm_Record->setPuntero(puntero);
	
	//Grabo en disco
	this->phy->FCM_GuardarPalabra(tempFcm_Record);
	delete tempFcm_Record; bytesDelHeap -= sizeof(*tempFcm_Record);//TODO //LEAK CORREGIDA
}

void FrontCodingManager::compararPalabras(string palabraAnterior, string palabraNueva,FCM_Record*  fcm_record)  //, unsigned int& cantLetrasAnterior,unsigned int& cantLetrasNuevas,string& strLetrasNuevas)
{
	unsigned int posLetra=0;
	while ((posLetra<palabraAnterior.length() ) && (palabraAnterior[posLetra]==palabraNueva[posLetra]))  
	{
		posLetra++;
	}
	fcm_record->setCantLetrasNuevas(palabraNueva.length()-posLetra);
	fcm_record->setCantLetrasAnteriores(posLetra);
	fcm_record->setLetrasNuevas(palabraNueva.substr(posLetra,fcm_record->getCantLetrasNuevas()));
	//std::cout<<fcm_record->GetLetrasNuevas();
	
//	cantLetrasNuevas=palabraNueva.length()-posLetra;
//	cantLetrasAnterior =posLetra;
//	strLetrasNuevas=palabraNueva.substr(posLetra,cantLetrasNuevas);
}

FCM_Record* FrontCodingManager::obtenerSigPalabra(FCM_Record* toReturn)
{
	string tempWord; 
	char* tempChar;
	//FCM_Record* fcm_record = new FCM_Record();
	toReturn=phy->FCM_LeerPalabra(palabrasProcesadas,toReturn);
	tempChar= new char[toReturn->getCantLetrasNuevas()]; bytesDelHeap += sizeof(*tempChar); //TODO
	tempWord=palabraAnterior.substr(0,toReturn->getCantLetrasAnteriores())  +toReturn->getLetrasNuevas();
	palabrasProcesadas++;
	palabraAnterior=tempWord;
	toReturn->setPalabraCompleta(tempWord);
	delete[] tempChar; bytesDelHeap -= sizeof(*tempChar); //TODO //LEAK (CORREGIDA)
	return toReturn;
}


//Verificar si esxiste la palabra
bool FrontCodingManager::verificarPalabra(string palabra)
{
	return true; //por ahora es un dummy
}


