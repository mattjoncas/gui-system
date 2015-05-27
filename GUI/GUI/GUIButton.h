#pragma once
#include "GUIObject.h"
#include "TextureManager.h"

class GUIButton : public GUIObject{

public:
	GUIButton();
	GUIButton(int _width, int _height, int _x, int _y, std::string _text, sf::Color _color, sf::Color _h_color, sf::Color _c_color, sf::Font *_font);
	GUIButton(int _width, int _height, int _x, int _y, std::string _text, sf::Font *_font, std::string _texture_path);
	~GUIButton();

	void Render(sf::RenderWindow *_window) override;
	void Update(sf::RenderWindow *_window, float _delta) override;

	void SetPosition(sf::Vector2f _pos) override;
	void SetText(std::string _text) override;
	std::string GetText() override;
	bool Contains(sf::Vector2i _pos) override;

	bool IsClicked();
private:
	sf::Vector2f size;
	sf::RectangleShape shape;
	sf::Color color, h_color, c_color;

	sf::Text button_text;
	std::string text;

	bool clicked, c_state, p_state;

	bool texture_button;
	sf::Texture* button_texture;
	//sf::RectangleShape button_rec;
};