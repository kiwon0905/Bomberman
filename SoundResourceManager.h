#pragma once
#include "resourcemanager.h"
#include <SFML/Audio.hpp>

class SoundResourceManager :public ResourceManager<sf::SoundBuffer>
{
	friend class SoundResource;
	SoundResourceManager(){};
	~SoundResourceManager(){};
};

