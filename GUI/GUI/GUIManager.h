#pragma once

#include <gl/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

#include "Menu.h"
#include "GUIObject.h"
#include "GUIButton.h"
#include "GUIText.h"
#include "GUITextBox.h"
#include "GUISlider.h"

#include "Event.h"

namespace gui{

	class GUIManager{
	public:
		GUIManager();
		GUIManager(bool gui_cursor);
		~GUIManager();

		//creates and binds new menu
		int AddMenu();
		//create a menu with a background color
		int AddMenu(sf::Color background_color);
		//bind a menu by index [binding -1 will unbind all menus]
		void BindMenu(int menu_index);
		//add a basic gui object to a menu
		void AddObject(int menu_index);
		//remove a gui object from a menu
		void RemoveObject(int menu_index, std::string _name);
		//add a gui button to a menu
		void AddButton(int menu_index, std::string _name, int _width, int _height, int _x, int _y, bool _isCentred, std::string _text, sf::Color _color, sf::Color _hColor, sf::Color _cColor, std::string _font_name);
		void AddButton(int menu_index, std::string _name, int _width, int _height, int _x, int _y, bool _isCentred, std::string _text, std::string _font_name, std::string _texture_path);
		//add a gui text field to a menu
		void AddText(int menu_index, std::string _name, int _x, int _y, bool _isCentred, std::string _text, sf::Color _color, std::string _font_name, int _font_size, float _fade);
		//add a gui text box to a menu
		void AddTextBox(int menu_index, std::string _name, int _width, int _height, int _x, int _y, bool _isCentred, std::string _text, sf::Color _color, std::string _font_name);
		//add a gui slider to a menu
		void AddSlider(int menu_index, std::string _name, int _width, int _height, int _x, int _y, bool _isCentred, std::string _text, sf::Color _m_color, sf::Color _i_color, sf::Color _s_color, std::string _font_name);
		//render binded menu
		void Render(sf::RenderWindow *_window);
		//update binded menu
		void Update(sf::RenderWindow *_window, float _delta);
		//check if button is clicked
		bool ButtonClicked(std::string _name);
		//set if a gui object should be centred at its position
		void SetCentred(std::string _name, bool _centred);
		//set a gui objects position
		void SetPosition(std::string _name, sf::Vector2f new_pos);
		//get on screen position of gui object
		sf::Vector2f GetPosition(std::string _name);
		//set the text of a gui object
		void SetText(std::string _name, std::string _text);
		//get the string within a gui object
		std::string GetText(std::string _name);
		//set if a gui object is active [unbinded objects are not active||will not render/update if not active]
		void SetActive(std::string _name, bool _isActive);
		//character input for currently selected gui text box
		void TextBoxInput(char _c);
		//returns true if gui object is selected
		bool IsSelected(std::string _name);
		//select a gui object [example: select a text box for typing]
		void Select(std::string _name);
		//unselect all gui objects
		void Unselect();
		//hide text inside a textbox [replaces display text with '****']
		void SetTextBoxHidden(std::string _name, bool _isHidden);
		//lerp a gui object
		void Lerp(std::string _name, sf::Vector2f _target, float lerp_time);

		//is mouse cursor over an gui objects
		bool CursorOverGUI();

		//events
		bool PollEvent(Event &g_event);

		void Pause(bool _is_paused);
	private:
		int current;
		bool cursor;

		bool paused;

		//std::vector<std::map<std::string, GUIObject*>> menus;
		std::vector<Menu*> menu;
		//loads a font from the 'fonts' folder
		void LoadFont(std::string _font_name);
		std::map<std::string, sf::Font> fonts;

		bool cursor_over_gui;

		//events
		std::vector<Event*> events;

		void AddCursor();
		sf::Texture cursor_texture;
		sf::RectangleShape cursor_rec;
	};

}