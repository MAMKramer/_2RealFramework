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

#include "engine/_2RealTimerCollection.h"
#include "engine/_2RealTimer.h"

namespace _2Real
{
	TimerCollection::TimerCollection() :
		std::enable_shared_from_this< TimerCollection >(),
		mIoService(),
		mWork( new boost::asio::io_service::work( mIoService ) ),
		mThread( &TimerCollection::run, this )
	{
		
	}

	TimerCollection::~TimerCollection()
	{
		std::cout << "cleaning up timers" << std::endl;

		for ( auto it : mTimers )
		{
			it->stop();
			it.reset();
		}

		mWork.reset();
		mThread.join();

		std::cout << "cleaned up timers" << std::endl;
	}

	void TimerCollection::run()
	{
		mIoService.run();
	}

	std::shared_ptr< Timer > TimerCollection::createTimer( const double fps )
	{
		uint64_t period = static_cast< uint64_t >( 1000 / fps );
		std::shared_ptr< Timer > timer( new Timer( mIoService, period ) );
		mTimers.insert( timer );
		return timer;
	}
}
