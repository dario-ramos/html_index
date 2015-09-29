#include "indexador.h"

extern unsigned long bytesDelHeap; //TODO

Indexador::Indexador() : idDocActual(1), t(NULL), 
			 terminosParseados(string(Constantes::NOM_STREAMTERMS), Constantes::ESCRITURA_BIN),
			 aux1(string(Constantes::NOM_AUX1),Constantes::ESCRITURA_BIN), lex(),
			 aux2(string(Constantes::NOM_AUX2),Constantes::ESCRITURA_BIN),stopWords(NULL) , fcm(NULL){
	
	stopWords = new Trie(); bytesDelHeap += sizeof(stopWords); //TODO
	t = new Trie();
	File stopW(Constantes::STOPWORDS,Constantes::LECTURA_BIN);
	char palabra[MAX_LONG_PAL];
	string stopAux;
	fcm = FrontCodingManager::getInstance();
	
	while ( (!stopW.esFin()) && (stopW.estado_archivo()) ){
	
		stopW.lectura_secuencial(palabra);
		if (strlen(palabra) > 0){ 
			stopAux.assign(palabra,strlen(palabra));
			stopAux.erase(stopAux.size()-1);
			stopWords->insertarTermino(stopAux,0);
			stopAux.erase(0,stopAux.size());
		}
	}
}

Indexador::~Indexador() { cout << "BYTES AL DESTRUIR EL INDEX " << bytesDelHeap << endl; /*TODO*/} //TODO: Asegurarse de liberar recursos

//Recibe el archivo a indexar, y extrae sus términos uno a uno. A medida que los obtiene, los
//inserta en un Trie, computando así la frecuencia de cada uno en el documento. Además, los va
//escribiendo en un stream de la forma NUMTERM1 TERM1 NUMTERM2 TERM2 ... 
void Indexador::indexarFase1(string nomArch){

	int cant = 0;
	std::string termino;
	unsigned int longTerm; //TODO
	char* cTerm;
	
	p.setear(nomArch.c_str());
	do{
		if (!termino.empty())
			termino.erase(0,termino.length());
		termino = p.Prox_Termino(); //Devuelve el proximo termino a indexar. Cuando no hay más,
					    //devuelve un string vacío
		if(!termino.empty())
		{
			if (!filtrarTermino(termino))
				if (!stopWords->pertenece(termino))
				{
					cant++;
					if(t->insertarTermino(termino, terminosParseados.getFinal()) )
					{
						//cout<< "Termino: "<< termino<<" "<<termino.size()<< endl; //TODO
						//getchar();
						longTerm = termino.size();
						terminosParseados.escribir(&longTerm, sizeof(unsigned int));
						cTerm = const_cast<char*>(termino.c_str());
						terminosParseados.escribir(cTerm, termino.size());
					}
				}
				else{
					//cout << "Termino : " << termino << "----------> NO INDEXADO." <<endl; //TODO  
					//getchar();//TODO
				}
			else
			{
				//cout<<"Termino: "<<termino<< "----------------> FILTRADO. "<<endl; //TODO
				//getchar();//TODO
			}
		}
		//cout << "BYTES OCUPADOS: " << bytesDelHeap << endl; //TODO
		
	}
	while(!termino.empty());
        //Terminé con el Documento
        agregarRegistrosAux1();
	//Vacío el trie TODO
	//cout << "Llevo " << idDocActual << "documentos indexados" << endl; getchar(); TODO
	//t->vaciar(); //TODO
	idDocActual++;
}
void Indexador::agregarRegistrosAux1(){
	//Recorre el trie volcando a Aux1 un registro asociado
	//a cada término con ftd no nula. Cada uno de esos registros
	//tiene la forma : nDoc ftd offsetATerminosParseados
	t->volcarAAux1(idDocActual, aux1);
	// Resetea las ftds para contar frecuencias en el próximo
	// documento. Los términos ya insertados amortizan el costo
	// de las posibles nuevas inserciones al trie.
	t->ponerFtdsEnCero();
}
void Indexador::indexarFase2(){

	//El trie de stopwords ya no es necesario
	delete stopWords; bytesDelHeap -= sizeof(stopWords); //TODO
	stopWords = NULL;
	//t.mostrar();//*TODO
	//getchar();
	// Se genera el archivo de léxico ordenado, que es un stream
	// con registros de longitud variable de estructura:
	// 	nTerm LongTerm Term.
	t->podarYGenerarLexico(lex);
	//cout<<"auxiliar 1..."<<endl;
	//aux1.mostrarAux1(); //TODO
	//terminosParseados.mostrarStream(); //TODO*/
	//cout<<"mostrando lexico..."<<endl;//TODO que quede usable despues de mostrar	
	//getchar();
	//lex.archLexico.mostrarStream(); //TODO
	// Ahora, se procede a generar el archivo auxiliar 2 a partir
	// de aux1 y t, donde quedaron todos los términos.
	aux1.cambiarModo(Constantes::LECTURA_BIN);
	terminosParseados.cambiarModo(Constantes::LECTURA_BIN);
	(lex.archLexico).cambiarModo(Constantes::LECTURA_BIN);
	RegAux1 regAux1; RegAux2 regAux2;
	string termino = "", sLongTerm = "", sNumTerm = ""; char c = '@';
	unsigned int longTerm, numTerm; long int offsetAlLex; char* cTerm;
	aux1.setPosicionLect(0);
	while(!aux1.esFin()){
		aux1.leer(&regAux1, sizeof(RegAux1));
		if(!aux1.esFin()){
			regAux2.nroDoc = regAux1.nroDoc;
			regAux2.ftd = regAux1.ftd;
			// Obtengo el string a partir del offset
			terminosParseados.setPosicionLect(regAux1.offset);
			terminosParseados.leer(&longTerm, sizeof(unsigned int));
			cTerm = new char[longTerm+1];
			terminosParseados.leer(cTerm, longTerm);
			cTerm[longTerm] = '\0';
			termino.assign(cTerm);
			delete cTerm;
			// Ahora, obtengo el offset al número de término buscando en el trie
			offsetAlLex = t->getOffsetAlLexico(termino);
			(lex.archLexico).setPosicionLect(offsetAlLex);
			lex.archLexico.leer(&numTerm, sizeof(unsigned int));
			regAux2.nroTerm = numTerm;
			// Escribo un nuevo registro a Aux2
			aux2.escribir(&regAux2, sizeof(RegAux2));
		}
		sLongTerm = termino = sNumTerm = "";
	}
	getchar();
	cout << "<-----------------------AUX 2------------------->" << endl; getchar(); //TODO
	aux2.mostrarAux2(); //TODO
	// Aux1 y terminosParseados ya no son necesarios
	aux1.eliminar();
	terminosParseados.eliminar();
	// El próximo paso es ordenar aux2 (sort externo)	
	SortExterno se;
	se.RealizarMergeSort();

}

