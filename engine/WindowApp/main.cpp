#include <lotus.h>
#include <dxr.h>
#include <iostream>
#include <string>

using namespace Lotus;
using namespace DX;
using namespace std;

class Rotator : public Controller
{
private:
	//float x;
	Matrix3 rotation;
	Vector3 rotationAxis;
	float angle;

	float val;
public:
	Rotator(Vector3 axis) : rotationAxis(axis), angle(0), val(1.0f) {}

	virtual void update(double time)
	{
		angle += time;
		rotation.fromAxisAngle(rotationAxis, angle);
		((Spatial*)m_object)->changeLocalTransform().setRotation(rotation);
	}
};


int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Application::Create(hInstance, nCmdShow);
	Application* app = Application::GetInstance();
	
	DXRenderer renderer;
	renderer.attachTo(app);

	float nl = 1.0f/Math<float>::Sqrt(3.0f);
	
	/*ArrayPtr<GeometryVertex> garr(new GeometryVertex[8], 8);
	garr[0].color0 = D3DCOLOR_XRGB(255, 255, 255);
	garr[0].position = Vector3(-0.25f, -0.25f, -0.25f);
	garr[0].normal = Vector3(-nl, -nl, -nl);
	garr[1].color0 = D3DCOLOR_XRGB(255, 255, 255);
	garr[1].position = Vector3(-0.25f, 0.25f, -0.25f);
	garr[1].normal = Vector3(-nl, nl, -nl);
	garr[2].color0 = D3DCOLOR_XRGB(255, 255, 255);
	garr[2].position = Vector3(0.25f, 0.25f, -0.25f);
	garr[2].normal = Vector3(nl, nl, -nl);
	garr[3].color0 = D3DCOLOR_XRGB(255, 255, 255);
	garr[3].position = Vector3(0.25f, -0.25f, -0.25f);
	garr[3].normal = Vector3(nl, -nl, -nl);
	garr[4].color0 = D3DCOLOR_XRGB(255, 255, 255);
	garr[4].position = Vector3(-0.25f, -0.25f, 0.25f);
	garr[4].normal = Vector3(-nl, -nl, nl);
	garr[5].color0 = D3DCOLOR_XRGB(255, 255, 255);
	garr[5].position = Vector3(-0.25f, 0.25f, 0.25f);
	garr[5].normal = Vector3(-nl, nl, nl);
	garr[6].color0 = D3DCOLOR_XRGB(255, 255, 255);
	garr[6].position = Vector3(0.25f, 0.25f, 0.25f);
	garr[6].normal = Vector3(nl, nl, nl);
	garr[7].color0 = D3DCOLOR_XRGB(255, 255, 255);
	garr[7].position = Vector3(0.25f, -0.25f, 0.25f);
	garr[7].normal = Vector3(nl, -nl, nl);

	ArrayPtr<float> tarr(new float[16], 16);
	tarr[0] = 0.0f;
	tarr[1] = 0.0f;
	tarr[2] = 0.0f;
	tarr[3] = 1.0f;
	tarr[4] = 1.0f;
	tarr[5] = 1.0f;
	tarr[6] = 1.0f;
	tarr[7] = 0.0f;
	tarr[8] = 0.0f;
	tarr[9] = 0.0f;
	tarr[10] = 0.0f;
	tarr[11] = 1.0f;
	tarr[12] = 1.0f;
	tarr[13] = 1.0f;
	tarr[14] = 1.0f;
	tarr[15] = 0.0f;

	ArrayPtr<unsigned int> iarr(new unsigned int[36], 36);
	iarr[0] = 1;
	iarr[1] = 2;
	iarr[2] = 0;
	iarr[3] = 0;
	iarr[4] = 2;
	iarr[5] = 3;

	iarr[6] = 3;
	iarr[7] = 2;
	iarr[8] = 6;
	iarr[9] = 3;
	iarr[10] = 6;
	iarr[11] = 7; 

	iarr[12] = 1;
	iarr[13] = 5;
	iarr[14] = 6;
	iarr[15] = 1;
	iarr[16] = 6;
	iarr[17] = 2; 

	iarr[18] = 0;
	iarr[19] = 1;
	iarr[20] = 5;
	iarr[21] = 0;
	iarr[22] = 5;
	iarr[23] = 4; 

	iarr[24] = 0;
	iarr[25] = 4;
	iarr[26] = 7;
	iarr[27] = 0;
	iarr[28] = 7;
	iarr[29] = 3; 

	iarr[30] = 4;
	iarr[31] = 5;
	iarr[32] = 6;
	iarr[33] = 4;
	iarr[34] = 6;
	iarr[35] = 7; 


	int* dims = new int[1];
	dims[0] = 2;

	Ptr<TextureEffect> teff(new TextureEffect(TA_DIFFUSE));
	teff->addLayer(new TextureLayer(renderer.createTexture("schach.bmp")));
	Ptr<DirectionalLight> leff(new DirectionalLight);
	leff->ambient = Color4.WHITE;
	leff->diffuse = Color4.WHITE;
	leff->specular = Color4.WHITE;
	leff->direction = Vector3(-nl, -nl, -nl);

	Ptr<VertexData> vdata = new VertexData(garr, iarr, tarr, TextureDeclaration(1, dims));
	
	List< Ptr<Effect> > list;
	Ptr<GeometryData> gdata = new GeometryData(vdata, list, BT_INSTANCE);
	gdata->addEffect(teff);
	gdata->addEffect(leff);

	Geometry* g = new Geometry(gdata, &renderer);
	g->setName("Triangle");
	Ptr<Controller> mover(new Rotator(Vector3(0,1,0)));
	g->addController(mover);
	g->changeLocalTransform().setTranslation(Vector3(0, 0, 1));*/

	

	
	Ptr<DirectionalLight> leff(new DirectionalLight);
	leff->ambient = Color4.WHITE;
	leff->diffuse = Color4(1.0, 1.0, 1.0, 1.0);
	leff->specular = Color4.WHITE;
	leff->direction = Vector3(nl/2.0f, nl, nl);

	Ptr<MaterialEffect> meff(new MaterialEffect);
	meff->ambient = Color4(0.2, 0.05, 0.05, 1.0);
	meff->diffuse = meff->specular = Color4(1.0, 0.0, 0.0, 1.0);

	Ptr<RenderPass> stdPass(new RenderPass(&renderer));
	stdPass->addEffect(leff);
	stdPass->addEffect(meff);

	//renderer.getCamera()->setView(Vector3(0, 10, -10), Vector3(0, 0, 1), Vector3(0, 1, 0));

	SceneGraph sgraph(&renderer, 1000);
	sgraph.load("testmodel.sg");

	Group* root = (Group*)sgraph.get("RootFrame");
	root->addRenderPass(stdPass);

	Group* entry = root->getGroup("Cube");
	entry->changeLocalTransform().setUniformScale(0.25);
	entry->changeLocalTransform().setTranslation(Vector3(0, 15, -3));
	Ptr<Controller> mover(new Rotator(Vector3(0,0,1)));
	entry->addController(mover);

	app->run(renderer);
	Application::Clear();
}