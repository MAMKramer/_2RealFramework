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

#include "_2RealIdentifier.h"
#include "_2RealException.h"

#include <list>

#include "Poco/BasicEvent.h"

namespace _2Real
{

	class IExceptionListener;
	class RunnableError;

	typedef void (*ExceptionCallback)(RunnableError &exception);

	class ExceptionHandler
	{

	public:

		ExceptionHandler(Identifier const& system);
		void registerExceptionCallback(ExceptionCallback callback);
		void unregisterExceptionCallback(ExceptionCallback callback);
		void registerExceptionListener(IExceptionListener &listener);
		void unregisterExceptionListener(IExceptionListener &listener);
		void handleException(Exception const& exception, Identifier const& sender);

	private:

		Poco::BasicEvent< RunnableError >	m_Event;

		Identifier							const m_System;

	};
}