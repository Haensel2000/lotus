#pragma once

#include "dxinclude.h"
#include "dxbasic.h"
#include "dxvertex.h"
#include "dxtexture.h"
#include "dxmatrix.h"
#include "d3dfont.h"
#include <map>
#include <string>

namespace DX
{
	using std::map;
	using std::string;

	class DisplayDevice
	{
		private: 
			PDIRECT3DDEVICE device;
			Camera* camera;
			Camera* stdCamera;
			Projection* projection;

			D3DDISPLAYMODE displayMode;

			map<D3DRENDERSTATETYPE, DWORD> oldRenderState;
			map<D3DSAMPLERSTATETYPE, DWORD> oldSamplerState;
			map<string, CD3DFont> fonts;
			CD3DFont* currentFont;
			D3DXMATRIX oldWorldMatrix;
			D3DXMATRIX oldViewMatrix;
			D3DXMATRIX oldProjectionMatrix;

			D3DXMATRIX curWorldMatrix;
			D3DXMATRIX curViewMatrix;
			D3DXMATRIX curProjectionMatrix;

			D3DXMATRIX viewportMatrix;
			D3DXMATRIX ptransform;
			bool ptransformIsCurrent;

			void updateProjTransform()
			{
				D3DXMATRIX wv, ps;
				D3DXMatrixMultiply(&wv, &curWorldMatrix, &curViewMatrix);
				D3DXMatrixMultiply(&ps, &curProjectionMatrix, &viewportMatrix);
				D3DXMatrixMultiply(&ptransform, &wv, &ps); 
				ptransformIsCurrent = true;
			}

			bool zBuffering;
		public:
			DisplayDevice(PDIRECT3DDEVICE device, D3DDISPLAYMODE displayMode);

			~DisplayDevice();

			PDIRECT3DDEVICE toInternal() { return device; }
			
			void clear( D3DCOLOR color = D3DCOLOR_XRGB(0, 0, 0) );
			void beginScene() { device->BeginScene(); }
			void endScene() { device->EndScene(); }
			void present() { device->Present( 0, 0, 0, 0 ); }
			Point getResolution() { return Point(displayMode.Width, displayMode.Height); }
			Point getScreenCoordinates(D3DXVECTOR3 position, D3DXMATRIX* camera = 0);

			void setCamera(Camera* cam)
			{
				camera = cam;
			}

			void resetCamera()
			{
				camera = stdCamera;
			}

			// customization functions, which give direct Access to IDirect3DDevice9 Methods
			void setRenderState(D3DRENDERSTATETYPE renderStateType, DWORD value)
			{
				DWORD tmp;
				device->GetRenderState(renderStateType, &tmp);
				oldRenderState[renderStateType] = tmp;
				device->SetRenderState(renderStateType, value);				
			}
			void setSamplerState(DWORD sampler, D3DSAMPLERSTATETYPE samplerStateType, DWORD value)
			{
				DWORD tmp;
				device->GetSamplerState(sampler, samplerStateType, &tmp);
				oldSamplerState[samplerStateType] = tmp;
				device->SetSamplerState(sampler, samplerStateType, value);	
			}

			DWORD getRenderState(D3DRENDERSTATETYPE renderStateType)
			{
				DWORD tmp;
				device->GetRenderState(renderStateType, &tmp);
				return tmp;
			}

			// helper functions, which give access to IDirect3DDevice9 functionality
			void resetRenderState(D3DRENDERSTATETYPE renderStateType)
			{
				if (oldRenderState.find(renderStateType) != oldRenderState.end())
					device->SetRenderState(renderStateType, oldRenderState[renderStateType]);
			}
			void resetSamplerState(int sampler, D3DSAMPLERSTATETYPE samplerStateType)
			{
				if (oldSamplerState.find(samplerStateType) != oldSamplerState.end())
					device->SetSamplerState(sampler, samplerStateType, oldSamplerState[samplerStateType]);
			}

			Camera* getCamera() { return camera; }
			Projection* getProjection() { return projection; }
			D3DXVECTOR2 getViewingWindow() { return projection->getViewingWindow(); }

			void setWorldMatrix(D3DXMATRIX* matrix) 
			{ 
				oldWorldMatrix = curWorldMatrix;
				device->SetTransform(D3DTS_WORLD, matrix);
				curWorldMatrix = *matrix;
				ptransformIsCurrent = false;
			}
			void setViewMatrix(D3DXMATRIX* matrix) 
			{ 
				oldViewMatrix = curViewMatrix;
				device->SetTransform(D3DTS_VIEW, matrix);
				curViewMatrix = *matrix;
				ptransformIsCurrent = false;
			}
			void setViewMatrixFromCamera()
			{
				setViewMatrix(&camera->getMatrix());
			}
			void setProjectionMatrix(D3DXMATRIX* matrix) 
			{ 
				oldProjectionMatrix = curProjectionMatrix;
				device->SetTransform(D3DTS_PROJECTION, matrix);
				curProjectionMatrix = *matrix;
				ptransformIsCurrent = false;
			}
			D3DXMATRIX getWorldMatrix()
			{
				D3DXMATRIX result;
				device->GetTransform(D3DTS_WORLD, &result);
				return result;
			}
			void resetWorldMatrix()
			{
				device->SetTransform(D3DTS_WORLD, &oldWorldMatrix);
			}
			void resetViewMatrix()
			{
				device->SetTransform(D3DTS_VIEW, &oldViewMatrix);
			}
			void resetProjectionMatrix()
			{
				device->SetTransform(D3DTS_PROJECTION, &oldProjectionMatrix);
			}

