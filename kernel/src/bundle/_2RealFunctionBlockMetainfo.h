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
#include "engine/_2RealSharedServiceFactory_T.h"

namespace _2Real
{
	class SharedServiceMetainfo;

	namespace bundle
	{
		class InletMetainfo;
		class OutletMetainfo;
		class ParameterMetainfo;
		class InSlotPolicy;

		class FunctionBlockMetainfo
		{

		public:

			explicit FunctionBlockMetainfo( std::shared_ptr< SharedServiceMetainfo > );

			template< typename TBlock >
			void setBlockClass()
			{
				std::shared_ptr< AbstractSharedServiceFactory > f( new SharedServiceFactory_T< TBlock > );
				setBlockClassInternal( f );
			}

			void setDescription( std::string const& );
			void setDependencies( std::vector< std::string > const& );

			OutletMetainfo createOutlet( std::string const& name );
			InletMetainfo createInlet( std::string const& name );
			ParameterMetainfo createParameter( std::string const& name );

			void setDefaultUpdatePolicy( InSlotPolicy const& );
			void setDefaultSetupPolicy( InSlotPolicy const& );

		private:

			void setBlockClassInternal( std::shared_ptr< AbstractSharedServiceFactory > );

			std::weak_ptr< SharedServiceMetainfo >		mImpl;

		};
	}
}