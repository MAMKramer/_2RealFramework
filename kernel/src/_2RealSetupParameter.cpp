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

#include "_2RealSetupParameter.h"
#include "_2RealParameterMetadata.h"
#include "_2RealException.h"

#include <iostream>
#include <sstream>

namespace _2Real
{

	SetupParameter::SetupParameter(ParameterMetadata const& metadata) :
		Parameter(metadata),
		m_Data()
	{
		if (metadata.hasDefaultValue())
		{
			m_Data = metadata.getDefaultValue();
		}
	}

	void SetupParameter::setData(EngineData const& data)
	{
		if (data.typeinfo().name() != getDatatype())
		{
			std::ostringstream msg;
			msg << "datatype mismatch: " <<  m_Datatype << " vs. template parameter type " << data.typeinfo().name();
			throw TypeMismatchException(msg.str());
		}

		m_Data = data;
		m_IsInitialized = true;
	}

	EngineData const& SetupParameter::getData() const
	{
		return m_Data;
	}

}