#pragma once
#include "GUIObject.h"

namespace gui{
	class GUISlider : public GUIObject{
	public:
		GUISlider();
		GUISlider(int _width, int _height, int _x, int _y, std::string _text, sf::Color _m_color, sf::Color _i_color, sf::Color _s_color, sf::Font *_font);
		~GUISlider();

		void Render(sf::RenderWindow *_window) override;
		void Update(sf::RenderWindow *_window, float _delta) override;

		void SetPosition(sf::Vector2f _pos) override;
		void SetText(std::string _text) override;
		std::string GetText() override;
		bool Contains(sf::Vector2i _pos) override;
	private:
		sf::RectangleShape main_box, inside_box, slider_box;
		sf::Color m_color, i_color, s_color;

		sf::Text slider_text;
		std::string text;

		int slider_value;
	};

}