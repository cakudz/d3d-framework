#pragma once

#include "../WinInclude.h"

namespace win32 {

	class Window
	{
	private:

		struct window_size_t {
			int width, height;
		};

		int m_window_style{ 0 };

	public:

		// called to register window class, create, and show the window
		bool register_create_show_window( HINSTANCE );

		// called when window is closed
		void de_register_window_class();

		// calculate non-client + client window size
		void adjust_for_non_client_region( window_size_t* );

		LRESULT wndproc( HWND, UINT, WPARAM, LPARAM );

		// non zero is a valid handle
		HWND m_window_handle{ 0 };

		// size of client area in window
		window_size_t m_window_client_size{ 0 };

		// for unregistering the window class
		const wchar_t* m_window_clazz_name = L"d3d_ui_clazz";

		// static instance getter
		static Window* get_instance();

	};
}