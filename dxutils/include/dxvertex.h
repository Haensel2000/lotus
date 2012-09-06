#pragma once

#include "dxinclude.h"
#include "dxbasic.h"
#include <vector>

namespace DX
{
	using std::vector;

	class VertexBuffer
	{
		private:
			VERTEXBUFFER vbuffer;
			size_t elementsize;
			int elementcount;
			DWORD fvf;
		public:
			VertexBuffer(VERTEXBUFFER vbuffer, DWORD fvf) 
				: vbuffer(vbuffer), fvf(fvf), elementsize(0), elementcount(0) {}
			~VertexBuffer();

			template <class T> void addData(T* data, int count)
			{
				insertData(elementcount, data, count);
			}

			// one offset represents one T
			template <class T> void insertData(int offset, T* data, int size)
			{
				if (elementsize == 0)
					elementsize = sizeof(T);
				else if (elementsize != sizeof(T))
					throw new Exception(L"VertexBuffer::addData: size of data is invalid.");

				elementcount += size;
				T* buffer = 0;
				vbuffer->Lock(offset*sizeof(T), size*sizeof(T), reinterpret_cast<void**>(&buffer), 0);
				if (buffer != 0)
					memcpy(buffer, data, size*sizeof(T));
				else
					throw new Exception(L"DX::VertexBuffer::insertData: could not lock vertexbuffer.");
				vbuffer->Unlock();
			}

			template <class T> T* lock(int offset, int count)
			{
				T* result = 0;
				if (elementsize == 0)
					elementsize = sizeof(T);
				else if (elementsize != sizeof(T))
					throw new Exception(L"VertexBuffer::addData: size of data is invalid.");
				elementcount += count;
				vbuffer->Lock(offset*sizeof(T), count*sizeof(T), reinterpret_cast<void**>(&result), 0);
				return result;
			}

			void unlock()
			{
				vbuffer->Unlock();
			}

			size_t getElementSize() { return elementsize; }
			DWORD getFVF() { return fvf; }
			int getElementCount() { return elementcount; }
			VERTEXBUFFER toInternal() { return vbuffer; }
	};
}