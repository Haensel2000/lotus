/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#ifndef _HDR_DXRENDERER_H
#define _HDR_DXRENDERER_H 

#include <system\llist.h>
#include <scenegraph\lrenderer.h>
#include <scenegraph\lcamera.h>
#include <resource\lglobal.h>
#include <resource\lffeffects.h>
#include <resource\llight.h>
#include "dxvertex.h"
#include "dxbatch.h"
#include "dxdecl.h"
#include "dxapplication.h"
#include "dxconvert.h"
#include "dxtimer.h"
#include "dxtexture.h"

using Lotus::List;
using Lotus::Renderer;
using Lotus::RenderTreeLeaf;
using Lotus::RenderTreeNode;
using Lotus::Vector3;
using Lotus::Matrix4;
using Lotus::Camera;

using Lotus::ZBufferState;
using Lotus::TextureEffect;
using Lotus::MaterialEffect;
using Lotus::Light;
using Lotus::LightType;

namespace DX
{

	class DisplayConfiguration
	{
	private:
		unsigned int m_width, m_height;
		unsigned int m_refreshRate;
		bool m_depth32;
	public:
		static DisplayConfiguration Default(D3D_Direct3D* d3d);
		DisplayConfiguration(unsigned int width, unsigned int height, unsigned int refreshRate, bool depth32);

		unsigned int getWidth() const;
		unsigned int getHeight() const;
		void setWidth(unsigned int width);
		void setHeight(unsigned int height);
		unsigned int getRefreshRate() const;
		bool hasDepth32() const;
	};

	struct Adapter
	{
		string name;
		List<DisplayConfiguration> displayConfigurations;
	};

	class DXRenderer : public Renderer
	{
	private:
		static D3D_Direct3D* s_d3d;
		
		D3D_Device* m_device;
		DisplayConfiguration m_displayConfiguration;
		unsigned int m_x, m_y; // only used in window mode
		bool m_fullScreen;

		Timer m_timer;
		double m_frameTime;

		const ZBufferState* m_zBufferState;
		int m_maxLightIndex;
		D3D_Material m_material, m_stdMaterial;

		void createDevice(HWND windowHandle);
	protected:
		virtual bool beginScene();
		virtual void endScene();
	public:
		DXRenderer(unsigned int x = 0, unsigned int y = 0, unsigned int width = 0, unsigned int height = 0);
		DXRenderer(const DisplayConfiguration& displayConfiguration); // full screen
		~DXRenderer();

		static List<Adapter> GetDisplayConfigurations();

		//virtual void initialize();
		virtual GeometryBatch* createGeometryBatch(BatchType type);
		virtual void clearBuffers();
		virtual void displayBackBuffer();

		virtual void setProjectionFoV(float fovVer, float aspect, float min, float max);
		virtual void setProjection(float width, float height, float min, float max);
		virtual void setView(const Vector3& eye, const Vector3& dir, const Vector3& up);
		virtual void setWorldMatrix(const Matrix4& world);

		virtual void setZBufferState(const ZBufferState* state);

		virtual void setTextureEffect(const TextureEffect* effect);
		virtual void setMaterialEffect(const MaterialEffect* effect);

		virtual void activateLight(Light* light);
		virtual void deactivateLight(Light* light);

		virtual Ptr<Texture> createTexture(const char* filepath);

		void attachTo(Application* application);

		void render();


		D3D_Device* device() { return m_device; }
		
	};
}

#endif