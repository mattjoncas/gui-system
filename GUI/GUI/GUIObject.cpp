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

		if (lerping){
			sf::Vector2f pos;
			lerp_time += _delta;
			if (lerp_time >= lerp_end_time){
				pos = lerp_end;
				lerping = false;
			}
			else{
				float c_time = lerp_time / lerp_end_time;
				pos = lerp_start + c_time * (lerp_end - lerp_start);
			}
			SetPosition(pos);
		}
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
	std::string GUIObject::GetText(){
		//printf("get text\n");
		return "";
	}
	bool GUIObject::Contains(sf::Vector2i _pos){
		return false;
	}

	void GUIObject::Lerp(sf::Vector2f target_position, float _lerp_time){
		lerping = true;
		lerp_start = sf::Vector2f(x, y);
		lerp_end = target_position;
		lerp_time = 0.0f;
		lerp_end_time = _lerp_time;
	}

	bool GUIObject::Active(){
		return active;
	}
	void GUIObject::SetActive(bool _isActive){
		active = _isActive;
	}

}