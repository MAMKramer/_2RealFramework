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

#include "_2RealEntity.h"
#include "_2RealGraph.h"
#include "_2RealExceptionHandler.h"
#include "_2RealThreadPool.h"
#include "_2RealPluginPool.h"


#include <map>
#include <list>
#include <fstream>

namespace _2Real
{

	class Data;
	typedef void (*DataCallback)(Data &data);

	typedef std::map< std::string, std::string >	StringMap;

	class IExceptionListener;
	class IOutputListener;
	class Engine;
	class EngineData;

	class SystemGraph : public Graph, public Entity
	{

	public:

		SystemGraph(Identifier const& id);
		~SystemGraph();

		void				shutdown();
		void				stopAll();
		void				startAll();
		void				startChild(Identifier const& runnableId);
		void				stopChild(Identifier const& runnableId);
		void				updateChild(Identifier const& runnableId, unsigned int count);
		const Identifier	install(std::string const& idName, std::string const& classname);
		const Identifier	createService(std::string const& idName, Identifier const& pluginId, std::string const& serviceName);
		bool				contains(Identifier const& id) const;
		void				setup(Identifier const& setupAbleId);
		void				setValue(Identifier const& id, std::string const& paramName, EngineData const& value);
		void				setUpdateRate(Identifier const& id, float updatesPerSecond);
		void				linkSlots(Identifier const& serviceIn, std::string const& nameIn, Identifier const& serviceOut, std::string const& nameOut);
		void				insertChild(Runnable &runnable, unsigned int index);
		void				removeChild(Identifier const& runnableId);
		void				handleException(Runnable &runnable, Exception &exception);
		void				registerExceptionCallback(ExceptionCallback callback);
		void				unregisterExceptionCallback(ExceptionCallback callback);
		void				registerExceptionListener(IExceptionListener &listener);
		void				unregisterExceptionListener(IExceptionListener &listener);
		void				registerToNewData(Identifier const& serviceId, std::string const& outName, DataCallback callback);
		void				unregisterFromNewData(Identifier const& serviceId, std::string const& outName, DataCallback callback);
		void				registerToNewData(Identifier const& serviceId, std::string const& outName, IOutputListener &listener);
		void				unregisterFromNewData(Identifier const& serviceId, std::string const& outName, IOutputListener &listener);

		bool isLoggingEnabled() const;
		void setInstallDirectory(std::string const& directory);
		void setLogfile(std::string const& file);
		std::ofstream & getLogstream();
		StringMap const& getAllowedTypes() const;
		void startLogging();
		const std::string getInfoString(Identifier const& id) const;

	private:

		//whatever you do, don't change the order of the engine and the type table
		Engine					&m_Engine;
		ThreadPool				m_Threads;
		PluginPool				m_Plugins;
		ExceptionHandler		m_ExceptionHandler;
		StringMap				const& m_AllowedTypes;
		std::string				m_Logfile;
		std::ofstream			m_Logstream;

	};

	inline bool SystemGraph::isLoggingEnabled() const
	{
		return m_Logstream.is_open();
	}

	inline std::ofstream & SystemGraph::getLogstream()
	{
		return m_Logstream;
	}

	inline void SystemGraph::setInstallDirectory(std::string const& directory)
	{
		m_Plugins.setInstallDirectory(directory);
	}

	inline StringMap const& SystemGraph::getAllowedTypes() const
	{
		return m_AllowedTypes;
	}

	inline const std::string SystemGraph::getInfoString(Identifier const& id) const
	{
		return m_Plugins.getInfoString(id);
	}

}