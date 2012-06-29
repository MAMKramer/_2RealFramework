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

#include "_2RealEngineData.h"
#include "_2RealException.h"

#include <sstream>

namespace _2Real
{
	class Parameter;

	namespace bundle
	{
		class ParameterHandle
		{

		public:

			ParameterHandle();
			ParameterHandle( Parameter const& parameter );

			template< typename Datatype >
			Datatype const& getReadableRef() const
			{
				if ( m_Parameter == nullptr )
				{
					std::ostringstream msg;
					msg << "parameter handle not initialized";
					throw UninitializedHandleException( msg.str() );
				}

				EngineData curr = getParameterValue();
				Datatype const& data = extractFrom< Datatype >( curr );
				return data;
			}

		private:

			EngineData		getParameterValue() const;
			Parameter		const* m_Parameter;

		};
	}
}