#include "Event.h"

namespace gui{

	Event::Event(){
		type = Default;
		text = "";
		name = "";
	}
	Event::Event(GUIButton *_button, std::string button_name){
		type = Button;
		text = _button->GetText();
		name = button_name;
	}


	Event::~Event(){

	}

}