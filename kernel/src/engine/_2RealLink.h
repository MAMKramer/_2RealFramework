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

#pragma once

#include "common/_2RealStdIncludes.h"
#include "common/_2RealData.h"
#include "common/_2RealSignals.h"

#include "engine/_2RealDataSink_I.h"
#include "engine/_2RealDataSource_I.h"

namespace _2Real
{
	class Link : public DataSink_I, public DataSource_I, public std::enable_shared_from_this< Link >
	{

	public:

		static std::shared_ptr< Link > createLink( std::shared_ptr< DataSink_I >, std::shared_ptr< DataSource_I > );

		Link() = default;
		~Link() = default;

		Link( Link const& other ) = delete;
		Link( Link && other ) = delete;
		Link& operator=( Link const& other ) = delete;
		Link& operator=( Link && other ) = delete;

		void linkTo( std::shared_ptr< DataSource_I > );
		void receiveData( std::shared_ptr< const DataItem > );

		boost::signals2::connection registerToUpdate( boost::signals2::signal< void( std::shared_ptr< const DataItem > ) >::slot_type ) const;
		boost::signals2::connection registerToDestroyed( boost::signals2::signal< void( std::shared_ptr< const Link > ) >::slot_type ) const;
		boost::signals2::connection registerToRemoved( boost::signals2::signal< void( std::shared_ptr< const DataSource_I > ) >::slot_type ) const;
		boost::signals2::connection registerToRemoved( boost::signals2::signal< void( std::shared_ptr< const DataSink_I > ) >::slot_type ) const;

		void sinkRemoved();
		void sourceRemoved();
		void destroy();

	private:

		boost::signals2::connection		mDataConnection;
		boost::signals2::connection		mSinkRemovedConnection;
		boost::signals2::connection		mSourceRemovedConnection;
		mutable boost::signals2::signal< void( std::shared_ptr< const DataItem > ) >		mData;
		mutable boost::signals2::signal< void( std::shared_ptr< const Link > ) >			mDestroyed;
		mutable boost::signals2::signal< void( std::shared_ptr< const DataSource_I > ) >	mSourceRemoved;
		mutable boost::signals2::signal< void( std::shared_ptr< const DataSink_I > ) >		mSinkRemoved;

	};
}
