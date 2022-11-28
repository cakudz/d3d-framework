#include "processor.h"
#include <string>

bool TestProcessor::will_process_event( unsigned int code, void* data ) {
	return code == Event::KeyboardInputs::keydown;
}

void TestProcessor::process_event( unsigned int code, void* data ) {

	char keycode = static_cast<char>(*reinterpret_cast<unsigned int*>(data));
	
	output_debug( std::to_string( keycode ).c_str() );
}