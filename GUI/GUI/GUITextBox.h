#pragma once
#include "GUIObject.h"

#define TICK_TIME 0.5

namespace gui{

	class GUITextBox : public GUIObject{
	public:
		GUITextBox();
		GUITextBox(int _width, int _height, int _x, int _y, std::string _text, sf::Color _color, sf::Font *_font);
		~GUITextBox();

		void Render(sf::RenderWindow *_window) override;
		void Update(sf::RenderWindow *_window, float _delta) override;

		void SetPosition(sf::Vector2f _pos) override;
		void SetText(std::string _text) override;
		bool Contains(sf::Vector2i _pos) override;

		bool Selected();
		void AddChar(char _new_text);
		void Select();
		void Unselect();

		void SetHidden(bool _isHidden);

		std::string GetText() override;
	private:
		int width, height;
		bool selected;

		float current_time;

		sf::RectangleShape shape;
		sf::Color color;

		sf::Text box_text;
		sf::Text selected_text;
		std::string text;

		bool hidden_text;
		std::string HideText(std::string _string);
	};

}