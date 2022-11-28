#include "EventDispatcher.h"
#include "EventProcessor.h"
#include <windowsx.h>

namespace Event {

	bool EventDispatcher::dispatch_event( unsigned int msg, WPARAM wp, LPARAM lp ) {

		// here we are going to process keyboard in / out
		// and mouse movements
		
		void* buffer{ nullptr };
		unsigned int input_type{ 0 };

		unsigned int keycode{ 0 };
		int wheel_movement{ 0 };
		POINT pt{};

		switch (msg) {
		case WM_KEYDOWN:
		case WM_KEYUP:
		case WM_CHAR:

			keycode = (unsigned int) (wp);
			buffer = &keycode;
			input_type = WM_KEYUP == msg ? KeyboardInputs::keyup : (msg == WM_CHAR ? KeyboardInputs::keychar : KeyboardInputs::keydown);
			break;

		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:

			input_type = MouseInputs::lbutton;
			keycode = msg == WM_LBUTTONDOWN;
			buffer = &keycode;
			break;

		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:

			input_type = MouseInputs::rbutton;
			keycode = msg == WM_RBUTTONDOWN;
			buffer = &keycode;
			break;

		case WM_MOUSEWHEEL:

			input_type = MouseInputs::wheel;
			wheel_movement = GET_WHEEL_DELTA_WPARAM( wp ) / WHEEL_DELTA;
			buffer = &wheel_movement;
			break;

		case WM_MOUSEMOVE:

			input_type = MouseInputs::move;
			pt.x = GET_X_LPARAM( lp );
			pt.y = GET_Y_LPARAM( lp );

			buffer = &pt;
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
	
	// when we dont want to process any more events just remove the processors
	void EventDispatcher::deregister_all_processors() {
		for (unsigned int i = 0; i < ProcessorPriority::priority_count; i++)
			this->m_event_processors[i].clear();

	}

	void EventDispatcher::update_processor_priority( EventProcessor* processor, ProcessorPriority priority ) {

		// remove the processor from the current layer
		this->m_event_processors[processor->get_processor_priority()].remove( processor );

		// add to new layer
		this->m_event_processors[priority].push_back( processor );

	}

}