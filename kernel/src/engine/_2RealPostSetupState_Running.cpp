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

#include "engine/_2RealPostSetupState_Running.h"

namespace _2Real
{
	PostSetupState_Running::PostSetupState_Running( const BlockState state ) :
		AbstractBlockState( state )
	{
	}

// ----- loop

	std::shared_ptr< SignalResponse > PostSetupState_Running::onStartRunning()
	{
		return makeResponse( Action::DO_NOTHING, BlockState::POST_SETUP_RUNNING, false );
	}

	std::shared_ptr< SignalResponse > PostSetupState_Running::onStopRunning()
	{	
		return makeResponse( Action::DO_NOTHING, BlockState::POST_SETUP, true );
	}

	std::shared_ptr< SignalResponse > PostSetupState_Running::onUpdateSignalReceived()
	{
		return makeResponse( Action::DO_UPDATE, BlockState::POST_SETUP_RUNNING, false );
	}

// ----- user input

	std::shared_ptr< SignalResponse > PostSetupState_Running::onSetupSignalReceived()
	{
		return makeResponse( Action::DO_NOTHING, BlockState::POST_SETUP_RUNNING, false );
	}

	std::shared_ptr< SignalResponse > PostSetupState_Running::onSingleUpdateSignalReceived()
	{
		return makeResponse( Action::DO_NOTHING, BlockState::POST_SETUP_RUNNING, false );
	}

	std::shared_ptr< SignalResponse > PostSetupState_Running::onShutdownSignalReceived()
	{
		return makeResponse( Action::DO_SHUTDOWN, BlockState::POST_SHUTDOWN, true );
	}

// ----- shutdown

	std::shared_ptr< SignalResponse > PostSetupState_Running::onEngineShutdownReceived()
	{
		return makeResponse( Action::DO_NOTHING, BlockState::POST_SHUTDOWN, true );
	}
}
