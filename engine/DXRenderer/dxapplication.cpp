/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#include "dxapplication.h"

using namespace DX;

/* ------------------------------------------------------- */
/* class Application:                                      */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
void Application::quit()
{
	m_gotQuit = true;
	PostMessage(s_theApp->m_windowHandle, WM_DESTROY, 0, 0);
}
/* ------------------------------------------------------- */
EventHandler& Application::eventHandler() 
{ 
	return m_eventHandler;
}
/* ------------------------------------------------------- */
HWND Application::getWindowHandle() const 
{
	return m_windowHandle;
}
/* ------------------------------------------------------- */
unsigned int Application::getWidth() const
{
	return m_width;
}
/* ------------------------------------------------------- */
unsigned int Application::getHeight() const
{
	return m_height;
}
/* ------------------------------------------------------- */
HWND Application::getWindowHandle(unsigned int x, unsigned int y, unsigned int width, unsigned int height)
{
	// create a subcomponent into the main window and return a handle to it

	return createWindow("", m_windowHandle, x, y, width, height, WS_CHILD);
}
/* ------------------------------------------------------- */
/*                      PRIVATE                            */
/* ------------------------------------------------------- */
Application* Application::s_theApp;
/* ------------------------------------------------------- */
HWND Application::createWindow(const char* title, HWND parent, unsigned int x, unsigned int y,
							   unsigned int width, unsigned int height, unsigned int style)
{
	HWND windowHandle;	
	windowHandle = CreateWindow("DXWndClass", title, style, x, y, width, height,
		parent, 0, m_hInstance, 0);
	assert(windowHandle);

	ShowWindow(windowHandle, m_nCmdShow);
	UpdateWindow(windowHandle);
	return windowHandle;
}
/* ------------------------------------------------------- */
Application::Application( HINSTANCE hInstance, int nCmdShow, const char* title, unsigned int width, 
						 unsigned int height, bool showCursor ) 
: m_gotQuit(false), m_nCmdShow(nCmdShow), m_hInstance(hInstance), m_width(width), m_height(height)
{

	WNDCLASSEX wcex;
	memset(&wcex, 0, sizeof(WNDCLASSEX));
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = Application::stdWndProc;
	wcex.hInstance = hInstance;
	wcex.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
	wcex.lpszClassName = "DXWndClass";
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	ATOM r = RegisterClassEx(&wcex);
	assert(r != 0);

	m_windowHandle = createWindow(title, 0,  0, 0, width, height);
	ShowCursor( (showCursor) ? TRUE : FALSE );
}
/* ------------------------------------------------------- */
/*                      STATIC                             */
/* ------------------------------------------------------- */
void Application::Create( HINSTANCE hInstance, int nCmdShow, const char* title,
	unsigned int width, unsigned int height, bool showCursor)
{ 
	s_theApp = new Application(hInstance, nCmdShow, title, width, height, showCursor);
}
/* ------------------------------------------------------- */
void Application::Clear() 
{ 
	delete s_theApp;
}
/* ------------------------------------------------------- */
Application *const Application::GetInstance() 
{ 
	return s_theApp;
}			
/* ------------------------------------------------------- */
LRESULT CALLBACK Application::stdWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (s_theApp)
	{
		switch(message)
		{
			case WM_CREATE:
				if ( s_theApp->m_eventHandler.onCreate )
					s_theApp->m_eventHandler.onCreate(s_theApp);
				break;
			case WM_PAINT:
				if ( s_theApp->m_eventHandler.onPaint )
					s_theApp->m_eventHandler.onPaint(s_theApp, (HDC)wParam);
				break;
			case WM_DESTROY:
				if ( s_theApp->m_eventHandler.onDestroy )
					s_theApp->m_eventHandler.onDestroy(s_theApp);
				PostQuitMessage(0);
				break;
			case WM_KEYDOWN:
				if ( s_theApp->m_eventHandler.onKeyDown )
					s_theApp->m_eventHandler.onKeyDown(s_theApp, (int)wParam);
				break;
			case WM_KEYUP:
				if ( s_theApp->m_eventHandler.onKeyUp )
					s_theApp->m_eventHandler.onKeyUp(s_theApp, (int)wParam);
				break;
			case WM_MOUSEMOVE:
				if ( s_theApp->m_eventHandler.onMouseMove )
					s_theApp->m_eventHandler.onMouseMove(s_theApp, LOWORD(lParam), HIWORD(lParam), wParam);
				break;
			case WM_LBUTTONDOWN:
				if ( s_theApp->m_eventHandler.onLButtonDown )
					s_theApp->m_eventHandler.onLButtonDown(s_theApp, LOWORD(lParam), HIWORD(lParam), wParam);
				break;
			case WM_RBUTTONDOWN:
				if ( s_theApp->m_eventHandler.onRButtonDown )
					s_theApp->m_eventHandler.onRButtonDown(s_theApp, LOWORD(lParam), HIWORD(lParam), wParam);
				break;
			case WM_LBUTTONUP:
				if ( s_theApp->m_eventHandler.onClick )
					s_theApp->m_eventHandler.onClick(s_theApp, LOWORD(lParam), HIWORD(lParam), wParam);
				break;
			case WM_RBUTTONUP:
				if ( s_theApp->m_eventHandler.onRClick )
					s_theApp->m_eventHandler.onRClick(s_theApp, LOWORD(lParam), HIWORD(lParam), wParam);
				break;
			case WM_SIZE:
				if ( s_theApp->m_eventHandler.onResize )
					s_theApp->m_eventHandler.onResize(s_theApp, wParam, LOWORD(lParam), HIWORD(lParam));
				break;
			case WM_MOVE:
				if ( s_theApp->m_eventHandler.onMove )
					s_theApp->m_eventHandler.onMove(s_theApp, LOWORD(lParam), HIWORD(lParam));
				break;
			case WM_ACTIVATE:
				s_theApp->m_windowActive = !(LOWORD(wParam) == WA_INACTIVE);
				if ( s_theApp->m_eventHandler.onActivate )
					s_theApp->m_eventHandler.onActivate(s_theApp, s_theApp->m_windowActive, (HIWORD(wParam) > 0) ? true : false, reinterpret_cast<HWND>(lParam));				
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
		return 0;
	}
	else
		return DefWindowProc(hWnd, message, wParam, lParam);
}



