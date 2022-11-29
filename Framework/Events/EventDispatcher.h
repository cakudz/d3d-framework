#pragma once

#include "../../Win32/WinInclude.h"
#include "EventInfo.h"
#include <list>

namespace Event {

	class EventProcessor;

	// dispatches events and registers event processors
	class EventDispatcher {
	public:

		// stored in priority order 
		std::list<EventProcessor*> m_event_processors[ProcessorPriority::priority_count]{};

		// event lists, arranged in priority
		bool dispatch_event( unsigned int, WPARAM, LPARAM );

		// register to the processors list
		void register_processor( EventProcessor*, ProcessorPriority = ProcessorPriority::low_priority );

		// get rid of the processor?
		void deregister_processor( EventProcessor* );
		void deregister_all_processors();
		
		// switch processor priority from processor class, call this function
		void update_processor_priority( EventProcessor*, ProcessorPriority );

		static EventDispatcher* get_instance( void ) {
			static EventDispatcher* instance{ nullptr };

			if (instance != nullptr)
				return instance;

			instance = new EventDispatcher();

			return instance;
		}

	};
}