/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#ifndef _HDR_LSPATIAL_H
#define _HDR_LSPATIAL_H

#include <math\lgeom.h>
#include <math\lmatrix.h>
#include <math\lvector.h>
#include <resource\leffect.h>
#include <resource\lvertex.h>
#include <scenegraph\lsgbase.h>
#include <scenegraph\lbatch.h>
#include <system\lstream.h>
#include <system\lbitset.h>

#include <iostream> 

using namespace std;

namespace Lotus
{

	class Transformation
	{
	private:
		Matrix3 m_matrix;
		Vector3 m_translate;
		Vector3 m_scale;
		bool m_isIdentity, m_isRSMatrix, m_isUniformScale;
		void invS(Vector3& v) const;
	public:
		static const Transformation IDENTITY;

		Transformation(); // initializes with identity
		Transformation(const Transformation& t);
		Transformation(const Matrix4& matrix);
		void operator=(const Transformation& t);

		void setRotation(const Matrix3& rotation);
		const Matrix3& getRotation() const;
		void setMatrix(const Matrix3& matrix);
		const Matrix3& getMatrix() const;
		void setTranslation(const Vector3& translation);
		const Vector3& getTranslation() const;
		void setScale(const Vector3& scale);
		const Vector3& getScale() const;
		void setUniformScale(float scale);
		const float getUniformScale() const;

		Vector3 apply(const Vector3& input) const;
		Plane3 apply(const Plane3& input) const;
		Vector3 applyInverse(const Vector3& input) const;
		Vector3 applyVector(const Vector3& input) const;
		Vector3 applyInverseVector(const Vector3& input) const;

		void getTransform(Matrix4& matrix) const;
		void getTransposedTransform(Matrix4& matrix) const;

		Transformation operator*(const Transformation& t);
		Transformation inverse() const;
		float norm() const;
	};

	/* class BoundingVolume
	 * This is an abstract interface for all BoundingVolumes (e.g. Sphere,
	 * axis-aligned Bounding Box etc.). The interface is introduced so that
	 * an application programer can easily change the standard BoundingVolume
	 * to test which is most efficient for his application. Every BoundingVolume
	 * must have the concept of a center point and a radius.*/
	class BoundingVolume : public Object
	{
	private:

	public:
		template <class T> static BoundingVolume* Create()
		{
			T* bv = new T();
			return bv;
		}

		virtual void setCenter(const Vector3& center) = 0;
		virtual void setRadius(float radius) = 0;
		virtual Vector3 getCenter() const = 0;
		virtual float getRadius() const = 0;

		virtual void computeFromData(const Ptr<VertexData>& vdata) = 0;
		virtual void transform(const Transformation& t) = 0;
		virtual int whichSide(const Plane3& plane) const = 0;
		virtual bool intersects(const Vector3& origin, const Vector3& direction) const = 0;
		virtual bool intersects(const BoundingVolume* input) const = 0;

		virtual void operator=(const BoundingVolume* input) = 0;
		virtual void growToContain(const BoundingVolume* input) = 0;
		virtual bool contains(const Vector3& point) const = 0;

		virtual BoundingVolume* copy() const = 0;
	};

	class SphereVolume : public BoundingVolume
	{
	private:
		Vector3 m_center;
		float m_radius;
	public:
		SphereVolume();
		SphereVolume(Vector3 center, float radius);

		virtual void load(Stream& stream);
		virtual void link(PtrLinker& linker);
		virtual void save(Stream& stream) const;
		virtual int getDiskUsed() const;

		void setCenter(const Vector3& center);
		void setRadius(float radius);
		Vector3 getCenter() const;
		float getRadius() const;

		void computeFromData(const Ptr<VertexData>& vdata);
		void transform(const Transformation& t);
		int whichSide(const Plane3& plane) const;
		bool intersects(const Vector3& origin, const Vector3& direction) const;
		bool intersects(const BoundingVolume* input) const;

		void operator=(const BoundingVolume* input);
		void growToContain(const BoundingVolume* input);
		bool contains(const Vector3& point) const;

		BoundingVolume* copy() const;
	};

	
	/* class Spatial
	 * The spatial class is an abstraction of an object that has a position, 
	 * "volume" and a alignment. The information is controlled through transformations
	 * that are hierachicaly odered in the scene tree. Furthermore every Spatial object
	 * has a BoundingVolume to support fast culling and intersection tests. */
	class Spatial : public Controllable
	{
	protected:										  
		Spatial* m_parent;	
		List< Ptr<RenderPass> > m_renderPasses;

		Transformation m_local, m_world;
		BoundingVolume* m_worldBound;
		bool m_worldIsCurrent, m_worldBoundIsCurrent;
		bool m_transformChanged, m_boundChanged, m_static; // flags for controlling the geometric update traverser		 	

		bool m_culled;

		static BoundingVolume* newBoundingVolume();		
	public:											
		Spatial();
		Spatial(const Spatial& s);
		virtual ~Spatial();

		virtual Spatial* copy() = 0;
		
		virtual void load(Stream& stream);
		virtual void link(PtrLinker& stream);
		virtual void save(Stream& stream) const;
		virtual int getDiskUsed() const;
		virtual bool fowardAll(Fowarder& c);

		Spatial* getParent();
		void setParent(Spatial* parent);

		virtual void addEffect(Ptr<Effect> effect);
		virtual void removeEffect(Ptr<Effect> effect);

		virtual void addRenderPass(Ptr<RenderPass>& renderPass);
		virtual void removeRenderPass(Ptr<RenderPass>& renderPass);
		const List< Ptr<RenderPass> >& getRenderPasses() const;

		const BoundingVolume* getWorldBound() const;
		BoundingVolume* changeWorldBound();
		const Transformation& getLocalTransform() const;
		const Transformation& getWorldTransform() const;
		Transformation& changeLocalTransform();
		Transformation& changeWorldTransform();
		void setLocalTransform(const Transformation& t);
		void setWorldTransform(Transformation& t);

		

		bool isCulled();
		void setCulled(bool on = true);

		void resetFlags();
		bool transformChanged();
		bool boundChanged();
		bool isStatic();

		virtual void updateTransform();
		virtual void updateBound() = 0;
	};

	


}

#endif