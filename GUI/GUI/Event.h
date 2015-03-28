#pragma once
#include <string>

#include "GUIButton.h"
#include "GUISlider.h"

namespace gui{
	enum EventType{
		Default, Button, Slider
	};

	class Event{
	public:
		Event();
		Event(GUIButton *_button, std::string button_name);
		Event(GUISlider *_slider, std::string slider_name);
		~Event();

		EventType type;
		std::string text, name;
		float value;
	};

}