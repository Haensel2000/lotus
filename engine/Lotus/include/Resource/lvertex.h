/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#ifndef _HDR_LVERTEX_H
#define _HDR_LVERTEX_H

#include <math\lvector.h>
#include <math\lmath.h>
#include <system\lstream.h>
#include <scenegraph\lsgbase.h>
#include <system\lbitset.h>

namespace Lotus
{

	class GeometryData;

	enum GeometryType
	{
		GT_POLYPOINT = 1,
		GT_POLYLINE_SEGMENTS = 2,
		GT_POLYLINE_OPEN = 3,
		GT_TRIMESH = 4,
		GT_MAX
	};

	enum VertexElement
	{
		VT_POSITION = 0,
		VT_BLENDWEIGHT = 1,
		VT_BLENDINDICES = 2,
		VT_NORMAL = 3,
		VT_PSIZE = 4,
		//VT_TEXCOORD = 5,
		VT_TANGENT = 6,
		VT_BINORMAL = 7,
		VT_TESSFACTOR = 8,
		VT_POSITIONT = 9,
		VT_COLOR = 10,
		VT_FOG = 11,
		VT_DEPTH = 12,
		VT_SAMPLE = 13,
		VT_TEXCOORD_0 = 14,
		VT_TEXCOORD_1 = 15,
		VT_TEXCOORD_2 = 16,
		VT_TEXCOORD_3 = 17,
		VT_TEXCOORD_4 = 18,
		VT_TEXCOORD_5 = 19,
		VT_TEXCOORD_6 = 20,
		VT_TEXCOORD_7 = 21,
		VT_MAX = 22
		
	};
	
	static int VertexElementSize[VT_MAX];



	class TextureDeclaration
	{
	public:
		const static int MAX_TEXCOOR = 8;
	private:
		int m_textureCoordinates[MAX_TEXCOOR];
		int m_numTextureCoordinates;
	public:
		TextureDeclaration();
		TextureDeclaration(unsigned int numTexCoorSets, const int* dimensions); 

		void load(Stream& stream);
		void save(Stream& stream);

		int getTexCoorDim(int stage) const;
		void setTexCoorDim(int stage, int value);
		int getNumTexCoor() const;
		void setNumTexCoor(int to);

		int getSize() const;
	};


	struct GeometryVertex
	{
		Vector3 position;
		Vector3 normal;
		unsigned int color0, color1;
	};
	
	/* class VertexData:
	 * This class represents the abstract concept of a collection of vertices.
	 * It can be combined with an index buffer to connect vertices. The implementation
	 * depends on the graphics api. Therefore this class is a baseclass for 
	 * the specific implementations. It is not guaranteed that a vertex buffer maps
	 * exactly to a vertex buffer in DirectX, since batching strategies may be applied. */
	class VertexData : public Object
	{
	protected:

		TextureDeclaration m_texDecl;
		GeometryType m_geometryType;
		int m_size;
		int m_indexCount;
		bool m_dynamic;


		// platform independent representation of the data
		ArrayPtr<GeometryVertex> m_gdata;
		ArrayPtr<unsigned int> m_idata;
		ArrayPtr<float> m_tdata;
	public:
		VertexData(ArrayPtr<GeometryVertex> gdata, ArrayPtr<unsigned int> idata, ArrayPtr<float> tdata, 
			TextureDeclaration& ttype, GeometryType geometryType = GT_TRIMESH);
		VertexData(TextureDeclaration& ttype = TextureDeclaration(), GeometryType geometryType = GT_TRIMESH);

		virtual void load(Stream& stream);
		virtual void save(Stream& stream) const;
		virtual int getDiskUsed() const;	

		void setGeometryType(GeometryType type);
		GeometryType getGeometryType();
		const TextureDeclaration& getTextureDeclaration() const;
		int getSize(); 
		int getIndexCount();

		const ArrayPtr<GeometryVertex> getGeometryData() const;
		const ArrayPtr<unsigned int> getIndexData() const;
		const ArrayPtr<float> getTextureData() const;

		virtual bool isDynamic();

		friend GeometryData;
	};

	class DynamicVertexData : public VertexData
	{
	private:
	public:
		void setGeometryData(ArrayPtr<GeometryVertex> varray);
		void setIndexData(ArrayPtr<unsigned int> iarray);
		void setTextureData(ArrayPtr<float>	tarray);
	};

}

#endif