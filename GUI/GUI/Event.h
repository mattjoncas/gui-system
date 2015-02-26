#pragma once
#include <string>

#include "GUIButton.h"

namespace gui{
	enum EventType{
		Default, Button
	};

	class Event{
	public:
		Event();
		Event(GUIButton *_button, std::string button_name);
		~Event();

		EventType type;
		std::string text, name;
	};

}