			void setAlphaBlending(bool on)
			{			
				setRenderState(D3DRS_ALPHABLENDENABLE, (on == true) ? TRUE : FALSE);
			}
			D3DBLEND getAlphaBlendingSource()
			{
				return (D3DBLEND)getRenderState(D3DRS_SRCBLEND);
			}
			D3DBLEND getAlphaBlendingDestination()
			{
				return (D3DBLEND)getRenderState(D3DRS_DESTBLEND);
			}
			void setAlphaBlendingSource(D3DBLEND src)
			{
				setRenderState(D3DRS_SRCBLEND, src);
			}
			void setAlphaBlendingDestination(D3DBLEND src)
			{
				setRenderState(D3DRS_DESTBLEND, src);
			}
			void resetAlphaBlending()
			{
				resetRenderState(D3DRS_ALPHABLENDENABLE);
			}
			void setZBuffering(bool on)
			{
				setRenderState(D3DRS_ZENABLE, (on == true) ? TRUE : FALSE);
			}
			void resetZBuffering()
			{
				resetRenderState(D3DRS_ZENABLE);
			}
			void setLighting(bool on)
			{
				setRenderState(D3DRS_LIGHTING, (on == true) ? TRUE : FALSE);
			}
			void resetLighting()
			{
				resetRenderState(D3DRS_LIGHTING);
			}

			void setTexture(int stage, Texture* texture)
			{
				device->SetTexture(stage, (texture) ? texture->toInternal() : 0);
			}


			VertexBuffer* createVertexBuffer(size_t elementsize, int elementcount, DWORD vertexFormat, DWORD usage = D3DUSAGE_WRITEONLY, 
				D3DPOOL pool = D3DPOOL_MANAGED);
			void renderVertexBuffer(VertexBuffer* vbuffer, D3DPRIMITIVETYPE primitiveType, UINT startVertex = 0, 
				int primitiveCount = -1, int offset = 0);

			Texture* createTexture(const wchar_t* filePath, unsigned width = D3DX_DEFAULT, 
				unsigned height = D3DX_DEFAULT, D3DCOLOR transparentColor = D3DCOLOR_XRGB(0, 0, 0),
				unsigned mipLevels = D3DX_DEFAULT, DWORD usage = 0, D3DFORMAT format = D3DFMT_UNKNOWN,
				D3DPOOL pool = D3DPOOL_MANAGED, DWORD filter = D3DX_FILTER_TRIANGLE | D3DX_FILTER_MIRROR | D3DX_FILTER_DITHER,
				DWORD mipFilter = D3DX_FILTER_BOX | D3DX_FILTER_MIRROR | D3DX_FILTER_DITHER);

			Texture* createTexture(unsigned width = D3DX_DEFAULT, unsigned height = D3DX_DEFAULT,
				unsigned mipLevels = D3DX_DEFAULT, DWORD usage = 0, D3DFORMAT format = D3DFMT_UNKNOWN,
				D3DPOOL pool = D3DPOOL_MANAGED);

			void createFont(const string& id, const TCHAR* fontName, DWORD height, DWORD flags=0L);
			void selectFont(const string& id);
			void textOut(FLOAT x, FLOAT y, DWORD color, const TCHAR* text, DWORD flags=0L);
			void textOut(float x, float y, float z, DWORD color, const TCHAR* text, float scaleX = 1.0f, 
				float scaleY = 1.0f, DWORD flags = 0L);


			void setLight(int index, D3DLIGHT9* light)
			{
				device->SetLight(index, light);
			}

			void lightEnable(int index, BOOL to)
			{
				device->LightEnable(index, to);
			}

			void setMaterial(D3DMATERIAL9* material)
			{
				device->SetMaterial(material);
			}

			D3DVIEWPORT9 getViewport()
			{
				D3DVIEWPORT9 res;
				device->GetViewport(&res);
				return res;
			}

			void updateViewportMatrix()
			{
				D3DVIEWPORT9 vport = getViewport();
				memset(&viewportMatrix, 0, sizeof(D3DXMATRIX));
				viewportMatrix._11 = (vport.Width/2);
				viewportMatrix._22 = -float(vport.Height/2);
				viewportMatrix._33 = (vport.MaxZ - vport.MinZ);
				viewportMatrix._41 = (vport.X + vport.Width/2);
				viewportMatrix._42 = (vport.Y + vport.Height/2);
				viewportMatrix._43 = vport.MinZ;
				viewportMatrix._44 = 1;	
				ptransformIsCurrent = false;
			}

			D3DXVECTOR2 project(D3DXVECTOR3& vec)
			{
				if (!ptransformIsCurrent)
					updateProjTransform();
				
				D3DXVECTOR3 tmp;
				D3DXVec3TransformCoord(&tmp, &vec, &ptransform);
				return D3DXVECTOR2(tmp.x, tmp.y);
			}

			void getViewFrustumPlanes(D3DXPLANE plane[6])
			{
				camera->getViewFrustumPlanes(plane);
				
				
				
				

			}

	};
}