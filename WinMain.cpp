#include <Windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {

	WNDCLASSEXW wnd_class{ 0 };
	
	wnd_class.cbSize = sizeof(wnd_class);
	wnd_class.style = CS_OWNDC;
	wnd_class.lpfnWndProc = DefWindowProc;

	// registering window class
	RegisterClassEx()
	return 0;

}