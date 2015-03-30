#include "Menu.h"

namespace gui{
	Menu::Menu(){
		background = false;
	}
	Menu::Menu(sf::Color back_color){
		background = true;
		back = sf::RectangleShape(sf::Vector2f(5000.0f, 5000.0f));
		back.setPosition(sf::Vector2f(0.0f, 0.0f));
		back.setFillColor(back_color);
	}

	Menu::~Menu(){
		//delete all collections of gui objects
		for (std::map<std::string, GUIObject*>::iterator it = items.begin(); it != items.end(); ++it){
			delete it->second;
		}
		items.clear();
	}

	void Menu::Update(sf::RenderWindow *_window, float _delta){
		
	}
	void Menu::Render(sf::RenderWindow *_window){
		if (background){
			_window->draw(back);
		}
		std::map<std::string, GUIObject*>::iterator it;
		for (it = items.begin(); it != items.end(); it++){
			if (it->second->Active()){
				it->second->Render(_window);
			}
		}
	}

	void Menu::AddItem(std::string _name, GUIObject *_item){
		
		items.insert(std::pair<std::string, GUIObject*>(_name, _item));
	}
}