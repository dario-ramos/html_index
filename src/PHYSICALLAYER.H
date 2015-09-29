#ifndef PHYSICALLAYER_H_
#define PHYSICALLAYER_H_
//
// C++ Interface: PhysicalLayer
//
// Description: Capa FISICA
//
//
// Author: Seba <sebasg@gmail.com>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include <string>
#include <fstream>

#include "constants.h"
#include "fcmrecord.h"
#include "file2.h"

class PhysicalLayer 
{
	public:
		//SingleTon
		static PhysicalLayer* GetInstance(unsigned short int instanceType);
		static void Destroy(unsigned short int instanceType);

		//Front Coding Manager
		bool FCM_Create();
		bool FCM_GuardarPalabra(FCM_Record* fcm_record);
		//void FCM_Delete();
		FCM_Record* FCM_LeerPalabra(long int wordPos,FCM_Record* toReturn);

	private:
		//Constantes
		static Constants* constantes;	
		//SingleTon	
		static PhysicalLayer* FCM_instance; //El singleton con un parametro va a saber que instance devolverme esta es la de front coding manager
		static PhysicalLayer * instance;	
		unsigned short int _instanceType;
		
		PhysicalLayer(unsigned short int instanceType);
		~PhysicalLayer();
		
		//Front Conding Manager File
		long int _posLexico;
		long int _posPointers;
		File2* _lexicoFile;
		File2* _pointersFile;
};

#endif /*PHYSICALLAYER_H_*/
 


 

