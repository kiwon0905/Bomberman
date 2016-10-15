#pragma once
#include "resourcemanager.h"
#include <SFML\Graphics.hpp>

class FontResourceManager :public ResourceManager<sf::Font>
{
	friend class FontResource;
	FontResourceManager(){};
	~FontResourceManager(){};
};

