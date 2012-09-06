#include "..\include\dxvertex.h"

using namespace DX;

VertexBuffer::~VertexBuffer()
{
	if (vbuffer)
		vbuffer->Release();
}

