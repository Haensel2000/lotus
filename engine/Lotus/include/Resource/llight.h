/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#ifndef _HDR_LLIGHT_H
#define _HDR_LLIGHT_H

#include <scenegraph\lspatial.h>
#include <scenegraph\lrenderer.h>
#include <resource\leffect.h>
#include <math\lcolor.h>

namespace Lotus
{
	enum LightType
	{
		LT_AMBIENT = 0,
		LT_POINT = 1,
		LT_SPOT = 2,
		LT_DIRECTIONAL = 3,				
		LT_MAX
	};

	class Light : public Effect
	{
	private:
		int m_id;
	public:
		static const int NULL_ID = -1;

		Light();
		void setID(int id);
		int getID() const;
		virtual LightType getLightType() const = 0;
		virtual void begin(Renderer* renderer);
		virtual void end(Renderer* renderer);
	};

	class AmbientLight : public Light
	{
	public:		
		static const int PRIORITY = 200;

		virtual LightType getLightType() const;
		virtual void load(Stream& stream);
		virtual void save(Stream& stream) const;
		virtual int getDiskUsed() const;
		
		Color4 ambient;
		Color4 diffuse;
		Color4 specular;	
	
		virtual int getPriority() const;
	};

	class DirectionalLight : public AmbientLight
	{
	public:		
		static const int PRIORITY = 300;

		virtual LightType getLightType() const;
		virtual void load(Stream& stream);
		virtual void save(Stream& stream) const;
		virtual int getDiskUsed() const;
		
		
		Vector3 direction;
		virtual int getPriority() const;
		
	};

	class PointLight : public Light, public Spatial
	{
	public:		
		static const int PRIORITY = 300;

		virtual LightType getLightType() const;
		virtual void load(Stream& stream);
		virtual void save(Stream& stream) const;
		virtual int getDiskUsed() const;
		
		Color4 ambient;
		Color4 diffuse;
		Color4 specular;
		float range;
		float constant;
		float linear;
		float quadratic;
		Vector3 position;

		Vector3 getWorldPosition() const;
		void updateBound();

		virtual int getPriority() const;
	};

	class SpotLight : public PointLight
	{
	public:
		virtual LightType getLightType() const;
		virtual void load(Stream& stream);
		virtual void save(Stream& stream) const;
		virtual int getDiskUsed() const;

		float innerAngle;
		float outerAngle;
		float falloff;
		Vector3 direction;

		Vector3 getWorldDirection() const;
	};
}

#endif