/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#include <scenegraph\lcamera.h>

using namespace Lotus;

/* ------------------------------------------------------- */
/* class Camera:                                           */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
Camera::Camera()
: m_planeCount(FRUSTUM_PLANES), m_eye(0, 0, 0), m_direction(0, 0, 1), m_up(0, 1, 0), m_renderer(0)
{
	setProjection(Math<float>::PI*0.25f, 4.0f/3.0f, 1.0f, 100.0f); 
}
/* ------------------------------------------------------- */
Camera::Camera(const Camera& c)
: Spatial(c), m_planeCount(c.m_planeCount), m_eye(c.m_eye), m_direction(c.m_direction), m_up(c.m_up),
m_dMin(c.m_dMin), m_dMax(c.m_dMax), m_width(c.m_width), m_height(c.m_height), m_renderer(0)
{
	for (int i = 0; i < m_planeCount; i++)
	{
		m_cullingPlanes[i] = c.m_cullingPlanes[i];
	}
}
/* ------------------------------------------------------- */
Spatial* Camera::copy()
{
	return new Camera(*this);
}
/* ------------------------------------------------------- */
void Camera::updateBound()
{
}
/* ------------------------------------------------------- */
void Camera::setRenderer(Renderer* renderer)
{
	m_renderer = renderer;
	m_renderer->setView(m_eye, m_direction, m_up);
	m_renderer->setProjection(m_width, m_height, m_dMin, m_dMax);
}
/* ------------------------------------------------------- */
void Camera::setEye(const Vector3& eye)
{
	m_eye = eye;
	viewChange();
}
/* ------------------------------------------------------- */
void Camera::setDirection(const Vector3& dir)
{
	m_direction = dir;
	viewChange();
}
/* ------------------------------------------------------- */
void Camera::setUp(const Vector3& up)
{
	m_up = up;
	viewChange();
}
/* ------------------------------------------------------- */
void Camera::setView(const Vector3& eye, const Vector3& dir, const Vector3& up)
{
	m_eye = eye;
	m_direction = dir;
	m_up = up;
	viewChange();
}
/* ------------------------------------------------------- */
void Camera::setProjection(float fovVer, float aspect, float min, float max)
{
	m_dMin = min;
	m_dMax = max;
	m_height = 2*min*Math<float>::Tan(fovVer*0.5f);
	m_width = aspect*m_height;
	projectionChange();
}
/* ------------------------------------------------------- */
void Camera::updateTransform()
{
	Spatial::updateTransform();
	viewChange();
}
/* ------------------------------------------------------- */
int Camera::getPlaneCount() const
{
	return m_planeCount;
}
/* ------------------------------------------------------- */
void Camera::pushPlane(const Plane3& plane)
{
	m_cullingPlanes[m_planeCount++] = plane;
}
/* ------------------------------------------------------- */
void Camera::popPlane()
{
	m_planeCount--;
}
/* ------------------------------------------------------- */
bool Camera::culled(const BoundingVolume* bv, unsigned int& planeState) const
{
	// bit = 1 means that plane has to be compared, bit = 0 means the parent is inside and 
	// no check has to be made for this plane
	int last = m_planeCount - 1;
	unsigned int mask = 1 << last;
	for (int i = last; i >= 0; i--, mask >>= 1)
	{
		if (planeState & mask)
		{
			int side = bv->whichSide(m_cullingPlanes[i]);
			if (side < 0)
			{
				return true;
			}
			if (side > 0)
			{
				planeState &= ~mask;
			}
		}
	}

	return false;
}
/* ------------------------------------------------------- */
/*                      PROTECTED                          */
/* ------------------------------------------------------- */
void Camera::projectionChange()
{
	if (m_renderer)
		m_renderer->setProjection(m_width, m_height, m_dMin, m_dMax);

	// calculating the frustum:
	Vector3 d = m_world.applyVector(m_direction);
	Vector3 u = m_world.applyVector(m_up);
	Vector3 e = m_world.apply(m_eye);
	Vector3 r = d.cross(u);
	Vector3 normal;
	float hwidth = m_width*0.5f;
	float hheight = m_height*0.5f;
	
	// Near:
	m_cullingPlanes[0] = Plane3(d, d.dot(e) + m_dMin);

	// Far:
	m_cullingPlanes[1] = Plane3(-d, -(d.dot(e) + m_dMax));

	float invLength = 1 / sqrt(m_dMin*m_dMin + hwidth*hwidth);
	// Left:
	normal = (m_dMin*r + hwidth*d) * invLength;
	m_cullingPlanes[2] = Plane3(normal, -normal.dot(e));		

	// Right:
	normal = (-m_dMin*r + hwidth*d) * invLength;
	m_cullingPlanes[3] = Plane3(normal, -normal.dot(e));

	invLength = 1 / sqrt(m_dMin*m_dMin + hheight*hheight);
	// Top:
	normal = (-m_dMin*u + hheight*d) * invLength;
	m_cullingPlanes[4] = Plane3(normal, normal.dot(e));
	
	// Bottom:
	normal = (m_dMin*u + hheight*d) * invLength;
	m_cullingPlanes[5] = Plane3(normal, normal.dot(e));
}
/* ------------------------------------------------------- */
void Camera::viewChange()
{
	if (m_renderer)
		m_renderer->setView(m_eye, m_direction, m_up);
}
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* class Culler:                                           */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
Culler::Culler(const Camera* cam)
: m_camera(cam), m_wasCulled(0)
{
	m_stack.push(0xFFFFFFFF);
}
/* ------------------------------------------------------- */
bool Culler::pre(Spatial* obj)
{
	unsigned int state = m_stack.peek();
	bool c = (m_wasCulled) ? true : m_camera->culled(obj->getWorldBound(), state);
	obj->setCulled(c);
	if (c == true && !m_wasCulled)
	{
		m_wasCulled = obj;
	}
	m_stack.push(state);
	return true;
}
/* ------------------------------------------------------- */
bool Culler::post(Spatial* obj)
{
	m_stack.pop();
	if (m_wasCulled == obj)
		m_wasCulled = 0;
	return true;
}
/* ------------------------------------------------------- */


		