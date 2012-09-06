#include "..\include\dxapplication.h"
#include "math.h"
#include <timer.h>

using namespace DX;

/* class Application */

/* private */

Application* Application::theApp;

void Application::updateFramerate(int newFramerate)
{
	/*float oldweight = log(float(newFramerate)/framerate);
	oldweight *= oldweight;
	framerate = (framerate*oldweight + newFramerate) / (oldweight+1);*/
	framerate = newFramerate;
}

void Application::setMouseAcquire()
{
	if ( mouse )
	{
		
	}
}

void Application::cleanup()
{
    if (displayDevice)
		delete displayDevice;
	if( direct3D)
        direct3D->Release();

	if (input) 
    { 
        if (keyboard) 
        { 
            delete keyboard;
        } 
		if (mouse) 
        { 
			delete mouse;
        } 
        input->Release();
        input = NULL; 
    }

	if (audioManager)
		delete audioManager;
}

void Application::error(const wchar_t* msg)
{
	cleanup();
	throw new Exception(msg);
}

void Application::render()
{
	keyboard->update();
	mouse->update();
	displayDevice->clear(D3DCOLOR_XRGB(0, 0, 0));
	displayDevice->beginScene();
	if ( dxHandler.onRender )
			dxHandler.onRender(this, displayDevice, keyboard, mouse);
	displayDevice->endScene();
	if (displayDevice->getCamera())
		displayDevice->setViewMatrixFromCamera();
	displayDevice->present();
}

Application::Application( HINSTANCE hInstance, int nCmdShow, bool fullScreen, 
						 const wchar_t* title, Point resolution ) : gotQuit(false)
{
	WNDCLASSEX wcex;
	memset(&wcex, 0, sizeof(WNDCLASSEX));
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = Application::stdWndProc;
	wcex.hInstance = hInstance;
	wcex.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
	wcex.lpszClassName = L"DXStdWndClass";
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	if (!RegisterClassEx(&wcex))
		error(L"DXApplication::DXApplication: RegisterClassEx() failed.");
		
	windowHandle = CreateWindow(L"DXStdWndClass", title, WS_OVERLAPPEDWINDOW, 0, 0, resolution.x, resolution.y,
		0, 0, hInstance, 0);
	if (!windowHandle)
		error(L"DXApplication::DXApplication: CreateWindow() failed.");
	
	direct3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (!direct3D)
		error(L"DXApplication::DXApplication: Direct3DCreate9() failed.");
		
	D3DDISPLAYMODE displayMode;
	ZeroMemory( &displayMode, sizeof(displayMode) );
	int maxAdapterMode = direct3D->GetAdapterModeCount( D3DADAPTER_DEFAULT, D3DFMT_X8R8G8B8 );
	int i = 0;
	while ( i++ < maxAdapterMode && ( displayMode.Width != resolution.x || displayMode.Height != resolution.y ) )
	{
		if ( FAILED ( direct3D->EnumAdapterModes(D3DADAPTER_DEFAULT, D3DFMT_X8R8G8B8, i, &displayMode) ) )
			error(L"DXApplication::DXApplication: EnumAdapterModes() failed.");
	}
	if ( i == maxAdapterMode ) // es wurde keine Übereinstimmung gefunden
	{
		if ( FAILED ( direct3D->EnumAdapterModes(D3DADAPTER_DEFAULT, D3DFMT_X8R8G8B8, maxAdapterMode - 1, &displayMode) ) )
			error(L"DXApplication::DXApplication: EnumAdapterModes() failed.");
	}

	D3DDISPLAYMODE d3ddm;
	if (!fullScreen)
	{	
        direct3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm); 
	}
	
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory( &d3dpp, sizeof(d3dpp) );
	d3dpp.BackBufferWidth =  (fullScreen) ? displayMode.Width : 0;
	d3dpp.BackBufferHeight = (fullScreen) ? displayMode.Height : 0;
	d3dpp.BackBufferFormat = (fullScreen) ? displayMode.Format : d3ddm.Format;
	d3dpp.hDeviceWindow = 0;
	d3dpp.Windowed = (fullScreen) ? FALSE : TRUE;
	d3dpp.FullScreen_RefreshRateInHz = (fullScreen) ? displayMode.RefreshRate : 0;
	d3dpp.SwapEffect = (fullScreen) ? D3DSWAPEFFECT_FLIP : D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	LPDIRECT3DDEVICE9 dev;
	if( FAILED( direct3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, windowHandle, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &dev )))
		error(L"DXApplication::DXApplication display: CreateDevice() failed.");

	displayDevice = new DisplayDevice(dev, displayMode);

	/*stdRenderSettings = renderSettings;

	if (stdRenderSettings.zBuffer)
		displayDevice->SetRenderState( D3DRS_ZENABLE, D3DZB_TRUE );
	if (stdRenderSettings.culling)
		displayDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );
	if (stdRenderSettings.lightning)
		displayDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
	displayDevice->SetRenderState( D3DRS_AMBIENT, stdRenderSettings.ambientColor ); */
	
	if ( dxHandler.onInit )
		dxHandler.onInit(this, direct3D, displayDevice);

	ShowWindow(windowHandle, nCmdShow);
	ShowCursor( FALSE );
	UpdateWindow(windowHandle);

	// init input:
	DirectInput8Create( hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&input, NULL );
	keyboard = new KeyboardDevice(input, windowHandle);
	mouse = new MouseDevice(input, windowHandle);
	audioManager = new AudioManager(windowHandle, displayDevice);
	
}

