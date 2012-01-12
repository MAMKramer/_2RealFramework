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

#include "_2RealRunnable.h"
#include "_2RealGraph.h"

#include "Poco/Mutex.h"
#include "Poco/Event.h"

namespace _2Real
{
	/**
	*	sequences & synchronizations are runnable graphs,
	*	i.e. graphs that have a run method
	*	this means that insert / remove operations might happen while the graph is running
	*/

	class Operation
	{

		void performOperation(std::list< RunnableManager * > &children);

	};

	class Insertion : public Operation
	{
	public:

		Insertion(RunnableManager *child, unsigned int index);

		RunnableManager * getChild();
		unsigned int getPosition();

	private:

		RunnableManager *	m_Runnable;
		unsigned int		m_Position;

	};

	class Removal : public Operation
	{
	};

	class RunnableGraph : public Runnable, public Graph
	{

	public:

		RunnableGraph(Identifier const& id, SystemGraph &system);
		virtual ~RunnableGraph();

		/**
		*	recursive. not sure whether that's good
		*/
		void setup();
		void shutdown();

		void insertChild(RunnableManager &child, unsigned int position);
		void removeChild(Identifier const& childId);

		void childFinished(Identifier const& childId);

	protected:

		/**
		*	these are needed for thread safe iteration
		*/
		bool updateFirstChild(PooledThread &thread);
		bool updateNextChild(PooledThread &thread);

		Poco::Event				m_ChildrenFinished;

		//runnable graphs can have a list of objects that are to remove or inserted
		std::list< Operation > m_Operations;

	private:

		/**
		*	these are needed for concurrent access (remove operations while graph is being run)
		*/
		Poco::FastMutex				m_Mutex;
		RunnableList::iterator		m_ListIterator;

		unsigned int				m_ChildrenInUpdate;


	};

}