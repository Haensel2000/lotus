/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

/* ------------------------------------------------------- */
/* class Stream:                                           */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
template <class T> void PtrLinker::link(Ptr<T>& ptr)
{
	link(ptr.m_ptr);
}
/* ------------------------------------------------------- */
template <class T> void PtrLinker::link(T*& ptr)
{
	if (ptr)
		ptr = (T*)getLink(ptr);
}
/* ------------------------------------------------------- */
template <class T> void PtrLinker::link(List<T>& list)
{
	for (List<T>::Iterator i = list.begin(); i != false; i++)
	{
		link(*i);
	}
}
/* ------------------------------------------------------- */