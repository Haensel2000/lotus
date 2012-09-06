/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#include "conv.h"

char* duplicateCharString(const char* c_str)
{
    if (!c_str)
		return NULL;

	size_t len=strlen(c_str) + 1;
	char *newString = new char[len];
	memcpy(newString, c_str, len*sizeof(char));

	return newString;
}

/* ------------------------------------------------------- */
/* class MeshHierarchy:                                    */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
HRESULT MeshHierarchy::CreateFrame( const char* name, LPD3DXFRAME* newFrame )
{
	D3DXFRAME* nframe = new D3DXFRAME;
	ZeroMemory(nframe, sizeof(D3DXFRAME));
	nframe->Name = duplicateCharString(name);
	D3DXMatrixIdentity(&nframe->TransformationMatrix);
	nframe->pMeshContainer = 0;
    nframe->pFrameSibling = 0;
	nframe->pFrameFirstChild = 0;

	*newFrame = nframe;

	return S_OK;
}
/* ------------------------------------------------------- */
HRESULT  MeshHierarchy::CreateMeshContainer(const char* name, CONST D3DXMESHDATA* meshData, 
                        CONST D3DXMATERIAL* materials, CONST D3DXEFFECTINSTANCE* effectInstances,
                        DWORD numMaterials, CONST DWORD* adjacency, LPD3DXSKININFO skinInfo, 
                        LPD3DXMESHCONTAINER* newMeshContainer )
{
	D3DXMESHCONTAINER* meshContainer = new D3DXMESHCONTAINER;
	ZeroMemory(meshContainer, sizeof(D3DXMESHCONTAINER));

	meshContainer->Name = duplicateCharString(name);
	
	if (meshData->Type != D3DXMESHTYPE_MESH) // only support for D3DXMESHTYPE_MESH
	{
		DestroyMeshContainer(meshContainer);
		return E_FAIL;
	}
	meshContainer->MeshData.Type = meshData->Type;

	DWORD faces = meshData->pMesh->GetNumFaces();
	meshContainer->pAdjacency = new DWORD[faces*3];
	memcpy(meshContainer->pAdjacency, adjacency, sizeof(DWORD)*faces*3);

	LPDIRECT3DDEVICE9 device = NULL;
	meshData->pMesh->GetDevice(&device);

	D3DVERTEXELEMENT9 declaration[MAX_FVF_DECL_SIZE];
	if (FAILED(meshData->pMesh->GetDeclaration(declaration)))
		return E_FAIL;
	
	meshData->pMesh->CloneMesh(D3DXMESH_MANAGED, declaration, device, 
		&meshContainer->MeshData.pMesh);

	meshContainer->NumMaterials = max(numMaterials, 1);
	meshContainer->pMaterials = new D3DXMATERIAL[meshContainer->NumMaterials];
	if (numMaterials > 0)
	{
		memcpy(meshContainer->pMaterials, materials, sizeof(D3DXMATERIAL)*meshContainer->NumMaterials);
	}
	else // generate default material
	{
		ZeroMemory(&meshContainer->pMaterials[0], sizeof( D3DXMATERIAL ) );
		meshContainer->pMaterials[0].MatD3D.Diffuse.r = 0.5f;
        meshContainer->pMaterials[0].MatD3D.Diffuse.g = 0.5f;
        meshContainer->pMaterials[0].MatD3D.Diffuse.b = 0.5f;
        meshContainer->pMaterials[0].MatD3D.Specular = meshContainer->pMaterials[0].MatD3D.Diffuse;
	}

	// TODO: copy skinInfo

	SAFE_RELEASE(device);

	// TODO: handle effect instances

	*newMeshContainer = meshContainer;

	return S_OK;
}
/* ------------------------------------------------------- */
HRESULT MeshHierarchy::DestroyFrame( LPD3DXFRAME frameToFree )
{
	SAFE_DELETE_ARRAY( frameToFree->Name );
    SAFE_DELETE( frameToFree );

    return S_OK; 
}
/* ------------------------------------------------------- */
HRESULT MeshHierarchy::DestroyMeshContainer( LPD3DXMESHCONTAINER meshContainerToFree )
{
	// name
	SAFE_DELETE_ARRAY(meshContainerToFree->Name)

	// material array
	SAFE_DELETE_ARRAY(meshContainerToFree->pMaterials)

	// adjacency data
	SAFE_DELETE_ARRAY(meshContainerToFree->pAdjacency) 
	
	// release the main mesh
	SAFE_RELEASE(meshContainerToFree->MeshData.pMesh)
	
	// release skin information
	SAFE_RELEASE(meshContainerToFree->pSkinInfo)
	
	// finally delete the mesh container itself
	SAFE_DELETE(meshContainerToFree);

	return S_OK;
}
/* ------------------------------------------------------- */