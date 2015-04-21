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
		static GUIManager& GetInstance(bool gui_cursor);
		static void ResetInstance();
		~GUIManager();
		
		/*
		func: creates and binds a new instance of a menu, which gui objects can be added to
		return: index of new menu
		*/
		int AddMenu();
		/*
		func: creates and binds a new menu but with background color
		param:
			background color for menu.
		return: index of new menu
		*/
		int AddMenu(sf::Color background_color);
		/*
		func: bind a menu by it's index. binding -1 will undbind all menus.
		param: 
			menu index [returned from AddMenu()]
		*/
		void BindMenu(int menu_index);
		/*
		func: add a new default empty gui object to the specified menu
		param:
			menu index to add new gui object to.
		*/
		void AddObject(int menu_index);
		/*
		func: remove gui object from the specified menu
		param:
			menu index to remove object from.
			name of object to remove.
		*/
		void RemoveObject(int menu_index, std::string _name);
		/*
		func: add a 3 colored button to specified menu
		param:
			menu index to add button to.
			name to assign to new button object.
			width of button on the screen.
			height of button on the screen.
			horizontal screen position.
			vertical screen position.
			position button based on centre, rather then top left corner.
			text displayed on the button object.
			main button color.
			hover button color.
			click button color.
			font name to be used.
		*/
		void AddButton(int menu_index, std::string _name, int _width, int _height, int _x, int _y, bool _isCentred, std::string _text, sf::Color _color, sf::Color _hColor, sf::Color _cColor, std::string _font_name);
		/*
		func: add a textured button to specified menu
		param:
		menu index to add button to.
		name to assign to new button object.
		width of button on the screen.
		height of button on the screen.
		horizontal screen position.
		vertical screen position.
		position button based on centre, rather then top left corner.
		text displayed on the button object.
		font name to be used.
		texture path to be used for button
		*/
		void AddButton(int menu_index, std::string _name, int _width, int _height, int _x, int _y, bool _isCentred, std::string _text, std::string _font_name, std::string _texture_path);
		/*
		func: add a text field to a menu
		param: 
			menu index to add text to.
			name to assign to new text object.
			horizontal screen position.
			vertical screen position.
			position object based on centre, rather then top left corner.
			text to be displayed
			text color.
			font name to be used.
			font size.
			fade in time value, NULL for no fade in.
		*/
		void AddText(int menu_index, std::string _name, int _x, int _y, bool _isCentred, std::string _text, sf::Color _color, std::string _font_name, int _font_size, float _fade);
		/*
		func: add a typeable text box to a menu
		param:
		menu index to add text box to.
		name to assign to new text box object.
		width of new text box.
		height of new text box, height determines size of text.
		horizontal screen position.
		vertical screen position.
		position object based on centre, rather then top left corner.
		default text to be displayed in text box
		color to be used for text box.
		font name to be used.
		*/
		void AddTextBox(int menu_index, std::string _name, int _width, int _height, int _x, int _y, bool _isCentred, std::string _text, sf::Color _color, std::string _font_name);
		/*
		func: add a slider to a menu
		param:
		menu index to add slider to.
		name to assign to new slider object.
		width of new slider.
		height of new slider.
		horizontal screen position.
		vertical screen position.
		position object based on centre, rather then top left corner.
		text inside of slider, empty string for blank slider.
		border color of slider.
		inside color of slider.
		color of actual slider.
		font name to be used.
		*/
		void AddSlider(int menu_index, std::string _name, int _width, int _height, int _x, int _y, bool _isCentred, std::string _text, sf::Color _m_color, sf::Color _i_color, sf::Color _s_color, std::string _font_name);
		/*
		func: renders the currently binded menu and all of it's gui objects
		param: 
			sfml window instance.
		*/
		void Render(sf::RenderWindow *_window);
		/*
		func: updates the currently binded menu
		param:
			sfml window instance.
			delta time value.
		*/
		void Update(sf::RenderWindow *_window, float _delta);
		/*
		func: check if button is currently being clicked.
		param:
			name of button to be checked.
		return: true if button is currently being clicked.
		*/
		bool ButtonClicked(std::string _name);
		/*
		func: set a gui object to be centred at its position
		param:
			name of gui object to be updated.
			should object be centred?
		*/
		void SetCentred(std::string _name, bool _centred);
		/*
		func: set the position of a gui object
		param:
			name of gui object to be updated.
			new position of gui object.
		*/
		void SetPosition(std::string _name, sf::Vector2f new_pos);
		/*
		func: get the position of a gui object
		param:
			name of gui object.
		return: the current position of gui object.
		*/
		sf::Vector2f GetPosition(std::string _name);
		/*
		func: set the text of a gui object
		param:
			name of gui object to be updated.
			new text for the gui object.
		*/
		void SetText(std::string _name, std::string _text);
		/*
		func: get the text of a gui object
		param:
			name of gui object.
		return: the text of gui object.
		*/
		std::string GetText(std::string _name);
		/*
		func: set if a gui object is active
		param:
			name of gui object to be set.
			is the object active.
		*/
		void SetActive(std::string _name, bool _isActive);
		/*
		func: set a gui object to be temporary.
		*temporary gui objects will automatically be removed when the menu it is within is unbinded.
		param:
		name of gui object to be set.
		*/
		void SetTemporary(std::string name);
		/*
		func: input for currently selected text box
		param:
			character to be added, NULL will remove last character of text box.
		*/
		void TextBoxInput(char _c);
		/*
		func: check if gui object is selected
		param:
			name of gui object to be checked.
		return: true if object is selected.
		*/
		bool IsSelected(std::string _name);
		/*
		func: select a gui object. [example: select a text box for typing]
		param:
			name of gui object to be selected.
		*/
		void Select(std::string _name);
		/*
		func: unselect all gui objects in current menu.
		*/
		void Unselect();
		//hide text inside a textbox [replaces display text with '****']
		/*
		func: set a text box to use hidden text [hidden text displayed as '***']
		param:
			name of text box to be updated.
			should text box be hidden?
		*/
		void SetTextBoxHidden(std::string _name, bool _isHidden);
		/*
		func: set a gui object to lerp from its current screen position to a new position.
		param:
			name of gui object to be be lerped.
			new target screen position.
			time that lerp will tke to complete.
		*/
		void Lerp(std::string _name, sf::Vector2f _target, float lerp_time);

		/*
		func: check if cursor is currently hovering over any type of gui object.
		return: true if cursor is currently over a gui object.
		*/
		bool CursorOverGUI();

		/*
		func: poll for gui events using an instance of gui::Event. [Examples: Button event, Slider event]
		as events happen they will be added to the list until they are check.
		handle events using the passed in instance of g_event.
		returns true if an event was polled in this call.
		param:
			instance of a Event variable.
		return: true if event was polled.
		*/
		bool PollEvent(Event &g_event);
		/*
		func: pause the gui manager to stop objects from being updated and events from firing.
		[needed since in SFML you currently can't check if window is in focus or not]
		param:
			bool for if you would like to pause or unpause the gui manager.
		*/
		void Pause(bool _is_paused);
	private:
		static GUIManager *instance;
		GUIManager();
		GUIManager(bool gui_cursor);

		int current;
		bool cursor;
		bool paused;

		//std::vector<std::map<std::string, GUIObject*>> menus;
		std::vector<Menu*> menu;
		//loads a font from the 'fonts' folder
		void LoadFont(std::string _font_name);
		std::map<std::string, sf::Font> fonts;

		bool cursor_over_gui;

		void RemoveTempObjects();
		//events
		std::vector<Event*> events;

		void AddCursor();
		sf::Texture cursor_texture;
		sf::RectangleShape cursor_rec;
	};

}