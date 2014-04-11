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

#include "engine/_2RealOutlet.h"
#include "engine/_2RealBlock.h"
#include "engine/_2RealIoSlotMetainfo.h"
#include "engine/_2RealId.h"

namespace _2Real
{

	std::shared_ptr< Outlet > Outlet::createFromMetainfo( std::shared_ptr< Block > parent, std::shared_ptr< const IoSlotMetainfo > meta )
	{
		std::shared_ptr< const InstanceId > outletId = InstanceId::create( meta->getId(), parent->getId(), InstanceType::IOSLOT, meta->getId()->getName() );
		std::shared_ptr< Outlet > outlet( new Outlet( parent, meta, outletId ) );

		return outlet;
	}

	Outlet::Outlet( std::shared_ptr< Block > parent, std::shared_ptr< const IoSlotMetainfo > meta, std::shared_ptr< const InstanceId > id ) :
		DataSource(),
		std::enable_shared_from_this< Outlet >(),
		mParent( parent ),
		mMetainfo( meta ),
		mId( id ),
		mTmpValue( new DataItem( meta->getInitialValue() ) ),
		mValue( new DataItem( meta->getInitialValue() ) )
	{
	}

	std::shared_ptr< const InstanceId > Outlet::getId() const
	{
		return mId;
	}

	std::shared_ptr< Block > Outlet::getParent()
	{
		return mParent.lock();
	}

	DataItem & Outlet::getValue()
	{
		return *mValue.get();
	}

	void Outlet::update()
	{
		std::lock_guard< std::mutex > lock( mMutex );
		mTmpValue = mValue;
		mValue.reset( new DataItem( mMetainfo.lock()->getInitialValue() ) );
		DataSource::notify( mTmpValue );
	}
}
