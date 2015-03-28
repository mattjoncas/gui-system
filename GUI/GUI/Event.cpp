#include "Event.h"

namespace gui{

	Event::Event(){
		type = Default;
		text = "";
		name = "";
		value = 0;
	}
	Event::Event(GUIButton *_button, std::string button_name){
		type = Button;
		text = _button->GetText();
		name = button_name;
	}
	Event::Event(GUISlider *_slider, std::string slider_name){
		type = Slider;
		text = _slider->GetText();
		name = slider_name;
		value = _slider->GetValue();
	}


	Event::~Event(){

	}

}