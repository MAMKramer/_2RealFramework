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

#include "_2RealInputHandle.h"
#include "_2RealOutputHandle.h"
#include "_2RealSharedAny.h"

#include <string>

namespace _2Real
{

	/**
	*	a service's means of communicating with the framework
	*/

	class Service;

	class ServiceContext
	{

	public:

		/**
		*	creates an input handle for an input slot
		*	
		*	@param name:	name of slot
		*	@return:		input handle
		*	@throw:			InvalidParameterException
		*/
		InputHandle getInputHandle(std::string const& name);

		/**
		*	creates an output handle for an output slot
		*	
		*	@param name:	name of slot
		*	@return:		output handle
		*	@throw:			InvalidParameterException
		*/
		OutputHandle getOutputHandle(std::string const& name);

		/**
		*	returns the value of a setup parameter
		*	
		*	@param name:		name of a setup parameter
		*	@return:			constant reference to setup parameter
		*	@throw:				InvalidParameterException, DatatypeMismatchException
		*/
		template< typename Datatype >
		Datatype const& getParameterValue(std::string const& name)
		{
			Poco::SharedPtr< Datatype > ptr = Extract< Datatype >(getSetupParameter(name));
			return *ptr.get();
		}
	
	private:

		friend class Service;

		ServiceContext(Service *const container);
		ServiceContext(ServiceContext const& src);
		ServiceContext& operator=(ServiceContext const& src);
		~ServiceContext();

		SharedAny			getSetupParameter(std::string const& name);

		Service				*const m_Service;

	};

}