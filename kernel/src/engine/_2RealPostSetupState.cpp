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

#include "engine/_2RealPostSetupState.h"
#include "engine/_2RealSignalResponse.h"

namespace _2Real
{
	std::shared_ptr< SignalResponse > PostSetupState::nextAction( std::deque< std::shared_ptr< SignalResponse > > &responses )
	{
		/*assert( !responses.empty() );*/
		if ( responses.empty() ) return nullptr;

		struct PrioritySort
		{
			static uint8_t getPriority( const BlockRequest r )
			{
				switch ( r )
				{
				case BlockRequest::SHUTDOWN:
					return 0;
				default:
					return 1;
				}
			}

			bool operator()( std::shared_ptr< SignalResponse > a, std::shared_ptr< SignalResponse > b ) const
			{
				return getPriority( a->request ) < getPriority( b->request );
			}
		};

		std::stable_sort( responses.begin(), responses.end(), PrioritySort() );

		std::shared_ptr< SignalResponse > response;
		if ( responses.front()->request == BlockRequest::SHUTDOWN )
		{
			response = responses.front();
			responses.pop_front();
			response->action = BlockAction::DO_SHUTDOWN;
			response->followupState = BlockState::POST_SHUTDOWN;
			response->shouldBeQueued = false;
		}
		assert( response.get() );

		for ( auto it : responses )
			it->result.set_value( BlockResult::IGNORED );
		responses.clear();

		return response;
	}

	PostSetupState::PostSetupState( const BlockState state ) :
		mId( state )
	{
	}

	bool PostSetupState::operator==( const BlockState state ) const
	{
		return mId == state;
	}

// ----- loop

	std::shared_ptr< SignalResponse > PostSetupState::onStartRunning()
	{
		return SignalResponse::makeResponse( BlockRequest::START, BlockAction::DO_NOTHING, BlockState::POST_SETUP_RUNNING, false );
	}

	std::shared_ptr< SignalResponse > PostSetupState::onStopRunning()
	{	
		return SignalResponse::makeResponse( BlockRequest::STOP, BlockAction::DO_NOTHING, BlockState::POST_SETUP, false );
	}

	std::shared_ptr< SignalResponse > PostSetupState::onUpdateSignalReceived()
	{
		return SignalResponse::makeResponse( BlockRequest::UPDATE, BlockAction::DO_NOTHING, BlockState::POST_SETUP, false );
	}

// ----- user input

	std::shared_ptr< SignalResponse > PostSetupState::onSetupSignalReceived()
	{	
		return SignalResponse::makeResponse( BlockRequest::SETUP, BlockAction::DO_SETUP, BlockState::POST_SETUP, false );
	}

	std::shared_ptr< SignalResponse > PostSetupState::onSingleUpdateSignalReceived()
	{
		return SignalResponse::makeResponse( BlockRequest::SINGLESTEP, BlockAction::DO_UPDATE, BlockState::POST_SETUP, false );
	}

	std::shared_ptr< SignalResponse > PostSetupState::onShutdownSignalReceived()
	{
		return SignalResponse::makeResponse( BlockRequest::SHUTDOWN, BlockAction::DO_SHUTDOWN, BlockState::POST_SHUTDOWN, true );
	}

// ----- shutdown

	std::shared_ptr< SignalResponse > PostSetupState::onEngineShutdownReceived()
	{
		return SignalResponse::makeResponse( BlockRequest::SHUTDOWN, BlockAction::DO_SHUTDOWN, BlockState::POST_SHUTDOWN, true );
	}
}