#include "Win32/WinInclude.h"
#include "wndproc/wndproc.h"
#include "Win32/Window/Window.h"
#include "Framework/Events/EventDispatcher.h"
#include "Framework/Keyboard/Keyboard.h"
#include "Framework/Mouse/Mouse.h"

int APIENTRY WinMain( HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow )
{

	if (!win32::Window::get_instance()->register_create_show_window( hInst )) {

		output_debug( "failed to register / create the base window" );
		
		return -1;
		

	}


	// test event processor
	// ############################
	// delete when finished with event system
	// Event::EventDispatcher::get_instance()->register_processor( new TestProcessor() );
	Event::EventDispatcher::get_instance()->register_processor( new keyboard(), Event::high_priority );
	Event::EventDispatcher::get_instance()->register_processor( new mouse(), Event::high_priority );

	MSG msg{};
	BOOL state_result{};

	while ((state_result = GetMessage( &msg, NULL, NULL, NULL )) != 0) {

		TranslateMessage( &msg );
		DispatchMessage( &msg );

	}

	// we dont want any further windows messages processed
	Event::EventDispatcher::get_instance()->deregister_all_processors();

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