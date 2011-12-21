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

#include "_2RealOutputHandle.h"
#include "_2RealOutputSlot.h"
#include "_2RealEngineData.h"

namespace _2Real
{

	OutputHandle::OutputHandle() :
		ParameterHandle(""),
		m_Output(NULL)
	{
	}

	OutputHandle::OutputHandle(OutputSlot &slot) :
		ParameterHandle(slot.getName()),
		m_Output(&slot)
	{
	}

	OutputHandle::OutputHandle(OutputHandle const& src) :
		ParameterHandle(src),
		m_Output(src.m_Output)
	{
	}

	OutputHandle& OutputHandle::operator=(OutputHandle const& src)
	{
		ParameterHandle::operator=(src);
		m_Output = src.m_Output;

		return *this;
	}

	EngineData OutputHandle::data()
	{
		return m_Output->getData();
	}

}