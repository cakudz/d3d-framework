#include <Windows.h>
#include "wndproc/wndproc.h"

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR lpCmdLine, INT nCmdShow)
{

	WNDCLASSEXW wnd_class{};
	ZeroMemory(&wnd_class, sizeof(wnd_class));

	const auto clazz_name = L"d3d_ui_clazz";
	
	wnd_class.cbSize = sizeof(wnd_class);
	wnd_class.style = CS_OWNDC;
	wnd_class.lpfnWndProc = win32::wndproc;
	wnd_class.hInstance = hInstance;
	wnd_class.lpszClassName = clazz_name;
	

	// registering window class
	RegisterClassEx(&wnd_class);

	auto window = CreateWindowExW(NULL, clazz_name, L"D3D Framework", WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX, 20, 20, 500, 500, NULL, NULL, hInstance, nullptr);

	// must do this for the window to be visible
	ShowWindow(window, SW_SHOW);

	MSG msg{};
	BOOL state_result{};

	while ((state_result = GetMessage( &msg, NULL, NULL, NULL )) != 0) {

		TranslateMessage( &msg );
		DispatchMessage( &msg );

	}

	// will only reach here
	// if quits window
	if (state_result == -1)
		return -1;

	return msg.wParam;

}