#include "file2.h"
//
// C++ Implementation: File
//
// Description:  Implementacion de la clase de manejo de archivos en disco
//
//
// Author: Seba <sebasg@gmail.com>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
extern unsigned long bytesDelHeap; //TODO
//#include <iostream>
//#include <fstream>
//#include <string>
//#include <stdio.h>

//#include <unistd.h>
//#include <fcntl.h>

using namespace std;

File2::File2(std::string nombre)
{
	nombreArchivo = nombre;
	
	
	this->archivo.open(this->nombreArchivo.c_str(),ios::in | ios::out | ios::binary);
	
	// si no lo pudo abrir crea el archivo
	
	if(!this->archivo.is_open())
	{
		// limpio los flags
		this->archivo.clear();
		
		// crea el archivo abriendolo para escritura binaria
		
		this->archivo.open(this->nombreArchivo.c_str(),ios::out | ios::binary);
		this->archivo.close();
		
		// ahora lo abre para lectura / escritura binaria y lo deja listo para usar
		archivo.open(this->nombreArchivo.c_str(),ios::in |ios::out | ios::binary);
	}    
}

File2::~File2()
{
	this->archivo.close();
	// vuelvo a poner el directorio de aplicacion 
	//chdir(appDirectory);
	cout << "BYTES AL DESTR ARCH2 " << bytesDelHeap << endl; //TODO
}

void File2::escribir(void* registro,int tamanio)
{
	this->archivo.write(static_cast<char*>(registro),tamanio);   
	current+=tamanio;
}

void File2::leer(void* registro,int tamanio){
	this->archivo.read(static_cast<char*>(registro),tamanio);
	current+=tamanio;
}

void File2::setPosicion(long int posicion){
	this->archivo.seekg(posicion);
	current = posicion;
}

