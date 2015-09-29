#ifndef _FILE_2_H_
#define _FILE_2_H_
//
// C++ Interface: File
//
// Description: 
//			Clase de manejo de archivos en disco
//
// Author: Seba <sebasg@gmail.com>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>


class File2 

{
	
private:
	char directory[256];
	std::string nombreArchivo;
	std::fstream archivo;
	long int current;
//	long int processFile();
//	void processDirectory();
public:    
	File2(std::string nombre);
//	File(char*);	
	~File2();
	void escribir(void*,int);
	void leer(void*,int);
//	long int getPosicion();
	void setPosicion(long int);
//	bool final();
//	long int getFinal();
//	bool existe();
//	void eraseFile();
	
};

#endif


