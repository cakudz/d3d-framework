#include "Mouse.h"
#include <string>
#include "../../Win32/Window/Window.h"

bool mouse::will_process_event( unsigned int code, void* buffer ) {

	if (code != Event::MouseInputs::move)
		return false;

	this->m_location = *reinterpret_cast<POINT*>(buffer);

	auto window = win32::Window::get_instance();

	// capture window for non client behaviour
	if (this->m_location.x >= 0 && this->m_location.x < window->m_window_client_size.width
		&& this->m_location.y >= 0 && this->m_location.y < window->m_window_client_size.height)
		SetCapture( window->m_window_handle );
	else if (!this->m_capture_external)
		ReleaseCapture();

	return false;

}
