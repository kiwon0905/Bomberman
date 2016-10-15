#pragma once
#include "resourcemanager.h"
#include <SFML\Graphics.hpp>

class TextureResourceManager :public ResourceManager<sf::Texture>
{
	friend class TextureResource;
	TextureResourceManager(){};
	~TextureResourceManager(){};
};

