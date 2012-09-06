/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#ifndef _HDR_LCAMERA_H
#define _HDR_LCAMERA_H

#include <scenegraph\lspatial.h>
#include <scenegraph\lrenderer.h>
#include <math\lgeom.h>

namespace Lotus
{

	class Camera : public Spatial
	{
	public:
		static const int FRUSTUM_PLANES = 6;
		static const int MAX_CULLING_PLANES = 32;
	private:		
		Vector3 m_eye;
		Vector3 m_direction;
		Vector3 m_up;
		float m_dMin, m_dMax, m_width, m_height;
		Plane3 m_cullingPlanes[MAX_CULLING_PLANES];
		int m_planeCount;

		Renderer* m_renderer;
	protected:
		void projectionChange();
		void viewChange();
	public:
		Camera();
		Camera(const Camera& c);

		virtual Spatial* copy();
		virtual void updateBound();

		void setRenderer(Renderer* renderer);

		void setEye(const Vector3& eye);
		void setDirection(const Vector3& dir);
		void setUp(const Vector3& up);

		void setView(const Vector3& eye, const Vector3& dir, const Vector3& up);
		void setProjection(float fovVer, float aspect, float min, float max);

		int getPlaneCount() const;
		void pushPlane(const Plane3& plane);
		void popPlane();
		bool culled(const BoundingVolume* bv, unsigned int& planeState) const;

		virtual void updateTransform();
	};

	class Culler
	{
	private:
		const Camera* m_camera;
		Spatial* m_wasCulled;
		Stack<unsigned int, 513> m_stack;
	public:
		Culler(const Camera* cam);
		bool pre(Spatial* obj);
		bool post(Spatial* obj);
	};


}

#endif