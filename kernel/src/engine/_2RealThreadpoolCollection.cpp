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

#include "engine/_2RealThreadpoolCollection.h"
#include "engine/_2RealThreadpool.h"

namespace _2Real
{
	ThreadpoolCollection::ThreadpoolCollection() :
		std::enable_shared_from_this< ThreadpoolCollection >()
	{
	}

	ThreadpoolCollection::~ThreadpoolCollection()
	{
		for ( auto it : mThreadpools )	
		{
			it.reset();
		}
	}

	std::shared_ptr< Threadpool > ThreadpoolCollection::createThreadpool( const ThreadpoolPolicy p )
	{
		auto threadpool = Threadpool::create( p );
		mThreadpools.insert( threadpool );
		return threadpool;
	}
}