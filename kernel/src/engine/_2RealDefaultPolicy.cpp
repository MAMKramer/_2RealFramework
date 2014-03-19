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

#include "engine/_2RealDefaultPolicy.h"

namespace _2Real
{
	DefaultPolicy::DefaultPolicy( const Code c ) : mCode( c )
	{
	}

	DefaultPolicy::DefaultPolicy( std::vector< std::vector< std::string > > const& inlets ) : mCode( UNDEFINED ), mInlets( inlets )
	{
	}

	bool DefaultPolicy::resolve( std::vector< std::string > const& inlets )
	{
		bool ok = true;
		switch ( mCode )
		{
		case ANY:

				for ( auto it : inlets )
				{
					std::vector< std::string > tmp;
					tmp.push_back( it );
					mInlets.push_back( tmp );
				}

			break;
		case ALL:

				mInlets.push_back( inlets );

			break;
		default:

			for ( auto i : mInlets )
				for ( auto j : i )
				{
					if ( std::find( inlets.begin(), inlets.end(), j ) == inlets.end() )
						ok = false;
				}

			break;
		}

		return ok;
	}

	std::vector< std::vector< std::string > > const& DefaultPolicy::getStringRep() const
	{
		return mInlets;
	}

	std::shared_ptr< DefaultPolicy > DefaultPolicy::clone() const
	{
		std::shared_ptr< DefaultPolicy > result( new DefaultPolicy( mCode ) );

		for ( auto it : mInlets )
		{
			std::vector< std::string > tmp;
			for ( auto p : it )
			{
				tmp.push_back( p );
			}
			result->mInlets.push_back( tmp );
		}

		return result;
	}

}
