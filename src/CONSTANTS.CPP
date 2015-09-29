
#include "constants.h"
extern unsigned long bytesDelHeap; //TODO

Constants* Constants::instance = NULL;

Constants* Constants::GetInstance() {
	if (instance == NULL)	{
		instance = new Constants(); bytesDelHeap += sizeof(*instance);
	}
	return instance;	
}

void Constants::destroy(){ // LEAK
	delete instance;
}


Constants::Constants()
{
	//Front Coding Manager
	this->FCM_LexicoFileName="FCM_Lexico.fcm";
	this->FCM_PunterosFileName="FCM_Punteros.fcm";
	this->FCM_PalabrasPrevioReseteo=5;
}


