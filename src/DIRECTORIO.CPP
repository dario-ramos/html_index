#include "directorio.h"
extern unsigned long bytesDelHeap; //TODO
int Directorio::es_directorio(char *name){
	struct stat stbuf;
	
	if (stat(name,&stbuf) == -1){
		printf("No es posible abrir: %s\n",name);
		return(DIRECTORIO_ERROR);//Error en el archivo
	}
	else{
		if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
			return(ES_DIRECTORIO); //Es un Directorio
		else
			return(NO_ES_DIRECTORIO); //No es un directorio
	}
}
Directorio::~Directorio() { cout << "BYTES AL DESTR DIR " << bytesDelHeap << endl; } //TODO
DIR* Directorio::Abrir_Directorio(char *direc){
	static DIR *dirp;
	
	if ((dirp = opendir(direc)) == NULL){
		printf("No se puede abrir el directorio %s.\n",direc);
		exit(1);
	}
	/*printf("Aqui");
	getchar();*/
	return(dirp);
} 
void Directorio::Leer_Directorio(char *directorio_actual, DIR *dirp, Indexador &index){
	DIR *dirp2;
	struct dirent *direntp;
	char direccion[MAX_DIR];
	int estado;
	char *tipo;

	while ( (direntp = readdir( dirp )) != NULL ){
	   if ( (strcmp(direntp->d_name,".")!=0) && (strcmp(direntp->d_name,"..")!=0) ){
		if ( (strlen(direntp->d_name) + strlen(directorio_actual)) <= MAX_DIR){
		   strcpy(direccion,directorio_actual);
		   strncat(direccion,"/",1);
		   strncat(direccion,direntp->d_name,strlen(direntp->d_name));
		   estado = es_directorio(direccion); 
		   if (estado == ES_DIRECTORIO){
			dirp2 = Abrir_Directorio(direccion);
			Leer_Directorio(direccion,dirp2, index);  
		   }
		   else{
			if (estado == NO_ES_DIRECTORIO){
				tipo = rindex(direntp->d_name, '.'); /* Probar que tenga un punto */
				if (tipo == NULL) //El archivpo no es .algo
       					printf("El archivo %s no se indexa\n", direntp->d_name );
				else{
					if ( (strcmp(tipo, ".htm") == 0) || (strcmp(tipo, ".txt") == 0) ){
						printf("El archivo %s será indexado. Presione Enter.\n",
							direntp->d_name );
						//getchar(); TODO
						index.indexarFase1(direccion);
					}else printf("El archivo %s no se indexará.\n", direntp->d_name );
				}
                	}	 
			else printf("El archivo %s tiene un error y no será indexado.\n", direntp->d_name );
		    }
           	}else printf("Nombre demasiado largo.\n");
	   }
	}
	closedir(dirp);
}	
void Directorio::Validar_Parametros(int cant_arg,char *arg[]){
	if (cant_arg != 2){
		printf("Usar: %s directorio\n", arg[0]);
		exit (1);
	}
	if (!es_directorio(arg[1]) == ES_DIRECTORIO){
		printf(" %s no es un directorio\n",arg[1]);
		exit(1);
	}
}
void Directorio::Recorrer(char *direc,Indexador &Index){
	DIR *dirp;
	
	dirp = Abrir_Directorio(direc);
	Leer_Directorio(direc,dirp,Index);
}

//----------------------------------------------Fin de la Clase Directorio-----------------------
//Ejemplo
/*int main(int argc, char *argv[])
{
	Directorio D;	
	Parser_G7 p;
	D.Validar_Parametros(argc,argv);
	D.Recorrer(argv[1]);
  
}*/

