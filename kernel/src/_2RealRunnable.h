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

#include "Poco/Runnable.h"

namespace _2Real
{

	/**
	*	services, sequences and synchronizations are runnable
	*/

	class Graph;
	class SystemGraph;
	class RunnableGraph;

	class Runnable : public Poco::Runnable, public Entity
	{

	public:

		Runnable(Identifier const& id, SystemGraph &system);
		virtual ~Runnable();

		void start(bool const& runOnce);
		void stop();

		virtual void setup() = 0;
		virtual void run() = 0;
		virtual void update() = 0;
		virtual void shutdown() = 0;

		virtual void checkConfiguration() = 0;

		void setRoot(RunnableGraph &root);
		RunnableGraph & root();
		RunnableGraph const&  root() const;

		void setFather(RunnableGraph &father);
		RunnableGraph &father();
		RunnableGraph const& father() const;

		SystemGraph &system();
		SystemGraph const& system() const;

	protected:

		bool					m_Run;
		bool					m_RunOnce;

		SystemGraph				&m_System;
		RunnableGraph			*m_Root;
		RunnableGraph			*m_Father;

	};

	inline Runnable::Runnable(Identifier const& id, SystemGraph &system) :
		Entity(id),
		m_System(system)
	{
	}

	inline Runnable::~Runnable()
	{
	}

	inline void Runnable::start(bool const& runOnce)
	{
		m_RunOnce = runOnce;
		m_Run = !runOnce;
	}

	inline void Runnable::stop()
	{
		m_RunOnce = false;
		m_Run = false;
	}

	inline void Runnable::setRoot(RunnableGraph &root)
	{
		m_Root = &root;
	}

	inline RunnableGraph & Runnable::root()
	{
		return *m_Root;
	}

	inline RunnableGraph const& Runnable::root() const
	{
		return *m_Root;
	}

	inline void Runnable::setFather(RunnableGraph &father)
	{
		m_Father = &father;
	}

	inline RunnableGraph & Runnable::father()
	{
		return *m_Father;
	}

	inline RunnableGraph const& Runnable::father() const
	{
		return *m_Father;
	}

	inline SystemGraph & Runnable::system()
	{
		return m_System;
	}

	inline SystemGraph const& Runnable::system() const
	{
		return m_System;
	}

}