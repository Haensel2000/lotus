
#pragma once

#include "dxinclude.h"
#include "dxplatform.h"

using std::exception;

namespace DX
{

	typedef unsigned long Flag;
	enum Axis { X_AXIS, Y_AXIS, Z_AXIS };

	typedef LPDIRECTINPUTDEVICE8 PINPUTDEVICE;
	typedef LPDIRECT3DDEVICE9 PDIRECT3DDEVICE;
	typedef LPDIRECT3D9 PDIRECT3D;
	typedef LPDIRECTINPUT8 PINPUT;

	typedef D3DVIEWPORT9 VIEWPORT;
	typedef LPDIRECT3DVERTEXBUFFER9 VERTEXBUFFER;
	typedef LPDIRECT3DINDEXBUFFER9 INDEXBUFFER;
	typedef LPDIRECT3DSURFACE9 SURFACE;
	typedef LPDIRECT3DTEXTURE9 TEXTURE;
	typedef LPDIRECT3DCUBETEXTURE9 CUBETEXTURE;
	typedef D3DMATERIAL9 MATERIAL;
	typedef D3DLIGHT9 LIGHT;

	struct Point : public POINT
	{
		int x;
		int y;

		Point(int x, int y) : x(x), y(y) {}
	};

	class Exception
	{
		private:
			const wchar_t* msg;
		public:
			Exception(const wchar_t* msg) : msg(msg) {}
			const wchar_t* getMessage() { return msg; }
	};

	const D3DXVECTOR3 VERTICAL = D3DXVECTOR3(0, 1, 0);
	const D3DXVECTOR3 FRONT = D3DXVECTOR3(0, 0, 1);

	D3DXVECTOR3 mul(D3DXMATRIX mat, D3DXVECTOR3 vec);

};