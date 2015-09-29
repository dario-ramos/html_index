#ifndef DIRECTORIO_H
#define DIRECTORIO_H

#define MAX_DIR    400   //Cantidad maxima de Caracteres en un path
#define ES_DIRECTORIO 1
#define NO_ES_DIRECTORIO 0
#define DIRECTORIO_ERROR -1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "indexador.h"


class Directorio{
protected:
	int es_directorio(char *name);
	DIR *Abrir_Directorio(char *direc);
	void Leer_Directorio(char *directorio_actual, DIR *dirp, Indexador &index);

public : 
	void Validar_Parametros(int cant_arg, char *arg[]);
	void Recorrer (char *direc, Indexador &index);
	~Directorio(); //TODO
};

#endif	

