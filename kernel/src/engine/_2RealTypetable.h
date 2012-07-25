/*
	CADET - Center for Advances in Digital Entertainment Technologies
	Copyright 2011 Fachhochschule Salzburg GmbH
		http://www.cadet.at

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

		http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/

#pragma once

#include "helpers/_2RealAny.h"
#include "helpers/_2RealInitializers.h"

#include <list>
#include <vector>
#include <map>
#include <string>
#include <assert.h>

namespace _2Real
{
	class Typetable
	{

	public:

		template< typename TType >
		void registerType( std::string const& typeName );

		std::string const&		lookupTypename( std::string const& longTypename ) const;
		const std::string		lookupLongTypename( std::string const& typeName ) const;
		Any const&				getInitialValueFromLongTypename( std::string const& longTypename ) const;
		Any const&				getInitialValueFromTypename( std::string const& typeName ) const;

	private:

		typedef std::map< std::string, Any >							Datatypes;
		typedef std::map< std::string, Any >::iterator					DatatypeIterator;
		typedef std::map< std::string, Any >::const_iterator			DatatypeConstIterator;

		typedef std::map< std::string, std::string >					Typenames;
		typedef std::map< std::string, std::string >::iterator			TypenameIterator;
		typedef std::map< std::string, std::string >::const_iterator	TypenameConstIterator;

		Datatypes			m_Datatypes;
		Typenames			m_Typenames;

	};

	template< typename TType >
	void Typetable::registerType( std::string const& typeName )
	{

#ifdef _DEBUG
		DatatypeIterator it = m_Datatypes.find( typeName );
		if ( it != m_Datatypes.end() )
		{
			assert( NULL );
		}
#endif

		TType data;// = _2Real::initialValue< TType >();
		Any any( data );
		m_Datatypes[ typeName ] = any;

		std::string type = typeid( TType ).name();
		m_Typenames[ type ] = typeName;

	}

}