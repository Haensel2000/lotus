/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#ifndef _HDR_DXDECL_H
#define _HDR_DXDECL_H 

#include <d3d9.h>
#include <d3dx9.h>
#include <dxerr.h>
#include <dxfile.h>

namespace DX
{
	typedef IDirect3DVertexBuffer9 D3D_VertexBuffer;
	typedef IDirect3DIndexBuffer9 D3D_IndexBuffer;
	typedef IDirect3D9 D3D_Direct3D;
	typedef IDirect3DDevice9 D3D_Device;
	typedef IDirect3DVertexDeclaration9 D3D_VertexDeclaration;
	typedef D3DVERTEXELEMENT9 D3D_VertexElement;

	typedef IDirect3DTexture9 D3D_Texture;
	typedef D3DLIGHT9 D3D_Light;
	typedef D3DMATERIAL9 D3D_Material;

	typedef D3DXVECTOR3 D3D_Vector;
	typedef D3DXMATRIX D3D_Matrix;
}

#endif