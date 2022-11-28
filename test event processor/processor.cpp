#include "processor.h"
#include <string>

bool TestProcessor::will_process_event( unsigned int code, void* data ) {

	return code == Event::MouseInputs::wheel;

}

void TestProcessor::process_event( unsigned int code, void* data ) {

	int movement = *reinterpret_cast<int*>(data);
	
	output_debug( std::to_string( movement ).c_str() );

}