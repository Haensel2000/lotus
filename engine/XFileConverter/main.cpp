
#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <lotus.h>
#include <dxr.h>

#include <rmxftmpl.h>
#include <rmxfguid.h>

using namespace std;
using namespace Lotus;
using namespace DX;

/*IDirect3D9* d3d;
IDirect3DDevice9* device;
MeshHierarchy alloc;
LPD3DXFRAME frameRoot;
LPD3DXANIMATIONCONTROLLER animController;*/

char* sp;
int pos = 0;

SIZE_T fileSize;

SceneGraph sgraph(0, 1000);

bool swapYZ = false;

int materialIndex = 0;
int currentMaterialIndex = 0;

struct VertexPosition
{
	Vector3 position;
	unsigned int origIndex;
};

map<Vector3, vector<int> > positions;
vector<int> usedVertices;
map<int, int> duplicated;

DXRenderer renderer;

String GetName(ID3DXFileData* data)
{
	SIZE_T len;
	char* ch;
	data->GetName(0, &len);
	if (len > 0)
	{
		ch = new char[len];
		data->GetName(ch, &len);
	}
	else
	{
		ch = new char[1];
		ch = '\0';
	}
	return String(ch);
}

void AssignVector(Vector3& dst, const Vector3& src, bool swapYZ)
{
	if (swapYZ)
	{
		dst[0] = src[0];
		dst[1] = src[2];
		dst[2] = src[1];
	}
	else
	{
		dst = src;
	}
}

void SwapYZ(Vector3& v)
{
	float tmp = v[1];
	v[1] = v[2];
	v[2] = tmp;
}

