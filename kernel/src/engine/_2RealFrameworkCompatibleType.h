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

#include "helpers/_2RealStdIncludes.h"

namespace _2Real
{
	template< typename T > struct FrameworkCompatibleType;

	template< >
	struct FrameworkCompatibleType< int >
	{
		static int defaultValue()
		{
			return static_cast< int >( 0 );
		}

		static std::string humanReadableName()
		{
			return "int";
		}

		static void writeTo( std::ostream &out, int v )
		{
			out << v;
		}

		static void readFrom( std::istream &in, int &v )
		{
			in >> v;
		}
	};

	template< >
	struct FrameworkCompatibleType< float >
	{
		static float defaultValue()
		{
			return 0.f;
		}

		static std::string humanReadableName()
		{
			return "float";
		}

		static void writeTo( std::ostream &out, float v )
		{
			out << v;
		}

		static void readFrom( std::istream &in, float &v )
		{
			in >> v;
		}
	};

	template< >
	struct FrameworkCompatibleType< std::string >
	{
		static std::string defaultValue()
		{
			return "";
		}

		static std::string humanReadableName()
		{
			return "string";
		}

		static void writeTo( std::ostream &out, std::string const& v )
		{
			out << v;
		}

		static void readFrom( std::istream &in, std::string &v )
		{
			in >> v;
		}
	};
}