/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#include <resource\lvertex.h>
#include <resource\leffect.h>

using namespace Lotus;

int VertexElementSize[14] = { 3*sizeof(float), 0, 0, 3*sizeof(float), 0, 0, 0, 0, 0, 0, 4*sizeof(float), 0, 0, 0 };

/* ------------------------------------------------------- */
/* class TextureDeclaration:                               */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
TextureDeclaration::TextureDeclaration()
: m_numTextureCoordinates(0)
{
}
/* ------------------------------------------------------- */
TextureDeclaration::TextureDeclaration(unsigned int numTexCoorSets, const int* dimensions)
: m_numTextureCoordinates(numTexCoorSets)
{
	assert(numTexCoorSets <= MAX_TEXCOOR);
	for (int i = 0; i < m_numTextureCoordinates; i++)
	{
		m_textureCoordinates[i] = dimensions[i];
	}
}
/* ------------------------------------------------------- */
void TextureDeclaration::load(Stream& stream)
{
	stream.read(&m_textureCoordinates, 8);
	stream.read(m_numTextureCoordinates);
}
/* ------------------------------------------------------- */
void TextureDeclaration::save(Stream& stream)
{
	stream.write(&m_textureCoordinates, 8);
	stream.write(m_numTextureCoordinates);
}
/* ------------------------------------------------------- */
int TextureDeclaration::getTexCoorDim(int stage) const
{
	assert(stage >= 0 && stage < MAX_TEXCOOR);
	return m_textureCoordinates[stage];
}
/* ------------------------------------------------------- */
void TextureDeclaration::setTexCoorDim(int stage, int value)
{
	assert(stage >= 0 && stage < MAX_TEXCOOR && value >= 0);
	m_textureCoordinates[stage] = value;
}
/* ------------------------------------------------------- */
int TextureDeclaration::getNumTexCoor() const
{
	return m_numTextureCoordinates;
}
/* ------------------------------------------------------- */
void TextureDeclaration::setNumTexCoor(int to)
{
	assert(to >= 0 && to <= MAX_TEXCOOR);
	m_numTextureCoordinates = to;
}
/* ------------------------------------------------------- */
int TextureDeclaration::getSize() const
{
	int sum = 0;
	for (int i = 0; i < m_numTextureCoordinates; i++)
	{
		sum += m_textureCoordinates[i];
	}
	return sum*sizeof(float);
}
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* class VertexData:                                     */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */

VertexData::VertexData(TextureDeclaration& tdecl, GeometryType geometryType)
: m_texDecl(tdecl), m_geometryType(geometryType), m_size(0), m_dynamic(false)
{
}
/* ------------------------------------------------------- */
VertexData::VertexData(ArrayPtr<GeometryVertex> gdata, ArrayPtr<unsigned int> idata, ArrayPtr<float> tdata, 
 TextureDeclaration& ttype, GeometryType geometryType)
 : m_gdata(gdata), m_idata(idata), m_tdata(tdata), m_size(gdata.size()), m_indexCount(idata.size()),
	m_geometryType(geometryType), m_texDecl(ttype), m_dynamic(false)
{
}
/* ------------------------------------------------------- */
void VertexData::load(Stream& stream)
{
	Object::load(stream);

	stream.read(m_texDecl);
	stream.read(m_geometryType);
	stream.read(m_size);
	stream.read(m_indexCount);
	
	m_dynamic = false;
	
	GeometryVertex* garr = new GeometryVertex[m_size];
	stream.read(garr, m_size);
	m_gdata = ArrayPtr<GeometryVertex>(garr, m_size);
	
	unsigned int* iarr = new unsigned int[m_indexCount];	
	stream.read(iarr, m_indexCount);
	m_idata = ArrayPtr<unsigned int>(iarr, m_indexCount);

	int tb = m_size*m_texDecl.getSize();
	if (tb > 0)
	{
		float* tarr = new float[tb];
		stream.read(tarr, tb);
		m_tdata = ArrayPtr<float>(tarr, tb);
	}
}
/* ------------------------------------------------------- */
void VertexData::save(Stream& stream) const
{
	Object::save(stream);

	stream.write(m_texDecl);
	stream.write(m_geometryType);
	stream.write(m_size);
	stream.write(m_indexCount);

	if (m_gdata)
		stream.write(m_gdata.toInternal(), m_gdata.size());
	if (m_idata)
		stream.write(m_idata.toInternal(), m_idata.size());
	if (m_tdata)
		stream.write(m_tdata.toInternal(), m_tdata.size());
}
/* ------------------------------------------------------- */
int VertexData::getDiskUsed() const
{
	return Object::getDiskUsed() + sizeof(m_texDecl) + sizeof(m_geometryType) + sizeof(m_size)
		+ sizeof(m_indexCount) +
		((m_gdata) ? sizeof(GeometryVertex)*m_gdata.size() : 0) +
		((m_idata) ? sizeof(unsigned int)*m_idata.size() : 0) +
		((m_tdata) ? sizeof(float)*m_tdata.size() : 0);	
}
/* ------------------------------------------------------- */
void VertexData::setGeometryType(GeometryType type)
{
	m_geometryType = type;
}
/* ------------------------------------------------------- */
GeometryType VertexData::getGeometryType()
{
	return m_geometryType;
}
/* ------------------------------------------------------- */
const TextureDeclaration& VertexData::getTextureDeclaration() const
{
	return m_texDecl;
}
/* ------------------------------------------------------- */
int VertexData::getSize()
{
	return m_size;
}
/* ------------------------------------------------------- */
int VertexData::getIndexCount()
{
	return m_indexCount;
}
/* ------------------------------------------------------- */
const ArrayPtr<GeometryVertex> VertexData::getGeometryData() const
{
	return m_gdata;
}
/* ------------------------------------------------------- */
const ArrayPtr<unsigned int> VertexData::getIndexData() const
{
	return m_idata;
}
/* ------------------------------------------------------- */
const ArrayPtr<float> VertexData::getTextureData() const
{
	return m_tdata;
}
/* ------------------------------------------------------- */
bool VertexData::isDynamic()
{
	return m_dynamic;
}
/* ------------------------------------------------------- */
/* ------------------------------------------------------- */
/* class DynamicVertexData:                                */
/*                      PUBLIC                             */
/*-------------------------------------------------------- */
void DynamicVertexData::setGeometryData(ArrayPtr<GeometryVertex> varray)
{
		
}
/* ------------------------------------------------------- */
void DynamicVertexData::setIndexData(ArrayPtr<unsigned int> iarray)
{
	
}
/* ------------------------------------------------------- */
void DynamicVertexData::setTextureData(ArrayPtr<float> tarray)
{
	
}
/* ------------------------------------------------------- */