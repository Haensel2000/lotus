/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

/* ------------------------------------------------------- */
/* class DXApplication:                                    */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
template <class R> int Application::run(R& renderer)
{
	if (m_gotQuit)
		return 0;

	MSG msg;
	ZeroMemory( &msg, sizeof(msg) );
    while( msg.message != WM_QUIT )
    {
		renderer.render();
		
		if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
        {	
			TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
    }

	return (int)msg.wParam;
}