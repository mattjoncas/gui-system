#pragma once
#include "GUIObject.h"

namespace gui{

	class GUIText : public GUIObject{
	public:
		GUIText();
		GUIText(int _x, int _y, std::string _text, sf::Color _color, sf::Font *_font, int _font_size);
		~GUIText();

		void Render(sf::RenderWindow *_window) override;
		void Update(sf::RenderWindow *_window, float _delta) override;

		void SetPosition(sf::Vector2f _pos) override;
		void SetText(std::string _text) override;
		std::string GetText() override;
		bool Contains(sf::Vector2i _pos) override;
	private:
		sf::Text text_object;
		std::string text;

		sf::Color color;
	};

}