#include "Mouse.h"
#include <string>

bool mouse::will_process_event( unsigned int code, void* buffer ) {

	if (code != Event::MouseInputs::move)
		return false;

	this->m_location = *reinterpret_cast<POINT*>(buffer);

	return false;

}
