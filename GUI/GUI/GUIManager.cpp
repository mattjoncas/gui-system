#include "GUIManager.h"

namespace gui{

	GUIManager::GUIManager(){
		current = -1;
		cursor = false;
		paused = false;
	}
	GUIManager::GUIManager(bool gui_cursor){
		current = -1;
		if (gui_cursor){
			AddCursor();
		}
		paused = false;
	}

	GUIManager::~GUIManager(){
		for (std::vector<Menu*>::iterator iter = menu.begin(); iter != menu.end(); ++iter){
			delete((*iter));
		}
		for (std::vector<Event*>::iterator iter = events.begin(); iter != events.end(); ++iter){
			delete((*iter));
		}
	}

	int GUIManager::AddMenu(){
		menu.push_back(new Menu());
		current = menu.size() - 1;
		return current;
	}
	int GUIManager::AddMenu(sf::Color background_color){
		menu.push_back(new Menu(background_color));
		current = menu.size() - 1;
		return current;
	}
	void GUIManager::BindMenu(int menu_index){
		if (menu_index < int(menu.size())){
			current = menu_index;
		}
		else{
			printf("menu index out of range [bind menu]. \n");
		}
	}

	void GUIManager::AddObject(int menu_index){
		if (menu_index < menu.size()){
			menu[menu_index]->AddItem("object", new GUIObject());
		}
		else{
			printf("menu index out of range.\n");
		}
	}
	void GUIManager::RemoveObject(int menu_index, std::string _name){
		std::map<std::string, GUIObject*>::iterator t = menu[menu_index]->items.find(_name);
		if (t != menu[menu_index]->items.end()){
			delete t->second;
			menu[menu_index]->items.erase(t);
		}
	}
	void GUIManager::AddButton(int menu_index, std::string _name, int _width, int _height, int _x, int _y, bool _isCentred, std::string _text, sf::Color _color, sf::Color _hColor, sf::Color _cColor, std::string _font_name){
		LoadFont(_font_name);
		if (menu_index < menu.size()){
			GUIButton* b = new GUIButton(_width, _height, _x, _y, _text, _color, _hColor, _cColor, &fonts.find(_font_name)->second);
			b->SetCentred(_isCentred);
			menu[menu_index]->AddItem(_name, b);
		}
		else{
			printf("menu index out of range.\n");
		}
	}
	void GUIManager::AddButton(int menu_index, std::string _name, int _width, int _height, int _x, int _y, bool _isCentred, std::string _text, std::string _font_name, std::string _texture_path){
		LoadFont(_font_name);
		if (menu_index < menu.size()){
			GUIButton* b = new GUIButton(_width, _height, _x, _y, _text, &fonts.find(_font_name)->second, _texture_path);
			b->SetCentred(_isCentred);
			menu[menu_index]->AddItem(_name, b);
		}
		else{
			printf("menu index out of range.\n");
		}
	}
	void GUIManager::AddText(int menu_index, std::string _name, int _x, int _y, bool _isCentred, std::string _text, sf::Color _color, std::string _font_name, int _font_size, float _fade){
		LoadFont(_font_name);
		if (menu_index < menu.size()){
			GUIText* t = new GUIText(_x, _y, _text, _color, &fonts.find(_font_name)->second, _font_size, _fade);
			t->SetCentred(_isCentred);
			menu[menu_index]->AddItem(_name, t);
		}
		else{
			printf("menu index out of range.\n");
		}
	}
	void GUIManager::AddTextBox(int menu_index, std::string _name, int _width, int _height, int _x, int _y, bool _isCentred, std::string _text, sf::Color _color, std::string _font_name){
		LoadFont(_font_name);
		if (menu_index < menu.size()){
			GUITextBox* t = new GUITextBox(_width, _height, _x, _y, _text, _color, &fonts.find(_font_name)->second);
			t->SetCentred(_isCentred);
			menu[menu_index]->AddItem(_name, t);
		}
		else{
			printf("menu index out of range.\n");
		}
	}
	void GUIManager::AddSlider(int menu_index, std::string _name, int _width, int _height, int _x, int _y, bool _isCentred, std::string _text, sf::Color _m_color, sf::Color _i_color, sf::Color _s_color, std::string _font_name){
		LoadFont(_font_name);
		if (menu_index < menu.size()){
			GUISlider* s = new GUISlider(_width, _height, _x, _y, _text, _m_color, _i_color, _s_color, &fonts.find(_font_name)->second);
			s->SetCentred(_isCentred);
			menu[menu_index]->AddItem(_name, s);
		}
		else{
			printf("menu index out of range.\n");
		}
	}

	void GUIManager::Render(sf::RenderWindow *_window){
		if (current >= 0){
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glUseProgram(0);
			glBindVertexArray(0);
			_window->pushGLStates();

			menu[current]->Render(_window);
			if (cursor){
				_window->draw(cursor_rec);
			}
			_window->popGLStates();
		}
	}
	void GUIManager::Update(sf::RenderWindow *_window, float _delta){
		cursor_over_gui = false;
		if (current >= 0 && !paused){
			std::map<std::string, GUIObject*>::iterator it;
			for (it = menu[current]->items.begin(); it != menu[current]->items.end(); it++){
				if (it->second->Active()){
					it->second->Update(_window, _delta);
					if (!cursor_over_gui){
						sf::Vector2i _pos = sf::Mouse::getPosition(*_window);
						cursor_over_gui = it->second->Contains(_pos);
					}
					GUIButton *b = dynamic_cast<GUIButton*>(it->second);
					if (b){
						if (b->IsClicked()){
							events.push_back(new Event(b, it->first));
						}
					}
					GUISlider *s = dynamic_cast<GUISlider*>(it->second);
					if (s){
						if (s->Updated()){
							events.push_back(new Event(s, it->first));
						}
					}
				}
			}
			if (cursor){
				_window->setMouseCursorVisible(false);
				cursor_rec.setPosition(sf::Vector2f(sf::Mouse::getPosition(*_window).x - cursor_rec.getSize().x / 2.0f, sf::Mouse::getPosition(*_window).y - 1));
			}
		}
	}

