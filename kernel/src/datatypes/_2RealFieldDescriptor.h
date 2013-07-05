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

#include "datatypes/_2RealAbstractFieldDescriptor.h"
//#include "datatypes/_2RealAnyHolder.h"
#include "datatypes/_2RealTypes.h"
#include "datatypes/_2RealBaseTypes.h"
#include "datatypes/_2RealCustomData.h"
#include "datatypes/_2RealCustomBase.h"
#include "datatypes/_2RealFields.h"
#include "engine/_2RealTypeMetadata.h"

namespace _2Real
{
	class TypeMetadata;
	class AbstractAnyHolder;

	template< typename TType >
	class FieldDescriptor_t : public FieldDescriptor
	{

	public:

		FieldDescriptor_t( TType const& initValue ) :
			FieldDescriptor(),
			mInitValue ( new TType( initValue ) )
		{
			if ( BaseType< TType >::isBaseType() )
				mMetadata = nullptr;
			else
				mMetadata = CustomDerivedType< TType >::getTypeMetadata();
		}

		~FieldDescriptor_t()
		{
			delete mMetadata;
			delete mInitValue;
		}

		AbstractAnyHolder * createAnyHolder() const
		{
			return new AnyHolder< TType >( *mInitValue );
		}

		Field * getField() const
		{
			if ( BaseType< TType >::isBaseType() )
			{
				SimpleField *f = new SimpleField;
				f->mType = Name< TType >::humanReadableName();
				return f;
			}
			else if ( CustomDerivedType< TType >::isCustomDerived() )
			{
				ComplexField *f = new ComplexField;
				f->mType = Name< TType >::humanReadableName();
				mMetadata->getFields( f->mFields );
				return f;
			}

#ifdef _DEBUG
			assert( NULL );
#endif
			return nullptr;
		}

	private:

		TypeMetadata					const* mMetadata;
		TType							*mInitValue;

	};

	template< >
	class FieldDescriptor_t< CustomType > : public FieldDescriptor
	{

	public:

		FieldDescriptor_t( TypeMetadata const* metadata ) :
			FieldDescriptor(),
			mInitValue( new CustomType( *metadata ) ),
			mMetadata( metadata )
		{
		}

		~FieldDescriptor_t()
		{
			delete mInitValue;
		}

		AbstractAnyHolder * createAnyHolder() const
		{
			return new AnyHolder< CustomType >( *mInitValue );
		}

		Field * getField() const
		{
			ComplexField *f = new ComplexField;
			f->mType = "CustomType";				// not good
			mMetadata->getFields( f->mFields );
			return f;
		}

	private:

		TypeMetadata					const* mMetadata;
		CustomType						*mInitValue;

	};
}