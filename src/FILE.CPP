#include "file.h"
extern unsigned long bytesDelHeap; //TODO
File::File(string s, const int m) : nomArch(s), modo(m), offsetAlFinal(0){
	if(m == Constantes::ESCRITURA_BIN)
		archivo.open(nomArch.c_str(), ios::out | ios:: binary | ios::trunc);
	else if(m == Constantes::LECTURA_BIN)
		archivo.open(nomArch.c_str(), ios::in | ios::binary);
	else
		archivo.open(nomArch.c_str(), ios::in | ios::out | ios::binary);
	if(!this->archivo.is_open())
	{
		// limpio los flags
		this->archivo.clear();
		
		// crea el archivo abriendolo para escritura binaria
		
		this->archivo.open(this->nomArch.c_str(),ios::out | ios::binary);
		this->archivo.close();
		
		// ahora lo abre para lectura / escritura binaria y lo deja listo para usar
		archivo.open(this->nomArch.c_str(),ios::in |ios::out | ios::binary);
	}    

}
File::~File(){
	if(archivo.good()) archivo.close(); cout << "BYTES LUEGO DE DESTR ARCH " << bytesDelHeap << endl; //TODO
}
bool File::escribir(const void* reg, int tamEnBytes){
	if(modo == Constantes::ESCRITURA_BIN || modo == Constantes::LECT_Y_ESC_BIN){
		archivo.write((char*)reg, tamEnBytes);
		offsetAlFinal += tamEnBytes;
		return true;
	}else
		return false;
}
void File::cambiarModo(const int m){
	archivo.close();
	if(m == Constantes::ESCRITURA_BIN){
		archivo.open(nomArch.c_str(), ios::out | ios:: binary | ios::trunc);
		archivo.seekg(0);
	}
	else if(m == Constantes::LECTURA_BIN)
		archivo.open(nomArch.c_str(), ios::in | ios::binary);
	else
		archivo.open(nomArch.c_str(), ios::in | ios::out | ios::binary);
	modo = m;
}
bool File::leer(void* reg, int tamEnBytes){
	if (modo == Constantes::LECTURA_BIN || modo == Constantes::LECT_Y_ESC_BIN){
		archivo.read((char*)reg, tamEnBytes);
		return true;
	}
	else
		return false;
}
long int File::getFinal(){
	return offsetAlFinal;
}
bool File::leerProxCaracter(char& c){
	if (modo == Constantes::LECTURA_BIN || modo == Constantes::LECT_Y_ESC_BIN){
		archivo.get(c);
		return true;
	}
	else
		return false;
}
bool File::esFin(){
	return archivo.eof();
}
void File::setPosicionLect(long int pos){
	archivo.seekg(pos);
}
void File::eliminar(){
	archivo.close();
	remove(nomArch.c_str());
}

//Es para un secuencial

bool File::lectura_secuencial(void *reg){
	if (modo == Constantes::LECTURA_BIN){
		archivo.getline((char *) reg, MAX_LONG_PAL);
		return true;
	}
	else
		return false;
}
bool File::estado_archivo(){
	return (archivo.good());
}

//TODO: Sacar todos los métodos que siguen
void File::mostrarAux1(){
	archivo.close();
	archivo.open(nomArch.c_str(), ios::in | ios::binary);
	archivo.seekg(0);
	RegAux1 r;
	modo = Constantes::LECTURA_BIN;
	while(!archivo.eof()){
		leer(&r, sizeof(RegAux1));
		if(!archivo.eof()){
			cout << "NDoc = " << r.nroDoc;
			cout << " Ftd = " << r.ftd;
			cout << " Offset = " << r.offset << endl;
		}
	}
}
void File::mostrarStream(){
	archivo.close();
	archivo.open(nomArch.c_str(), ios::in | ios::binary);
	archivo.seekg(0);
	char c;
	modo = Constantes::LECTURA_BIN;
	while(!archivo.eof()){
		leerProxCaracter(c);
		if (!(archivo.eof()))
			if(c == ' ') cout << endl;
			else cout << c;
			
	}
	cout << endl;
}
void File::mostrarAux2(){
	archivo.close();
	archivo.open(nomArch.c_str(), ios::in | ios::binary);
	archivo.seekg(0);
	RegAux2 r;
	modo = Constantes::LECTURA_BIN;
	while(!archivo.eof()){
		leer(&r, sizeof(RegAux2));
		if(!archivo.eof()){
			cout << "NTerm = " << r.nroTerm;
			cout << " NroDoc = " << r.nroDoc;
			cout << " Ftd = " << r.ftd << endl;
		}
	}
}

