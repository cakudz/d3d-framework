#include "Win32/WinInclude.h"
#include "wndproc/wndproc.h"
#include "Win32/Window/Window.h"
#include "framework/EventDispatcher.h"
#include "test event processor/processor.h"

int APIENTRY WinMain( HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow )
{

	if (!win32::Window::get_instance()->register_create_show_window( hInst )) {

		output_debug( "failed to register / create the base window" );
		
		return -1;
		

	}


	// test event processor
	// ############################
	// delete when finished with event system
	Event::EventDispatcher::get_instance()->register_processor( new TestProcessor() );

	MSG msg{};
	BOOL state_result{};

	while ((state_result = GetMessage( &msg, NULL, NULL, NULL )) != 0) {

		TranslateMessage( &msg );
		DispatchMessage( &msg );

	}

	// will only reach here
	// if closes / quits window

	win32::Window::get_instance()->de_register_window_class();

	// destroy the window handle
	DestroyWindow( win32::Window::get_instance()->m_window_handle );

	// has error occured?
	if (state_result == -1)
		return -1;

	return msg.wParam;

}