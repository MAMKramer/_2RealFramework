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

#include "bundle/_2RealCustomTypeMetainfo.h"
#include "engine/_2RealCustomTypeMetainfoImpl.h"

namespace _2Real
{
	namespace bundle
	{

		CustomTypeMetainfo::CustomTypeMetainfo( std::shared_ptr< CustomTypeMetainfoImpl > metadata ) :
			mImpl( metadata )
		{
		}

		bool CustomTypeMetainfo::isBasicType() const
		{
			return false;
		}

		void CustomTypeMetainfo::setDescription( std::string description )
		{
			mImpl->setDescription( description );
		}

		void CustomTypeMetainfo::setInitialFieldValue( std::string const& fieldName, DataItem value )
		{
			mImpl->setInitialFieldValue( fieldName, std::move( value ) );
		}

		CustomDataItem CustomTypeMetainfo::makeCustomData() const
		{
			return mImpl->makeCustomData();
		}
	
		DataItem CustomTypeMetainfo::makeData() const
		{
			return mImpl->makeData();
		}

		std::string CustomTypeMetainfo::getName() const
		{
			return mImpl->getName();
		}

	}
}