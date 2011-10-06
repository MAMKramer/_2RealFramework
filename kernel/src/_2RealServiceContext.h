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

#include "_2RealParamRef.h"

#include <string>
#include <typeinfo>

namespace _2Real
{

	/**
	*	a service's means of communicating with the framework
	*	allows for querying of setup params & registration of input / output slots
	*/

	class ServiceContext
	{

	public:

		/**
		*	registers a reference to an input variable in the framework
		*	name & type must match some input parameter defined in plugin metadata
		*/
		template< typename T >
		void registerInputSlot(std::string const& name, T &var)
		{
			try
			{
				AbstractRef *value = new ParamRef< T >(var);
				registerInputSlot(name, value);
			}
			catch (Exception &e)
			{
				throw e;
			}
		}

		/**
		*	registers a reference to an output variable in the framework
		*	name & type must match some output parameter defined in plugin metadata
		*/
		template< typename T >
		void registerOutputSlot(std::string const& name, T &var)
		{
			try
			{
				AbstractRef *value = new ParamRef< T >(var);
				registerOutputSlot(name, value);
			}
			catch (Exception &e)
			{
				throw e;
			}
		}

		/**
		*	retrieves the value of a setup parameter from the framework
		*	name & type must match some setup parameter defined in plugin metadata
		*/
		template< typename T >
		void getSetupParameter(std::string const& name, T &param)
		{
			try
			{
				AbstractRef *value = new ParamRef< T >(param);
				getSetupParameter(name, value);
			}
			catch (Exception &e)
			{
				throw e;
			}
		}
	
	private:

		friend class ServiceContainer;

		/**
		*	
		*/
		ServiceContext(ServiceContainer *const _impl);

		/**
		*
		*/
		ServiceContext(ServiceContext const& _src);

		/**
		*
		*/
		ServiceContext& operator=(ServiceContext const& _src);

		/**
		*	
		*/
		~ServiceContext();

		/**
		*	internally used method for retrieving setup params
		*/
		void getSetupParameter(std::string const& _name, AbstractRef *const _var);

		/**
		*	internally used method for registering input slots
		*/
		void registerInputSlot(std::string const& _name, AbstractRef *const _var);

		/**
		*	internally used method for registering output slots
		*/
		void registerOutputSlot(std::string const& _name, AbstractRef *const _param);

		/**
		*	
		*/
		ServiceContainer			*m_Container;

	};

}