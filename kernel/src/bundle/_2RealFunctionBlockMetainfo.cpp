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

#include "bundle/_2RealFunctionBlockMetainfo.h"
#include "bundle/_2RealInletMetainfo.h"
#include "bundle/_2RealOutletMetainfo.h"
#include "bundle/_2RealParameterMetainfo.h"
#include "bundle/_2RealDefaultUpdatePolicy.h"
#include "engine/_2RealSharedServiceMetainfo.h"

namespace _2Real
{
	namespace bundle
	{
		FunctionBlockMetainfo::FunctionBlockMetainfo( std::shared_ptr< SharedServiceMetainfo > info ) :
			BlockMetainfo(),
			mImpl( info )
		{
		}

		std::string FunctionBlockMetainfo::getName() const
		{
			return mImpl.lock()->getName();
		}

		void FunctionBlockMetainfo::setBlockClassInternal( std::shared_ptr< AbstractSharedServiceFactory > factory )
		{
			mImpl.lock()->setFactory( factory );
		}

		void FunctionBlockMetainfo::setDescription( std::string const& description )
		{
			mImpl.lock()->setDescription( description );
		}

		OutletMetainfo FunctionBlockMetainfo::getOutletMetainfo( std::string const& name )
		{
			return OutletMetainfo( mImpl.lock()->getOutletMetainfo( name ) );
		}

		InletMetainfo FunctionBlockMetainfo::getInletMetainfo( std::string const& name )
		{
			return InletMetainfo( mImpl.lock()->getInletMetainfo( name ) );
		}

		ParameterMetainfo FunctionBlockMetainfo::getParameterMetainfo( std::string const& name )
		{
			return ParameterMetainfo( mImpl.lock()->getParameterMetainfo( name ) );
		}

		void FunctionBlockMetainfo::setDependencies( std::vector< std::string > const& dependencies )
		{
			mImpl.lock()->setDependencies( dependencies );
		}

		DefaultUpdatePolicy FunctionBlockMetainfo::getDefaultUpdatePolicy()
		{
			return mImpl.lock()->getDefaultUpdatePolicy();
		}
	}
}