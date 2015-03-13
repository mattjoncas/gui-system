#pragma once


#include "GUIObject.h"
#include "GUIButton.h"

namespace gui{

	class Menu{
	public:
		Menu();
		~Menu();

		std::map<std::string, GUIObject*> items;

		//update
		void Update(sf::RenderWindow *_window, float _delta);
		//render menu
		void Render(sf::RenderWindow *_window);

		void AddItem(std::string _name, GUIObject *_item);
	private:
		

	};

}