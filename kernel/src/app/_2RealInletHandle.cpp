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

#include "app/_2RealInletHandle.h"
#include "app/_2RealBlockHandle.h"

#include "engine/_2RealInletImpl.h"

#include "common/_2RealWeakPtrCheck.h"

namespace _2Real
{
	namespace app
	{
		InletHandle::InletHandle( std::shared_ptr< InletImpl > inlet ) :
			InletHandle_I(),
			mImpl( inlet )
		{
		}

		bool InletHandle::isValid() const
		{
			std::shared_ptr< InletImpl > inlet = mImpl.lock();
			return ( nullptr != inlet.get() );
		}

		bool InletHandle::isMultiInlet() const
		{
			std::shared_ptr< InletImpl > inlet = checkValidity< InletImpl >( mImpl, "inlet" );
			return false;
		}

		BlockHandle InletHandle::getBlock()
		{
			std::shared_ptr< InletImpl > inlet = checkValidity< InletImpl >( mImpl, "inlet" );
			return BlockHandle( inlet->getParent() );
		}

		void InletHandle::setValue( std::shared_ptr< const DataItem > value )
		{
			std::shared_ptr< InletImpl > inlet = checkValidity< InletImpl >( mImpl, "inlet" );
			inlet->receiveData( value );
		}
	}
}