void processData(ID3DXFileData* data, Object* context)
{
	sp[pos] = ' ';
	pos += 2;
	sp[pos] = '\0';

	GUID type;
	data->GetType(&type);
	
	Object* newContext = 0;

	if (type == TID_D3DRMFrame)
	{
		String str = GetName(data);
		cout << sp << "FRAME: " << str.toCharArray() << endl;
		Group* g = new Group();
		g->setName(str);
		g->setParent(((Spatial*)context));
		
		if (context == 0) // root frame
		{
			sgraph.add(g);
		}		
		else
		{
			Group* parent = dynamic_cast<Group*>(context);
			assert(parent);
			parent->getChildren().insertFront(g);
		}

		newContext = g;	
	}
	else if (type == TID_D3DRMMesh)
	{
		cout << sp << "MESH" << endl;

		const char* buffer;
		SIZE_T sz = 0;

		int vcount = 0;
		int icount = 0;
		int numFaces = 0;
		unsigned int bufferPos = 0;

		data->Lock(&sz, reinterpret_cast<const void**>(&buffer));
		
		memcpy(&vcount, buffer + bufferPos, sizeof(int));
		bufferPos += sizeof(int);

		
		positions.clear();
		usedVertices.clear();
		duplicated.clear();
		Vector3 current;
		for (int i = 0; i < vcount; i++)
		{
			memcpy(&current, buffer + bufferPos, sizeof(Vector3));
			bufferPos += sizeof(Vector3);

			positions[current].push_back(i);
		}

		ArrayPtr<GeometryVertex> garr(new GeometryVertex[positions.size()], positions.size());
		int k = 0;
		for (map<Vector3, vector<int> >::iterator i = positions.begin(); i != positions.end(); i++)
		{
			AssignVector(garr[k].position, i->first, swapYZ);
			usedVertices.push_back(i->second.front());
			for (vector<int>::iterator j = i->second.begin(); j != i->second.end(); j++)
			{
				duplicated[*j] = k;
			}
			k++;
		}

		memcpy(&numFaces, buffer + bufferPos, sizeof(int));
		bufferPos += sizeof(int);

		int faceSize;
		unsigned int mark = bufferPos;
		for (int i = 0; i < numFaces; i++)
		{
			memcpy(&faceSize, buffer + bufferPos, sizeof(int));
			bufferPos += sizeof(int)*(faceSize+1);

			icount += (faceSize != 4) ? faceSize : 6; // quad is split into two triangles
		}	
		bufferPos = mark;

		ArrayPtr<unsigned int> iarr(new unsigned int[icount], icount);
		int c = 0;
		int ind[4];
		for (int i = 0; i < numFaces; i++)
		{
			memcpy(&faceSize, buffer + bufferPos, sizeof(int));
			bufferPos += sizeof(int);
			if (faceSize != 4)
			{
				for (int j = 0; j < faceSize; j++)
				{
					memcpy(&iarr[c], buffer + bufferPos, sizeof(int));
					bufferPos += sizeof(int);
					iarr[c] = duplicated[iarr[c]];
					c++;
				}
			}
			else
			{
				memcpy(&ind[0], buffer + bufferPos, sizeof(int)*4);
				bufferPos += sizeof(int)*4;

				iarr[c++] = duplicated[ind[0]];
				iarr[c++] = duplicated[ind[3]];
				iarr[c++] = duplicated[ind[2]];

				iarr[c++] = duplicated[ind[0]];
				iarr[c++] = duplicated[ind[2]];
				iarr[c++] = duplicated[ind[1]];
			}
		}
		data->Unlock();

		Ptr<VertexData> vdata = new VertexData(garr, iarr, ArrayPtr<float>(), TextureDeclaration());
		List< Ptr<Effect> > list;
		Ptr<GeometryData> gdata = new GeometryData(vdata, list, BT_INSTANCE);

		Geometry* g = new Geometry(gdata, 0);
		
		if (context)
		{
			// replace group object with geometry object
			//g->setName(context->getName());
			//g->setLocalTransform(context->getLocalTransform());
			//g->setParent(context->getParent());
			
			g->changeModelBound()->computeFromData(g->getVertexData());
			g->setName(GetName(data));
			g->setParent(((Spatial*)context));

			Group* parent = dynamic_cast<Group*>(context);
			assert(parent);
			parent->getChildren().insertFront(g);

			/*if (context->getParent())
			{
				Group* parent = dynamic_cast<Group*>(context->getParent());
				assert(parent);
				parent->getChildren().remove(context);
				parent->getChildren().insertFront(g);
			}
			else
			{
				sgraph.remove(context);
				sgraph.add(g);
			}
			delete context;*/
		}
		else
		{
			g->setName(GetName(data));
			g->setParent(0);
			sgraph.add(g);
		}
		newContext = g;
	}
	else if (type == TID_D3DRMMeshMaterialList)
	{
		cout << sp << "MATERIAL LIST" << endl;

		int mcount;
		SIZE_T sz;

		const int* buffer;

		data->Lock(&sz, reinterpret_cast<const void**>(&buffer));

		mcount = buffer[0];
		materialIndex = buffer[2];
		currentMaterialIndex = 0;

		data->Unlock();


	}
	else if (type == TID_D3DRMMeshNormals)
	{
		cout << sp << "NORMALS" << endl;
		
		const char* buffer;
		SIZE_T sz = 0;
		int vcount;
		unsigned int bufferPos = 0;

		data->Lock(&sz, reinterpret_cast<const void**>(&buffer));

		memcpy(&vcount, buffer + bufferPos, sizeof(int));
		bufferPos += sizeof(int);

		Geometry* g = dynamic_cast<Geometry*>(context);
		assert(g);

		ArrayPtr<GeometryVertex>& gv = g->getGeometryData()->changeGeometryVertexData();

		const Vector3* normals = reinterpret_cast<const Vector3*>(buffer + bufferPos);
		int j = 0;
		for (vector<int>::iterator i = usedVertices.begin(); i != usedVertices.end(); i++)
		{
			AssignVector(gv[j++].normal, normals[*i], swapYZ);
		}

		data->Unlock();

		newContext = context;
	}	
	else if (type == TID_D3DRMMaterial)
	{
		cout << sp << "MATERIAL" << endl;

		if (currentMaterialIndex == materialIndex)
		{
			
			const float* buffer;
			SIZE_T sz;
			data->Lock(&sz, reinterpret_cast<const void**>(&buffer));
			
			Ptr<MaterialEffect> matEffect(new MaterialEffect);
			matEffect->ambient = Color4::WHITE;
			matEffect->diffuse = Color4(buffer);
			matEffect->power = buffer[4];
			matEffect->specular = Color4(buffer[5], buffer[6], buffer[7], 1.0f);
			matEffect->emissive = Color4(buffer[8], buffer[9], buffer[10], 1.0f);

			data->Unlock();

			((Geometry*)context)->addEffect(matEffect);
		
		}
		currentMaterialIndex++;
	}
	else if (type == TID_D3DRMTextureFilename)
	{
		cout << sp << "TEXTURE_FILENAME" << endl;

		const char* buffer;
		SIZE_T sz;
		data->Lock(&sz, reinterpret_cast<const void**>(&buffer));

		Ptr<Texture> tex = renderer.createTexture(buffer);

		data->Unlock();
		
		Ptr<TextureEffect> texEffect(new TextureEffect);
		texEffect->addLayer(new TextureLayer(tex));
		((Geometry*)context)->addEffect(texEffect);

	}
	else if (type == TID_D3DRMFrameTransformMatrix)
	{
		cout << sp << "TRANSFORM" << endl;

		const float* farr;
		SIZE_T sz = 0;
		data->Lock(&sz, reinterpret_cast<const void**>(&farr));
		Matrix4 matrix( farr[0], farr[4], farr[8],  farr[12],
						farr[1], farr[5], farr[9],  farr[13], 
						farr[2], farr[6], farr[10], farr[14], 
						farr[3], farr[7], farr[11], farr[15] );
		data->Unlock();

		if (swapYZ && matrix != Matrix4::IDENTITY)
		{
			Transformation transform;
			Vector3 translation(matrix[0][3], matrix[1][3], matrix[2][3]);
			Matrix3 rotation(matrix[0][0], matrix[0][1], matrix[0][2],
							 matrix[1][0], matrix[1][1], matrix[1][2],
							 matrix[2][0], matrix[2][1], matrix[2][2]);
			Vector3 scale, axis;
			float angle;
			rotation.decompose(rotation, scale);	
			rotation.getAxisAngle(axis, angle);	
			
			SwapYZ(axis);
			SwapYZ(scale);
			SwapYZ(translation);
			
			rotation.fromAxisAngle(axis, angle);

			if ((scale[0] == scale[1]) && (scale[1] == scale[2]))
			{
				transform.setUniformScale(scale[0]);
			}
			transform.setRotation(rotation);
			transform.setTranslation(translation);
		}
		else
		{
			((Spatial*)context)->setLocalTransform(Transformation(matrix));
		}

		Matrix3 rot = ((Spatial*)context)->getLocalTransform().getRotation();
		Vector3 t = ((Spatial*)context)->getLocalTransform().getTranslation();
		Vector3 s = ((Spatial*)context)->getLocalTransform().getScale();
		cout << rot[0][0] << " " << rot[0][1] << " " << rot[0][2] << "    " << t[0] << "    " << s[0] << endl;
		cout << rot[1][0] << " " << rot[1][1] << " " << rot[1][2] << "    " << t[1] << "    " << s[1] << endl;
		cout << rot[2][0] << " " << rot[2][1] << " " << rot[2][2] << "    " << t[2] << "    " << s[2] << endl;
	}

	ID3DXFileData* child;
	SIZE_T max;
	data->GetChildren(&max);
	for (unsigned int i = 0; i < max; i++)
	{
		data->GetChild(i, &child);
		processData(child, newContext);
		child->Release();
	}
	sp[pos] = ' ';
	pos -= 2;
	sp[pos] = '\0';
}

