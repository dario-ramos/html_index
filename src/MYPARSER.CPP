// -*- C++ -*-

/* myparser.cc
 *
 * Copyright (C) 2002 The libxml++ development team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

extern unsigned long bytesDelHeap; //TODO
#include <iostream> //TODO
using namespace std; //TODO
#include "myparser.h"

//---------------------------------------------------------------------------------------------------------------
//Declaramos los metodos de Auxilares
void Auxiliares::Limpiar_Buffer(char Bufer[],int longitud)
{
	int i;
	for (i = 0;i < longitud;i++)
		Bufer[i] = '\0';
}

//---------------------------------------------------------------------------------------------------------------
// Declaramos los metodos de MySaxParser

MySaxParser::MySaxParser()
  : xmlpp::SaxParser(true /* override on_get_entity */)
{
}

MySaxParser::~MySaxParser()
{ cout << "BYTES AL DESTR PARSER " << bytesDelHeap << endl; //TODO
}

void MySaxParser::on_start_document()
{
  //std::cout << "on_start_document()" << std::endl;
}

void MySaxParser::on_end_document()
{
  //std::cout << "on_end_document()" << std::endl;
}

void MySaxParser::on_start_element(const std::string& name,
                                   const AttributeList& attributes)
{
  /*
  std::cout << "node name=" << name << std::endl;

  // Print attributes:
  for(AttributeMap::const_iterator iter = attributes.begin();
      iter != attributes.end();
      ++iter)
  {
    std::cout << "  Attribute " << iter->first << " = " << iter->second << std::endl;
  }
  */
	
}

void MySaxParser::on_end_element(const std::string& name)
{
  //std::cout << "on_end_element()" << std::endl;
	//Aca agrego Yo
	if (!Texto.empty()){
		if (Texto[Texto.length()-1]!=' ')
			Texto+=' ';
	}else Texto+=' ';
}

void MySaxParser::on_characters(const std::string& text)
{
    //std::cout << "on_characters(): " << text << std::endl;
	
    //Aca agrego Yo
	int x=0;

	do
	{	 
		if ( ( text[x] >= 65 && text[x] <= 90 ) ||
		( text[x] >= 97 && text[x]<= 122 ) ||
		( text[x] >= 48 && text[x] <= 57 ) || 
		 (text[x] == 'ñ') || 
		 (text[x] == 'Ñ') )
			  Texto+=text[x];
		else
		switch (text[x])
		{	
			case ('á') :  Texto+= 'a'; break;
			case ('Á') :  Texto+= 'A'; break;
			case ('é') :  Texto+= 'e'; break;
			case ('É') :  Texto+= 'E'; break;
			case ('í') :  Texto+= 'i'; break; 
			case ('Í') :  Texto+= 'I'; break;
			case ('ó') :  Texto+= 'o'; break;
			case ('Ó') :  Texto+= 'O'; break;
			case ('ú') :  Texto+= 'u'; break;
			case ('Ú') :  Texto+= 'U'; break;
			default : {
					if (!Texto.empty())
					{	if (Texto[Texto.length()-1]!=' ')
							Texto+=' ';}
					else
						Texto+=' ';
				   }	 
		}	
		x++;
				
	}
	while ( x < text.length() );
		
}

void MySaxParser::on_comment(const std::string& text)
{
  //std::cout << "on_comment(): " << text << std::endl;
}

void MySaxParser::on_warning(const std::string& text)
{
  std::cout << "on_warning(): " << text << std::endl;
  getchar(); //TODO
}

void MySaxParser::on_error(const std::string& text)
{
  std::cout << "on_error(): " << text << std::endl;
  getchar(); //TODO
}

void MySaxParser::on_fatal_error(const std::string& text)
{
  std::cout << "on_fatal_error(): " << text << std::endl;
  getchar(); //TODO
}

_xmlEntity* MySaxParser::on_get_entity(const std::string& name)
{
	static bool llamado = false;

	if (!llamado)
	{
		xmlpp::XmlEntityType type;
		std::string publicId; 
		std::string systemId;
		std::string contenido;
		//unsigned char enie = 241;
		//contenido+=enie;
		type = (xmlpp::XmlEntityType) 1;
		SaxParser::on_entity_declaration("aacute", type, publicId, systemId,"a");
		SaxParser::on_entity_declaration("eacute", type, publicId, systemId,"e");
		SaxParser::on_entity_declaration("iacute", type, publicId, systemId,"i");
		SaxParser::on_entity_declaration("oacute", type, publicId, systemId,"o");
		SaxParser::on_entity_declaration("uacute", type, publicId, systemId,"u");
		SaxParser::on_entity_declaration("ntilde", type, publicId, systemId,"n");
		SaxParser::on_entity_declaration("Aacute", type, publicId, systemId,"a");
		SaxParser::on_entity_declaration("Eacute", type, publicId, systemId,"e");
		SaxParser::on_entity_declaration("Iacute", type, publicId, systemId,"i");
		SaxParser::on_entity_declaration("Oacute", type, publicId, systemId,"o");
		SaxParser::on_entity_declaration("Uacute", type, publicId, systemId,"u");
		SaxParser::on_entity_declaration("Ntilde", type, publicId, systemId,"n");
		llamado = true;
	}
  //std::cout << "on_get_entity(): " << name << std::endl;
  
  //Call the base class:
  return SaxParser::on_get_entity(name);
}

