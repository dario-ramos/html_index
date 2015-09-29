#ifndef REGISTROS_H
#define REGISTROS_H

//Definiciones de las estructuras de los registros usados
class RegAux1{
public:
	unsigned int nroDoc;
	unsigned int ftd;
	long int offset;
};

class RegAux2{
public:
	unsigned int nroTerm;
	unsigned int nroDoc;
	unsigned int ftd;
};

class RegVecNorma{
	public:
	float wt;	
};

class RegBuff{
	public:
	RegAux2 reg;
	char estado;	//C:congelado D:descongelado V:vacío
};

class RegPart{
	public:
	int nroPart;
	int cantRegPart;
};
class RegDocFrec {
	public:
	int nroDoc;
	int ftd;
};

#endif