// Genera los archivos que conforman el índice invertido: Éste es el último paso del
// proceso de indexación
void Indexador::GrabarArchivosdeIndexacion(){
	cout << "<-------------VOY A GRABAR ARCHIVOS DE INDEXACION------------->" << endl; //TODO
	getchar(); //TODO

	File aux2Ord(Constantes::NOM_AUX2_ORD, Constantes::LECTURA_BIN);
	File punt(Constantes::NOM_PUNT, Constantes::ESCRITURA_BIN);

	vector<RegDocFrec> vec;
	//FrontCodingManager* fcm=FrontCodingManager::getInstance();

	RegDocFrec regDocFrec;
	RegAux2 regAux2;
	string palabra;
	char* cTerm;

	int offset;
	int ft=0;
	int nroTermAnt;

	aux2Ord.leer(&regAux2,sizeof(RegAux2));
	nroTermAnt=regAux2.nroTerm;
	char c = '@';
	unsigned int numTerm, longTerm;
	

	lex.archLexico.cambiarModo(Constantes::LECTURA_BIN);
	while(!aux2Ord.esFin()){
		
		// Leo el número de término
		lex.archLexico.leer(&numTerm, sizeof(unsigned int));
		// Leo la longitud del término
		lex.archLexico.leer(&longTerm, sizeof(unsigned int));
		// Leo el término
		cTerm = new char[longTerm+1];
		lex.archLexico.leer(cTerm, longTerm);
		cTerm[longTerm] = '\0';
		palabra.assign(cTerm);
		delete cTerm; cTerm = NULL;
		
		while ((!aux2Ord.esFin()) && (regAux2.nroTerm==nroTermAnt)){
			ft++;
			regDocFrec.nroDoc=regAux2.nroDoc;
			regDocFrec.ftd=regAux2.ftd;
			vec.push_back(regDocFrec);
			aux2Ord.leer(&regAux2,sizeof(RegAux2));
			}
	
		offset= punt.getFinal();
		fcm->procesarPalabra(palabra,offset);

		punt.escribir(&ft,sizeof(int));
		for (int i=0;i<ft;i++)
			punt.escribir(&vec[i],sizeof(regDocFrec));
		vec.clear();	
		ft=0;
		nroTermAnt=regAux2.nroTerm;
		palabra="";
	}	
	aux2Ord.eliminar();
}

// Filtra strings que representen números, y al mismo tiempo aplica case folding.
bool Indexador::filtrarTermino(string &termino){
	bool esNum=true;

	for (int i=0; i<termino.size(); i++){
		termino[i] = tolower(termino[i]);
		if (( (termino[i]>='a')&&(termino[i]<='z'))||(termino[i]=='ñ'))
			esNum=false;	
	}
	return esNum;
}

void Indexador::indexarFase3(){
	delete t; // El trie ya no es necesario
	Norma norm(idDocActual);
	norm.CalcularNorma();
	GrabarArchivosdeIndexacion();
	lex.archLexico.eliminar();
	aux2.eliminar();
	FrontCodingManager::destroy(); //Equivale a un delete ("destructor estático")
}
