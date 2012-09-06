/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#include <scenegraph\lspatial.h>

using namespace Lotus;

/* ------------------------------------------------------- */
/* class Spatial:                                          */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
Spatial::Spatial()
: m_parent(0), m_worldBound(0), m_worldIsCurrent(false), m_worldBoundIsCurrent(false),
m_transformChanged(false), m_boundChanged(false), m_static(false)
{
}
/* ------------------------------------------------------- */
Spatial::Spatial(const Spatial& s)
: m_parent(s.m_parent), m_local(s.m_local), m_world(s.m_world), m_worldBound(s.m_worldBound->copy()), m_static(s.m_static),
m_worldIsCurrent(false), m_worldBoundIsCurrent(false), m_transformChanged(false), m_boundChanged(false),
m_renderPasses(s.m_renderPasses)
{
}
/* ------------------------------------------------------- */
Spatial::~Spatial()
{
	if (m_worldBound)
		delete m_worldBound;
}
/* ------------------------------------------------------- */
void Spatial::load(Stream& stream)
{
	Controllable::load(stream);

	stream.read(m_parent);
	stream.read(m_local);
	stream.read(m_world);
	stream.read(m_worldBound);
	stream.read(m_renderPasses);
}
/* ------------------------------------------------------- */
void Spatial::link(PtrLinker& linker)
{
	Controllable::link(linker);

	linker.link(m_parent);
	linker.link(m_worldBound);
	linker.link(m_renderPasses);
}
/* ------------------------------------------------------- */
void Spatial::save(Stream& stream) const
{
	Controllable::save(stream);

	stream.write(m_parent);
	stream.write(m_local);
	stream.write(m_world);
	stream.write(m_worldBound);
	stream.write(m_renderPasses);
}
/* ------------------------------------------------------- */
int Spatial::getDiskUsed() const
{
	return	Controllable::getDiskUsed() + sizeof(Spatial*) + sizeof(BoundingVolume*) +
			sizeof(m_local) + sizeof(m_world) + sizeof(m_renderPasses);
}
/* ------------------------------------------------------- */
bool Spatial::fowardAll(Fowarder& c)
{
	if (Controllable::fowardAll(c))
	{
		m_worldBound->fowardAll(c);
		for (List< Ptr<RenderPass> >::Iterator i = m_renderPasses.begin(); i != false; i++)
		{
			(*i)->fowardAll(c);
		}
		return true;
	}
	return false;
}
/* ------------------------------------------------------- */
Spatial* Spatial::getParent()
{
	return m_parent;
}
/* ------------------------------------------------------- */
void Spatial::setParent(Spatial* parent)
{
	m_parent = parent;
}
/* ------------------------------------------------------- */
void Spatial::addEffect(Ptr<Effect> effect)
{}
/* ------------------------------------------------------- */
void Spatial::removeEffect(Ptr<Effect> effect)
{}
/* ------------------------------------------------------- */
void Spatial::addRenderPass(Ptr<RenderPass>& renderPass)
{
	m_renderPasses.insertFront(renderPass);
}
/* ------------------------------------------------------- */
void Spatial::removeRenderPass(Ptr<RenderPass>& renderPass)
{
	m_renderPasses.remove(renderPass);
}
/* ------------------------------------------------------- */
const List< Ptr<RenderPass> >& Spatial::getRenderPasses() const
{
	return m_renderPasses;
}
/* ------------------------------------------------------- */
const BoundingVolume* Spatial::getWorldBound() const
{
	return m_worldBound;
}
/* ------------------------------------------------------- */
BoundingVolume* Spatial::changeWorldBound()
{
	m_boundChanged = true;
	m_worldBoundIsCurrent = true;
	return m_worldBound;
}
/* ------------------------------------------------------- */
const Transformation& Spatial::getLocalTransform() const
{
	return m_local;
}
/* ------------------------------------------------------- */
const Transformation& Spatial::getWorldTransform() const
{
	return m_world;
}
/* ------------------------------------------------------- */
Transformation& Spatial::changeLocalTransform()
{
	m_transformChanged = true;
	return m_local;
}
/* ------------------------------------------------------- */
Transformation& Spatial::changeWorldTransform()
{
	m_worldIsCurrent = true;
	m_transformChanged = true;
	return m_world;
}
/* ------------------------------------------------------- */
void Spatial::setLocalTransform(const Transformation& t)
{
	m_local = t;
	m_transformChanged = true;
}
/* ------------------------------------------------------- */
void Spatial::setWorldTransform(Transformation& t)
{
	m_world = t;
	m_worldIsCurrent = true;
	m_transformChanged = true;
}
/* ------------------------------------------------------- */
bool Spatial::isCulled()
{
	return m_culled;
}
/* ------------------------------------------------------- */
void Spatial::setCulled(bool on)
{
	m_culled = on;
}
/* ------------------------------------------------------- */
void Spatial::resetFlags()
{
	m_worldIsCurrent = false;
	m_worldBoundIsCurrent = false;
	m_transformChanged = false;
	m_boundChanged = false;
}
/* ------------------------------------------------------- */
bool Spatial::transformChanged()
{
	return m_transformChanged;
}
/* ------------------------------------------------------- */
bool Spatial::boundChanged()
{
	return m_boundChanged;
}
/* ------------------------------------------------------- */
bool Spatial::isStatic()
{
	return m_static;
}
/* ------------------------------------------------------- */
void Spatial::updateTransform()
{
	if (!m_worldIsCurrent)
	{
		cout << getName().toCharArray() << " [T]" << endl;
		if (m_parent)
			m_world = m_parent->m_world * m_local;
		else
			m_world = m_local;
	}
}
/* ------------------------------------------------------- */
/*                      PROTECTED                          */
/* ------------------------------------------------------- */
BoundingVolume* Spatial::newBoundingVolume()
{
	return BoundingVolume::Create<SphereVolume>();
}
/* ------------------------------------------------------- */
/* class Transformation:                                   */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
Transformation::Transformation()
: m_matrix(Matrix3::IDENTITY), m_translate(Vector3::ZERO), m_scale(1.0f, 1.0f, 1.0f),
  m_isIdentity(true), m_isRSMatrix(true), m_isUniformScale(true)
{
}
/* ------------------------------------------------------- */
Transformation::Transformation(const Transformation& t)
: m_matrix(t.m_matrix), m_translate(t.m_translate), m_scale(t.m_scale), 
  m_isIdentity(t.m_isIdentity), m_isRSMatrix(t.m_isRSMatrix), m_isUniformScale(t.m_isUniformScale)
{
}
/* ------------------------------------------------------- */
Transformation::Transformation(const Matrix4& matrix)
: m_matrix(matrix[0][0], matrix[0][1], matrix[0][2],
		   matrix[1][0], matrix[1][1], matrix[1][2],
		   matrix[2][0], matrix[2][1], matrix[2][2]),
  m_translate(matrix[0][3], matrix[1][3], matrix[2][3])
{
	m_matrix.decompose(m_matrix, m_scale);
	m_isUniformScale = (m_scale[0] == m_scale[1] == m_scale[2]);
	m_isIdentity = (matrix == Matrix4::IDENTITY);
	m_isRSMatrix = true;
}
/* ------------------------------------------------------- */
void Transformation::operator=(const Transformation& t)
{
	m_matrix = t.m_matrix;
	m_translate = t.m_translate;
	m_scale = t.m_scale;
	m_isIdentity = t.m_isIdentity;
	m_isRSMatrix = t.m_isRSMatrix;
	m_isUniformScale = t.m_isUniformScale;
}
/* ------------------------------------------------------- */
void Transformation::setRotation(const Matrix3& rotation)
{
	m_matrix = rotation;
	m_isRSMatrix = true;
	m_isIdentity = false;
}
/* ------------------------------------------------------- */
const Matrix3& Transformation::getRotation() const
{
	assert(m_isRSMatrix);
	return m_matrix;
}
/* ------------------------------------------------------- */
void Transformation::setMatrix(const Matrix3& matrix)
{
	m_matrix = matrix;
	m_isRSMatrix = false;
	m_isIdentity = false;
}
/* ------------------------------------------------------- */
const Matrix3& Transformation::getMatrix() const
{
	return m_matrix;
}
/* ------------------------------------------------------- */
void Transformation::setTranslation(const Vector3& translate)
{
	m_translate = translate;
	m_isIdentity = false;
}
/* ------------------------------------------------------- */
const Vector3& Transformation::getTranslation() const
{
	return m_translate;
}
/* ------------------------------------------------------- */
void Transformation::setScale(const Vector3& scale)
{
	assert(m_isRSMatrix && scale.X() != 0.0f && scale.Y() != 0.0f && scale.Z() != 0.0f);
	m_scale = scale;
	m_isIdentity = false;
	m_isUniformScale = false;
}
/* ------------------------------------------------------- */
const Vector3& Transformation::getScale() const
{
	return m_scale;
}
/* ------------------------------------------------------- */
void Transformation::setUniformScale(float scale)
{
	assert(m_isRSMatrix && scale != 0.0f);
	m_scale.X() = scale;
	m_scale.Y() = scale;
	m_scale.Z() = scale;
	m_isIdentity = false;
	m_isUniformScale = true;
}
/* ------------------------------------------------------- */
const float Transformation::getUniformScale() const
{
	assert(m_isUniformScale);
	return m_scale.X();
}
/* ------------------------------------------------------- */
Vector3 Transformation::apply(const Vector3& input) const
{
	if (m_isIdentity)
	{
		return input;
	}
	else
	{
		return applyVector(input) + m_translate;
	}
}
/* ------------------------------------------------------- */
Plane3 Transformation::apply(const Plane3& input) const
{
	if (m_isIdentity)
	{
		return input;
	}
	
	Plane3 result;
	
	if (m_isRSMatrix)
	{	
		result.normal = input.normal;
		invS(result.normal);
		result.normal = m_matrix*result.normal;
	}
	else
	{	
		result.normal =  input.normal * m_matrix.inverse();	
	}
	float invD = 1.0f / result.normal.length();
	result.normal *= invD;
	result.constant = input.constant*invD + result.normal.dot(m_translate);
	return result;
}
/* ------------------------------------------------------- */
Vector3 Transformation::applyVector(const Vector3& input) const
{
	if (m_isIdentity)
	{
		return input;
	}
	else if (m_isRSMatrix)
	{
		Vector3 result(input[0]*m_scale[0], input[1]*m_scale[1], input[2]*m_scale[2]);
		return m_matrix*result;
	}
	else
	{
		return m_matrix*input;
	}
	
}
/* ------------------------------------------------------- */
Vector3 Transformation::applyInverse(const Vector3& input) const
{
	if (m_isIdentity)
	{
		return input;
	}
	else if (m_isRSMatrix)
	{
		Vector3 result = (input - m_translate) * m_matrix;
		invS(result);
		return result;
	}
	else
	{
		return m_matrix.inverse()*(input - m_translate);
	}
}
/* ------------------------------------------------------- */
Vector3 Transformation::applyInverseVector(const Vector3& input) const
{
	if (m_isIdentity)
	{
		return input;
	}
	else if (m_isRSMatrix)
	{
		Vector3 result = input * m_matrix;
		invS(result);
		return result;
	}
	else
	{
		return m_matrix.inverse()*input;
	}
}
/* ------------------------------------------------------- */
void Transformation::getTransform(Matrix4& matrix) const
{
	float* f = matrix;
	f[0] = m_matrix[0][0]*m_scale[0]; f[1] = m_matrix[0][1]*m_scale[1]; f[2] = m_matrix[0][2]*m_scale[2];  f[3] = m_translate[0];
	f[4] = m_matrix[1][0]*m_scale[0]; f[5] = m_matrix[1][1]*m_scale[1]; f[6] = m_matrix[1][2]*m_scale[2];  f[7] = m_translate[1];
	f[8] = m_matrix[2][0]*m_scale[0]; f[9] = m_matrix[2][1]*m_scale[1]; f[10] = m_matrix[2][2]*m_scale[2]; f[11] = m_translate[2];
	f[12] = 0;						  f[13] = 0;						f[14] = 0;						   f[15] = 1;
}
/* ------------------------------------------------------- */
void Transformation::getTransposedTransform(Matrix4& matrix) const
{
	float* f = matrix;
	f[0] = m_matrix[0][0]*m_scale[0]; f[4] = m_matrix[0][1]*m_scale[1]; f[8] = m_matrix[0][2]*m_scale[2];  f[12] = m_translate[0];
	f[1] = m_matrix[1][0]*m_scale[0]; f[5] = m_matrix[1][1]*m_scale[1]; f[9] = m_matrix[1][2]*m_scale[2];  f[13] = m_translate[1];
	f[2] = m_matrix[2][0]*m_scale[0]; f[6] = m_matrix[2][1]*m_scale[1]; f[10] = m_matrix[2][2]*m_scale[2]; f[14] = m_translate[2];
	f[3] = 0;						  f[7] = 0;							f[11] = 0;						   f[15] = 1;
}
/* ------------------------------------------------------- */

