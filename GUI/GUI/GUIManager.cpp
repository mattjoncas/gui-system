#include "GUIManager.h"

namespace gui{

	GUIManager::GUIManager(){
		current = 0;
	}

	GUIManager::~GUIManager(){
		//delete all collections of gui objects
		for (int i = 0; i < menus.size(); i++){
			for (auto it = menus[i].begin(); it != menus[i].end(); ++it){
				delete it->second;
			}
		}
		menus.clear();
	}

	int GUIManager::AddMenu(){
		menus.push_back(std::map<std::string, GUIObject*>());
		current = menus.size() - 1;
		return current;
	}
	void GUIManager::BindMenu(int menu_index){
		if (menu_index < menus.size()){
			current = menu_index;
		}
		else{
			printf("menu index out of range.\n");
		}
	}

	void GUIManager::AddObject(int menu_index){
		if (menu_index < menus.size()){
			menus[menu_index].insert(std::pair<std::string, GUIObject*>("object", new GUIObject()));
		}
		else{
			printf("menu index out of range.\n");
		}
		//objects.insert(std::pair<std::string, GUIObject*>("object", new GUIObject()));
	}
	void GUIManager::AddButton(int menu_index, std::string _name, int _width, int _height, int _x, int _y, std::string _text, sf::Color _color, sf::Color _hColor, sf::Color _cColor, std::string _font_name){
		LoadFont(_font_name);
		if (menu_index < menus.size()){
			menus[menu_index].insert(std::pair<std::string, GUIObject*>(_name, new GUIButton(_width, _height, _x, _y, _text, _color, _hColor, _cColor, &fonts.find(_font_name)->second)));
		}
		else{
			printf("menu index out of range.\n");
		}
		//objects.insert(std::pair<std::string, GUIObject*>(_name, new GUIButton(_width, _height, _x, _y, _text, _color, _hColor, _cColor, &fonts.find(_font_name)->second)));
	}
	void GUIManager::AddText(int menu_index, std::string _name, int _x, int _y, std::string _text, sf::Color _color, std::string _font_name, int _font_size){
		LoadFont(_font_name);
		if (menu_index < menus.size()){
			menus[menu_index].insert(std::pair<std::string, GUIObject*>(_name, new GUIText(_x, _y, _text, _color, &fonts.find(_font_name)->second, _font_size)));
		}
		else{
			printf("menu index out of range.\n");
		}
		//objects.insert(std::pair<std::string, GUIObject*>(_name, new GUIText(_x, _y, _text, _color, &fonts.find(_font_name)->second, _font_size)));
	}
	void GUIManager::AddTextBox(int menu_index, std::string _name, int _width, int _height, int _x, int _y, std::string _text, sf::Color _color, std::string _font_name){
		LoadFont(_font_name);
		if (menu_index < menus.size()){
			menus[menu_index].insert(std::pair<std::string, GUIObject*>(_name, new GUITextBox(_width, _height, _x, _y, _text, _color, &fonts.find(_font_name)->second)));
		}
		else{
			printf("menu index out of range.\n");
		}
		//objects.insert(std::pair<std::string, GUIObject*>("text_box", new GUITextBox(280, 40, 50, 50, "type here.", sf::Color(9, 43, 106, 255), &fonts.find("fonts/TF2.ttf")->second)));
	}

	void GUIManager::Render(sf::RenderWindow *_window){
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glUseProgram(0);
		glBindVertexArray(0);
		_window->pushGLStates();

		std::map<std::string, GUIObject*>::iterator it;
		for (it = menus[current].begin(); it != menus[current].end(); it++){
			if (it->second->Active()){
				it->second->Render(_window);
			}
		}

		_window->popGLStates();
	}
	void GUIManager::Update(sf::RenderWindow *_window, float _delta){
		cursor_over_gui = false;
		std::map<std::string, GUIObject*>::iterator it;
		for (it = menus[current].begin(); it != menus[current].end(); it++){
			if (it->second->Active()){
				it->second->Update(_window, _delta);
				if (!cursor_over_gui){
					sf::Vector2i _pos = sf::Mouse::getPosition(*_window);
					cursor_over_gui = it->second->Contains(_pos);
				}
			}
		}
	}

	bool GUIManager::ButtonClicked(std::string _name){
		std::map<std::string, GUIObject*>::iterator b = menus[current].find(_name);
		if (b != menus[current].end()){
			return dynamic_cast<GUIButton*>(b->second)->IsClicked();
		}
		else{
			return false;
		}
	}
	void GUIManager::SetCentred(std::string _name, bool _centred){
		std::map<std::string, GUIObject*>::iterator t = menus[current].find(_name);
		if (t != menus[current].end()){
			t->second->SetCentred(_centred);
		}
	}
	void GUIManager::SetPosition(std::string _name, sf::Vector2f new_pos){
		std::map<std::string, GUIObject*>::iterator t = menus[current].find(_name);
		if (t != menus[current].end()){
			t->second->SetPosition(new_pos);
		}
	}
	void GUIManager::SetText(std::string _name, std::string _text){
		std::map<std::string, GUIObject*>::iterator t = menus[current].find(_name);
		if (t != menus[current].end()){
			t->second->SetText(_text);
		}
	}
	void GUIManager::SetActive(std::string _name, bool _isActive){
		std::map<std::string, GUIObject*>::iterator t = menus[current].find(_name);
		if (t != menus[current].end()){
			t->second->SetActive(_isActive);
		}
	}

	void GUIManager::TextBoxInput(char _c){
		std::map<std::string, GUIObject*>::iterator it;
		for (it = menus[current].begin(); it != menus[current].end(); it++){
			if (it->second->Active()){
				GUITextBox *b = dynamic_cast<GUITextBox*>(it->second);
				if (b){
					if (b->Selected()){
						b->AddChar(_c);
					}
				}
			}
		}
	}
	void GUIManager::Unselect(){
		std::map<std::string, GUIObject*>::iterator it;
		for (it = menus[current].begin(); it != menus[current].end(); it++){
			if (it->second->Active()){
				GUITextBox *b = dynamic_cast<GUITextBox*>(it->second);
				if (b){
					b->Unselect();
				}
			}
		}
	}

	std::string GUIManager::GetText(std::string _name){
		std::map<std::string, GUIObject*>::iterator b = menus[current].find(_name);
		if (b != menus[current].end()){
			return dynamic_cast<GUITextBox*>(b->second)->GetText();
		}
		else{
			return false;
		}
	}

	void GUIManager::LoadFont(std::string _font_name){
		std::map<std::string, sf::Font>::iterator it = fonts.find(_font_name);
		//add font since it isn't already loaded
		if (it == fonts.end()){
			printf("font loaded.\n");
			sf::Font new_font;
			new_font.loadFromFile("fonts/" + _font_name);
			fonts.insert(std::pair<std::string, sf::Font>(_font_name, new_font));
		}
	}

	bool GUIManager::CursorOverGUI(){
		return cursor_over_gui;
	}

}