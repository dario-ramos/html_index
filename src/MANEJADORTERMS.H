#ifndef MANEJADOR_DE_TERMINOS
#define MANEJADOR_DE_TERMINOS

class ManejadorDeTerms{
	//TODO: Atributos: Los determinaré al implementar. =P
public:
	ManejadorDeTerms();
	~ManejadorDeTerms();
	// Recibe un término parseado y el número de documento al que pertenece.
	// Si es nuevo, lo agrega al trie donde va almacenando el léxico.
	// Si no, sólo aumenta la ftd.
	void procesarTerm(unsigned long numDoc, Termino t);
	// Si el trie llena la memoria, una parte del mismo es volcada a disco
	// al invocar este método. 
	// TODO: Encontrar una manera de saber cuánta memoria hay disponible
	void generarParticionOrdenada();
	// Al terminar de parsear un doc, hay que invocar este método para
	// que vuelque los registros correspondientes a los términos nuevos
	// al archivo auxiliar1. Al terminar, debe resetear las ftd's a 0.
	void volcarAArchAux1(Archivo aux1);
	// Una vez parseados todos los docs...
	Lexico generarLexico();
};

#endif
