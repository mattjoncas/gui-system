#pragma once
#include <SFML/Graphics.hpp>

class GUIObject{

public:
	GUIObject();
	~GUIObject();

	float x, y;

	virtual void Render(sf::RenderWindow *_window);
	virtual void Update(sf::RenderWindow *_window, float _delta);

	//set gui objct centred
	void SetCentred(bool _centred);
	//set gui object position
	virtual void SetPosition(sf::Vector2f _pos);
	//set gui objects string value
	virtual void SetText(std::string _text);
	//get gui objects string value
	virtual std::string GetText();
	//returns true if gui objects bounds contain the given screen position
	virtual bool Contains(sf::Vector2i _pos);
	//lerp
	virtual void Lerp(sf::Vector2f _target, float _lerp_time);

	inline bool Active(){
		return active;
	}
	inline void SetActive(bool _isActive){
		active = _isActive;
	}
	inline bool IsTemp(){
		return temporary;
	}
	inline void SetTemporary(){
		temporary = true;
	}
protected:
	bool active, centred, lerping = false, temporary = false;

	sf::Vector2f lerp_start, lerp_end;
	float lerp_time, lerp_end_time;
};