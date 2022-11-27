#include "wndproc.h"

namespace win32 {

	LRESULT __stdcall wndproc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam ) {
		
		// handle our messages
		// when handling text input
		// remember to use WM_CHAR -- produces raw input with wparam
		// when processing text input
		

		switch (msg) {
		case WM_CLOSE:
			PostQuitMessage( 0 );
			break;

		}
		return DefWindowProc( hwnd, msg, wParam, lParam );

	}

}