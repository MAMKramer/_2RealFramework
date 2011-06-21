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

#include "Common.h"

/*
	returned by the framework context when a service is registered
	can be used by the plugin activator to unregister a service
*/

namespace _2Real
{
	class ServiceRegistration
	{
	public:

		~ServiceRegistration();
		void unregister();
		
		IService* servicePtr();
		std::string name();

	private:

		PluginFrameworkContext*		m_FrameworkContext;
		IService*					m_Service;
		std::string					m_Name;

		ServiceRegistration(const std::string name, PluginFrameworkContext* fwContext, IService* service);

		friend class PluginFrameworkContext;
	};
}