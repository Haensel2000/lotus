/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#include "dxbatch.h"

using namespace DX;

unsigned int DX::GetFVF(const TextureDeclaration& tdecl)
{
	unsigned int tfvf = 0;
	switch (tdecl.getNumTexCoor())
	{
	case 0: tfvf |= D3DFVF_TEX0; break;
	case 1: tfvf |= D3DFVF_TEX1; break;
	case 2: tfvf |= D3DFVF_TEX2; break;
	case 3: tfvf |= D3DFVF_TEX3; break;
	case 4: tfvf |= D3DFVF_TEX4; break;
	case 5: tfvf |= D3DFVF_TEX5; break;
	case 6: tfvf |= D3DFVF_TEX6; break;
	case 7: tfvf |= D3DFVF_TEX7; break;
	case 8: tfvf |= D3DFVF_TEX8; break;
	}

	for (int i = 0; i < tdecl.getNumTexCoor(); i++)
	{
		switch (tdecl.getTexCoorDim(i))
		{
		case 1: tfvf |= D3DFVF_TEXCOORDSIZE1(i); break;
		case 2: tfvf |= D3DFVF_TEXCOORDSIZE2(i); break;
		case 3: tfvf |= D3DFVF_TEXCOORDSIZE3(i); break;
		}
	}
	return tfvf;
}

D3D_VertexDeclaration* DX::GetDeclaration(D3D_Device* device, const Ptr<VertexData>& data)
{
	const TextureDeclaration& tdecl = data->getTextureDeclaration();
	D3D_VertexElement* elements = new D3D_VertexElement[4 + tdecl.getNumTexCoor() + 1];
	D3D_VertexElement tmp = {0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0};
	
	// Generate Declaration for the GeometryVertex
	elements[0] = tmp;
	tmp.Offset += 12;
	tmp.Usage = D3DDECLUSAGE_NORMAL;
	elements[1] = tmp;
	tmp.Offset += 12;
	tmp.Type = D3DDECLTYPE_D3DCOLOR;
	tmp.Usage = D3DDECLUSAGE_COLOR;
	elements[2] = tmp;
	tmp.Offset += 4;
	tmp.UsageIndex = 1;
	elements[3] = tmp;

	tmp.Stream = 1;
	tmp.Offset = 0;
	tmp.UsageIndex = 0;
	tmp.Usage = D3DDECLUSAGE_TEXCOORD;
	// Generate Declaration for the TextureVertex
	int i = 0;
	for (i = 0; i < tdecl.getNumTexCoor(); i++)
	{
		switch (tdecl.getTexCoorDim(i))
		{
		case 1: tmp.Type = D3DDECLTYPE_FLOAT1; break;
		case 2: tmp.Type = D3DDECLTYPE_FLOAT2; break;
		case 3: tmp.Type = D3DDECLTYPE_FLOAT3; break;
		}
		elements[i+4] = tmp;
		tmp.UsageIndex++;
		tmp.Offset += sizeof(float)*tdecl.getTexCoorDim(i);
	}
	tmp.Stream = 0xFF;
	tmp.Offset = 0;
	tmp.Type = D3DDECLTYPE_UNUSED;
	tmp.Method = 0;
	tmp.Usage = 0;
	tmp.UsageIndex = 0;
	elements[i+4] = tmp;

	D3D_VertexDeclaration* result;
	HRESULT hr = device->CreateVertexDeclaration(elements, &result);
	delete elements;
	return result;
}

