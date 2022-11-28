#pragma once

#include "../framework/EventProcessor.h"

class TestProcessor : public Event::EventProcessor {
public:
	bool will_process_event( unsigned int, void* ) override;
	void process_event( unsigned int, void* ) override;
};