#include "..\include\dxdisplay.h"

using namespace DX;

/* class DisplayDevice */

/* private */



/* public */

DisplayDevice::DisplayDevice(PDIRECT3DDEVICE dev, D3DDISPLAYMODE displayMode) : device(dev), displayMode(displayMode), currentFont(0)
{ 
	//device->GetDisplayMode(0, &displayMode);	
	projection = new Projection(device, displayMode.Width / displayMode.Height);
	camera = new Camera(device, projection);
	stdCamera = camera;
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	// Verwendung von bilinearer Textur-Filterung:
    device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
    device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

    device->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
    device->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

    // TexturStageStates für 2 Texturstufen einstellen:

    // Die zu verwendenen Texturkoordinaten festlegen:
    device->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
    device->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 0);
	
    // Dithering verwenden - verbessert die grafische Qualität der Darstellung:
    device->SetRenderState(D3DRS_DITHERENABLE, TRUE);
    
    // speculare Lichtanteile bei der Beleuchtung berücksichtigen: 
    device->SetRenderState(D3DRS_SPECULARENABLE, TRUE);
    
    // Beleuchtung ausschalten:
    device->SetRenderState(D3DRS_LIGHTING, FALSE);

    // z-Buffer einschalten:
	zBuffering = true;
    device->SetRenderState(D3DRS_ZENABLE, TRUE);  
	D3DXMatrixIdentity(&oldWorldMatrix);
	D3DXMatrixIdentity(&curWorldMatrix);

	oldViewMatrix = curViewMatrix = camera->getMatrix();
	oldProjectionMatrix = curProjectionMatrix = projection->getMatrix();
	updateViewportMatrix();
	updateProjTransform();
}

DisplayDevice::~DisplayDevice() 
{ 
	resetCamera();
	if (device) 
		device->Release(); 
	if (camera)
		delete camera;
	if (projection)
		delete projection;
}


Point DisplayDevice::getScreenCoordinates(D3DXVECTOR3 position, D3DXMATRIX* cam)
{
	D3DXMATRIX viewProj;
	if (!cam)
		cam = &camera->getMatrix();
	D3DXMatrixMultiply(&viewProj, cam, &projection->getMatrix());
	float x = position.x;
	float y = position.y;
	float z = position.z;
	float x2 = viewProj._11*x + viewProj._21*y + viewProj._31*z + viewProj._41;
	float y2 = viewProj._12*x + viewProj._22*y + viewProj._32*z + viewProj._42;
	float w2 = viewProj._14*x + viewProj._24*y + viewProj._34*z + viewProj._44;
	float invw2 = 1.0f/w2;
	Point res = getResolution();
	return Point((1.0f + (x2*invw2))*0.5f*res.x, (1.0f + (y2*invw2))*0.5f*res.y);
}

void DisplayDevice::clear( D3DCOLOR color )
{
	DWORD flags = D3DCLEAR_TARGET;
	if (zBuffering)
		flags |= D3DCLEAR_ZBUFFER;
	device->Clear( 0, NULL, flags, color, 1.0f, 0 ); 
}

VertexBuffer* DisplayDevice::createVertexBuffer(size_t elementsize, int elementcount,
	DWORD vertexFormat, DWORD usage, D3DPOOL pool)
{
	VERTEXBUFFER vbuffer;
	if (FAILED(device->CreateVertexBuffer(elementsize*elementcount, usage, vertexFormat, pool, &vbuffer, 0)))
		throw Exception(L"DisplayDevice::createVertexBuffer: CreateVertexBuffer failed.");
	return new VertexBuffer(vbuffer, vertexFormat);
}

void DisplayDevice::renderVertexBuffer(VertexBuffer* vbuffer, D3DPRIMITIVETYPE primitiveType, UINT startVertex, 
	int primitiveCount, int offset)
{
	device->SetFVF(vbuffer->getFVF());
	device->SetStreamSource(0, vbuffer->toInternal(), offset, vbuffer->getElementSize());
	if (primitiveCount < 0)
	{
		switch (primitiveType)
		{
		case D3DPT_POINTLIST:
			primitiveCount = vbuffer->getElementCount() - startVertex;
			break;
		case D3DPT_LINELIST:
			primitiveCount = (vbuffer->getElementCount() - startVertex) / 2;
			break;
		case D3DPT_LINESTRIP:
			primitiveCount = vbuffer->getElementCount() - startVertex - 1;
			break;
		case D3DPT_TRIANGLELIST:
			primitiveCount = (vbuffer->getElementCount() - startVertex) / 3;
			break;
		case D3DPT_TRIANGLESTRIP:
		case D3DPT_TRIANGLEFAN:
			primitiveCount = vbuffer->getElementCount() - startVertex - 2;
			break;
		default:
			throw new Exception(L"DisplayDevice::renderVertexBuffer: primitiveType unknown.");
		}
	}
	device->DrawPrimitive(primitiveType, startVertex,
		(primitiveCount < 0) ? vbuffer->getElementCount() - startVertex : primitiveCount);
}

Texture* DisplayDevice::createTexture(const wchar_t* filePath, unsigned width, unsigned height,
	D3DCOLOR transparentColor, unsigned mipLevels, DWORD usage, D3DFORMAT format, D3DPOOL pool,
	DWORD filter, DWORD mipFilter)
{
	TEXTURE tex;
	D3DXCreateTextureFromFileEx(device, filePath, width, height, mipLevels, usage, format, pool,
		filter, mipFilter, transparentColor, 0, 0, &tex);
	return new Texture(tex);
}

Texture* DisplayDevice::createTexture(unsigned width, unsigned height, unsigned mipLevels, DWORD usage,
	D3DFORMAT format, D3DPOOL pool)
{
	TEXTURE tex;
	D3DXCreateTexture(device, width, height, mipLevels, usage, format, pool, &tex);
	return new Texture(tex);
}

void DisplayDevice::createFont(const string& id, const TCHAR* fontName, DWORD height, DWORD flags)
{
	fonts[id] = CD3DFont(fontName, height, flags);
	fonts[id].InitDeviceObjects(device);
	fonts[id].RestoreDeviceObjects();
	if (!currentFont)
		selectFont(id);

}

void DisplayDevice::selectFont(const string& id)
{
	currentFont = &fonts[id];
}

void DisplayDevice::textOut(FLOAT x, FLOAT y, DWORD color, const TCHAR* text,
	DWORD flags)
{
	if (currentFont)
		currentFont->DrawText(displayMode.Width, displayMode.Height, x, y, color, text, flags);
	else
		throw new Exception(L"DX::DisplayDevice::textOut: no font selected.");
}

void DisplayDevice::textOut(float x, float y, float z, DWORD color, const TCHAR* text, float scaleX, 
	float scaleY, DWORD flags)
{
	if (currentFont)
		currentFont->DrawTextScaled( displayMode.Width, displayMode.Height, x, y, z, scaleX, scaleY,
			color, text, flags);
	else
		throw new Exception(L"DX::DisplayDevice::textOut: no font selected.");
}