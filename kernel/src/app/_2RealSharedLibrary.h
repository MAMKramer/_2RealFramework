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

#ifdef _WIN64
	#include "_2RealSharedLibrary_WIN.h"
#elif _WIN32
	#include "_2RealSharedLibrary_WIN.h"
#elif _UNIX
	#include "_2RealSharedLibrary_UNIX.h"
#endif

#include "helpers/_2RealPath.h"

namespace _2Real
{

	class SharedLibrary : private SharedLibraryImpl
	{

	public:

		SharedLibrary( Path const& path );
		virtual ~SharedLibrary();

		bool hasSymbol( std::string const& name ) const;
		void * getSymbol( std::string const& name );

		//const std::string& getPath() const;
		//static std::string suffix();

		// debug methods
		void enumerateSymbols();
		
	private:

		SharedLibrary( SharedLibrary const& );
		SharedLibrary& operator=( SharedLibrary const& );

	};

}