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

#include "common/_2RealStdIncludes.h"
#include "common/_2RealData.h"
#include "bundle/_2RealTypeMetainfo_I.h"

namespace _2Real
{
	class CustomTypeMetainfoImpl;

	namespace bundle
	{
		class CustomTypeMetainfo : public TypeMetainfo_I
		{

		public:

			explicit CustomTypeMetainfo( std::shared_ptr< CustomTypeMetainfoImpl > );

			/*
			*	@return:always true
			*/
			bool isBasicType() const;

			/*
			*	@return: name
			*/
			std::string getName() const;

			/*
			*	set description
			*/
			void setDescription( std::string );

			/*
			*	sets initial value of a field
			*/
			void setInitialFieldValue( std::string const& fieldName, DataItem value );

			/*
			*	creates a custom data item
			*/
			CustomDataItem makeCustomData() const;

			/*
			*	creates a data item
			*/
			DataItem makeData() const;

		private:

			std::shared_ptr< CustomTypeMetainfoImpl >		mImpl;

		};
	}
}