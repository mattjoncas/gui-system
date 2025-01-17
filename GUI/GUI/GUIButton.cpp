#include "GUIButton.h"

GUIButton::GUIButton(){

}
GUIButton::GUIButton(int _width, int _height, int _x, int _y, std::string _text, sf::Color _color, sf::Color _h_color, sf::Color _c_color, sf::Font *_font){
	shape = sf::RectangleShape(sf::Vector2f(_width, _height));

	shape.setFillColor(_color);
	color = _color;
	h_color = _h_color;
	c_color = _c_color;

	shape.setPosition(sf::Vector2f(_x, _y));
	x = _x;
	y = _y;

	text = _text;
	button_text.setString(text);
	button_text.setColor(sf::Color(0, 0, 0, 255));
	button_text.setFont(*_font);
	button_text.setCharacterSize(_height / 1.3);

	button_text.setPosition(int(x - button_text.getLocalBounds().width / 2 + _width / 2), int(y));

	c_state = false; p_state = false; clicked = false;
	active = true;
	centred = false;

	texture_button = false;
}
GUIButton::GUIButton(int _width, int _height, int _x, int _y, std::string _text, sf::Font *_font, std::string _texture_path){
	button_texture = &TextureManager::GetInstance().LoadTexture(_texture_path);
	//button_texture.loadFromFile(_texture_path);
	button_texture->setSmooth(false);

	shape.setSize(sf::Vector2f(_width, _height));
	shape.setTexture(button_texture);
	shape.setPosition(sf::Vector2f(_x, _y));
	x = _x;
	y = _y;

	text = _text;
	button_text.setString(text);
	button_text.setColor(sf::Color(0, 0, 0, 255));
	button_text.setFont(*_font);
	button_text.setCharacterSize(_height / 1.3);

	button_text.setPosition(int(x - button_text.getLocalBounds().width / 2 + _width / 2), int(y));

	c_state = false; p_state = false; clicked = false;
	active = true;
	centred = false;
	texture_button = true;
	size = sf::Vector2f(_width, _height);
}

GUIButton::~GUIButton(){

}

void GUIButton::Render(sf::RenderWindow *_window){
	_window->draw(shape);
	_window->draw(button_text);
}
void GUIButton::Update(sf::RenderWindow *_window, float _delta){
	GUIObject::Update(_window, _delta);

	sf::Vector2i _pos = sf::Mouse::getPosition(*_window);
	if (!texture_button){
		if (_pos.x > x && _pos.x < x + shape.getSize().x
			&& _pos.y > y && _pos.y < y + shape.getSize().y){
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
				shape.setFillColor(c_color);
				c_state = true;
			}
			else{
				c_state = false;
				shape.setFillColor(h_color);
				if (!c_state && p_state){
					clicked = true;
				}
			}
		}
		else{
			shape.setFillColor(color);
			c_state = false;
		}
		p_state = c_state;
	}
	else{
		if (_pos.x > x && _pos.x < x + shape.getSize().x
			&& _pos.y > y && _pos.y < y + shape.getSize().y){
			shape.setSize(sf::Vector2f(size.x + 10, size.y + 10));
			shape.setPosition(sf::Vector2f(x - 5, y - 5));
			button_text.setCharacterSize(shape.getLocalBounds().height / 1.3);
			button_text.setPosition(int(shape.getPosition().x - button_text.getLocalBounds().width / 2 + shape.getLocalBounds().width / 2), int(shape.getPosition().y));
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
				c_state = true;
				shape.setFillColor(sf::Color(200, 200, 200, 50));
				button_text.setColor(sf::Color(0, 0, 0, 50));
			}
			else{
				c_state = false;
				shape.setFillColor(sf::Color::White);
				button_text.setColor(sf::Color(0, 0, 0, 255));
				if (!c_state && p_state){
					clicked = true;
				}
			}
		}
		else{
			shape.setSize(size);
			shape.setPosition(sf::Vector2f(x, y));
			shape.setFillColor(sf::Color::White);
			button_text.setColor(sf::Color(0, 0, 0, 255));
			button_text.setCharacterSize(shape.getLocalBounds().height / 1.3);
			button_text.setPosition(int(shape.getPosition().x - button_text.getLocalBounds().width / 2 + shape.getLocalBounds().width / 2), int(shape.getPosition().y));
			c_state = false;
		}
		p_state = c_state;
	}
}

void GUIButton::SetPosition(sf::Vector2f _pos){
	if (centred){
		x = _pos.x - shape.getLocalBounds().width / 2;
		y = _pos.y;
		shape.setPosition(x, y);
	}
	else{
		shape.setPosition(_pos);
		x = _pos.x;
		y = _pos.y;
	}
	button_text.setPosition(int(x - button_text.getLocalBounds().width / 2 + shape.getLocalBounds().width / 2), int(y));
}
void GUIButton::SetText(std::string _text){
	float old_offset = 0.0f;
	if (centred){
		old_offset += shape.getLocalBounds().width / 2;
	}
	text = _text;

	button_text.setString(text);

	SetPosition(sf::Vector2f(x + old_offset, y));
}
std::string GUIButton::GetText(){
	return text;
}
bool GUIButton::Contains(sf::Vector2i _pos){
	if (_pos.x > x && _pos.x < x + shape.getSize().x
		&& _pos.y > y && _pos.y < y + shape.getSize().y){
		return true;
	}
	return false;
}

bool GUIButton::IsClicked(){
	if (clicked){
		clicked = false;
		return true;
	}
	return false;
}