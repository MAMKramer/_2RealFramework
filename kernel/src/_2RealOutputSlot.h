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

#include "_2RealIOSlot.h"
#include "_2RealData.h"

#include "Poco\Mutex.h"
#include "Poco\BasicEvent.h"
#include "Poco\Timestamp.h"

namespace _2Real
{

	/**
	*	represents an output slot of a service
	*/

	class InputSlot;

	typedef void (*DataCallback)(Data &_data);

	class OutputSlot : public IOSlot
	{

	public:

		OutputSlot(Id *const id, Service *const service, std::string const& type, std::string const& key, SharedAny init);
		virtual ~OutputSlot();

		void init(SharedAny const& initialValue);

		InputSlot *const linkedInput()
		{
			return m_Input;
		}

		InputSlot const *const linkedInput() const
		{
			return m_Input;
		}

		const bool isLinked() const
		{
			if (m_Input)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		SharedAny data()
		{
			return m_WriteData;
		}

		void registerCallback(DataCallback callback);
		void unregisterCallback(DataCallback callback);

	private:

		friend class Service;
		friend class Engine;

		void update();
		void addListener(InputSlot *listener);

		InputSlot								*m_Input;

		Poco::FastMutex							m_Mutex;

		Data									m_CurrentData;

		SharedAny								m_WriteData;

		Poco::BasicEvent< Data >				m_Event;

	};

}