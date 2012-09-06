/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#ifndef _HDR_LSCENEGRAPH_H
#define _HDR_LSCENEGRAPH_H

#include <scenegraph\lsgbase.h>
#include <scenegraph\lspatial.h>
#include <scenegraph\ltraverser.h>
#include <system\lstring.h>

namespace Lotus
{

	class Renderer;

	/* class SceneGraph
	 * An instance of SceneGraph is in most cases the interface of the engine for
	 * an application programer. It facilitates loading, saving and deleting of scenegraph
	 * data. A scene graph in terms of this engine refers to a collection of named root
	 * nodes. Every root node is either a root for a so called scenetree. Furthermore the
	 * class provides methods for interaction with Traversers or direct access to certain
	 * scenetrees. */
	class SceneGraph
	{
	private:
		HashTable<String, Spatial*>* m_roots;
		Renderer* m_renderer;

		void fillHash(Set<Serializable*>& roots);
		void assignRenderer();
	public:
		SceneGraph(Renderer* renderer);
		SceneGraph(Renderer* renderer, int hashSize);
		SceneGraph(Renderer* renderer, Set<Serializable*>&  roots);
		~SceneGraph();
		
		void load(const char* filename, int bufferSize = Stream::BUFFER_SIZE);
		void save(const char* filename, int bufferSize = Stream::BUFFER_SIZE);

		template <class Operation> void apply(Traverser<Operation>& t, const String& root);

		template <class Operation> void apply(Traverser<Operation>& t); // apply to all scenetrees

		Object* get(const String& root); // get root
		Object* get(const String& root, const String& name); // get specific object
		bool add(Spatial* root);
		bool remove(Spatial* root);

		void update(double time);
	};

	class Deleter
	{
	private:
	public:
		bool operator()(Object* object);
	};

	class Instancer
	{
	private:
	public:
		bool operator()(Spatial* object);
	};

	class UnInstancer
	{
	private:
	public:
		bool operator()(Spatial* object);
	};

#include "lscenegraph.inl"
};

#endif