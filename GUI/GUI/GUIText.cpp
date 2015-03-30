#include "GUIText.h"

namespace gui{

	GUIText::GUIText(){

	}
	GUIText::GUIText(int _x, int _y, std::string _text, sf::Color _color, sf::Font *_font, int _font_size, float _fade){
		color = _color;
		x = _x;
		y = _y;

		text = _text;
		text_object.setString(text);
		text_object.setColor(color);
		text_object.setFont(*_font);
		text_object.setCharacterSize(_font_size);

		text_object.setPosition(int(x), int(y));

		active = true;
		centred = false;

		fade_time = _fade;
		if (fade_time != 0.0f){
			sf::Color f_color = color;
			f_color.a = 0.0f;
			text_object.setColor(f_color);
		}
		fade_timer = 0.0f;
	}

	GUIText::~GUIText(){

	}

	void GUIText::Render(sf::RenderWindow *_window){
		_window->draw(text_object);
	}
	void GUIText::Update(sf::RenderWindow *_window, float _delta){
		GUIObject::Update(_window, _delta);

		if (fade_timer < fade_time){
			fade_timer += _delta;

			sf::Color f_color = color;
			if (fade_timer > fade_time){ fade_timer = fade_time; }
			f_color.a = fade_timer / fade_time * 255;
			text_object.setColor(f_color);
		}
		else{
			text_object.setColor(color);
		}
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
		text_object.setPosition(int(x), int(y));
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
	void GUIText::Lerp(sf::Vector2f target_position, float _lerp_time){
		lerping = true;
		if (!centred){
			lerp_start = sf::Vector2f(x, y);
		}
		else{
			lerp_start = sf::Vector2f(x + text_object.getLocalBounds().width / 2, y);
		}
		lerp_end = target_position;
		lerp_time = 0.0f;
		lerp_end_time = _lerp_time;
	}
}