/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#ifndef _HDR_DXVERTEX_H
#define _HDR_DXVERTEX_H 

#include <resource\lvertex.h>
#include <system\larray.h>
#include <system\lpointer.h>
#include "dxdecl.h"

using Lotus::Array;
using Lotus::ArrayPtr;
using Lotus::TextureDeclaration;
using Lotus::GeometryVertex;
using Lotus::GeometryType;

namespace DX
{

	struct TextureVBuffer
	{
		D3D_VertexBuffer* vbuffer;
		TextureDeclaration declaration;

		D3D_VertexDeclaration* getVertexDeclaration();
	};

	struct IndexBuffer
	{
		D3D_IndexBuffer* ibuffer;
		bool isShort;
	};

	

	class DXGeometryData : public Lotus::VertexData
	{
	private:
		D3D_VertexDeclaration *m_gDecl, *m_tDecl/*, *m_aDecl, *m_iDecl*/;
	protected:
	public:
		DXGeometryData(TextureDeclaration& ttype, GeometryType geometryType = Lotus::GT_TRIMESH,
			bool dynamic = false);

		
	};
}

#endif