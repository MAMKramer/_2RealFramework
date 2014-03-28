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

#include "engine/_2RealData.h"

#include <memory>
#include <string>

namespace _2Real
{
	class Parameter;

	namespace bundle
	{
		class ParameterHandle
		{

		public:

			explicit ParameterHandle( std::shared_ptr< const Parameter > );

			std::string const& getName() const;

			DataItem const& getValue() const;

		private:

			std::shared_ptr< const Parameter >		mImpl;

		};
	}
}