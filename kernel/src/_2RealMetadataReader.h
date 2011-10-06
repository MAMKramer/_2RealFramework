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

#include <string>
#include <map>
#include <vector>
#include <typeinfo>

namespace Poco
{
	namespace XML
	{
		class NamedNodeMap;
		class Node;
	}
}

namespace _2Real
{

	/**
	*	helper class for reading plugin metadata
	*/

	class PluginMetadata;

	class MetadataReader
	{

	public:

		/**
		*	creates plugin metadata from xml file
		*
		*	reads xml file located in plugin directory with given name,
		*	attempts to build plugin metadata from information
		*	contained in the file. if successful, returns metadata.
		*
		*	@param _info:			metadata initialized with classname & classpath
		*	@throw:					definitions TODO
		*/
		void readMetadata(PluginMetadata &info);

	private:

		/**
		*
		*/
		static std::map< std::string, std::string >		s_Typenames;

		void											processPluginNode(PluginMetadata &info, Poco::XML::Node *const plugin);

		void											processServiceNode(PluginMetadata &info, Poco::XML::Node *const service);

		Poco::XML::Node *const							getChildNode(std::string const& name, Poco::XML::Node *const parent);

		const std::string								getTypename(std::string const& type) const;

		const std::string								getParameterType(Poco::XML::Node *const attrib);

		const std::string								getNodeAttribute(std::string const& name, Poco::XML::Node *const node);

	};

}