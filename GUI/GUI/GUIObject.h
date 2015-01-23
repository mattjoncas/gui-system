#pragma once
#include <SFML/Graphics.hpp>

namespace gui{

	class GUIObject{

	public:
		GUIObject();
		~GUIObject();

		float x, y;

		virtual void Render(sf::RenderWindow *_window);
		virtual void Update(sf::RenderWindow *_window, float _delta);

		void SetCentred(bool _centred);
		virtual void SetPosition(sf::Vector2f _pos);
		virtual void SetText(std::string _text);
		virtual bool Contains(sf::Vector2i _pos);

		bool Active();
		void SetActive(bool _isActive);
	protected:
		bool active, centred;
	};

}