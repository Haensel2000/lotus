#include <windows.h>



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch( message )
    {
        case WM_DESTROY:
            PostQuitMessage( 0 );
            return 0;
    }
    return DefWindowProc( hWnd, message, wParam, lParam );
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// Information zum Fenstertyp:	
	WNDCLASSEX wcex;
	memset(&wcex, 0, sizeof(WNDCLASSEX));
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = (WNDPROC)WndProc;
	wcex.hInstance = hInstance;
	wcex.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
	wcex.lpszClassName = "SimpleWindowClass";
	if (!RegisterClassEx(&wcex))
		return 0;

	// Information zum konkreten Fenster:
	HWND hWnd;
	hWnd = CreateWindow("SimpleWindowClass", "Jawohlen!", WS_OVERLAPPEDWINDOW, 100, 100, 300, 300, 0, 0, hInstance, 0);
	if (!hWnd)
		return 0;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);




	// Event-Handling:
	MSG msg;
	ZeroMemory( &msg, sizeof(msg) );
    while( msg.message!=WM_QUIT )
    {
		if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
        {
			TranslateMessage( &msg );
            DispatchMessage( &msg );
        };
    }
	return msg.wParam;
}