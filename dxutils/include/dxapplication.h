#pragma once

#include "dxinclude.h"
#include "dxbasic.h"
#include "dxdisplay.h"
#include "dxinput.h"
#include "dxmatrix.h"
#include "dxaudio.h"

namespace DX
{
	class Application;
	
	// DirectX Funktionen
	typedef void (*InitFunction) ( Application* app, PDIRECT3D direct3D, DisplayDevice* displayDevice );
	typedef void (*RenderFunction) ( Application* app, DisplayDevice* display, KeyboardDevice* keyboard, MouseDevice* mouse );

	// Ereignisbehandlungsfunktionen
	typedef void (*MouseEvent) (Application* app, int x, int y, int keys);
	typedef void (*MoveEvent) (Application* app, int x, int y);
	typedef void (*ResizeEvent) (Application* app, Flag flags, int width, int height);
	typedef void (*ActivationEvent) (Application* app, bool isActivated, bool minimized, HWND handle);
	typedef void (*PaintEvent) (Application* app, HDC hdc);
	typedef void (*KeyEvent) (Application* app, int key);
	typedef void (*EmptyEvent) (Application* app);

	struct EventHandler
	{
		MouseEvent onClick;
		MouseEvent onRClick;
		MouseEvent onLButtonDown;
		MouseEvent onRButtonDown;
		MouseEvent onMouseMove;

		PaintEvent onPaint;

		KeyEvent onKeyUp;
		KeyEvent onKeyDown;

		EmptyEvent onCreate;
		EmptyEvent onDestroy;

		MoveEvent onMove;

		ResizeEvent onResize;

		ActivationEvent onActivate;

		EventHandler() : onClick(0), onRClick(0), onLButtonDown(0), 
			onRButtonDown(0), onMouseMove(0), onPaint(0), onKeyUp(0), onKeyDown(0),
			onCreate(0), onDestroy(0), onMove(0), onResize(0), onActivate(0) {}
	};

	struct DirectXHandler
	{
		InitFunction onInit;
		RenderFunction onRender;

		DirectXHandler() : onInit(0), onRender(0) {}
	};

	class Application
	{
		private:
			static Application* theApp;		
			static LRESULT CALLBACK stdWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

			int framerate;
			bool staticFramerate;
			void updateFramerate(int newFramerate);

			HWND windowHandle;
			bool windowActive;
			bool gotQuit;
			PDIRECT3D direct3D;
			DisplayDevice* displayDevice;
			KeyboardDevice* keyboard;
			MouseDevice* mouse;
			AudioManager* audioManager;
			PINPUT input;

			EventHandler eventHandler;
			DirectXHandler dxHandler;

			void setMouseAcquire();
			void setWindowActive(bool active) { windowActive = active; }

			void cleanup();
			void error(const wchar_t* msg);
			void render();

			Application();
			Application( HINSTANCE hInstance, int nCmdShow, bool fullScreen, 
				const wchar_t* title, Point resolution );
			~Application();

		public:
			static void create( HINSTANCE hInstance, int nCmdShow, bool fullScreen, 
				const wchar_t* title = L"DXApplication", Point resolution = Point(1024, 768),
				bool staticFramerate = false )
			{ 
				theApp = new Application(hInstance, nCmdShow, fullScreen, title, resolution);
				theApp->framerate = 10;
				theApp->staticFramerate = staticFramerate;
			}
			static void clear() { delete theApp; }
			static Application *const getInstance() { return theApp; }

			int run();
			void setEventHandler(EventHandler handler) { eventHandler = handler; }
			void setDirectXHandler(DirectXHandler handler) { dxHandler = handler; }
			HWND getWindowHandle() { return windowHandle; }
			DisplayDevice* getDisplayDevice() { return displayDevice; }
			KeyboardDevice* getKeyboardDevice() { return keyboard; }
			MouseDevice* getMouseDevice() { return mouse; }
			AudioManager* getAudioManager() { return audioManager; }
			void setStaticFramerate(int value) { if (staticFramerate) framerate = value; }
			int getFramerate() { return framerate; }
			float getFramefactor(int onerate = 60) { return float(onerate)/framerate; }
			void quit();

			void setCamera(Camera* newCamera);
			void setProjection(Projection* newProjection);

			Point getScreenCoordinates(D3DXVECTOR3 position);
			

	};
}