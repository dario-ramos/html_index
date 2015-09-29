#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <string>
#include <iostream>
using namespace std;

//FILE EXTENSIONS
		//static const string FI_EXTENSION = string(".Fi");
class Constants{
	
	public:
		//singleton
		static Constants* instance;
		static Constants* GetInstance();
		static void destroy(); // LEAK

		//Front Coding Manager
		string FCM_LexicoFileName;
		string FCM_PunterosFileName;
		int FCM_PalabrasPrevioReseteo;

	private:
		Constants();
};
#endif