	bool GUIManager::ButtonClicked(std::string _name){
		std::map<std::string, GUIObject*>::iterator b = menu[current]->items.find(_name);
		if (b != menu[current]->items.end()){
			return dynamic_cast<GUIButton*>(b->second)->IsClicked();
		}
		else{
			return false;
		}
	}
	void GUIManager::SetCentred(std::string _name, bool _centred){
		std::map<std::string, GUIObject*>::iterator t = menu[current]->items.find(_name);
		if (t != menu[current]->items.end()){
			t->second->SetCentred(_centred);
		}
	}
	void GUIManager::SetPosition(std::string _name, sf::Vector2f new_pos){
		std::map<std::string, GUIObject*>::iterator t = menu[current]->items.find(_name);
		if (t != menu[current]->items.end()){
			t->second->SetPosition(new_pos);
		}
	}
	sf::Vector2f GUIManager::GetPosition(std::string _name){
		std::map<std::string, GUIObject*>::iterator t = menu[current]->items.find(_name);
		if (t != menu[current]->items.end()){
			return sf::Vector2f(t->second->x, t->second->y);
		}
	}
	void GUIManager::SetText(std::string _name, std::string _text){
		std::map<std::string, GUIObject*>::iterator t = menu[current]->items.find(_name);
		if (t != menu[current]->items.end()){
			t->second->SetText(_text);
		}
	}
	void GUIManager::SetActive(std::string _name, bool _isActive){
		std::map<std::string, GUIObject*>::iterator t = menu[current]->items.find(_name);
		if (t != menu[current]->items.end()){
			t->second->SetActive(_isActive);
		}
	}

	void GUIManager::TextBoxInput(char _c){
		std::map<std::string, GUIObject*>::iterator it;
		for (it = menu[current]->items.begin(); it != menu[current]->items.end(); it++){
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
	
	bool GUIManager::IsSelected(std::string _name){
		std::map<std::string, GUIObject*>::iterator it;
		for (it = menu[current]->items.begin(); it != menu[current]->items.end(); it++){
			if (it->second->Active() && it->first == _name){
				GUITextBox *b = dynamic_cast<GUITextBox*>(it->second);
				if (b){
					return b->Selected();
				}
			}
		}
		return false;
	}
	void GUIManager::Select(std::string _name){
		std::map<std::string, GUIObject*>::iterator it;
		for (it = menu[current]->items.begin(); it != menu[current]->items.end(); it++){
			if (it->second->Active() && it->first == _name){
				GUITextBox *b = dynamic_cast<GUITextBox*>(it->second);
				if (b){
					b->Select();
				}
				break;
			}
		}
	}
	void GUIManager::Unselect(){
		std::map<std::string, GUIObject*>::iterator it;
		for (it = menu[current]->items.begin(); it != menu[current]->items.end(); it++){
			if (it->second->Active()){
				GUITextBox *b = dynamic_cast<GUITextBox*>(it->second);
				if (b){
					b->Unselect();
				}
			}
		}
	}
	void GUIManager::SetTextBoxHidden(std::string _name, bool _isHidden){
		std::map<std::string, GUIObject*>::iterator it;
		for (it = menu[current]->items.begin(); it != menu[current]->items.end(); it++){
			if (it->second->Active() && it->first == _name){
				GUITextBox *b = dynamic_cast<GUITextBox*>(it->second);
				if (b){
					b->SetHidden(_isHidden);
				}
				break;
			}
		}
	}
	void GUIManager::Lerp(std::string _name, sf::Vector2f _target, float lerp_time){
		std::map<std::string, GUIObject*>::iterator t = menu[current]->items.find(_name);
		if (t != menu[current]->items.end()){
			t->second->Lerp(_target, lerp_time);
		}
	}

	std::string GUIManager::GetText(std::string _name){
		std::map<std::string, GUIObject*>::iterator b = menu[current]->items.find(_name);
		if (b != menu[current]->items.end()){
			return b->second->GetText();
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

	bool GUIManager::PollEvent(Event &g_event){
		if (events.size() > 0){
			g_event = *events[0];

			for (std::vector<Event*>::iterator iter = events.begin(); iter != events.begin() + 1; ++iter){
				delete((*iter));
			}
			events.erase(events.begin());
			return true;
		}
		return false;
	}

	void GUIManager::AddCursor(){
		if (!cursor){
			cursor_texture.loadFromFile("textures/cursor_centered.png", sf::IntRect());
			cursor_texture.setSmooth(false);

			cursor_rec.setSize(sf::Vector2f(cursor_texture.getSize().x * 0.5, cursor_texture.getSize().y * 0.5));
			cursor_rec.setTexture(&cursor_texture);
			
			cursor = true;
		}
	}

	void GUIManager::Pause(bool _is_paused){
		paused = _is_paused;
	}
}