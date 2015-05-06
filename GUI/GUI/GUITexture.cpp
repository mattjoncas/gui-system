#include "GUITexture.h"


GUITexture::GUITexture(){

}
GUITexture::GUITexture(int _width, int _height, int _x, int _y, std::string _texture_path){
	size = sf::Vector2f(float(_width), float(_height));

	texture.loadFromFile(_texture_path);
	texture.setSmooth(true);

	x = _x;
	y = _y;
	shape.setPosition(sf::Vector2f(float(_x), float(_y)));
	shape.setSize(size);
	shape.setTexture(&texture);
}

GUITexture::~GUITexture(){

}

void GUITexture::Render(sf::RenderWindow *_window){
	_window->draw(shape);
}
/*
void GUITexture::Update(sf::RenderWindow *_window, float _delta){
	GUIObject::Update(_window, _delta);
}*/

void GUITexture::SetPosition(sf::Vector2f _pos){
	if (centred){
		x = _pos.x - shape.getLocalBounds().width / 2;
		y = _pos.y - shape.getLocalBounds().height / 2;
		shape.setPosition(x, y);
	}
	else{
		shape.setPosition(_pos);
		x = _pos.x;
		y = _pos.y;
	}
}