/* ------------------------------------------------------- */
/* class IterateBatch:                                     */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
IterateBatch::IterateBatch(D3D_Device* device, Renderer* renderer)
: GeometryBatch(renderer), m_device(device), m_gbuffer(0), m_tbuffer(0), m_indexbuffer(0), m_declaration(0)
{
}
/* ------------------------------------------------------- */
IterateBatch::~IterateBatch()
{
	if (m_gbuffer)
		m_gbuffer->Release();
	if (m_tbuffer)
		m_tbuffer->Release();
	if (m_indexbuffer)
		m_indexbuffer->Release();
	if (m_declaration)
		m_declaration->Release();
}
/* ------------------------------------------------------- */
bool IterateBatch::uniqueOnly() const
{
	return true;
}
/* ------------------------------------------------------- */
BatchType IterateBatch::getType() const
{
	return Lotus::BT_INSTANCE;
}
/* ------------------------------------------------------- */
void IterateBatch::commit()
{
	if (!m_gbuffer && !m_indexbuffer)
	{
		Ptr<VertexData>& vd = m_registered.front()->getVertexData();

		// create geometry buffer
		m_gsize = vd->getSize() * sizeof(Lotus::GeometryVertex);
		m_device->CreateVertexBuffer(	m_gsize,
										D3DUSAGE_WRITEONLY,
										D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_SPECULAR,
										D3DPOOL_MANAGED,
										&m_gbuffer,
										0 );
		GeometryVertex* gv;
		HRESULT hr = m_gbuffer->Lock(0, 0, reinterpret_cast<void**>(&gv), 0);
		memcpy(gv, vd->getGeometryData().toInternal(), m_gsize);
		m_gbuffer->Unlock();

		// create index buffer
		bool shortIndices = (vd->getSize() <= Lotus::MAX_UNSIGNED_SHORT && !vd->isDynamic());
		m_isize = (shortIndices) ? sizeof(unsigned short) * vd->getIndexCount() : sizeof(unsigned int) * vd->getIndexCount();
		m_device->CreateIndexBuffer(	m_isize,
										D3DUSAGE_WRITEONLY,
										(shortIndices) ? D3DFMT_INDEX16  : D3DFMT_INDEX32,
										D3DPOOL_MANAGED,
										&m_indexbuffer,
										0 );
		if (shortIndices)
		{
			unsigned short* id;
			ArrayPtr<unsigned int> idata = vd->getIndexData();
			hr = m_indexbuffer->Lock(0, 0, reinterpret_cast<void**>(&id), 0);
			for (int i = 0; i < vd->getIndexCount(); i++)
			{
				id[i] = (unsigned short)idata[i];
			}
			m_gbuffer->Unlock();
		}
		else
		{
			unsigned int* id;
			hr = m_indexbuffer->Lock(0, 0, reinterpret_cast<void**>(&id), 0);
			memcpy(gv, vd->getIndexData().toInternal(), m_isize);
			m_gbuffer->Unlock();
		}
		

		// create texture buffer
		m_tsize = vd->getSize() * vd->getTextureDeclaration().getSize();
		if (m_tsize > 0 && !m_tbuffer)
		{
			m_device->CreateVertexBuffer(	m_tsize,
											D3DUSAGE_WRITEONLY,
											GetFVF(vd->getTextureDeclaration()),
											D3DPOOL_MANAGED,
											&m_tbuffer,		
											0 );
			float* td;
			m_tbuffer->Lock(0, 0, reinterpret_cast<void**>(&td), 0);
			memcpy(td, vd->getTextureData().toInternal(), m_tsize);
			m_tbuffer->Unlock();
		}
		else
		{
			m_tbuffer = 0;
		}

		m_declaration = GetDeclaration(m_device, vd);
	}	

}
/* ------------------------------------------------------- */
void IterateBatch::update()
{
	GeometryBatch::update();
}
/* ------------------------------------------------------- */
void IterateBatch::draw()
{
	Ptr<VertexData>& vd = m_registered.front()->getVertexData();	
	m_device->SetStreamSource(0, m_gbuffer, 0, sizeof(Lotus::GeometryVertex));
	if (m_tbuffer)
	{
		m_device->SetStreamSource(1, m_tbuffer, 0, vd->getTextureDeclaration().getSize());
	}
	m_device->SetIndices(m_indexbuffer);
	m_device->SetVertexDeclaration(m_declaration);
	
	Matrix4 worldMatrix;
	CONST D3DXMATRIX* d3dMatrix;
	for (List<InstanceGroup>::Iterator i = m_instanceGroups.begin(); i != false; i++)
	{
		i->renderPass->begin(m_renderer);
		for (int j = 0; j < i->instances.size(); j++)
		{
			i->instances[j]->getWorldTransform().getTransposedTransform(worldMatrix);
			d3dMatrix = (CONST D3DXMATRIX*)(&worldMatrix);	
			m_device->SetTransform(D3DTS_WORLD, d3dMatrix);
			m_device->DrawIndexedPrimitive(	D3DPRIMITIVETYPE(vd->getGeometryType()), 
											0,
											0,
											vd->getSize(),
											0,
											vd->getIndexCount()/3 );
		}
		i->renderPass->end(m_renderer);
	}
	
}
/* ------------------------------------------------------- */