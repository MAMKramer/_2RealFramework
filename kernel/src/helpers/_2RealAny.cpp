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

#include "helpers/_2RealAny.h"

namespace _2Real
{
	Any::Any() :
		m_Content(),
		m_Typename( typeid( void ).name() )
	{
		AbstractAnyHolder *h = nullptr;
		m_Content.reset( h );
	}

	Any::Any( Any const& src ) :
		m_Content( src.m_Content ),
		m_Typename( src.m_Typename )
	{
	}

	Any& Any::operator=( Any const& src )
	{
		if (this == &src)
		{
			return *this;
		}

		m_Typename = src.m_Typename;
		m_Content = src.m_Content;

		return *this;
	}

	bool Any::isEmpty() const
	{
		return m_Content.get() == nullptr;
	}

	bool Any::isEqualTo( Any const& any ) const
	{
		if ( any.isEmpty() )
		{
			return isEmpty();
		}

		return m_Content->isEqualTo( *any.m_Content.get() );
	}

	bool Any::isLessThan( Any const& any ) const
	{
		if ( any.isEmpty() )
		{
			return false;
		}

		return m_Content->isLessThan( *any.m_Content.get() );
	}

	void Any::writeTo(std::ostream &out) const
	{
		if ( !isEmpty() )
		{
			m_Content->writeTo(out);
		}
	}

	void Any::readFrom(std::istream &in)
	{
		if ( !isEmpty() )
		{
			m_Content->readFrom(in);
		}
	}

	std::string const& Any::getTypename() const
	{
		return m_Typename;
	}

	void Any::cloneFrom( Any const& src )
	{
		m_Content.reset( src.m_Content->clone() );
		m_Typename = src.m_Typename;
	}

	void Any::createNew( Any const& src )
	{
		m_Content.reset( src.m_Content->create() );
		m_Typename = src.m_Typename;
	}

}