// -*- C++ -*-

/* myparser.h
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

#ifndef __LIBXMLPP_EXAMPLES_MYPARSER_H
#define __LIBXMLPP_EXAMPLES_MYPARSER_H

#include <libxml++/libxml++.h>
#include <string.h>

//Aca agrego Yo
#include <fstream>
#include <iostream>
#define BUFFSIZE        64
#define MAXPAL          30
class Auxiliares
{
	public:
		void Limpiar_Buffer(char Bufer[],int longitud);
};
		
class MySaxParser : public xmlpp::SaxParser
{
	public:
  		MySaxParser();
  		virtual ~MySaxParser();
		//Aca agergo Yo
		std::string Texto;

	protected:

		//overrides:
	
  		virtual void on_start_document();
  		virtual void on_end_document();
  		virtual void on_start_element(const std::string& name,
                                const AttributeList& properties);
  		virtual void on_end_element(const std::string& name);
  		virtual void on_characters(const std::string& characters);
  		virtual void on_comment(const std::string& text);
  		virtual void on_warning(const std::string& text);
  		virtual void on_error(const std::string& text);
  		virtual void on_fatal_error(const std::string& text);
		virtual _xmlEntity* on_get_entity(const std::string& name);
  		virtual void on_entity_declaration(const std::string& name, xmlpp::XmlEntityType type,
						   const std::string& publicId, const std::string& systemId,
						   const std::string& content);
};

class Parser_G7
{
	protected:
		MySaxParser parser;
		std::ifstream fichero;
		char Buff[BUFFSIZE];

		bool leer();		
	public:
		Parser_G7();
		void setear(const char *archivo);
		std::string Prox_Termino ();
	protected:
		void Limpiar_Buffer();
};		
#endif //__LIBXMLPP_EXAMPLES_MYPARSER_H

