#ifndef FRONTCODINGMANAGER_H_
#define FRONTCODINGMANAGER_H_

//
// C++ Interface: Front Coding Manager
//
// Description: 
// Manejador de Front Coding
//
// Author: Sebastian Gnagnarella <sebasg@gmail.com>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "fcmrecord.h"
#include "file2.h"
#include "physicallayer.h"
#include "constants.h"

#include <iostream>

class FrontCodingManager {
	public:
		~FrontCodingManager();
		
		//SingleTon
		static FrontCodingManager* getInstance();
		static void destroy(); //LEAK (CORREGIDA)
		//Funciones
		void procesarPalabra(string palabra,long int puntero);
		
		FCM_Record* obtenerSigPalabra(FCM_Record* toReturn);
		
		//Verificar Si Existe Palabra
		bool verificarPalabra(string palabra);
	private:
		//Constantes
		Constants* constantes;	
		//SingleTon	
		static FrontCodingManager* instance;
        	FrontCodingManager();

		PhysicalLayer* phy;	
		int palabrasProcesadas;
		string palabraAnterior;
		void compararPalabras(string palabraAnterior, string palabraNueva,FCM_Record* fcm_record);

};

#endif /*FRONTCODINGMANAGER_H_*/

