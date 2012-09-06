#include "..\include\dxbasic.h"

D3DXVECTOR3 DX::mul(D3DXMATRIX mat, D3DXVECTOR3 vec)
{
	return D3DXVECTOR3(vec.x*mat._11 + vec.y*mat._21 + vec.z*mat._31,
					   vec.x*mat._12 + vec.y*mat._22 + vec.z*mat._32,
					   vec.x*mat._13 + vec.y*mat._23 + vec.z*mat._33);
}