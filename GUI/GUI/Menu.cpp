#include "Menu.h"

namespace gui{
	Menu::Menu(){

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