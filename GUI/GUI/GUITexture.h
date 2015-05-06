#pragma once
#include "GUIObject.h"

class GUITexture : public GUIObject{
public:
	GUITexture();
	GUITexture(int _width, int _height, int _x, int _y, std::string _texture_path);
	~GUITexture();

	void Render(sf::RenderWindow *_window) override;
	//void Update(sf::RenderWindow *_window, float _delta) override;

	void SetPosition(sf::Vector2f _pos) override;
private:
	sf::Vector2f size;
	sf::RectangleShape shape;
	
	sf::Texture texture;
};
