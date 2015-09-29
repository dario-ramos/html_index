#include "sortexterno.h"
extern unsigned long bytesDelHeap; //TODO

using namespace std;

SortExterno::SortExterno():archAux2(Constantes::NOM_AUX2,Constantes::LECTURA_BIN){}//,archAux2Ord("aux2ord.bin",1){}


int SortExterno::Sort(){

	RegAux2 regAux2;
	RegPart regPart;
	int i=0;
	int pos=0;	
	int nroPart=1; //empiezo con particion nro 1
	int cantRegPart=0;
	string nombre;
	
	archAux2.leer(&regAux2,sizeof(RegAux2));

	while ((i<MAX_ELEMENT) && (!archAux2.esFin())){
		buff[i].reg= regAux2;
		buff[i].estado='D';
		i++;
		archAux2.leer(&regAux2,sizeof(RegAux2));
	}
	cantRegs=i;  

	while (!VectorVacio()){
		cout << "HACIENDO MERGE..." << endl; //TODO
		nombre=GenerarNomParticion(nroPart);
		File particion(nombre,1);

		while ((!TodosCongelados()) && (!VectorVacio())){

			BuscarMenor(pos);
			particion.escribir(&buff[pos].reg,sizeof(RegAux2));
			cantRegPart++;
			if (!archAux2.esFin()){			

				if (regAux2.nroTerm<buff[pos].reg.nroTerm)	
					buff[pos].estado='C';
				buff[pos].reg=regAux2;
				archAux2.leer(&regAux2,sizeof(RegAux2));	
			}
			else
				buff[pos].estado='V';
		}
		
		if ((TodosCongelados())&&(!VectorVacio()))
			Descongelar();
		
		//agrego particion a vector
		regPart.nroPart=nroPart;
		regPart.cantRegPart=cantRegPart;
		vecPart.push_back(regPart);	
		//inicializo cant de registros por particion para la siguiente particion
		cantRegPart=0;

		nroPart++;
	}
	nroPart--;

	return nroPart;//"cantidad de particiones"
}



bool SortExterno::TodosCongelados(){
	bool congelados=true;
	int i=0;
	while ((congelados) && (i<cantRegs)){
		if (buff[i].estado=='D')
			congelados=false;
		i++;
		}
	return congelados;
}


void SortExterno::Descongelar(){
	for (int i=0;i<MAX_ELEMENT;i++){
		if (buff[i].estado=='C')
			buff[i].estado='D';
	}

}


bool SortExterno::VectorVacio(){
	bool vacio=true;
	int i=0;
	while ((vacio) && (i<cantRegs)){
		if (buff[i].estado!='V')
			vacio=false;
			i++;
		}
	return vacio;
}


string SortExterno::GenerarNomParticion(int nroPart){
	
	string nro;
	stringstream out;
	out << nroPart;
	nro = out.str();
	
	string nombre;
	nombre = "Part"+nro+".bin";
	return nombre;
}


void SortExterno::BuscarMenor(int& pos){
	RegAux2 menor;
	menor.nroTerm=MAX_NTERM;
	menor.nroDoc=MAX_NDOC;
	int i;

	for (i=0;i<cantRegs;i++){

		if ( (buff[i].estado=='D') && (  (buff[i].reg.nroTerm<menor.nroTerm)||( (buff[i].reg.nroTerm==menor.nroTerm)
								   && (buff[i].reg.nroDoc<menor.nroDoc)) ) ){
			menor.nroTerm=buff[i].reg.nroTerm;
			menor.nroDoc=buff[i].reg.nroDoc;
			pos = i;
		}
	}
}


void SortExterno::Merge(int cantPart){
	RegPart regPart;

	//ordeno el vector de particiones de acuerdo a cantidad de registros
	sort(vecPart.begin(),vecPart.end(),MyDataSortPredicate);	

	int proxPart=cantPart+1;
	while(vecPart.size()>1){
		if (vecPart.size()==2){

			MergeDeA2(vecPart[0].nroPart,vecPart[1].nroPart,proxPart);

			//agrego la nueva particion al vector 			
			regPart.nroPart=proxPart;
			regPart.cantRegPart=vecPart[0].cantRegPart+vecPart[1].cantRegPart;
			vecPart.push_back(regPart);

			//borro particiones 0 y 1
			vecPart.erase(vecPart.begin());
			vecPart.erase(vecPart.begin());

			//ordeno para la proxima pasada
			sort(vecPart.begin(), vecPart.end(), MyDataSortPredicate);			

			//cantPart--;
			proxPart++;
		}else{
			MergeDeA3(vecPart[0].nroPart,vecPart[1].nroPart,vecPart[2].nroPart,proxPart);
			//agrego la nueva particion al vector 			
			regPart.nroPart=proxPart;
			regPart.cantRegPart=vecPart[0].cantRegPart+vecPart[1].cantRegPart+vecPart[2].cantRegPart;
			vecPart.push_back(regPart);

			//borro particiones 0 y 1 y 2
			vecPart.erase(vecPart.begin());
			vecPart.erase(vecPart.begin());
			vecPart.erase(vecPart.begin());

			//ordeno para la proxima pasada
			sort(vecPart.begin(), vecPart.end(), MyDataSortPredicate);			

			proxPart++;
		}
	}
			
	/*Elimino las particiones hasta ProxPart:*/
	EliminarParticiones(proxPart-1);//Ademas deja auxiliar2ord.bin
	
}


