#pragma once

#include "../Events/EventProcessor.h"

class keyboard : public Event::EventProcessor {
public:

	// vk @ 0x0 will never have a state
	DWORD m_keystates[VK_OEM_CLEAR + 0x1]{ 0 };

	// passive processor
	bool will_process_event( unsigned int, void* ) override;

	// changed convention to get for simplicity
	// will be referenced alot
	static keyboard* get() {
		static keyboard* instance{ nullptr };
		
		if (instance != nullptr)
			return instance;

		instance = new keyboard();
		return instance;
	}
};