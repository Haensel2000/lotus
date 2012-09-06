#include <d3d9.h>
#include <d3dx9.h>

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#endif    
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#endif    
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }
#endif

char* duplicateCharString(const char* c_str);

class MeshHierarchy : public ID3DXAllocateHierarchy
{
	// callback to create a D3DXFRAME extended object and initialize it
    STDMETHOD(CreateFrame) ( const char* name, LPD3DXFRAME* newFrame );

    // callback to create a D3DXMESHCONTAINER extended object and initialize it
    STDMETHOD(CreateMeshContainer) (const char* name, CONST D3DXMESHDATA* meshData, 
                            CONST D3DXMATERIAL* materials, CONST D3DXEFFECTINSTANCE* effectInstances,
                            DWORD numMaterials, CONST DWORD* adjacency, LPD3DXSKININFO skinInfo, 
                            LPD3DXMESHCONTAINER* newMeshContainer );

    // callback to release a D3DXFRAME extended object
    STDMETHOD(DestroyFrame) ( LPD3DXFRAME frameToFree );

    // callback to release a D3DXMESHCONTAINER extended object
    STDMETHOD(DestroyMeshContainer) ( LPD3DXMESHCONTAINER meshContainerToFree );
};