/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#ifndef _HDR_LTRAVERSER_H
#define _HDR_LTRAVERSER_H

#include <scenegraph\lgroup.h>
#include <system\larray.h>
#include <system\lhash.h>

namespace Lotus
{

	/* The following classes support traversing of the whole
	 * scene graph by using fowardAll: */

	class Fowarder
	{
	public:
		virtual bool operator()(Object* obj) = 0;
		virtual bool all() = 0;
	};

	/* class Collector
	 * Generates a collection of unique objects during a traversal. */
	class Collector : public Fowarder
	{
	private:
		HashSet<Object*> m_objects;
		Ptr< Array<Object*> > m_ordered;
		static const int HASH_SIZE = 1025;	
	public:
		Collector(int hashSize = HASH_SIZE);
		bool operator()(Object* obj);
		Ptr< Array<Object*> > getCollection();
		virtual bool all();
	};

	/* Common Template Functions: */

	class Seeker
	{
	private:
		const String& m_targetName;
		Object* m_target;
	public:
		Seeker(const String& targetName);
		bool operator()(Object* obj);
		Object* getTarget();
	};

	class SpatialUpdater
	{
	private:
		Spatial* m_transformChanged;
		Spatial* m_boundChanged;
		Spatial* m_parentBoundChange;		
		double m_time;
	public:
		SpatialUpdater(double time);
		bool pre(Spatial* obj);
		bool post(Spatial* obj);
	};

	


	/* class Traverser
	 * Traverser provides an abstract interface for traversing through the
	 * scenegraph. It facilitates the separation between data, which
	 * is the scene graph and processing. Basically there are many different
	 * traversing methods. Subclasses can implement a specific method by implementing
	 * apply. The operation that is applied to every object that is traversed is 
	 * realised through a function template. That allows separation of traversing technique
	 * and performed operation.
	 * The Operation template parameter has to provide a method: bool operator()(Object*)*/
	template <class Operation> class Traverser
	{
	protected:
		Operation& m_operation;
	public:
		Traverser(Operation& operation = Operation());
		Operation& getOperation();
		virtual void apply(Object* root) = 0;
	};

	/* class GraphTraverser
	 * Performs a traversal through the whole scenegraph, touching every object exactly
	 * once. */
	template <class Operation> class GraphTraverser : public Traverser<Operation>
	{
	private:
		Collector m_collector;
	public:
		GraphTraverser(Operation& operation = Operation());
		virtual void apply(Object* root);
		template <class OtherOperation> void reapply(OtherOperation op);

		int objectCount();
	};

	/* class PreorderTraverser
	 * Performs a preorder tree traversal through the tree with the given root */
	template <class Operation> class PreorderTraverser : public Traverser<Operation>
	{
	private:
		bool m_leafsOnly;
		void recApply(Spatial* object);
	public:
		PreorderTraverser(bool leafsOnly = false, Operation& operation = Operation());
		virtual void apply(Object* root);
	};

	template <class Operation> class TreeTraverser : public Traverser<Operation>
	{
	private:
		void recApply(Spatial* object);
	public:
		TreeTraverser(Operation& operation = Operation());
		virtual void apply(Object* root);
	};

#include "ltraverser.inl"
}

#endif