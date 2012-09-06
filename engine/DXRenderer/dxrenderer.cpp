/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#include "dxrenderer.h"

using namespace DX;

D3D_Direct3D* DXRenderer::s_d3d = 0;

/* ------------------------------------------------------- */
/* class DisplayConfiguration:                             */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
DisplayConfiguration::DisplayConfiguration(unsigned int width, unsigned int height,
	unsigned int refreshRate, bool depth32)
	: m_width(width), m_height(height), m_refreshRate(refreshRate), m_depth32(depth32)
{
}
/* ------------------------------------------------------- */
/*                      STATIC                             */
/* ------------------------------------------------------- */
DisplayConfiguration DisplayConfiguration::Default(D3D_Direct3D* d3d)
{
	Adapter defaultAdapter = DXRenderer::GetDisplayConfigurations().front();
	return defaultAdapter.displayConfigurations.front();
}
/* ------------------------------------------------------- */
unsigned int DisplayConfiguration::getWidth() const
{
	return m_width;
}
/* ------------------------------------------------------- */
unsigned int DisplayConfiguration::getHeight() const
{
	return m_height;
}
/* ------------------------------------------------------- */
void DisplayConfiguration::setWidth(unsigned int width)
{
	m_width = width;
}
/* ------------------------------------------------------- */
void DisplayConfiguration::setHeight(unsigned int height)
{
	m_height = height;
}
/* ------------------------------------------------------- */
unsigned int DisplayConfiguration::getRefreshRate() const
{
	return m_refreshRate;
}
/* ------------------------------------------------------- */
bool DisplayConfiguration::hasDepth32() const
{
	return m_depth32;
}
/* ------------------------------------------------------- */
/* class DXRenderer:                                       */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
DXRenderer::DXRenderer(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
: m_fullScreen(false), m_displayConfiguration(width, height, 0, false), m_x(x), m_y(y), m_zBufferState(0),
  m_frameTime(0.0), m_maxLightIndex(0)
{

}
/* ------------------------------------------------------- */
DXRenderer::DXRenderer(const DisplayConfiguration& displayConfiguration)
: m_fullScreen(true), m_displayConfiguration(displayConfiguration), m_zBufferState(0), m_maxLightIndex(0)
{
}
/* ------------------------------------------------------- */
DXRenderer::~DXRenderer()
{
	if (s_d3d)
		s_d3d->Release();
	s_d3d = 0;
	if (m_device)
		m_device->Release();
	//Renderer::~Renderer();
}
/* ------------------------------------------------------- */
GeometryBatch* DXRenderer::createGeometryBatch(BatchType type)
{
	return new IterateBatch(m_device, this);
}
/* ------------------------------------------------------- */
void DXRenderer::clearBuffers()
{
	m_device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(int(m_backgroundColor.R()*255), int(m_backgroundColor.G()*255), int(m_backgroundColor.B()*255)),
		1.0f, 0);
}
/* ------------------------------------------------------- */
void DXRenderer::displayBackBuffer()
{
	m_device->Present(0, 0, 0, 0);
}
/* ------------------------------------------------------- */
void DXRenderer::setProjectionFoV(float fovVer, float aspect, float min, float max)
{
	D3DXMATRIX matrix;
	D3DXMatrixPerspectiveFovLH(&matrix, fovVer, aspect, min, max);
	m_device->SetTransform(D3DTS_PROJECTION, &matrix);
}
/* ------------------------------------------------------- */
void DXRenderer::setProjection(float width, float height, float min, float max)
{
	D3DXMATRIX matrix;
	D3DXMatrixPerspectiveLH(&matrix, width, height, min, max);
	m_device->SetTransform(D3DTS_PROJECTION, &matrix);
}
/* ------------------------------------------------------- */
void DXRenderer::setView(const Vector3& eye, const Vector3& dir, const Vector3& up)
{
	D3DXMATRIX matrix;
	D3DXMatrixLookAtLH(&matrix, &Convert(eye), &Convert(dir), &Convert(up)); 
	m_device->SetTransform(D3DTS_VIEW, &matrix);
}
/* ------------------------------------------------------- */
void DXRenderer::setWorldMatrix(const Matrix4& world)
{
	m_device->SetTransform(D3DTS_WORLD, &Convert(world));
}
/* ------------------------------------------------------- */
void DXRenderer::setZBufferState(const ZBufferState* state)
{
	const ZBufferState* oldState = m_zBufferState;
	m_zBufferState = state;
	if (oldState)
	{
		if (oldState->enabled != m_zBufferState->enabled)
			m_device->SetRenderState(D3DRS_ZENABLE, (m_zBufferState->enabled) ? D3DZB_TRUE : D3DZB_FALSE);
		if (oldState->writable != m_zBufferState->writable)
			m_device->SetRenderState(D3DRS_ZWRITEENABLE, (m_zBufferState->writable) ? TRUE : FALSE);
		if (oldState->compare != m_zBufferState->compare)
			m_device->SetRenderState(D3DRS_ZFUNC, D3DCMPFUNC(m_zBufferState->compare));
	}
	else
	{
		m_device->SetRenderState(D3DRS_ZENABLE, (m_zBufferState->enabled) ? D3DZB_TRUE : D3DZB_FALSE);
		m_device->SetRenderState(D3DRS_ZWRITEENABLE, (m_zBufferState->writable) ? TRUE : FALSE);
		m_device->SetRenderState(D3DRS_ZFUNC, D3DCMPFUNC(m_zBufferState->compare));
	}
}
/* ------------------------------------------------------- */
void DXRenderer::setTextureEffect(const TextureEffect* effect)
{
	if (effect) // activate the effect
	{
		if (effect->getLayerCount() > 0)
		{
			m_device->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_MODULATE );
			//m_device->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_TEXTURE);
			//m_device->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_DIFFUSE );
			m_device->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_DISABLE );
			
			m_device->SetTextureStageState( 0, D3DTSS_COLORARG1, Convert(effect->getBaseArgument()) );
			m_device->SetTextureStageState( 0, D3DTSS_ALPHAARG1, Convert(effect->getBaseArgument()) );
			for (unsigned int i = 0; i < effect->getLayerCount(); i++)
			{
				if (i > 0)
				{
					m_device->SetTextureStageState( i, D3DTSS_COLORARG1, D3DTA_CURRENT );
					m_device->SetTextureStageState( i, D3DTSS_ALPHAARG1, D3DTA_CURRENT );
				}
				m_device->SetTextureStageState( i, D3DTSS_COLORARG2, Convert(effect->getLayer(i)->getColorArgument()) );
				m_device->SetTextureStageState( i, D3DTSS_ALPHAARG2, Convert(effect->getLayer(i)->getAlphaArgument()) );
				m_device->SetTextureStageState( i, D3DTSS_COLOROP, effect->getLayer(i)->getColorOperation() );
				m_device->SetTextureStageState( i, D3DTSS_ALPHAOP, effect->getLayer(i)->getAlphaOperation() );
				
				m_device->SetSamplerState(i, D3DSAMP_MINFILTER, effect->getLayer(i)->getMinificationFilter() );
				m_device->SetSamplerState(i, D3DSAMP_MAGFILTER, effect->getLayer(i)->getMagnificationFilter() );
				m_device->SetSamplerState(i, D3DSAMP_MIPFILTER, effect->getLayer(i)->getMipmapFilter() );
				m_device->SetSamplerState(i, D3DSAMP_ADDRESSU, effect->getLayer(i)->getAddressMode() );
				m_device->SetSamplerState(i, D3DSAMP_ADDRESSV, effect->getLayer(i)->getAddressMode() );
				m_device->SetSamplerState(i, D3DSAMP_ADDRESSW, effect->getLayer(i)->getAddressMode() );

				m_device->SetRenderState(D3DRENDERSTATETYPE(128 + i), effect->getLayer(i)->getWrappingMode());

				if (effect->getLayer(i)->getColorArgument() == Lotus::TA_TEXTURE ||
					effect->getLayer(i)->getAlphaArgument() == Lotus::TA_TEXTURE)
					m_device->SetTexture(i, ((DXTexture*)effect->getLayer(i)->getTexture().toInternal())->toInternal());
			}
		}
	}
	else // deactivate
	{
		m_device->SetTextureStageState(0, D3DTSS_COLOROP, Lotus::TO_DISABLE);
	}
	
}
/* ------------------------------------------------------- */
void DXRenderer::setMaterialEffect(const MaterialEffect* effect)
{
	if (effect)
	{
		m_material.Ambient = Convert(effect->ambient);
		m_material.Diffuse = Convert(effect->diffuse);
		m_material.Specular = Convert(effect->specular);
		m_material.Emissive = Convert(effect->emissive);
		m_material.Power = effect->power;
		m_device->SetMaterial(&m_material);
	}
	else
	{
		m_device->SetMaterial(&m_stdMaterial);
	}
}
/* ------------------------------------------------------- */
void DXRenderer::activateLight(Light* light)
{
	if (light->getID() == Lotus::Light::NULL_ID)
	{
		D3D_Light l;
		memset(&l, 0, sizeof(D3D_Light));
		switch (light->getLightType())
		{
		case Lotus::LT_AMBIENT:
			m_device->SetRenderState(D3DRS_AMBIENT, ConvertUInt(((Lotus::AmbientLight*)light)->ambient));
			return;
		case Lotus::LT_DIRECTIONAL:
			l.Ambient = Convert(((Lotus::DirectionalLight*)light)->ambient);
			l.Diffuse = Convert(((Lotus::DirectionalLight*)light)->diffuse);
			l.Specular = Convert(((Lotus::DirectionalLight*)light)->specular);
			l.Direction = Convert(((Lotus::DirectionalLight*)light)->direction);
			break;
		case Lotus::LT_POINT:
			l.Ambient = Convert(((Lotus::PointLight*)light)->ambient);
			l.Diffuse = Convert(((Lotus::PointLight*)light)->diffuse);
			l.Specular = Convert(((Lotus::PointLight*)light)->specular);
			l.Position = Convert(((Lotus::PointLight*)light)->position);
			l.Range = ((Lotus::PointLight*)light)->range;
			l.Attenuation0 = ((Lotus::PointLight*)light)->constant;
			l.Attenuation1 = ((Lotus::PointLight*)light)->linear;
			l.Attenuation2 = ((Lotus::PointLight*)light)->quadratic;
			break;
		case Lotus::LT_SPOT:
			l.Ambient = Convert(((Lotus::SpotLight*)light)->ambient);
			l.Diffuse = Convert(((Lotus::SpotLight*)light)->diffuse);
			l.Specular = Convert(((Lotus::SpotLight*)light)->specular);
			l.Position = Convert(((Lotus::SpotLight*)light)->position);
			l.Range = ((Lotus::SpotLight*)light)->range;
			l.Attenuation0 = ((Lotus::SpotLight*)light)->constant;
			l.Attenuation1 = ((Lotus::SpotLight*)light)->linear;
			l.Attenuation2 = ((Lotus::SpotLight*)light)->quadratic;
			l.Theta = ((Lotus::SpotLight*)light)->innerAngle;
			l.Phi = ((Lotus::SpotLight*)light)->outerAngle;
			l.Falloff = ((Lotus::SpotLight*)light)->falloff;
			l.Direction = Convert(((Lotus::SpotLight*)light)->direction);
			break;
		}
		l.Type = D3DLIGHTTYPE(light->getLightType());
		m_device->SetLight(m_maxLightIndex, &l);
		light->setID(m_maxLightIndex++);
	}
	m_device->LightEnable(light->getID(), TRUE);
}	
/* ------------------------------------------------------- */
void DXRenderer::deactivateLight(Light* light)
{
	m_device->LightEnable(light->getID(), FALSE);
}
/* ------------------------------------------------------- */
Ptr<Texture> DXRenderer::createTexture(const char* filepath)
{
	D3D_Texture* tex;
	D3DXCreateTextureFromFileEx(m_device, filepath, D3DX_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &tex);
	return Ptr<Texture>(0);
}
/* ------------------------------------------------------- */
void DXRenderer::attachTo(Application* application)
{
	Renderer::initialize();
	HWND whandle;
	if (m_displayConfiguration.getWidth() > 0 && m_displayConfiguration.getHeight() > 0 && !m_fullScreen)
	{
		whandle = application->getWindowHandle(m_x, m_y, m_displayConfiguration.getWidth(), m_displayConfiguration.getHeight());
	}
	else
	{
		whandle = application->getWindowHandle();
		if (!m_fullScreen)
		{
			m_displayConfiguration.setWidth(application->getWidth());
			m_displayConfiguration.setHeight(application->getHeight());
		}
	}
	createDevice(whandle);

	//setZBufferState(ZBufferState::DEFAULT.toInternal());

	Ptr<Camera> camera = new Camera();
	camera->setView(Vector3(0, 0, 0), Vector3(0, 0, 1), Vector3(0, 1, 0));
	camera->setProjection(Lotus::Math<float>::PI / 4.0f, (float)m_displayConfiguration.getWidth()/(float)(m_displayConfiguration.getHeight()), 0.5f, 40.0f);
	setCamera(camera);
}
/* ------------------------------------------------------- */
void DXRenderer::render()
{
	m_timer.begin();
	drawScene(m_frameTime);
	m_frameTime = m_timer.timeMS()*0.001;
}
/* ------------------------------------------------------- */
/*                      PROTECTED                          */
/* ------------------------------------------------------- */
bool DXRenderer::beginScene()
{
	bool result = Renderer::beginScene();
	m_device->BeginScene();
	return result;
}
/* ------------------------------------------------------- */
void DXRenderer::endScene()
{
	Renderer::endScene();
	m_device->EndScene();
}
/* ------------------------------------------------------- */
/*                      PRIVATE                            */
/* ------------------------------------------------------- */
void DXRenderer::createDevice(HWND windowHandle)
{
	if (!s_d3d)
		s_d3d = Direct3DCreate9(D3D_SDK_VERSION);
	
	D3DDISPLAYMODE d3ddm;
	if (!m_fullScreen)
	{	
        s_d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm); 
	}
	
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory( &d3dpp, sizeof(d3dpp) );
	d3dpp.BackBufferWidth =  (m_fullScreen) ? m_displayConfiguration.getWidth() : 0;
	d3dpp.BackBufferHeight = (m_fullScreen) ? m_displayConfiguration.getHeight() : 0;
	d3dpp.BackBufferFormat = (m_fullScreen) ? ((m_displayConfiguration.hasDepth32()) ? D3DFMT_X8R8G8B8 : D3DFMT_R5G6B5) 
											: d3ddm.Format;
	d3dpp.hDeviceWindow = 0;
	d3dpp.Windowed = (m_fullScreen) ? FALSE : TRUE;
	d3dpp.FullScreen_RefreshRateInHz = (m_fullScreen) ? m_displayConfiguration.getRefreshRate() : 0;
	d3dpp.SwapEffect = (m_fullScreen) ? D3DSWAPEFFECT_FLIP : D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	HRESULT hr = s_d3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, windowHandle,
		D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_device );
	assert(hr == D3D_OK);

	m_device->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//m_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_device->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	m_device->SetRenderState(D3DRS_SPECULARMATERIALSOURCE, D3DMCS_MATERIAL);

	D3D_Material mat;
	memset(&mat, 0, sizeof(D3D_Material));
	mat.Diffuse = mat.Specular = Convert(Lotus::Color4(0.0, 1.0, 0.0, 0.0));
	mat.Ambient.r = 0.2f;
	mat.Ambient.g = 0.2f;
	mat.Ambient.b = 0.2f;
	m_device->SetMaterial(&mat);
}
/* ------------------------------------------------------- */
/*                      STATIC                             */
/* ------------------------------------------------------- */
List<Adapter> DXRenderer::GetDisplayConfigurations()
{
	if (!s_d3d)
		s_d3d = Direct3DCreate9(D3D_SDK_VERSION);
	
	List<Adapter> result;

	D3DADAPTER_IDENTIFIER9 adapterID;
	for (int i = 0; i < s_d3d->GetAdapterCount(); i++)
	{
		s_d3d->GetAdapterIdentifier(i, 0, &adapterID);
		Adapter adapter;
		adapter.name = adapterID.Description;
		for (unsigned int j = 0; j < s_d3d->GetAdapterModeCount(i, D3DFMT_X8R8G8B8); j++)
		{
			D3DDISPLAYMODE displayMode;
			s_d3d->EnumAdapterModes(i, D3DFMT_X8R8G8B8, j, &displayMode);
			adapter.displayConfigurations.insertFront(
				DisplayConfiguration(displayMode.Width, displayMode.Height, displayMode.RefreshRate,
					(displayMode.Format == D3DFMT_X8R8G8B8) ? true : false));
		}
		result.insertFront(adapter);
	}

	return result;
}
/* ------------------------------------------------------- */