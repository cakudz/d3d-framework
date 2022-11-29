#include "wndproc.h"
#include "../Win32/Window/Window.h"
#include "../Framework/Events/EventDispatcher.h"

namespace win32 {

	// wndproc callback stub
	LRESULT __stdcall wndproc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam ) {
	
		if (Event::EventDispatcher::get_instance()->dispatch_event( msg, wParam, lParam ))
			return 0;

		return Window::get_instance()->wndproc( hwnd, msg, wParam, lParam );

	}

}