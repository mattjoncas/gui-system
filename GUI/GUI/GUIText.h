#pragma once
#include "GUIObject.h"

class GUIText : public GUIObject{
public:
	GUIText();
	GUIText(int _x, int _y, std::string _text, sf::Color _color, sf::Font *_font, int _font_size, float _fade);
	~GUIText();

	void Render(sf::RenderWindow *_window) override;
	void Update(sf::RenderWindow *_window, float _delta) override;

	void SetPosition(sf::Vector2f _pos) override;
	void SetText(std::string _text) override;
	std::string GetText() override;
	bool Contains(sf::Vector2i _pos) override;
	void Lerp(sf::Vector2f target_position, float _lerp_time) override;
private:
	sf::Text text_object;
	std::string text;

	sf::Color color;

	float fade_time, fade_timer;
};