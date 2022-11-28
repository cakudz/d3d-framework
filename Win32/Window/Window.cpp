#include "Window.h"
#include "../../wndproc/wndproc.h"

namespace win32 {

	// registers, creates, and shows the window
	bool Window::register_create_show_window( HINSTANCE hInst ) {

		WNDCLASSEXW wnd_class{};
		ZeroMemory( &wnd_class, sizeof( wnd_class ) );

		wnd_class.cbSize = sizeof( wnd_class );
		wnd_class.style = CS_OWNDC;
		wnd_class.lpfnWndProc = win32::wndproc;
		wnd_class.hInstance = hInst;
		wnd_class.lpszClassName = this->m_window_clazz_name;

		window_size_t window_size{ 900,500 };
		// size of the window when first opened

		// registering window class
		auto registered_clazz = RegisterClassEx( &wnd_class );

		// failed to register window class
		if (static_cast<int>(registered_clazz) == 0)
			return false;

		// let our class know what styles we are going to use in advance
		// https://learn.microsoft.com/en-us/windows/win32/winmsg/window-styles
		this->m_window_style = 0;

		// client drawing region
		m_window_client_size = window_size;

		// add non client area to size
		this->adjust_for_non_client_region( &window_size );

		auto window = CreateWindowExW( NULL, this->m_window_clazz_name, L"D3D Framework", 
			this->m_window_style, CW_USEDEFAULT, CW_USEDEFAULT, 
			window_size.width, window_size.height, NULL, NULL, hInst, nullptr );

		// failed to create window ?
		if (reinterpret_cast<int>(window) == 0)
		{
			// de-register class
			auto success = UnregisterClassW( this->m_window_clazz_name, hInst );
			return false;

		}

		this->m_window_handle = window;

		// must do this for the window to be visible
		ShowWindow( window, SW_SHOW );

		return true;

	}

	void Window::de_register_window_class() {
		
		// gets the instance of the current module / dll
		auto instance = GetModuleHandle( nullptr );
		UnregisterClass( this->m_window_clazz_name, instance );

	}

	// calculate non-client + client window size
	void Window::adjust_for_non_client_region( window_size_t* window_size ) {

		RECT a{};
		ZeroMemory( &a, sizeof( a ) );

		a.right = window_size->width;
		a.bottom = window_size->height;

		AdjustWindowRect( &a, this->m_window_style, FALSE );

		window_size->width = a.right;
		window_size->height = a.bottom;

	}

	LRESULT Window::wndproc( HWND window, UINT msg, WPARAM wp, LPARAM lp ) {

		// handle our messages
		// when handling text input
		// remember to use WM_CHAR -- produces raw input with wparam
		// when processing text input

		switch (msg) {
		case WM_CLOSE:
			PostQuitMessage( 0 );
			break;
		
		// keyboard input
		case WM_CHAR:
			break;
		case WM_KEYDOWN:
			break;
		case WM_KEYUP:
			break;

		// mouse input
		case WM_LBUTTONDOWN:
			break;
		case WM_RBUTTONDOWN:
			break;
		case WM_LBUTTONUP:
			break;
		case WM_RBUTTONUP:
			break;
		case WM_MOUSEMOVE:
			break;
		case WM_MOUSEWHEEL:
			break;
		}

		return DefWindowProc( window, msg, wp, lp );

	}

	// cool singleton ;-;
	Window* Window::get_instance() {

		static Window* instance{ nullptr };

		if (instance != nullptr)
			return instance;

		instance = new Window();

		return instance;

	}

}
