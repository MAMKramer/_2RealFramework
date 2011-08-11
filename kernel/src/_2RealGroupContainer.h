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

#include "_2RealTypedefs.h"

#include "_2RealAbstractContainer.h"

#include <list>

#include "Poco/ThreadPool.h"

/*
	container which contains not a service, but a number > 1 of other containers
	sequence container & synchronization container are derived off this
*/

namespace _2Real
{
	class GroupContainer : public AbstractContainer
	{

	public:

		GroupContainer(ServiceName const& _name) : AbstractContainer(_name) {}

		void start(bool const& _loop);
		void stop();
		void run();

		/**
		*	calls setup function of all child containers
		*	does nothing & returns false if container is already configured
		*	otherwise, returns true only if all child containers were successfully configured
		*/
		const bool setup(ConfigurationData *const _config);
		
		/**
		*	calls update function of all child containers
		*	does nothing if container is not configured
		*/
		virtual void update() = 0;

		/**
		*	calls shutdown function of all child containers
		*/
		void shutdown();

		/**
		*	adds _container to child container list;
		*	if container with same name already exists in the list, does nothing & returns false
		*	if this group container is already configured, does nothing & returns false
		*/
		bool addElement(ContainerPtr _container);
		
		/**
		*	listener functions are not used in group containers
		*/
		void addListener(ServicePtr &_listener) {}
		void removeListener(ServicePtr &_listener) {}
		void serviceListener(DataPtr &_input) {}

	protected:

		typedef std::list< ContainerPtr >	ContainerList;

		Poco::ThreadPool					m_ThreadPool;

		ContainerList						m_Containers;

	};
}