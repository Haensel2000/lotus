/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#ifndef _HDR_LGEOMETRY_H
#define _HDR_LGEOMETRY_H

#include <scenegraph\lspatial.h>
#include <scenegraph\lrenderer.h>

namespace Lotus
{
	class Effect;
	class VertexData;

	class Geometry : public Spatial
	{
	protected:
		BoundingVolume* m_modelBound;
		Ptr<GeometryData> m_geometryData;
		void registerData(Renderer* renderer = 0);
		
		bool m_isRegistered;
	public:
		Geometry();
		Geometry(const Geometry& g);
		Geometry(Ptr<GeometryData>& gdata, Renderer* renderer);
		virtual ~Geometry();

		virtual Spatial* copy();

		virtual void load(Stream& stream);
		virtual void link(PtrLinker& linker);
		virtual void save(Stream& stream) const;
		virtual int getDiskUsed() const;
		virtual bool fowardAll(Fowarder& c);

		virtual void addEffect(Ptr<Effect> effect);
		virtual void removeEffect(Ptr<Effect> effect);
		virtual void addRenderPass(Ptr<RenderPass>& renderPass);
		virtual void removeRenderPass(Ptr<RenderPass>& renderPass);

		const List<Ptr<Effect>>& getEffects() const;
		Ptr<VertexData>& getVertexData();
		Ptr<GeometryData>& getGeometryData();

		void registerInstance();
		void unregisterInstance();

		const BoundingVolume* getModelBound() const;
		BoundingVolume* changeModelBound();

		virtual void updateBound();
	};

}

#endif