int main(int argc, const char** argv)
{
	 if (argc != 3)
	 {
		 cerr << "ERROR: exactly two arguments expected." << endl;
		 return 1;
	 }

	const char* filename = argv[1];
	ID3DXFile* xfile;
	ID3DXFileEnumObject* enumObj;
	ID3DXFileData* data;
		
	D3DXFileCreate(&xfile);
	xfile->RegisterTemplates((LPVOID)D3DRM_XTEMPLATES, D3DRM_XTEMPLATE_BYTES);
	xfile->CreateEnumObject((LPVOID)filename, D3DXF_FILELOAD_FROMFILE, &enumObj);

	SIZE_T max;

	sp = new char[100];
	for (int i = 0; i < 100; i++)
	{
		sp[i] = ' ';
	}
	sp[pos] = '\0';
	
	enumObj->GetChildren(&max);
	for (unsigned int i = 0; i < max; i++)
	{
		enumObj->GetChild(i, &data);
		processData(data, 0);
		data->Release();
	}
	enumObj->Release();
	xfile->Release();

	delete sp;

	sgraph.update(0.0f);
	sgraph.save(argv[2]);


	 
	 
	 /*d3d = Direct3DCreate9(D3D_SDK_VERSION);
	 if (d3d)
	 {
		 D3DDISPLAYMODE dispMode;
		 d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &dispMode);
		 D3DPRESENT_PARAMETERS presentParams;
		 ZeroMemory(&presentParams, sizeof(presentParams));
		 presentParams.Windowed = TRUE;
		 presentParams.SwapEffect = D3DSWAPEFFECT_COPY;
		 presentParams.BackBufferWidth = 8;
		 presentParams.BackBufferHeight = 8;
		 presentParams.BackBufferFormat = 
			 ( ( dispMode.Format == D3DFMT_R8G8B8 ) ? D3DFMT_R5G6B5 : dispMode.Format );

		  d3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, GetDesktopWindow(),
							 D3DCREATE_SOFTWARE_VERTEXPROCESSING, &presentParams, &device);
	 }

	 HRESULT hr = D3DXLoadMeshHierarchyFromX(filename, D3DXMESH_MANAGED, device, &alloc, 0, &frameRoot,
		 &animController);
	
	 if (FAILED(hr))
		 cerr << "ERROR: could not read from " << filename << endl;

	 device->Release();
	 d3d->Release();*/
}