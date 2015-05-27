#include "TextureManager.h"


TextureManager* TextureManager::instance = nullptr;

TextureManager::TextureManager(){
	
}

TextureManager::~TextureManager(){

}

TextureManager& TextureManager::GetInstance(){
	if (instance == nullptr){
		instance = new TextureManager();
	}
	return *instance;
}

sf::Texture& TextureManager::LoadTexture(std::string _path){
	if (!CheckLoaded(_path)){
		sf::Texture new_texture;
		new_texture.loadFromFile(_path);
		textures.insert(std::pair<std::string, sf::Texture>(_path, new_texture));

		return textures.find(_path)->second;
	}
	return textures.find(_path)->second;
}

bool TextureManager::CheckLoaded(std::string _file){
	std::map<std::string, sf::Texture>::iterator it = textures.find(_file);
	if (it == textures.end()){
		return false;
	}
	return true;
}
