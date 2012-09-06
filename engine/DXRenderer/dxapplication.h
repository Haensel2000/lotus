/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#ifndef _HDR_DXAPPLICATION_H
#define _HDR_DXAPPLICATION_H 

#include "dxdecl.h"
#include <system\lsystem.h>

namespace DX
{
	class Application;

	// Ereignisbehandlungsfunktionen
	typedef void (*MouseEvent) (Application* app, int x, int y, int keys);
	typedef void (*MoveEvent) (Application* app, int x, int y);
	typedef void (*ResizeEvent) (Application* app, unsigned int flags, int width, int height);
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

	class Application
	{
		private:
			static Application* s_theApp;		
			static LRESULT CALLBACK stdWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

			HWND m_windowHandle;
			bool m_windowActive;
			bool m_gotQuit;
			int m_nCmdShow;
			HINSTANCE m_hInstance;
			EventHandler m_eventHandler;

			unsigned int m_width, m_height;

			void setWindowActive(bool active) { m_windowActive = active; }
			HWND createWindow(const char* title, HWND parent, unsigned int x, unsigned int y,
				unsigned int width, unsigned int height, unsigned int style = WS_OVERLAPPEDWINDOW);
			Application();
			Application( HINSTANCE hInstance, int nCmdShow, const char* title,
				unsigned int width, unsigned int height, bool showCursor );

		public:
			static void Create( HINSTANCE hInstance, int nCmdShow, const char* title = "DXApplication",
				unsigned int width = 1024, unsigned int height = 768, bool showCursor = true);
			static void Clear();
			static Application *const GetInstance();

			template <class R> int run(R& renderer);

			EventHandler& eventHandler();

			unsigned int getWidth() const;
			unsigned int getHeight() const;
			HWND getWindowHandle() const;
			HWND getWindowHandle(unsigned int x, unsigned int y, unsigned int width, unsigned int height);

			void quit();
	};

#include "dxapplication.inl"
}

#endif