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

#include "app/_2RealEngine.h"
#include "app/_2RealBundleHandle.h"
#include "app/_2RealBundleMetainfo.h"
#include "app/_2RealTimerHandle.h"
#include "app/_2RealThreadpoolHandle.h"
#include "app/_2RealLinkHandle.h"
#include "app/_2RealInletHandle.h"
#include "app/_2RealOutletHandle.h"

#include "engine/_2RealEngineImpl.h"
#include "common/_2RealBoost.h"

namespace _2Real
{
	namespace app
	{
		Engine::Engine() :
			mImpl( new EngineImpl )
		{
		}

		Engine::~Engine()
		{
			clear();
		}

		void Engine::clear()
		{
			mImpl->clear();
		}

		Path Engine::getBundleDirectory() const
		{
			return mImpl->getBundleDirectory();
		}

		std::pair< BundleHandle, BundleMetainfo > Engine::loadBundle( std::string const& libname )
		{
			auto result = mImpl->loadLibrary( libname );
			return std::make_pair( BundleHandle( result.first ), BundleMetainfo( result.second ) );
		}

		TimerHandle Engine::createTimer( const double fps )
		{
			auto timer = mImpl->createTimer( fps );
			return TimerHandle( timer );
		}

		ThreadpoolHandle Engine::createThreadpool( const ThreadpoolPolicy policy )
		{
			auto system = mImpl->createThreadpool( policy );
			return ThreadpoolHandle( system );
		}

		LinkHandle Engine::link( InletHandle inlet, OutletHandle outlet )
		{
			if ( inlet.mImpl.lock().get() == nullptr || outlet.mImpl.lock().get() == nullptr )
				throw HandleAccessFailure( "could not create link" );

			auto link = mImpl->createLink( inlet.mImpl.lock(), outlet.mImpl.lock() );
			return LinkHandle( link );
		}
	}
}