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

#include "app/_2RealMultiInletHandle.h"
#include "app/_2RealInletHandle.h"
#include "app/_2RealBlockHandle.h"
#include "engine/_2RealMultiInletImpl.h"
#include "common/_2RealWeakPtrCheck.h"

namespace _2Real
{
	namespace app
	{
		MultiInletHandle::MultiInletHandle( std::shared_ptr< MultiInletImpl > inlet ) :
			InletHandle_I(),
			mImpl( inlet )
		{
		}

		bool MultiInletHandle::isValid() const
		{
			std::shared_ptr< MultiInletImpl > inlet = mImpl.lock();
			return ( nullptr != inlet.get() );
		}

		bool MultiInletHandle::isMultiInlet() const
		{
			std::shared_ptr< MultiInletImpl > inlet = checkValidity< MultiInletImpl >( mImpl, "multiinlet" );
			return true;
		}
		
		BlockHandle MultiInletHandle::getBlock()
		{
			std::shared_ptr< MultiInletImpl > inlet = checkValidity< MultiInletImpl >( mImpl, "inlet" );
			return BlockHandle( inlet->getParent() );
		}

		InletHandle MultiInletHandle::operator[]( const uint32_t index )
		{
			std::shared_ptr< MultiInletImpl > inlet = checkValidity< MultiInletImpl >( mImpl, "multiinlet" );
			return InletHandle( inlet->operator[]( index ) );
		}

		uint32_t MultiInletHandle::getSize() const
		{
			std::shared_ptr< MultiInletImpl > inlet = checkValidity< MultiInletImpl >( mImpl, "multiinlet" );
			return inlet->getSize();
		}

		bool MultiInletHandle::isEmpty() const
		{
			std::shared_ptr< MultiInletImpl > inlet = checkValidity< MultiInletImpl >( mImpl, "multiinlet" );
			return inlet->isEmpty();
		}

		InletHandle MultiInletHandle::add()
		{
			std::shared_ptr< MultiInletImpl > inlet = checkValidity< MultiInletImpl >( mImpl, "multiinlet" );
			return InletHandle( inlet->add_back() );
		}

		void MultiInletHandle::remove( InletHandle subinlet )
		{
			std::shared_ptr< MultiInletImpl > inlet = checkValidity< MultiInletImpl >( mImpl, "multiinlet" );
			std::shared_ptr< InletImpl > sub = subinlet.mImpl.lock();
			inlet->remove( sub );
		}
	}
}
