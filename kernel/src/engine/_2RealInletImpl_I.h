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

#include "common/_2RealStdIncludes.h"

namespace _2Real
{
	class InstanceId;
	class BlockImpl;

	class InletImpl_I
	{

	public:

		InletImpl_I() = default;
		virtual ~InletImpl_I() = default;

		InletImpl_I( InletImpl_I const& other ) = delete;
		InletImpl_I( InletImpl_I && other ) = delete;
		InletImpl_I& operator=( InletImpl_I const& other ) = delete;
		InletImpl_I& operator=( InletImpl_I && other ) = delete;

		virtual bool									isMultiInlet() const = 0;
		virtual std::shared_ptr< const InstanceId >		getId() const = 0;
		virtual std::shared_ptr< BlockImpl >			getParent() = 0;
		virtual void									update() = 0;

	};
}