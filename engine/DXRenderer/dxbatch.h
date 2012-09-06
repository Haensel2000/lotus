/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#ifndef _HDR_DXBATCH_H
#define _HDR_DXBATCH_H 

#include <scenegraph\lbatch.h>
#include <scenegraph\lrenderer.h>
#include <scenegraph\lgeometry.h>
#include <resource\lvertex.h>
#include <system\lpointer.h>
#include "dxdecl.h"
#include "dxconvert.h"

using Lotus::Ptr;
using Lotus::ArrayPtr;
using Lotus::List;
using Lotus::GeometryBatch;
using Lotus::BatchType;
using Lotus::TextureDeclaration;
using Lotus::VertexData;
using Lotus::Renderer;
using Lotus::GeometryVertex;
using Lotus::InstanceGroup;

namespace DX
{

	unsigned int GetFVF(const TextureDeclaration& tdecl);

	D3D_VertexDeclaration* GetDeclaration(D3D_Device* device, const Ptr<VertexData>& data);

	class IterateBatch : public GeometryBatch
	{
	private:
		D3D_VertexBuffer* m_gbuffer;
		unsigned int m_gsize;
		D3D_VertexBuffer* m_tbuffer;
		unsigned int m_tsize;
		D3D_IndexBuffer* m_indexbuffer;
		unsigned int m_isize;
		
		D3D_VertexDeclaration* m_declaration;

		D3D_Device* m_device;
	public:
		IterateBatch(D3D_Device* device, Renderer* renderer);
		~IterateBatch();

		bool uniqueOnly() const;
		BatchType getType() const;
		void commit();
		void update();
		void draw();
	};
}

#endif