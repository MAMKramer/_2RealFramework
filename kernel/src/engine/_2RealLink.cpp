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

#include "engine/_2RealLink.h"
#include "engine/_2RealAbstractIOManager.h"
#include "app/_2RealCallbacksInternal.h"

#include <assert.h>
#include <iostream>

namespace _2Real
{

//	AbstractLink::AbstractLink( Parameter &p1, Parameter &p2 ) :
//		m_Link1( p1 ),
//		m_Link2( p2 )
//	{
//#ifdef _DEBUG
//		if ( &p1 == &p2 )
//		{
//			assert( NULL );
//		}
//#endif
//	}
//
//	bool AbstractLink::operator<( AbstractLink const& other )
//	{
//		return ( &m_Link1 < &other.m_Link1 && &m_Link2 < &other.m_Link2 );
//	}

	IOLink::IOLink( InletIO &inlet, OutletIO &outlet ) :
		m_InletIO( inlet ),
		m_OutletIO( outlet )
	{
	}

	bool IOLink::operator<( IOLink const& other )
	{
		return ( m_InletIO.m_Inlet < other.m_InletIO.m_Inlet && m_OutletIO.m_Outlet < other.m_OutletIO.m_Outlet );
	}

	void IOLink::activate() 
	{
		AbstractCallback< TimestampedData const& > *cb = new MemberCallback< InletBuffer, TimestampedData const& >( *m_InletIO.m_Buffer, &InletBuffer::receiveData );
		m_OutletIO.m_InletEvent->addListener( *cb );
	}

	void IOLink::deactivate()
	{
		AbstractCallback< TimestampedData const& > *cb = new MemberCallback< InletBuffer, TimestampedData const& >( *m_InletIO.m_Buffer, &InletBuffer::receiveData );
		m_OutletIO.m_InletEvent->removeListener( *cb );
	}

}