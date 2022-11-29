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

		// do not dispatch the same event if the priority level changed
		std::list<EventProcessor*> dont_process_twice{};

		this->m_cancel_enumeration = false;

		for (unsigned int layer = 0; layer < ProcessorPriority::priority_count; layer++) {	
			for (unsigned int i = 0; i < this->m_event_processors[layer].size(); i++) {

				// have to do this because of list
				auto _processors = this->m_event_processors[layer].begin();
				std::advance( _processors, i );

				auto processor = *_processors;
				
				// lambda that checks if the processor is in the do not process list
				if ([processor, &dont_process_twice]( void )->bool {

					for (auto v : dont_process_twice) {
						if (processor == v)
							return true;
					}
					return false;

					}())
					continue;

				// have to do this here
				auto will_process = processor->will_process_event( input_type, buffer );

				if (this->m_cancel_enumeration) {
					i--;

					// if priority has been changed lower or equal dont process again
					if (processor->get_processor_priority() >= layer)
						dont_process_twice.push_back( processor );

					this->m_cancel_enumeration = false;

					continue;
				}

				if (will_process)
				{
					processor->process_event( input_type, buffer );

					// and again here
					if (this->m_cancel_enumeration) {
						i--;

						if (processor->get_processor_priority() >= layer)
							dont_process_twice.push_back( processor );

						this->m_cancel_enumeration = false;

						continue;
					}

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

		// tell the event dispatch to restart enumeration if dispatching an event
		this->m_cancel_enumeration = true;

	}

}