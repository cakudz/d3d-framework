#pragma once

namespace Event {

	// this is for processor input handling 
	// priority / who gets to handle the event first
	enum ProcessorPriority : unsigned int {
		high_priority = 0,
		medium_priority = 1,
		low_priority = 2,

		priority_count = 3
	};

}