Application::~Application()
{
	cleanup();
}


/* public */

int Application::run()
{
	if (gotQuit)
		return 0;

	MSG msg;
	ZeroMemory( &msg, sizeof(msg) );
	Timer frameTime;
    while( msg.message != WM_QUIT )
    {
		frameTime.begin();
		render();
		
		if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
        {	
			TranslateMessage( &msg );
            DispatchMessage( &msg );
        }

		DWORD delta = frameTime.timeMS();
		if (staticFramerate)
		{
			while (frameTime.timeMS() <= 1000/framerate);
		}
		else
		{
			if (delta > 0)
				updateFramerate(1000 / delta);
		}
    }

	return msg.wParam;
}

void Application::quit()
{
	gotQuit = true;
	PostMessage(theApp->windowHandle, WM_DESTROY, 0, 0);
}

/* static */

LRESULT CALLBACK Application::stdWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (theApp)
	{
		switch(message)
		{
			case WM_CREATE:
				if ( theApp->eventHandler.onCreate )
					theApp->eventHandler.onCreate(theApp);
				break;
			case WM_PAINT:
				if ( theApp->eventHandler.onPaint )
					theApp->eventHandler.onPaint(theApp, (HDC)wParam);
				break;
			case WM_DESTROY:
				if ( theApp->eventHandler.onDestroy )
					theApp->eventHandler.onDestroy(theApp);
				PostQuitMessage(0);
				break;
			case WM_KEYDOWN:
				if ( theApp->eventHandler.onKeyDown )
					theApp->eventHandler.onKeyDown(theApp, (int)wParam);
				break;
			case WM_KEYUP:
				if ( theApp->eventHandler.onKeyUp )
					theApp->eventHandler.onKeyUp(theApp, (int)wParam);
				break;
			case WM_MOUSEMOVE:
				if ( theApp->eventHandler.onMouseMove )
					theApp->eventHandler.onMouseMove(theApp, LOWORD(lParam), HIWORD(lParam), wParam);
				break;
			case WM_LBUTTONDOWN:
				if ( theApp->eventHandler.onLButtonDown )
					theApp->eventHandler.onLButtonDown(theApp, LOWORD(lParam), HIWORD(lParam), wParam);
				break;
			case WM_RBUTTONDOWN:
				if ( theApp->eventHandler.onRButtonDown )
					theApp->eventHandler.onRButtonDown(theApp, LOWORD(lParam), HIWORD(lParam), wParam);
				break;
			case WM_LBUTTONUP:
				if ( theApp->eventHandler.onClick )
					theApp->eventHandler.onClick(theApp, LOWORD(lParam), HIWORD(lParam), wParam);
				break;
			case WM_RBUTTONUP:
				if ( theApp->eventHandler.onRClick )
					theApp->eventHandler.onRClick(theApp, LOWORD(lParam), HIWORD(lParam), wParam);
				break;
			case WM_SIZE:
				if ( theApp->eventHandler.onResize )
					theApp->eventHandler.onResize(theApp, wParam, LOWORD(lParam), HIWORD(lParam));
				break;
			case WM_MOVE:
				if ( theApp->eventHandler.onMove )
					theApp->eventHandler.onMove(theApp, LOWORD(lParam), HIWORD(lParam));
				break;
			case WM_ACTIVATE:
				theApp->windowActive = !(LOWORD(wParam) == WA_INACTIVE);
				theApp->setMouseAcquire();
				if ( theApp->eventHandler.onActivate )
					theApp->eventHandler.onActivate(theApp, theApp->windowActive, (HIWORD(wParam) > 0) ? true : false, reinterpret_cast<HWND>(lParam));				
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
		return 0;
	}
	else
		return DefWindowProc(hWnd, message, wParam, lParam);
}

