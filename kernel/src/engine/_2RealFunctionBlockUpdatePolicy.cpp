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

#include "engine/_2RealFunctionBlockUpdatePolicy.h"
#include "engine/_2RealEngineImpl.h"
#include "engine/_2RealInletBuffer.h"
#include "engine/_2RealFunctionBlock.h"
#include "engine/_2RealFunctionBlockStateManager.h"
#include "engine/_2RealFunctionBlockIOManager.h"
#include "engine/_2RealParameterData.h"

using std::string;
using std::make_pair;
using std::greater;
using std::shared_ptr;

#include <assert.h>
#include <iostream>

namespace _2Real
{

	FunctionBlockUpdatePolicy::InletPolicy::~InletPolicy()
	{
		delete m_Ctor;
		delete m_Trigger;
	}

	FunctionBlockUpdatePolicy::FunctionBlockUpdatePolicy( FunctionBlock &owner ) :
		AbstractUpdatePolicy( owner ),
		m_TimeChanged( false ),
		m_InletsChanged( false ),
		m_UpdateTime( -1 ),
		m_TimeTrigger( nullptr )
	{
	}

	FunctionBlockUpdatePolicy::~FunctionBlockUpdatePolicy()
	{
		if ( m_TimeTrigger != nullptr )
		{
			delete m_TimeTrigger;
		}
	}

	void FunctionBlockUpdatePolicy::addInlet( InletIO &inletIO )
	{
		Poco::ScopedLock< Poco::FastMutex > lock( m_Access );
#ifdef _DEBUG
		if ( m_InletPolicies.find( &inletIO ) != m_InletPolicies.end() )
		{
			assert( NULL );
		}
#endif
		m_InletsChanged = true;
		InletPolicy *p = new InletPolicy();
		p->m_Ctor = new InletTriggerCtor< ValidData, false >();
		p->m_Trigger = nullptr;
		p->m_WasChanged = true;
		m_InletPolicies.insert( make_pair( &inletIO, p ) );
	}

	void FunctionBlockUpdatePolicy::changePolicy()
	{
		Poco::ScopedLock< Poco::FastMutex > lock( m_Access );

		if ( ! ( m_TimeChanged || m_InletsChanged ) ) return;

		if ( m_TimeChanged )
		{
			if ( m_TimeTrigger != nullptr )
			{
				delete m_TimeTrigger;
				m_TimeTrigger = nullptr;
			}
			if ( m_UpdateTime > 0 )
			{
				m_TimeTrigger = new TimeBasedTrigger< std::greater< long > >( *m_StateManager, m_UpdateTime );
			}

			m_TimeChanged = false;
		}

		if ( m_InletsChanged )
		{
			for ( InletPolicyIterator it = m_InletPolicies.begin(); it != m_InletPolicies.end(); ++it )
			{
				if ( it->second->m_WasChanged )
				{
					InletBuffer *buffer = it->first->m_Buffer;
					AbstractInletTriggerCtor *ctor = it->second->m_Ctor;
					AbstractInletBasedTrigger *currTrigger = it->second->m_Trigger;
					AbstractInletBasedTrigger *newTrigger = ctor->createTrigger( *buffer, *m_StateManager );

					if ( currTrigger != nullptr )
					{
						*newTrigger = *currTrigger;		// copies the triggering data + timestamp
					}

					delete currTrigger;
					currTrigger = newTrigger;

					it->second->m_WasChanged = false;
				}
			}
			m_InletsChanged = false;
		}
	}

	void FunctionBlockUpdatePolicy::setNewUpdateTime( const long time )
	{
		Poco::ScopedLock< Poco::FastMutex > lock( m_Access );
		m_TimeChanged = true;
		m_UpdateTime = time;
	}

	//void FunctionBlockUpdatePolicy::setNewInletDefaultPolicy( InletTriggerCtor &inletDefault )
	//{
	//	Poco::ScopedLock< Poco::FastMutex > lock( m_Access );
	//	m_WasChanged = true;
	//	for ( InletPolicyMap::iterator it = m_InletPolicies.begin(); it != m_InletPolicies.end(); ++it )
	//	{
	//		it->second = inletDefault;
	//	}
	//}

	void FunctionBlockUpdatePolicy::setNewInletPolicy( InletIO &io, AbstractInletTriggerCtor *inletPolicy )
	{
		Poco::ScopedLock< Poco::FastMutex > lock( m_Access );
		m_InletsChanged = true;
		InletPolicyIterator it = m_InletPolicies.find( &io );
		if ( it != m_InletPolicies.end() )
		{
			it->second->m_WasChanged = true;
			delete it->second->m_Ctor;
			it->second->m_Ctor = inletPolicy;
		}
	}

}