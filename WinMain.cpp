#include "Win32/WinInclude.h"
#include "wndproc/wndproc.h"
#include "Win32/Window/Window.h"

int APIENTRY WinMain( HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow )
{

	if (!win32::Window::get_instance()->register_create_show_window( hInst )) {

		output_debug( "failed to register / create the base window" );
		
		return -1;
		

	}

	MSG msg{};
	BOOL state_result{};

	while ((state_result = GetMessage( &msg, NULL, NULL, NULL )) != 0) {

		TranslateMessage( &msg );
		DispatchMessage( &msg );

	}

	// will only reach here
	// if closes / quits window

	win32::Window::get_instance()->de_register_window_class();

	// has error occured?
	if (state_result == -1)
		return -1;

	return msg.wParam;

}