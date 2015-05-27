#include "Menu.h"

Menu::Menu(){
	background = false;
}
Menu::Menu(sf::Color background_color, int screenWidth, int screenHeight){
	background = true;
	back = sf::RectangleShape(sf::Vector2f(float(screenWidth), float(screenHeight)));
	back.setPosition(sf::Vector2f(0.0f, 0.0f));
	back.setFillColor(background_color);
}
Menu::Menu(std::string background_texture, int screenWidth, int screenHeight){
	background = true;
	back = sf::RectangleShape(sf::Vector2f(float(screenWidth), float(screenHeight)));
	back.setPosition(sf::Vector2f(0.0f, 0.0f));

	back_texture = &TextureManager::GetInstance().LoadTexture(background_texture);
	back.setTexture(back_texture);
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