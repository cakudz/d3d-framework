#pragma once

#include "../Events/EventProcessor.h"

class mouse : public Event::EventProcessor {
public:
	
	POINT m_location{ 0,0 };

	// when you want to implement sliders
	// so when the user leaves client
	// you still get wm_move
	bool m_capture_external{ false };
	
	// always returns false, just keeps track of mouse position
	bool will_process_event( unsigned int, void* ) override;

	static mouse* get() {
		static mouse* instance{ nullptr };

		if (instance != nullptr)
			return instance;

		instance = new mouse();
		return instance;
	}

	
};