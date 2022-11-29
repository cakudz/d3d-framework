#include "Keyboard.h"

bool keyboard::will_process_event( unsigned int code, void* data ) {

	if (code != Event::KeyboardInputs::keydown && code != Event::KeyboardInputs::keyup)
		return false;

	auto vkkey = *reinterpret_cast<unsigned int*>(data);

	this->m_keystates[vkkey] = code == Event::KeyboardInputs::keydown;

	return false;
}