/* ------------------------------------------------------- */
Transformation Transformation::operator*(const Transformation& t)
{
	if (m_isIdentity)
	{
		return t;
	}

	if (t.m_isIdentity)
	{
		return *this;
	}

	Transformation result;
	if (m_isRSMatrix && t.m_isRSMatrix)
	{	
		if (m_isUniformScale)
		{
			result.setRotation(m_matrix * t.m_matrix);
			result.setTranslation(m_scale[0]*(m_matrix*t.m_translate) + m_translate);
			if (t.m_isUniformScale)
			{
				result.setUniformScale(m_scale[0] * t.m_scale[0]);
			}
			else
			{
				result.setScale(m_scale[0] * t.m_scale);
			}
			return result;
		}	
	}

	// In all remaining cases, the matrix cannot be written as R*S*X+T.
    Matrix3 a = ( m_isRSMatrix ?
        m_matrix.timesDiagonal(m_scale) :
        m_matrix );

    Matrix3 b = ( t.m_isRSMatrix ?
        t.m_matrix.timesDiagonal(t.m_scale) :
        t.m_matrix );

    result.setMatrix(a*b);
    result.setTranslation(a*t.m_translate + m_translate);
	return result;
}
/* ------------------------------------------------------- */
Transformation Transformation::inverse() const
{
	if ( m_isIdentity )
    {
        return *this;
    }

	Transformation result;
    if ( m_isRSMatrix )
    {
		result.setRotation(m_matrix.transpose());
        if ( m_isUniformScale )
        {		
			float invScale = 1.0f / m_scale[0];
			result.setUniformScale(invScale);
        }
        else
        {
			result.setScale(Vector3(1.0f/m_scale[0], 1.0f/m_scale[1], 1.0f/m_scale[2]));

            Matrix3 rs = m_matrix.timesDiagonal(m_scale);
            result.m_matrix = rs.inverse();
        }
		Vector3 translation = m_translate*m_matrix;
		translation[0] *= result.m_scale[0];
		translation[1] *= result.m_scale[1];
		translation[2] *= result.m_scale[2];
		result.setTranslation(-translation);
    }
    else
    {
        result.setMatrix(m_matrix.inverse());
		result.setTranslation(-(result.m_matrix*m_translate));
    }
	return result;
}
/* ------------------------------------------------------- */
float Transformation::norm() const
{
	if (m_isRSMatrix)
	{
		if (m_isUniformScale)
		{
			return m_scale[0];
		}
		else
		{
			return max(m_scale[0], m_scale[1], m_scale[2]);
		}
	}
	else
	{
		return max( abs(m_matrix[0][0]) + abs(m_matrix[1][0]) + abs(m_matrix[2][0]),
					abs(m_matrix[0][1]) + abs(m_matrix[1][1]) + abs(m_matrix[2][1]),
					abs(m_matrix[0][2]) + abs(m_matrix[1][2]) + abs(m_matrix[2][2]) );
	}
}
/* ------------------------------------------------------- */
/*                      PRIVATE                            */
/* ------------------------------------------------------- */
void Transformation::invS(Vector3& v) const
{
	assert(m_isRSMatrix);
	if (m_isUniformScale)
	{
		v /= m_scale[0];
	}
	else
	{
		// The direct inverse scaling is
        //   result.X() /= m_scale.X();
        //   result.Y() /= m_scale.Y();
        //   result.Z() /= m_scale.Z();
        // When division is much more expensive than multiplication,
        // three divisions are replaced by one division and nine
        // multiplications.
        float fSXY = m_scale.X()*m_scale.Y();
        float fSXYZ = fSXY*m_scale.Z();
        float fInvSXYZ = 1.0f/fSXYZ;
        float fInvSXY = fInvSXYZ*m_scale.Z();
        float fInvXScale = fInvSXY*m_scale.Y();
        float fInvYScale = fInvSXY*m_scale.X();
        float fInvZScale = fInvSXYZ*fSXY;
        v.X() *= fInvXScale;
        v.Y() *= fInvYScale;
        v.Z() *= fInvZScale;
	}
}
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* class SphereVolume:                                     */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
SphereVolume::SphereVolume()
: m_center(Vector3::ZERO), m_radius(1.0f)
{
}
/* ------------------------------------------------------- */
SphereVolume::SphereVolume(Vector3 center, float radius)
: m_center(center), m_radius(radius)
{
}
/* ------------------------------------------------------- */
void SphereVolume::load(Stream& stream)
{
	BoundingVolume::load(stream);

	stream.read(m_center);
	stream.read(m_radius);
}
/* ------------------------------------------------------- */
void SphereVolume::link(PtrLinker& linker)
{
	BoundingVolume::link(linker);

	// nothing to do here
}
/* ------------------------------------------------------- */
void SphereVolume::save(Stream& stream) const
{
	BoundingVolume::save(stream);

	stream.write(m_center);
	stream.write(m_radius);
}
/* ------------------------------------------------------- */
int SphereVolume::getDiskUsed() const
{
	return	BoundingVolume::getDiskUsed() +
			sizeof(m_center) +
			sizeof(m_radius);
}
/* ------------------------------------------------------- */
void SphereVolume::setCenter(const Vector3& center)
{
	m_center = center;
}
/* ------------------------------------------------------- */
void SphereVolume::setRadius(float radius)
{
	m_radius = radius;
}
/* ------------------------------------------------------- */
Vector3 SphereVolume::getCenter() const
{
	return m_center;
}
/* ------------------------------------------------------- */
float SphereVolume::getRadius() const
{
	return m_radius;
}
/* ------------------------------------------------------- */
void SphereVolume::computeFromData(const Ptr<VertexData>& vdata)
{
	m_radius = 0.0f;
	m_center = Vector3(0.0f, 0.0f, 0.0f);
	float curDistance = 0.0f;
	
	ArrayPtr<GeometryVertex> vertices = vdata->getGeometryData();

	for (int i = 0; i < vertices.size(); i++)
	{
		m_center += vertices[i].position;
	}
	m_center /= vertices.size();

	for (int i = 0; i < vertices.size(); i++)
	{
		curDistance = (vertices[i].position-m_center).squaredLength();
		if (curDistance > m_radius)
		{
			m_radius = curDistance;
		}
	}
	m_radius = Math<float>::Sqrt(m_radius);
}
/* ------------------------------------------------------- */
void SphereVolume::transform(const Transformation& t)
{
	m_center += t.getTranslation();
	m_radius *= t.norm();
}
/* ------------------------------------------------------- */
int SphereVolume::whichSide(const Plane3& plane) const
{
	float d = plane.distanceTo(m_center);
	if (d > m_radius)
		return 1;
	else if (d < -m_radius)
		return -1;
	else
		return 0;
}
/* ------------------------------------------------------- */
bool SphereVolume::intersects(const Vector3& origin, const Vector3& direction) const
{
	Vector3 v = origin - m_center;
	float a = v.squaredLength() - m_radius*m_radius;
	if (a <= 0.0f)
	{
		return true;
	}
	else
	{
		float b = direction.dot(v);
		if (b >= 0.0f)
			return false;
		return (b*b >= a);
	}
}
/* ------------------------------------------------------- */
bool SphereVolume::intersects(const BoundingVolume* input) const
{
	const SphereVolume* sv = dynamic_cast<const SphereVolume*>(input);
	float dsq = (sv->m_center - m_center).squaredLength();
	return (dsq <= Math<float>::Sqr(sv->m_radius + m_radius));
}
/* ------------------------------------------------------- */
void SphereVolume::operator=(const BoundingVolume* input)
{
	const SphereVolume* sv = dynamic_cast<const SphereVolume*>(input);
	m_center = sv->m_center;
	m_radius = sv->m_radius;
}
/* ------------------------------------------------------- */
void SphereVolume::growToContain(const BoundingVolume* input)
{
	const SphereVolume* sv = dynamic_cast<const SphereVolume*>(input);
	float necRad = (sv->m_center - m_center).length() + sv->m_radius;
	if (m_radius < necRad)
		m_radius = necRad;
}
/* ------------------------------------------------------- */
bool SphereVolume::contains(const Vector3& point) const
{
	return ((point - m_center).squaredLength() <= Math<float>::Sqr(m_radius));
}
/* ------------------------------------------------------- */
BoundingVolume* SphereVolume::copy() const
{
	return new SphereVolume(m_center, m_radius);
}
/* ------------------------------------------------------- */
