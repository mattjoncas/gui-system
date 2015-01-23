#include "GUIObject.h"

namespace gui{

	GUIObject::GUIObject(){

	}

	GUIObject::~GUIObject(){

	}

	void GUIObject::Render(sf::RenderWindow *_window){
		//printf("object render\n");
	}
	void GUIObject::Update(sf::RenderWindow *_window, float _delta){
		//printf("object update\n");
	}

	void GUIObject::SetCentred(bool _centred){
		centred = _centred;
		SetPosition(sf::Vector2f(x, y));
	}
	void GUIObject::SetPosition(sf::Vector2f _pos){
		//printf("object set position\n");
	}
	void GUIObject::SetText(std::string _text){
		//printf("set text\n");
	}
	bool GUIObject::Contains(sf::Vector2i _pos){
		return false;
	}

	bool GUIObject::Active(){
		return active;
	}
	void GUIObject::SetActive(bool _isActive){
		active = _isActive;
	}

}