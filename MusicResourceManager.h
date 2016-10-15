#pragma once
#include "resourcemanager.h"
#include <SFML\Audio.hpp>

class MusicResourceManager :public ResourceManager<sf::Music>
{
	friend class MusicResource;
	MusicResourceManager(){};
	~MusicResourceManager(){};
};

