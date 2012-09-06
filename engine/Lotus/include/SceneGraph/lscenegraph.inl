/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

/* ------------------------------------------------------- */
/* class SceneGraph:                                       */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
template <class Operation> void SceneGraph::apply(Traverser<Operation>& t, const String& root)
{
	t.apply(m_roots->get(root));
}
/* ------------------------------------------------------- */
template <class Operation> void SceneGraph::apply(Traverser<Operation>& t)
{
	for (HashTable<String, Spatial*>::Iterator i = m_roots->begin(); i != false; i++)
	{
		t.apply(*i);
	}
}
/* ------------------------------------------------------- */