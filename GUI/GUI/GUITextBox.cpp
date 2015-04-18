#include "GUITextBox.h"

GUITextBox::GUITextBox(){

}
GUITextBox::GUITextBox(int _width, int _height, int _x, int _y, std::string _text, sf::Color _color, sf::Font *_font){
	shape = sf::RectangleShape(sf::Vector2f(_width, _height));

	shape.setFillColor(_color);
	color = _color;

	shape.setPosition(sf::Vector2f(_x, _y));
	x = _x;
	y = _y;

	text = _text;
	box_text.setString(text);
	box_text.setColor(sf::Color(0, 0, 0, 255));
	box_text.setFont(*_font);
	box_text.setCharacterSize(_height / 1.3);
	box_text.setPosition(int(x + box_text.getCharacterSize() / 10), int(y));

	TextOverflow();

	selected_text.setString("");
	selected_text.setColor(sf::Color(0, 0, 0, 255));
	selected_text.setFont(*_font);
	selected_text.setCharacterSize(_height / 1.3);
	selected_text.setPosition(int(x + box_text.getLocalBounds().width + box_text.getCharacterSize() / 10), int(y));

	selected = false;
	active = true;
	centred = false;

	hidden_text = false;
}

GUITextBox::~GUITextBox(){

}

void GUITextBox::Render(sf::RenderWindow *_window){
	_window->draw(shape);
	_window->draw(box_text);
	_window->draw(selected_text);
}
void GUITextBox::Update(sf::RenderWindow *_window, float _delta){
	GUIObject::Update(_window, _delta);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
		sf::Vector2i _pos = sf::Mouse::getPosition(*_window);
		if (_pos.x > x && _pos.x < x + shape.getSize().x
			&& _pos.y > y && _pos.y < y + shape.getSize().y){
			selected = true;
			current_time = TICK_TIME;
			selected_text.setString("|");
		}
		else{
			selected = false;
			selected_text.setString("");
		}
	}

	if (selected){
		current_time -= _delta;
		if (current_time < 0){
			if (selected_text.getString() == ""){
				selected_text.setString("|");
			}
			else{
				selected_text.setString("");
			}
			current_time = TICK_TIME;
		}
	}
	else{
		selected_text.setString("");
	}
}

void GUITextBox::SetPosition(sf::Vector2f _pos){
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
	box_text.setPosition(int(x + box_text.getCharacterSize() / 10), int(y));
	selected_text.setPosition(int(x + box_text.getLocalBounds().width + box_text.getCharacterSize() / 10), int(y));
}
void GUITextBox::SetText(std::string _text){
	float old_offset = 0.0f;
	if (centred){
		old_offset += shape.getLocalBounds().width / 2;
	}
	text = _text;

	if (hidden_text){
		box_text.setString(HideText(text));
	}
	else{
		box_text.setString(text);
	}
	TextOverflow();
	SetPosition(sf::Vector2f(x + old_offset, y));
}
bool GUITextBox::Contains(sf::Vector2i _pos){
	if (_pos.x > x && _pos.x < x + shape.getSize().x
		&& _pos.y > y && _pos.y < y + shape.getSize().y){
		return true;
	}
	return false;
}

bool GUITextBox::Selected(){
	return selected;
}
void GUITextBox::AddChar(char _new_text){
	if (_new_text != NULL){
		text += _new_text;
	}
	else{
		if (text.size() > 0){
			text.pop_back();
		}
	}
	if (hidden_text){
		box_text.setString(HideText(text));
	}
	else{
		box_text.setString(text);
	}
	TextOverflow();
	selected_text.setPosition(x + box_text.getLocalBounds().width + box_text.getCharacterSize() / 10, y);
}
void GUITextBox::Select(){
	selected = true;
}
void GUITextBox::Unselect(){
	selected = false;
}

void GUITextBox::SetHidden(bool _isHidden){
	hidden_text = _isHidden;

	if (hidden_text){
		box_text.setString(HideText(text));
	}
	else{
		box_text.setString(text);
	}
}
std::string GUITextBox::HideText(std::string _string){
	std::string hidden_text;
	for (int i = 0; i < text.size(); i++){
		hidden_text += "*";
	}
	return hidden_text;
}
void GUITextBox::TextOverflow(){
	while (box_text.getLocalBounds().width + box_text.getCharacterSize() / 10 > shape.getLocalBounds().width){
		std::string n_string = box_text.getString();
		n_string.pop_back();
		box_text.setString(n_string);
	}
}

std::string GUITextBox::GetText(){
	return text;
}