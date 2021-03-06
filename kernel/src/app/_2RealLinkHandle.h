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

/*
*	links represent connections between inlets and outlets: when an outlet changes its value
*	( right after a block update ), the inlet will receive this value.
*/

namespace _2Real
{
	class Link;

	namespace app
	{
		class LinkHandle
		{

		public:

			/*
			*	create by engine via Engine::link
			*/
			explicit LinkHandle( std::shared_ptr< Link > );

			/*
			*	 @return: true id underlying object is still valid ( LinkHandle::destroy, removing the inlet or oulet OR destrying the engine will remove a link )
			*/
			bool			isValid() const;
			
			/*
			*	destroys the underlying object
			*/
			void			destroy();

		private:

			std::weak_ptr< Link >		mImpl;

		};
	}
}