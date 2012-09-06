/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/


/* ------------------------------------------------------- */
/* class Traverser:                                        */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
template <class Operation> Traverser<Operation>::Traverser(Operation& operation)
: m_operation(operation)
{
}
/* ------------------------------------------------------- */
template <class Operation> Operation& Traverser<Operation>::getOperation() 
{
	return m_operation;
}
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* class GraphTraverser:                                   */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
template <class Operation> GraphTraverser<Operation>::GraphTraverser(Operation& operation)
: Traverser(operation)
{
}
/* ------------------------------------------------------- */
template <class Operation> void GraphTraverser<Operation>::apply(Object* root)
{
	root->fowardAll(m_collector);
	for (Array<Object*>::Iterator i = m_collector.getCollection()->begin(); i != false; i++)
	{
		m_operation(*i);
	}
}
/* ------------------------------------------------------- */
template <class Operation> template <class OtherOperation> 
void GraphTraverser<Operation>::reapply(OtherOperation op)
{
	for (Array<Object*>::Iterator i = m_collector.getCollection()->begin(); i != false; i++)
	{
		op(*i);
	}
}
/* ------------------------------------------------------- */
template <class Operation> int GraphTraverser<Operation>::objectCount()
{
	return m_collector.getCollection()->size();
}
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* class PreorderTraverser:                                */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
template <class Operation> 
PreorderTraverser<Operation>::PreorderTraverser(bool leafsOnly, Operation& operation)
: Traverser(operation), m_leafsOnly(leafsOnly)
{
}
/* ------------------------------------------------------- */
template <class Operation> void PreorderTraverser<Operation>::apply(Object* root)
{
	Spatial* s = dynamic_cast<Spatial*>(root);
	assert(s);
	recApply(s);
}
/* ------------------------------------------------------- */
/*                      PRIVATE                            */
/* ------------------------------------------------------- */
template <class Operation> void PreorderTraverser<Operation>::recApply(Spatial* object)
{
	Group* group = dynamic_cast<Group*>(object);
	if (group)
	{
		if (m_leafsOnly || m_operation(object))
		{
			for (List<Spatial*>::Iterator i = group->getChildren().begin(); i != false; i++)
			{
				recApply(*i);
			}
		}
	}
	else // leaf node
	{
		m_operation(object);
	}
}
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* class TreeTraverser    :                                */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
template <class Operation> TreeTraverser<Operation>::TreeTraverser(Operation& operation)
: Traverser(operation)
{
}
/* ------------------------------------------------------- */
template <class Operation> void TreeTraverser<Operation>::apply(Object* root)
{
	Spatial* s = dynamic_cast<Spatial*>(root);
	assert(s);
	recApply(s);
}
/* ------------------------------------------------------- */
/*                      PROTECTED                          */
/* ------------------------------------------------------- */
template <class Operation> void TreeTraverser<Operation>::recApply(Spatial* object)
{
	Group* group = dynamic_cast<Group*>(object);
	if (group)
	{
		if (m_operation.pre(object))
		{
			for (List<Spatial*>::Iterator i = group->getChildren().begin(); i != false; i++)
			{
				recApply(*i);
			}
		}
		m_operation.post(object);
	}
	else // leaf node
	{
		m_operation.pre(object);
		m_operation.post(object);
	}
}
