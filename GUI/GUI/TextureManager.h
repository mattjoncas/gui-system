#pragma once
#include <SFML/Graphics.hpp>

class TextureManager{
private:
	static TextureManager *instance;
	std::map<std::string, sf::Texture> textures;

	TextureManager();
	bool CheckLoaded(std::string _file);
public:
	~TextureManager();

	static TextureManager& GetInstance();
	//load a texture, returns its index in vector
	sf::Texture& LoadTexture(std::string _path);
};

