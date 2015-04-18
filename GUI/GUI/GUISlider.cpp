#include "GUISlider.h"

GUISlider::GUISlider(){

}
GUISlider::GUISlider(int _width, int _height, int _x, int _y, std::string _text, sf::Color _m_color, sf::Color _i_color, sf::Color _s_color, sf::Font *_font){
	slider_value = 100.0f;
	main_box = sf::RectangleShape(sf::Vector2f(_width, _height));
	main_box.setFillColor(_m_color);
	main_box.setPosition(sf::Vector2f(_x, _y));

	inside_box = sf::RectangleShape(sf::Vector2f(_width - _height * 0.2f, _height * 0.8f));
	inside_box.setFillColor(_i_color);
	inside_box.setPosition(sf::Vector2f(_x + _height * 0.1f, _y + _height * 0.1f));

	slider_box = sf::RectangleShape(sf::Vector2f(_height * 0.8f, _height * 0.8f));
	slider_box.setFillColor(_s_color);
	slider_box.setPosition(sf::Vector2f(_x + _height * 0.1f + (inside_box.getLocalBounds().width - slider_box.getLocalBounds().width), _y + _height * 0.1f));

	text = _text;
	slider_text.setString(text);
	slider_text.setColor(sf::Color(0, 0, 0, 255));
	slider_text.setFont(*_font);
	slider_text.setCharacterSize(inside_box.getLocalBounds().height / 1.3f);
	slider_text.setPosition(sf::Vector2f(int(inside_box.getPosition().x - slider_text.getLocalBounds().width / 2 + inside_box.getLocalBounds().width / 2), inside_box.getPosition().y));

	active = true;
	centred = false;

	x = _x;
	y = _y;
		
	updated = false;
}
GUISlider::~GUISlider(){

}

void GUISlider::Render(sf::RenderWindow *_window){
	_window->draw(main_box);
	_window->draw(inside_box);
	_window->draw(slider_text);
	_window->draw(slider_box);
}
void GUISlider::Update(sf::RenderWindow *_window, float _delta){
	GUIObject::Update(_window, _delta);

	sf::Vector2i _pos = sf::Mouse::getPosition(*_window);
	if (_pos.x > main_box.getPosition().x && _pos.x < main_box.getPosition().x + main_box.getSize().x
		&& _pos.y > main_box.getPosition().y && _pos.y < main_box.getPosition().y + main_box.getSize().y){
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
			if (slider_box.getPosition().x >= _pos.x - 20.0f){
				slider_box.setPosition(slider_box.getPosition().x - (abs(slider_box.getPosition().x + slider_box.getLocalBounds().width - _pos.x) * 0.33), slider_box.getPosition().y);
				if (slider_box.getPosition().x < x + main_box.getSize().y * 0.1f){
					slider_box.setPosition(x + main_box.getSize().y * 0.1f, slider_box.getPosition().y);
				}
				CalculateSliderValue();
			}
			if (slider_box.getPosition().x + slider_box.getLocalBounds().width / 2.0f <= _pos.x){
				slider_box.setPosition(slider_box.getPosition().x + (abs(slider_box.getPosition().x - _pos.x) * 0.33), slider_box.getPosition().y);
				if (slider_box.getPosition().x > x + main_box.getSize().y * 0.1f + inside_box.getSize().x - slider_box.getSize().x){
					slider_box.setPosition(x + main_box.getSize().y * 0.1f + inside_box.getSize().x - slider_box.getSize().x, slider_box.getPosition().y);
				}
				CalculateSliderValue();
			}
		}
	}
}

void GUISlider::SetPosition(sf::Vector2f _pos){
	if (centred){
		x = _pos.x - main_box.getLocalBounds().width / 2;
		y = _pos.y;
		main_box.setPosition(x, y);
	}
	else{
		main_box.setPosition(_pos);
		x = _pos.x;
		y = _pos.y;
	}
	inside_box.setPosition(sf::Vector2f(x + main_box.getLocalBounds().height * 0.1f, y + main_box.getLocalBounds().height * 0.1f));
	slider_box.setPosition(sf::Vector2f(x + main_box.getLocalBounds().height * 0.1f + ((inside_box.getLocalBounds().width - slider_box.getLocalBounds().width) * slider_value/100.0f), y + main_box.getLocalBounds().height * 0.1f));
	slider_text.setPosition(sf::Vector2f(int(inside_box.getPosition().x - slider_text.getLocalBounds().width / 2 + inside_box.getLocalBounds().width / 2), inside_box.getPosition().y));
}

void GUISlider::SetText(std::string _text){
	text = _text;
}
std::string GUISlider::GetText(){
	return text;
}

bool GUISlider::Contains(sf::Vector2i _pos){
	if (_pos.x > x && _pos.x < x + main_box.getSize().x
		&& _pos.y > y && _pos.y < y + main_box.getSize().y){
		return true;
	}
	return false;
}

float GUISlider::GetValue(){
	return slider_value;
}
bool GUISlider::Updated(){
	if (updated){
		updated = false;
		return true;
	}
	return false;
}

void GUISlider::CalculateSliderValue(){
	float t = inside_box.getLocalBounds().width - slider_box.getLocalBounds().width;
	float r = slider_box.getPosition().x - inside_box.getPosition().x;
	slider_value = r / t * 100.0f;
	updated = true;
		
	//slider_text.setString(std::to_string(int(slider_value)));
}