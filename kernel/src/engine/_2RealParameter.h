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

#include "engine/_2RealTimestampedData.h"
#include "helpers/_2RealEngineData.h"
#include "helpers/_2RealPoco.h"

namespace _2Real
{

	class AbstractUberBlock;

	class Parameter
	{

	public:

		Parameter( AbstractUberBlock &owningBlock, std::string const& name, std::string const& longTypename, std::string const& typeName );

		std::string const&			getTypename() const;
		std::string const&			getLongTypename() const;
		std::string const&			getName() const;
		AbstractUberBlock &			getOwningUberBlock();

		void						setData( TimestampedData const& data );
		void						synchronize();		// syncs data & write data
		TimestampedData				getData() const;	// must return a copy, b/c could change anytime

	protected:

		mutable Poco::FastMutex		m_DataAccess;
		TimestampedData				m_Data;
		TimestampedData				m_DataBuffer;

		AbstractUberBlock			&m_Owner;
		std::string					const m_LongTypename;
		std::string					const m_Typename;
		std::string					const m_Name;

	};

}