void SortExterno::EliminarParticiones(int Part){
	string nombre;
	for(int i=0;i<Part;i++){
		nombre=GenerarNomParticion(i);
		remove (nombre.c_str());
	}
	nombre=GenerarNomParticion(Part);
	rename (nombre.c_str(),Constantes::NOM_AUX2_ORD.c_str());
	
}

void SortExterno::MergeDeA3(int p1,int p2,int p3,int prox){

	string ent1=GenerarNomParticion(p1); 
	string ent2=GenerarNomParticion(p2);
	string ent3=GenerarNomParticion(p3);
	string sal=GenerarNomParticion(prox);
	
	File E1(ent1,Constantes::LECTURA_BIN);
	File E2(ent2,Constantes::LECTURA_BIN);
	File E3(ent3,Constantes::LECTURA_BIN);
	File S(sal,Constantes::ESCRITURA_BIN);
	
	RegAux2 r1;
	RegAux2 r2;
	RegAux2 r3;
	RegAux2 rs;
	
	E1.leer(&r1,sizeof(RegAux2));
	E2.leer(&r2,sizeof(RegAux2));
	E3.leer(&r3,sizeof(RegAux2));
	
	while(!E1.esFin() || !E2.esFin() || !E3.esFin()){
		rs=r1;

		if((r2.nroTerm < rs.nroTerm)||((r2.nroTerm == rs.nroTerm)&&(r2.nroDoc < rs.nroDoc))) rs=r2;
		if((r3.nroTerm < rs.nroTerm)||((r3.nroTerm == rs.nroTerm)&&(r3.nroDoc < rs.nroDoc))) rs=r3;
		S.escribir(&rs,sizeof(RegAux2));
		
		//leer el que corresponda:
		if(SonIguales(rs,r1)) E1.leer(&r1,sizeof(RegAux2));
		if(SonIguales(rs,r2)) E2.leer(&r2,sizeof(RegAux2));
		if(SonIguales(rs,r3)) E3.leer(&r3,sizeof(RegAux2));
		
		if(E1.esFin()) {r1.nroTerm=MAX_NTERM; r1.nroDoc=MAX_NDOC;}
		if(E2.esFin()) {r2.nroTerm=MAX_NTERM; r2.nroDoc=MAX_NDOC;}
		if(E3.esFin()) {r3.nroTerm=MAX_NTERM; r3.nroDoc=MAX_NDOC;}
	}
}

bool SortExterno::SonIguales(RegAux2 reg1, RegAux2 reg2){
	if((reg1.nroTerm == reg2.nroTerm)&&(reg1.nroDoc == reg2.nroDoc)) return true;
				else return false;
}

void SortExterno::MergeDeA2(int p1,int p2,int prox){
	string ent1=GenerarNomParticion(p1);
	string ent2=GenerarNomParticion(p2);
	string sal=GenerarNomParticion(prox);
	
	File E1(ent1,Constantes::LECTURA_BIN);
	File E2(ent2,Constantes::LECTURA_BIN);
	File S(sal,Constantes::ESCRITURA_BIN);
	
	RegAux2 r1;
	RegAux2 r2;
	RegAux2 rs;
	
	E1.leer(&r1,sizeof(RegAux2));
	E2.leer(&r2,sizeof(RegAux2));
	

	while((!E1.esFin()) || (!E2.esFin())){
		rs=r1;
		if((r2.nroTerm < rs.nroTerm)||((r2.nroTerm == rs.nroTerm)&&(r2.nroDoc < rs.nroDoc))) rs=r2;
		S.escribir(&rs,sizeof(RegAux2));
		
		//leer el que corresponda:
		if(SonIguales(rs,r1)) E1.leer(&r1,sizeof(RegAux2));
		if(SonIguales(rs,r2)) E2.leer(&r2,sizeof(RegAux2));
		
		if(E1.esFin()) {r1.nroTerm=MAX_NTERM; r1.nroDoc=MAX_NDOC;}
		if(E2.esFin()) {r2.nroTerm=MAX_NTERM; r2.nroDoc=MAX_NDOC;}
		
	}
}


bool SortExterno::MyDataSortPredicate(const RegPart& lhs,const RegPart& rhs){
  return lhs.cantRegPart < rhs.cantRegPart;
}



void SortExterno::RealizarMergeSort(){
   int CantParticiones;
   CantParticiones=Sort();
   Merge(CantParticiones);
   cout<<"<----------------AUX2 ORDENADO:----------------->PARTICIONES: "<<CantParticiones<<endl;
   //eliminar las particiones
   File aux2Ord(Constantes::NOM_AUX2_ORD,Constantes::LECTURA_BIN); //TODO
   aux2Ord.mostrarAux2();//TODO
   
}

SortExterno::~SortExterno(){ //TODO
	cout << "BYTES AL DESTR SORTEXT " << bytesDelHeap << endl;
}
