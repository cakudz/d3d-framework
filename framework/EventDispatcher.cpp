#include "EventDispatcher.h"
#include "EventProcessor.h"

namespace Event {

	bool EventDispatcher::dispatch_event( unsigned int msg, WPARAM wp, LPARAM lp ) {

		// here we are going to process keyboard in / out
		// and mouse movements
		
		void* buffer{ nullptr };
		unsigned int input_type{ 0 };

		unsigned int keycode{ 0 };

		switch (msg) {
		case WM_KEYDOWN:
		case WM_KEYUP:
		case WM_CHAR:

			keycode = (unsigned int) (wp);
			buffer = &keycode;
			input_type = WM_KEYUP == msg ? KeyboardInputs::keyup : (msg == WM_CHAR ? KeyboardInputs::keychar : KeyboardInputs::keydown);
			break;

		default:
			return false;
		}

		for (unsigned int layer = 0; layer < ProcessorPriority::priority_count; layer++) {
			for (auto processor : this->m_event_processors[layer]) {
				if (processor->will_process_event( input_type, buffer ))
				{
					processor->process_event( input_type, buffer );
					return true;
				}
			}
		}

		return false;
	}

	void EventDispatcher::register_processor( EventProcessor* processor, ProcessorPriority priority ) {

		// will set priority when registered
		processor->override_set_processor_priority( priority );

		// blind faith
		// will assume processor is not already on the stack

		this->m_event_processors[priority].push_back( processor );

	}

	void EventDispatcher::deregister_processor( EventProcessor* processor ) {

		// remove processor
		this->m_event_processors[processor->get_processor_priority()].remove( processor );

	}

	void EventDispatcher::update_processor_priority( EventProcessor* processor, ProcessorPriority priority ) {

		// remove the processor from the current layer
		this->m_event_processors[processor->get_processor_priority()].remove( processor );

		// add to new layer
		this->m_event_processors[priority].push_back( processor );

	}

}