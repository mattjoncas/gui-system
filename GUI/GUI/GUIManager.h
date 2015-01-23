#pragma once

#include <gl/glew.h>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

#include "GUIObject.h"
#include "GUIButton.h"
#include "GUIText.h"
#include "GUITextBox.h"

namespace gui{

	class GUIManager{

	public:
		GUIManager();
		~GUIManager();

		//creates and binds new menu
		int AddMenu();
		//binds menu
		void BindMenu(int menu_index);
		//add a basic gui object to a menu
		void AddObject(int menu_index);
		//add a gui button to a menu
		void AddButton(int menu_index, std::string _name, int _width, int _height, int _x, int _y, std::string _text, sf::Color _color, sf::Color _hColor, sf::Color _cColor, std::string _font_name);
		//add a gui text field to a menu
		void AddText(int menu_index, std::string _name, int _x, int _y, std::string _text, sf::Color _color, std::string _font_name, int _font_size);
		//add a gui text box to a menu
		void AddTextBox(int menu_index, std::string _name, int _width, int _height, int _x, int _y, std::string _text, sf::Color _color, std::string _font_name);
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
		//set the text of a gui object
		void SetText(std::string _name, std::string _text);
		//get the string within a gui object
		std::string GetText(std::string _name);
		//set if a gui object is active [unbinded objects are not active||will not render/update if not active]
		void SetActive(std::string _name, bool _isActive);
		//character input for currently selected gui text box
		void TextBoxInput(char _c);
		//unselect all gui objects
		void Unselect();

		//is mouse cursor over an gui objects
		bool CursorOverGUI();
	private:
		int current;

		std::vector<std::map<std::string, GUIObject*>> menus;
		//loads a font from the 'fonts' folder
		void LoadFont(std::string _font_name);
		std::map<std::string, sf::Font> fonts;

		bool cursor_over_gui;
	};

}