void MySaxParser::on_entity_declaration(const std::string& name, xmlpp::XmlEntityType type, const std::string& publicId, const std::string& systemId, const std::string& content)
{
  std::cout << "on_entity_declaration(): name=" << name << ", publicId=" << publicId << ", systemId=" << systemId << ", content=" << content << std::endl;

	//std :: cout <<"El type es: "<<type<<std::endl;
  //Call the base class:
  SaxParser::on_entity_declaration(name, type, publicId, systemId, content);
}
//--------------------------------------------------------------------------------------------------------

// Ahora declaramos los metoodos del Parser G7

Parser_G7::Parser_G7()
{
	 try
  	{
    		MySaxParser parser;
    		parser.set_substitute_entities(true); 
    		//parser.parse_file(filepath);
  	}
  	catch(const xmlpp::exception& ex)
  	{
    		std::cout << "libxml++ exception: " << ex.what() << std::endl;
		getchar(); //TODO
  	}
}
void Parser_G7::setear(const char *archivo)
{
	static bool prim_vez = true;
	/*try
	{
		parser.parse_file(archivo);
	}
	catch(const xmlpp::exception& ex)
  	{
    		std::cout << "libxml++ exception: " << ex.what() << std::endl;
  	}*/
	if (prim_vez)
		prim_vez = false;
	else
	{
		fichero.close();
		fichero.clear(); 
		parser.finish_chunk_parsing();
	}
	fichero.open(archivo);
}
bool Parser_G7::leer()
{
	Limpiar_Buffer();
        fichero.read((char *)(Buff), BUFFSIZE-1);
	
	//std::cout << "Bufer: " << Buff << std::endl;
	//getchar(); 
        
	std::string input((char *)(Buff), fichero.gcount());

        parser.parse_chunk(input);
        
	return (fichero);   
}
std::string Parser_G7::Prox_Termino ()
{
	std::string palabra;
	bool estado = true;
	
	
	while ( (parser.Texto.empty()) && estado )
	{
		estado = leer();
		if (!parser.Texto.empty())
			if ( (parser.Texto.length() == 1) && (parser.Texto[0]== ' ') )
				parser.Texto.erase(0,1);
	}
			
	if (!parser.Texto.empty())
	{
		estado = true;
		while ( (parser.Texto[0]==' ') && (!parser.Texto.empty()) )
			parser.Texto.erase(0,1);
		while ( (parser.Texto[0]!=' ') && (parser.Texto[0]!='\0') && estado)
		{
			if (palabra.length() > MAXPAL)
			{
				std::cout << "Advertencia : Palabra demasiado larga ha sido truncada" << std::endl;
				parser.Texto[0] = ' ';
			}
			else
			{
				palabra+= parser.Texto[0];
				if ( parser.Texto.length() > 1 )
					parser.Texto.erase(0,1);
				else
					estado = false;
			}
		}	
		if (estado)
		{
			parser.Texto.erase(0,1);
			return(palabra);
		}
		else
		{
			parser.Texto.erase(0,1);
			estado = true;
			while ((parser.Texto.empty()) && estado )
			{
				estado = leer();
				/*if (!parser.Texto.empty())
					if ( (parser.Texto.length() == 1) && (parser.Texto[0] == ' ') )
						parser.Texto.erase(0,1);*/
			}
			if (parser.Texto.empty())
				return(palabra);
			else
			{
				estado = true;
				while ( (parser.Texto[0]!=' ') && (parser.Texto[0]!='\0') && estado)
				{
					if (palabra.length() > MAXPAL)
					{		
						std::cout << "Advertencia : Palabra demasiado larga ha sido truncada" << std::endl;
						parser.Texto[0] = 0;
					}
					else
					{			
						palabra+= parser.Texto[0];
						if ( parser.Texto.length() > 1 )
							parser.Texto.erase(0,1);
						else
							estado = false;
					}
				}
				parser.Texto.erase(0,1);
				return(palabra);
				
			}
		}
	}
	else
		return(palabra);
}	
void Parser_G7::Limpiar_Buffer()
{
	Auxiliares a;
	
	a.Limpiar_Buffer((char *)(Buff),BUFFSIZE);
}
//-------------------------------------Ahora un Ejemplito------------------------------------------
/*int main(void)
{
	int cant = 0;
        Parser_G7 p;
	std::string termino;
	p.setear("./fabulas.htm");
	do
	{
		if (!termino.empty())
			termino.erase(0,termino.length());
		termino = p.Prox_Termino();
		std::cout<< "Termino: "<< termino<< std::endl;
		cant++;
		if (cant == 50)
			{cant = 0;getchar();}
	}
	while(!termino.empty());	
  	return 1;
}*/
