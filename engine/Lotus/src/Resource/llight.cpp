/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#include <resource\llight.h>

using namespace Lotus;

/* ------------------------------------------------------- */
/* class Light:                                            */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
Light::Light()
: m_id(NULL_ID)
{
}
/* ------------------------------------------------------- */
void Light::setID(int id)
{
	m_id = id;
}
/* ------------------------------------------------------- */
int Light::getID() const
{
	return m_id;
}
/* ------------------------------------------------------- */
void Light::begin(Renderer* renderer)
{
	renderer->activateLight(this);
}
/* ------------------------------------------------------- */
void Light::end(Renderer* renderer)
{
	renderer->deactivateLight(this);
}
/* ------------------------------------------------------- */
/* class AmbientLight:                                     */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
LightType AmbientLight::getLightType() const
{
	return LT_AMBIENT;
}
/* ------------------------------------------------------- */
void AmbientLight::load(Stream& stream)
{
	Object::load(stream);

	stream.read(ambient);
	stream.read(diffuse);
	stream.read(specular);
}
/* ------------------------------------------------------- */
void AmbientLight::save(Stream& stream) const
{
	Object::save(stream);

	stream.write(ambient);
	stream.write(diffuse);
	stream.write(specular);
}
/* ------------------------------------------------------- */
int AmbientLight::getDiskUsed() const
{
	return	Object::getDiskUsed() + 
			sizeof(ambient) +
			sizeof(diffuse) +
			sizeof(specular);
}
/* ------------------------------------------------------- */
int AmbientLight::getPriority() const
{
	return PRIORITY;
}
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* class DirectionalLight:                                 */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
LightType DirectionalLight::getLightType() const
{
	return LT_DIRECTIONAL;
}
/* ------------------------------------------------------- */
void DirectionalLight::load(Stream& stream)
{
	AmbientLight::load(stream);

	stream.read(direction);

}
/* ------------------------------------------------------- */
void DirectionalLight::save(Stream& stream) const
{
	AmbientLight::save(stream);

	stream.write(direction);

}
/* ------------------------------------------------------- */
int DirectionalLight::getDiskUsed() const
{
	return	AmbientLight::getDiskUsed() + 
			sizeof(direction);
}
/* ------------------------------------------------------- */
int DirectionalLight::getPriority() const
{
	return PRIORITY;
}
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* class PointLight:                                       */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
LightType PointLight::getLightType() const
{
	return LT_POINT;
}
/* ------------------------------------------------------- */
void PointLight::load(Stream& stream)
{
	Spatial::load(stream);

	stream.read(ambient);
	stream.read(diffuse);
	stream.read(specular);
	stream.read(range);
	stream.read(constant);
	stream.read(linear);
	stream.read(quadratic);
	stream.read(position);
}
/* ------------------------------------------------------- */
void PointLight::save(Stream& stream) const
{
	Spatial::save(stream);

	stream.write(ambient);
	stream.write(diffuse);
	stream.write(specular);
	stream.write(range);
	stream.write(constant);
	stream.write(linear);
	stream.write(quadratic);
	stream.write(position);
}
/* ------------------------------------------------------- */
int PointLight::getDiskUsed() const
{
	return	Spatial::getDiskUsed() + 
			sizeof(ambient) +
			sizeof(diffuse) +
			sizeof(specular) +
			sizeof(range) +
			sizeof(constant) +
			sizeof(linear) +
			sizeof(quadratic) +
			sizeof(position);
}
/* ------------------------------------------------------- */
Vector3 PointLight::getWorldPosition() const
{
	return m_world.apply(position);
}
/* ------------------------------------------------------- */
void PointLight::updateBound()
{
	if (!m_worldBound)
		m_worldBound = newBoundingVolume();
	m_worldBound->setCenter(getWorldPosition());
	m_worldBound->setRadius(0.0f);
}
/* ------------------------------------------------------- */
int PointLight::getPriority() const
{
	return PRIORITY;
}
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* class SpotLight:                                        */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
LightType SpotLight::getLightType() const
{
	return LT_SPOT;
}
/* ------------------------------------------------------- */
void SpotLight::load(Stream& stream)
{
	PointLight::load(stream);

	stream.read(innerAngle);
	stream.read(outerAngle);
	stream.read(falloff);
	stream.read(direction);
}
/* ------------------------------------------------------- */
void SpotLight::save(Stream& stream) const
{
	PointLight::save(stream);

	stream.write(innerAngle);
	stream.write(outerAngle);
	stream.write(falloff);
	stream.write(direction);
}
/* ------------------------------------------------------- */
int SpotLight::getDiskUsed() const
{
	return	PointLight::getDiskUsed() + 
			sizeof(innerAngle) +
			sizeof(outerAngle) +
			sizeof(falloff) +
			sizeof(direction);
}
/* ------------------------------------------------------- */
Vector3 SpotLight::getWorldDirection() const
{
	return m_world.applyVector(direction);
}
/* ------------------------------------------------------- */