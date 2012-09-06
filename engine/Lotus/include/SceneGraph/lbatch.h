/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#ifndef _HDR_LBATCH_H
#define _HDR_LBATCH_H

#include <system\larray.h>
#include <system\llist.h>
#include <Resource\lvertex.h>
#include <Resource\leffect.h>

namespace Lotus
{

	class Geometry;
	class Renderer;

	/* enum BatchType
	 * Different types of geometry needs different levels of flexibility.
	 * - STATIC		is used when neither the objects vertex data nor its transform matrix or vertex color changes
	 * - INSTANCE	is used when only the transform or vertex color of an object changes but the vertex data does not
	 * - DYNAMIC	is used when transform and vertex data can change (e.g. skinning) */
	enum BatchType
	{
		BT_STATIC,
		BT_TRANSLATION,
		BT_TRANSFORM,
		BT_INSTANCE,
		BT_DYNAMIC,
		BT_MAX
	};

	class GeometryBatch;
	class Renderer;

	/* class InstanceSet
	 * To support instanced mulitpass rendering the engine supports "InstanceSet" based rendering. Any
	 * Geometry object can be part of one or more instance sets. This allows for dynamic multipass rendering
	 * where for every pass the set of instances can vary. */
	class RenderPass : public Object
	{
	private:
		List< Ptr<Effect> > m_globalEffects;
		Renderer* m_renderer;
	public:

		RenderPass(Renderer* renderer = 0);
		
		virtual void load(Stream& stream);
		virtual void link(PtrLinker& linker);
		virtual void save(Stream& stream) const;
		virtual int getDiskUsed() const;
		virtual bool fowardAll(Fowarder& c);

		void addEffect(Ptr<Effect> effect);
		void removeEffect(Ptr<Effect> effect);
		void begin(Renderer* renderer);
		void end(Renderer* renderer);

		Renderer* getRenderer();
	};

	struct InstanceGroup
	{
		Ptr<RenderPass> renderPass;
		Array<Geometry*> instances;

		InstanceGroup();
		InstanceGroup(const InstanceGroup& igroup);
	};


	class GeometryData : public Object
	{
	private:
		List< Ptr<Effect> > m_effects;
		Ptr<VertexData> m_vertexData;
		GeometryBatch* m_batch; // back reference to the assigned batch
		BatchType m_batchType;

		unsigned int m_refCount; // how many geometry object reference this data
	public:
		GeometryData();
		GeometryData(BatchType batchType);
		GeometryData(const GeometryData& g);
		GeometryData(Ptr<VertexData>& vdata, const List< Ptr<Effect> >& effects, BatchType batchType);

		virtual void load(Stream& stream);
		virtual void link(PtrLinker& linker);
		virtual void save(Stream& stream) const;
		virtual int getDiskUsed() const;
		virtual bool fowardAll(Fowarder& c);

		Ptr<GeometryData> copy();
		void addEffect(Ptr<Effect> effect);
		void removeEffect(Ptr<Effect> effect);

		Ptr<VertexData>& getVertexData();

		ArrayPtr<GeometryVertex>& changeGeometryVertexData();

		const List< Ptr<Effect> >& getEffects();
		BatchType getBatchType() const;
		Renderer* getRenderer() const;
		bool isRegistered() const;
		
		void addInstance(Geometry* instance, Ptr<RenderPass>& renderPass);
		void removeInstance(Geometry* instance, Ptr<RenderPass>& renderPass);

		void addRef();
		void removeRef();
		unsigned int getRefCount() const;
				
		friend GeometryBatch;
	};

	/* GeometryData is grouped into GeometryBatches to support instancing techniques. */
	class GeometryBatch
	{
	private:
		class VertexDataEquality
		{
		public:
			Ptr<VertexData> vertexData;
			bool operator() (Ptr<GeometryData>& data);
		};

		bool m_instancesChanged;

	protected:
		Renderer* m_renderer; // back reference to the assigned renderer
		List<InstanceGroup> m_instanceGroups;
		List< Ptr<GeometryData> > m_registered;

		
	public:
		static const int ARRAY_SIZE = 257;
		static const int ARRAY_GROW = 256;

		GeometryBatch(Renderer* renderer);
		virtual ~GeometryBatch();

		void addInstance(Geometry* instance, Ptr<RenderPass>& renderPass);
		void removeInstance(Geometry* instance, Ptr<RenderPass>& renderPass);
		virtual void removeAllInstances();
		Ptr<GeometryData>& registerData(Ptr<GeometryData>& data);
		const Ptr<GeometryData>& uniqueData() const;	
		Renderer* getRenderer() const;

		/* Some Instancing techniques only allow the grouping of one certain mesh.
		 * uniqueData returns 0 if multiple objects are allowed and the unique object 
		 * otherwise. */
		virtual bool uniqueOnly() const = 0;	
		virtual BatchType getType() const = 0;
		virtual void commit() = 0;
		virtual void update();
		virtual void draw() = 0;

	};

}

#endif