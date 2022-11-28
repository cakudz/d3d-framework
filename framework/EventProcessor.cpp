#include "EventProcessor.h"
#include "EventDispatcher.h"

namespace Event {

	void EventProcessor::set_processor_priority( ProcessorPriority priority ) {

		EventDispatcher::get_instance()->update_processor_priority( this, priority );

		this->m_priority = priority;
	}

	ProcessorPriority EventProcessor::get_processor_priority() {
		return this->m_priority;
	}

	void EventProcessor::override_set_processor_priority( ProcessorPriority priority ) {

		this->m_priority = priority;

	}

}