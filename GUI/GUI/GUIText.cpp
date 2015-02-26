#include "GUIText.h"

namespace gui{

	GUIText::GUIText(){

	}
	GUIText::GUIText(int _x, int _y, std::string _text, sf::Color _color, sf::Font *_font, int _font_size){
		color = _color;
		x = _x;
		y = _y;

		text = _text;
		text_object.setString(text);
		text_object.setColor(color);
		text_object.setFont(*_font);
		text_object.setCharacterSize(_font_size);

		text_object.setPosition(x, y);

		active = true;
		centred = false;
	}

	GUIText::~GUIText(){

	}

	void GUIText::Render(sf::RenderWindow *_window){
		_window->draw(text_object);
	}
	void GUIText::Update(sf::RenderWindow *_window, float _delta){

	}

	void GUIText::SetPosition(sf::Vector2f _pos){
		if (centred){
			x = _pos.x - text_object.getLocalBounds().width / 2;
			y = _pos.y;
		}
		else{
			x = _pos.x;
			y = _pos.y;
		}
		text_object.setPosition(x, y);
	}
	void GUIText::SetText(std::string _text){
		float old_offset = 0.0f;
		if (centred){
			old_offset += text_object.getLocalBounds().width / 2;
		}
		text = _text;

		text_object.setString(text);

		SetPosition(sf::Vector2f(x + old_offset, y));
	}
	std::string GUIText::GetText(){
		return text;
	}
	bool GUIText::Contains(sf::Vector2i _pos){
		return false;
	}

}