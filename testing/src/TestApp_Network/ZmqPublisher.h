 /*
	CADET - Center for Advances in Digital Entertainment Technologies
	Copyright 2012 Fachhochschule Salzburg GmbH

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

#include "ZmqNetworking.h"
#include "_2RealApplication.h"

namespace _2Real
{
	namespace network
	{
		class Publisher
		{

		public:
		
			Publisher( Publisher const& ) = delete;
			Publisher( Publisher && ) = delete;

			static std::shared_ptr< Publisher > create( std::string const& address, _2Real::app::Engine &engine, _2Real::app::ThreadpoolHandle threadpool );

			// !!!!! assumption: message contains space for header ( see Serializer ctor -> bytesToSkip )
			// also, will be altered ( header copied into msg )
			// is a shared ptr because thats what the setter function expects
			void publish( std::string const& topic, std::shared_ptr< _2Real::DataItem > message );

		private:

			Publisher( _2Real::app::BlockHandle sender );
			~Publisher() = default;

			_2Real::app::BlockHandle							mUnderlyingBlock;
			std::map< std::string, _2Real::app::InletHandle >	mTopics;

			// deleter for shared ptr
			struct Deleter
			{
				void operator()( Publisher *& pub );
			};

		};
	}
}
