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

#include "_2RealServiceMetadata.h"
#include "_2RealPluginMetadata.h"
#include "_2RealException.h"

#include <sstream>
#include <iostream>

namespace _2Real
{

	ServiceMetadata::ServiceMetadata(std::string const& _name) :
		m_ServiceName(_name),
		m_bIsSingleton(false),
		m_bCanReconfigure(false),
		m_SetupParams(),
		m_InputParams(),
		m_OutputParams()
	{

	}

	void ServiceMetadata::setDescription(std::string const& _desc)
	{
		m_Description = _desc;
	}

	void ServiceMetadata::setReconfiguration(bool const& _config)
	{
		m_bCanReconfigure = _config;
	}

	void ServiceMetadata::setSingleton(bool const& _singleton)
	{
		m_bIsSingleton = _singleton;
	}

	void ServiceMetadata::addSetupParam(std::string const& _name, std::string const& _type)
	{
		ParamMetadata::ParamMap::iterator it = m_SetupParams.find(_name);

		if (it != m_SetupParams.end())
		{
			throw Exception("setup parameter " + _name + " already exists");
		}

		m_SetupParams.insert(ParamMetadata::NamedParam(_name, ParamMetadata(_name, _type)));
	}

	void ServiceMetadata::addInputParam(std::string const& _name, std::string const& _type)
	{
		ParamMetadata::ParamMap::iterator it = m_InputParams.find(_name);

		if (it != m_InputParams.end())
		{
			throw Exception("input slot " + _name + " already exists");
		}

		m_InputParams.insert(ParamMetadata::NamedParam(_name, ParamMetadata(_name, _type)));
	}

	void ServiceMetadata::addOutputParam(std::string const& _name, std::string const& _type)
	{
		ParamMetadata::ParamMap::iterator it = m_OutputParams.find(_name);

		if (it != m_OutputParams.end())
		{
			throw Exception("output slot " + _name + " already exists");
		}

		m_OutputParams.insert(ParamMetadata::NamedParam(_name, ParamMetadata(_name, _type)));
	}

	ParamMetadata::StringMap ServiceMetadata::getInputParams() const
	{
		ParamMetadata::StringMap result;
		for (ParamMetadata::ParamMap::const_iterator it = m_InputParams.begin(); it !=m_InputParams.end(); it++)
		{
			ParamMetadata data = it->second;
			result.insert(std::make_pair(data.getName(), data.getType()));
		}
		return result;
	}

	ParamMetadata::StringMap ServiceMetadata::getOutputParams() const
	{
		ParamMetadata::StringMap result;
		for (ParamMetadata::ParamMap::const_iterator it = m_OutputParams.begin(); it !=m_OutputParams.end(); it++)
		{
			ParamMetadata data = it->second;
			result.insert(std::make_pair(data.getName(), data.getType()));
		}
		return result;
	}

	ParamMetadata::StringMap ServiceMetadata::getSetupParams() const
	{
		ParamMetadata::StringMap result;
		for (ParamMetadata::ParamMap::const_iterator it = m_SetupParams.begin(); it !=m_SetupParams.end(); it++)
		{
			ParamMetadata data = it->second;
			result.insert(std::make_pair(data.getName(), data.getType()));
		}
		return result;
	}

	std::string const& ServiceMetadata::getName() const
	{
		return m_ServiceName;
	}

	std::string const& ServiceMetadata::getDescription() const
	{
		return m_Description;
	}

	bool const& ServiceMetadata::canReconfigure() const
	{
		return m_bCanReconfigure;
	}

	bool const& ServiceMetadata::isSingleton() const
	{
		return m_bIsSingleton;
	}

	const bool ServiceMetadata::hasSetupParam(std::string const& _name) const
	{
		ParamMetadata::ParamMap::const_iterator it = m_SetupParams.find(_name);

		if (it != m_SetupParams.end())
		{
			return false;
		}

		return true;
	}

	const bool ServiceMetadata::hasInputParam(std::string const& _name) const
	{
		ParamMetadata::ParamMap::const_iterator it = m_InputParams.find(_name);

		if (it != m_InputParams.end())
		{
			return false;
		}

		return true;
	}

	const bool ServiceMetadata::hasOuputParam(std::string const& _name) const
	{
		ParamMetadata::ParamMap::const_iterator it = m_OutputParams.find(_name);

		if (it != m_OutputParams.end())
		{
			return false;
		}

		return true;
	}

	const std::string ServiceMetadata::info() const
	{
		std::stringstream info;
		info << std::endl;
		info << m_ServiceName << std::endl;
		info << m_Description << std::endl;

		//if (m_bIsSingleton)
		//{
		//	info << "this service is a singleton" << std::endl;
		//}

		//if (m_bCanReconfigure)
		//{
		//	info << "this service's setup parameters can be reconfigured" << std::endl;
		//}
		//else
		//{
		//	info << "this service's setup parameters can be initialized only once" << std::endl;
		//}

		if (!m_SetupParams.empty())
		{
			info << "this service has setup parameters: " << std::endl;
			for (ParamMetadata::ParamMap::const_iterator it = m_SetupParams.begin(); it != m_SetupParams.end(); it++)
			{
				info << it->first << std::endl;
			}
		}

		if (!m_InputParams.empty())
		{
			info << "this service has input parameters: " << std::endl;
			for (ParamMetadata::ParamMap::const_iterator it = m_InputParams.begin(); it != m_InputParams.end(); it++)
			{
				info << it->first << std::endl;
			}
		}

		if (!m_OutputParams.empty())
		{
			info << "this service has output parameters: " << std::endl;
			for (ParamMetadata::ParamMap::const_iterator it = m_OutputParams.begin(); it != m_OutputParams.end(); it++)
			{
				info << it->first << std::endl;
			}
		}

		return info.str();
	}

}