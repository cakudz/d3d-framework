#pragma once

#include "../Win32/WinInclude.h"
#include "EventInfo.h"

namespace Event {

	// event ids
	enum KeyboardInputs : unsigned int {
		keydown = 0,
		keyup = 1,
		keychar = 2
	};

	enum MouseInputs : unsigned int {
		move = 3,
		wheel = 4,
		button = 5
	};

	// classes will inherit this when they want to process input
	// EVENT PROCESSORS MUST BE PROGRAM LONG
	class EventProcessor {
	private:

		ProcessorPriority m_priority{ ProcessorPriority::priority_count };

	public:

		// returns whether the processor will use the current event to itself
		virtual bool will_process_event( unsigned int, void* ) { return false; }

		// actual event processing
		virtual void process_event( unsigned int, void* ) {}

		void set_processor_priority( ProcessorPriority );
		ProcessorPriority get_processor_priority( );

		void override_set_processor_priority( ProcessorPriority );

	};

}