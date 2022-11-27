#include "wndproc.h"

namespace win32 {

	LRESULT __stdcall wndproc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam ) {
		
		// handle our messages
		switch (msg) {
		case WM_CLOSE:
			PostQuitMessage( 0 );
			break;

		}
		return DefWindowProc( hwnd, msg, wParam, lParam );

	}

}